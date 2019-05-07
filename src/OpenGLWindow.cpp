#include "OpenGLWindow.h"

HWND OpenGLWindow::m_hwnd;
HDC OpenGLWindow::hdc;
HGLRC OpenGLWindow::hrc;

//=============================================================================
// window event callback function
//=============================================================================
LRESULT WINAPI OpenGLWindow::WinProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_ERASEBKGND:
            // Tell Windows that we handled the message
            // by returning a non-zero number (TRUE).
            return 1;

        case WM_DESTROY:
            //tell Windows to kill this program
            PostQuitMessage(0);
            return 0;

        case WM_CLOSE:
            if (false == ::wglMakeCurrent(0, 0)) return false;

            if (hrc && (false == ::wglDeleteContext(hrc)))
                return false;
            else
                hrc = NULL;
            
            ::DestroyWindow(hWnd);
            return 0;

        case WM_CREATE:
            InitializeOpenGL(hWnd);
            return 0;

    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//=============================================================================
// Initialize OpenGL context
//=============================================================================
void OpenGLWindow::InitializeOpenGL(HWND hWnd) {
    hdc = ::GetDC(hWnd);

    if (NULL == hdc) return; // false;

    if (!SetupPixelFormat(0)) return; // false;

    if (0 == (hrc = ::wglCreateContext(hdc))) return; // false;

    if (false == ::wglMakeCurrent(hdc, hrc)) return; // false;

    return; // true;
}

bool OpenGLWindow::SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD)
{
    // default pixel format for a double-buffered,
    // OpenGL-supporting, hardware-accelerated, 
    // RGBA-mode format. Pass in a pointer to a different
    // pixel format if you want something else
    PIXELFORMATDESCRIPTOR pfd = 
        {
        sizeof(PIXELFORMATDESCRIPTOR),// size of this pfd
        1,                      // version number
        PFD_DRAW_TO_WINDOW |    // support window
        PFD_SUPPORT_OPENGL |    // support OpenGL
        PFD_DOUBLEBUFFER,       // Must Support Double Buffering
        PFD_TYPE_RGBA,          // RGBA type
        32,                     // 32-bit color depth
        0, 0, 0, 0, 0, 0,       // color bits ignored
        0,                      // no alpha buffer
        0,                      // shift bit ignored
        0,                      // no accumulation buffer
        0, 0, 0, 0,             // accum bits ignored
        32,                     // 32-bit z-buffer
        0,                      // no stencil buffer
        0,                      // no auxiliary buffer
        PFD_MAIN_PLANE,         // main layer
        0,                      // reserved
        0, 0, 0                 // layer masks ignored
        };

    int pixelformat;
    PIXELFORMATDESCRIPTOR* pPFDtoUse;

    // let the user override the default pixel format
    pPFDtoUse = (0 == pPFD)? &pfd : pPFD; 
 
    if(0 == (pixelformat = ::ChoosePixelFormat(hdc, pPFDtoUse)))
    {
        return false;
    }

    if (false == ::SetPixelFormat(hdc, pixelformat, pPFDtoUse ))
    {
        return false;
    }

    return true;
}


//=============================================================================
// Create the window
// Returns: false on error
//=============================================================================
bool OpenGLWindow::Create(HINSTANCE hInstance, int nCmdShow) 
{
    // Constants
    static const char CLASS_NAME[]  = "WinMain";
    // const wchar_t CLASS_NAME[]  = L"WinMain";
    static const char APP_TITLE[]   = "Hello World";   // title bar text
    // const wchar_t APP_TITLE[]   = L"Hello World";   // title bar text
    static const int  WINDOW_WIDTH  = 400;             // width of window
    static const int  WINDOW_HEIGHT = 400;             // height of window

    WNDCLASSEXA wcx; 
    HWND hwnd;
 
    // Fill in the window class structure with parameters 
    // that describe the main window. 
    wcx.cbSize = sizeof(wcx);           // size of structure 
    wcx.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;    // redraw if size changes 
    wcx.lpfnWndProc = WinProc;          // points to window procedure 
    wcx.cbClsExtra = 0;                 // no extra class memory 
    wcx.cbWndExtra = 0;                 // no extra window memory 
    wcx.hInstance = hInstance;          // handle to instance 
    wcx.hIcon = NULL; 
    wcx.hCursor = LoadCursor(NULL,IDC_ARROW);   // predefined arrow 
    wcx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);    // black background brush 
    wcx.lpszMenuName =  NULL;           // name of menu resource 
    wcx.lpszClassName = CLASS_NAME;     // name of window class 
    wcx.hIconSm = NULL;                 // small class icon 
 
    // Register the window class. 
    // RegisterClassEx returns 0 on error.
    if (RegisterClassExA(&wcx) == 0)    // if error
        return false;

    // Create window
    hwnd = CreateWindowA(
        CLASS_NAME,             // name of the window class
        APP_TITLE,              // title bar text
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,    // window style
        CW_USEDEFAULT,          // default horizontal position of window
        CW_USEDEFAULT,          // default vertical position of window
        WINDOW_WIDTH,           // width of window
        WINDOW_HEIGHT,          // height of the window
        (HWND) NULL,            // no parent window
        (HMENU) NULL,           // no menu
        hInstance,              // handle to application instance
        (LPVOID) NULL);         // no window parameters

    // if there was an error creating the window
    if (!hwnd)
        return false;

    m_hwnd = hwnd;
    // Show the window
    ShowWindow(hwnd, nCmdShow);

    // Send a WM_PAINT message to the window procedure
    UpdateWindow(hwnd);
    return true;
}
