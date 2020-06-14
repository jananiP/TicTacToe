#include "Utils/GDraw.hpp"
#include <cmath>

struct GDrawData
{
    GDrawData(void)
    {
	m_params[GDRAW_MINX] = -30;
	m_params[GDRAW_MINY] = -20;
	m_params[GDRAW_MAXX] =  30;
	m_params[GDRAW_MAXY] =  20;
	m_params[GDRAW_ORTHO_NEAR_PLANE] = -10;
	m_params[GDRAW_ORTHO_FAR_PLANE] = 10;
    }
    
    double m_params[GDRAW_NR_PARAMS];	    
};


//general	    

GDrawData* GDrawGetData(void)
{
    static GDrawData ddata;
    return &ddata;
}

double GDrawGetParam(const GDrawParam p)
{
    return GDrawGetData()->m_params[p];
}

void GDrawSetParam(const GDrawParam p, const double val)
{
    GDrawGetData()->m_params[p] = val;
}

void GDrawWireframe(const bool val)
{
    if(val)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
}

void GDrawColor(const double r, const double g, const double b)
{
    glColor3d(r, g, b);
}



void GDrawLineWidth(const double w)
{
    glLineWidth(w);
}


void GDrawString2D(const char s[], const double x, const double y)
{
    if(s)
    {
	glRasterPos2d(x, y);
	for(int i = 0; s[i] != '\0'; ++i)
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }	
}


void GDrawSegment2D(const double x1, const double y1,
		    const double x2, const double y2)
{
    glBegin(GL_LINES);
    glVertex3d(x1, y1, 0);
    glVertex3d(x2, y2, 0);
    glEnd();
}
void GDrawSegment2D(const double p1[], const double p2[])
{
    GDrawSegment2D(p1[0], p1[1], p2[0], p2[1]);		
}
void GDrawSegment2D(const double p1p2[])
{
    GDrawSegment2D(p1p2[0], p1p2[1], p1p2[2], p1p2[3]);		
}

void GDrawAABox2D(const double minx, const double miny,
		  const double maxx, const double maxy)
{
    glNormal3d(0, 0, 1);		
    glBegin(GL_QUADS);
    glVertex2d(minx, miny);
    glVertex2d(maxx, miny);
    glVertex2d(maxx, maxy);
    glVertex2d(minx, maxy);
    glEnd();
}
void GDrawAABox2D(const double min[],
		  const double max[])
{
    GDrawAABox2D(min[0], min[1], max[0], max[1]);		
}
void GDrawAABox2D(const double minmax[])
{
    GDrawAABox2D(minmax[0], minmax[1], minmax[2], minmax[3]);		
}


void GDrawGrid2D(const double xmin,
		 const double ymin,
		 const double xmax,
		 const double ymax,
		 const int    xNrDims,
		 const int    yNrDims)
    
{
    const double xunit  = (xmax - xmin) / xNrDims;
    const double yunit  = (ymax - ymin) / yNrDims;
    
    for(int i = 0; i <= xNrDims; ++i)
	GDrawSegment2D(xmin + i * xunit, ymin, xmin + i * xunit, ymax);
    for(int i = 0; i <= yNrDims; ++i)
	GDrawSegment2D(xmin, ymin  + i * yunit, xmax, ymin + i * yunit);
}











