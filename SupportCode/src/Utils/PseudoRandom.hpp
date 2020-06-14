#ifndef UTILS__PSEUDO_RANDOM_HPP_
#define UTILS__PSEUDO_RANDOM_HPP_

#include "Utils/Definitions.hpp"
#include <cstdlib>
 
    
/**
 *@cond
 */

/**
 *@brief Operating system specific definitions 
 */
#ifdef OS_WINDOWS
  #define srandom srand
  #define random rand
  #define RANDOM_MAX RAND_MAX
#else
  #define RANDOM_MAX 2147483647
#endif

/**
 *@endcond
 */

    /**
     *@name Seed the random number generator
     *@{
     */
    
    /**
     *@brief Set the seed for the random number generator 
     *@param s seed value
     */
    void RandomSeed(const unsigned int s);
    
    /**
     *@brief Generate and set the seed for the random number generator 
     * 
     *@returns
     *  A pseudorandom number read from the file <em>/dev/urandom</em>, 
     *  which is then used to set the seed using <em>srandom</em>
     *  \n
     *  If file <em>/dev/urandom</em> does not exist, then
     *  <em>time(NULL)</em> is used to obtain the seed. 
     */
    unsigned int RandomSeed(void);
    
    /**
     *END Seed the random number generator
     *@}
     */
    
    /**
     *@name Generate real numbers uniformly at random
     *@{
     */
    
    /**
     *@brief Generate a real number uniformly at random from the interval
     *       <em>[0, 1]</em> 
     */
    static inline double RandomUniformReal(void)
    {
	return ((double) random()) / ((double) RANDOM_MAX);
    }
    
    /**
     *@brief Generate a real number uniformly at random from the interval
     *       <em>[min, max]</em> 
     *
     *@param min left boundary of the sampling interval
     *@param max right boundary of the sampling interval
     */
    static inline double RandomUniformReal(const double min, const double max)
    {
	return min + (max - min) * RandomUniformReal();
    }
    
    /**
     *END Generate real numbers uniformly at random
     *@}
     */
    
    /**
     *@name Generate integers uniformly at random
     *@{
     */
    
    /**
     *@brief Generate an integer number uniformly at random from the
     *       interval <em>[min, max]</em> 
     *
     *@param min left boundary of the sampling interval
     *@param max right boundary of the sampling interval
     */
    static inline long RandomUniformInteger(const long min, const long max)
    {
	const long x = min + (long) RandomUniformReal(0, max - min + 1);
 	return x > max ? max : x;
   }
    
    /**
     *END Generate integer numbers uniformly at random
     *@}
     */
    
    /**
     *@name Generate boolean values uniformly at random
     *@{
     */
    
    /**
     *@brief Generate either true or false uniformly at random
     */
    static inline bool RandomUniformBoolean(void)
    {
	return RandomUniformReal() > 0.5;
    }
    
    /**
     *END Generate boolean values uniformly at random
     *@}
     */
    
    

#endif











