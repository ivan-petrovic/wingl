#include "OpenGLWindow.h"
#include "GL/GL.h"


//=============================================================================
// Starting point for a Windows application
// Parameters are:
//   hInstance - handle to the current instance of the application
//   hPrevInstance - always NULL, obsolete parameter, maintained for backwards compatibilty
//   lpCmdLine - pointer to null-terminated string of command line arguments
//   nCmdShow - specifies how the window is to be shown
//=============================================================================
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow
) {
    // Create the window
    if (!OpenGLWindow::Create(hInstance, nCmdShow))
        return false;

    // main message loop
    MSG	 msg;
    bool done = false;
    while (!done)
    {
        // PeekMessage is a non-blocking method for checking for Windows messages.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            //look for quit message
            if (msg.message == WM_QUIT)
                done = true;

            //decode and pass messages on to WinProc
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Clear the color/depth/stencil buffer
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //
        //  Draw your geometry using OpenGL commands here 
        //

        // Swap buffers to make geometry visible on screen
        ::SwapBuffers(::GetDC(OpenGLWindow::m_hwnd));
    }
    return msg.wParam;
}
