//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\compiled_shader_factory.hpp"
#include "shader\cso\transform_VS.hpp"
#include "shader\cso\emissive_PS.hpp"
#include "shader\cso\lambertian_PS.hpp"
#include "shader\cso\phong_PS.hpp"
#include "shader\cso\modified_phong_PS.hpp"
#include "shader\cso\blinn_phong_PS.hpp"
#include "shader\cso\modified_blinn_phong_PS.hpp"
#include "shader\cso\ward_PS.hpp"
#include "shader\cso\ward_duer_PS.hpp"
#include "shader\cso\cook_torrance_PS.hpp"
#include "shader\cso\tsnm_lambertian_PS.hpp"
#include "shader\cso\tsnm_phong_PS.hpp"
#include "shader\cso\tsnm_modified_phong_PS.hpp"
#include "shader\cso\tsnm_blinn_phong_PS.hpp"
#include "shader\cso\tsnm_modified_blinn_phong_PS.hpp"
#include "shader\cso\tsnm_ward_PS.hpp"
#include "shader\cso\tsnm_ward_duer_PS.hpp"
#include "shader\cso\tsnm_cook_torrance_PS.hpp"
#include "shader\cso\sprite_VS.hpp"
#include "shader\cso\sprite_PS.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CompiledVertexShader CreateCompiledTransformVertexShader() noexcept {
		return CompiledVertexShader(MAGE_GUID_TRANSFORM_VS, g_transform_vs, sizeof(g_transform_vs));
	}

	const CompiledPixelShader CreateCompiledEmissivePixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_EMISSIVE_PS, g_emissive_ps, sizeof(g_emissive_ps));
	}

	const CompiledPixelShader CreateCompiledLambertianPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_LAMBERTIAN_PS, g_lambertian_ps, sizeof(g_lambertian_ps));
	}

	const CompiledPixelShader CreateCompiledPhongPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_PHONG_PS, g_phong_ps, sizeof(g_phong_ps));
	}

	const CompiledPixelShader CreateCompiledModifiedPhongPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_MODIFIED_PHONG_PS, g_modified_phong_ps, sizeof(g_modified_phong_ps));
	}

	const CompiledPixelShader CreateCompiledBlinnPhongPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_BLINN_PHONG_PS, g_blinn_phong_ps, sizeof(g_blinn_phong_ps));
	}

	const CompiledPixelShader CreateCompiledModifiedBlinnPhongPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_MODIFIED_BLINN_PHONG_PS, g_modified_blinn_phong_ps, sizeof(g_modified_blinn_phong_ps));
	}

	const CompiledPixelShader CreateCompiledWardPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_WARD_PS, g_ward_ps, sizeof(g_ward_ps));
	}

	const CompiledPixelShader CreateCompiledWardDuerPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_WARD_DUER_PS, g_ward_duer_ps, sizeof(g_ward_duer_ps));
	}

	const CompiledPixelShader CreateCompiledCookTorrancePixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_COOK_TORRANCE_PS, g_cook_torrance_ps, sizeof(g_cook_torrance_ps));
	}

	const CompiledPixelShader CreateCompiledLambertianTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_LAMBERTIAN_PS, g_tsnm_lambertian_ps, sizeof(g_tsnm_lambertian_ps));
	}

	const CompiledPixelShader CreateCompiledPhongTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_PHONG_PS, g_tsnm_phong_ps, sizeof(g_tsnm_phong_ps));
	}

	const CompiledPixelShader CreateCompiledModifiedPhongTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_MODIFIED_PHONG_PS, g_tsnm_modified_phong_ps, sizeof(g_tsnm_modified_phong_ps));
	}

	const CompiledPixelShader CreateCompiledBlinnPhongTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_BLINN_PHONG_PS, g_tsnm_blinn_phong_ps, sizeof(g_tsnm_blinn_phong_ps));
	}

	const CompiledPixelShader CreateCompiledModifiedBlinnPhongTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_MODIFIED_BLINN_PHONG_PS, g_tsnm_modified_blinn_phong_ps, sizeof(g_tsnm_modified_blinn_phong_ps));
	}

	const CompiledPixelShader CreateCompiledWardTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_WARD_PS, g_tsnm_ward_ps, sizeof(g_tsnm_ward_ps));
	}

	const CompiledPixelShader CreateCompiledWardDuerTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_WARD_DUER_PS, g_tsnm_ward_duer_ps, sizeof(g_tsnm_ward_duer_ps));
	}

	const CompiledPixelShader CreateCompiledCookTorranceTSNMPixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_TSNM_COOK_TORRANCE_PS, g_tsnm_cook_torrance_ps, sizeof(g_tsnm_cook_torrance_ps));
	}

	const CompiledVertexShader CreateCompiledSpriteVertexShader() noexcept {
		return CompiledVertexShader(MAGE_GUID_SPRITE_VS, g_sprite_vs, sizeof(g_sprite_vs));
	}

	const CompiledPixelShader CreateCompiledSpritePixelShader() noexcept {
		return CompiledPixelShader(MAGE_GUID_SPRITE_PS, g_sprite_ps, sizeof(g_sprite_ps));
	}
}