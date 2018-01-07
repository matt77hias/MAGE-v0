//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "mesh\vertex.hpp"

// AA
#include "aa\aa_preprocess_CS.hpp"
#include "aa\fxaa_CS.hpp"
#include "aa\msaa_resolve_CS.hpp"
#include "aa\ssaa_resolve_CS.hpp"

// Deferred
#include "deferred\deferred_blinn_phong_CS.hpp"
#include "deferred\deferred_cook_torrance_CS.hpp"
#include "deferred\deferred_emissive_CS.hpp"
#include "deferred\deferred_frostbite_CS.hpp"
#include "deferred\deferred_lambertian_CS.hpp"
#include "deferred\deferred_ward_duer_CS.hpp"
#include "deferred\deferred_msaa_blinn_phong_PS.hpp"
#include "deferred\deferred_msaa_cook_torrance_PS.hpp"
#include "deferred\deferred_msaa_emissive_PS.hpp"
#include "deferred\deferred_msaa_frostbite_PS.hpp"
#include "deferred\deferred_msaa_lambertian_PS.hpp"
#include "deferred\deferred_msaa_ward_duer_PS.hpp"

// Depth
#include "depth\depth_VS.hpp"
#include "depth\depth_transparent_VS.hpp"
#include "depth\depth_transparent_PS.hpp"

// Forward
#include "forward\forward_blinn_phong_PS.hpp"
#include "forward\forward_cook_torrance_PS.hpp"
#include "forward\forward_emissive_PS.hpp"
#include "forward\forward_frostbite_PS.hpp"
#include "forward\forward_lambertian_PS.hpp"
#include "forward\forward_ward_duer_PS.hpp"
// Forward: TSNM
#include "forward\forward_tsnm_blinn_phong_PS.hpp"
#include "forward\forward_tsnm_cook_torrance_PS.hpp"
#include "forward\forward_tsnm_frostbite_PS.hpp"
#include "forward\forward_tsnm_lambertian_PS.hpp"
#include "forward\forward_tsnm_ward_duer_PS.hpp"
// Forward: Transparent
#include "forward\forward_transparent_blinn_phong_PS.hpp"
#include "forward\forward_transparent_cook_torrance_PS.hpp"
#include "forward\forward_transparent_emissive_PS.hpp"
#include "forward\forward_transparent_frostbite_PS.hpp"
#include "forward\forward_transparent_lambertian_PS.hpp"
#include "forward\forward_transparent_ward_duer_PS.hpp"
// Forward: Transparent + TSNM
#include "forward\forward_transparent_tsnm_blinn_phong_PS.hpp"
#include "forward\forward_transparent_tsnm_cook_torrance_PS.hpp"
#include "forward\forward_transparent_tsnm_frostbite_PS.hpp"
#include "forward\forward_transparent_tsnm_lambertian_PS.hpp"
#include "forward\forward_transparent_tsnm_ward_duer_PS.hpp"

// GBuffer
#include "gbuffer\gbuffer_PS.hpp"
// GBuffer: TSNM
#include "gbuffer\gbuffer_tsnm_PS.hpp"

// Miscellaneous
#include "miscellaneous\back_buffer_PS.hpp"
#include "miscellaneous\distance_PS.hpp"
#include "miscellaneous\constant_color_PS.hpp"
#include "miscellaneous\constant_color_texture_PS.hpp"
#include "miscellaneous\shading_normal_VS.hpp"
#include "miscellaneous\shading_normal_PS.hpp"
#include "miscellaneous\tsnm_shading_normal_PS.hpp"

// Post-processing
#include "postprocessing\postprocessing_depth_of_field_CS.hpp"

// Primitive
#include "primitive\line_cube_VS.hpp"
#include "primitive\line_cube_PS.hpp"
#include "primitive\far_fullscreen_triangle_VS.hpp"
#include "primitive\near_fullscreen_triangle_VS.hpp"

// Sky
#include "sky\sky_VS.hpp"
#include "sky\sky_PS.hpp"

// Sprite
#include "sprite\sprite_VS.hpp"
#include "sprite\sprite_PS.hpp"

// Transform
#include "transform\minimal_transform_VS.hpp"
#include "transform\transform_VS.hpp"

