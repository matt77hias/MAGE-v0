//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader_factory.hpp"

// Depth
#include "shader\cso\depth\depth_VS.hpp"

// GBuffer
#include "shader\cso\gbuffer\gbuffer_PS.hpp"
#include "shader\cso\gbuffer\gbuffer_tsnm_PS.hpp"

// Deferred
#include "shader\cso\deferred\transform_VS.hpp"
#include "shader\cso\deferred\emissive_PS.hpp"
#include "shader\cso\deferred\lambertian_PS.hpp"
#include "shader\cso\deferred\phong_PS.hpp"
#include "shader\cso\deferred\modified_phong_PS.hpp"
#include "shader\cso\deferred\blinn_phong_PS.hpp"
#include "shader\cso\deferred\modified_blinn_phong_PS.hpp"
#include "shader\cso\deferred\ward_PS.hpp"
#include "shader\cso\deferred\ward_duer_PS.hpp"
#include "shader\cso\deferred\cook_torrance_PS.hpp"

// Forward
#include "shader\cso\forward\transform_VS.hpp"
#include "shader\cso\forward\emissive_PS.hpp"
#include "shader\cso\forward\lambertian_PS.hpp"
#include "shader\cso\forward\phong_PS.hpp"
#include "shader\cso\forward\modified_phong_PS.hpp"
#include "shader\cso\forward\blinn_phong_PS.hpp"
#include "shader\cso\forward\modified_blinn_phong_PS.hpp"
#include "shader\cso\forward\ward_PS.hpp"
#include "shader\cso\forward\ward_duer_PS.hpp"
#include "shader\cso\forward\cook_torrance_PS.hpp"
#include "shader\cso\forward\tsnm_lambertian_PS.hpp"
#include "shader\cso\forward\tsnm_phong_PS.hpp"
#include "shader\cso\forward\tsnm_modified_phong_PS.hpp"
#include "shader\cso\forward\tsnm_blinn_phong_PS.hpp"
#include "shader\cso\forward\tsnm_modified_blinn_phong_PS.hpp"
#include "shader\cso\forward\tsnm_ward_PS.hpp"
#include "shader\cso\forward\tsnm_ward_duer_PS.hpp"
#include "shader\cso\forward\tsnm_cook_torrance_PS.hpp"

// Miscellaneous
#include "shader\cso\miscellaneous\minimal_transform_VS.hpp"
#include "shader\cso\miscellaneous\distance_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_texture_PS.hpp"
#include "shader\cso\miscellaneous\shading_normal_VS.hpp"
#include "shader\cso\miscellaneous\shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\tsnm_shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\bounding_volume_VS.hpp"
#include "shader\cso\miscellaneous\bounding_volume_PS.hpp"

