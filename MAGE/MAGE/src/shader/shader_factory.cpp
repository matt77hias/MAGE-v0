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
#include "shader\cso\deferred\phong_CS.hpp"
#include "shader\cso\deferred\modified_phong_CS.hpp"
#include "shader\cso\deferred\blinn_phong_CS.hpp"
#include "shader\cso\deferred\modified_blinn_phong_CS.hpp"
#include "shader\cso\deferred\ward_CS.hpp"
#include "shader\cso\deferred\ward_duer_CS.hpp"
#include "shader\cso\deferred\cook_torrance_CS.hpp"

// Forward
#include "shader\cso\forward\transform_VS.hpp"
#include "shader\cso\forward\emissive_PS.hpp"
#include "shader\cso\forward\lambertian_PS.hpp"
#include "shader\cso\forward\phong_PS.hpp"
#include "shader\cso\forward\modified_phong_PS.hpp"
#include "shader\cso\forward\blinn_phong_PS.hpp"
#include "shader\cso\forward\modified_blinn_phong_PS.hpp"
#include "shader\cso\forward\ward_PS.hpp"
#include "shader\cso\forward\ward_duer_PS.hpp"
#include "shader\cso\forward\cook_torrance_PS.hpp"
#include "shader\cso\forward\tsnm_lambertian_PS.hpp"
#include "shader\cso\forward\tsnm_phong_PS.hpp"
#include "shader\cso\forward\tsnm_modified_phong_PS.hpp"
#include "shader\cso\forward\tsnm_blinn_phong_PS.hpp"
#include "shader\cso\forward\tsnm_modified_blinn_phong_PS.hpp"
#include "shader\cso\forward\tsnm_ward_PS.hpp"
#include "shader\cso\forward\tsnm_ward_duer_PS.hpp"
#include "shader\cso\forward\tsnm_cook_torrance_PS.hpp"

// Sprite
#include "shader\cso\sprite\sprite_VS.hpp"
#include "shader\cso\sprite\sprite_PS.hpp"

// Miscellaneous
#include "shader\cso\miscellaneous\minimal_transform_VS.hpp"
#include "shader\cso\miscellaneous\image_PS.hpp"
#include "shader\cso\miscellaneous\image_depth_PS.hpp"
#include "shader\cso\miscellaneous\distance_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_texture_PS.hpp"
#include "shader\cso\miscellaneous\shading_normal_VS.hpp"
#include "shader\cso\miscellaneous\shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\tsnm_shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\bounding_volume_VS.hpp"
#include "shader\cso\miscellaneous\bounding_volume_PS.hpp"

