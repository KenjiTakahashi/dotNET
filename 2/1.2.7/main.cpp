#include <windows.h>
#include <GL/gl.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.5f, 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(-0.5f, -0.5f);
    glEnd();
    glFlush();
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
    static PAINTSTRUCT ps;
    switch(uMsg) {
    case WM_PAINT:
		display();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
    case WM_SIZE:
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		PostMessage(hWnd, WM_PAINT, 0, 0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;    
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
	return 0;
} 

HWND CreateOpenGLWindow(LPCTSTR title, int x, int y, int width, int height, 
		   BYTE type, DWORD flags)
{
    int pf;
    HDC hDC;
    HWND hWnd;
    WNDCLASS wc;
    PIXELFORMATDESCRIPTOR pfd;
    static HINSTANCE hInstance = 0;
    if(!hInstance) {
		hInstance = GetModuleHandle(NULL);
		wc.style         = CS_OWNDC;
		wc.lpfnWndProc   = WindowProc;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = hInstance;
		wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
		wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName  = NULL;
		wc.lpszClassName = TEXT("OpenGL");
		if(!RegisterClass(&wc)) {
		    MessageBox(NULL, TEXT("RegisterClass() failed:  ")
			       TEXT("Cannot register window class."), TEXT("Error"), MB_OK);
		    return NULL;
		}
    }
    hWnd = CreateWindowEx(0, TEXT("OpenGL"), title, WS_OVERLAPPEDWINDOW |
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
			x, y, width, height, NULL, NULL, hInstance, NULL);
    if(hWnd == NULL) {
		MessageBox(NULL, TEXT("CreateWindow() failed:  Cannot create a window."),
			   TEXT("Error"), MB_OK);
		return NULL;
    }
    hDC = GetDC(hWnd);
    memset(&pfd, 0, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | flags;
    pfd.iPixelType = type;
    pfd.cColorBits = 32;
    pf = ChoosePixelFormat(hDC, &pfd);
    if(pf == 0) {
		MessageBox(NULL, TEXT("ChoosePixelFormat() failed: \
							  Cannot find a suitable pixel format."),
							  TEXT("Error"), MB_OK); 
		return 0;
    } 
    if(SetPixelFormat(hDC, pf, &pfd) == FALSE) {
		MessageBox(NULL, TEXT("SetPixelFormat() failed: \
							  Cannot set format specified."),
			TEXT("Error"), MB_OK);
		return 0;
    } 
    DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    ReleaseDC(hWnd, hDC);
    return hWnd;
}    

int WINAPI WinMain(HINSTANCE hCurrentInst, HINSTANCE hPreviousInst,
	LPSTR lpszCmdLine, int nCmdShow)
{
    HDC hDC;
    HGLRC hRC;
    HWND hWnd;
    MSG msg;

    hWnd = CreateOpenGLWindow(TEXT("minimal"),
		0, 0,
		256, 256,
		PFD_TYPE_RGBA, 0);
    if(hWnd == NULL) {
		return 1;
	}

    hDC = GetDC(hWnd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    ShowWindow(hWnd, nCmdShow);

	while(TRUE) {
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message != WM_QUIT) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {
				break;
			}
		} else {
			Sleep(50);
			display();
		}
	}

    wglMakeCurrent(NULL, NULL);
    ReleaseDC(hWnd, hDC);
    wglDeleteContext(hRC);
    DestroyWindow(hWnd);

    return msg.wParam;
}