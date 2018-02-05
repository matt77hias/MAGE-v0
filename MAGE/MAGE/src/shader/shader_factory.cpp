//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader_factory.hpp"
#include "resource\resource_manager.hpp"
#include "mesh\vertex.hpp"

// FXAA
#include "aa\aa_preprocess_CS.hpp"
#include "aa\fxaa_CS.hpp"
// MSAA
#include "aa\msaa_resolve_CS.hpp"
// SSAA
#include "aa\ssaa_resolve_CS.hpp"

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

// Miscellaneous
#include "miscellaneous\back_buffer_PS.hpp"
#include "miscellaneous\distance_PS.hpp"
#include "miscellaneous\constant_color_PS.hpp"
#include "miscellaneous\constant_color_texture_PS.hpp"
#include "miscellaneous\shading_normal_VS.hpp"
#include "miscellaneous\shading_normal_PS.hpp"
#include "miscellaneous\tsnm_shading_normal_PS.hpp"

// Post-processing
#include "postprocessing\postprocessing_depth_of_field_CS.hpp"

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
#include "transform\minimal_transform_VS.hpp"
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

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_SHADER_GUID(buffer) L#buffer
#define MAGE_SHADER_ARGS(buffer) MAGE_SHADER_GUID(buffer), \
								 BufferCompiledShader(buffer, sizeof(buffer))

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Note: All factory methods could be made lazy. This will not result in 
	//       performance gains since BufferCompiledShaders are not expensive to 
	//       create. 

	/**
	 Creates a shader of the given type.

	 @tparam		ShaderT
					The shader type.
	 @tparam		ConstructorArgsT
					The constructor argument types of the shader.
	 @param[in]		args
					A reference to the constructor arguments for the shader.
	 @return		A pointer to the shader.
	 @throws		Exception
					Failed to create the shader.
	 */
	template< typename ShaderT, typename... ConstructorArgsT >
	static inline SharedPtr< const ShaderT > Create(ConstructorArgsT &&...args) {
		
		// All factory methods could be made lazy. This will not result in 
		// performance gains since BufferCompiledShaders are not expensive to 
		// create. 
		
		return ResourceManager::Get()->GetOrCreate< ShaderT >(
			                           std::forward< ConstructorArgsT >(args)...);
	}

	//-------------------------------------------------------------------------
	// Factory Methods: AA
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateAAPreprocessCS() {
		return Create< ComputeShader >(MAGE_SHADER_ARGS(g_aa_preprocess_CS));
	}

	ComputeShaderPtr CreateFXAACS() {
		return Create< ComputeShader >(MAGE_SHADER_ARGS(g_fxaa_CS));
	}

	ComputeShaderPtr CreateMSAAResolveCS() {
		return Create< ComputeShader >(MAGE_SHADER_ARGS(g_msaa_resolve_CS));
	}

	ComputeShaderPtr CreateSSAAResolveCS() {
		return Create< ComputeShader >(MAGE_SHADER_ARGS(g_ssaa_resolve_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Deferred
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateDeferredBlinnPhongCS(bool vct) {
		return vct ? Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_vct_blinn_phong_CS))
			       : Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_blinn_phong_CS));
	}

	ComputeShaderPtr CreateDeferredCookTorranceCS(bool vct) {
		return vct ? Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_vct_cook_torrance_CS))
			       : Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_cook_torrance_CS));
	}

	ComputeShaderPtr CreateDeferredEmissiveCS() {
		return Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_emissive_CS));
	}

	ComputeShaderPtr CreateDeferredFrostbiteCS(bool vct) {
		return vct ? Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_vct_frostbite_CS))
			       : Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_frostbite_CS));
	}

	ComputeShaderPtr CreateDeferredLambertianCS(bool vct) {
		return vct ? Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_vct_lambertian_CS))
			       : Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_lambertian_CS));
	}

	ComputeShaderPtr CreateDeferredWardDuerCS(bool vct) {
		return vct ? Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_vct_ward_duer_CS))
			       : Create< ComputeShader >(MAGE_SHADER_ARGS(g_deferred_ward_duer_CS));
	}

	ComputeShaderPtr CreateDeferredCS(BRDFType brdf, bool vct) {
		switch (brdf) {

		case BRDFType::BlinnPhong:
			return CreateDeferredBlinnPhongCS(vct);
		case BRDFType::CookTorrance:
			return CreateDeferredCookTorranceCS(vct);
		case BRDFType::Lambertian:
			return CreateDeferredLambertianCS(vct);
		case BRDFType::WardDuer:
			return CreateDeferredWardDuerCS(vct);
		default:
			return CreateDeferredFrostbiteCS(vct);
		}
	}

	PixelShaderPtr CreateDeferredMSAABlinnPhongPS(bool vct) {
		return vct ? Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_vct_blinn_phong_PS))
			       : Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_blinn_phong_PS));
	}

	PixelShaderPtr CreateDeferredMSAACookTorrancePS(bool vct) {
		return vct ? Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_vct_cook_torrance_PS))
		           : Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_cook_torrance_PS));
	}

	PixelShaderPtr CreateDeferredMSAAEmissivePS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_emissive_PS));
	}

	PixelShaderPtr CreateDeferredMSAAFrostbitePS(bool vct) {
		return vct ? Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_vct_frostbite_PS))
		           : Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_frostbite_PS));
	}

	PixelShaderPtr CreateDeferredMSAALambertianPS(bool vct) {
		return vct ? Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_vct_lambertian_PS))
		           : Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_lambertian_PS));
	}

	PixelShaderPtr CreateDeferredMSAAWardDuerPS(bool vct) {
		return vct ? Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_vct_ward_duer_PS))
		           : Create< PixelShader >(MAGE_SHADER_ARGS(g_deferred_msaa_ward_duer_PS));
	}

	PixelShaderPtr CreateDeferredMSAAPS(BRDFType brdf, bool vct) {
		switch (brdf) {

		case BRDFType::BlinnPhong:
			return CreateDeferredMSAABlinnPhongPS(vct);
		case BRDFType::CookTorrance:
			return CreateDeferredMSAACookTorrancePS(vct);
		case BRDFType::Lambertian:
			return CreateDeferredMSAALambertianPS(vct);
		case BRDFType::WardDuer:
			return CreateDeferredMSAAWardDuerPS(vct);
		default:
			return CreateDeferredMSAAFrostbitePS(vct);
		}
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Depth
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateDepthVS() {
		using vertex_t = VertexPositionNormalTexture;
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_depth_VS),
									  vertex_t::s_input_element_desc,
									  vertex_t::s_nb_input_elements);
	}

	VertexShaderPtr CreateDepthTransparentVS() {
		using vertex_t = VertexPositionNormalTexture;
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_depth_transparent_VS),
									  vertex_t::s_input_element_desc,
									  vertex_t::s_nb_input_elements);
	}

	PixelShaderPtr CreateDepthTransparentPS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_depth_transparent_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Forward
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateForwardBlinnPhongPS(bool transparency, bool vct, bool tsnm) {
		const auto config = static_cast< U32 >(transparency) << 2u
		                  | static_cast< U32 >(vct)          << 1u
						  | static_cast< U32 >(tsnm);
		
		switch(config) {
			
		case 0b000:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_blinn_phong_PS));
		case 0b001:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_tsnm_blinn_phong_PS));
		case 0b010:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_blinn_phong_PS));
		case 0b011:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_tsnm_blinn_phong_PS));
		case 0b100:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_blinn_phong_PS));			
		case 0b101:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_tsnm_blinn_phong_PS));
		case 0b110:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_blinn_phong_PS));
		case 0b111:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_blinn_phong_PS));
		default:
			return nullptr;
		}
	}

	PixelShaderPtr CreateForwardCookTorrancePS(bool transparency, bool vct, bool tsnm) {
		const auto config = static_cast< U32 >(transparency) << 2u
		                  | static_cast< U32 >(vct)          << 1u
						  | static_cast< U32 >(tsnm);
		
		switch(config) {
			
		case 0b000:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_cook_torrance_PS));
		case 0b001:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_tsnm_cook_torrance_PS));
		case 0b010:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_cook_torrance_PS));
		case 0b011:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_tsnm_cook_torrance_PS));
		case 0b100:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_cook_torrance_PS));			
		case 0b101:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_tsnm_cook_torrance_PS));
		case 0b110:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_cook_torrance_PS));
		case 0b111:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_cook_torrance_PS));
		default:
			return nullptr;
		}
	}

	PixelShaderPtr CreateForwardEmissivePS(bool transparency) {
		return transparency ? Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_emissive_PS))
		                    : Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_emissive_PS));
	}

	PixelShaderPtr CreateForwardFrostbitePS(bool transparency, bool vct, bool tsnm) {
		const auto config = static_cast< U32 >(transparency) << 2u
		                  | static_cast< U32 >(vct)          << 1u
						  | static_cast< U32 >(tsnm);
		
		switch(config) {
			
		case 0b000:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_frostbite_PS));
		case 0b001:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_tsnm_frostbite_PS));
		case 0b010:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_frostbite_PS));
		case 0b011:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_tsnm_frostbite_PS));
		case 0b100:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_frostbite_PS));			
		case 0b101:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_tsnm_frostbite_PS));
		case 0b110:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_frostbite_PS));
		case 0b111:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_frostbite_PS));
		default:
			return nullptr;
		}
	}

	PixelShaderPtr CreateForwardLambertianPS(bool transparency, bool vct, bool tsnm) {
		const auto config = static_cast< U32 >(transparency) << 2u
		                  | static_cast< U32 >(vct)          << 1u
						  | static_cast< U32 >(tsnm);
		
		switch(config) {
			
		case 0b000:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_lambertian_PS));
		case 0b001:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_tsnm_lambertian_PS));
		case 0b010:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_lambertian_PS));
		case 0b011:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_tsnm_lambertian_PS));
		case 0b100:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_lambertian_PS));			
		case 0b101:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_tsnm_lambertian_PS));
		case 0b110:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_lambertian_PS));
		case 0b111:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_lambertian_PS));
		default:
			return nullptr;
		}
	}

	PixelShaderPtr CreateForwardWardDuerPS(bool transparency, bool vct, bool tsnm) {
		const auto config = static_cast< U32 >(transparency) << 2u
		                  | static_cast< U32 >(vct)          << 1u
						  | static_cast< U32 >(tsnm);
		
		switch(config) {
			
		case 0b000:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_ward_duer_PS));
		case 0b001:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_tsnm_ward_duer_PS));
		case 0b010:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_ward_duer_PS));
		case 0b011:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_vct_tsnm_ward_duer_PS));
		case 0b100:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_ward_duer_PS));			
		case 0b101:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_tsnm_ward_duer_PS));
		case 0b110:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_ward_duer_PS));
		case 0b111:
			return Create< PixelShader >(MAGE_SHADER_ARGS(g_forward_transparent_vct_tsnm_ward_duer_PS));
		default:
			return nullptr;
		}
	}

	PixelShaderPtr CreateForwardPS(BRDFType brdf, bool transparency, bool vct, bool tsnm) {
		switch (brdf) {

		case BRDFType::BlinnPhong:
			return CreateForwardBlinnPhongPS(  transparency, vct, tsnm);
		case BRDFType::CookTorrance:
			return CreateForwardCookTorrancePS(transparency, vct, tsnm);
		case BRDFType::Lambertian:
			return CreateForwardLambertianPS(  transparency, vct, tsnm);
		case BRDFType::WardDuer:
			return CreateForwardWardDuerPS(    transparency, vct, tsnm);
		default:
			return CreateForwardFrostbitePS(   transparency, vct, tsnm);
		}
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBuffer
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateGBufferPS(bool tsnm) {
		return tsnm ? Create< PixelShader >(MAGE_SHADER_ARGS(g_gbuffer_tsnm_PS))
			        : Create< PixelShader >(MAGE_SHADER_ARGS(g_gbuffer_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Miscellaneous
	//-------------------------------------------------------------------------
	#pragma region

	PixelShaderPtr CreateBackBufferPS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_back_buffer_PS));
	}

	PixelShaderPtr CreateConstantColorPS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_constant_color_PS));
	}

	PixelShaderPtr CreateConstantColorTexturePS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_constant_color_texture_PS));
	}

	PixelShaderPtr CreateDistancePS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_distance_PS));
	}

	VertexShaderPtr CreateShadingNormalVS() {
		using vertex_t = VertexPositionNormalTexture;
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_shading_normal_VS),
									  vertex_t::s_input_element_desc,
									  vertex_t::s_nb_input_elements);
	}

	PixelShaderPtr CreateShadingNormalPS(bool tsnm) {
		return tsnm ? Create< PixelShader >(MAGE_SHADER_ARGS(g_tsnm_shading_normal_PS))
			        : Create< PixelShader >(MAGE_SHADER_ARGS(g_shading_normal_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Post Processing
	//-------------------------------------------------------------------------
	#pragma region

	ComputeShaderPtr CreateDepthOfFieldCS() {
		return Create< ComputeShader >(MAGE_SHADER_ARGS(g_postprocessing_depth_of_field_CS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Primitive
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateLineCubeVS() {
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_line_cube_VS), 
									  nullptr, 0u);
	}

	PixelShaderPtr CreateLineCubePS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_line_cube_PS));
	}

	VertexShaderPtr CreateFarFullscreenTriangleVS() {
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_far_fullscreen_triangle_VS), 
									  nullptr, 0u);
	}

	VertexShaderPtr CreateNearFullscreenTriangleVS() {
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_near_fullscreen_triangle_VS), 
									  nullptr, 0u);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sky
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateSkyVS() {
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_sky_VS), 
									  nullptr, 0u);
	}

	PixelShaderPtr CreateSkyPS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_sky_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Sprite
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateSpriteVS() {
		using vertex_t = VertexPositionColorTexture;
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_sprite_VS),
									  vertex_t::s_input_element_desc,
									  vertex_t::s_nb_input_elements);
	}

	PixelShaderPtr CreateSpritePS() {
		return Create< PixelShader >(MAGE_SHADER_ARGS(g_sprite_PS));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Transform
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateMinimalTransformVS() {
		using vertex_t = VertexPositionNormalTexture;
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_minimal_transform_VS), 
									  vertex_t::s_input_element_desc, 
									  vertex_t::s_nb_input_elements);
	}

	VertexShaderPtr CreateTransformVS() {
		using vertex_t = VertexPositionNormalTexture;
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_transform_VS),
									  vertex_t::s_input_element_desc,
									  vertex_t::s_nb_input_elements);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: Voxelization
	//-------------------------------------------------------------------------
	#pragma region

	VertexShaderPtr CreateVoxelizationVS() {
		using vertex_t = VertexPositionNormalTexture;
		return Create< VertexShader >(MAGE_SHADER_ARGS(g_voxelization_VS), 
			                          vertex_t::s_input_element_desc,
			                          vertex_t::s_nb_input_elements);
	}

	GeometryShaderPtr CreateVoxelizationGS() {
		return Create< GeometryShader >(MAGE_SHADER_ARGS(g_voxelization_GS));
	}

	PixelShaderPtr CreateVoxelizationBlinnPhongPS(bool tsnm) {
		return tsnm ? Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_tsnm_blinn_phong_PS))
					: Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_blinn_phong_PS));
	}

	PixelShaderPtr CreateVoxelizationCookTorrancePS(bool tsnm) {
		return tsnm ? Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_tsnm_cook_torrance_PS))
					: Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_cook_torrance_PS));
	}

	PixelShaderPtr CreateVoxelizationFrostbitePS(bool tsnm) {
		return tsnm ? Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_tsnm_frostbite_PS))
					: Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_frostbite_PS));
	}

	PixelShaderPtr CreateVoxelizationLambertianPS(bool tsnm) {
		return tsnm ? Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_tsnm_lambertian_PS))
					: Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_lambertian_PS));
	}

	PixelShaderPtr CreateVoxelizationWardDuerPS(bool tsnm) {
		return tsnm ? Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_tsnm_ward_duer_PS))
					: Create< PixelShader >(MAGE_SHADER_ARGS(g_voxelization_ward_duer_PS));
	}

	PixelShaderPtr CreateVoxelizationPS(BRDFType brdf, bool tsnm) {
		switch (brdf) {

		case BRDFType::BlinnPhong:
			return CreateVoxelizationBlinnPhongPS(tsnm);
		case BRDFType::CookTorrance:
			return CreateVoxelizationCookTorrancePS(tsnm);
		case BRDFType::Lambertian:
			return CreateVoxelizationLambertianPS(tsnm);
		case BRDFType::WardDuer:
			return CreateVoxelizationWardDuerPS(tsnm);
		default:
			return CreateVoxelizationFrostbitePS(tsnm);
		}
	}

	ComputeShaderPtr CreateVoxelizationCS() {
		return Create< ComputeShader >(MAGE_SHADER_ARGS(g_voxelization_CS));
	}

	#pragma endregion
}