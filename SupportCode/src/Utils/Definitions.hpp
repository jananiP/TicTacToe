#ifndef AI__DEFINITIONS_HPP_
#define AI__DEFINITIONS_HPP_


/**
 *@cond
 */
    
/**
 *@brief Recognize operating system: Linux 
 */
#if defined (linux) || defined (__linux__)
#define OS_LINUX
#endif
    
/**
 *@brief Recognize operating system: Microsoft Windows
 */
#if defined (WINDOWS) || defined (_WIN32) || defined (__WIN32__)
#define OS_WINDOWS 
#endif
    
/**
 *@brief Recognize operating system: Macintosh OS
 */
#ifdef __APPLE__
#define OS_MAC
#endif
    
/**
 *@brief Recognize operating system: SunOS/Solaris
 */
#if defined(sun) || defined(__sun)
#define OS_SUNOS
#endif
    
/**
 *@brief Recognize compiler: GNU C/C++
 */
#ifdef __GNUC__
#define COMPILER_GNU
#endif
    
/**
 *@brief Recognize compiler: PGI
 */
#ifdef __PGI
#define COMPILER_PGI
#endif
    
/**
 *@brief Recognize compiler: Microsoft Visual Studio 
 */
#ifdef _MSC_VER
#define COMPILER_VISUAL_STUDIO
#endif
    
    
/**
 *@author Erion Plaku
 *@brief Make Visual Studio happy: avoid warnings/errors about
 *       <em>strdup</em> and <em>inline</em> 
 */
#ifdef COMPILER_VISUAL_STUDIO
#define strdup _strdup
#define inline __inline
#include <cstdlib>
#include <cmath>
static inline double round(const double x) { return (int)(floor(x + 0.5)); }
#define _CRT_SECURE_NO_WARNINGS

#endif
    
/**
 *@author Erion Plaku
 *@brief Namespace STL extension: different compilers place
 *       STL extensions in different directories and use different
 *       naming conventions for the file names 
 */
#ifdef COMPILER_PGI
#define STD_EXT_NAMESPACE _STLP_STD
#define STD_EXT_INCLUDE(fname) <fname>
#elif defined COMPILER_GNU
#define STD_EXT_NAMESPACE __gnu_cxx
#define STD_EXT_INCLUDE(fname) <ext/fname>
#else
#define STD_EXT_NAMESPACE stdext
#define STD_EXT_INCLUDE(fname) <fname>
#endif
    
/**
 *@endcond
 */

#if DEBUG
#include <cassert>
#endif



#endif
