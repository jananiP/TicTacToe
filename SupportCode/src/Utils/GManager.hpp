#ifndef  UTILS__GMANAGER_HPP_
#define  UTILS__GMANAGER_HPP_

#include "Utils/GDraw.hpp"

class GManager
{
public:
    GManager(void);
    
    virtual ~GManager(void);
    
    virtual void MainLoop(const char * const title, 
			  const int width = 1000, 
			  const int height=  600);
    
    static void MousePosFromScreenToWorld(const int x, const int y, 
					  double * const wx,
					  double * const wy,
					  double * const wz);
    
    static void ExportFrameAsImage(const char fname[]);
    
    
    virtual void HandleEventOnTimer(void)
    {
    }
    
    virtual void HandleEventOnDisplay(void)
    {
    }
    
    virtual bool HandleEventOnMouseLeftBtnDown(const int x, const int y)
    {
	return false;
    }
    
    virtual bool HandleEventOnActiveMouseMove(const int x, const int y)
    {
	return false;
    }
    
    virtual bool HandleEventOnPassiveMouseMove(const int x, const int y)
    {
	return false;
    }
    
    virtual bool HandleEventOnNormalKeyPress(const int key);
    
    virtual bool HandleEventOnSpecialKeyPress(const int key);
    
    virtual bool HandleEventOnNormalKeyUp(const int key)
    {
	return false;
    }
    
    virtual bool HandleEventOnSpecialKeyUp(const int key)
    {
	return false;
    }
    
    virtual bool HandleEventOnIdle(void)
    {
	return false;
    }
    
    
protected:	
    static void CallbackEventOnActiveMouseMove(int x, int y);
    static void CallbackEventOnPassiveMouseMove(int x, int y);
    static void CallbackEventOnMouse(int button, int state, int x, int y);
    static void CallbackEventOnTimer(int id);
    static void CallbackEventOnMenu(int item);
    static void CallbackEventOnSpecialKeyPress(int key, int x, int y);
    static void CallbackEventOnNormalKeyPress(unsigned char key, int x, int y);
    static void CallbackEventOnSpecialKeyUp(int key, int x, int y);
    static void CallbackEventOnNormalKeyUp(unsigned char key, int x, int y);
    
    static void CallbackEventOnDisplay(void);
    static void CallbackEventOnIdle(void);
    
    
    int m_idWindow;
    int m_timer;
    int m_mousePrevX;
    int m_mousePrevY;
    
};

#endif
