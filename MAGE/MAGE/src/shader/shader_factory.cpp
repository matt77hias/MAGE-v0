//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "mesh\vertex.hpp"

// Depth
#include "shader\cso\depth\depth_VS.hpp"
#include "shader\cso\depth\depth_transparent_VS.hpp"
#include "shader\cso\depth\depth_transparent_PS.hpp"

// GBuffer
#include "shader\cso\gbuffer\gbuffer_PS.hpp"
#include "shader\cso\gbuffer\gbuffer_tsnm_PS.hpp"

// Deferred
#include "shader\cso\deferred\emissive_CS.hpp"
#include "shader\cso\deferred\lambertian_CS.hpp"
#include "shader\cso\deferred\cook_torrance_CS.hpp"

// Forward
#include "shader\cso\forward\transform_VS.hpp"
#include "shader\cso\forward\emissive_PS.hpp"
#include "shader\cso\forward\lambertian_PS.hpp"
#include "shader\cso\forward\cook_torrance_PS.hpp"
#include "shader\cso\forward\tsnm_lambertian_PS.hpp"
#include "shader\cso\forward\tsnm_cook_torrance_PS.hpp"

// Sprite
#include "shader\cso\sky\sky_PS.hpp"

// Sprite
#include "shader\cso\sprite\sprite_VS.hpp"
#include "shader\cso\sprite\sprite_PS.hpp"

// Miscellaneous
#include "shader\cso\miscellaneous\minimal_transform_VS.hpp"
#include "shader\cso\miscellaneous\back_buffer_PS.hpp"
#include "shader\cso\miscellaneous\distance_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_texture_PS.hpp"
#include "shader\cso\miscellaneous\shading_normal_VS.hpp"
#include "shader\cso\miscellaneous\shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\tsnm_shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\bounding_volume_VS.hpp"
#include "shader\cso\miscellaneous\bounding_volume_PS.hpp"

