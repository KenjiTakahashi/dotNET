#include <windows.h>
#include <strsafe.h>
#include <UrlMon.h>
#include <ShlObj.h>
#include "StatusCallback.h"

INT_PTR CALLBACK DialogBoxWindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* threading things */
DWORD WINAPI Worker(LPVOID lParam);
typedef struct DlData {
	TCHAR *path;
	TCHAR *url;
	HWND hwnd;
} DLDATA, *PDLDATA;

LPCTSTR szClassName = TEXT("1.2.6");

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpszArgument, int nFunsterStil)
{
	DialogBox(hThisInstance,
		MAKEINTRESOURCE(501),
		HWND_DESKTOP, DialogBoxWindowProcedure);
	return 0;
}

const int ID_PATH = 644;
const int ID_URL = 666;
const int ID_PROGRESS = 777;

INT_PTR CALLBACK DialogBoxWindowProcedure(HWND hwnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam)
{
	PTSTR path;
	LPTSTR newpath;
	HWND pathItem, urlItem;
	PDLDATA data = new DLDATA;
	data->path = NULL;
	data->url = NULL;
	data->hwnd = hwnd;
	int length;
	switch(message) {
	case WM_INITDIALOG:
		path = (PTSTR)CoTaskMemAlloc(1);
		SHGetKnownFolderPath(FOLDERID_Desktop,
			0, NULL, &path);
		length = wcslen(path) + 10;
		newpath = new TCHAR[length];
		StringCchCopy(newpath, length, path);
		StringCchCat(newpath, length, TEXT("\\file.pdf"));
		pathItem = GetDlgItem(hwnd, ID_PATH);
		SendMessage(pathItem, WM_SETTEXT, 0, (LPARAM)newpath);
		CoTaskMemFree(path);
		delete [] newpath;
		return TRUE;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDOK:
			pathItem = GetDlgItem(hwnd, ID_PATH);
			urlItem = GetDlgItem(hwnd, ID_URL);
			length = SendMessage(pathItem, EM_LINELENGTH, 0, 0);
			if(length > 0) {
				data->path = new TCHAR[length + 1];
				data->path[0] = length;
				SendMessage(pathItem, EM_GETLINE, 0, (LPARAM)data->path);
				data->path[length] = 0;
			} else {
				MessageBox(hwnd, TEXT("Path cannot be empty!"),
					TEXT("MSG"), 0);
				break;
			}
			length = SendMessage(urlItem, EM_LINELENGTH, 0, 0);
			if(length > 0) {
				data->url = new TCHAR[length + 1];
				data->url[0] = length;
				SendMessage(urlItem, EM_GETLINE, 0, (LPARAM)data->url);
				data->url[length] = 0;
			} else {
				MessageBox(hwnd, TEXT("Url cannot be empty!"),
					TEXT("MSG"), 0);
				break;
			}
			CreateThread(NULL, 0, Worker, data, 0, NULL);
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

DWORD WINAPI Worker(LPVOID lParam) {
	PDLDATA data = (PDLDATA)lParam;
	StatusCallback callback;
	callback.hwnd = data->hwnd;
	HWND progressBar = GetDlgItem(data->hwnd, 777);
	SendMessage(progressBar, PBM_SETPOS, 0, 0);
	HRESULT result = URLDownloadToFile(NULL,
		data->url, data->path, 0, &callback);
	if(result == E_OUTOFMEMORY) {
		MessageBox(HWND_DESKTOP, TEXT("Memory error!"),
			TEXT("MSG"), 0);
	} else if(result != S_OK) {
		MessageBox(HWND_DESKTOP, TEXT("Download error!"),
			TEXT("MSG"), 0);
	}
	delete [] data->path;
	delete [] data->url;
	delete data;
	return 0;
}
