//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

#include "forward\forward_solid_PS.hpp"
// Forward: Opaque
#include "forward\forward_blinn_phong_PS.hpp"
#include "forward\forward_cook_torrance_PS.hpp"
#include "forward\forward_emissive_PS.hpp"
#include "forward\forward_frostbite_PS.hpp"
#include "forward\forward_lambertian_PS.hpp"
#include "forward\forward_ward_duer_PS.hpp"
// Forward: Opaque + VCT
#include "forward\forward_vct_blinn_phong_PS.hpp"
#include "forward\forward_vct_cook_torrance_PS.hpp"
#include "forward\forward_vct_frostbite_PS.hpp"
#include "forward\forward_vct_lambertian_PS.hpp"
#include "forward\forward_vct_ward_duer_PS.hpp"
// Forward: Opaque + TSNM
#include "forward\forward_tsnm_blinn_phong_PS.hpp"
#include "forward\forward_tsnm_cook_torrance_PS.hpp"
#include "forward\forward_tsnm_frostbite_PS.hpp"
#include "forward\forward_tsnm_lambertian_PS.hpp"
#include "forward\forward_tsnm_ward_duer_PS.hpp"
// Forward: Opaque + VCT + TSNM
#include "forward\forward_vct_tsnm_blinn_phong_PS.hpp"
#include "forward\forward_vct_tsnm_cook_torrance_PS.hpp"
#include "forward\forward_vct_tsnm_frostbite_PS.hpp"
#include "forward\forward_vct_tsnm_lambertian_PS.hpp"
#include "forward\forward_vct_tsnm_ward_duer_PS.hpp"
// Forward: Transparent
#include "forward\forward_transparent_blinn_phong_PS.hpp"
#include "forward\forward_transparent_cook_torrance_PS.hpp"
#include "forward\forward_transparent_emissive_PS.hpp"
#include "forward\forward_transparent_frostbite_PS.hpp"
#include "forward\forward_transparent_lambertian_PS.hpp"
#include "forward\forward_transparent_ward_duer_PS.hpp"
// Forward: Transparent + VCT
#include "forward\forward_transparent_vct_blinn_phong_PS.hpp"
#include "forward\forward_transparent_vct_cook_torrance_PS.hpp"
#include "forward\forward_transparent_vct_frostbite_PS.hpp"
#include "forward\forward_transparent_vct_lambertian_PS.hpp"
#include "forward\forward_transparent_vct_ward_duer_PS.hpp"
// Forward: Transparent + TSNM
#include "forward\forward_transparent_tsnm_blinn_phong_PS.hpp"
#include "forward\forward_transparent_tsnm_cook_torrance_PS.hpp"
#include "forward\forward_transparent_tsnm_frostbite_PS.hpp"
#include "forward\forward_transparent_tsnm_lambertian_PS.hpp"
#include "forward\forward_transparent_tsnm_ward_duer_PS.hpp"
// Forward: Transparent + VCT + TSNM
#include "forward\forward_transparent_vct_tsnm_blinn_phong_PS.hpp"
#include "forward\forward_transparent_vct_tsnm_cook_torrance_PS.hpp"
#include "forward\forward_transparent_vct_tsnm_frostbite_PS.hpp"
#include "forward\forward_transparent_vct_tsnm_lambertian_PS.hpp"
#include "forward\forward_transparent_vct_tsnm_ward_duer_PS.hpp"

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
	// Factory Methods: Forward
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateForwardEmissivePS(ResourceManager& resource_manager, 
										   bool transparency) {

		return transparency ? CreatePS(resource_manager, 
									   MAGE_SHADER_ARGS(g_forward_transparent_emissive_PS))
		                    : CreatePS(resource_manager, 
									   MAGE_SHADER_ARGS(g_forward_emissive_PS));
	}

	namespace {

		PixelShaderPtr CreateForwardBlinnPhongPS(ResourceManager& resource_manager, 
												 bool transparency,
												 bool vct, 
												 bool tsnm) {

			const auto config = static_cast< U32 >(transparency) << 2u
							  | static_cast< U32 >(vct)          << 1u
							  | static_cast< U32 >(tsnm);
		
			switch(config) {
			
			case 0b000:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_blinn_phong_PS));
			case 0b001:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_tsnm_blinn_phong_PS));
			case 0b010:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_blinn_phong_PS));
			case 0b011:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_tsnm_blinn_phong_PS));
			case 0b100:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_blinn_phong_PS));
			case 0b101:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_tsnm_blinn_phong_PS));
			case 0b110:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_blinn_phong_PS));
			case 0b111:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_blinn_phong_PS));
			default:
				return nullptr;
			}
		}

		PixelShaderPtr CreateForwardCookTorrancePS(ResourceManager& resource_manager, 
												   bool transparency,
												   bool vct, 
												   bool tsnm) {
		
			const auto config = static_cast< U32 >(transparency) << 2u
							  | static_cast< U32 >(vct)          << 1u
							  | static_cast< U32 >(tsnm);
		
			switch(config) {
			
			case 0b000:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_cook_torrance_PS));
			case 0b001:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_tsnm_cook_torrance_PS));
			case 0b010:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_cook_torrance_PS));
			case 0b011:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_tsnm_cook_torrance_PS));
			case 0b100:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_cook_torrance_PS));
			case 0b101:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_tsnm_cook_torrance_PS));
			case 0b110:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_cook_torrance_PS));
			case 0b111:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_cook_torrance_PS));
			default:
				return nullptr;
			}
		}

	
		PixelShaderPtr CreateForwardFrostbitePS(ResourceManager& resource_manager, 
												bool transparency,
												bool vct, 
												bool tsnm) {
		
			const auto config = static_cast< U32 >(transparency) << 2u
							  | static_cast< U32 >(vct)          << 1u
							  | static_cast< U32 >(tsnm);
		
			switch(config) {
			
			case 0b000:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_frostbite_PS));
			case 0b001:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_tsnm_frostbite_PS));
			case 0b010:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_frostbite_PS));
			case 0b011:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_tsnm_frostbite_PS));
			case 0b100:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_frostbite_PS));
			case 0b101:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_tsnm_frostbite_PS));
			case 0b110:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_frostbite_PS));
			case 0b111:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_frostbite_PS));
			default:
				return nullptr;
			}
		}

		PixelShaderPtr CreateForwardLambertianPS(ResourceManager& resource_manager, 
												 bool transparency,
												 bool vct, 
												 bool tsnm) {
		
			const auto config = static_cast< U32 >(transparency) << 2u
							  | static_cast< U32 >(vct)          << 1u
							  | static_cast< U32 >(tsnm);
		
			switch(config) {
			
			case 0b000:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_lambertian_PS));
			case 0b001:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_tsnm_lambertian_PS));
			case 0b010:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_lambertian_PS));
			case 0b011:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_tsnm_lambertian_PS));
			case 0b100:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_lambertian_PS));
			case 0b101:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_tsnm_lambertian_PS));
			case 0b110:
				return CreatePS(resource_manager,
								MAGE_SHADER_ARGS(g_forward_transparent_vct_lambertian_PS));
			case 0b111:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_lambertian_PS));
			default:
				return nullptr;
			}
		}

		PixelShaderPtr CreateForwardWardDuerPS(ResourceManager& resource_manager, 
											   bool transparency,
											   bool vct, 
											   bool tsnm) {
		
			const auto config = static_cast< U32 >(transparency) << 2u
							  | static_cast< U32 >(vct)          << 1u
							  | static_cast< U32 >(tsnm);
		
			switch(config) {
			
			case 0b000:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_ward_duer_PS));
			case 0b001:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_tsnm_ward_duer_PS));
			case 0b010:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_ward_duer_PS));
			case 0b011:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_vct_tsnm_ward_duer_PS));
			case 0b100:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_ward_duer_PS));
			case 0b101:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_tsnm_ward_duer_PS));
			case 0b110:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_ward_duer_PS));
			case 0b111:
				return CreatePS(resource_manager, 
								MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_ward_duer_PS));
			default:
				return nullptr;
			}
		}
	}

	PixelShaderPtr CreateForwardPS(ResourceManager& resource_manager, 
								   BRDF brdf,
								   bool transparency, 
								   bool vct, 
								   bool tsnm) {
		
		switch (brdf) {

		case BRDF::Lambertian:
			return CreateForwardLambertianPS(resource_manager, transparency, vct, tsnm);
		case BRDF::BlinnPhong:
			return CreateForwardBlinnPhongPS(resource_manager, transparency, vct, tsnm);
		case BRDF::CookTorrance:
			return CreateForwardCookTorrancePS(resource_manager, transparency, vct, tsnm);
		case BRDF::Frostbite:
			return CreateForwardFrostbitePS(resource_manager, transparency, vct, tsnm);
		case BRDF::WardDuer:
			return CreateForwardWardDuerPS(resource_manager, transparency, vct, tsnm);
		default:
			return nullptr;
		}
	}

	PixelShaderPtr CreateForwardSolidPS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager, 
						MAGE_SHADER_ARGS(g_forward_solid_PS));
	}

	#pragma endregion
}