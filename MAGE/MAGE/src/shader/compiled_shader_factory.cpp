//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader_factory.hpp"

#include "shader\cso\basic\transform_VS.hpp"
#include "shader\cso\basic\emissive_PS.hpp"
#include "shader\cso\basic\lambertian_PS.hpp"
#include "shader\cso\basic\phong_PS.hpp"
#include "shader\cso\basic\modified_phong_PS.hpp"
#include "shader\cso\basic\blinn_phong_PS.hpp"
#include "shader\cso\basic\modified_blinn_phong_PS.hpp"
#include "shader\cso\basic\ward_PS.hpp"
#include "shader\cso\basic\ward_duer_PS.hpp"
#include "shader\cso\basic\cook_torrance_PS.hpp"

#include "shader\cso\miscellaneous\minimal_transform_VS.hpp"
#include "shader\cso\miscellaneous\distance_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_PS.hpp"
#include "shader\cso\miscellaneous\constant_color_texture_PS.hpp"
#include "shader\cso\miscellaneous\shading_normal_transform_VS.hpp"
#include "shader\cso\miscellaneous\shading_normal_PS.hpp"
#include "shader\cso\miscellaneous\tsnm_shading_normal_PS.hpp"

#include "shader\cso\tsnm\tsnm_lambertian_PS.hpp"
#include "shader\cso\tsnm\tsnm_phong_PS.hpp"
#include "shader\cso\tsnm\tsnm_modified_phong_PS.hpp"
#include "shader\cso\tsnm\tsnm_blinn_phong_PS.hpp"
#include "shader\cso\tsnm\tsnm_modified_blinn_phong_PS.hpp"
#include "shader\cso\tsnm\tsnm_ward_PS.hpp"
#include "shader\cso\tsnm\tsnm_ward_duer_PS.hpp"
#include "shader\cso\tsnm\tsnm_cook_torrance_PS.hpp"

#include "shader\cso\sprite\sprite_VS.hpp"
#include "shader\cso\sprite\sprite_PS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

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

	const BufferCompiledShader CreateCompiledSpriteVS() noexcept {
		return BufferCompiledShader(g_sprite_vs, sizeof(g_sprite_vs));
	}

	const BufferCompiledShader CreateCompiledSpritePS() noexcept {
		return BufferCompiledShader(g_sprite_ps, sizeof(g_sprite_ps));
	}

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

	const BufferCompiledShader CreateCompiledShadingNormalTransformVS() noexcept {
		return BufferCompiledShader(g_shading_normal_transform_vs, sizeof(g_shading_normal_transform_vs));
	}

	const BufferCompiledShader CreateCompiledShadingNormalPS() noexcept {
		return BufferCompiledShader(g_shading_normal_ps, sizeof(g_shading_normal_ps));
	}

	const BufferCompiledShader CreateCompiledShadingNormalTSNMPS() noexcept {
		return BufferCompiledShader(g_tsnm_shading_normal_ps, sizeof(g_tsnm_shading_normal_ps));
	}
}