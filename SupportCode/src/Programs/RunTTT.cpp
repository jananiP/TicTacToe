#include "Utils/GManager.hpp"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "Utils/PseudoRandom.hpp"
#include "Programs/TTT.hpp"

class RunTTT : public GManager
{
public:
    RunTTT(void) : GManager()
    {
	m_state  = NULL;
	m_turn   = TTT::FIRST;
	m_winner = TTT::EMPTY;
	m_nrMoves= 0;
	m_lastMove = -1;
	
    }
    
    virtual ~RunTTT(void)
    {
    }
    
    virtual void HandleEventOnDisplay(void)
    {
	GManager::HandleEventOnDisplay();
	
	GDrawSetParam(GDRAW_MINX, 0);
	GDrawSetParam(GDRAW_MINY, 0);
	GDrawSetParam(GDRAW_MAXX, m_ttt.m_nrCols);
	GDrawSetParam(GDRAW_MAXY, m_ttt.m_nrRows);
	
	GDrawColor(0, 0, 0);
	GDrawGrid2D(0, 0, m_ttt.m_nrCols, m_ttt.m_nrRows, m_ttt.m_nrCols, m_ttt.m_nrRows);
	
	if(m_state)
	    for(int i = 0; i < m_ttt.m_nrRows; ++i)
		for(int j = 0; j < m_ttt.m_nrCols; ++j)
		{
		    const TTT::Value val = m_ttt.GetValueState(m_state, i, j);
		    if(val != TTT::EMPTY)
		    {
			if(val == TTT::SECOND)
			    GDrawColor(m_winner == TTT::SECOND ? 0.4 : 1, 0, 0);
			else 
			    GDrawColor(0, 0, m_winner == TTT::FIRST ? 0.4 : 1);
			GDrawAABox2D(j + 0.1,  m_ttt.m_nrRows - 1 - i + 0.1, j + 0.9, m_ttt.m_nrRows - 1 - i + 0.9);
		    }
		}
	
    }
    
    virtual bool HandleEventOnNormalKeyPress(const int key)
    {
	if(key == 's')
	{
	    double alpha    = -HUGE_VAL;
	    double beta     = HUGE_VAL;
	    int    remMoves = m_ttt.m_nrRows * m_ttt.m_nrCols - m_nrMoves;
	    double bestScore = -HUGE_VAL;
	    int    bestMove  = -1;
	    
		printf("\nkey s pressed");	
	    m_ttt.BestMove(m_state, m_depth, remMoves, m_lastMove, m_turn, &bestScore, &bestMove);
	    printf("bestScore = %f bestMove = %d %d [player = %s] [nrMoves = %d]\n", bestScore, 
		   bestMove / m_ttt.m_nrCols, bestMove % m_ttt.m_nrCols, m_turn == TTT::FIRST ? "BLUE" : "RED", m_nrMoves);
	    
	    return true;
		
	}
	else if(key == 'h')
	{
		printf("\nkey h pressed");
	    printf("EvalScore = %f\n", m_ttt.EvalState(m_state));
	    return true;
	}
	else
	    return GManager::HandleEventOnNormalKeyPress(key);
    }
    
    virtual bool HandleEventOnMouseLeftBtnDown(const int x, const int y)
    {
	if(m_winner != TTT::EMPTY && m_nrMoves < m_ttt.m_nrRows * m_ttt.m_nrCols)
	    return false;
	
	double wx, wy, wz;
	MousePosFromScreenToWorld(x, y, &wx, &wy, &wz);
	
	int r, c;
	
	c = (int) wx;
	r = m_ttt.m_nrRows  - 1 - ((int) wy);
	
	if(c >= 0 && c < m_ttt.m_nrCols && 
	   r >= 0 && r < m_ttt.m_nrRows &&
	   m_ttt.GetValueState(m_state, r, c) == TTT::EMPTY)
	{
	    printf("setting position %d %d to value %d (%s)\n", r, c, m_turn, m_turn == TTT::FIRST ? "BLUE":"RED");
	    MakeMove(r, c);
	}
	
	return true;
    }
    
    void MakeMove(const int r, const int c)
    {
	m_lastMove = m_ttt.m_nrCols * r + c;
	m_ttt.SetValueState(m_state, r, c, m_turn);
	++m_nrMoves;
	if(m_ttt.CheckWin(m_state, r, c))
	    m_winner = m_turn;
	else if(m_turn == TTT::FIRST)
	    m_turn = TTT::SECOND;
	else
	    m_turn = TTT::FIRST;

	if (m_winner)
	{
		printf("player %s won\n", m_winner == TTT::FIRST ? "BLUE" : "RED");
	}	    
    }
    
    
    TTT        m_ttt;
    TTT::State m_state;
    TTT::Value m_turn;
    TTT::Value m_winner;
    int        m_nrMoves;
    int        m_lastMove;
    int        m_depth;
    
    
};


int main(int argc, char **argv)
{
    RandomSeed();
    
/*
  ./bin/TTT
  nrRows
  nrCols
  nrToWin
  depth
*/
#ifdef OS_WINDOWS
    printf("bin\\Release\\TTT nrRows nrCols nrToWin depth\n");
#else
    printf("./bin/TTT nrRows nrCols nrToWin depth\n");
#endif    
    
    
    RunTTT gManager;
    
	printf("argc %d",argc);
	gManager.m_ttt.m_nrRows  = argc > 1 ? atoi(argv[1]) : 3;
    gManager.m_ttt.m_nrCols  = argc > 2 ? atoi(argv[2]) : 3;
    gManager.m_ttt.m_nrToWin = argc > 3 ? atoi(argv[3]) : 3;
    gManager.m_depth         = argc > 4 ? atoi(argv[4]) : 10;
    gManager.m_state = gManager.m_ttt.NewState();
    gManager.m_ttt.ClearState(gManager.m_state);
    
    printf("running with\n");
    printf(" nrRows   = %d\n", gManager.m_ttt.m_nrRows);
    printf(" nrCols   = %d\n", gManager.m_ttt.m_nrCols);
    printf(" nrToWin  = %d\n", gManager.m_ttt.m_nrToWin);
    printf(" depth    = %d\n", gManager.m_depth);
    
    gManager.MainLoop("TTT", 200, 200);
    
    return 0;
}

