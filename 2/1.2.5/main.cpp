#include <Windows.h>
#include <IPHlpApi.h>
#include <atlstr.h>
#include <CommCtrl.h>

INT_PTR CALLBACK DialogBoxWindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* watcher */
DWORD WINAPI Watcher(LPVOID);
bool watching = false;
/* filler */
void FillTcpTable(HWND);
/* SetWindowText wrapper */
void SetWindowText_(HWND, DWORD);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,
	LPSTR lpszArgument, int nFunsterStill) {
	DialogBox(hThisInstance,
		MAKEINTRESOURCE(501),
		HWND_DESKTOP, DialogBoxWindowProcedure);
	return 0;
}

const int TCP_LIST = 777;
const int IDREFRESH = 555;

INT_PTR CALLBACK DialogBoxWindowProcedure(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	HWND listView;
	LVCOLUMN listColumn;
	switch(message) {
	case WM_INITDIALOG:
		listView = GetDlgItem(hwnd, TCP_LIST);
		memset(&listColumn, 0, sizeof(listColumn));
		listColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
		listColumn.cx = 100;
		listColumn.pszText = TEXT("State");
		SendMessage(listView, LVM_INSERTCOLUMN, 0, (LPARAM)&listColumn);
		listColumn.pszText = TEXT("Local Address");
		SendMessage(listView, LVM_INSERTCOLUMN, 1, (LPARAM)&listColumn);
		listColumn.cx = 60;
		listColumn.pszText = TEXT("Local Port");
		SendMessage(listView, LVM_INSERTCOLUMN, 2, (LPARAM)&listColumn);
		listColumn.cx = 100;
		listColumn.pszText = TEXT("Remote Address");
		SendMessage(listView, LVM_INSERTCOLUMN, 3, (LPARAM)&listColumn);
		listColumn.cx = 80;
		listColumn.pszText = TEXT("Remote Port");
		SendMessage(listView, LVM_INSERTCOLUMN, 4, (LPARAM)&listColumn);
		watching = true;
		CreateThread(NULL, 0, Watcher, hwnd, 0, NULL);
		return TRUE;
	case WM_DESTROY:
		watching = false;
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDOK:
			EndDialog(hwnd, 0);
			return TRUE;
		case IDCANCEL:
			if(watching) {
				SetWindowText(GetDlgItem(hwnd, IDCANCEL), TEXT("Resume"));
				watching = false;
			} else {
				SetWindowText(GetDlgItem(hwnd, IDCANCEL), TEXT("Pause"));
				watching = true;
				CreateThread(NULL, 0, Watcher, hwnd, 0, NULL);
			}
			break;
		case IDREFRESH:
			FillTcpTable(hwnd);
			break;
		}
	default:
		DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

DWORD WINAPI Watcher(LPVOID lParam) {
	MIB_TCPSTATS *tcpStats = (MIB_TCPSTATS*)malloc(sizeof(MIB_TCPSTATS));
	FillTcpTable((HWND)lParam);
	while(watching) {
		if(GetTcpStatistics(tcpStats) != NO_ERROR) {
			MessageBox(NULL, TEXT("Error retrieving TCP info!"), NULL, 0);
		} else {
			SetWindowText_(GetDlgItem((HWND)lParam, 668), tcpStats->dwActiveOpens);
			SetWindowText_(GetDlgItem((HWND)lParam, 669), tcpStats->dwAttemptFails);
			SetWindowText_(GetDlgItem((HWND)lParam, 670), tcpStats->dwCurrEstab);
			SetWindowText_(GetDlgItem((HWND)lParam, 671), tcpStats->dwEstabResets);
			SetWindowText_(GetDlgItem((HWND)lParam, 672), tcpStats->dwInErrs);
			SetWindowText_(GetDlgItem((HWND)lParam, 673), tcpStats->dwInSegs);
			SetWindowText_(GetDlgItem((HWND)lParam, 674), tcpStats->dwMaxConn);
			SetWindowText_(GetDlgItem((HWND)lParam, 675), tcpStats->dwNumConns);
			SetWindowText_(GetDlgItem((HWND)lParam, 676), tcpStats->dwOutRsts);
			SetWindowText_(GetDlgItem((HWND)lParam, 677), tcpStats->dwOutSegs);
			SetWindowText_(GetDlgItem((HWND)lParam, 678), tcpStats->dwPassiveOpens);
			SetWindowText_(GetDlgItem((HWND)lParam, 679), tcpStats->dwRetransSegs);
			switch(tcpStats->dwRtoAlgorithm) {
			case MIB_TCP_RTO_OTHER:
				SetWindowText(GetDlgItem((HWND)lParam, 680), TEXT("Other"));
				break;
			case MIB_TCP_RTO_CONSTANT:
				SetWindowText(GetDlgItem((HWND)lParam, 680), TEXT("Constant Time-Out"));
				break;
			case MIB_TCP_RTO_RSRE:
				SetWindowText(GetDlgItem((HWND)lParam, 680), TEXT("MIL-STD-1778 A/B"));
				break;
			case MIB_TCP_RTO_VANJ:
				SetWindowText(GetDlgItem((HWND)lParam, 680), TEXT("Van Jacobson's"));
				break;
			default:
				break;
			}
			SetWindowText_(GetDlgItem((HWND)lParam, 681), tcpStats->dwRtoMax);
			SetWindowText_(GetDlgItem((HWND)lParam, 682), tcpStats->dwRtoMin);
			SetWindowText_(GetDlgItem((HWND)lParam, 683), tcpStats->RtoAlgorithm);
		}
		Sleep(100);
	}
	if(tcpStats) {
		free(tcpStats);
	}
	return 0;
}

void FillTcpTable(HWND hwnd) {
	MIB_TCPTABLE *tcpTable = (MIB_TCPTABLE*)malloc(sizeof(MIB_TCPTABLE));
	HWND listView = GetDlgItem(hwnd, TCP_LIST);
	LVITEM item;
	memset(&item, 0, sizeof(item));
	item.mask = LVIF_TEXT;
	item.cchTextMax = 256;
	struct in_addr IpAddr;
	TCHAR szLocalAddr[128];
	TCHAR szLocalPort[6];
	TCHAR szRemoteAddr[128];
	TCHAR szRemotePort[6];
	size_t num;
	DWORD expSize = sizeof(MIB_TCPTABLE);
	if(GetTcpTable(tcpTable, &expSize, TRUE) == ERROR_INSUFFICIENT_BUFFER) {
		free(tcpTable);
		tcpTable = (MIB_TCPTABLE*)malloc(expSize);
	}
	if(GetTcpTable(tcpTable, &expSize, TRUE) != NO_ERROR) {
		MessageBox(NULL, TEXT("Error retrieving TCP table!"), NULL, 0);
	} else {
		SendMessage(listView, LVM_DELETEALLITEMS, 0, 0);
		for(int i = 0; i < (int)tcpTable->dwNumEntries; ++i) {
			item.iItem = i;
			item.iSubItem = 0;
			switch(tcpTable->table[i].dwState) {
			case MIB_TCP_STATE_CLOSED:
				item.pszText = TEXT("CLOSED");
				break;
			case MIB_TCP_STATE_LISTEN:
				item.pszText = TEXT("LISTEN");
				break;
			case MIB_TCP_STATE_SYN_SENT:
				item.pszText = TEXT("SYN-SENT");
				break;
			case MIB_TCP_STATE_SYN_RCVD:
				item.pszText = TEXT("SYN-RECEIVED");
				break;
			case MIB_TCP_STATE_ESTAB:
				item.pszText = TEXT("ESTABLISHED");
				break;
			case MIB_TCP_STATE_FIN_WAIT1:
				item.pszText = TEXT("FIN-WAIT-1");
				break;
			case MIB_TCP_STATE_FIN_WAIT2:
				item.pszText = TEXT("FIN-WAIT-2");
				break;
			case MIB_TCP_STATE_CLOSE_WAIT:
				item.pszText = TEXT("CLOSE-WAIT");
				break;
			case MIB_TCP_STATE_CLOSING:
				item.pszText = TEXT("CLOSING");
				break;
			case MIB_TCP_STATE_LAST_ACK:
				item.pszText = TEXT("LAST-ACK");
				break;
			case MIB_TCP_STATE_TIME_WAIT:
				item.pszText = TEXT("TIME-WAIT");
				break;
			case MIB_TCP_STATE_DELETE_TCB:
				item.pszText = TEXT("DELETE-TCB");
				break;
			default:
				item.pszText = TEXT("UNKNOWN");
				break;
			}
			SendMessage(listView, LVM_INSERTITEM, i, (LPARAM)&item);
			IpAddr.S_un.S_addr = (u_long)tcpTable->table[i].dwLocalAddr;
			mbstowcs_s(&num, szLocalAddr, inet_ntoa(IpAddr), 128);
			item.iSubItem = 1;
			item.pszText = szLocalAddr;
			SendMessage(listView, LVM_SETITEM, i, (LPARAM)&item);
			_itow_s((u_short)tcpTable->table[i].dwLocalPort, szLocalPort, 6, 10);
			item.iSubItem = 2;
			item.pszText = szLocalPort;
			SendMessage(listView, LVM_SETITEM, i, (LPARAM)&item);
			IpAddr.S_un.S_addr = (u_long)tcpTable->table[i].dwRemoteAddr;
			mbstowcs_s(&num, szRemoteAddr, inet_ntoa(IpAddr), 128);
			item.iSubItem = 3;
			item.pszText = szRemoteAddr;
			SendMessage(listView, LVM_SETITEM, i, (LPARAM)&item);
			_itow_s((u_short)tcpTable->table[i].dwRemotePort, szRemotePort, 6, 10);
			item.iSubItem = 4;
			item.pszText = szRemotePort;
			SendMessage(listView, LVM_SETITEM, i, (LPARAM)&item);
		}
	}
	if(tcpTable) {
		free(tcpTable);
	}
}

void SetWindowText_(HWND hwnd, DWORD value) {
	CString str;
	str.Format(TEXT("%lu"), value);
	SetWindowText(hwnd, str);
}