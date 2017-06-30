//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\sprite_shader_factory.hpp"
#include "shader\compiled_shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "resource\guids.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	const CombinedShader CreateSpriteShader() {
		const CompiledVertexShader cvs = CreateCompiledSpriteVertexShader();
		SharedPtr< VertexShader > vs   = GetOrCreateSpriteVertexShader(MAGE_GUID_VS_SPRITE, cvs);

		const CompiledPixelShader cps  = CreateCompiledSpritePixelShader();
		SharedPtr< PixelShader >  ps   = GetOrCreateSpritePixelShader(MAGE_GUID_PS_SPRITE, cps);

		return CombinedShader(vs, ps);
	}
}