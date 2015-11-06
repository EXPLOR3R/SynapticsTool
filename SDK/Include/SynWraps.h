//===========================================================================
// Copyright (c) 1996-2012 Synaptics Incorporated. All rights reserved.
//
// RCS Header - Do not delete or modify.
//
// $RCSfile: synwraps.h,v $
// $Source: /cvs/software/Driver/SynCom/SynCom/synwraps.h,v $
//===========================================================================

// Public header file for access to the Synaptics COM API/Toolkit.

#ifndef __SYNWRAPS_H
#define __SYNWRAPS_H

#include "SynComDefs.h"
#ifdef SYNA_LINUX // Linux requires concrete classes
#include "bstr.h"
#include "SynAPI.h"
#include "LinuxSynDevice.h"
#include "LinuxSynAPI.h"
#include "SynPacket.h"
#include "SynGroup.h"
#define __ISynDevice CLinuxSynDevice
#define __ISynAPI    CLinuxSynAPI
#define __ISynPacket CSynPacket
#define __ISynGroup  CSynGroup
#else
#include <comdef.h>
#include <string>
#define __ISynAPI    ISynAPI
#define __ISynDevice ISynDevice
#define __ISynPacket ISynPacket
#define __ISynGroup  ISynGroup

#endif

const LPTSTR pszSCRYBE_PROFILES_PATH = TEXT("Software\\Synaptics\\Scrybe\\Profiles");
const LPTSTR pszSCRYBE_SETTINGS_WINDOW_NAME = TEXT("ScrybeSettingsWindowName");

struct SProcessedKBPacket;

// Definitions used for Synaptics Gesture API
const LPTSTR pszSYN_GESTURE_MSG = TEXT("SYN_GESTURE-{96E11DAB-6AE3-48c6-A1CF-391D8C5F2A17}");

#ifdef THINTOUCH
#define SYNCOM_SYNAPI L"SynComTT.SynAPI"
#define SYNCOM_POINTINGDEVICE L"SynComTT.PointingDevice"
#define SYNCOM_SYNDISPLAY L"SynComTT.SynDisplay"
#define SYNCOM_SYNPACKET L"SynComTT.SynPacket"
#define SYNCOM_SYNGROUP L"SynComTT.SynGroup"
#else
#define SYNCOM_SYNAPI L"SynCom.SynAPI"
#define SYNCOM_POINTINGDEVICE L"SynCom.PointingDevice"
#define SYNCOM_SYNDISPLAY L"SynCom.SynDisplay"
#define SYNCOM_SYNPACKET L"SynCom.SynPacket"
#define SYNCOM_SYNGROUP L"SynCom.SynGroup"
#endif
#ifndef SYNA_LINUX

//---------------------------------------------------------------------------
// GetCurrentModule()
//
// PURPOSE:
//    Get the module handle of the app (dll, exe ...) which call SynCom.dll
//---------------------------------------------------------------------------
inline HMODULE GetCurrentModule(HMODULE hKernel32)
{ 
  HMODULE hModule = 0;

  if (hKernel32) {
    BOOL (__stdcall *pFGetModuleHandleExW)(DWORD, LPCWSTR, HMODULE *) = NULL;
    pFGetModuleHandleExW = (BOOL (__stdcall *)(DWORD, LPCWSTR, HMODULE *)) 
      GetProcAddress(hKernel32, "GetModuleHandleExW");

    if (pFGetModuleHandleExW) {
      DWORD dwGET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS = 0x4;
      (*pFGetModuleHandleExW)
        (dwGET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)GetCurrentModule, &hModule);
    }
  }

  return hModule;
}

//---------------------------------------------------------------------------
// GetSynComLocalManifest()
//
//---------------------------------------------------------------------------
inline LPCWSTR GetSynComLocalManifest()
{
  static BOOL s_bFirstCall = TRUE;
  static WCHAR s_szManifestFile[MAX_PATH] = {0}; // empty string

  if (!s_bFirstCall) {    
    return s_szManifestFile;
  }

  s_bFirstCall = FALSE;

  HMODULE hd = 0;
  BOOL bIsWow64 = FALSE;
  HMODULE hKernel32 = LoadLibraryW(L"kernel32.dll");

  if (hKernel32) {
    BOOL (__stdcall *pFIsWow64Process)(HANDLE, PBOOL) = NULL;
    pFIsWow64Process = (BOOL (__stdcall *)(HANDLE, PBOOL)) 
      GetProcAddress(hKernel32, "IsWow64Process");

    if (pFIsWow64Process) {
      (*pFIsWow64Process)(GetCurrentProcess(), &bIsWow64);
    }
    hd = GetCurrentModule(hKernel32);
    FreeLibrary(hKernel32);
  }
  
  if (!hd) {    
    return s_szManifestFile; // empty string
  }
  
  GetModuleFileNameW(hd, s_szManifestFile, _countof(s_szManifestFile));  
  WCHAR * pwstr = wcsrchr(s_szManifestFile, L'\\'); 
  if (pwstr) {
    *pwstr = 0;
  }
  
  std::wstring wsFilePath = s_szManifestFile;
#ifdef THINTOUCH
  if (bIsWow64 &&
    GetFileAttributesW((wsFilePath + L"\\SynCom32TT.dll").c_str()) != INVALID_FILE_ATTRIBUTES &&
    GetFileAttributesW((wsFilePath + L"\\SynCom32TT.dll.manifest").c_str()) != INVALID_FILE_ATTRIBUTES)
  {    
    wcscat_s(s_szManifestFile, _countof(s_szManifestFile), L"\\SynCom32TT.dll.manifest");  
  } else if (!bIsWow64 &&
    GetFileAttributesW((wsFilePath + L"\\SynComTT.dll").c_str()) != INVALID_FILE_ATTRIBUTES &&
    GetFileAttributesW((wsFilePath + L"\\SynComTT.dll.manifest").c_str()) != INVALID_FILE_ATTRIBUTES)
  {    
    wcscat_s(s_szManifestFile, _countof(s_szManifestFile), L"\\SynComTT.dll.manifest");
  } else {
    s_szManifestFile[0] = 0; // empty string
  }
#else
  if (bIsWow64 &&
    GetFileAttributesW((wsFilePath + L"\\SynCom32.dll").c_str()) != INVALID_FILE_ATTRIBUTES &&
    GetFileAttributesW((wsFilePath + L"\\SynCom32.dll.manifest").c_str()) != INVALID_FILE_ATTRIBUTES)
  {    
    wcscat_s(s_szManifestFile, _countof(s_szManifestFile), L"\\SynCom32.dll.manifest");  
  } else if (!bIsWow64 &&
    GetFileAttributesW((wsFilePath + L"\\SynCom.dll").c_str()) != INVALID_FILE_ATTRIBUTES &&
    GetFileAttributesW((wsFilePath + L"\\SynCom.dll.manifest").c_str()) != INVALID_FILE_ATTRIBUTES)
  {    
    wcscat_s(s_szManifestFile, _countof(s_szManifestFile), L"\\SynCom.dll.manifest");
  } else {
    s_szManifestFile[0] = 0; // empty string
  }
#endif // THINTOUCH
  return s_szManifestFile;
}

