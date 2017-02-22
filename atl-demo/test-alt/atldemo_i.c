

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Feb 22 20:44:57 2017
 */
/* Compiler settings for .\atldemo.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IComponentRegistrar,0xa817e7a2,0x43fa,0x11d0,0x9e,0x44,0x00,0xaa,0x00,0xb6,0x77,0x0a);


MIDL_DEFINE_GUID(IID, IID_IMyClass,0x1D8D593F,0xD92F,0x419E,0x9F,0xF1,0xFA,0x49,0x40,0x3A,0xAD,0x3A);


MIDL_DEFINE_GUID(IID, LIBID_atldemoLib,0x410EF0F5,0x512C,0x4AC8,0x8A,0xC5,0xF7,0x55,0x87,0x68,0xE1,0x57);


MIDL_DEFINE_GUID(CLSID, CLSID_CompReg,0x651C1AB5,0x97D5,0x4D25,0x9E,0xFA,0xF8,0xB7,0xA3,0x0B,0x47,0x14);


MIDL_DEFINE_GUID(CLSID, CLSID_MyClass,0xD94F275D,0xFF8F,0x4B72,0x98,0x27,0xA2,0x16,0x3D,0x81,0xB7,0x0B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



