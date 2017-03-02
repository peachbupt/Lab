#include "stdafx.h"
#include "sized_array.h"
#include "DemoApi.h"
#include <iostream>

void ReadProcessMIC()
{
	//
	HANDLE hToken = NULL;
	DWORD dwSize = 0;
	OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);

	/* Get the current user from GetTokenInformation(TokenUser) */
	DWORD ReturnLength = 0, TokenInformationLength = 0;
	::GetTokenInformation(hToken, TokenIntegrityLevel, NULL, TokenInformationLength, &ReturnLength);
	std::sized_array<BYTE> TokenInformation(ReturnLength);
	TokenInformationLength = ReturnLength;

	if(::GetTokenInformation(hToken, TokenIntegrityLevel, TokenInformation.get(), TokenInformationLength, &ReturnLength))
	{
		TOKEN_USER *tp = reinterpret_cast<TOKEN_USER *>(TokenInformation.get());
		DWORD dwIntegrityLevel = *GetSidSubAuthority(tp->User.Sid, 0);
		if (dwIntegrityLevel == SECURITY_MANDATORY_LOW_RID)
		{
			// Low Integrity
			std::cout<<"Low Process\n";
		}
		else if (dwIntegrityLevel >= SECURITY_MANDATORY_MEDIUM_RID && 
			dwIntegrityLevel < SECURITY_MANDATORY_HIGH_RID)
		{
			// Medium Integrity
			std::cout<<"Medium Process\n";
		}
		else if (dwIntegrityLevel >= SECURITY_MANDATORY_HIGH_RID)
		{
			// High Integrity
			std::cout<<"High Integrity Process\n";
		}
		else if (dwIntegrityLevel >= SECURITY_MANDATORY_SYSTEM_RID)
		{
			// System Integrity
			std::cout<<"System Integrity Process\n";
		}
	}
	if(hToken)
	{
		CloseHandle(hToken);
	}
}