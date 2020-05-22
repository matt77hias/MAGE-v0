//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// FXAA
#include "aa\aa_preprocess_CS.hpp"
#include "aa\fxaa_CS.hpp"
// MSAA
#include "aa\msaa_resolve_CS.hpp"
// SSAA
#include "aa\ssaa_resolve_CS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_SHADER_GUID(buffer) L#buffer
#define MAGE_SHADER_ARGS(buffer) MAGE_SHADER_GUID(buffer), \
								 BufferCompiledShader(buffer)

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Factory Methods: FXAA
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateAAPreprocessCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager,
						MAGE_SHADER_ARGS(g_aa_preprocess_CS));
	}

	ComputeShaderPtr CreateFXAACS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager,
						MAGE_SHADER_ARGS(g_fxaa_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: MSAA
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateMSAAResolveCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager,
						MAGE_SHADER_ARGS(g_msaa_resolve_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: SSAA
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateSSAAResolveCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager,
						MAGE_SHADER_ARGS(g_ssaa_resolve_CS));
	}

	#pragma endregion
}