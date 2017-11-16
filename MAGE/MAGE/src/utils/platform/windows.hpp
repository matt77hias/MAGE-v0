#pragma once

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

// Exclude APIs such as Cryptography, DDE, RPC, Shell, and Windows Sockets.
#define WIN32_LEAN_AND_MEAN

// Inhibit definitions: macros min(a,b) and max(a,b).
#define NOMINMAX

// Inhibit definitions: DrawText() and DT_*.
#define NODRAWTEXT

// Inhibit definitions: all GDI defines and routines.
#define NOGDI

// Inhibit definitions
#define NOBITMAP

// Inhibit definitions: typedef MSG and associated routines.
#define NOMCX

// Inhibit definitions: all Service Controller routines, SERVICE_ equates, etc.
#define NOSERVICE

// Inhibit definitions: help engine interface.
#define NOHELP

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <windows.h>

#pragma endregion