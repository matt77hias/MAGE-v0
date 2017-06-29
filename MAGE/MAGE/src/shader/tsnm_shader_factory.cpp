//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "shader\tsnm_shader_factory.hpp"
#include "shader\compiled_shader_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CombinedShader CreateLambertianTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledLambertianTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledModifiedPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledBlinnPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledModifiedBlinnPhongTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledWardTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledWardDuerTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceTSNMShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateTSNMVertexShader(cvs.m_name, cvs);

		const CompiledPixelShader cps  = CreateCompiledCookTorranceTSNMPixelShader();
		SharedPtr< PixelShader >  ps   = CreateTSNMPixelShader(cps.m_name, cps);

		return CombinedShader(vs, ps);
	}
}