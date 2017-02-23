

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Feb 23 09:23:20 2017
 */
/* Compiler settings for .\altbho.idl:
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


MIDL_DEFINE_GUID(IID, IID_IEyEonIE,0xE0F5ECFC,0x9244,0x4B3E,0x9E,0x90,0xC3,0x0F,0xF2,0x8F,0xA9,0x43);


MIDL_DEFINE_GUID(IID, LIBID_altbhoLib,0xC944AC7E,0xEAB7,0x4E84,0xAF,0x37,0x98,0x47,0xAB,0x40,0x8A,0x99);


MIDL_DEFINE_GUID(CLSID, CLSID_CompReg,0x3BA845B4,0xD8A8,0x4186,0xAF,0xEF,0x06,0xE0,0xA5,0x9F,0xFA,0x03);


MIDL_DEFINE_GUID(CLSID, CLSID_EyEonIE,0x65778286,0xC644,0x4543,0xB9,0x83,0xB2,0x65,0xAB,0x44,0x6A,0x65);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



