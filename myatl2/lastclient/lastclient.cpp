// lastclient.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "stdafx.h"
#import "C:\Users\Kenji\Documents\Visual Studio 2010\Projects\myatl2\lastlib\bin\Release\com.lastlib.tlb" named_guids raw_interfaces_only

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);
	lastlib::IPrimeTesterCSPtr ptr;
	HRESULT result = ptr.CreateInstance(lastlib::CLSID_PrimeTesterCS);
	if(result == S_OK) {
		long value;
		long rresult;
		std::cout << "Enter number: ";
		std::cin >> value;
		ptr->IsPrime(value, &rresult);
		if(rresult == 0) {
			std::cout << "It's prime!";
		} else {
			std::cout << "It's not prime!";
		}
		std::cout << std::endl;
	}
	CoUninitialize();
	return 0;
}

