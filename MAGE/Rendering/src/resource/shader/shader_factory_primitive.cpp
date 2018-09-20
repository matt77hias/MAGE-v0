//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// Primitive
#include "primitive\line_cube_VS.hpp"
#include "primitive\line_cube_PS.hpp"
#include "primitive\far_fullscreen_triangle_VS.hpp"
#include "primitive\near_fullscreen_triangle_VS.hpp"

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
	// Factory Methods: Primitive
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateLineCubeVS(ResourceManager& resource_manager) {
		return CreateVS(resource_manager,
						MAGE_SHADER_ARGS(g_line_cube_VS),
						gsl::span< const D3D11_INPUT_ELEMENT_DESC >());
	}

	PixelShaderPtr CreateLineCubePS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager,
						MAGE_SHADER_ARGS(g_line_cube_PS));
	}

	VertexShaderPtr CreateFarFullscreenTriangleVS(ResourceManager& resource_manager) {
		return CreateVS(resource_manager,
						MAGE_SHADER_ARGS(g_far_fullscreen_triangle_VS),
						gsl::span< const D3D11_INPUT_ELEMENT_DESC >());
	}

	VertexShaderPtr CreateNearFullscreenTriangleVS(ResourceManager& resource_manager) {
		return CreateVS(resource_manager,
						MAGE_SHADER_ARGS(g_near_fullscreen_triangle_VS),
						gsl::span< const D3D11_INPUT_ELEMENT_DESC >());
	}

	#pragma endregion
}