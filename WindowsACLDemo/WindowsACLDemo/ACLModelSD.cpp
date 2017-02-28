#include "stdafx.h"
#include "sized_array.h"
#include "DemoApi.h"
#include <iostream>

int TranslateSddl(const std::basic_string<TCHAR> &SddlSD)
{
	/** Although SDDL is already in a readable form, Our task requires us to make it even more
	*	readable, using this form:
	*	UserName (Allow|deny|inherit). This will require some regular expressions.
	**/
	std::wcout <<SddlSD.c_str()<<std::endl;
	return 0;
}

const std::basic_string<TCHAR> DoPrintSecurityDescriptor(PSECURITY_DESCRIPTOR ppSD, SECURITY_INFORMATION psi)
{
	std::basic_string<TCHAR> Resultstr;
	LPTSTR SddlSD = NULL;
	/* ConvertStringSecurityDescriptorToSecurityDescriptor will allocate a buffer for us. */
	::ConvertSecurityDescriptorToStringSecurityDescriptor(ppSD, SDDL_REVISION_1, psi, &SddlSD, NULL);

	TranslateSddl(SddlSD);

	Resultstr = SddlSD;
	::LocalFree(SddlSD); SddlSD = NULL;
	return Resultstr;
}

int DoAccessCheck(PSECURITY_DESCRIPTOR OutSecDesc, DWORD DesiredAccess)
{
	/* This program performs an access check on the security descriptor. */
	HANDLE ProcToken = NULL, ImpersonationToken = NULL;
	/* We need an impersonation token, an access token, a generic mapping, and a desired access mask. */
	BOOL AccessStatus = FALSE;
	DWORD GrantedAccess = 0, PrivilegeSetLength = 0;
	GENERIC_MAPPING GenericMapping =
	{
		READ_CONTROL | FILE_READ_DATA | FILE_READ_ATTRIBUTES | FILE_READ_EA,
		FILE_WRITE_ATTRIBUTES | FILE_WRITE_EA | FILE_WRITE_DATA | FILE_APPEND_DATA,
		READ_CONTROL | FILE_READ_ATTRIBUTES | FILE_EXECUTE,
		FILE_ALL_ACCESS
	} ;

	if(!::OpenThreadToken(::GetCurrentThread(), TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_IMPERSONATE, TRUE, &ProcToken))
	{
		if(!::OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_IMPERSONATE, &ProcToken))
		{
			return 1;
		}
	}
	if(!::DuplicateToken(ProcToken, SecurityImpersonation, &ImpersonationToken))
	{/* Make an impersonation token */
		::CloseHandle(ProcToken); ProcToken = NULL;
		::CloseHandle(ImpersonationToken); ImpersonationToken = NULL;
	}
	::MapGenericMask(&DesiredAccess, &GenericMapping);
	/* map generic accesses to specific accesses. */

	/* What size do we need our PRIVILEGE_SET? */
	::AccessCheck(OutSecDesc, ImpersonationToken, DesiredAccess, &GenericMapping, NULL, &PrivilegeSetLength,
		&GrantedAccess, &AccessStatus);

	PRIVILEGE_SET PrivilegeSet;

	/* OK, we're ready: AccessCheck()! */
	::AccessCheck(OutSecDesc, ImpersonationToken, DesiredAccess, &GenericMapping, &PrivilegeSet, &PrivilegeSetLength,
		&GrantedAccess, &AccessStatus);
	if(AccessStatus == TRUE)
	{/* Results, results. */
		_tprintf(_T("%x"), GrantedAccess==DesiredAccess);
	}

	::CloseHandle(ProcToken); ProcToken = NULL;
	::CloseHandle(ImpersonationToken); ImpersonationToken = NULL;
	return 0;
}

BOOL GetAndPrintSecurityDescs(const std::basic_string<TCHAR> &FNameStr)
{
	/* Get all possible security information for the object: 0xf000000f */
	SECURITY_INFORMATION psi = GROUP_SECURITY_INFORMATION | OWNER_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION |
		SACL_SECURITY_INFORMATION | PROTECTED_SACL_SECURITY_INFORMATION |
		PROTECTED_DACL_SECURITY_INFORMATION | UNPROTECTED_SACL_SECURITY_INFORMATION |
		UNPROTECTED_DACL_SECURITY_INFORMATION;
	PSECURITY_DESCRIPTOR ppSecurityDescriptor = NULL;
	DWORD dwErr = ::GetNamedSecurityInfo(const_cast<LPTSTR>(FNameStr.c_str()),
		SE_FILE_OBJECT, psi, NULL, NULL, NULL, NULL, &ppSecurityDescriptor);
	if(dwErr != ERROR_SUCCESS)
	{
		//
		std::wcout << _T("GetNamedSecurityInfo error ")<< dwErr <<std::endl;
		return FALSE;
	}
	{
		PACL AbsDAcl = NULL, AbsSAcl = NULL ;
		PSID AbsOwner = NULL, AbsGroup = NULL ;
		DWORD dwSize = 0, dwSizes[5] = {0} ;
		PSECURITY_DESCRIPTOR ppSDRel = ppSecurityDescriptor ;/* Transfer ppSD into this variable. */

		::MakeAbsoluteSD(ppSDRel, NULL, &dwSizes[0], NULL, &dwSizes[4], NULL, &dwSizes[3],
			NULL, &dwSizes[2], NULL, &dwSizes[1]) ;
		for(size_t i = 0 ; i < 5 ; i++) dwSize += dwSizes[i] ;
		ppSecurityDescriptor = reinterpret_cast<PSECURITY_DESCRIPTOR>
			( ::LocalAlloc(LPTR, 2 * sizeof(ACL) + 2 * sizeof(SID) + dwSize) ) ;
		if(ppSDRel == NULL) throw std::logic_error("Could not allocate memory") ;
		/* HACKHACK: Allocate a 2D array with one LocalAlloc */

		/* Now set the pointers to the appropriate offsets. */
		dwSize = dwSizes[0] ;
		AbsOwner = reinterpret_cast<PSID>(reinterpret_cast<BYTE *>(ppSecurityDescriptor) + dwSize) ;
		dwSize += sizeof(SID) + dwSizes[1] ;
		AbsGroup = reinterpret_cast<PSID>(reinterpret_cast<BYTE *>(ppSecurityDescriptor) + dwSize) ;
		dwSize += sizeof(SID) + dwSizes[2] ;
		AbsSAcl = reinterpret_cast<PACL>(reinterpret_cast<BYTE *>(ppSecurityDescriptor) + dwSize) ;
		dwSize += sizeof(ACL) + dwSizes[3] ;
		AbsDAcl = reinterpret_cast<PACL>(reinterpret_cast<BYTE *>(ppSecurityDescriptor) + dwSize) ;

		::SetLastError(ERROR_SUCCESS) ;
		::MakeAbsoluteSD(ppSDRel, ppSecurityDescriptor, &dwSizes[0], AbsDAcl, &dwSizes[4], AbsSAcl,
			&dwSizes[3], AbsOwner, &dwSizes[2], AbsGroup, &dwSizes[1]) ;
		/* This security descriptor is now absolute */
		::LocalFree(ppSDRel) ; ppSDRel = NULL ;
	}

	/* Print out the contents of the security descriptor. */
	DoPrintSecurityDescriptor(ppSecurityDescriptor, psi);
	DoAccessCheck(ppSecurityDescriptor, FILE_GENERIC_WRITE);

	/* Cleanup. */
	::LocalFree(ppSecurityDescriptor); ppSecurityDescriptor = NULL;
	return dwErr;
}