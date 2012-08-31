#include <ShlObj.h>
#include <windows.h>
#include <strsafe.h>

int main() {
	/* getting path */
	PTSTR path = (PTSTR)CoTaskMemAlloc(1);
	SHGetKnownFolderPath(FOLDERID_Desktop,
		0, NULL, &path);
	int length = wcslen(path) + 10;
	LPTSTR newpath = new TCHAR[length];
	StringCchCopy(newpath, length, path);
	StringCchCat(newpath, length, TEXT("\\file.rtf"));
	/* getting date */
	SYSTEMTIME time;
	GetLocalTime(&time);
	char date[100];
	sprintf_s(date, "%d %d %d\n%d:%d:%d",
		time.wYear, time.wMonth, time.wDay,
		time.wHour, time.wMinute, time.wSecond);
	/* writing to file */
	HANDLE file = CreateFile(newpath,
		GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(file == INVALID_HANDLE_VALUE) {
		return 1;
	}
	DWORD written = 0;
	BOOL error = WriteFile(file,
		date, strlen(date), &written, NULL);
	if(FALSE == error) {
		return 1;
	}
	CloseHandle(file);
	/* printing */
	HINSTANCE result = ShellExecute(NULL,
		TEXT("print"), newpath,
		NULL, NULL,
		SW_SHOWNORMAL);
	CoTaskMemFree(path);
	delete [] newpath;
	return 0;
}