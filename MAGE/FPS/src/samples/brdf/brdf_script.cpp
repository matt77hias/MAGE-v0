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
		: m_settings(settings), m_text(text), m_models(models),
		m_shaders(), m_model_index(0), m_shader_index(0) {

		Assert(m_settings);
		Assert(m_text);

		InitModels();
		InitShaders();
	}

	BRDFScript::BRDFScript(BRDFScript &&script) = default;

	BRDFScript::~BRDFScript() {
		m_models.clear();
		m_shaders.clear();
	}

	void BRDFScript::InitModels() noexcept {
		for (const auto &node : m_models) {
			node->Deactivate();
		}

		m_models[0]->Activate();
	}

	void BRDFScript::InitShaders() {
		const SharedPtr< const Texture > white 
			= CreateWhiteTexture();
		const SharedPtr< const Texture > tsnm 
			= ResourceManager::Get()->GetOrCreateTexture(L"assets/sprites/tsnm/rock 4.dds");

		Material mat_emissive;
		mat_emissive.DissableLightInteraction();
		mat_emissive.SetBaseColorRGB(1.0f, 0.0f, 0.0f);

		Material mat;
		mat.SetBaseColorRGB(1.0f, 0.0f, 0.0f);
		mat.SetRoughness(0.15f);
		Material mat_tsnm = mat;
		mat_tsnm.SetNormalTexture(tsnm);

		m_shaders.reserve(17);
		m_shaders.emplace_back(std::make_pair(ShaderType::Emissive,         mat_emissive));
		m_shaders.emplace_back(std::make_pair(ShaderType::Lambertian,       mat));
		m_shaders.emplace_back(std::make_pair(ShaderType::CookTorrance,     mat));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMLambertian,   mat_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMCookTorrance, mat_tsnm));

		SetShader();
		SetMaterial();
	}

	void BRDFScript::SetMaterial() noexcept {
		const Material &material = m_shaders[m_shader_index].second;
		for (const auto &node : m_models) {
			node->GetModel()->SetMaterial(material);
		}
	}

	void BRDFScript::SetShader() noexcept {
		switch (m_shaders[m_shader_index].first) {

		case ShaderType::Lambertian:
		case ShaderType::TSNMLambertian: {
			m_settings->SetBRDF(BRDFType::Lambertian);
			break;
		}

		case ShaderType::CookTorrance:
		case ShaderType::TSNMCookTorrance: {
			m_settings->SetBRDF(BRDFType::CookTorrance);
			break;
		}

		}
	}

	void BRDFScript::PrintText() {
		switch (m_shaders[m_shader_index].first) {

		case ShaderType::Emissive: {
			m_text->SetText(L"\n\n\n\n\nEmissive");
			break;
		}
		case ShaderType::Lambertian: {
			m_text->SetText(L"\n\n\n\n\nLambertian");
			break;
		}
		case ShaderType::CookTorrance: {
			m_text->SetText(L"\n\n\n\n\nCook-Torrance");
			break;
		}
		case ShaderType::TSNMLambertian: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Lambertian");
			break;
		}
		case ShaderType::TSNMCookTorrance: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Cook-Torrance");
			break;
		}
		}
	}

	void BRDFScript::Update(F64 time) {
		UNUSED(time);
		
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
			m_shader_index = (m_shader_index + 1) % m_shaders.size();
			SetShader();
			SetMaterial();
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, false)) {
			m_shader_index = std::min(m_shader_index - 1, m_shaders.size() - 1);
			SetShader();
			SetMaterial();
		}

		PrintText();
	}
}