// Primitives
#include "shader\cso\primitives\far_fullscreen_triangle_VS.hpp"
#include "shader\cso\primitives\near_fullscreen_triangle_VS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Note: All factory methods could be made lazy. This will not result in 
	//       performance gains since BufferCompiledShaders are not expensive to 
	//       create. 

	//-------------------------------------------------------------------------
	// Factory Methods: DepthPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateDepthVS() {
		const BufferCompiledShader cs(
				g_depth_vs, sizeof(g_depth_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_DEPTH, &cs,
				VertexPositionNormalTexture::s_input_element_desc,
				VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const VertexShader > CreateDepthTransparentVS() {
		const BufferCompiledShader cs(
				g_depth_transparent_vs, sizeof(g_depth_transparent_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_DEPTH_TRANSPARENT, &cs,
				VertexPositionNormalTexture::s_input_element_desc,
				VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateDepthTransparentPS() {
		const BufferCompiledShader cs(
				g_depth_transparent_ps, sizeof(g_depth_transparent_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_DEPTH_TRANSPARENT, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantShadingPass and VariableShadingPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateTransformVS() {
		const BufferCompiledShader cs(
				g_transform_vs, sizeof(g_transform_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_TRANSFORM, &cs,
				VertexPositionNormalTexture::s_input_element_desc,
				VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateEmissivePS() {
		const BufferCompiledShader cs(
				g_emissive_ps, sizeof(g_emissive_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_EMISSIVE, &cs);
	}

	SharedPtr< const PixelShader > CreateLambertianPS() {
		const BufferCompiledShader cs(
				g_lambertian_ps, sizeof(g_lambertian_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_LAMBERTIAN, &cs);
	}

	SharedPtr< const PixelShader > CreateCookTorrancePS() {
		const BufferCompiledShader cs(
				g_cook_torrance_ps, sizeof(g_cook_torrance_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_COOK_TORRANCE, &cs);
	}
	
	SharedPtr< const PixelShader > CreatePS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::Lambertian:
			return CreateLambertianPS();
		case BRDFType::CookTorrance:
			return CreateCookTorrancePS();
		default:
			return CreateCookTorrancePS();
		}
	}

	SharedPtr< const PixelShader > CreateLambertianTSNMPS() {
		const BufferCompiledShader cs(
				g_tsnm_lambertian_ps, sizeof(g_tsnm_lambertian_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_TSNM_LAMBERTIAN, &cs);
	}

	SharedPtr< const PixelShader > CreateCookTorranceTSNMPS() {
		const BufferCompiledShader cs(
				g_tsnm_cook_torrance_ps, sizeof(g_tsnm_cook_torrance_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_TSNM_COOK_TORRANCE, &cs);
	}

	SharedPtr< const PixelShader > CreateTSNMPS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::Lambertian:
			return CreateLambertianTSNMPS();
		case BRDFType::CookTorrance:
			return CreateCookTorranceTSNMPS();
		default:
			return CreateCookTorranceTSNMPS();
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBufferPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateGBufferPS() {
		const BufferCompiledShader cs(
				g_gbuffer_ps, sizeof(g_gbuffer_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_GBUFFER, &cs);
	}

	SharedPtr< const PixelShader > CreateGBufferTSNMPS() {
		const BufferCompiledShader cs(
				g_gbuffer_tsnm_ps, sizeof(g_gbuffer_tsnm_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_GBUFFER_TSNM, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: DeferredShadingPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const ComputeShader > CreateDeferredEmissiveCS() {
		const BufferCompiledShader cs(
				g_deferred_emissive_cs, sizeof(g_deferred_emissive_cs));
		
		return ResourceManager::Get()->GetOrCreateCS(
				MAGE_GUID_CS_DEFERRED_EMISSIVE, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredLambertianCS() {
		const BufferCompiledShader cs(
				g_deferred_lambertian_cs, sizeof(g_deferred_lambertian_cs));
		
		return ResourceManager::Get()->GetOrCreateCS(
				MAGE_GUID_CS_DEFERRED_LAMBERTIAN, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredCookTorranceCS() {
		const BufferCompiledShader cs(
				g_deferred_cook_torrance_cs, sizeof(g_deferred_cook_torrance_cs));
		
		return ResourceManager::Get()->GetOrCreateCS(
				MAGE_GUID_CS_DEFERRED_COOK_TORRANCE, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredCS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::Lambertian:
			return CreateDeferredLambertianCS();
		case BRDFType::CookTorrance:
			return CreateDeferredCookTorranceCS();
		default:
			return CreateDeferredCookTorranceCS();
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: SpritePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateSpriteVS() {
		const BufferCompiledShader cs(
				g_sprite_vs, sizeof(g_sprite_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_SPRITE, &cs,
				VertexPositionColorTexture::s_input_element_desc,
				VertexPositionColorTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateSpritePS() {
		const BufferCompiledShader cs(
				g_sprite_ps, sizeof(g_sprite_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_SPRITE, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantComponentPass and VariableComponentPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateMinimalTransformVS() noexcept {
		const BufferCompiledShader cs(
				g_minimal_transform_vs, sizeof(g_minimal_transform_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_MINIMAL_TRANSFORM, &cs,
				VertexPositionNormalTexture::s_input_element_desc,
				VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateConstantColorPS() noexcept {
		const BufferCompiledShader cs(
				g_constant_color_ps, sizeof(g_constant_color_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_CONSTANT_COLOR, &cs);
	}

	SharedPtr< const PixelShader > CreateConstantColorTexturePS() noexcept {
		const BufferCompiledShader cs(
				g_constant_color_texture_ps, sizeof(g_constant_color_texture_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_CONSTANT_COLOR_TEXTURE, &cs);
	}

	SharedPtr< const PixelShader > CreateDistancePS() noexcept {
		const BufferCompiledShader cs(
				g_distance_ps, sizeof(g_distance_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_DISTANCE, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ShadingNormalPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateShadingNormalVS() noexcept {
		const BufferCompiledShader cs(
				g_shading_normal_vs, sizeof(g_shading_normal_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_SHADING_NORMAL, &cs,
				VertexPositionNormalTexture::s_input_element_desc,
				VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateShadingNormalPS() noexcept {
		const BufferCompiledShader cs(
				g_shading_normal_ps, sizeof(g_shading_normal_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_SHADING_NORMAL, &cs);
	}

	SharedPtr< const PixelShader > CreateShadingNormalTSNMPS() noexcept {
		const BufferCompiledShader cs(
				g_tsnm_shading_normal_ps, sizeof(g_tsnm_shading_normal_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_TSNM_SHADING_NORMAL, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: BoundingVolumePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateBoundingVolumeVS() noexcept {
		const BufferCompiledShader cs(
				g_bounding_volume_vs, sizeof(g_bounding_volume_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_BOUNDING_VOLUME, &cs,
				VertexPosition::s_input_element_desc,
				VertexPosition::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateBoundingVolumePS() noexcept {
		const BufferCompiledShader cs(
				g_bounding_volume_ps, sizeof(g_bounding_volume_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_BOUNDING_VOLUME, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ImagePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateBackBufferPS() {
		const BufferCompiledShader cs(
				g_back_buffer_ps, sizeof(g_back_buffer_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_BACK_BUFFER, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: SkyPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateSkyPS() {
		const BufferCompiledShader cs(
				g_sky_ps, sizeof(g_sky_ps));
		
		return ResourceManager::Get()->GetOrCreatePS(
				MAGE_GUID_PS_SKY, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Primitives
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateFarFullscreenTriangleVS() {
		const BufferCompiledShader cs(
			g_far_fullscreen_triangle_vs, sizeof(g_far_fullscreen_triangle_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_FAR_FULLSCREEN_TRIANGLE, &cs,
				nullptr,
				0);
	}

	SharedPtr< const VertexShader > CreateNearFullscreenTriangleVS() {
		const BufferCompiledShader cs(
				g_near_fullscreen_triangle_vs, sizeof(g_near_fullscreen_triangle_vs));
		
		return ResourceManager::Get()->GetOrCreateVS(
				MAGE_GUID_VS_NEAR_FULLSCREEN_TRIANGLE, &cs,
				nullptr,
				0);
	}

#pragma endregion
}