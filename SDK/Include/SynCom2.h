

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Aug 29 04:39:52 2014
 */
/* Compiler settings for idl\SynCom2.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SynCom2_h__
#define __SynCom2_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISynPlugin_FWD_DEFINED__
#define __ISynPlugin_FWD_DEFINED__
typedef interface ISynPlugin ISynPlugin;
#endif 	/* __ISynPlugin_FWD_DEFINED__ */


#ifndef ___ISynGestureActionEvents_FWD_DEFINED__
#define ___ISynGestureActionEvents_FWD_DEFINED__
typedef interface _ISynGestureActionEvents _ISynGestureActionEvents;
#endif 	/* ___ISynGestureActionEvents_FWD_DEFINED__ */


#ifndef __ISynDevice2_FWD_DEFINED__
#define __ISynDevice2_FWD_DEFINED__
typedef interface ISynDevice2 ISynDevice2;
#endif 	/* __ISynDevice2_FWD_DEFINED__ */


#ifndef __SynDevice2_FWD_DEFINED__
#define __SynDevice2_FWD_DEFINED__

#ifdef __cplusplus
typedef class SynDevice2 SynDevice2;
#else
typedef struct SynDevice2 SynDevice2;
#endif /* __cplusplus */

#endif 	/* __SynDevice2_FWD_DEFINED__ */


#ifndef __SynPlugin_FWD_DEFINED__
#define __SynPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class SynPlugin SynPlugin;
#else
typedef struct SynPlugin SynPlugin;
#endif /* __cplusplus */

#endif 	/* __SynPlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ISynPlugin_INTERFACE_DEFINED__
#define __ISynPlugin_INTERFACE_DEFINED__