//---------------------------------------------------------------------------
// SetupContextForSynComLocal()
//
// PARAMETERS:
//   rhActCtx [out] a handle to the returned activation context in CreateActCtxW
//   rlpCookie [out] uniquely identifying a specific, activated activation context in ActivateActCtx
//   
// NOTE:
//   #define _WIN32_WINNT 0x0501 to access ACTCTXW structure  is used by the CreateActCtx function to
//   create the activation context
//---------------------------------------------------------------------------
inline BOOL SetupContextForSynComLocal(HANDLE &rhActCtx, ULONG_PTR &rlpCookie)
{  
  if (*GetSynComLocalManifest() == 0) {
    return FALSE;
  }

  ACTCTXW actctx; 
  ZeroMemory(&actctx, sizeof(actctx)); 
  actctx.cbSize = sizeof(actctx);  // This is used to determine the version of this structure.
  actctx.lpSource = GetSynComLocalManifest();  

  rhActCtx = CreateActCtxW(&actctx); 
  
  return (rhActCtx != INVALID_HANDLE_VALUE) && ActivateActCtx(rhActCtx, &rlpCookie);  
}

//---------------------------------------------------------------------------
// CleanupContextForSynComLocal()
//
//    Deactivates the activation context corresponding to the specified cookie.
//    Decrements the reference count of the specified activation context.
//---------------------------------------------------------------------------
inline VOID CleanupContextForSynComLocal(HANDLE hActCtx, ULONG_PTR lpCookie)
{
  if (lpCookie) {    
    DeactivateActCtx(0, lpCookie);
  }
  if (hActCtx != INVALID_HANDLE_VALUE) {    
    ReleaseActCtx(hActCtx);
  }
}

#endif

typedef struct
{
  SynProfileCommand Command;
  SynProfileCommandResult Result;
  TCHAR szProfileDescription[1024];
  TCHAR szProfileGuidString[48];
} SCopyProfileData;

typedef struct _SSynGestureActionEventData
{
  DWORD dwGestureSubType;
  LONG lGestureActionValue;
  LONG lGestureActionValueReserved;
} SSynGestureActionEventData;

template <class Object, class Interface> class SynWrap
{
public:
  SynWrap()
  {
#ifdef SYNA_LINUX
    m_pInternal = Interface::CreateInstance();
#else
    m_pInternal = 0; // Fault reliably if a SynWrap can't be created.

    ULONG_PTR lpCookie = 0; 
    HANDLE hActCtx = INVALID_HANDLE_VALUE;    
    SetupContextForSynComLocal(hActCtx, lpCookie);

    DoThreadCoInitialize();
    CoCreateInstance(_uuidof(Object), 0, CLSCTX_SERVER,
      _uuidof(Interface), (void **) &m_pInternal);

    CleanupContextForSynComLocal(hActCtx, lpCookie);

#endif
  }

  SynWrap(LPCOLESTR psProgID)
  {
#ifdef SYNA_LINUX
    m_pInternal = Interface::CreateInstance();
#else
    CLSID clsid;
    m_pInternal = 0; // Fault reliably if a SynWrap can't be created.

    ULONG_PTR lpCookie = 0; 
    HANDLE hActCtx = INVALID_HANDLE_VALUE;    
    SetupContextForSynComLocal(hActCtx, lpCookie);
    
    DoThreadCoInitialize();
    CLSIDFromProgID( psProgID, &clsid );
    CoCreateInstance(clsid, 0, CLSCTX_SERVER,
      _uuidof(Interface), (void **) &m_pInternal);

    CleanupContextForSynComLocal(hActCtx, lpCookie);

#endif
  }

  SynWrap(Interface *pDevice)
  {
    m_pInternal = pDevice;
    if (m_pInternal)
      pDevice->AddRef();
  }
  
  ~SynWrap()
  {
    if (m_pInternal) {
      m_pInternal->Release();
      m_pInternal = NULL;
    }
 }

  operator Interface *() { return m_pInternal; }

  Interface *operator->() { return m_pInternal; }


  LONG GetLongProperty(LONG lSpecifier) const
  {
    LONG lProperty = 0;

    if (m_pInternal)
      m_pInternal->GetProperty(lSpecifier, &lProperty);
    return lProperty;
  }

  bool SetLongProperty(LONG lSpecifier, LONG lProperty)
  {
    return  (m_pInternal &&
      m_pInternal->SetProperty(lSpecifier, lProperty) == S_OK);
  }

  _bstr_t GetStringProperty (LONG lSpecifier)
  {
    char buf[256];
    LONG ulSize = sizeof(buf);
    buf[0] = 0;

    if (m_pInternal)
      m_pInternal->GetStringProperty(lSpecifier, (unsigned char *)buf, &ulSize);
    return _bstr_t(buf);
  }

  Interface *m_pInternal;

private:
  void DoThreadCoInitialize()
  {
#ifndef SYNA_LINUX
    static DWORD s_dwTlsIndex = TlsAlloc();
    if (!TlsGetValue(s_dwTlsIndex)) { // These are initted to NULL for each thread.
      CoInitialize(0);
      TlsSetValue(s_dwTlsIndex, (PVOID)1);
    }
#endif
  }
};

