//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// Depth-of-Field
#include "postprocessing\dof_CS.hpp"
// Low Dynamic Range
#include "postprocessing\ldr_aces_filmic_CS.hpp"
#include "postprocessing\ldr_max3_CS.hpp"
#include "postprocessing\ldr_none_CS.hpp"
#include "postprocessing\ldr_reinhard_CS.hpp"
#include "postprocessing\ldr_uncharted_CS.hpp"

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
	// Factory Methods: Depth-of-Field
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateDepthOfFieldCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager,
						MAGE_SHADER_ARGS(g_dof_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Low Dynamic Range
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateLowDynamicRangeCS(ResourceManager& resource_manager,
											 ToneMapping tone_mapping) {
		switch (tone_mapping) {

		case ToneMapping::None:
			return CreateCS(resource_manager,
							MAGE_SHADER_ARGS(g_ldr_none_CS));
		case ToneMapping::ACESFilmic:
			return CreateCS(resource_manager,
							MAGE_SHADER_ARGS(g_ldr_aces_filmic_CS));
		case ToneMapping::Max3:
			return CreateCS(resource_manager,
							MAGE_SHADER_ARGS(g_ldr_max3_CS));
		case ToneMapping::Reinhard:
			return CreateCS(resource_manager,
							MAGE_SHADER_ARGS(g_ldr_reinhard_CS));
		case ToneMapping::Uncharted:
			return CreateCS(resource_manager,
							MAGE_SHADER_ARGS(g_ldr_uncharted_CS));
		default:
			return nullptr;
		}
	}

	#pragma endregion
}