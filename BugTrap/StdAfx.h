/*
 * This is a part of the BugTrap package.
 * Copyright (c) 2005-2007 IntelleSoft.
 * All rights reserved.
 *
 * Description: Precomplied header file.
 * Author: Maksim Pyatkovskiy.
 *
 * This source code is only intended as a supplement to the
 * BugTrap package reference and related electronic documentation
 * provided with the product. See these sources for detailed
 * information regarding the BugTrap package.
 */

#pragma once

#ifndef WINVER		
#define WINVER 0x0501
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0501
#endif
#ifndef _WIN32_WINNT	
#define _WIN32_WINNT 0x0501
#endif	
#ifndef _WIN32_IE
#define _WIN32_IE 0x0501
#endif

//vs 2005 up
#if _MSC_VER >= 1400

//disables floods of depreciated warnings
#pragma warning(disable: 4996)

//fix crash in vs 2005 and vs 2008
#ifdef _DEBUG
#define _HAS_ITERATOR_DEBUGGING 0 
#endif

#ifndef _SECURE_ATL
#define _SECURE_ATL 0
#endif

#ifndef _SECURE_SCL
#define _SECURE_SCL 0
#endif

#endif

#ifdef _MANAGED
 #pragma unmanaged              // Compile all code as unmanaged by default
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <winsock2.h>
#include <shellapi.h>
#include <psapi.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdlib.h>
#include <psapi.h>
#include <tlhelp32.h>
#include <vdmdbg.h>
#include <dbghelp.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <mapi.h>
#include <lmcons.h>
#include <wininet.h>
#include <process.h>
#include <zmouse.h>
#include <limits.h>
#include "../=ZLIB/zip.h"


struct _IMAGELIST { }; // unresolved typeref token

//#define DEBUG_WITH_BOUNDSCHECKER

#ifdef DEBUG_WITH_BOUNDSCHECKER
 #include <crtdbg.h>
 #pragma warning (disable : 4702) // unreachable code
 #define DEBUG_NEW new
#else
 #include "LeakWatcher.h"
#endif

//#include <malloc.h>

#define countof(array) (sizeof(array) / sizeof((array)[0]))
/*
#ifdef _MANAGED
 #ifdef _DEBUG
  #pragma comment(lib, "zlibMSD.lib")
 #else
  #pragma comment(lib, "zlibMS.lib")
 #endif
#else
 #ifdef _DEBUG
  #pragma comment(lib, "zlibSD.lib")
 #else
  #pragma comment(lib, "zlibS.lib")
 #endif
#endif
*/