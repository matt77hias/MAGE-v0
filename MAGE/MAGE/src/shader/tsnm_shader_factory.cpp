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
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledLambertianTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_LAMBERTIAN, cps.get());

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongTSNMShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_PHONG, cps.get());

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongTSNMShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledModifiedPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_MODIFIED_PHONG, cps.get());

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongTSNMShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledBlinnPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_BLINN_PHONG, cps.get());

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongTSNMShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledModifiedBlinnPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_MODIFIED_BLINN_PHONG, cps.get());

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardTSNMShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledWardTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_WARD, cps.get());

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerTSNMShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledWardDuerTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_WARD_DUER, cps.get());

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceTSNMShader() {
		UniquePtr< CompiledShader > cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs    = GetOrCreateBasicVertexShader(MAGE_GUID_VS_TRANSFORM, cvs.get());

		UniquePtr< CompiledShader > cps = CreateCompiledCookTorranceTSNMPixelShader();
		SharedPtr< PixelShader >  ps    = GetOrCreateTSNMPixelShader(MAGE_GUID_PS_TSNM_COOK_TORRANCE, cps.get());

		return CombinedShader(vs, ps);
	}
}