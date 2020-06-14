#include <cmath>
#include "Utils/GManager.hpp"
#include "Utils/GDraw.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>

GManager *m_gManager = NULL;

void GManager::CallbackEventOnActiveMouseMove(int x, int y)
{
    if(m_gManager)
    {		
	if(m_gManager->HandleEventOnActiveMouseMove(x, y))
	    glutPostRedisplay();	    
	m_gManager->m_mousePrevX = x;
	m_gManager->m_mousePrevY = y;
    }
}

void GManager::CallbackEventOnPassiveMouseMove(int x, int y)
{
    if(m_gManager)
    {	
	if(m_gManager->HandleEventOnPassiveMouseMove(x, y))
	    glutPostRedisplay();	    
	m_gManager->m_mousePrevX = x;
	m_gManager->m_mousePrevY = y;
    }
}

void GManager::CallbackEventOnMouse(int button, int state, int x, int y)
{
    if(m_gManager)
    {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
	   m_gManager->HandleEventOnMouseLeftBtnDown(x, y))
	    glutPostRedisplay();
	
	m_gManager->m_mousePrevX = x;
	m_gManager->m_mousePrevY = y;
    }
}

void GManager::CallbackEventOnTimer(int id)
{
    if(m_gManager)
    {
	m_gManager->HandleEventOnTimer();
	glutTimerFunc(m_gManager->m_timer, CallbackEventOnTimer, id);
	glutPostRedisplay();	    
    }
}

void GManager::CallbackEventOnIdle(void)
{
    if(m_gManager && m_gManager->HandleEventOnIdle())
	glutPostRedisplay();	    
    
}

void GManager::CallbackEventOnSpecialKeyPress(int key, int x, int y)
{
    if(m_gManager && m_gManager->HandleEventOnSpecialKeyPress(key))
	glutPostRedisplay();
}

void GManager::CallbackEventOnNormalKeyPress(unsigned char key, int x, int y)
{
    if(m_gManager && m_gManager->HandleEventOnNormalKeyPress(key))
	glutPostRedisplay();
}


void GManager::CallbackEventOnSpecialKeyUp(int key, int x, int y)
{
    if(m_gManager && m_gManager->HandleEventOnSpecialKeyUp(key))
	glutPostRedisplay();
}

void GManager::CallbackEventOnNormalKeyUp(unsigned char key, int x, int y)
{
    if(m_gManager && m_gManager->HandleEventOnNormalKeyUp(key))
	glutPostRedisplay();
}


void  GManager::CallbackEventOnDisplay(void)
{
    if(m_gManager)
    {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
	
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(GDrawGetParam(GDRAW_MINX), 
		GDrawGetParam(GDRAW_MAXX),
		GDrawGetParam(GDRAW_MINY), 
		GDrawGetParam(GDRAW_MAXY),
		GDrawGetParam(GDRAW_ORTHO_NEAR_PLANE),
		GDrawGetParam(GDRAW_ORTHO_FAR_PLANE));
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	m_gManager->HandleEventOnDisplay();
	
	glutSwapBuffers();	    
    }
}

GManager::GManager(void) 
{
    m_idWindow      = -1;
    m_timer         = 2;
    m_mousePrevX    = 0;
    m_mousePrevY    = 0;	    
}

GManager::~GManager(void)
{
    if(m_idWindow >= 0)
	glutDestroyWindow(m_idWindow);	
}


void GManager::MainLoop(const char * const title, const int width, const int height)
{	
    m_gManager = this;
    
    static int    argc = 1;	
    static char  *args = (char*)"args";
    
    glutInit(&argc, &args);    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);    
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0); 
    m_idWindow = glutCreateWindow(title);	   	
    
    glutDisplayFunc(CallbackEventOnDisplay);
    glutMouseFunc(CallbackEventOnMouse);
    glutMotionFunc(CallbackEventOnActiveMouseMove);
    glutPassiveMotionFunc(CallbackEventOnPassiveMouseMove);
    glutIdleFunc(CallbackEventOnIdle);
    glutTimerFunc(0, CallbackEventOnTimer, 0); 
    glutKeyboardFunc(CallbackEventOnNormalKeyPress);
    glutSpecialFunc(CallbackEventOnSpecialKeyPress);
    glutKeyboardUpFunc(CallbackEventOnNormalKeyUp);
    glutSpecialUpFunc(CallbackEventOnSpecialKeyUp);
    
    glutMainLoop();	
}

bool GManager::HandleEventOnNormalKeyPress(const int key)
{
    if(key == 27) //escape key
    {
	exit(0);
	return true;
    }
    return false;
}

bool GManager::HandleEventOnSpecialKeyPress(const int key)
{	    
    return false;
}


void GManager::MousePosFromScreenToWorld(const int x, const int y, 
					 double * const wx,
					 double * const wy,
					 double * const wz)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ=0;
    double px = 0, py = 0, pz = 0;
    
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
    gluUnProject(winX, winY, winZ, modelview, projection, viewport, &px, &py, &pz);
    
    if(wx)
	*wx = px;
    if(wy)
	*wy = py;
    if(wz)
	*wz = pz;    
}



