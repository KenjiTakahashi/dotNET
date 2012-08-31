// PrimeTester.cpp : Implementation of PrimeTester

#include "stdafx.h"
#include "PrimeTester.h"


// PrimeTester



STDMETHODIMP PrimeTester::IsPrime(int number, int *state)
{
	for(int i = 2; i * 2 < number; ++i) {
		if(number % i == 0) {
			*state = 1;
		}
	}
	return S_OK;
}


STDMETHODIMP PrimeTester::IsPrime2(int number, int* state)
{
	for(int i = 2; i * 2 < number; ++i) {
		if(number % i == 0) {
			*state = 1;
		}
	}
	return S_OK;
}
