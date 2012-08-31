extern "C" __declspec(dllexport) 
		int _stdcall IsPrimeC(int number) {
		for(int i = 2; i * 2 < number; ++i) {
			if(number % i == 0) {
				return -1;
			}
		}
		return 0;
	}
