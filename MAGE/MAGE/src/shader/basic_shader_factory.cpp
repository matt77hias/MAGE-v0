//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\basic_shader_factory.hpp"
#include "shader\compiled_shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "resource\guids.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CombinedShader CreateEmissiveShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledEmissivePixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_EMISSIVE, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateLambertianShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledLambertianPixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_LAMBERTIAN, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledPhongPixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_PHONG, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledModifiedPhongPixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_MODIFIED_PHONG, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledBlinnPhongPixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_BLINN_PHONG, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledModifiedBlinnPhongPixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_MODIFIED_BLINN_PHONG, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledWardPixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_WARD, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledWardDuerPixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_WARD_DUER, cps.get());
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = ResourceManager::Get()->GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());
		
		UniquePtr< CompiledShader > cps = CreateCompiledCookTorrancePixelShader();
		SharedPtr< PixelShader >  ps    = ResourceManager::Get()->GetOrCreateBasicPixelShader(MAGE_GUID_PS_COOK_TORRANCE, cps.get());
		
		return CombinedShader(vs, ps);
	}
}