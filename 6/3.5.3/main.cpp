extern "C" __declspec(dllexport) int __stdcall ExecuteC(int n, int(*f)(int)) {
	return f(n);
}