// Sprite
#include "shader\cso\sprite\sprite_VS.hpp"
#include "shader\cso\sprite\sprite_PS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Factory Methods: DepthPass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledDepthVS() noexcept {
		return BufferCompiledShader(g_depth_vs, sizeof(g_depth_vs));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantShadingPass and VariableShadingPass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledTransformVS() noexcept {
		return BufferCompiledShader(g_transform_vs, sizeof(g_transform_vs));
	}

	const BufferCompiledShader CreateCompiledEmissivePS() noexcept {
		return BufferCompiledShader(g_emissive_ps, sizeof(g_emissive_ps));
	}

	const BufferCompiledShader CreateCompiledLambertianPS() noexcept {
		return BufferCompiledShader(g_lambertian_ps, sizeof(g_lambertian_ps));
	}

	const BufferCompiledShader CreateCompiledPhongPS() noexcept {
		return BufferCompiledShader(g_phong_ps, sizeof(g_phong_ps));
	}

	const BufferCompiledShader CreateCompiledModifiedPhongPS() noexcept {
		return BufferCompiledShader(g_modified_phong_ps, sizeof(g_modified_phong_ps));
	}

	const BufferCompiledShader CreateCompiledBlinnPhongPS() noexcept {
		return BufferCompiledShader(g_blinn_phong_ps, sizeof(g_blinn_phong_ps));
	}

	const BufferCompiledShader CreateCompiledModifiedBlinnPhongPS() noexcept {
		return BufferCompiledShader(g_modified_blinn_phong_ps, sizeof(g_modified_blinn_phong_ps));
	}

	const BufferCompiledShader CreateCompiledWardPS() noexcept {
		return BufferCompiledShader(g_ward_ps, sizeof(g_ward_ps));
	}

	const BufferCompiledShader CreateCompiledWardDuerPS() noexcept {
		return BufferCompiledShader(g_ward_duer_ps, sizeof(g_ward_duer_ps));
	}

	const BufferCompiledShader CreateCompiledCookTorrancePS() noexcept {
		return BufferCompiledShader(g_cook_torrance_ps, sizeof(g_cook_torrance_ps));
	}

	const BufferCompiledShader CreateCompiledLambertianTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_lambertian_ps, sizeof(g_tsnm_lambertian_ps));
	}

	const BufferCompiledShader CreateCompiledPhongTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_phong_ps, sizeof(g_tsnm_phong_ps));
	}

	const BufferCompiledShader CreateCompiledModifiedPhongTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_modified_phong_ps, sizeof(g_tsnm_modified_phong_ps));
	}

	const BufferCompiledShader CreateCompiledBlinnPhongTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_blinn_phong_ps, sizeof(g_tsnm_blinn_phong_ps));
	}

	const BufferCompiledShader CreateCompiledModifiedBlinnPhongTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_modified_blinn_phong_ps, sizeof(g_tsnm_modified_blinn_phong_ps));
	}

	const BufferCompiledShader CreateCompiledWardTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_ward_ps, sizeof(g_tsnm_ward_ps));
	}

	const BufferCompiledShader CreateCompiledWardDuerTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_ward_duer_ps, sizeof(g_tsnm_ward_duer_ps));
	}

	const BufferCompiledShader CreateCompiledCookTorranceTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_cook_torrance_ps, sizeof(g_tsnm_cook_torrance_ps));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: GBufferPass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledGBufferPS() noexcept {
		return BufferCompiledShader(g_gbuffer_ps, sizeof(g_gbuffer_ps));
	}

	const BufferCompiledShader CreateCompiledGBufferTSNMPS() noexcept {
		return BufferCompiledShader(g_gbuffer_tsnm_ps, sizeof(g_gbuffer_tsnm_ps));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: DeferredShadingPass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledDeferredTransformVS() noexcept {
		return BufferCompiledShader(g_deferred_transform_vs, sizeof(g_deferred_transform_vs));
	}

	const BufferCompiledShader CreateCompiledDeferredEmissivePS() noexcept {
		return BufferCompiledShader(g_deferred_emissive_ps, sizeof(g_deferred_emissive_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredLambertianPS() noexcept {
		return BufferCompiledShader(g_deferred_lambertian_ps, sizeof(g_deferred_lambertian_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredPhongPS() noexcept {
		return BufferCompiledShader(g_deferred_phong_ps, sizeof(g_deferred_phong_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredModifiedPhongPS() noexcept {
		return BufferCompiledShader(g_deferred_modified_phong_ps, sizeof(g_deferred_modified_phong_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredBlinnPhongPS() noexcept {
		return BufferCompiledShader(g_deferred_blinn_phong_ps, sizeof(g_deferred_blinn_phong_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredModifiedBlinnPhongPS() noexcept {
		return BufferCompiledShader(g_deferred_modified_blinn_phong_ps, sizeof(g_deferred_modified_blinn_phong_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredWardPS() noexcept {
		return BufferCompiledShader(g_deferred_ward_ps, sizeof(g_deferred_ward_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredWardDuerPS() noexcept {
		return BufferCompiledShader(g_deferred_ward_duer_ps, sizeof(g_deferred_ward_duer_ps));
	}

	const BufferCompiledShader CreateCompiledDeferredCookTorrancePS() noexcept {
		return BufferCompiledShader(g_deferred_cook_torrance_ps, sizeof(g_deferred_cook_torrance_ps));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: SpritePass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledSpriteVS() noexcept {
		return BufferCompiledShader(g_sprite_vs, sizeof(g_sprite_vs));
	}

	const BufferCompiledShader CreateCompiledSpritePS() noexcept {
		return BufferCompiledShader(g_sprite_ps, sizeof(g_sprite_ps));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ConstantComponentPass and VariableComponentPass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledMinimalTransformVS() noexcept {
		return BufferCompiledShader(g_minimal_transform_vs, sizeof(g_minimal_transform_vs));
	}
	
	const BufferCompiledShader CreateCompiledConstantColorPS() noexcept {
		return BufferCompiledShader(g_constant_color_ps, sizeof(g_constant_color_ps));
	}

	const BufferCompiledShader CreateCompiledConstantColorTexturePS() noexcept {
		return BufferCompiledShader(g_constant_color_texture_ps, sizeof(g_constant_color_texture_ps));
	}

	const BufferCompiledShader CreateCompiledDistancePS() noexcept {
		return BufferCompiledShader(g_distance_ps, sizeof(g_distance_ps));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: ShadingNormalPass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledShadingNormalVS() noexcept {
		return BufferCompiledShader(g_shading_normal_vs, sizeof(g_shading_normal_vs));
	}

	const BufferCompiledShader CreateCompiledShadingNormalPS() noexcept {
		return BufferCompiledShader(g_shading_normal_ps, sizeof(g_shading_normal_ps));
	}

	const BufferCompiledShader CreateCompiledShadingNormalTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_shading_normal_ps, sizeof(g_tsnm_shading_normal_ps));
	}

#pragma endregion

	//-------------------------------------------------------------------------
	// Factory Methods: WireframePass
	//-------------------------------------------------------------------------
#pragma region

	const BufferCompiledShader CreateCompiledBoundingVolumeVS() noexcept {
		return BufferCompiledShader(g_bounding_volume_vs, sizeof(g_bounding_volume_vs));
	}

	const BufferCompiledShader CreateCompiledBoundingVolumePS() noexcept {
		return BufferCompiledShader(g_bounding_volume_ps, sizeof(g_bounding_volume_ps));
	}

#pragma endregion
}