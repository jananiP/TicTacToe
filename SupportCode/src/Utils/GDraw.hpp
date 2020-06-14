#ifndef UTILS__GDRAW_HPP_
#define UTILS__GDRAW_HPP_

#include <cstdlib>

#ifdef __APPLE__
#include <GLUT/glut.h>
#elif defined _WIN32
#include "Utils/glutForWindows.h"
#else
#include <GL/glut.h>
#endif

enum GDrawParam
    {
	GDRAW_MINX = 0,
	GDRAW_MINY,
	GDRAW_MAXX,
	GDRAW_MAXY,
	GDRAW_ORTHO_NEAR_PLANE,
	GDRAW_ORTHO_FAR_PLANE,
	GDRAW_NR_PARAMS
    };

double GDrawGetParam(const GDrawParam p);

void GDrawSetParam(const GDrawParam p, const double val);

void GDrawWireframe(const bool val);

void GDrawColor(const double r, const double g, const double b);

static inline void GDrawColor(const double * const rgb)
{
    GDrawColor(rgb[0], rgb[1], rgb[2]);
}

void GDrawLineWidth(const double w);

void GDrawString2D(const char s[], const double x, const double y);

void GDrawSegment2D(const double x1, const double y1,
		    const double x2, const double y2);

void GDrawSegment2D(const double p1[], const double p2[]);

void GDrawSegment2D(const double p1p2[]);

void GDrawAABox2D(const double minx, const double miny,
		  const double maxx, const double maxy);

void GDrawAABox2D(const double min[], const double max[]);

void GDrawAABox2D(const double minmax[]);

void GDrawGrid2D(const double xmin,
		 const double ymin,
		 const double xmax,
		 const double ymax,
		 const int    xNrDims,
		 const int    yNrDims);

#endif









