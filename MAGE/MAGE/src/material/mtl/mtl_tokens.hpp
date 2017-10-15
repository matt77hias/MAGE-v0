#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_MTL_COMMENT_CHAR               '#'
#define MAGE_MTL_TOKEN_MATERIAL_DECLARATION "newmtl"

// RGBAs
#define MAGE_MTL_TOKEN_BASE_COLOR           "base_color"

// Scalars
#define MAGE_MTL_TOKEN_ROUGHNESS            "roughness"
#define MAGE_MTL_TOKEN_METALNESS            "metalness"

// Textures
#define MAGE_MTL_TOKEN_BASE_COLOR_TEXTURE   "texture_base_color"
#define MAGE_MTL_TOKEN_MATERIAL_TEXTURE     "texture_material"
#define MAGE_MTL_TOKEN_NORMAL_TEXTURE       "texture_normal"

// Flags
#define MAGE_MTL_TOKEN_TRANSPARENT          "transparent"
#define MAGE_MTL_TOKEN_OPAQUE               "opaque"
#define MAGE_MTL_TOKEN_EMISSIVE             "emissive"

#pragma endregion