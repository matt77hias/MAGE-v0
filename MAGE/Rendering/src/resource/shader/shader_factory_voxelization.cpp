//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// Voxelization
#include "voxelization\voxelization_CS.hpp"
#include "voxelization\voxelization_VS.hpp"
#include "voxelization\voxelization_GS.hpp"
// Voxelization: Opaque
#include "voxelization\voxelization_emissive_PS.hpp"
#include "voxelization\voxelization_lambertian_PS.hpp"
// Voxelization: Opaque + TSNM
#include "voxelization\voxelization_tsnm_lambertian_PS.hpp"
// Voxel Grid
#include "voxelization\voxel_grid_VS.hpp"
#include "voxelization\voxel_grid_GS.hpp"
#include "voxelization\voxel_grid_PS.hpp"

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
	// Factory Methods: Voxelization
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateVoxelizationVS(ResourceManager& resource_manager) {
		using vertex_t = VertexPositionNormalTexture;
		return CreateVS(resource_manager, 
						MAGE_SHADER_ARGS(g_voxelization_VS), 
						gsl::make_span(vertex_t::s_input_element_descs));
	}

	GeometryShaderPtr CreateVoxelizationGS(ResourceManager& resource_manager) {
		return CreateGS(resource_manager, 
						MAGE_SHADER_ARGS(g_voxelization_GS));
	}

	PixelShaderPtr CreateVoxelizationEmissivePS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager,
						MAGE_SHADER_ARGS(g_voxelization_emissive_PS));
	}

	PixelShaderPtr CreateVoxelizationPS(ResourceManager& resource_manager, 
										bool tsnm) {

		return tsnm ? CreatePS(resource_manager, 
							   MAGE_SHADER_ARGS(g_voxelization_tsnm_lambertian_PS))
			        : CreatePS(resource_manager, 
							   MAGE_SHADER_ARGS(g_voxelization_lambertian_PS));
	}

	ComputeShaderPtr CreateVoxelizationCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager, 
						MAGE_SHADER_ARGS(g_voxelization_CS));
	}
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Voxel Grid
	//-------------------------------------------------------------------------
	#pragma region
	
	VertexShaderPtr CreateVoxelGridVS(ResourceManager& resource_manager) {
		return CreateVS(resource_manager, 
						MAGE_SHADER_ARGS(g_voxel_grid_VS), 
						gsl::span< const D3D11_INPUT_ELEMENT_DESC >());
	}

	GeometryShaderPtr CreateVoxelGridGS(ResourceManager& resource_manager) {
		return CreateGS(resource_manager, 
						MAGE_SHADER_ARGS(g_voxel_grid_GS));
	}

	PixelShaderPtr CreateVoxelGridPS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager, 
						MAGE_SHADER_ARGS(g_voxel_grid_PS));
	}

	#pragma endregion
}