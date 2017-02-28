#include "stdafx.h"
#include "DemoApi.h"
#include "sized_array.h"

void PrintPrivAttrib(DWORD Attributes)
{/* This function prints out the attributes from a SID. */
	std::basic_ostream<TCHAR, std::char_traits<TCHAR> > &s = std::wcout;

	if(Attributes & SE_PRIVILEGE_ENABLED_BY_DEFAULT)
	{
		s << _T("default ");
	}
	if(Attributes & SE_PRIVILEGE_ENABLED)
	{
		s << _T("enabled, ");
	}
	if(Attributes & SE_PRIVILEGE_REMOVED)
	{
		s << _T("removed, ");
	}
	if(Attributes & SE_PRIVILEGE_USED_FOR_ACCESS)
	{
		s << _T("used for access, ");
	}
}


void PrintAttrib(DWORD Attributes)
{/* Obtain the group type */
	std::basic_ostream<TCHAR, std::char_traits<TCHAR> > &s = std::wcout;
	if(Attributes & SE_GROUP_OWNER)
	{
		s << _T(", owner");
	}
	if(Attributes & SE_GROUP_ENABLED_BY_DEFAULT)
	{
		s << _T(", default");
	}
	if(Attributes & SE_GROUP_RESOURCE)
	{
		s << _T(", domain-local");
	}
	if(Attributes & SE_GROUP_MANDATORY)
	{
		s << _T(", mandatory");
	}
	if(Attributes & SE_GROUP_USE_FOR_DENY_ONLY)
	{
		s << _T(", deny");
	}
}

void PrintSid(PSID sid)
{
	BOOL bRet = TRUE;
	LPTSTR sidText = NULL;
	SID_NAME_USE eUse = SidTypeUser;
	DWORD cchName = 0, cchReferencedDomainName = 0;

	bRet = ::LookupAccountSid(NULL, sid, NULL,
		&cchName, NULL, &cchReferencedDomainName, &eUse);	
	std::sized_array<TCHAR> UserName(cchName);
	std::sized_array<TCHAR> ReferencedDomainName(cchReferencedDomainName);

	if(::LookupAccountSid(NULL, sid, UserName.get(),
		&cchName, ReferencedDomainName.get(), &cchReferencedDomainName, &eUse))
	{
		std::wcout << ReferencedDomainName.get() << _T("\\");
		std::wcout << UserName.get();

		if(::ConvertSidToStringSid(sid, &sidText))
		{
			std::wcout << _T(" (") << sidText << _T(")");
			::LocalFree(sidText); sidText = NULL;
		}
	}
}

int PrintUserFromToken(HANDLE hToken)
{
	/* Get the current user from GetTokenInformation(TokenUser) */
	DWORD ReturnLength = 0, TokenInformationLength = 0;

	::GetTokenInformation(hToken, TokenUser, NULL, TokenInformationLength, &ReturnLength);
	std::sized_array<BYTE> TokenInformation(ReturnLength);
	TokenInformationLength = ReturnLength;

	if(::GetTokenInformation(hToken, TokenUser, TokenInformation.get(), TokenInformationLength, &ReturnLength))
	{/* Now that we have the SID, convert it to a user name */
		TOKEN_USER *tp = reinterpret_cast<TOKEN_USER *>(TokenInformation.get());
		PrintSid(tp->User.Sid);
	}
	return 0;
}

int PrintGroupsAndPrivilegesFromToken(HANDLE hToken)
{
	TOKEN_GROUPS_AND_PRIVILEGES *tp = NULL;
	DWORD ReturnLength = 0, TokenInformationLength = 0;
	/* Get the TOKEN_GROUPS_AND_PRIVILEGES from the token. */
	::GetTokenInformation(hToken, TokenGroupsAndPrivileges, NULL, TokenInformationLength, &ReturnLength);
	std::sized_array<BYTE> tpBuf(ReturnLength) ;
	TokenInformationLength = ReturnLength;
	::GetTokenInformation(hToken, TokenGroupsAndPrivileges, tpBuf.get(), TokenInformationLength, &ReturnLength);
	tp = reinterpret_cast<TOKEN_GROUPS_AND_PRIVILEGES *>(tpBuf.get());

	std::wcout << _T("\r\nAuthentication ID:") << (tp->AuthenticationId.HighPart)
		<< tp->AuthenticationId.LowPart << _T("\r\nGroups");

	for(unsigned int i = 0; i < tp->SidCount; i++)
	{/* Groups */
		std::wcout << _T("\r\n[Group ") << static_cast<unsigned int>(i) << _T("] ");
		PrintSid(tp->Sids[i].Sid);
		PrintAttrib(tp->Sids[i].Attributes);
	}

	std::wcout << _T("\r\n\r\nRestricted Sids");
	for(unsigned int i = 0; i < tp->RestrictedSidCount; i++)
	{/* Restricted Sids */
		std::wcout << _T("\r\n[SID ") << static_cast<unsigned int>(i) << _T("] ");
		PrintSid(tp->RestrictedSids[i].Sid);
		PrintAttrib(tp->RestrictedSids[i].Attributes);
	}

	std::wcout << _T("\r\n\r\nPrivileges\r\n");
	for(unsigned int i = 0; i < tp->PrivilegeCount; i++)
	{/* Privileges */
		ReturnLength = 0;
		::LookupPrivilegeName(NULL, &tp->Privileges[i].Luid, NULL, &ReturnLength);
		ReturnLength++;
		/* Docs are rather unclear on the null terminator ambiguity. Better safe than sorry. */
		std::sized_array<TCHAR> PrivilegeName (ReturnLength);

		::LookupPrivilegeName(NULL, &tp->Privileges[i].Luid, PrivilegeName.get(), &ReturnLength);

		PrintPrivAttrib(tp->Privileges[i].Attributes);
		std::wcout << _T("\t\t") << PrivilegeName.get() << _T("\r\n");
	}
	return 0;
}

BOOL GetAndPrintToken()
{
	DWORD dwSize = 0;
	HANDLE hToken = NULL;
	PTOKEN_USER ptu = NULL;
	OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken);
	if(!GetTokenInformation(hToken, TokenUser, NULL, 0, &dwSize)
		&& ERROR_INSUFFICIENT_BUFFER != GetLastError())
	{
		return FALSE;
	}
	PrintUserFromToken(hToken);
	PrintGroupsAndPrivilegesFromToken(hToken);
	CloseHandle(hToken);
	return FALSE;
}
