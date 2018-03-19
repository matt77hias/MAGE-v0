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

// Back Buffer
#include "backbuffer\back_buffer_aces_filmic_PS.hpp"
#include "backbuffer\back_buffer_reinhard_PS.hpp"
#include "backbuffer\back_buffer_uncharted_PS.hpp"

// Deferred: Opaque
#include "deferred\deferred_blinn_phong_CS.hpp"
#include "deferred\deferred_cook_torrance_CS.hpp"
#include "deferred\deferred_emissive_CS.hpp"
#include "deferred\deferred_frostbite_CS.hpp"
#include "deferred\deferred_lambertian_CS.hpp"
#include "deferred\deferred_ward_duer_CS.hpp"
// Deferred: Opaque + VCT
#include "deferred\deferred_vct_blinn_phong_CS.hpp"
#include "deferred\deferred_vct_cook_torrance_CS.hpp"
#include "deferred\deferred_vct_frostbite_CS.hpp"
#include "deferred\deferred_vct_lambertian_CS.hpp"
#include "deferred\deferred_vct_ward_duer_CS.hpp"
// Deferred MSAA: Opaque
#include "deferred\deferred_msaa_blinn_phong_PS.hpp"
#include "deferred\deferred_msaa_cook_torrance_PS.hpp"
#include "deferred\deferred_msaa_emissive_PS.hpp"
#include "deferred\deferred_msaa_frostbite_PS.hpp"
#include "deferred\deferred_msaa_lambertian_PS.hpp"
#include "deferred\deferred_msaa_ward_duer_PS.hpp"
// Deferred MSAA: Opaque + VCT
#include "deferred\deferred_msaa_vct_blinn_phong_PS.hpp"
#include "deferred\deferred_msaa_vct_cook_torrance_PS.hpp"
#include "deferred\deferred_msaa_vct_frostbite_PS.hpp"
#include "deferred\deferred_msaa_vct_lambertian_PS.hpp"
#include "deferred\deferred_msaa_vct_ward_duer_PS.hpp"

// Depth: Opaque
#include "depth\depth_VS.hpp"
// Depth: Transparent
#include "depth\depth_transparent_VS.hpp"
#include "depth\depth_transparent_PS.hpp"

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

// GBuffer: Opaque
#include "gbuffer\gbuffer_PS.hpp"
// GBuffer: Opaque + TSNM
#include "gbuffer\gbuffer_tsnm_PS.hpp"

// Post-processing
#include "postprocessing\depth_of_field_CS.hpp"

// Primitive
#include "primitive\line_cube_VS.hpp"
#include "primitive\line_cube_PS.hpp"
#include "primitive\far_fullscreen_triangle_VS.hpp"
#include "primitive\near_fullscreen_triangle_VS.hpp"

// Sky
#include "sky\sky_VS.hpp"
#include "sky\sky_PS.hpp"

// Sprite
#include "sprite\sprite_VS.hpp"
#include "sprite\sprite_PS.hpp"

// Transform
#include "transform\transform_VS.hpp"

