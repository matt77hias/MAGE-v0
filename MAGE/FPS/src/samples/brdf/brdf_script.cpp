//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\brdf\brdf_script.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BRDFScript::BRDFScript(CameraSettings *settings,
		SpriteText *text, const vector< ModelNode * > &models)
		: m_settings(settings), m_text(text), 
		m_models(models), m_model_index(0),
		m_modes(), m_mode_index(0) {

		Assert(m_settings);
		Assert(m_text);

		InitModels();
		InitModes();
	}

	BRDFScript::BRDFScript(BRDFScript &&script) = default;

	BRDFScript::~BRDFScript() {
		m_models.clear();
		m_modes.clear();
	}

	void BRDFScript::InitModels() noexcept {
		for (const auto &node : m_models) {
			node->Deactivate();
		}

		m_models[0]->Activate();
	}

	void BRDFScript::InitModes() {
		const SharedPtr< const Texture > white 
			= CreateWhiteTexture();
		const SharedPtr< const Texture > tsnm 
			= ResourceManager::Get()->GetOrCreateTexture(L"assets/textures/tsnm/rock 4.dds");

		Material mat_emissive;
		mat_emissive.DissableLightInteraction();
		mat_emissive.GetBaseColor() = SRGB(1.0f, 0.0f, 0.0f);

		Material mat;
		mat.GetBaseColor() = SRGB(1.0f, 0.0f, 0.0f);
		mat.SetRoughness(0.25f);
		mat.SetMetalness(1.0f);
		Material mat_tsnm = mat;
		mat_tsnm.SetNormalTexture(tsnm);

		m_modes.reserve(11);
		m_modes.emplace_back(L"\n\n\n\n\nEmissive", mat_emissive, BRDFType::Unknown);
		m_modes.emplace_back(L"\n\n\n\n\nLambertian", mat, BRDFType::Lambertian);
		m_modes.emplace_back(L"\n\n\n\n\nFrostbite", mat, BRDFType::Frostbite);
		m_modes.emplace_back(L"\n\n\n\n\nCook-Torrance", mat, BRDFType::CookTorrance);
		m_modes.emplace_back(L"\n\n\n\n\nBlinn-Phong", mat, BRDFType::BlinnPhong);
		m_modes.emplace_back(L"\n\n\n\n\nWard-Duer", mat, BRDFType::WardDuer);
		m_modes.emplace_back(L"\n\n\n\n\nTSNM + Lambertian", mat_tsnm, BRDFType::Lambertian);
		m_modes.emplace_back(L"\n\n\n\n\nTSNM + Frostbite", mat_tsnm, BRDFType::Frostbite);
		m_modes.emplace_back(L"\n\n\n\n\nTSNM + Cook-Torrance", mat_tsnm, BRDFType::CookTorrance);
		m_modes.emplace_back(L"\n\n\n\n\nTSNM + Blinn-Phong", mat_tsnm, BRDFType::BlinnPhong);
		m_modes.emplace_back(L"\n\n\n\n\nTSNM + Ward-Duer", mat_tsnm, BRDFType::WardDuer);
		
		SetMode();
	}

	void BRDFScript::SetMode() noexcept {
		const Mode &mode = m_modes[m_mode_index];
		
		// Set the material.
		for (const auto &node : m_models) {
			*(node->GetModel()->GetMaterial()) = mode.m_material;
		}
		
		// Set the BRDF.
		m_settings->SetBRDF(mode.m_brdf);
	}

	void BRDFScript::Update([[maybe_unused]] F64 time) {
		const Keyboard * const keyboard = Keyboard::Get();

		// Switch model.
		if (keyboard->GetKeyPress(DIK_UP, false)) {
			m_models[m_model_index]->Deactivate();
			m_model_index = (m_model_index + 1) % m_models.size();
			m_models[m_model_index]->Activate();
		} 
		else if (keyboard->GetKeyPress(DIK_DOWN, false)) {
			m_models[m_model_index]->Deactivate();
			m_model_index = std::min(m_model_index - 1, m_models.size() - 1);
			m_models[m_model_index]->Activate();
		}

		// Switch shader.
		if (keyboard->GetKeyPress(DIK_RIGHT, false)) {
			m_mode_index = (m_mode_index + 1) % m_modes.size();
			SetMode();
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, false)) {
			m_mode_index = std::min(m_mode_index - 1, m_modes.size() - 1);
			SetMode();
		}

		const Mode &mode = m_modes[m_mode_index];
		m_text->SetText(mode.m_name.c_str());
	}
}