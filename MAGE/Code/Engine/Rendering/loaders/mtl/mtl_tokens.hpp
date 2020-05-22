#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	constexpr const char    g_mtl_token_comment              = '#';
	constexpr const_zstring g_mtl_token_material_declaration = "newmtl";

	// sRGBA spectra
	constexpr const_zstring g_mtl_token_base_color           = "base_color";

	// Scalars
	constexpr const_zstring g_mtl_token_roughness            = "roughness";
	constexpr const_zstring g_mtl_token_metalness            = "metalness";
	constexpr const_zstring g_mtl_token_radiance             = "radiance";

	// Textures
	constexpr const_zstring g_mtl_token_base_color_texture   = "texture_base_color";
	constexpr const_zstring g_mtl_token_material_texture     = "texture_material";
	constexpr const_zstring g_mtl_token_normal_texture       = "texture_normal";

	// Flags
	constexpr const_zstring g_mtl_token_transparent          = "transparent";
	constexpr const_zstring g_mtl_token_opaque               = "opaque";
}