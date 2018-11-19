//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// Back Buffer
#include "backbuffer\back_buffer_PS.hpp"

// GBuffer: Opaque
#include "gbuffer\gbuffer_PS.hpp"
// GBuffer: Opaque + TSNM
#include "gbuffer\gbuffer_tsnm_PS.hpp"

// Sky
#include "sky\sky_VS.hpp"
#include "sky\sky_PS.hpp"

// Sprite
#include "sprite\sprite_VS.hpp"
#include "sprite\sprite_PS.hpp"

// Transform
#include "transform\transform_VS.hpp"

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
	// Factory Methods: Back Buffer
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateBackBufferPS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager,
						MAGE_SHADER_ARGS(g_back_buffer_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBuffer
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateGBufferPS(ResourceManager& resource_manager,
								   bool tsnm) {

		return tsnm ? CreatePS(resource_manager,
							   MAGE_SHADER_ARGS(g_gbuffer_tsnm_PS))
			        : CreatePS(resource_manager,
							   MAGE_SHADER_ARGS(g_gbuffer_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sky
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateSkyVS(ResourceManager& resource_manager) {
		return CreateVS(resource_manager,
						MAGE_SHADER_ARGS(g_sky_VS),
						gsl::span< const D3D11_INPUT_ELEMENT_DESC >());
	}

	PixelShaderPtr CreateSkyPS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager,
						MAGE_SHADER_ARGS(g_sky_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sprite
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateSpriteVS(ResourceManager& resource_manager) {
		return CreateVS(resource_manager,
						MAGE_SHADER_ARGS(g_sprite_VS),
						VertexPositionColorTexture::s_input_element_descs);
	}

	PixelShaderPtr CreateSpritePS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager,
						MAGE_SHADER_ARGS(g_sprite_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Transform
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateTransformVS(ResourceManager& resource_manager) {
		using Vertex = VertexPositionNormalTexture;
		return CreateVS(resource_manager,
						MAGE_SHADER_ARGS(g_transform_VS),
						gsl::make_span(Vertex::s_input_element_descs));
	}

	#pragma endregion
}