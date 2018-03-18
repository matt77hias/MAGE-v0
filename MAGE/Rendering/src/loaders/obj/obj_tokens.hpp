#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	constexpr const char    g_obj_token_comment          = '#';
	constexpr const_zstring g_obj_token_vertex           = "v";
	constexpr const_zstring g_obj_token_texture          = "vt";
	constexpr const_zstring g_obj_token_normal           = "vn";
	constexpr const_zstring g_obj_token_face             = "f";
	constexpr const_zstring g_obj_token_material_library = "mtllib";
	constexpr const_zstring g_obj_token_material_use     = "usemtl";
	constexpr const_zstring g_obj_token_group            = "g";
	constexpr const_zstring g_obj_token_object           = "o";
	constexpr const_zstring g_obj_token_smoothing_group  = "s";
}