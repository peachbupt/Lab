// WindowsACLDemo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "stdafx.h"
#include "DemoApi.h"

int _tmain(int argc, _TCHAR* argv[])
{
	printf("************************************************\n");
	GetAndPrintToken();
	printf("************************************************\n");
	GetAndPrintSecurityDescs(_T("C:\\Users\\jinxingh\\Documents\\github\\Lab\\WindowsACLDemo\\WindowsACLDemo\\DemoApi.h"));
	printf("************************************************\n");
	//ImpersonationTest();
	printf("************************************************\n");
	ReadProcessMIC();
	printf("************************************************\n");
	CreateLowProcess();
	getchar();
	return 0;
}

