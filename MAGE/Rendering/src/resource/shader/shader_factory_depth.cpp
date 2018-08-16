//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// Depth: Opaque
#include "depth\depth_VS.hpp"
// Depth: Transparent
#include "depth\depth_transparent_VS.hpp"
#include "depth\depth_transparent_PS.hpp"

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
	// Factory Methods: Depth
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateDepthVS(ResourceManager& resource_manager) {
		using vertex_t = VertexPositionNormalTexture;
		return CreateVS(resource_manager, 
						MAGE_SHADER_ARGS(g_depth_VS), 
						gsl::make_span(vertex_t::s_input_element_descs));
	}

	VertexShaderPtr CreateDepthTransparentVS(ResourceManager& resource_manager) {
		using vertex_t = VertexPositionNormalTexture;
		return CreateVS(resource_manager, 
						MAGE_SHADER_ARGS(g_depth_transparent_VS), 
						gsl::make_span(vertex_t::s_input_element_descs));
	}

	PixelShaderPtr CreateDepthTransparentPS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager, 
						MAGE_SHADER_ARGS(g_depth_transparent_PS));
	}

	#pragma endregion
}