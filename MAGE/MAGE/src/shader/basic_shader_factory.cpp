//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "shader\basic_shader_factory.hpp"
#include "shader\compiled_shader_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CombinedShader CreateEmissiveShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledEmissivePixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateLambertianShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledLambertianPixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreatePhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledPhongPixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedPhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledModifiedPhongPixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateBlinnPhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledBlinnPhongPixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateModifiedBlinnPhongShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledModifiedBlinnPhongPixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledWardPixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateWardDuerShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledWardDuerPixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}

	const CombinedShader CreateCookTorranceShader() {
		const CompiledVertexShader cvs = CreateCompiledTransformVertexShader();
		SharedPtr< VertexShader > vs   = CreateBasicVertexShader(cvs.m_name, cvs);
		
		const CompiledPixelShader cps  = CreateCompiledCookTorrancePixelShader();
		SharedPtr< PixelShader >  ps   = CreateBasicPixelShader(cps.m_name, cps);
		
		return CombinedShader(vs, ps);
	}
}