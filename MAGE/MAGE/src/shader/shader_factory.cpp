//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "mesh\vertex.hpp"

// AA
#include "shader\cso\aa\fxaa_CS.hpp"
#include "shader\cso\aa\msaa_2x_resolve_CS.hpp"
#include "shader\cso\aa\msaa_4x_resolve_CS.hpp"
#include "shader\cso\aa\msaa_8x_resolve_CS.hpp"
#include "shader\cso\aa\msaa_16x_resolve_CS.hpp"
#include "shader\cso\aa\msaa_32x_resolve_CS.hpp"
#include "shader\cso\aa\msaa_resolve_CS.hpp"
#include "shader\cso\aa\ssaa_2x_resolve_CS.hpp"
#include "shader\cso\aa\ssaa_3x_resolve_CS.hpp"
#include "shader\cso\aa\ssaa_4x_resolve_CS.hpp"
#include "shader\cso\aa\ssaa_resolve_CS.hpp"

// Deferred
#include "shader\cso\deferred\deferred_blinn_phong_CS.hpp"
#include "shader\cso\deferred\deferred_cook_torrance_CS.hpp"
#include "shader\cso\deferred\deferred_emissive_CS.hpp"
#include "shader\cso\deferred\deferred_frostbite_CS.hpp"
#include "shader\cso\deferred\deferred_lambertian_CS.hpp"
#include "shader\cso\deferred\deferred_ward_duer_CS.hpp"

// Depth
#include "shader\cso\depth\depth_VS.hpp"
#include "shader\cso\depth\depth_transparent_VS.hpp"
#include "shader\cso\depth\depth_transparent_PS.hpp"

// Forward
#include "shader\cso\forward\forward_blinn_phong_PS.hpp"
#include "shader\cso\forward\forward_cook_torrance_PS.hpp"
#include "shader\cso\forward\forward_emissive_PS.hpp"
#include "shader\cso\forward\forward_frostbite_PS.hpp"
#include "shader\cso\forward\forward_lambertian_PS.hpp"
#include "shader\cso\forward\forward_ward_duer_PS.hpp"
// Forward: TSNM
#include "shader\cso\forward\forward_tsnm_blinn_phong_PS.hpp"
#include "shader\cso\forward\forward_tsnm_cook_torrance_PS.hpp"
#include "shader\cso\forward\forward_tsnm_frostbite_PS.hpp"
#include "shader\cso\forward\forward_tsnm_lambertian_PS.hpp"
#include "shader\cso\forward\forward_tsnm_ward_duer_PS.hpp"
// Forward: Transparent
#include "shader\cso\forward\forward_transparent_blinn_phong_PS.hpp"
#include "shader\cso\forward\forward_transparent_cook_torrance_PS.hpp"
#include "shader\cso\forward\forward_transparent_emissive_PS.hpp"
#include "shader\cso\forward\forward_transparent_frostbite_PS.hpp"
#include "shader\cso\forward\forward_transparent_lambertian_PS.hpp"
#include "shader\cso\forward\forward_transparent_ward_duer_PS.hpp"
// Forward: Transparent + TSNM
#include "shader\cso\forward\forward_transparent_tsnm_blinn_phong_PS.hpp"
#include "shader\cso\forward\forward_transparent_tsnm_cook_torrance_PS.hpp"
#include "shader\cso\forward\forward_transparent_tsnm_frostbite_PS.hpp"
#include "shader\cso\forward\forward_transparent_tsnm_lambertian_PS.hpp"
#include "shader\cso\forward\forward_transparent_tsnm_ward_duer_PS.hpp"

// GBuffer
#include "shader\cso\gbuffer\gbuffer_PS.hpp"
// GBuffer: TSNM
#include "shader\cso\gbuffer\gbuffer_tsnm_PS.hpp"

// Miscellaneous
#include "shader\cso\miscellaneous\back_buffer_PS.hpp"
#include "shader\cso\miscellaneous\distance_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_texture_PS.hpp"
#include "shader\cso\miscellaneous\shading_normal_VS.hpp"
#include "shader\cso\miscellaneous\shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\tsnm_shading_normal_PS.hpp"

