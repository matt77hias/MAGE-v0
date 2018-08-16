//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// False Color
#include "falsecolor\constant_color_PS.hpp"
#include "falsecolor\constant_color_texture_PS.hpp"
#include "falsecolor\constant_texture_PS.hpp"
#include "falsecolor\base_color_PS.hpp"
#include "falsecolor\base_color_coefficient_PS.hpp"
#include "falsecolor\base_color_texture_PS.hpp"
#include "falsecolor\material_PS.hpp"
#include "falsecolor\material_coefficient_PS.hpp"
#include "falsecolor\material_texture_PS.hpp"
#include "falsecolor\roughness_PS.hpp"
#include "falsecolor\roughness_coefficient_PS.hpp"
#include "falsecolor\roughness_texture_PS.hpp"
#include "falsecolor\metalness_PS.hpp"
#include "falsecolor\metalness_coefficient_PS.hpp"
#include "falsecolor\metalness_texture_PS.hpp"
#include "falsecolor\shading_normal_PS.hpp"
#include "falsecolor\tsnm_shading_normal_PS.hpp"
#include "falsecolor\depth_PS.hpp"
#include "falsecolor\distance_PS.hpp"

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
	// Factory Methods: False Color
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateFalseColorPS(ResourceManager& resource_manager, 
									  FalseColor false_color) {
		switch (false_color) {
			
			case FalseColor::ConstantColor:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_constant_color_PS));
			case FalseColor::UV:
			case FalseColor::ConstantColorTexture:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_constant_texture_PS));
			case FalseColor::BaseColor:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_base_color_PS));
			case FalseColor::BaseColorCoefficient:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_base_color_coefficient_PS));
			case FalseColor::BaseColorTexture:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_base_color_texture_PS));
			case FalseColor::Material:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_material_PS));
			case FalseColor::MaterialCoefficient:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_material_coefficient_PS));
			case FalseColor::MaterialTexture:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_material_texture_PS));
			case FalseColor::Roughness:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_roughness_PS));
			case FalseColor::RoughnessCoefficient:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_roughness_coefficient_PS));
			case FalseColor::RoughnessTexture:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_roughness_texture_PS));
			case FalseColor::Metalness:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_metalness_PS));
			case FalseColor::MetalnessCoefficient:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_metalness_coefficient_PS));
			case FalseColor::MetalnessTexture:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_metalness_texture_PS));
			case FalseColor::ShadingNormal:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_shading_normal_PS));
			case FalseColor::TSNMShadingNormal:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_tsnm_shading_normal_PS));
			case FalseColor::Depth:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_depth_PS));
			case FalseColor::Distance:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_distance_PS));
			default:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_base_color_PS));
		}
	}

	#pragma endregion
}