template <class Object, class Interface, class Events> class SynWrapEvents :
  public SynWrap<Object, Interface>,
  public Events
{
public:
  SynWrapEvents() { }
  SynWrapEvents(LPCOLESTR psProgID) : SynWrap<Object, Interface>(psProgID){ }
  SynWrapEvents(Interface *pDevice) : SynWrap<Object, Interface>(pDevice) { }
  ~SynWrapEvents() { }

  HRESULT Activate()
  {
    HRESULT res = SYNE_FAIL;
    if (this->m_pInternal)
      res = this->m_pInternal->SetSynchronousNotification(this);

    return res;
  }

  HRESULT Deactivate()
  {
    HRESULT res = SYNE_FAIL;
    if (this->m_pInternal)
      res = this->m_pInternal->SetSynchronousNotification(0);

    return res;
  }

  HRESULT STDMETHODCALLTYPE OnSynAPINotify(LONG /* lReason */) { return 0; }
  HRESULT STDMETHODCALLTYPE OnSynDevicePacket(LONG /* lSequence */) { return 0; }
  HRESULT STDMETHODCALLTYPE OnSynDisplayMessage(LONG /* lMessage */) { return 0; }
};


#ifndef SYNA_LINUX
#pragma warning(disable:4100)
#endif

// Dummy classes used in case if no connection can be established
// to the COM server. These are needed because the connection to COM
// is done in constructor thus its failure cannot be tracked