/* interface ISynPlugin */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISynPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FB16AA71-F2DD-45CF-9B1B-1C5F732A4B21")
    ISynPlugin : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [out] */ BSTR *pName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumberOfActions( 
            /* [out] */ LONG *plCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetActionName( 
            /* [in] */ LONG lIndex,
            /* [out] */ BSTR *pActionName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetActionStringProperty( 
            /* [in] */ LONG lIndex,
            /* [in] */ BSTR pStrValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetActionBlobProperty( 
            /* [in] */ LONG lIndex,
            /* [in] */ LONG lSize,
            /* [size_is][in] */ UCHAR *pucData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetActionProperty( 
            /* [in] */ LONG lIndex,
            /* [in] */ LONG lValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISynPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISynPlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISynPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISynPlugin * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ISynPlugin * This,
            /* [out] */ BSTR *pName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNumberOfActions )( 
            ISynPlugin * This,
            /* [out] */ LONG *plCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetActionName )( 
            ISynPlugin * This,
            /* [in] */ LONG lIndex,
            /* [out] */ BSTR *pActionName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetActionStringProperty )( 
            ISynPlugin * This,
            /* [in] */ LONG lIndex,
            /* [in] */ BSTR pStrValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetActionBlobProperty )( 
            ISynPlugin * This,
            /* [in] */ LONG lIndex,
            /* [in] */ LONG lSize,
            /* [size_is][in] */ UCHAR *pucData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetActionProperty )( 
            ISynPlugin * This,
            /* [in] */ LONG lIndex,
            /* [in] */ LONG lValue);
        
        END_INTERFACE
    } ISynPluginVtbl;

    interface ISynPlugin
    {
        CONST_VTBL struct ISynPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISynPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISynPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISynPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISynPlugin_GetName(This,pName)	\
    ( (This)->lpVtbl -> GetName(This,pName) ) 

#define ISynPlugin_GetNumberOfActions(This,plCount)	\
    ( (This)->lpVtbl -> GetNumberOfActions(This,plCount) ) 

#define ISynPlugin_GetActionName(This,lIndex,pActionName)	\
    ( (This)->lpVtbl -> GetActionName(This,lIndex,pActionName) ) 

#define ISynPlugin_SetActionStringProperty(This,lIndex,pStrValue)	\
    ( (This)->lpVtbl -> SetActionStringProperty(This,lIndex,pStrValue) ) 

#define ISynPlugin_SetActionBlobProperty(This,lIndex,lSize,pucData)	\
    ( (This)->lpVtbl -> SetActionBlobProperty(This,lIndex,lSize,pucData) ) 

#define ISynPlugin_SetActionProperty(This,lIndex,lValue)	\
    ( (This)->lpVtbl -> SetActionProperty(This,lIndex,lValue) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISynPlugin_INTERFACE_DEFINED__ */


#ifndef ___ISynGestureActionEvents_INTERFACE_DEFINED__
#define ___ISynGestureActionEvents_INTERFACE_DEFINED__

/* interface _ISynGestureActionEvents */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID__ISynGestureActionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("513F1384-1B4E-4533-975D-42C787668C08")
    _ISynGestureActionEvents : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnSynGestureActionEvent( 
            /* [in] */ LONG lGestureActionType,
            /* [in] */ LONG lGestureActionDataSize,
            /* [size_is][in] */ UCHAR *ucGestureActionData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct _ISynGestureActionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ISynGestureActionEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ISynGestureActionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ISynGestureActionEvents * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnSynGestureActionEvent )( 
            _ISynGestureActionEvents * This,
            /* [in] */ LONG lGestureActionType,
            /* [in] */ LONG lGestureActionDataSize,
            /* [size_is][in] */ UCHAR *ucGestureActionData);
        
        END_INTERFACE
    } _ISynGestureActionEventsVtbl;

    interface _ISynGestureActionEvents
    {
        CONST_VTBL struct _ISynGestureActionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ISynGestureActionEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _ISynGestureActionEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _ISynGestureActionEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _ISynGestureActionEvents_OnSynGestureActionEvent(This,lGestureActionType,lGestureActionDataSize,ucGestureActionData)	\
    ( (This)->lpVtbl -> OnSynGestureActionEvent(This,lGestureActionType,lGestureActionDataSize,ucGestureActionData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* ___ISynGestureActionEvents_INTERFACE_DEFINED__ */


#ifndef __ISynDevice2_INTERFACE_DEFINED__
#define __ISynDevice2_INTERFACE_DEFINED__

/* interface ISynDevice2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISynDevice2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4FF2C59B-0D34-42F1-A3FC-43ABC2EB70C7")
    ISynDevice2 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ LONG lSpecifier,
            /* [out][in] */ LONG *pValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPropertyDefault( 
            /* [in] */ LONG lSpecifier,
            /* [out] */ LONG *pValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStringProperty( 
            /* [in] */ LONG lSpecifier,
            /* [out] */ BSTR *strValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetProperty( 
            /* [in] */ LONG lSpecifier,
            /* [in] */ LONG lValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Select( 
            /* [in] */ LONG lHandle) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPluginAction( 
            /* [in] */ LONG lZoneId,
            /* [in] */ ISynPlugin *pPlugin,
            /* [in] */ LONG lActionIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPluginAction( 
            /* [in] */ LONG lZoneId,
            /* [out] */ ISynPlugin **ppPlugin,
            /* [out] */ LONG *lActionIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetPluginActionDefault( 
            /* [in] */ LONG lZoneId,
            /* [out] */ ISynPlugin **ppPlugin,
            /* [out] */ LONG *lActionIndexDefault) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetGestureActionNotification( 
            /* [in] */ DWORD dwProcId,
            /* [in] */ _ISynGestureActionEvents *pConnection,
            /* [in] */ LONG lValue,
            /* [in] */ LONG lValueEx) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPropertyEx( 
            /* [in] */ LONG lSpecifier,
            /* [in] */ LONG lValue[ 2 ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISynDevice2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISynDevice2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISynDevice2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISynDevice2 * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetProperty )( 
            ISynDevice2 * This,
            /* [in] */ LONG lSpecifier,
            /* [out][in] */ LONG *pValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPropertyDefault )( 
            ISynDevice2 * This,
            /* [in] */ LONG lSpecifier,
            /* [out] */ LONG *pValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStringProperty )( 
            ISynDevice2 * This,
            /* [in] */ LONG lSpecifier,
            /* [out] */ BSTR *strValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetProperty )( 
            ISynDevice2 * This,
            /* [in] */ LONG lSpecifier,
            /* [in] */ LONG lValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Select )( 
            ISynDevice2 * This,
            /* [in] */ LONG lHandle);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetPluginAction )( 
            ISynDevice2 * This,
            /* [in] */ LONG lZoneId,
            /* [in] */ ISynPlugin *pPlugin,
            /* [in] */ LONG lActionIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPluginAction )( 
            ISynDevice2 * This,
            /* [in] */ LONG lZoneId,
            /* [out] */ ISynPlugin **ppPlugin,
            /* [out] */ LONG *lActionIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetPluginActionDefault )( 
            ISynDevice2 * This,
            /* [in] */ LONG lZoneId,
            /* [out] */ ISynPlugin **ppPlugin,
            /* [out] */ LONG *lActionIndexDefault);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetGestureActionNotification )( 
            ISynDevice2 * This,
            /* [in] */ DWORD dwProcId,
            /* [in] */ _ISynGestureActionEvents *pConnection,
            /* [in] */ LONG lValue,
            /* [in] */ LONG lValueEx);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetPropertyEx )( 
            ISynDevice2 * This,
            /* [in] */ LONG lSpecifier,
            /* [in] */ LONG lValue[ 2 ]);
        
        END_INTERFACE
    } ISynDevice2Vtbl;

    interface ISynDevice2
    {
        CONST_VTBL struct ISynDevice2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISynDevice2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISynDevice2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISynDevice2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISynDevice2_GetProperty(This,lSpecifier,pValue)	\
    ( (This)->lpVtbl -> GetProperty(This,lSpecifier,pValue) ) 

#define ISynDevice2_GetPropertyDefault(This,lSpecifier,pValue)	\
    ( (This)->lpVtbl -> GetPropertyDefault(This,lSpecifier,pValue) ) 

#define ISynDevice2_GetStringProperty(This,lSpecifier,strValue)	\
    ( (This)->lpVtbl -> GetStringProperty(This,lSpecifier,strValue) ) 

#define ISynDevice2_SetProperty(This,lSpecifier,lValue)	\
    ( (This)->lpVtbl -> SetProperty(This,lSpecifier,lValue) ) 

#define ISynDevice2_Select(This,lHandle)	\
    ( (This)->lpVtbl -> Select(This,lHandle) ) 

#define ISynDevice2_SetPluginAction(This,lZoneId,pPlugin,lActionIndex)	\
    ( (This)->lpVtbl -> SetPluginAction(This,lZoneId,pPlugin,lActionIndex) ) 

#define ISynDevice2_GetPluginAction(This,lZoneId,ppPlugin,lActionIndex)	\
    ( (This)->lpVtbl -> GetPluginAction(This,lZoneId,ppPlugin,lActionIndex) ) 

#define ISynDevice2_GetPluginActionDefault(This,lZoneId,ppPlugin,lActionIndexDefault)	\
    ( (This)->lpVtbl -> GetPluginActionDefault(This,lZoneId,ppPlugin,lActionIndexDefault) ) 

#define ISynDevice2_SetGestureActionNotification(This,dwProcId,pConnection,lValue,lValueEx)	\
    ( (This)->lpVtbl -> SetGestureActionNotification(This,dwProcId,pConnection,lValue,lValueEx) ) 

#define ISynDevice2_SetPropertyEx(This,lSpecifier,lValue)	\
    ( (This)->lpVtbl -> SetPropertyEx(This,lSpecifier,lValue) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISynDevice2_INTERFACE_DEFINED__ */



#ifndef __SynTPEnhLib_LIBRARY_DEFINED__
#define __SynTPEnhLib_LIBRARY_DEFINED__

/* library SynTPEnhLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SynTPEnhLib;

EXTERN_C const CLSID CLSID_SynDevice2;

#ifdef __cplusplus

class DECLSPEC_UUID("A5D8CC60-F629-4C13-83A3-55CB38031A70")
SynDevice2;
#endif

EXTERN_C const CLSID CLSID_SynPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("B7A9DB83-64AA-4930-B171-82B792125782")
SynPlugin;
#endif
#endif /* __SynTPEnhLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


