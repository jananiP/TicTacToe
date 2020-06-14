#include <cmath>
#include "Programs/TTT.hpp"
#include <cstdio>
#include <algorithm>

int temp=0, MAX_DEPTH;

double TTT::EvalState(const State s) const
{
    //add your implementation
	int size = (m_nrRows *m_nrCols) - 1;
	int row=0, col=0;
	for (int i = 0; i <= size; i++)
	{
		row = RowFromId(i);
		col = ColFromId(i);
		if (GetValueState(s,row,col)!=EMPTY)
		{
			if (CheckWin(s, row, col))
			{
				if ((Value)GetValueState(s, row, col) == FIRST)
					return 10.0;
				else
					return -10.0;
			}
		}
	}
    return 0;
}	


void TTT::BestMove(State   s, 
		   int     depth, 
		   int     remMoves, 
		   int     lastMove,
		   Value   player,
		   double *bestScore,
		   int    *bestMove) const
{
    //add your implementation
	int color = 0;
	if (player==FIRST)
		color = 1;
	else if (player==SECOND)
		color = -1;
	MAX_DEPTH = depth;
	double v=NegaMax(s,0, -HUGE_VAL,HUGE_VAL,remMoves,lastMove,color);
	*bestScore = v;
	*bestMove = temp;
	printf("\nBest move is %d",*bestMove);
}


double TTT::NegaMax(State   s, 
		    int     depth, 
		    double  alpha, 
		    double  beta, 
		    int     remMoves, 
		    int     lastMove,
		    int     color) const
{
    //add your implementation

	int size = (m_nrRows*m_nrCols) - 1;
	int row = 0;
	int col = 0;
	Value currentPlayer;
	currentPlayer = color==1?FIRST:SECOND;

	double d;

	//algorithm
	double score = EvalState(s);
	if (remMoves == 0 || score!=0 || depth==MAX_DEPTH)			//If Game over return score
	{
		//printf("\nNode Value: %f", score, depth);
		if (score > 0)						//If maximizer won
			return score - depth;
		else if (score < 0)					//If minimizer won  
			return score + depth;
		else
			return score;
	}
	int bestMove=-1;
	double v;
	if (currentPlayer == FIRST)
	{
		//Get available moves
		//v = -HUGE_VAL;
		for (int i = 0; i <= size; i++)
		{
			row = RowFromId(i);
			col = ColFromId(i);
			if (GetValueState(s, row, col) == EMPTY && EvalState(s) == 0)
			{
				State child;
				child = NewState();
				CopyState(s, child);
				SetValueState(child, row, col, currentPlayer);
				/*for (int j = 0; j <= size; j++)
					printf("%u ",child[j]);*/
				//printf("\n MAX's turn Child %d %d :", row, col);
				v=NegaMax(child, depth + 1, alpha, beta, remMoves - 1, i, (-1)*color);
				//printf("\n After processing... MAX's turn Child %d %d ", row, col);
				if (v>alpha)
				{
					alpha = v;
					bestMove = i;
					//printf("Alpha=%f v=%f ", alpha, v);
					//printf("Alpha=%f v=%f \nBest Move %d",alpha,v, bestMove);
				}
				if (alpha >= beta)
					break;
			}	//End of if
		}	//End of for loop
		//bestMove = temp;
		temp = bestMove;
		//printf("\nState %d processed.. Best Move: %d",lastMove, bestMove);
		return alpha;
	}
	else if (currentPlayer == SECOND)
	{
		//Get available moves
		//v = HUGE_VAL;
		for (int i = 0; i <= size; i++)
		{
			row = RowFromId(i);
			col = ColFromId(i);
			if (GetValueState(s, row, col) == EMPTY && EvalState(s) == 0)
			{
				State child;
				child = NewState();
				CopyState(s, child);
				SetValueState(child, row, col, currentPlayer);
				/*for (int j = 0; j <= size; j++)
					printf("%u ", child[j]);*/
				//printf("\nMIN's turn Child %d %d : ", row, col);
				double v= NegaMax(child, depth + 1, alpha, beta, remMoves - 1, i, (-1)*color);
				//printf("\nAfter processing... MIN's turn Child %d %d", row,col);
				if (v<beta)
				{
					beta = v;
					bestMove = i;
					//printf(" Beta=%f v=%f ", beta, v);
					//printf(" Beta=%f v=%f \nBest Move %d", beta,v,bestMove);
				}
				if (alpha >= beta)
					break;
			}//End of if
		}//End of for loop
		//bestMove = temp;
		temp = bestMove;
		//printf("\nState %d processed.. Best Move: %d",lastMove, bestMove);
		return beta;
	}


	return 0.0;
    
}

bool TTT::CheckWin(const State s, const int r, const int c) const
{
    const Value val  = GetValueState(s, r, c);
    int   cons = 0, end;
    
    //check row
    cons = 0; end = std::min(m_nrCols, c + m_nrToWin);
    for(int i = std::max(0, c - m_nrToWin); i < end; ++i)
	if(GetValueState(s, r, i) != val)
	    cons = 0;
	else if ((++cons) >= m_nrToWin)
	{
		//printf("Won row wise at %d %d\n",r,c);
		return true;
	}
    
    //check column

    cons = 0; end = std::min(m_nrRows, r + m_nrToWin);
    for(int i = std::max(0, r - m_nrToWin); i < end; ++i)
	if(GetValueState(s, i, c) != val)
	    cons = 0;
	else if ((++cons) >= m_nrToWin)
	{
		//printf("Won col wise at %d %d\n", r, c);
		return true;
	}
    
    //check diagonal
    cons = 0; end = 1 + std::min(m_nrToWin - 1, std::min(m_nrRows - r - 1, m_nrCols - c - 1));
    for(int i = std::max(-m_nrToWin + 1, std::max(-r, -c)); i < end; ++i)
	if(GetValueState(s, r + i, c + i) != val)
	    cons = 0;
	else if ((++cons) >= m_nrToWin)
	{
		//printf("Won diag wise at %d %d\n", r, c);
		return true;
	}
    
    //check anti-diagonal
    cons = 0; end = 1 + std::min(m_nrToWin - 1, std::min(r, m_nrCols - c - 1));
    for(int i = std::max(-m_nrToWin + 1, std::max(r - m_nrRows + 1, -c)); i < end; ++i)
    {
	if(GetValueState(s, r - i, c + i) != val)
	    cons = 0;
	else if ((++cons) >= m_nrToWin)
	{
		//printf("Won anti-diag wise at %d %d\n", r, c);
		return true;
	}
    }
    
    
    return false;
    
    
}


