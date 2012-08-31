/*
 *
 * Tworzenie okna aplikacji
 *
 */
#include <windows.h>

/* Deklaracja wyprzedzaj�ca: funkcja obs�ugi okna */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK GroupBoxProcedure(HWND, UINT, WPARAM, LPARAM);
/* Nazwa klasy okna */
LPCWSTR szClassName = L"PRZYKLAD";

int WINAPI WinMain(HINSTANCE hInstance, 
                   HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, 
                   int nShowCmd) {
    HWND hwnd;               /* Uchwyt okna */
    MSG messages;            /* Komunikaty okna */
    WNDCLASSEX wincl;        /* Struktura klasy okna */

    /* Klasa okna */
    wincl.hInstance     = hInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc   = WindowProcedure;    // wska�nik na funkcj� 
                                              // obs�ugi okna  
    wincl.style         = CS_DBLCLKS;                 
    wincl.cbSize        = sizeof(WNDCLASSEX);

    /* Domy�lna ikona i wska�nik myszy */
    wincl.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL; 
    wincl.cbClsExtra = 0;   
    wincl.cbWndExtra = 0;   
    /* Jasnoszare t�o */
	wincl.hbrBackground = (HBRUSH)COLOR_WINDOW;

    /* Rejestruj klas� okna */
    if(!RegisterClassEx(&wincl)) return 0;

    /* Tw�rz okno */
    hwnd = CreateWindowEx(
           0, szClassName,
		   szClassName,
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT, CW_USEDEFAULT,       
           512, 512,                 
           HWND_DESKTOP, NULL,                
           hInstance, NULL );

    ShowWindow(hwnd, nShowCmd);
    /* P�tla obs�ugi komunikat�w */
    while(GetMessage(&messages, NULL, 0, 0)) {
           /* T�umacz kody rozszerzone */
           TranslateMessage(&messages);
           /* Obs�u� komunikat */
           DispatchMessage(&messages);
    }

    /* Zwr�� parametr podany w PostQuitMessage( ) */
    return messages.wParam;
}

const int ID_CHILD = 666;
WNDPROC oldProc;

/* T� funkcj� wo�a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam) {
	HWND groupBox;
    switch(message) {
	case WM_COMMAND:
		if(HIWORD(wParam) == BN_CLICKED) {
			switch(LOWORD(wParam)) {
			case ID_CHILD:
				MessageBox(hwnd, TEXT("It is working from main!"),
					TEXT("Announce"), 0);
				break;
			}
		}
		break;
	case WM_CREATE:
		groupBox = CreateWindowEx(0,
			TEXT("BUTTON"),
			TEXT("Parent"),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			0, 0,
			497, 100,
			hwnd,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		oldProc = (WNDPROC)SetWindowLongPtr(groupBox,
			GWLP_WNDPROC,
			(LONG_PTR)GroupBoxProcedure);
		CreateWindowEx(0,
			TEXT("BUTTON"),
			TEXT("Child"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 30,
			100, 40,
			groupBox,
			(HMENU)ID_CHILD,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK GroupBoxProcedure(HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam) {
	HWND parent = GetParent(hwnd);
	switch(message) {
	case WM_COMMAND:
		SendMessage(parent, message, wParam, lParam);
		break;
	}
	return CallWindowProc(oldProc, hwnd, message, wParam, lParam);
}