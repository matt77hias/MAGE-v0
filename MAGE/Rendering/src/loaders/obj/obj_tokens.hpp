#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	constexpr const char  g_obj_token_comment          = '#';
	constexpr const char* g_obj_token_vertex           = "v";
	constexpr const char* g_obj_token_texture          = "vt";
	constexpr const char* g_obj_token_normal           = "vn";
	constexpr const char* g_obj_token_face             = "f";
	constexpr const char* g_obj_token_material_library = "mtllib";
	constexpr const char* g_obj_token_material_use     = "usemtl";
	constexpr const char* g_obj_token_group            = "g";
	constexpr const char* g_obj_token_object           = "o";
	constexpr const char* g_obj_token_smoothing_group  = "s";
}