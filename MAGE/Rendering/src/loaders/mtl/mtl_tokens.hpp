#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	constexpr const char  g_mtl_token_comment              = '#';
	constexpr const char *g_mtl_token_material_declaration = "newmtl";

	// RGBAs
	constexpr const char *g_mtl_token_base_color           = "base_color";

	// Scalars
	constexpr const char *g_mtl_token_roughness            = "roughness";
	constexpr const char *g_mtl_token_metalness            = "metalness";

	// Textures
	constexpr const char *g_mtl_token_base_color_texture   = "texture_base_color";
	constexpr const char *g_mtl_token_material_texture     = "texture_material";
	constexpr const char *g_mtl_token_normal_texture       = "texture_normal";

	// Flags
	constexpr const char *g_mtl_token_transparent          = "transparent";
	constexpr const char *g_mtl_token_opaque               = "opaque";
	constexpr const char *g_mtl_token_emissive             = "emissive";
}