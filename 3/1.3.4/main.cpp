#include <windows.h>
#include <strsafe.h>
#include <WbemIdl.h>
#include <strsafe.h>
#include <CommCtrl.h>

/* Deklaracja wyprzedzaj¹ca: funkcja obs³ugi okna */
INT_PTR CALLBACK DialogBoxWindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* refresher */
void Refresh(HWND);
void SetUnknown(HWND, int);
bool ExecQuery_(LPTSTR, IEnumWbemClassObject**);
/* Nazwa klasy okna */
LPCTSTR szClassName = TEXT("1.3.4");

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpszArgument, int nFunsterStil)
{
	DialogBox(hThisInstance,
		MAKEINTRESOURCE(501),
		HWND_DESKTOP, DialogBoxWindowProcedure);
	return 0;
}

const int ID_REFRESH = 666;
const int ID_CLOSE = 777;

IWbemServices *pSvc = 0;
IWbemLocator *pLoc = 0;

INT_PTR CALLBACK DialogBoxWindowProcedure(HWND hwnd, UINT message, 
                                 WPARAM wParam, LPARAM lParam)
{
	switch(message) {
	case WM_INITDIALOG:
		if(FAILED(CoInitializeEx(0, COINIT_MULTITHREADED))) {
			MessageBox(hwnd, TEXT("Failed to init COM!"), NULL, 0);
			EndDialog(hwnd, 0);
		} else {
			if(FAILED(CoInitializeSecurity(NULL,
				-1, NULL, NULL,
				RPC_C_AUTHN_LEVEL_DEFAULT,
				RPC_C_IMP_LEVEL_IMPERSONATE,
				NULL, EOAC_NONE, NULL))) {
				CoUninitialize();
				MessageBox(hwnd, TEXT("Failed to set COM SEC!"), NULL, 0);
				EndDialog(hwnd, 0);
			} else {
				if(FAILED(CoCreateInstance(CLSID_WbemLocator,
					0, CLSCTX_INPROC_SERVER,
					IID_IWbemLocator, (LPVOID*)&pLoc))) {
					CoUninitialize();
					MessageBox(hwnd, TEXT("Failed to create WMI_COM inst!"), NULL, 0);
					EndDialog(hwnd, 0);
				} else {
					if(FAILED(pLoc->ConnectServer(TEXT("ROOT\\CIMV2"),
						NULL, NULL, 0, NULL, 0, 0, &pSvc))) {
						pLoc->Release();
						CoUninitialize();
						MessageBox(hwnd, TEXT("Failed to connect to WMI!"), NULL, 0);
						EndDialog(hwnd, 0);
					} else {
						if(FAILED(CoSetProxyBlanket(pSvc,
							RPC_C_AUTHN_WINNT,
							RPC_C_AUTHZ_NONE,
							NULL,
							RPC_C_AUTHN_LEVEL_CALL,
							RPC_C_IMP_LEVEL_IMPERSONATE,
							NULL,
							EOAC_NONE))) {
							pSvc->Release();
							pLoc->Release();
							CoUninitialize();
							MessageBox(hwnd, TEXT("Failed to set WMI proxy!"), NULL, 0);
							EndDialog(hwnd, 0);
						} else {
							Refresh(hwnd);
						}
					}
				}
			}
		}
		return TRUE;
	case WM_DESTROY:
		pSvc->Release();
		pLoc->Release();
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case ID_REFRESH:
			Refresh(hwnd);
			break;
		case ID_CLOSE:
			EndDialog(hwnd, 0);
			return TRUE;
		}
	default:
		DefWindowProc(hwnd, message, wParam, lParam);
	}
    return 0;
}

