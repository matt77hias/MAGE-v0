//-----------------------------------------------------------------------------
// COMPILE-TIME OPTIONS FOR DEAR IMGUI
// Runtime options (clipboard callbacks, enabling various features, etc.) can generally be set via the ImGuiIO structure.
// You can use ImGui::SetAllocatorFunctions() before calling ImGui::CreateContext() to rewire memory allocation functions.
//-----------------------------------------------------------------------------
// A) You may edit imconfig.h (and not overwrite it when updating imgui, or maintain a patch/branch with your modifications to imconfig.h)
// B) or add configuration directives in your own file and compile with #define IMGUI_USER_CONFIG "myfilename.h" 
// C) Many compile-time options have an effect on data structures. They need defined consistently _everywhere_ imgui.h is included, 
// not only for the imgui*.cpp compilation units. Defining those options in imconfig.h will ensure they correctly get used everywhere.
//-----------------------------------------------------------------------------
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

#define IM_ASSERT(expr)  Assert(expr)

//---- Define attributes of all API symbols declarations, e.g. for DLL under Windows.
//#define IMGUI_API __declspec( dllexport )
//#define IMGUI_API __declspec( dllimport )

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS

//---- Don't implement default handlers for Windows (so as not to link with certain functions)
//#define IMGUI_DISABLE_WIN32_DEFAULT_CLIPBOARD_FUNCTIONS   // Don't use and link with OpenClipboard/GetClipboardData/CloseClipboard etc.
//#define IMGUI_DISABLE_WIN32_DEFAULT_IME_FUNCTIONS         // Don't use and link with ImmGetContext/ImmSetCompositionWindow.

//---- Don't implement demo windows functionality (ShowDemoWindow()/ShowStyleEditor()/ShowUserGuide() methods will be empty)
//---- It is very strongly recommended to NOT disable the demo windows during development. Please read the comments in imgui_demo.cpp.
//#define IMGUI_DISABLE_DEMO_WINDOWS

//---- Don't implement ImFormatString(), ImFormatStringV() so you can reimplement them yourself.
//#define IMGUI_DISABLE_FORMAT_STRING_FUNCTIONS

//---- Include imgui_user.hpp at the end of imgui.hpp as a convenience
//#define IMGUI_INCLUDE_IMGUI_USER_HPP

//---- Pack colors to BGRA8 instead of RGBA8 (if you needed to convert from one to another anyway)
//#define IMGUI_USE_BGRA_PACKED_COLOR

//---- Avoid multiple STB libraries implementations, or redefine path/filenames to prioritize another version
// By default the embedded implementations are declared static and not available outside of imgui cpp files.
//#define IMGUI_STB_TRUETYPE_FILENAME   "my_folder/stb_truetype.h"
//#define IMGUI_STB_RECT_PACK_FILENAME  "my_folder/stb_rect_pack.h"
//#define IMGUI_DISABLE_STB_TRUETYPE_IMPLEMENTATION
//#define IMGUI_DISABLE_STB_RECT_PACK_IMPLEMENTATION

#define IM_VEC2_CLASS_EXTRA \
        ImVec2(const mage::F32x2& f) noexcept : x(f[0]), y(f[1]) {} \
        operator mage::F32x2() const noexcept { return mage::F32x2(x, y); }

#define IM_VEC4_CLASS_EXTRA \
        ImVec4(const mage::F32x4& f) noexcept : x(f[0]), y(f[1]), z(f[2]), w(f[3]) {} \
        operator mage::F32x4() const noexcept { return mage::F32x4(x, y, z, w); }

//---- Use 32-bit vertex indices (default is 16-bit) to allow meshes with more than 64K vertices. Render function needs to support it.
//#define ImDrawIdx unsigned int

//---- Tip: You can add extra functions within the ImGui:: namespace, here or in your own headers files.
/*
namespace ImGui
{
    void MyFunction(const char* name, const MyMatrix44& v);
}
*/