// Primitives
#include "shader\cso\primitives\fullscreen_triangle_VS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Note: All factory methods could be made lazy.
	//       This will not result in performance gains since 
	//       BufferCompiledShaders are not expensive to create. 

	//-------------------------------------------------------------------------
	// Factory Methods: DepthPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateDepthVS() {
		const BufferCompiledShader cs(g_depth_vs, sizeof(g_depth_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_DEPTH, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const VertexShader > CreateDepthTransparentVS() {
		const BufferCompiledShader cs(g_depth_transparent_vs, sizeof(g_depth_transparent_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_DEPTH_TRANSPARENT, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateDepthTransparentPS() {
		const BufferCompiledShader cs(g_depth_transparent_ps, sizeof(g_depth_transparent_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEPTH_TRANSPARENT, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantShadingPass and VariableShadingPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateTransformVS() {
		const BufferCompiledShader cs(g_transform_vs, sizeof(g_transform_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_TRANSFORM, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateEmissivePS() {
		const BufferCompiledShader cs(g_emissive_ps, sizeof(g_emissive_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_EMISSIVE, &cs);
	}

	SharedPtr< const PixelShader > CreateLambertianPS() {
		const BufferCompiledShader cs(g_lambertian_ps, sizeof(g_lambertian_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_LAMBERTIAN, &cs);
	}

	SharedPtr< const PixelShader > CreatePhongPS() {
		const BufferCompiledShader cs(g_phong_ps, sizeof(g_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedPhongPS() {
		const BufferCompiledShader cs(g_modified_phong_ps, sizeof(g_modified_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_MODIFIED_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateBlinnPhongPS() {
		const BufferCompiledShader cs(g_blinn_phong_ps, sizeof(g_blinn_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedBlinnPhongPS() {
		const BufferCompiledShader cs(g_modified_blinn_phong_ps, sizeof(g_modified_blinn_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_MODIFIED_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateWardPS() {
		const BufferCompiledShader cs(g_ward_ps, sizeof(g_ward_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_WARD, &cs);
	}

	SharedPtr< const PixelShader > CreateWardDuerPS() {
		const BufferCompiledShader cs(g_ward_duer_ps, sizeof(g_ward_duer_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_WARD_DUER, &cs);
	}

	SharedPtr< const PixelShader > CreateCookTorrancePS() {
		const BufferCompiledShader cs(g_cook_torrance_ps, sizeof(g_cook_torrance_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_COOK_TORRANCE, &cs);
	}
	
	SharedPtr< const PixelShader > CreatePS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::Lambertian:
			return CreateLambertianPS();
		case BRDFType::Phong:
			return CreatePhongPS();
		case BRDFType::ModifiedPhong:
			return CreateModifiedPhongPS();
		case BRDFType::BlinnPhong:
			return CreateBlinnPhongPS();
		case BRDFType::Ward:
			return CreateWardPS();
		case BRDFType::WardDuer:
			return CreateWardDuerPS();
		case BRDFType::CookTorrance:
			return CreateCookTorrancePS();
		default:
			return CreateModifiedBlinnPhongPS();
		}
	}

	SharedPtr< const PixelShader > CreateLambertianTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_lambertian_ps, sizeof(g_tsnm_lambertian_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_LAMBERTIAN, &cs);
	}

	SharedPtr< const PixelShader > CreatePhongTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_phong_ps, sizeof(g_tsnm_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedPhongTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_modified_phong_ps, sizeof(g_tsnm_modified_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_MODIFIED_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateBlinnPhongTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_blinn_phong_ps, sizeof(g_tsnm_blinn_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedBlinnPhongTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_modified_blinn_phong_ps, sizeof(g_tsnm_modified_blinn_phong_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_MODIFIED_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateWardTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_ward_ps, sizeof(g_tsnm_ward_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_WARD, &cs);
	}

	SharedPtr< const PixelShader > CreateWardDuerTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_ward_duer_ps, sizeof(g_tsnm_ward_duer_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_WARD_DUER, &cs);
	}

	SharedPtr< const PixelShader > CreateCookTorranceTSNMPS() {
		const BufferCompiledShader cs(g_tsnm_cook_torrance_ps, sizeof(g_tsnm_cook_torrance_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_COOK_TORRANCE, &cs);
	}

	SharedPtr< const PixelShader > CreateTSNMPS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::Lambertian:
			return CreateLambertianTSNMPS();
		case BRDFType::Phong:
			return CreatePhongTSNMPS();
		case BRDFType::ModifiedPhong:
			return CreateModifiedPhongTSNMPS();
		case BRDFType::BlinnPhong:
			return CreateBlinnPhongTSNMPS();
		case BRDFType::Ward:
			return CreateWardTSNMPS();
		case BRDFType::WardDuer:
			return CreateWardDuerTSNMPS();
		case BRDFType::CookTorrance:
			return CreateCookTorranceTSNMPS();
		default:
			return CreateModifiedBlinnPhongTSNMPS();
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBufferPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateGBufferPS() {
		const BufferCompiledShader cs(g_gbuffer_ps, sizeof(g_gbuffer_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_GBUFFER, &cs);
	}

	SharedPtr< const PixelShader > CreateGBufferTSNMPS() {
		const BufferCompiledShader cs(g_gbuffer_tsnm_ps, sizeof(g_gbuffer_tsnm_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_GBUFFER_TSNM, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: DeferredShadingPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const ComputeShader > CreateDeferredEmissiveCS() {
		const BufferCompiledShader cs(g_deferred_emissive_cs, sizeof(g_deferred_emissive_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_EMISSIVE, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredLambertianCS() {
		const BufferCompiledShader cs(g_deferred_lambertian_cs, sizeof(g_deferred_lambertian_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_LAMBERTIAN, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredPhongCS() {
		const BufferCompiledShader cs(g_deferred_phong_cs, sizeof(g_deferred_phong_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_PHONG, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredModifiedPhongCS() {
		const BufferCompiledShader cs(g_deferred_modified_phong_cs, sizeof(g_deferred_modified_phong_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_MODIFIED_PHONG, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredBlinnPhongCS() {
		const BufferCompiledShader cs(g_deferred_blinn_phong_cs, sizeof(g_deferred_blinn_phong_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_BLINN_PHONG, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredModifiedBlinnPhongCS() {
		const BufferCompiledShader cs(g_deferred_modified_blinn_phong_cs, sizeof(g_deferred_modified_blinn_phong_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_MODIFIED_BLINN_PHONG, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredWardCS() {
		const BufferCompiledShader cs(g_deferred_ward_cs, sizeof(g_deferred_ward_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_WARD, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredWardDuerCS() {
		const BufferCompiledShader cs(g_deferred_ward_duer_cs, sizeof(g_deferred_ward_duer_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_WARD_DUER, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredCookTorranceCS() {
		const BufferCompiledShader cs(g_deferred_cook_torrance_cs, sizeof(g_deferred_cook_torrance_cs));
		return ResourceManager::Get()->GetOrCreateCS(MAGE_GUID_CS_DEFERRED_COOK_TORRANCE, &cs);
	}

	SharedPtr< const ComputeShader > CreateDeferredCS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::Lambertian:
			return CreateDeferredLambertianCS();
		case BRDFType::Phong:
			return CreateDeferredPhongCS();
		case BRDFType::ModifiedPhong:
			return CreateDeferredModifiedPhongCS();
		case BRDFType::BlinnPhong:
			return CreateDeferredBlinnPhongCS();
		case BRDFType::Ward:
			return CreateDeferredWardCS();
		case BRDFType::WardDuer:
			return CreateDeferredWardDuerCS();
		case BRDFType::CookTorrance:
			return CreateDeferredCookTorranceCS();
		default:
			return CreateDeferredModifiedBlinnPhongCS();
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: SpritePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateSpriteVS() {
		const BufferCompiledShader cs(g_sprite_vs, sizeof(g_sprite_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_SPRITE, &cs,
										VertexPositionColorTexture::s_input_element_desc,
										VertexPositionColorTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateSpritePS() {
		const BufferCompiledShader cs(g_sprite_ps, sizeof(g_sprite_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_SPRITE, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantComponentPass and VariableComponentPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateMinimalTransformVS() noexcept {
		const BufferCompiledShader cs(g_minimal_transform_vs, sizeof(g_minimal_transform_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_MINIMAL_TRANSFORM, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateConstantColorPS() noexcept {
		const BufferCompiledShader cs(g_constant_color_ps, sizeof(g_constant_color_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_CONSTANT_COLOR, &cs);
	}

	SharedPtr< const PixelShader > CreateConstantColorTexturePS() noexcept {
		const BufferCompiledShader cs(g_constant_color_texture_ps, sizeof(g_constant_color_texture_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_CONSTANT_COLOR_TEXTURE, &cs);
	}

	SharedPtr< const PixelShader > CreateDistancePS() noexcept {
		const BufferCompiledShader cs(g_distance_ps, sizeof(g_distance_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DISTANCE, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ShadingNormalPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateShadingNormalVS() noexcept {
		const BufferCompiledShader cs(g_shading_normal_vs, sizeof(g_shading_normal_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_SHADING_NORMAL, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateShadingNormalPS() noexcept {
		const BufferCompiledShader cs(g_shading_normal_ps, sizeof(g_shading_normal_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_SHADING_NORMAL, &cs);
	}

	SharedPtr< const PixelShader > CreateShadingNormalTSNMPS() noexcept {
		const BufferCompiledShader cs(g_tsnm_shading_normal_ps, sizeof(g_tsnm_shading_normal_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_SHADING_NORMAL, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: BoundingVolumePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateBoundingVolumeVS() noexcept {
		const BufferCompiledShader cs(g_bounding_volume_vs, sizeof(g_bounding_volume_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_BOUNDING_VOLUME, &cs,
								VertexPosition::s_input_element_desc,
								VertexPosition::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateBoundingVolumePS() noexcept {
		const BufferCompiledShader cs(g_bounding_volume_ps, sizeof(g_bounding_volume_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_BOUNDING_VOLUME, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ImagePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateImagePS() {
		const BufferCompiledShader cs(g_image_ps, sizeof(g_image_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_IMAGE, &cs);
	}

	SharedPtr< const PixelShader > CreateImageDepthPS() {
		const BufferCompiledShader cs(g_image_depth_ps, sizeof(g_image_depth_ps));
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_IMAGE_DEPTH, &cs);
	}

	SharedPtr< const VertexShader > CreateFullscreenTriangleVS() {
		const BufferCompiledShader cs(g_fullscreen_triangle_vs, sizeof(g_fullscreen_triangle_vs));
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_FULLSCREEN_TRIANGLE, &cs,
										nullptr,
										0);
	}

#pragma endregion
}