// Primitive
#include "shader\cso\primitive\line_cube_VS.hpp"
#include "shader\cso\primitive\line_cube_PS.hpp"
#include "shader\cso\primitive\far_fullscreen_triangle_VS.hpp"
#include "shader\cso\primitive\near_fullscreen_triangle_VS.hpp"

// Sky
#include "shader\cso\sky\sky_VS.hpp"
#include "shader\cso\sky\sky_PS.hpp"

// Sprite
#include "shader\cso\sprite\sprite_VS.hpp"
#include "shader\cso\sprite\sprite_PS.hpp"

// Tone Mapping
#include "shader\cso\tone_mapping\tone_mapper_CS.hpp"

// Transform
#include "shader\cso\transform\minimal_transform_VS.hpp"
#include "shader\cso\transform\transform_VS.hpp"

// Voxelization
#include "shader\cso\voxelization\voxelization_GS.hpp"
#include "shader\cso\voxelization\voxelization_PS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_SHADER_GUID(buffer) L#buffer
#define MAGE_SHADER_ARGS(buffer) MAGE_SHADER_GUID(buffer), \
								 BufferCompiledShader(buffer, sizeof(buffer))

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Note: All factory methods could be made lazy. This will not result in 
	//       performance gains since BufferCompiledShaders are not expensive to 
	//       create. 

	//-------------------------------------------------------------------------
	// Factory Methods: AA
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const ComputeShader > CreateFXAACS() {
		return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_fxaa_CS));
	}

	SharedPtr< const ComputeShader > CreateMSAAResolveCS(U32 nb_samples) {
		switch (nb_samples) {
		case 2:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_msaa_2x_resolve_CS));
		case 4:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_msaa_4x_resolve_CS));
		case 8:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_msaa_8x_resolve_CS));
		case 16:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_msaa_16x_resolve_CS));
		case 32:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_msaa_32x_resolve_CS));
		default:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_msaa_resolve_CS));
		}
	}

	SharedPtr< const ComputeShader > CreateSSAAResolveCS(U32 nb_samples) {
		switch (nb_samples) {
		case 4:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_ssaa_2x_resolve_CS));
		case 9:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_ssaa_3x_resolve_CS));
		case 16:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_ssaa_4x_resolve_CS));
		default:
			return ResourceManager::Get()->GetOrCreateCS(
				MAGE_SHADER_ARGS(g_ssaa_resolve_CS));
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Deferred
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const ComputeShader > CreateDeferredBlinnPhongCS() {
		return ResourceManager::Get()->GetOrCreateCS(
			MAGE_SHADER_ARGS(g_deferred_blinn_phong_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredCookTorranceCS() {
		return ResourceManager::Get()->GetOrCreateCS(
			MAGE_SHADER_ARGS(g_deferred_cook_torrance_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredEmissiveCS() {
		return ResourceManager::Get()->GetOrCreateCS(
			MAGE_SHADER_ARGS(g_deferred_emissive_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredFrostbiteCS() {
		return ResourceManager::Get()->GetOrCreateCS(
			MAGE_SHADER_ARGS(g_deferred_frostbite_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredLambertianCS() {
		return ResourceManager::Get()->GetOrCreateCS(
			MAGE_SHADER_ARGS(g_deferred_lambertian_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredWardDuerCS() {
		return ResourceManager::Get()->GetOrCreateCS(
			MAGE_SHADER_ARGS(g_deferred_ward_duer_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredCS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::BlinnPhong:
			return CreateDeferredBlinnPhongCS();
		case BRDFType::CookTorrance:
			return CreateDeferredCookTorranceCS();
		case BRDFType::Lambertian:
			return CreateDeferredLambertianCS();
		case BRDFType::WardDuer:
			return CreateDeferredWardDuerCS();
		default:
			return CreateDeferredFrostbiteCS();
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Depth
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateDepthVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_depth_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const VertexShader > CreateDepthTransparentVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_depth_transparent_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateDepthTransparentPS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_depth_transparent_PS));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Forward
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateForwardBlinnPhongPS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_blinn_phong_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_tsnm_blinn_phong_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_blinn_phong_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_blinn_phong_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardCookTorrancePS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_cook_torrance_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_tsnm_cook_torrance_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_cook_torrance_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_cook_torrance_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardEmissivePS(
		bool transparency) {

		return transparency ?
			ResourceManager::Get()->GetOrCreatePS(
				MAGE_SHADER_ARGS(g_forward_transparent_emissive_PS))
			:
			ResourceManager::Get()->GetOrCreatePS(
				MAGE_SHADER_ARGS(g_forward_emissive_PS));
	}

	SharedPtr< const PixelShader > CreateForwardFrostbitePS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_frostbite_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_tsnm_frostbite_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_frostbite_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_frostbite_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardLambertianPS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_lambertian_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_tsnm_lambertian_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_lambertian_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_lambertian_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardWardDuerPS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_ward_duer_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_tsnm_ward_duer_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_transparent_ward_duer_PS))
				:
				ResourceManager::Get()->GetOrCreatePS(
					MAGE_SHADER_ARGS(g_forward_ward_duer_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardPS(
		BRDFType brdf, bool tsnm, bool transparency) {

		switch (brdf) {

		case BRDFType::BlinnPhong:
			return CreateForwardBlinnPhongPS(tsnm, transparency);
		case BRDFType::CookTorrance:
			return CreateForwardCookTorrancePS(tsnm, transparency);
		case BRDFType::Lambertian:
			return CreateForwardLambertianPS(tsnm, transparency);
		case BRDFType::WardDuer:
			return CreateForwardWardDuerPS(tsnm, transparency);
		default:
			return CreateForwardFrostbitePS(tsnm, transparency);
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBuffer
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateGBufferPS(bool tsnm) {
		return tsnm ?
			ResourceManager::Get()->GetOrCreatePS(
				MAGE_SHADER_ARGS(g_gbuffer_tsnm_PS))
			:
			ResourceManager::Get()->GetOrCreatePS(
				MAGE_SHADER_ARGS(g_gbuffer_PS));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateBackBufferPS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_back_buffer_PS));
	}

	SharedPtr< const PixelShader > CreateConstantColorPS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_constant_color_PS));
	}

	SharedPtr< const PixelShader > CreateConstantColorTexturePS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_constant_color_texture_PS));
	}

	SharedPtr< const PixelShader > CreateDistancePS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_distance_PS));
	}

	SharedPtr< const VertexShader > CreateShadingNormalVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_shading_normal_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateShadingNormalPS(bool tsnm) {
		return tsnm ?
			ResourceManager::Get()->GetOrCreatePS(
				MAGE_SHADER_ARGS(g_tsnm_shading_normal_PS))
			:
			ResourceManager::Get()->GetOrCreatePS(
				MAGE_SHADER_ARGS(g_shading_normal_PS));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Primitive
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateLineCubeVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_line_cube_VS), nullptr, 0u);
	}

	SharedPtr< const PixelShader > CreateLineCubePS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_line_cube_PS));
	}

	SharedPtr< const VertexShader > CreateFarFullscreenTriangleVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_far_fullscreen_triangle_VS), nullptr, 0u);
	}

	SharedPtr< const VertexShader > CreateNearFullscreenTriangleVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_near_fullscreen_triangle_VS), nullptr, 0u);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sky
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateSkyVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_sky_VS), nullptr, 0u);
	}

	SharedPtr< const PixelShader > CreateSkyPS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_sky_PS));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sprite
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateSpriteVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_sprite_VS),
			VertexPositionColorTexture::s_input_element_desc,
			VertexPositionColorTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateSpritePS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_sprite_PS));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Tone Mapping
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const ComputeShader > CreateToneMapperCS() {
		return ResourceManager::Get()->GetOrCreateCS(
			MAGE_SHADER_ARGS(g_tone_mapper_CS));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Transform
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateMinimalTransformVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_minimal_transform_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const VertexShader > CreateTransformVS() {
		return ResourceManager::Get()->GetOrCreateVS(
			MAGE_SHADER_ARGS(g_transform_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Voxelization
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const GeometryShader > CreateVoxelizationGS() {
		return ResourceManager::Get()->GetOrCreateGS(
			MAGE_SHADER_ARGS(g_voxelization_GS));
	}

	SharedPtr< const PixelShader > CreateVoxelizationPS() {
		return ResourceManager::Get()->GetOrCreatePS(
			MAGE_SHADER_ARGS(g_voxelization_PS));
	}

#pragma endregion
}