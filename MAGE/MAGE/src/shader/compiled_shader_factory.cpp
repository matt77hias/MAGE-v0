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

	UniquePtr< CompiledShader > CreateCompiledTransformVertexShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_transform_vs, sizeof(g_transform_vs));
	}

	UniquePtr< CompiledShader > CreateCompiledEmissivePixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_emissive_ps, sizeof(g_emissive_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledLambertianPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_lambertian_ps, sizeof(g_lambertian_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledPhongPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_phong_ps, sizeof(g_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledModifiedPhongPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_modified_phong_ps, sizeof(g_modified_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledBlinnPhongPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_blinn_phong_ps, sizeof(g_blinn_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledModifiedBlinnPhongPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_modified_blinn_phong_ps, sizeof(g_modified_blinn_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledWardPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_ward_ps, sizeof(g_ward_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledWardDuerPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_ward_duer_ps, sizeof(g_ward_duer_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledCookTorrancePixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_cook_torrance_ps, sizeof(g_cook_torrance_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledLambertianTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_lambertian_ps, sizeof(g_tsnm_lambertian_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledPhongTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_phong_ps, sizeof(g_tsnm_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledModifiedPhongTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_modified_phong_ps, sizeof(g_tsnm_modified_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledBlinnPhongTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_blinn_phong_ps, sizeof(g_tsnm_blinn_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledModifiedBlinnPhongTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_modified_blinn_phong_ps, sizeof(g_tsnm_modified_blinn_phong_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledWardTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_ward_ps, sizeof(g_tsnm_ward_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledWardDuerTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_ward_duer_ps, sizeof(g_tsnm_ward_duer_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledCookTorranceTSNMPixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_tsnm_cook_torrance_ps, sizeof(g_tsnm_cook_torrance_ps));
	}

	UniquePtr< CompiledShader > CreateCompiledSpriteVertexShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_sprite_vs, sizeof(g_sprite_vs));
	}

	UniquePtr< CompiledShader > CreateCompiledSpritePixelShader() noexcept {
		return std::make_unique< BufferCompiledShader >(g_sprite_ps, sizeof(g_sprite_ps));
	}
}