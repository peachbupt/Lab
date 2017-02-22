// test-alt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "atldemo_i.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	HRESULT hr;
	IMyClass *pMyClass = NULL;
	hr = CoInitialize(NULL);
	hr = CoCreateInstance(CLSID_MyClass, NULL, 1,
		IID_IMyClass, (void**)&pMyClass);
	if(SUCCEEDED(hr))
	{
		long n = 0;
		long sum = 0;
		cout << "Input an Integer"<< endl;
		cin >> n;
		pMyClass->TotalSum(n, &sum);
		std::cout<<"sum of 0 - "<< n <<" = "<<sum<<endl;
	}
	CoUninitialize();
	return 0;
}

