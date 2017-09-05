//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader_factory.hpp"
#include "shader\compiled_shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "mesh\vertex.hpp"

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
		const BufferCompiledShader cs = CreateCompiledDepthVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_DEPTH, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantShadingPass and VariableShadingPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateTransformVS() {
		const BufferCompiledShader cs = CreateCompiledTransformVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_TRANSFORM, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateEmissivePS() {
		const BufferCompiledShader cs = CreateCompiledEmissivePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_EMISSIVE, &cs);
	}

	SharedPtr< const PixelShader > CreateLambertianPS() {
		const BufferCompiledShader cs = CreateCompiledLambertianPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_LAMBERTIAN, &cs);
	}

	SharedPtr< const PixelShader > CreatePhongPS() {
		const BufferCompiledShader cs = CreateCompiledPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedPhongPS() {
		const BufferCompiledShader cs = CreateCompiledModifiedPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_MODIFIED_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateBlinnPhongPS() {
		const BufferCompiledShader cs = CreateCompiledBlinnPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedBlinnPhongPS() {
		const BufferCompiledShader cs = CreateCompiledModifiedBlinnPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_MODIFIED_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateWardPS() {
		const BufferCompiledShader cs = CreateCompiledWardPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_WARD, &cs);
	}

	SharedPtr< const PixelShader > CreateWardDuerPS() {
		const BufferCompiledShader cs = CreateCompiledWardDuerPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_WARD_DUER, &cs);
	}

	SharedPtr< const PixelShader > CreateCookTorrancePS() {
		const BufferCompiledShader cs = CreateCompiledCookTorrancePS();
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
		const BufferCompiledShader cs = CreateCompiledLambertianTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_LAMBERTIAN, &cs);
	}

	SharedPtr< const PixelShader > CreatePhongTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedPhongTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledModifiedPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_MODIFIED_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateBlinnPhongTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledBlinnPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateModifiedBlinnPhongTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledModifiedBlinnPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_MODIFIED_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateWardTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledWardTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_WARD, &cs);
	}

	SharedPtr< const PixelShader > CreateWardDuerTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledWardDuerTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_WARD_DUER, &cs);
	}

	SharedPtr< const PixelShader > CreateCookTorranceTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledCookTorranceTSNMPS();
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
		const BufferCompiledShader cs = CreateCompiledGBufferPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_GBUFFER, &cs);
	}

	SharedPtr< const PixelShader > CreateGBufferTSNMPS() {
		const BufferCompiledShader cs = CreateCompiledGBufferTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_GBUFFER_TSNM, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: DeferredShadingPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const PixelShader > CreateDeferredEmissivePS() {
		const BufferCompiledShader cs = CreateCompiledDeferredEmissivePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_EMISSIVE, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredLambertianPS() {
		const BufferCompiledShader cs = CreateCompiledDeferredLambertianPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_LAMBERTIAN, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredPhongPS() {
		const BufferCompiledShader cs = CreateCompiledDeferredPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredModifiedPhongPS() {
		const BufferCompiledShader cs = CreateCompiledDeferredModifiedPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_MODIFIED_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredBlinnPhongPS() {
		const BufferCompiledShader cs = CreateCompiledDeferredBlinnPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredModifiedBlinnPhongPS() {
		const BufferCompiledShader cs = CreateCompiledDeferredModifiedBlinnPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_MODIFIED_BLINN_PHONG, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredWardPS() {
		const BufferCompiledShader cs = CreateCompiledDeferredWardPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_WARD, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredWardDuerPS() {
		const BufferCompiledShader cs = CreateCompiledDeferredWardDuerPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_WARD_DUER, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredCookTorrancePS() {
		const BufferCompiledShader cs = CreateCompiledDeferredCookTorrancePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DEFERRED_COOK_TORRANCE, &cs);
	}

	SharedPtr< const PixelShader > CreateDeferredPS(BRDFType brdf) {
		switch (brdf) {

		case BRDFType::Lambertian:
			return CreateDeferredLambertianPS();
		case BRDFType::Phong:
			return CreateDeferredPhongPS();
		case BRDFType::ModifiedPhong:
			return CreateDeferredModifiedPhongPS();
		case BRDFType::BlinnPhong:
			return CreateDeferredBlinnPhongPS();
		case BRDFType::Ward:
			return CreateDeferredWardPS();
		case BRDFType::WardDuer:
			return CreateDeferredWardDuerPS();
		case BRDFType::CookTorrance:
			return CreateDeferredCookTorrancePS();
		default:
			return CreateDeferredModifiedBlinnPhongPS();
		}
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Primitives
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateFullscreenTriangleVS() {
		const BufferCompiledShader cs = CreateCompiledFullscreenTriangleVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_FULLSCREEN_TRIANGLE, &cs,
										nullptr,
										0);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: SpritePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateSpriteVS() {
		const BufferCompiledShader cs = CreateCompiledSpriteVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_SPRITE, &cs,
										VertexPositionColorTexture::s_input_element_desc,
										VertexPositionColorTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateSpritePS() {
		const BufferCompiledShader cs = CreateCompiledSpritePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_SPRITE, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantComponentPass and VariableComponentPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateMinimalTransformVS() noexcept {
		const BufferCompiledShader cs = CreateCompiledMinimalTransformVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_MINIMAL_TRANSFORM, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateConstantColorPS() noexcept {
		const BufferCompiledShader cs = CreateCompiledConstantColorPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_CONSTANT_COLOR, &cs);
	}

	SharedPtr< const PixelShader > CreateConstantColorTexturePS() noexcept {
		const BufferCompiledShader cs = CreateCompiledConstantColorTexturePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_CONSTANT_COLOR_TEXTURE, &cs);
	}

	SharedPtr< const PixelShader > CreateDistancePS() noexcept {
		const BufferCompiledShader cs = CreateCompiledDistancePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_DISTANCE, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ShadingNormalPass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateShadingNormalVS() noexcept {
		const BufferCompiledShader cs = CreateCompiledShadingNormalVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_SHADING_NORMAL, &cs,
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateShadingNormalPS() noexcept {
		const BufferCompiledShader cs = CreateCompiledShadingNormalPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_SHADING_NORMAL, &cs);
	}

	SharedPtr< const PixelShader > CreateShadingNormalTSNMPS() noexcept {
		const BufferCompiledShader cs = CreateCompiledShadingNormalTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_SHADING_NORMAL, &cs);
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: WireframePass
	//-------------------------------------------------------------------------
#pragma region

	SharedPtr< const VertexShader > CreateBoundingVolumeVS() noexcept {
		const BufferCompiledShader cs = CreateCompiledBoundingVolumeVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_BOUNDING_VOLUME, &cs,
								VertexPosition::s_input_element_desc,
								VertexPosition::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateBoundingVolumePS() noexcept {
		const BufferCompiledShader cs = CreateCompiledBoundingVolumePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_BOUNDING_VOLUME, &cs);
	}

#pragma endregion
}