class CDummySynAPI : public ISynAPI
{
public:
  CDummySynAPI(){}
  ~CDummySynAPI(){}

  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
    REFIID riid, void  **ppvObject){return E_UNEXPECTED;}

  virtual ULONG STDMETHODCALLTYPE AddRef( void){return 1;}

  virtual ULONG STDMETHODCALLTYPE Release( void){return 1;}


  virtual  HRESULT STDMETHODCALLTYPE Initialize(){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE FindDevice(LONG lConnectionType,
    LONG lDeviceType, LONG *ulHandle){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE CreateDevice(
    LONG lHandle, ISynDevice **ppDevice){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE GetProperty(
    LONG lSpecifier, LONG *pValue){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE GetStringProperty(
    LONG lSpecifier, unsigned char *pBuffer, LONG *ulBufLen){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE SetProperty(
    LONG lSpecifier, LONG lValue){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE SetEventNotification(
    HANDLE hEvent){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE GetEventParameter(
    LONG *lParameter){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE PersistState(
    LONG lStateFlags){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE RestoreState(
    LONG lStateFlags){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE RestoreDefaultState(
    LONG lStateFlags){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE HardwareBroadcast(
    LONG lAction){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE SetSynchronousNotification(
    _ISynAPIEvents *pCallbackInstance){return E_UNEXPECTED;}

  virtual  HRESULT STDMETHODCALLTYPE ForwardSystemMessage(
    UINT uMsg, WPARAM wParam, LPARAM lParam){return E_UNEXPECTED;}

};



class CDummySynDevice : public ISynDevice
{
public:
  CDummySynDevice(){}
  ~CDummySynDevice(){}

  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
    REFIID riid, void  **ppvObject){return E_UNEXPECTED;}

  virtual ULONG STDMETHODCALLTYPE AddRef( void){return 1;}

  virtual ULONG STDMETHODCALLTYPE Release( void){return 1;}

  virtual HRESULT STDMETHODCALLTYPE GetProperty(
    LONG lSpecifier,
    LONG *pValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetBooleanProperty(
    LONG lSpecifier,
    LONG *pValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetStringProperty(
    LONG lSpecifier,
    unsigned char *pBuffer,
    LONG *ulBufLen){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetProperty(
    LONG lSpecifier,
    LONG lValue){return E_UNEXPECTED;}
  
  virtual HRESULT STDMETHODCALLTYPE SetPropertyEx(
    LONG lSpecifier,
    LONG lValue[2]){
    return E_UNEXPECTED;
  }

  virtual HRESULT STDMETHODCALLTYPE SetEventNotification(
    HANDLE hEvent){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE CreatePacket(
    ISynPacket **ppPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE LoadPacket(
    ISynPacket *pPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE ForceMotion(
    LONG lDeltaX,
    LONG lDeltaY,
    LONG lButtonState){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE ForcePacket(
    ISynPacket *pPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Acquire(
    LONG lFlags){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Unacquire( void){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE CreateDisplay(
    ISynDisplay **ppDisplay){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Select(
    LONG lHandle){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE PeekPacket(
    LONG *plSequence){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetSynchronousNotification(
    _ISynDeviceEvents *pCallbackInstance){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetPropertyDefault(
    LONG lSpecifier,
    LONG *pValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE BulkTransaction(
    ULONG ulWriteLength,
    UCHAR *ucWriteBuffer,
    ULONG ulReadLength,
    UCHAR *ucReadBuffer){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE DiagnosticTransaction(
    ULONG ulWriteLength,
    UCHAR *ucWriteBuffer,
    ULONG ulReadLength,
    UCHAR *ucReadBuffer){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE DiagnosticSelect(
    LONG lHandle,
    LONG lFlags){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE ForceMotionWithWheel(
    LONG lDeltaX,
    LONG lDeltaY,
    LONG lButtonState,
    LONG lWheelDelta){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE ForceMotionWithHorizontalWheel(
    LONG lDeltaX,
    LONG lDeltaY,
    LONG lButtonState,
    LONG lWheelDelta){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE ValidateProperty(
    LONG lSpecifier,
    LONG lSynAccessRightType){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE ForceSecondaryFingerPacket(
    ISynPacket *pPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE ForceFingerCountPacket(
    ISynPacket *pPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetZoneAction(
    DWORD dwZoneID,
    DWORD dwActionID,
    LPTSTR pszPlugInName){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE OnSynGestureActionEvent(
    LONG lType,
    LONG lSize,
    UCHAR *ucData) { return E_UNEXPECTED; }


  virtual HRESULT STDMETHODCALLTYPE ForceMotionWithWheelEx(
    LONG lDeltaX,
    LONG lDeltaY,
    LONG lButtonState,
    LONG lWheelDelta,
    LONG lFlags){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE LoadGroupPackets( 
    ISynPacket **ppPacket,
    ULONG ulPacketCount){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetBinaryProperty(
    LONG lSpecifier,
    WORD wArg,
    UCHAR *pucData,
    WORD nData){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE CreateGroup( 
    ISynGroup **ppGroup){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE LoadGroup( 
    ISynGroup *pGroup){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetBinaryProperty(
    LONG lSpecifier,
    WORD wArg,
    UCHAR *pucData,
    WORD nData){return E_UNEXPECTED;}
  
  virtual HRESULT STDMETHODCALLTYPE GetDefaultBinaryProperty(
    LONG lSpecifier,
    WORD wArg,
    UCHAR *pucData,
    WORD nData){return E_UNEXPECTED;}  
};


#ifndef SYNA_LINUX
class CDummySynDisplay : public ISynDisplay
{
public:
  CDummySynDisplay(){}
  ~CDummySynDisplay(){}

  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
    REFIID riid, void  **ppvObject){return E_UNEXPECTED;}

  virtual ULONG STDMETHODCALLTYPE AddRef( void){return 1;}

  virtual ULONG STDMETHODCALLTYPE Release( void){return 1;}

  virtual HRESULT STDMETHODCALLTYPE GetProperty(
    LONG lSpecifier,
    LONG *pValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetProperty(
    LONG lSpecifier,
    LONG lValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE PixelToTouch(
    LONG PixelX,
    LONG PixelY,
    LONG *pTouchX,
    LONG *pTouchY){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE TouchToPixel(
    LONG TouchX,
    LONG TouchY,
    LONG *pPixelX,
    LONG *pPixelY){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetDC(
    HDC *pHDC){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE FlushDC(
    LONG lFlags){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Acquire(
    LONG lDisplayAcquisitionMethod){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Unacquire( void){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Select(
    LONG lDeviceHandle){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetEventNotification(
    HANDLE hEvent){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetEventParameter(
    LONG *lParameter){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetSynchronousNotification(
    _ISynDisplayEvents *pCallbackInstance){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetStringProperty(
    LONG lSpecifier,
    unsigned char *pBuffer,
    LONG *ulBufLen){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetBackgroundImage(
    HBITMAP hBmp){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE CloneBackgroundImage(
    HBITMAP *pHBmp){return E_UNEXPECTED;}
};
#endif


class CDummySynPacket : public ISynPacket
{
public:
  CDummySynPacket(){}
  ~CDummySynPacket(){}

  virtual HRESULT STDMETHODCALLTYPE QueryInterface(
    REFIID riid, void  **ppvObject){return E_UNEXPECTED;}

  virtual ULONG STDMETHODCALLTYPE AddRef( void){return 1;}

  virtual ULONG STDMETHODCALLTYPE Release( void){return 1;}

  virtual HRESULT STDMETHODCALLTYPE GetProperty(
    LONG lSpecifier,
    LONG *pValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetProperty(
    LONG lSpecifier,
    LONG lValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetStringProperty(
    LONG lSpecifier,
    unsigned char *pBuffer,
    LONG *ulBufLen){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Copy(
    ISynPacket *pFrom){return E_UNEXPECTED;}

};

class CDummySynGroup : public ISynGroup
{
public:
  CDummySynGroup(){}
  ~CDummySynGroup(){}

  virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
    REFIID riid, void  **ppvObject){return E_UNEXPECTED;}

  virtual ULONG STDMETHODCALLTYPE AddRef( void){return 1;}

  virtual ULONG STDMETHODCALLTYPE Release( void){return 1;}

  virtual HRESULT STDMETHODCALLTYPE GetProperty( 
    LONG lSpecifier,
    LONG *pValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetProperty( 
    LONG lSpecifier,
    LONG lValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetPropertyByIndex( 
    LONG lSpecifier,
    LONG lIndex,
    LONG *pValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetPropertyByIndex( 
    LONG lSpecifier,
    LONG lIndex,
    LONG lValue){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetPacketByIndex( 
    LONG lIndex,
    ISynPacket *pPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE SetPacketByIndex( 
    LONG lIndex,
    ISynPacket *pPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE GetPacketPointer( 
    LONG lIndex,
    ISynPacket **ppPacket){return E_UNEXPECTED;}

  virtual HRESULT STDMETHODCALLTYPE Copy( 
    ISynGroup *pFrom){return E_UNEXPECTED;}
};

class SynAPI :
  public SynWrapEvents<SynAPI, __ISynAPI, _ISynAPIEvents>
{
public:
  SynAPI() :
    SynWrapEvents<SynAPI, __ISynAPI, _ISynAPIEvents>(SYNCOM_SYNAPI) { }

  SynAPI(__ISynAPI *pInterface) :
    SynWrapEvents<SynAPI, __ISynAPI, _ISynAPIEvents>(pInterface) { }


  HRESULT STDMETHODCALLTYPE OnSynAPINotify(LONG /* lReason */) { return 0; }


  LONG FindDevice(enum SynConnectionType eConnectionType,
    enum SynDeviceType eDeviceType, LONG lStart)
  {
    if (m_pInternal && m_pInternal->FindDevice(eConnectionType, eDeviceType, &lStart) == S_OK) {
      return lStart;
    }
    return -1;
  }

#ifndef SYNA_LINUX
  operator ISynAPI *() { return m_pInternal? m_pInternal : &m_dummyInterface;}
  ISynAPI *operator->() { return m_pInternal? m_pInternal : &m_dummyInterface;}

private:
  CDummySynAPI m_dummyInterface;
#endif
};

class SynDevice :
  public SynWrapEvents<SynDevice, __ISynDevice, _ISynDeviceEvents>
#ifndef SYNA_LINUX
  , public _ISynGestureActionEvents
#endif
{

public:
  SynDevice() :
    SynWrapEvents<SynDevice, __ISynDevice, _ISynDeviceEvents>(SYNCOM_POINTINGDEVICE)
  {
    PerformInit();
  }

  SynDevice(__ISynDevice *pInterface) :
    SynWrapEvents<SynDevice, __ISynDevice, _ISynDeviceEvents>(pInterface)
  {
    PerformInit();
  }

  ~SynDevice()
  {
    PerformUninit();
  }

  LONG GetLongPropertyDefault(LONG lSpecifier)
  {
    LONG lProperty = 0;

    if (m_pInternal)
      m_pInternal->GetPropertyDefault(lSpecifier, &lProperty);
    return lProperty;
  }

  HRESULT STDMETHODCALLTYPE OnSynDevicePacket(LONG /* lSequence */) { return 0; }

  bool IsTouchPad() {
    return (SE_DeviceTouchPad == GetLongProperty(SP_DeviceType));
  }

  bool IsStyk() {
    return (SE_DeviceStyk == GetLongProperty(SP_DeviceType));
  }

  bool IsIBMCompatibleStick() {
    return (SE_DeviceIBMCompatibleStick == GetLongProperty(SP_DeviceType));
  }

  bool IsStykOrIBMCompatibleStick() {
    return (IsStyk() || IsIBMCompatibleStick());
  }

  bool IscPad() {
    return IsDisplayPresent();
  }

  bool IsDisplayPresent() {
    return IsTouchPad() &&
      !!(GetLongProperty(SP_DisplayFlags) & SF_DisplayPresent);
  }

  bool IsRGBControlBar() {
    return (SE_DeviceRGBControlBar == GetLongProperty(SP_DeviceType));
  }

  bool IsStdControlBar() {
    return (SE_DeviceControlBar == GetLongProperty(SP_DeviceType));
  }

  bool IsControlBar() {
    return (IsStdControlBar() || IsRGBControlBar());
  }

  bool IsTouchBar() {
    return (SE_DeviceTouchBar == GetLongProperty(SP_DeviceType));
  }

  bool IsStandardMouse() {
    return (SE_DeviceMouse == GetLongProperty(SP_DeviceType));
  }

  bool IsWheelMouse() {
    return (SE_DeviceWheelMouse == GetLongProperty(SP_DeviceType));
  }

  bool IsFiveButtonWheelMouse() {
    return (SE_DeviceFiveButtonWheelMouse == GetLongProperty(SP_DeviceType));
  }

  bool IsMouse() {
    return (IsStandardMouse() || IsWheelMouse() || IsFiveButtonWheelMouse());
  }

  bool IsUSBDevice() {
    return (SE_ConnectionUSB == GetLongProperty(SP_ConnectionType));
  }

  bool IsPS2Device() {
    return (SE_ConnectionPS2 == GetLongProperty(SP_ConnectionType));
  }

  bool HasACM2() const {
    return !!GetLongProperty(SP_HasACM2);
  }

  LONG KbGetPositionKeyCount() {
    LONG ret = 0;
    if (m_pInternal)
    {
      m_pInternal->GetProperty(SP_KBPositionKeyCount, &ret);
    }
    return ret;
  }

  LONG KbPositionKeyScanCodeByIndex(LONG index) {
    LONG ret = index;
    if (m_pInternal)
    {
      if (S_OK != m_pInternal->GetProperty(SP_KBPositionKeyByIndex, &ret))
      {
        ret = 0;
      }
    }
    return ret;
  }

  LONG GetKbPositionKeyDelta(LONG scancode) {
    LONG ret = scancode;
    if (m_pInternal)
    {
      if (S_OK != m_pInternal->GetProperty(SP_KBPositionKeyDelta, &ret))
      {
        ret = 0;
      }
    }
    return ret;
  }

  BOOL SetKbPositionKeyDelta(LONG scancode, LONG delta) {
    LONG lValue = (scancode << 16) | (delta);
    if (m_pInternal)
    {
      return (S_OK == m_pInternal->SetProperty(SP_KBPositionKeyDelta, lValue));
    }
    return FALSE;
  }

  LONG GetKbPositionKeyResolution(LONG scancode) {
    LONG ret = scancode;
    if (m_pInternal)
    {
      if (S_OK != m_pInternal->GetProperty(SP_KBPositionKeyResolution, &ret))
      {
        ret = 0;
      }
    }
    return ret;
  }

protected:

  void PerformInit()
  {
    m_RefCount = 0;
#ifndef SYNA_LINUX
    m_pISynDevice2 = NULL;
#endif
  }

  void PerformUninit()
  {
#ifndef SYNA_LINUX
    if (m_pISynDevice2) {
      m_pISynDevice2->Release();
      m_pISynDevice2 = NULL;
    }
#endif
  }

#ifndef SYNA_LINUX

public:
  BOOL SetGestureActionNotification(DWORD dwProcID, _ISynGestureActionEvents *pConnection,
    LONG lValue, LONG lValueEx)
  {    
    EnsureISynDevice2();

    if(!m_pISynDevice2)
      return FALSE;

    BOOL bResult = (m_pISynDevice2->SetGestureActionNotification(dwProcID, pConnection, lValue, lValueEx)
      == SYN_OK);

    return bResult;
  }

   virtual HRESULT STDMETHODCALLTYPE OnSynGestureActionEvent(LONG lType, LONG lSize, UCHAR *ucData)
  {
    UNREFERENCED_PARAMETER(lType);
    UNREFERENCED_PARAMETER(lSize);
    UNREFERENCED_PARAMETER(ucData);
    return S_OK;
  }

  virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid,  void **ppvObject)
  {
    if (ppvObject == NULL || !m_pInternal)
      return E_POINTER;
    *ppvObject = NULL;
    HRESULT hr = E_NOINTERFACE;
    if (IsEqualIID(riid,IID_IUnknown)) {
      *ppvObject = (IUnknown *)(this);
      AddRef();
      hr = S_OK;
    }
    return hr;
  }

  virtual ULONG STDMETHODCALLTYPE AddRef()
  {
    return InterlockedIncrement((LONG *)&m_RefCount);
  }

  virtual ULONG STDMETHODCALLTYPE Release()
  {
    m_RefCount = InterlockedDecrement((LONG *)&m_RefCount);
    if (m_RefCount == 0)
      delete this;
    return m_RefCount;
  }

  operator ISynDevice *() { return m_pInternal? m_pInternal : &m_dummyInterface;}

  ISynDevice *operator->() { return m_pInternal? m_pInternal : &m_dummyInterface;}

private:

  HRESULT EnsureISynDevice2()
  {
    if (!m_pInternal)
      return E_FAIL;

    if (m_pISynDevice2)
      return S_OK;
    
    ULONG_PTR lpCookie = 0; 
    HANDLE hActCtx = INVALID_HANDLE_VALUE;    
    SetupContextForSynComLocal(hActCtx, lpCookie);

    HRESULT hr = S_OK;   
    hr = CoCreateInstance(__uuidof(SynDevice2), NULL, CLSCTX_SERVER,
      __uuidof(ISynDevice2), (void**)&m_pISynDevice2);
    
    CleanupContextForSynComLocal(hActCtx, lpCookie);

    if(FAILED(hr))
      goto CLEANUP;

    LONG lHandle = 0;
    hr = m_pInternal->GetProperty(SP_Handle, &lHandle);
    if (FAILED(hr))
      goto CLEANUP;

    hr = m_pISynDevice2->Select(lHandle);
    if (FAILED(hr))
      goto CLEANUP;

    return S_OK;

CLEANUP:
    if (m_pISynDevice2) {
      m_pISynDevice2->Release();
      m_pISynDevice2 = NULL;
    }
    return hr;
  }

  ISynDevice2* m_pISynDevice2;
  CDummySynDevice m_dummyInterface;
#endif
  ULONG m_RefCount;
};

#ifdef SYNA_LINUX
class SynDisplay;
#else
class SynDisplay :
  public SynWrapEvents<SynDisplay, ISynDisplay, _ISynDisplayEvents>
{
public:
  SynDisplay() :
    SynWrapEvents<SynDisplay, ISynDisplay, _ISynDisplayEvents>(SYNCOM_SYNDISPLAY) { }

  SynDisplay(ISynDisplay *pInterface) :
    SynWrapEvents<SynDisplay, ISynDisplay, _ISynDisplayEvents>(pInterface) { }


  HRESULT STDMETHODCALLTYPE OnSynDisplayMessage(LONG /* lMessage */) { return 0; }

  LONG PixelX(LONG lTouchX)
  {
    LONG lPixelX = 0, lPixelY = 0;
    if (m_pInternal)
    {
      m_pInternal->TouchToPixel(lTouchX, 0, &lPixelX, &lPixelY);
    }

    return lPixelX;
  }

  LONG PixelY(LONG lTouchY)
  {
    LONG lPixelX = 0, lPixelY = 0;
    if (m_pInternal)
    {
      m_pInternal->TouchToPixel(0, lTouchY, &lPixelX, &lPixelY);
    }

    return lPixelY;
  }

  LONG TouchX(LONG lPixelX)
  {
    LONG lTouchX = 0, lTouchY = 0;
    if (m_pInternal)
    {
      m_pInternal->PixelToTouch(lPixelX, 0, &lTouchX, &lTouchY);
    }

    return lTouchX;
  }

  LONG TouchY(LONG lPixelY)
  {
    LONG lTouchX = 0, lTouchY = 0;
    if (m_pInternal)
    {
      m_pInternal->PixelToTouch(0, lPixelY, &lTouchX, &lTouchY);
    }

    return lTouchY;
  }

  operator ISynDisplay *() { return m_pInternal? m_pInternal : &m_dummyInterface;}

  ISynDisplay *operator->() { return m_pInternal? m_pInternal : &m_dummyInterface;}

private:
  CDummySynDisplay m_dummyInterface;
};
#endif

class SynPacket :
  public SynWrap<SynPacket, __ISynPacket>
{
public:
  SynPacket() : SynWrap<SynPacket, __ISynPacket>(SYNCOM_SYNPACKET) { }

  SynPacket(__ISynPacket *pPacket) : SynWrap<SynPacket, __ISynPacket>(pPacket) { }

  LONG AssociatedDeviceHandle() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_AssociatedDeviceHandle, &lProperty);
    return lProperty;
  }

  LONG SequenceNumber() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_SequenceNumber, &lProperty);
    return lProperty;
  }

  LONG GroupNumber() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_PacketGroupNumber, &lProperty);
    return lProperty;
  }

  LONG SubType() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_SubType, &lProperty);
    return lProperty;
  }

  ULONG TimeStamp() const
  {
    if(!m_pInternal)
      return 0;

    ULONG ulProperty;
    m_pInternal->GetProperty(SP_TimeStamp, (LONG *) &ulProperty);
    return ulProperty;
  }

  LONG W() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_W, &lProperty);
    return lProperty;
  }

  LONG X() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_X, &lProperty);
    return lProperty;
  }

  LONG Y() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_Y, &lProperty);
    return lProperty;
  }

  LONG Z() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_Z, &lProperty);
    return lProperty;
  }

  LONG XRaw() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_XRaw, &lProperty);
    return lProperty;
  }

  LONG ZXRaw() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ZXRaw, &lProperty);
    return lProperty;
  }

  LONG YRaw() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_YRaw, &lProperty);
    return lProperty;
  }

  LONG ZRaw() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ZRaw, &lProperty);
    return lProperty;
  }

  LONG ZYRaw() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ZYRaw, &lProperty);
    return lProperty;
  }

  LONG XDelta() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_XDelta, &lProperty);
    return lProperty;
  }

  LONG YDelta() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_YDelta, &lProperty);
    return lProperty;
  }

  LONG ZDelta() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ZDelta, &lProperty);
    return lProperty;
  }

  LONG XMickeys() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_XMickeys, &lProperty);
    return lProperty;
  }

  LONG YMickeys() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_YMickeys, &lProperty);
    return lProperty;
  }

  LONG WheelDelta() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_WheelDelta, &lProperty);
    return lProperty;
  }

  LONG ExtendedState() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ExtendedState, &lProperty);
    return lProperty;
  }

  LONG ExtendedState2() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ExtendedState2, &lProperty);
    return lProperty;
  }

  LONG ZForce() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ZForce, &lProperty);
    return lProperty;
  }

  LONG ZImage() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ZImage, &lProperty);
    return lProperty;
  }

  LONG ContactType() const 
  {
    if(!m_pInternal)
      return SACT_Non_Finger_Object;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ContactType, &lProperty);
    return lProperty;
  }

  LONG Confidence() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_Confidence, &lProperty);
    return lProperty;
  }

  LONG KbKeyInfo() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_KBPacketKeyInfo, &lProperty);
    return lProperty;
  }

  LONG KbFingerInfo() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_KBPacketFingerInfo, &lProperty);
    return lProperty;
  }

  LONG FingerState() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_FingerState, &lProperty);
    return lProperty;
  }

  // This function is only called by ForcePacket to convert SynCOM button and finger states
  // into TP_PACKET_xxx
  LONG ConvertSFPacketStateToTPPacketState() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty = 0;
    LONG lState = 0;
    // Get finger state
    m_pInternal->GetProperty(SP_FingerState, &lProperty);
    // Map finger state
    lState = lProperty & (SF_FingerPresent | SF_FingerPrimGest | SF_FingerSecGest |
      SF_FingerStylus);
    // Get button state
    lProperty = 0;
    m_pInternal->GetProperty(SP_ButtonState, &lProperty);
    // Map L,R,M buttons
    lState |= (lProperty & (SF_ButtonLeft | SF_ButtonRight | SF_ButtonMiddle));
    // Map SF_ButtonUp&SF_ButtonDown to TP_PacketState_UpSw&TP_PacketState_DownSw
    lState |= ((lProperty & (SF_ButtonUp | SF_ButtonDown)) << 24);
    return lState;
  }

  LONG FingerIndex() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty = 0;  // if GetProperty() fails defaults to zero
    m_pInternal->GetProperty(SP_FingerIndex, &lProperty);
    return lProperty;
  }

  LONG FilterIndex() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty = 0;  // if GetProperty() fails defaults to zero
    m_pInternal->GetProperty(SP_FilterIndex, &lProperty);
    return lProperty;
  }

  LONG ExtraFingerState() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_ExtraFingerState, &lProperty);
    return lProperty;
  }

  LONG NumCurrentFingers() const
  {
    return (ExtraFingerState() & SF_CurrentFingerCountMask) >> SF_CurrentFingerCountBit;
  }

  LONG NumStrokeFingers() const
  {
    return (ExtraFingerState() & SF_StrokeFingerCountMask) >> SF_StrokeFingerCountBit;
  }

  LONG PrimaryFingerContactID() const
  {
    return (((DWORD) ExtraFingerState() & SF_PrimaryFingerContactIDMask) >>
      SF_PrimaryFingerContactIDBit);
  }

  LONG SecondaryFingerContactID() const
  {
    return (((DWORD) ExtraFingerState() & SF_SecondaryFingerContactIDMask) >>
      SF_SecondaryFingerContactIDBit);
  }

  LONG ButtonState() const
  {
    if(!m_pInternal)
      return 0;
    LONG lProperty;
    m_pInternal->GetProperty(SP_ButtonState, &lProperty);
    return lProperty;
  }

  bool IsLeftButton() const {
    return (ButtonState() & SF_ButtonLeft) != 0;
  }

  bool IsRightButton() const {
    return (ButtonState() & SF_ButtonRight) != 0;
  }

  bool IsMiddleButton() const {
    return (ButtonState() & SF_ButtonMiddle) != 0;
  }

  bool IsTap() const {
    return (FingerState() & SF_FingerTap) != 0;
  }

  bool IsMotion() const {
    return (FingerState() & SF_FingerMotion) != 0;
  }

  bool IsFinger() const {
    return (FingerState() & SF_FingerPresent) != 0;
  }

  bool IsTouch() const {
    return (FingerState() & SF_FingerTouch) != 0;
  }

  bool IsScrollFinger() const {
    return (ExtendedState() & SF_StateScrollFinger) != 0;
  }

  bool IsMomentum() const {
    return (ExtendedState() & SF_Momentum) != 0;
  }

  bool IsNearKeyPress() const {
    return (ExtendedState() & SF_NearKeyPress) != 0;
  }

  bool IsNearHighPalmW() const {
    return ((ExtendedState() & SF_NearHighPalmW) != 0) && (ContactType() != SACT_Non_Finger_Object);
  }

  bool IsAnyFinger() const {
    return (IsFinger() || IsScrollFinger());
  }

  bool IsAnyButton() const {
    return (!!ButtonState() || !!(FingerState() & SF_FingerAsButton));
  }

  void Attach(__ISynPacket* pPkt) {
    if (m_pInternal) {
      m_pInternal->Release();
    }   
    m_pInternal = pPkt;
    if (m_pInternal) {
      m_pInternal->AddRef();
    }
  }

  bool IsAnyPalm() const {
    SynACMContactType c = static_cast<SynACMContactType>(ContactType());
    return c == SACT_Palm_13 || c == SACT_Palm_14 || c == SACT_Palm_15;
  }

