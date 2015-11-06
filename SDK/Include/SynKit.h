//===========================================================================
// Copyright (c) 1996-2007 Synaptics Incorporated. All rights reserved.
//
// RCS Header - Do not delete or modify.
//
// $RCSfile: SynKit.h,v $
// $Source: /cvs/software/Driver/SynCom/SynCom/SynKit.h,v $
//===========================================================================

// Public header file for access to the Synaptics COM API/Toolkit.

#ifndef __SYNKIT_H
#define __SYNKIT_H

#ifdef SYNA_LINUX
#include "Windows.h"
#include "Linux/SynCom.h"
#include "SynError.h"
#include "synwraps.h"
#else

#if !defined(SYN_INCLUDE_NO_CONTROLS) && (!defined(_MFC_VER) || defined(SYN_INCLUDE_CONTROLS))
// Include controls by default only for non-MFC programs.
// MFC programs likely will import the type library and add controls to dialogs which will
// automatically create MFC wrapper classes for the  controls.
// If controls are included, inlcude them first as the enumerations are in the type library.
#ifdef THINTOUCH  // building SynComTT
#include "SynCtrlTT.h"
#else
#include "SynCtrl.h"
#endif // #ifdef THINTOUCH
#endif 

#ifdef THINTOUCH  
#include "SynComTT.h"
#else
#include "SynCom.h"
#endif // #ifdef THINTOUCH

#ifndef SYNA_LINUX
#ifndef SKIP_INITGUID
#include <initguid.h>
#endif
#ifdef THINTOUCH
#include "SynCom2TT.h"
#else
#include "SynCom2.h"
#endif // #ifdef THINTOUCH
#endif // #ifndef SYNA_LINUX
#include "SynError.h"
#include "SynWraps.h"

STDAPI SynCreateAPI(ISynAPI **ppAPI);

// Declare GUIDs here so that controls can be imported into MFC even if
// SYN_INCLUDE_NO_CONTROLS has been defined. 
// Define SYN_INCLUDE_NO_CONTROLS to allow classwizard to reuse the ISynXXX 
// names when using MFC to import the synctrl.dll class library.
#ifdef THINTOUCH
class DECLSPEC_UUID("9155D529-912A-4AEC-8353-3A8B4C5BF888") SynAPICtrl;
class DECLSPEC_UUID("68292901-9D8F-4A14-9F42-7AC5E5BFF3F8") SynPacketCtrl;
class DECLSPEC_UUID("64D186BD-A6CB-4482-A3CF-F294FCE0B8AB") SynGroupCtrl;
class DECLSPEC_UUID("D206BF5E-8359-4A14-9917-455CA7ADF346") SynDeviceCtrl;
#else
class DECLSPEC_UUID("F418EBA0-6A10-4482-AC2B-2D10C807073A") SynAPICtrl;
class DECLSPEC_UUID("a220a2df-406f-4d68-9b62-995669ae0c92") SynPacketCtrl;
class DECLSPEC_UUID("856BEFCE-E5DD-47bf-B274-B17FA9DFE7D2") SynGroupCtrl;
class DECLSPEC_UUID("2060435E-AB52-49E1-A2EA-5D31645887CF") SynDeviceCtrl;
#endif // THINTOUCH
#endif // SYNA_LINUX

#endif 
