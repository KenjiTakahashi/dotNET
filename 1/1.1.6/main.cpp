/*
 *
 * Tworzenie okna aplikacji
 *
 */
#include <windows.h>
#include <CommCtrl.h>
#include <strsafe.h>

/* Deklaracja wyprzedzaj¹ca: funkcja obs³ugi okna */
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

	/* common controls initialization */
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);

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

    /* Twórz okno */
    hwnd = CreateWindowEx(
           0, szClassName,
		   szClassName,
           WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT, CW_USEDEFAULT,       
           512, 512,                 
           HWND_DESKTOP, NULL,                
           hInstance, NULL );

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

const int ID_ADD = 666;
const int ID_REMOVE = 333;
int index = 0;
HWND listView;
HWND progressBarClassic;
HWND progressBarSmooth;
HWND statusBar;

/* Tê funkcjê wo³a DispatchMessage( ) */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam) {
	TCHAR itemText[10];
	TCHAR statusText[18];
	TCHAR rStatusText[2000];
	TCHAR char_[3];
	int position;
    switch(message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		if(HIWORD(wParam) == BN_CLICKED) {
			switch(LOWORD(wParam)) {
			case ID_ADD:
				if(index < 100) {
					StringCchCopy(itemText, 10, TEXT("ELEM "));
					_itow_s(index, char_, 10);
					StringCchCat(itemText, 10, char_);
					LVITEM item;
					item.mask = LVIF_TEXT;
					item.iSubItem = 0;
					item.pszText = itemText;
					item.iItem = index;
					SendMessage(listView, LVM_INSERTITEM, 0, (LPARAM)&item);
					StringCchCopy(statusText, 18, TEXT("Dodano "));
					StringCchCat(statusText, 18, itemText);
					SendMessage(progressBarClassic, PBM_STEPIT, 0, 0);
					SendMessage(progressBarSmooth, PBM_STEPIT, 0, 0);
					SendMessage(statusBar, SB_SETTEXT, 0, (LPARAM)statusText);
					index++;
				} else {
					SendMessage(statusBar, SB_SETTEXT, 0, (LPARAM)TEXT("Nie ma miejsca!"));
				}
				break;
			case ID_REMOVE:
				position = SendMessage(listView, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
				StringCchCopy(rStatusText, 2000, TEXT("Usuniêto "));
				while(position != -1) {
					TCHAR tmp[10];
					LVITEM item;
					item.mask = LVIF_TEXT;
					item.iSubItem = 0;
					item.iItem = position;
					item.pszText = tmp;
					item.cchTextMax = 10;
					SendMessage(listView, LVM_GETITEM, 0, (LPARAM)&item);
					SendMessage(listView, LVM_DELETEITEM, position, 0);
					StringCchCat(rStatusText, 2000, item.pszText);
					StringCchCat(rStatusText, 2000, TEXT(", "));
					SendMessage(progressBarClassic, PBM_DELTAPOS, -1, 0);
					SendMessage(progressBarSmooth, PBM_DELTAPOS, -1, 0);
					index--;
					position = SendMessage(listView, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
				}
				SendMessage(statusBar, SB_SETTEXT, 0, (LPARAM)rStatusText);
				break;
			}
		}
		break;
	case WM_SIZE:
		MoveWindow(statusBar, 0, 0, 0, 0, 1);
		break;
	case WM_CREATE:
		listView = CreateWindowEx(0,
			WC_LISTVIEW,
			TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_LIST,
			0, 0,
			500, 200,
			hwnd,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		CreateWindowEx(0,
			TEXT("BUTTON"),
			TEXT("Dodaj"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0, 210,
			100, 20,
			hwnd,
			(HMENU)ID_ADD,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		CreateWindowEx(0,
			TEXT("BUTTON"),
			TEXT("Usuñ"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			110, 210,
			100, 20,
			hwnd,
			(HMENU)ID_REMOVE,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		progressBarClassic = CreateWindowEx(0,
			PROGRESS_CLASS,
			TEXT(""),
			WS_CHILD | WS_VISIBLE,
			0, 240,
			500, 20,
			hwnd,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		SendMessage(progressBarClassic, PBM_SETSTEP, 1, 0);
		progressBarSmooth = CreateWindowEx(0,
			PROGRESS_CLASS,
			TEXT(""),
			WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
			0, 270,
			500, 20,
			hwnd,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		SendMessage(progressBarSmooth, PBM_SETSTEP, 1, 0);
		statusBar = CreateWindowEx(0,
			STATUSCLASSNAME,
			TEXT(""),
			WS_CHILD | WS_VISIBLE,
			0, 0,
			0, 0,
			hwnd,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
