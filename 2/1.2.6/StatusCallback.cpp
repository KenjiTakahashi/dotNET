#include "StatusCallback.h"

StatusCallback::StatusCallback() {
}

StatusCallback::~StatusCallback() {
}

HRESULT StatusCallback::OnProgress(ULONG ulProgress, ULONG ulProgressMax,
	ULONG ulStatusCode, LPCTSTR wszStatusText) {
	HWND progressBar = GetDlgItem(hwnd, 777);
	if(0 != ulProgressMax) {
		SendMessage(progressBar, PBM_SETPOS, 100 * ulProgress / ulProgressMax, 0);
	} else {
		SendMessage(progressBar, PBM_SETPOS, 100, 0);
	}
	return S_OK;
}