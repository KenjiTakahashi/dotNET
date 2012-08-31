/*
 *
 * Tworzenie okna aplikacji
 *
 */
#include <windows.h>
#include <strsafe.h>

/* Deklaracja wyprzedzaj¹ca: funkcja obs³ugi okna */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void CreatePopup(HWND);
/* Nazwa klasy okna */
LPCTSTR szClassName = TEXT("1.1.4");


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
	wincl.hbrBackground = (HBRUSH)COLOR_WINDOW;

    /* Rejestruj klasê okna */
    if(!RegisterClassEx(&wincl)) return 0;

    /* Twórz okno */    
	hwnd = CreateWindowEx(
           0,                   
           szClassName,         
		   szClassName,
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT, CW_USEDEFAULT,       
		   500, 240,
           HWND_DESKTOP,        
           NULL,                
           hInstance,       
           NULL                 
           );

    ShowWindow(hwnd, nShowCmd);
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

const int ID_ACCEPT = 100;
const int ID_CANCEL = 101;
static HWND children[2];
static HWND editBoxes[2];
static HWND combobox;
static HWND checkBoxes[2];
static HWND buttons[2];

void CreatePopup(HWND hwnd) {
	int index, length;
	TCHAR studia[2000];
	length = SendMessage(editBoxes[0], EM_LINELENGTH, 0, 0);
	TCHAR *tmp = new TCHAR[length + 2];
	tmp[0] = length;
	SendMessage(editBoxes[0], EM_GETLINE, 0, (LPARAM)tmp);
	tmp[length] = 0;
	StringCchCopy(studia, 2000, tmp);
	if(length > 0) {
		StringCchCat(studia, 2000, TEXT("\n"));
	}
	length = SendMessage(editBoxes[1], EM_LINELENGTH, 0, 0);
	delete [] tmp;
	tmp = new TCHAR[length + 2];
	tmp[0] = length;
	SendMessage(editBoxes[1], EM_GETLINE, 0, (LPARAM)tmp);
	tmp[length] = 0;
	StringCchCat(studia, 2000, tmp);
	if(length > 0) {
		StringCchCat(studia, 2000, TEXT("\n"));
	}
	index = SendMessage(combobox, CB_GETCURSEL, 0, 0);
	length = SendMessage(combobox, CB_GETLBTEXTLEN, index, 0);
	delete [] tmp;
	tmp = new TCHAR[length + 1];
	SendMessage(combobox, CB_GETLBTEXT, index, (LPARAM)tmp);
	tmp[length] = 0;
	StringCchCat(studia, 2000, TEXT("Studia "));
	StringCchCat(studia, 2000, tmp);
	StringCchCat(studia, 2000, TEXT("\n"));
	delete [] tmp;
	for(int i = 0; i < 2; ++i) {
		if(SendMessage(checkBoxes[i], BM_GETCHECK, 0, 0)) {
			tmp = new TCHAR[30];
			SendMessage(checkBoxes[i], WM_GETTEXT, 30, (LPARAM)tmp);
			StringCchCat(studia, 2000, tmp);
			StringCchCat(studia, 2000, TEXT("\n"));
			delete [] tmp;
		}
	}
	MessageBox(hwnd, studia, TEXT("Uczelnia"), 0);
}

/* Tê funkcjê wo³a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	int xSize, ySize;
	LPCTSTR names[2] = {L"Nazwa:", L"Adres:"};
	LPCTSTR btnLabels[2] = {L"Akceptuj", L"Anuluj"};
    switch(message) {
	case WM_COMMAND:
		if(HIWORD(wParam) == BN_CLICKED) {
			switch(LOWORD(wParam)) {
			case ID_ACCEPT:
				CreatePopup(hwnd);
				break;
			case ID_CANCEL:
				PostQuitMessage(0);
				break;
			}
		}
		break;
	case WM_SIZE:
		xSize = LOWORD(lParam);
		ySize = (HIWORD(lParam) - 20) / 2;
		MoveWindow(children[0],
			0, 0,
			xSize, ySize, 1);
		MoveWindow(children[1],
			0, ySize,
			xSize, ySize, 1);
		for(int i = 24, j = 0; i < 53; i += i + 2, ++j) {
			MoveWindow(editBoxes[j],
				70, i,
				xSize - 80, 20, 1);
		}
		MoveWindow(combobox,
			90, 24,
			xSize - 100, 1000, 1);
		MoveWindow(buttons[0],
			0, ySize * 2,
			60, 20, 1);
		MoveWindow(buttons[1],
			xSize - 60, ySize * 2,
			60, 20, 1);
		break;
	case WM_CREATE:
		children[0] = CreateWindowEx(0,
			L"BUTTON", L"Uczelnia",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			0, 0,
			0, 0,
			hwnd,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		for(int i = 25, j = 0; i < 53; i += i + 2, ++j) {
			CreateWindowEx(0,
				L"STATIC", names[j],
				WS_CHILD | WS_VISIBLE | WS_TABSTOP,
				10, i,
				50, 20,
				children[0],
				NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
			editBoxes[j] = CreateWindowEx(0,
				L"EDIT", L"",
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				70, i - 1,
				0, 0,
				children[0],
				NULL,
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
		}
		children[1] = CreateWindowEx(0,
			L"BUTTON", L"Rodzaj studiow",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			0, 0,
			0, 0,
			hwnd,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		CreateWindowEx(0,
			L"STATIC", L"Cykl nauki:",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			10, 25,
			80, 20,
			children[1],
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		combobox = CreateWindowEx(0,
			L"COMBOBOX", L"",
			WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
			90, 24,
			0, 0,
			children[1],
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		SendMessage(combobox, CB_ADDSTRING, 0, (LPARAM)L"3-letnie");
		SendMessage(combobox, CB_ADDSTRING, 0, (LPARAM)L"5-letnie");
		SendMessage(combobox, CB_SETCURSEL, 0, 0);
		checkBoxes[0] = CreateWindowEx(0,
			L"BUTTON", L"dzienne",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			90, 52,
			80, 20,
			children[1],
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		checkBoxes[1] = CreateWindowEx(0,
			L"BUTTON", L"uzupe³niaj¹ce",
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			170, 52,
			160, 20,
			children[1],
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		for(int i = 0; i < 2; ++i) {
			buttons[i] = CreateWindowEx(0,
				L"BUTTON", btnLabels[i],
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				0, 0,
				0, 0,
				hwnd,
				(HMENU)(i + 100),
				((LPCREATESTRUCT)lParam)->hInstance,
				NULL);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
