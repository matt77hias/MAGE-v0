#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\vector_types.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define IM_ASSERT(expr)  Assert(expr)

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS

//---- Define attributes of all API symbols declarations, e.g. for DLL under Windows.
//#define IMGUI_API __declspec( dllexport )
//#define IMGUI_API __declspec( dllimport )

//---- Include imgui_user.h at the end of imgui.h
//#define IMGUI_INCLUDE_IMGUI_USER_H

//---- Don't implement default handlers for Windows (so as not to link with OpenClipboard() and others Win32 functions)
//#define IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS
//#define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS

//---- Don't implement test window functionality (ShowTestWindow()/ShowStyleEditor()/ShowUserGuide() methods will be empty)
//---- It is very strongly recommended to NOT disable the test windows. Please read the comment at the top of imgui_demo.cpp to learn why.
//#define IMGUI_DISABLE_TEST_WINDOWS

//---- Don't implement ImFormatString(), ImFormatStringV() so you can reimplement them yourself.
//#define IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS

//---- Pack colors to BGRA instead of RGBA (remove need to post process vertex buffer in back ends)
//#define IMGUI_USE_BGRA_PACKED_COLOR

//---- Implement STB libraries in a namespace to avoid linkage conflicts
//#define IMGUI_STB_NAMESPACE     ImGuiStb

#define IM_VEC2_CLASS_EXTRA \
        ImVec2(const mage::F32x2 &f) { x = f.m_x; y = f.m_y; } \
        operator mage::F32x2() const noexcept { return mage::F32x2(x, y); }

#define IM_VEC4_CLASS_EXTRA \
        ImVec4(const mage::F32x4 &f) { x = f.m_x; y = f.m_y; z = f.m_z; w = f.m_w; } \
        operator mage::F32x4() const noexcept { return mage::F32x4(x, y, z, w); }

//---- Use 32-bit vertex indices (instead of default: 16-bit) to allow meshes with more than 64K vertices
//#define ImDrawIdx unsigned int

#pragma endregion