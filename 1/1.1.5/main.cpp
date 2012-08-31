/*
 *
 * Okna dialogowe
 *
 */
#include <windows.h>
#include <strsafe.h>

/* Deklaracja wyprzedzaj¹ca: funkcja obs³ugi okna */
INT_PTR CALLBACK DialogBoxWindowProcedure(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK PopupBoxWindowProcedure(HWND, UINT, WPARAM, LPARAM);
void FillPopupText(HWND hwnd);
/* Getters */
TCHAR *GetEditBoxText(HWND item);
TCHAR *GetComboBoxText(HWND item);
TCHAR *GetCheckBoxText(HWND item);
/* Nazwa klasy okna */
LPCTSTR szClassName = TEXT("1.1.5");

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpszArgument, int nFunsterStil)
{
	DialogBox(hThisInstance,
		MAKEINTRESOURCE(501),
		HWND_DESKTOP, DialogBoxWindowProcedure);
	return 0;
}

INT_PTR CALLBACK DialogBoxWindowProcedure(HWND hwnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam)
{
	HWND item;
	switch(message) {
	case WM_INITDIALOG:
		/* ComboBox items */
		item = GetDlgItem(hwnd, 506);
		SendMessage(item, CB_ADDSTRING, 0, (LPARAM)L"3-letnie");
		SendMessage(item, CB_ADDSTRING, 0, (LPARAM)L"5-letnie");
		SendMessage(item, CB_SETCURSEL, 0, 0);
		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDOK:
			DialogBox(0,
				MAKEINTRESOURCE(502), hwnd, PopupBoxWindowProcedure);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			return TRUE;
		}
	default:
		DefWindowProc(hwnd, message, wParam, lParam);
	}
    return 0;
}

INT_PTR CALLBACK PopupBoxWindowProcedure(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	switch(message) {
	case WM_INITDIALOG:
		FillPopupText(hwnd);
		return TRUE;
	case WM_DESTROY:
		EndDialog(hwnd, 0);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDOK:
			EndDialog(hwnd, 0);
			return TRUE;
		}
	default:
		DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void FillPopupText(HWND hwnd) {
	TCHAR studia[1000];
	HWND parent = GetParent(hwnd);
	StringCchCopy(studia, 1000, GetEditBoxText(GetDlgItem(parent, 504)));
	StringCchCat(studia, 1000, GetEditBoxText(GetDlgItem(parent, 505)));
	StringCchCat(studia, 1000, GetComboBoxText(GetDlgItem(parent, 506)));
	StringCchCat(studia, 1000, GetCheckBoxText(GetDlgItem(parent, 507)));
	StringCchCat(studia, 1000, GetCheckBoxText(GetDlgItem(parent, 508)));
	SendMessage(GetDlgItem(hwnd, 503), WM_SETTEXT, 0, (LPARAM)studia);
}

TCHAR *GetEditBoxText(HWND item) {
	int length = SendMessage(item, EM_LINELENGTH, 0, 0);
	if(length > 0) {
		TCHAR *result = new TCHAR[length + 2];
		result[0] = length;
		SendMessage(item, EM_GETLINE, 0, (LPARAM)result);
		result[length] = TEXT('\n');
		result[length + 1] = 0;
		return result;
	} else {
		return TEXT("");
	}
}

TCHAR *GetComboBoxText(HWND item) {
	int index = SendMessage(item, CB_GETCURSEL, 0, 0);
	int length = SendMessage(item, CB_GETLBTEXTLEN, index, 0);
	if(length > 0) {
		TCHAR *result = new TCHAR[length + 2];
		SendMessage(item, CB_GETLBTEXT, index, (LPARAM)result);
		result[length] = TEXT('\n');
		result[length + 1] = 0;
		return result;
	} else {
		return TEXT("");
	}
}

TCHAR *GetCheckBoxText(HWND item) {
	if(SendMessage(item, BM_GETCHECK, 0, 0)) {
		TCHAR *result = new TCHAR[30];
		int length = SendMessage(item, WM_GETTEXT, 30, (LPARAM)result);
		result[length] = TEXT('\n');
		result[length + 1] = 0;
		return result;
	} else {
		return TEXT("");
	}
}