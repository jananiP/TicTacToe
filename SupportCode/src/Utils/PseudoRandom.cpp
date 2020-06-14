#include <cmath>
#include "Utils/PseudoRandom.hpp"
#include <cstdio>
#include <ctime>


    unsigned int RandomSeed(void)
    {
	FILE        *fp = fopen("/dev/urandom", "r");    
	unsigned int s;
	int          ignore;
	
	if(fp != NULL)
	{
	    ignore = fread(&s, sizeof(unsigned int), 1, fp);    
	    fclose(fp);    	        
	}
	else
	    s = (unsigned int) time(NULL);
	
	printf("using seed: %u\n", s);
	
	
	RandomSeed(s);
	
	return s;
    }
    
    void RandomSeed(const unsigned int s)
    {
	srandom(s);
    }





    
    
    
    
    
    