#ifndef SYNA_LINUX
  operator ISynPacket *() { return m_pInternal? m_pInternal : &m_dummyInterface;}

  ISynPacket *operator->() { return m_pInternal? m_pInternal : &m_dummyInterface;}

private:
  CDummySynPacket m_dummyInterface;
#endif
};


class SynGroup :
  public SynWrap<SynGroup, __ISynGroup>
{
public:
  SynGroup() : SynWrap<SynGroup, __ISynGroup>(SYNCOM_SYNGROUP) { Init(); }

  SynGroup(__ISynGroup *pGroup) : SynWrap<SynGroup, __ISynGroup>(pGroup) { Init(); }

  ~SynGroup()
  {
    for (UINT ui = 0 ; ui <= SE_MaxReportedFingers; ui++) {
      delete m_pPackets[ui];
    }
  }

protected:
  // Init - Initalize the object. Used by both constructors above.
  void Init()
  {
    // Create array of SynPacket wrapper classes for each finger.
    for (UINT ui = 0 ; ui <= SE_MaxReportedFingers; ui++) {
      // Attach this wrapper's SynPackets to the internal ISynGroup's ISynPackets, if available.
      __ISynPacket* pTmp = NULL;
      if (m_pInternal) {
        // Note: This will result in an AddRef to pTmp.
        // Redundant cast needed for Linux build.
        m_pInternal->GetPacketPointer(ui, (ISynPacket**)&pTmp); 
      }
      if (pTmp) {
        // Note: This will also result in an AddRef to pTmp.
        m_pPackets[ui] = new SynPacket(pTmp);
        // This Releases the AddRef done in GetPacketPointer above.
        // The ISynPacket object that pTmp points to will still have 2 ref counts: One that is held
        // by the m_pInternal group object and one that is held by the SynPacket wrapper that is
        // pointed to by m_pPackets[ui]. Both of these will be released when this group wrapper is 
        // destroyed.
        pTmp->Release();
      } else {
        // This should never occur since m_pInternal should never be NULL and GetPacketPointer 
        // should never return NULL, but just in case we create an empty SynPacket wrapper.
        m_pPackets[ui] = new SynPacket();
      }
    }
  }

public:
  LONG DeviceHandle() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_DeviceHandle, &lProperty);
    return lProperty;
  }

  LONG GroupNumber() const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetProperty(SP_GroupNumber, &lProperty);
    return lProperty;
  }

  LONG ForceRaw(LONG lIndex) const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetPropertyByIndex(SP_ForceRaw, lIndex, &lProperty);
    return lProperty;
  }


  LONG Force(LONG lIndex) const
  {
    if(!m_pInternal)
      return 0;

    LONG lProperty;
    m_pInternal->GetPropertyByIndex(SP_Force, lIndex, &lProperty);
    return lProperty;
  }


  BOOL Packet(LONG lIndex, SynPacket& pkt) {
    if (lIndex <= SE_MaxReportedFingers) {
      pkt->Copy((ISynPacket*)*m_pPackets[lIndex]);
      return TRUE;
    }
    return FALSE;
  }

  SynPacket* CreatePacket(LONG lIndex) {
    SynPacket* pPkt = NULL;
    if (lIndex <= SE_MaxReportedFingers) {
      pPkt = new SynPacket((__ISynPacket*)*m_pPackets[lIndex]);
    }
    return pPkt;
  }

  SynPacket* GetPacketPointer(LONG lIndex) {
    if (lIndex <= SE_MaxReportedFingers) {
      return m_pPackets[lIndex];
    } else {
      return NULL;
    }
  }

  BOOL SetPacket(LONG lIndex, SynPacket& pkt) {
    if (lIndex <= SE_MaxReportedFingers) {
      (*m_pPackets[lIndex])->Copy(pkt);
      return TRUE;
    }
    return FALSE;
  }

  void Copy(SynGroup* pGroup) {
    // Copy underlying ISynGroup object.
    // This wrapper's array of SynPackets are already attached to the underlying ISynGroup's
    // array of ISynPackets, so we don't need to copy those seperately.
    // Note that the cast operator casts from this object, not from a pointer to this object.
    ((ISynGroup*)*this)->Copy(*pGroup);
  }

#ifndef SYNA_LINUX
  operator ISynGroup *() { return m_pInternal? m_pInternal : &m_dummyInterface;}

  ISynGroup *operator->() { return m_pInternal? m_pInternal : &m_dummyInterface;}

private:
  CDummySynGroup m_dummyInterface;
#endif

protected:
  SynPacket* m_pPackets[SE_MaxReportedFingers + 1];
};

#endif
