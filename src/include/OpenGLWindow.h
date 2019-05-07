#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

class OpenGLWindow {
public:
    static bool Create(HINSTANCE, int);
    static HWND m_hwnd;
    static HDC hdc;
    static HGLRC hrc;

protected:
    static LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);
    static void InitializeOpenGL(HWND);
    static bool SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD);
};

#endif // OPENGL_WINDOW_H