// Voxelization
#include "voxelization\voxelization_CS.hpp"
#include "voxelization\voxelization_VS.hpp"
#include "voxelization\voxelization_GS.hpp"
// Voxelization: Opaque
#include "voxelization\voxelization_blinn_phong_PS.hpp"
#include "voxelization\voxelization_cook_torrance_PS.hpp"
#include "voxelization\voxelization_frostbite_PS.hpp"
#include "voxelization\voxelization_lambertian_PS.hpp"
#include "voxelization\voxelization_ward_duer_PS.hpp"
// Voxelization: Opaque + TSNM
#include "voxelization\voxelization_tsnm_blinn_phong_PS.hpp"
#include "voxelization\voxelization_tsnm_cook_torrance_PS.hpp"
#include "voxelization\voxelization_tsnm_frostbite_PS.hpp"
#include "voxelization\voxelization_tsnm_lambertian_PS.hpp"
#include "voxelization\voxelization_tsnm_ward_duer_PS.hpp"

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
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// General Factory Methods
	//-------------------------------------------------------------------------
	namespace {

		/**
		 Creates a vertex shader.
	 
		 @tparam		ConstructorArgsT
						The constructor argument types of the vertex shader.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		args
						A reference to the constructor arguments for the vertex 
						shader.
		 @return		A pointer to the vertex shader.
		 @throws		Exception
						Failed to create the vertex shader.
		 */
		template< typename... ConstructorArgsT >
		[[nodiscard]]
		inline VertexShaderPtr CreateVS(ResourceManager& resource_manager, 
										ConstructorArgsT&&... args) {
		
			return resource_manager.GetOrCreate< VertexShader >(
									std::forward< ConstructorArgsT >(args)...);
		}

		/**
		 Creates a hull shader.
	 
		 @tparam		ConstructorArgsT
						The constructor argument types of the hull shader.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		args
						A reference to the constructor arguments for the hull 
						shader.
		 @return		A pointer to the hull shader.
		 @throws		Exception
						Failed to create the hull shader.
		 */
		template< typename... ConstructorArgsT >
		[[nodiscard]]
		inline HullShaderPtr CreateHS(ResourceManager& resource_manager, 
									  ConstructorArgsT&&... args) {
		
			return resource_manager.GetOrCreate< HullShader >(
									std::forward< ConstructorArgsT >(args)...);
		}

		/**
		 Creates a domain shader.
	 
		 @tparam		ConstructorArgsT
						The constructor argument types of the domain shader.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		args
						A reference to the constructor arguments for the domain 
						shader.
		 @return		A pointer to the domain shader.
		 @throws		Exception
						Failed to create the domain shader.
		 */
		template< typename... ConstructorArgsT >
		[[nodiscard]]
		inline DomainShaderPtr CreateDS(ResourceManager& resource_manager, 
										ConstructorArgsT&&... args) {
		
			return resource_manager.GetOrCreate< DomainShader >(
									std::forward< ConstructorArgsT >(args)...);
		}

		/**
		 Creates a geometry shader.
	 
		 @tparam		ConstructorArgsT
						The constructor argument types of the geometry shader.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		args
						A reference to the constructor arguments for the geometry 
						shader.
		 @return		A pointer to the geometry shader.
		 @throws		Exception
						Failed to create the geometry shader.
		 */
		template< typename... ConstructorArgsT >
		[[nodiscard]]
		inline GeometryShaderPtr CreateGS(ResourceManager& resource_manager, 
										  ConstructorArgsT&&... args) {
		
			return resource_manager.GetOrCreate< GeometryShader >(
									std::forward< ConstructorArgsT >(args)...);
		}

		/**
		 Creates a pixel shader.
	 
		 @tparam		ConstructorArgsT
						The constructor argument types of the pixel shader.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		args
						A reference to the constructor arguments for the pixel 
						shader.
		 @return		A pointer to the pixel shader.
		 @throws		Exception
						Failed to create the pixel shader.
		 */
		template< typename... ConstructorArgsT >
		[[nodiscard]]
		inline PixelShaderPtr CreatePS(ResourceManager& resource_manager, 
									   ConstructorArgsT&&... args) {
		
			return resource_manager.GetOrCreate< PixelShader >(
									std::forward< ConstructorArgsT >(args)...);
		}

		/**
		 Creates a compute shader.
	 
		 @tparam		ConstructorArgsT
						The constructor argument types of the compute shader.
		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		args
						A reference to the constructor arguments for the compute 
						shader.
		 @return		A pointer to the compute shader.
		 @throws		Exception
						Failed to create the compute shader.
		 */
		template< typename... ConstructorArgsT >
		[[nodiscard]]
		inline ComputeShaderPtr CreateCS(ResourceManager& resource_manager, 
										 ConstructorArgsT&&... args) {
		
			return resource_manager.GetOrCreate< ComputeShader >(
									std::forward< ConstructorArgsT >(args)...);
		}

	}

	//-------------------------------------------------------------------------
	// Factory Methods: Anti-aliasing
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

	ComputeShaderPtr CreateMSAAResolveCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager, 
						MAGE_SHADER_ARGS(g_msaa_resolve_CS));
	}

	ComputeShaderPtr CreateSSAAResolveCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager, 
						MAGE_SHADER_ARGS(g_ssaa_resolve_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Back Buffer
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateBackBufferPS(ResourceManager& resource_manager, 
									  ToneMapping tone_mapping) {
		
		switch (tone_mapping) {

		case ToneMapping::ACESFilmic:
			return CreatePS(resource_manager,
							MAGE_SHADER_ARGS(g_back_buffer_aces_filmic_PS));
		case ToneMapping::Reinhard:
			return CreatePS(resource_manager,
							MAGE_SHADER_ARGS(g_back_buffer_reinhard_PS));
		case ToneMapping::Uncharted:
			return CreatePS(resource_manager,
							MAGE_SHADER_ARGS(g_back_buffer_uncharted_PS));
		default:
			return CreatePS(resource_manager,
							MAGE_SHADER_ARGS(g_back_buffer_uncharted_PS));
		}
	}

	#pragma endregion
	
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

		ComputeShaderPtr CreateDeferredWardDuerCS(ResourceManager& resource_manager, 
												  bool vct) {
		
			return vct ? CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_vct_ward_duer_CS))
					   : CreateCS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_ward_duer_CS));
		}
	}

	ComputeShaderPtr CreateDeferredCS(ResourceManager& resource_manager, 
									  BRDF brdf, bool vct) {
		switch (brdf) {

		case BRDF::BlinnPhong:
			return CreateDeferredBlinnPhongCS(resource_manager, vct);
		case BRDF::CookTorrance:
			return CreateDeferredCookTorranceCS(resource_manager, vct);
		case BRDF::Lambertian:
			return CreateDeferredLambertianCS(resource_manager, vct);
		case BRDF::WardDuer:
			return CreateDeferredWardDuerCS(resource_manager, vct);
		default:
			return CreateDeferredFrostbiteCS(resource_manager, vct);
		}
	}

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

		PixelShaderPtr CreateDeferredMSAAWardDuerPS(ResourceManager& resource_manager,
													bool vct) {

			return vct ? CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_vct_ward_duer_PS)) 
				       : CreatePS(resource_manager, 
								  MAGE_SHADER_ARGS(g_deferred_msaa_ward_duer_PS));
		}
	}

	PixelShaderPtr CreateDeferredMSAAPS(ResourceManager& resource_manager, 
										BRDF brdf, bool vct) {
		switch (brdf) {

		case BRDF::BlinnPhong:
			return CreateDeferredMSAABlinnPhongPS(resource_manager, vct);
		case BRDF::CookTorrance:
			return CreateDeferredMSAACookTorrancePS(resource_manager, vct);
		case BRDF::Lambertian:
			return CreateDeferredMSAALambertianPS(resource_manager, vct);
		case BRDF::WardDuer:
			return CreateDeferredMSAAWardDuerPS(resource_manager, vct);
		default:
			return CreateDeferredMSAAFrostbitePS(resource_manager, vct);
		}
	}

	#pragma endregion

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

		case BRDF::BlinnPhong:
			return CreateForwardBlinnPhongPS(resource_manager, transparency, vct, tsnm);
		case BRDF::CookTorrance:
			return CreateForwardCookTorrancePS(resource_manager, transparency, vct, tsnm);
		case BRDF::Lambertian:
			return CreateForwardLambertianPS(resource_manager, transparency, vct, tsnm);
		case BRDF::WardDuer:
			return CreateForwardWardDuerPS(resource_manager, transparency, vct, tsnm);
		default:
			return CreateForwardFrostbitePS(resource_manager, transparency, vct, tsnm);
		}
	}

	PixelShaderPtr CreateForwardSolidPS(ResourceManager& resource_manager) {
		return CreatePS(resource_manager, 
						MAGE_SHADER_ARGS(g_forward_solid_PS));
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
	// Factory Methods: Post-processing
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateDepthOfFieldCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager, 
						MAGE_SHADER_ARGS(g_depth_of_field_CS));
	}

	#pragma endregion

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
		using vertex_t = VertexPositionNormalTexture;
		return CreateVS(resource_manager, 
						MAGE_SHADER_ARGS(g_transform_VS), 
						gsl::make_span(vertex_t::s_input_element_descs));
	}

	#pragma endregion

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

	namespace {

		PixelShaderPtr CreateVoxelizationBlinnPhongPS(ResourceManager& resource_manager, 
													  bool tsnm) {

			return tsnm ? CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_tsnm_blinn_phong_PS))
						: CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_blinn_phong_PS));
		}

		PixelShaderPtr CreateVoxelizationCookTorrancePS(ResourceManager& resource_manager, 
														bool tsnm) {

			return tsnm ? CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_tsnm_cook_torrance_PS))
						: CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_cook_torrance_PS));
		}

		PixelShaderPtr CreateVoxelizationFrostbitePS(ResourceManager& resource_manager, 
													 bool tsnm) {

			return tsnm ? CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_tsnm_frostbite_PS))
						: CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_frostbite_PS));
		}

		PixelShaderPtr CreateVoxelizationLambertianPS(ResourceManager& resource_manager, 
													  bool tsnm) {

			return tsnm ? CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_tsnm_lambertian_PS))
						: CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_lambertian_PS));
		}

		PixelShaderPtr CreateVoxelizationWardDuerPS(ResourceManager& resource_manager, 
													bool tsnm) {

			return tsnm ? CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_tsnm_ward_duer_PS))
						: CreatePS(resource_manager, 
								   MAGE_SHADER_ARGS(g_voxelization_ward_duer_PS));
		}
	}

	PixelShaderPtr CreateVoxelizationPS(ResourceManager& resource_manager, 
										BRDF brdf, bool tsnm) {
		switch (brdf) {

		case BRDF::BlinnPhong:
			return CreateVoxelizationBlinnPhongPS(resource_manager, tsnm);
		case BRDF::CookTorrance:
			return CreateVoxelizationCookTorrancePS(resource_manager, tsnm);
		case BRDF::Lambertian:
			return CreateVoxelizationLambertianPS(resource_manager, tsnm);
		case BRDF::WardDuer:
			return CreateVoxelizationWardDuerPS(resource_manager, tsnm);
		default:
			return CreateVoxelizationFrostbitePS(resource_manager, tsnm);
		}
	}

	ComputeShaderPtr CreateVoxelizationCS(ResourceManager& resource_manager) {
		return CreateCS(resource_manager, 
						MAGE_SHADER_ARGS(g_voxelization_CS));
	}

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