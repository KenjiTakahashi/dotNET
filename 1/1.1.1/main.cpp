/*
 *
 * Tworzenie okna aplikacji
 *
 */
#include <windows.h>

/* Deklaracja wyprzedzaj�ca: funkcja obs�ugi okna */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
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
    wincl.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

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

/* T� funkcj� wo�a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam) {
	int messageBox;
    switch(message) {
	case WM_CLOSE:
		messageBox = MessageBox(hwnd,
			L"Czy jestes pewien, ze chcesz zakonczyc program?",
			L"Question", MB_OKCANCEL);
		if(messageBox == IDOK) {
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
