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
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledEmissivePixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_EMISSIVE, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateLambertianShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledLambertianPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_LAMBERTIAN, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledPhongPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_PHONG, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledModifiedPhongPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_MODIFIED_PHONG, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledBlinnPhongPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_BLINN_PHONG, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledModifiedBlinnPhongPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_MODIFIED_BLINN_PHONG, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledWardPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_WARD, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledWardDuerPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_WARD_DUER, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledCookTorrancePixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateBasicPixelShader(MAGE_GUID_PS_COOK_TORRANCE, cps);
		
		return CombinedShader(vs, ps);
	}
}