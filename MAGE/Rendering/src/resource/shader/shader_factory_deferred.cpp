//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\shader\shader_factory.hpp"
#include "resource\mesh\vertex.hpp"

// Deferred: Opaque
#include "deferred\deferred_blinn_phong_CS.hpp"
#include "deferred\deferred_cook_torrance_CS.hpp"
#include "deferred\deferred_emissive_CS.hpp"
#include "deferred\deferred_frostbite_CS.hpp"
#include "deferred\deferred_lambertian_CS.hpp"
// Deferred: Opaque + VCT
#include "deferred\deferred_vct_blinn_phong_CS.hpp"
#include "deferred\deferred_vct_cook_torrance_CS.hpp"
#include "deferred\deferred_vct_frostbite_CS.hpp"
#include "deferred\deferred_vct_lambertian_CS.hpp"
// Deferred MSAA: Opaque
#include "deferred\deferred_msaa_blinn_phong_PS.hpp"
#include "deferred\deferred_msaa_cook_torrance_PS.hpp"
#include "deferred\deferred_msaa_emissive_PS.hpp"
#include "deferred\deferred_msaa_frostbite_PS.hpp"
#include "deferred\deferred_msaa_lambertian_PS.hpp"
// Deferred MSAA: Opaque + VCT
#include "deferred\deferred_msaa_vct_blinn_phong_PS.hpp"
#include "deferred\deferred_msaa_vct_cook_torrance_PS.hpp"
#include "deferred\deferred_msaa_vct_frostbite_PS.hpp"
#include "deferred\deferred_msaa_vct_lambertian_PS.hpp"

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
	// Factory Methods: Deferred
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateDeferredEmissiveCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager, 
						MAGE_SHADER_ARGS(g_deferred_emissive_CS));
	}

	namespace {

		ComputeShaderPtr CreateDeferredBlinnPhongCS(ResourceManager& resource_manager, 
													bool vct) {
		
			return vct ? CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_vct_blinn_phong_CS))
					   : CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_blinn_phong_CS));
		}

		ComputeShaderPtr CreateDeferredCookTorranceCS(ResourceManager& resource_manager, 
													  bool vct) {
		
			return vct ? CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_vct_cook_torrance_CS))
					   : CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_cook_torrance_CS));
		}

		ComputeShaderPtr CreateDeferredFrostbiteCS(ResourceManager& resource_manager, 
												   bool vct) {
		
			return vct ? CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_vct_frostbite_CS))
					   : CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_frostbite_CS));
		}

		ComputeShaderPtr CreateDeferredLambertianCS(ResourceManager& resource_manager, 
													bool vct) {
		
			return vct ? CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_vct_lambertian_CS))
					   : CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_lambertian_CS));
		}
	}

	ComputeShaderPtr CreateDeferredCS(ResourceManager& resource_manager, 
									  BRDF brdf, bool vct) {
		switch (brdf) {

		case BRDF::Lambertian:
			return CreateDeferredLambertianCS(resource_manager, vct);
		case BRDF::BlinnPhong:
			return CreateDeferredBlinnPhongCS(resource_manager, vct);
		case BRDF::CookTorrance:
			return CreateDeferredCookTorranceCS(resource_manager, vct);
		case BRDF::Frostbite:
			return CreateDeferredFrostbiteCS(resource_manager, vct);
		default:
			return nullptr;
		}
	}

	#pragma endregion
	
	//-------------------------------------------------------------------------
	// Factory Methods: Deferred MSAA
	//-------------------------------------------------------------------------
	#pragma region
	
	PixelShaderPtr CreateDeferredMSAAEmissivePS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager,
						MAGE_SHADER_ARGS(g_deferred_msaa_emissive_PS));
	}

	namespace {

		PixelShaderPtr CreateDeferredMSAABlinnPhongPS(ResourceManager& resource_manager,
													  bool vct) {

			return vct ? CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_vct_blinn_phong_PS))
				       : CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_blinn_phong_PS));
		}

		PixelShaderPtr CreateDeferredMSAACookTorrancePS(ResourceManager& resource_manager,
														bool vct) {

			return vct ? CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_vct_cook_torrance_PS))
				       : CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_cook_torrance_PS));
		}


		PixelShaderPtr CreateDeferredMSAAFrostbitePS(ResourceManager& resource_manager,
													 bool vct) {

			return vct ? CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_vct_frostbite_PS))
				       : CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_frostbite_PS));
		}

		PixelShaderPtr CreateDeferredMSAALambertianPS(ResourceManager& resource_manager,
													  bool vct) {

			return vct ? CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_vct_lambertian_PS))
				       : CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_lambertian_PS));
		}
	}

	PixelShaderPtr CreateDeferredMSAAPS(ResourceManager& resource_manager, 
										BRDF brdf, bool vct) {
		switch (brdf) {

		case BRDF::Lambertian:
			return CreateDeferredMSAALambertianPS(resource_manager, vct);
		case BRDF::BlinnPhong:
			return CreateDeferredMSAABlinnPhongPS(resource_manager, vct);
		case BRDF::CookTorrance:
			return CreateDeferredMSAACookTorrancePS(resource_manager, vct);
		case BRDF::Frostbite:
			return CreateDeferredMSAAFrostbitePS(resource_manager, vct);
		default:
			return nullptr;
		}
	}

	#pragma endregion
}