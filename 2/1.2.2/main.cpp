/*
 *
 * Tworzenie okna aplikacji
 *
 */
#include <windows.h>

/* Deklaracja wyprzedzaj¹ca: funkcja obs³ugi okna */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* Nazwa klasy okna */
LPCWSTR szClassName = TEXT("1.2.2");
HWND mainWindow;

int WINAPI WinMain(HINSTANCE hInstance, 
                   HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, 
                   int nShowCmd) {
    //HWND hwnd;               /* Uchwyt okna */
    MSG messages;            /* Komunikaty okna */
    WNDCLASSEX wincl;        /* Struktura klasy okna */

    /* Klasa okna */
    wincl.hInstance     = hInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc   = WindowProcedure;    // wskaŸnik na funkcjê 
                                              // obs³ugi okna  
    wincl.style         = CS_DBLCLKS;                 
    wincl.cbSize        = sizeof(WNDCLASSEX);

    /* Domyœlna ikona i wskaŸnik myszy */
    wincl.hIcon   = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL; 
    wincl.cbClsExtra = 0;   
    wincl.cbWndExtra = 0;   
    /* Jasnoszare t³o */
    wincl.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

    /* Rejestruj klasê okna */
    if(!RegisterClassEx(&wincl)) return 0;

	/* retrieve window size */
	DWORD xSize, ySize;
	HKEY result;
	LONG xError, yError;
	LONG error = RegOpenKeyEx(HKEY_CURRENT_USER,
		TEXT("Software\\Programowanie pod Windows\\1.2.2"),
		0, KEY_READ, &result);
	if(error == ERROR_SUCCESS) {
		DWORD size = sizeof(DWORD);
		xError = RegQueryValueEx(result,
			TEXT("xSize"), NULL, NULL, (LPBYTE)&xSize, &size);
		yError = RegQueryValueEx(result,
			TEXT("ySize"), NULL, NULL, (LPBYTE)&ySize, &size);
	}
	if(error != ERROR_SUCCESS
		|| xError != ERROR_SUCCESS
		|| yError != ERROR_SUCCESS) {
		xSize = 512;
		ySize = 512;
	}

    /* Twórz okno */
    mainWindow = CreateWindowEx(
           0, szClassName,
		   szClassName,
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT, CW_USEDEFAULT,       
		   xSize, ySize,
           HWND_DESKTOP, NULL,                
           hInstance, NULL );

    ShowWindow(mainWindow, nShowCmd);
    /* Pêtla obs³ugi komunikatów */
    while(GetMessage(&messages, NULL, 0, 0)) {
           /* T³umacz kody rozszerzone */
           TranslateMessage(&messages);
           /* Obs³u¿ komunikat */
           DispatchMessage(&messages);
    }

    /* Zwróæ parametr podany w PostQuitMessage( ) */
    return messages.wParam;
}

/* Tê funkcjê wo³a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam) {
	LONG error;
	HKEY result;
	DWORD disposition;
	int res;
	RECT rect;
    switch(message) {
	case WM_DESTROY:
		error = RegCreateKeyEx(HKEY_CURRENT_USER,
			TEXT("Software\\Programowanie pod Windows\\1.2.2"),
			0, NULL, 0, KEY_ALL_ACCESS, NULL, &result, &disposition);
		if(error == ERROR_SUCCESS) {
			res = GetClientRect(hwnd, &rect);
			if(res == TRUE) {
				error = RegSetValueEx(result,
					TEXT("xSize"), 0, REG_DWORD,
					(LPBYTE)&rect.right, sizeof(DWORD));
				error = RegSetValueEx(result,
					TEXT("ySize"), 0, REG_DWORD,
					(LPBYTE)&rect.bottom, sizeof(DWORD));
			}
		}
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
