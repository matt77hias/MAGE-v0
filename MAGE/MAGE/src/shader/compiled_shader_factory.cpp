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

	UniquePtr< const CompiledShader > CreateCompiledTransformVS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_transform_vs, sizeof(g_transform_vs));
	}

	UniquePtr< const CompiledShader > CreateCompiledEmissivePS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_emissive_ps, sizeof(g_emissive_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledLambertianPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_lambertian_ps, sizeof(g_lambertian_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledPhongPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_phong_ps, sizeof(g_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledModifiedPhongPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_modified_phong_ps, sizeof(g_modified_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledBlinnPhongPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_blinn_phong_ps, sizeof(g_blinn_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledModifiedBlinnPhongPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_modified_blinn_phong_ps, sizeof(g_modified_blinn_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledWardPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_ward_ps, sizeof(g_ward_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledWardDuerPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_ward_duer_ps, sizeof(g_ward_duer_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledCookTorrancePS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_cook_torrance_ps, sizeof(g_cook_torrance_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledLambertianTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_lambertian_ps, sizeof(g_tsnm_lambertian_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledPhongTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_phong_ps, sizeof(g_tsnm_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledModifiedPhongTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_modified_phong_ps, sizeof(g_tsnm_modified_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledBlinnPhongTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_blinn_phong_ps, sizeof(g_tsnm_blinn_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledModifiedBlinnPhongTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_modified_blinn_phong_ps, sizeof(g_tsnm_modified_blinn_phong_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledWardTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_ward_ps, sizeof(g_tsnm_ward_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledWardDuerTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_ward_duer_ps, sizeof(g_tsnm_ward_duer_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledCookTorranceTSNMPS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_tsnm_cook_torrance_ps, sizeof(g_tsnm_cook_torrance_ps));
	}

	UniquePtr< const CompiledShader > CreateCompiledSpriteVS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_sprite_vs, sizeof(g_sprite_vs));
	}

	UniquePtr< const CompiledShader > CreateCompiledSpritePS() noexcept {
		return MakeUnique< const BufferCompiledShader >(g_sprite_ps, sizeof(g_sprite_ps));
	}
}