void Refresh(HWND hwnd) {
	IWbemClassObject *pclsObj;
	ULONG uReturn = 0;
	/* Processor */
	IEnumWbemClassObject *pEnum = NULL;
	if(!ExecQuery_(TEXT("SELECT Name FROM Win32_Processor"), &pEnum)) {
		SetUnknown(hwnd, 888);
	} else {
		pEnum->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if(uReturn != 0) {
			VARIANT vtProp;
			pclsObj->Get(TEXT("Name"), 0, &vtProp, 0, 0);
			SetWindowText(GetDlgItem(hwnd, 888), vtProp.bstrVal);
			VariantClear(&vtProp);
			pclsObj->Release();
		} else {
			SetUnknown(hwnd, 888);
		}
	}
	/* Free Memory */
	pEnum->Reset();
	if(!ExecQuery_(TEXT("SELECT FreePhysicalMemory FROM Win32_OperatingSystem"),
		&pEnum)) {
		SetUnknown(hwnd, 889);
	} else {
		UINT64 memory;
		pEnum->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if(uReturn != 0) {
			VARIANT vtProp;
			pclsObj->Get(TEXT("FreePhysicalMemory"), 0, &vtProp, 0, 0);
			memory = _wtoi64(vtProp.bstrVal) / 1024;
			TCHAR buffer[20];
			_ui64tow_s(memory, buffer, 20, 10);
			SetWindowText(GetDlgItem(hwnd, 889), buffer);
			VariantClear(&vtProp);
			pclsObj->Release();
		} else {
			SetUnknown(hwnd, 889);
		}
	}
	/* Total Memory */
	pEnum->Reset();
	if(!ExecQuery_(TEXT("SELECT Capacity FROM Win32_PhysicalMemory"), &pEnum)) {
		SetUnknown(hwnd, 890);
	} else {
		UINT64 memory = 0;
		while(pEnum) {
			pEnum->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if(uReturn != 0) {
				VARIANT vtProp;
				pclsObj->Get(TEXT("Capacity"), 0, &vtProp, 0, 0);
				memory += _wtoi64(vtProp.bstrVal);
				VariantClear(&vtProp);
				pclsObj->Release();
			} else {
				break;
			}
		}
		if(memory == 0) {
			SetUnknown(hwnd, 890);
		} else {
			memory /= 1048576;
			TCHAR buffer[20];
			_ui64tow_s(memory, buffer, 20, 10);
			SetWindowText(GetDlgItem(hwnd, 890), buffer);
		}
	}
	/* Operating System Info */
	pEnum->Reset();
	if(!ExecQuery_(TEXT("SELECT Caption,Version,ServicePackMajorVersion,ServicePackMinorVersion FROM Win32_OperatingSystem"), &pEnum)) {
		SetUnknown(hwnd, 891);
	} else {
		pEnum->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if(uReturn != 0) {
			TCHAR buffer[1000];
			VARIANT vtProp;
			pclsObj->Get(TEXT("Caption"), 0, &vtProp, 0, 0);
			StringCchCopy(buffer, 1000, vtProp.bstrVal);
			VariantClear(&vtProp);
			pclsObj->Get(TEXT("Version"), 0, &vtProp, 0, 0);
			StringCchCat(buffer, 1000, vtProp.bstrVal);
			VariantClear(&vtProp);
			StringCchCat(buffer, 1000, TEXT(" SP "));
			pclsObj->Get(TEXT("ServicePackMajorVersion"), 0, &vtProp, 0, 0);
			TCHAR buff[10];
			_itow_s(vtProp.uiVal, buff, 10);
			StringCchCat(buffer, 1000, buff);
			VariantClear(&vtProp);
			StringCchCat(buffer, 1000, TEXT("."));
			pclsObj->Get(TEXT("ServicePackMinorVersion"), 0, &vtProp, 0, 0);
			_itow_s(vtProp.uiVal, buff, 10);
			StringCchCat(buffer, 1000, buff);
			SetWindowText(GetDlgItem(hwnd, 891), buffer);
			VariantClear(&vtProp);
			pclsObj->Release();
		} else {
			SetUnknown(hwnd, 891);
		}
	}
	/* User Info */
	pEnum->Reset();
	if(!ExecQuery_(TEXT("SELECT UserName FROM Win32_ComputerSystem"), &pEnum)) {
		SetUnknown(hwnd, 892);
	} else {
		pEnum->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if(uReturn != 0) {
			VARIANT vtProp;
			pclsObj->Get(TEXT("UserName"), 0, &vtProp, 0, 0);
			SetWindowText(GetDlgItem(hwnd, 892), vtProp.bstrVal);
			VariantClear(&vtProp);
			pclsObj->Release();
		} else {
			SetUnknown(hwnd, 892);
		}
	}
	/* Desktop Info (res and depth) */
	pEnum->Reset();
	if(!ExecQuery_(TEXT("SELECT CurrentHorizontalResolution,CurrentVerticalResolution,CurrentBitsPerPixel FROM Win32_VideoController"),
		&pEnum)) {
		SetUnknown(hwnd, 893);
	} else {
		pEnum->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if(uReturn != 0) {
			TCHAR buffer[1000];
			VARIANT vtProp;
			pclsObj->Get(TEXT("CurrentHorizontalResolution"), 0, &vtProp, 0, 0);
			TCHAR buff[10];
			_itow_s(vtProp.uintVal, buff, 10);
			StringCchCopy(buffer, 1000, buff);
			VariantClear(&vtProp);
			StringCchCat(buffer, 1000, TEXT(" x "));
			pclsObj->Get(TEXT("CurrentVerticalResolution"), 0, &vtProp, 0, 0);
			_itow_s(vtProp.uintVal, buff, 10);
			StringCchCat(buffer, 1000, buff);
			VariantClear(&vtProp);
			StringCchCat(buffer, 1000, TEXT(" ("));
			pclsObj->Get(TEXT("CurrentBitsPerPixel"), 0, &vtProp, 0, 0);
			_itow_s(vtProp.uintVal, buff, 10);
			StringCchCat(buffer, 1000, buff);
			VariantClear(&vtProp);
			StringCchCat(buffer, 1000, TEXT(" Bits)"));
			SetWindowText(GetDlgItem(hwnd, 893), buffer);
			pclsObj->Release();
		}
	}
	/* Printers */
	pEnum->Reset();
	if(ExecQuery_(TEXT("SELECT Name FROM Win32_Printer"), &pEnum)) {
		HWND listView = GetDlgItem(hwnd, 555);
		SendMessage(listView, LVM_DELETEALLITEMS, 0, 0);
		LVITEM item;
		item.mask = LVIF_TEXT;
		item.cchTextMax = 256;
		item.iSubItem = 0;
		item.iItem = 0;
		while(pEnum) {
			pEnum->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if(uReturn == 0) {
				break;
			}
			VARIANT vtProp;
			pclsObj->Get(TEXT("Name"), 0, &vtProp, 0, 0);
			item.iSubItem = 0;
			item.iItem = 0;
			item.pszText = vtProp.bstrVal;
			ListView_InsertItem(listView, &item);
			VariantClear(&vtProp);
			pclsObj->Release();
		}
	}
	pEnum->Release();
	/* IE */
	TCHAR version[20];
	HKEY result;
	DWORD length = 20;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\Microsoft\\Internet Explorer\\Version Vector"), 0,
		KEY_READ, &result) != ERROR_SUCCESS) {
		SetUnknown(hwnd, 897);
	} else {
		if(RegQueryValueEx(result, TEXT("IE"), NULL, NULL,
			(LPBYTE)&version, &length) != ERROR_SUCCESS) {
			SetUnknown(hwnd, 897);
		} else {
			SetWindowText(GetDlgItem(hwnd, 897), version);
		}
	}
	/* .NET */
	TCHAR net_buffer[1000];
	StringCchCopy(net_buffer, 1000, TEXT(""));
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client"), 0,
		KEY_READ, &result) != ERROR_SUCCESS) {
		SetUnknown(hwnd, 894);
	} else {
		DWORD value;
		DWORD size = sizeof(DWORD);
		if(RegQueryValueEx(result, TEXT("Install"), NULL, NULL,
			(LPBYTE)&value, &size) == ERROR_SUCCESS && value == 1) {
			StringCchCat(net_buffer, 1000, TEXT("4 - Client; "));
		}
	}
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full"), 0,
		KEY_READ, &result) != ERROR_SUCCESS) {
		SetUnknown(hwnd, 894);
	} else {
		DWORD value;
		DWORD size = sizeof(DWORD);
		if(RegQueryValueEx(result, TEXT("Install"), NULL, NULL,
			(LPBYTE)&value, &size) == ERROR_SUCCESS && value == 1) {
			StringCchCat(net_buffer, 1000, TEXT("4 - Full; "));
		}
	}
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v3.5"), 0,
		KEY_READ, &result) != ERROR_SUCCESS) {
		SetUnknown(hwnd, 894);
	} else {
		DWORD value;
		DWORD size = sizeof(DWORD);
		if(RegQueryValueEx(result, TEXT("Install"), NULL, NULL,
			(LPBYTE)&value, &size) == ERROR_SUCCESS && value == 1) {
			StringCchCat(net_buffer, 1000, TEXT("3.5"));
			if(RegQueryValueEx(result, TEXT("SP"), NULL, NULL,
				(LPBYTE)&value, &size) == ERROR_SUCCESS && value >= 1) {
				StringCchCat(net_buffer, 1000, TEXT(" (with SP)"));
			}
			StringCchCat(net_buffer, 1000, TEXT("; "));
		}
	}
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v3.0"), 0,
		KEY_READ, &result) != ERROR_SUCCESS) {
		SetUnknown(hwnd, 894);
	} else {
		DWORD value;
		DWORD size = sizeof(DWORD);
		if(RegQueryValueEx(result, TEXT("Install"), NULL, NULL,
			(LPBYTE)&value, &size) == ERROR_SUCCESS && value == 1) {
			StringCchCat(net_buffer, 1000, TEXT("3.0"));
			if(RegQueryValueEx(result, TEXT("SP"), NULL, NULL,
				(LPBYTE)&value, &size) == ERROR_SUCCESS && value >= 1) {
				StringCchCat(net_buffer, 1000, TEXT(" (with SP)"));
			}
			StringCchCat(net_buffer, 1000, TEXT("; "));
		}
	}
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		TEXT("SOFTWARE\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727"), 0,
		KEY_READ, &result) != ERROR_SUCCESS) {
		SetUnknown(hwnd, 894);
	} else {
		DWORD value;
		DWORD size = sizeof(DWORD);
		if(RegQueryValueEx(result, TEXT("Install"), NULL, NULL,
			(LPBYTE)&value, &size) == ERROR_SUCCESS && value == 1) {
			StringCchCat(net_buffer, 1000, TEXT("2.0"));
			if(RegQueryValueEx(result, TEXT("SP"), NULL, NULL,
				(LPBYTE)&value, &size) == ERROR_SUCCESS && value >= 1) {
				StringCchCat(net_buffer, 1000, TEXT(" (with SP)"));
			}
			StringCchCat(net_buffer, 1000, TEXT("; "));
		}
	}
	SetWindowText(GetDlgItem(hwnd, 894), net_buffer);
}

void SetUnknown(HWND hwnd, int item) {
	SetWindowText(GetDlgItem(hwnd, item), TEXT("Unknown"));
}

bool ExecQuery_(LPTSTR query, IEnumWbemClassObject **result) {
	if(FAILED(pSvc->ExecQuery(TEXT("WQL"), query,
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL, result))) {
		return false;
	} else {
		return true;
	}
}