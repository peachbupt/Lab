#include "stdafx.h"
#include "sized_array.h"
#include "DemoApi.h"
#include <iostream>

//run with administrator
//https://forum.sysinternals.com/spawning-normal-processes-from-elevated-ones_topic17010.html
BOOL ImpersonationTest()
{
	DWORD explorerProcess = 0;
	HANDLE explorerHandle = NULL;
	HANDLE hToken = NULL;
	HANDLE hPrimaryToken;
	HWND explorerWindow = GetShellWindow();
	if (NULL == explorerWindow)
	{
		std::cout<<"GetShellWindow failed"<<std::endl;
		return FALSE;
	}
	GetWindowThreadProcessId(explorerWindow, &explorerProcess);
	if (NULL == explorerProcess)
	{
		std::cout<<"GetWindowThreadProcessId failed"<<std::endl;
		return FALSE;
	}
	explorerHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, explorerProcess);
	if (NULL == explorerHandle)
	{
		std::cout<<"OpenProcess - PROCESS_QUERY_INFORMATION - failed"<<std::endl;
		return FALSE;
	}

	if(!OpenProcessToken(explorerHandle, TOKEN_DUPLICATE, &hToken))
	{
		std::cout<<"OpenProcessToken - TOKEN_DUPLICATE - failed"<<std::endl;
	}
	else
	{
		if (DuplicateTokenEx(hToken, TOKEN_ASSIGN_PRIMARY | TOKEN_ALL_ACCESS,
			NULL, SecurityImpersonation, TokenPrimary, &hPrimaryToken)) {
			STARTUPINFO StartupInfo;
			PROCESS_INFORMATION processInfo;
			ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
			ZeroMemory(&processInfo, sizeof(PROCESS_INFORMATION));
			StartupInfo.cb = sizeof(STARTUPINFO);
			StartupInfo.dwFlags |= STARTF_USESTDHANDLES;
			BOOL ret = CreateProcessWithTokenW(hPrimaryToken, 0, NULL, L"C:\\Windows\\notepad.exe", 0, NULL, NULL, &StartupInfo, &processInfo);
			if(ret == FALSE)
			{
				std::cout<<"CreateProcessWithTokenW failed"<<GetLastError()<<std::endl;
			}
		}
		else
		{
			std::cout<<"DuplicateTokenEx failed"<<GetLastError()<<std::endl;
		}
	}

	if(explorerHandle)
	{
		CloseHandle(explorerHandle);
	}
	if(hToken)
	{
		CloseHandle(hToken);
	}

	if(hPrimaryToken)
	{
		CloseHandle(hPrimaryToken);
	}
	return TRUE;
}