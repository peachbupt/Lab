// MyClass.cpp : Implementation of CMyClass

#include "stdafx.h"
#include "MyClass.h"


// CMyClass


STDMETHODIMP CMyClass::TotalSum(LONG n, LONG* sum)
{
	// TODO: Add your implementation code here
	*sum = 0;
	for(int i = 0; i < n; i++)
	{
		*sum += i;
	}
	return S_OK;
}
