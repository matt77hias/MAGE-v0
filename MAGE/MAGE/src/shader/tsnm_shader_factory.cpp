//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\tsnm_shader_factory.hpp"
#include "shader\compiled_shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "resource\guids.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CombinedShader CreateLambertianTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledLambertianTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_LAMBERTIAN, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_PHONG, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledModifiedPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_MODIFIED_PHONG, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledBlinnPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_BLINN_PHONG, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledModifiedBlinnPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_MODIFIED_BLINN_PHONG, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledWardTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_WARD, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledWardDuerTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_WARD_DUER, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs);

		const CompiledPixelShader cps  = CreateCompiledCookTorranceTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_COOK_TORRANCE, cps);

		return CombinedShader(vs, ps);
	}
}