// Voxelization
#include "voxelization\voxelization_GS.hpp"
#include "voxelization\voxelization_PS.hpp"

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

	SharedPtr< const ComputeShader > CreateAAPreprocessCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_aa_preprocess_CS));
	}

	SharedPtr< const ComputeShader > CreateFXAACS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
				MAGE_SHADER_ARGS(g_fxaa_CS));
	}

	SharedPtr< const ComputeShader > CreateMSAAResolveCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_msaa_resolve_CS));
	}

	SharedPtr< const ComputeShader > CreateSSAAResolveCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_ssaa_resolve_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Deferred
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const ComputeShader > CreateDeferredBlinnPhongCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_deferred_blinn_phong_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredCookTorranceCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_deferred_cook_torrance_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredEmissiveCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_deferred_emissive_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredFrostbiteCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_deferred_frostbite_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredLambertianCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_deferred_lambertian_CS));
	}

	SharedPtr< const ComputeShader > CreateDeferredWardDuerCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
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

	SharedPtr< const PixelShader > CreateDeferredMSAABlinnPhongPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_deferred_msaa_blinn_phong_PS));
	}

	SharedPtr< const PixelShader > CreateDeferredMSAACookTorrancePS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_deferred_msaa_cook_torrance_PS));
	}

	SharedPtr< const PixelShader > CreateDeferredMSAAEmissivePS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_deferred_msaa_emissive_PS));
	}

	SharedPtr< const PixelShader > CreateDeferredMSAAFrostbitePS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_deferred_msaa_frostbite_PS));
	}

	SharedPtr< const PixelShader > CreateDeferredMSAALambertianPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_deferred_msaa_lambertian_PS));
	}

	SharedPtr< const PixelShader > CreateDeferredMSAAWardDuerPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_deferred_msaa_ward_duer_PS));
	}

	SharedPtr< const PixelShader > CreateDeferredMSAAPS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::BlinnPhong:
			return CreateDeferredMSAABlinnPhongPS();
		case BRDFType::CookTorrance:
			return CreateDeferredMSAACookTorrancePS();
		case BRDFType::Lambertian:
			return CreateDeferredMSAALambertianPS();
		case BRDFType::WardDuer:
			return CreateDeferredMSAAWardDuerPS();
		default:
			return CreateDeferredMSAAFrostbitePS();
		}
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Depth
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const VertexShader > CreateDepthVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_depth_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const VertexShader > CreateDepthTransparentVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_depth_transparent_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateDepthTransparentPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
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
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_blinn_phong_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_tsnm_blinn_phong_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_blinn_phong_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_blinn_phong_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardCookTorrancePS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_cook_torrance_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_tsnm_cook_torrance_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_cook_torrance_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_cook_torrance_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardEmissivePS(
		bool transparency) {

		return transparency ?
			ResourceManager::Get()->GetOrCreate< PixelShader >(
				MAGE_SHADER_ARGS(g_forward_transparent_emissive_PS))
			:
			ResourceManager::Get()->GetOrCreate< PixelShader >(
				MAGE_SHADER_ARGS(g_forward_emissive_PS));
	}

	SharedPtr< const PixelShader > CreateForwardFrostbitePS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_frostbite_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_tsnm_frostbite_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_frostbite_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_frostbite_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardLambertianPS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_lambertian_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_tsnm_lambertian_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_lambertian_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_lambertian_PS)));
	}

	SharedPtr< const PixelShader > CreateForwardWardDuerPS(
		bool tsnm, bool transparency) {

		return tsnm ?
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_tsnm_ward_duer_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_tsnm_ward_duer_PS)))
			:
			(transparency ?
				ResourceManager::Get()->GetOrCreate< PixelShader >(
					MAGE_SHADER_ARGS(g_forward_transparent_ward_duer_PS))
				:
				ResourceManager::Get()->GetOrCreate< PixelShader >(
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
			ResourceManager::Get()->GetOrCreate< PixelShader >(
				MAGE_SHADER_ARGS(g_gbuffer_tsnm_PS))
			:
			ResourceManager::Get()->GetOrCreate< PixelShader >(
				MAGE_SHADER_ARGS(g_gbuffer_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const PixelShader > CreateBackBufferPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_back_buffer_PS));
	}

	SharedPtr< const PixelShader > CreateConstantColorPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_constant_color_PS));
	}

	SharedPtr< const PixelShader > CreateConstantColorTexturePS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_constant_color_texture_PS));
	}

	SharedPtr< const PixelShader > CreateDistancePS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_distance_PS));
	}

	SharedPtr< const VertexShader > CreateShadingNormalVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_shading_normal_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateShadingNormalPS(bool tsnm) {
		return tsnm ?
			ResourceManager::Get()->GetOrCreate< PixelShader >(
				MAGE_SHADER_ARGS(g_tsnm_shading_normal_PS))
			:
			ResourceManager::Get()->GetOrCreate< PixelShader >(
				MAGE_SHADER_ARGS(g_shading_normal_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Post Processing
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const ComputeShader > CreateDepthOfFieldCS() {
		return ResourceManager::Get()->GetOrCreate< ComputeShader >(
			MAGE_SHADER_ARGS(g_postprocessing_depth_of_field_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Primitive
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const VertexShader > CreateLineCubeVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_line_cube_VS), nullptr, 0u);
	}

	SharedPtr< const PixelShader > CreateLineCubePS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_line_cube_PS));
	}

	SharedPtr< const VertexShader > CreateFarFullscreenTriangleVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_far_fullscreen_triangle_VS), nullptr, 0u);
	}

	SharedPtr< const VertexShader > CreateNearFullscreenTriangleVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_near_fullscreen_triangle_VS), nullptr, 0u);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sky
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const VertexShader > CreateSkyVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_sky_VS), nullptr, 0u);
	}

	SharedPtr< const PixelShader > CreateSkyPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_sky_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sprite
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const VertexShader > CreateSpriteVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_sprite_VS),
			VertexPositionColorTexture::s_input_element_desc,
			VertexPositionColorTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateSpritePS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_sprite_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Transform
	//-------------------------------------------------------------------------
	#pragma region

	SharedPtr< const VertexShader > CreateMinimalTransformVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
			MAGE_SHADER_ARGS(g_minimal_transform_VS),
			VertexPositionNormalTexture::s_input_element_desc,
			VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const VertexShader > CreateTransformVS() {
		return ResourceManager::Get()->GetOrCreate< VertexShader >(
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
		return ResourceManager::Get()->GetOrCreate< GeometryShader >(
			MAGE_SHADER_ARGS(g_voxelization_GS));
	}

	SharedPtr< const PixelShader > CreateVoxelizationPS() {
		return ResourceManager::Get()->GetOrCreate< PixelShader >(
			MAGE_SHADER_ARGS(g_voxelization_PS));
	}

	#pragma endregion
}