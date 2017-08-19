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

	SharedPtr< const VertexShader > CreateTransformVS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledTransformVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_TRANSFORM, cs.get(),
								VertexPositionNormalTexture::s_input_element_desc,
								VertexPositionNormalTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateEmissivePS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledEmissivePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_EMISSIVE, cs.get());
	}

	SharedPtr< const PixelShader > CreateLambertianPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledLambertianPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_LAMBERTIAN, cs.get());
	}

	SharedPtr< const PixelShader > CreatePhongPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateModifiedPhongPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledModifiedPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_MODIFIED_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateBlinnPhongPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledBlinnPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_BLINN_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateModifiedBlinnPhongPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledModifiedBlinnPhongPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_MODIFIED_BLINN_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateWardPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledWardPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_WARD, cs.get());
	}

	SharedPtr< const PixelShader > CreateWardDuerPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledWardDuerPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_WARD_DUER, cs.get());
	}

	SharedPtr< const PixelShader > CreateCookTorrancePS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledCookTorrancePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_COOK_TORRANCE, cs.get());
	}
	
	SharedPtr< const PixelShader > CreateLambertianTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledLambertianTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_LAMBERTIAN, cs.get());
	}

	SharedPtr< const PixelShader > CreatePhongTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateModifiedPhongTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledModifiedPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_MODIFIED_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateBlinnPhongTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledBlinnPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_BLINN_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateModifiedBlinnPhongTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledModifiedBlinnPhongTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_MODIFIED_BLINN_PHONG, cs.get());
	}

	SharedPtr< const PixelShader > CreateWardTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledWardTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_WARD, cs.get());
	}

	SharedPtr< const PixelShader > CreateWardDuerTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledWardDuerTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_WARD_DUER, cs.get());
	}

	SharedPtr< const PixelShader > CreateCookTorranceTSNMPS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledCookTorranceTSNMPS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_TSNM_COOK_TORRANCE, cs.get());
	}

	SharedPtr< const VertexShader > CreateSpriteVS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledSpriteVS();
		return ResourceManager::Get()->GetOrCreateVS(MAGE_GUID_VS_SPRITE, cs.get(),
										VertexPositionColorTexture::s_input_element_desc,
										VertexPositionColorTexture::s_nb_input_elements);
	}

	SharedPtr< const PixelShader > CreateSpritePS() {
		UniquePtr< const CompiledShader > cs = CreateCompiledSpritePS();
		return ResourceManager::Get()->GetOrCreatePS(MAGE_GUID_PS_SPRITE, cs.get());
	}
}