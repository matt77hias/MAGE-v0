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

	BRDFScript::BRDFScript(SpriteText *text, const vector< ModelNode * > &models)
		: m_text(text), m_models(models), m_shaders(), m_shader_names(),
		m_model_index(0), m_shader_index(0) {

		Assert(m_text);

		InitModels();
		InitShaders();
		SetShaders();
	}

	BRDFScript::BRDFScript(BRDFScript &&script) = default;

	BRDFScript::~BRDFScript() {
		m_models.clear();
		m_shaders.clear();
		m_shader_names.clear();
	}

	void BRDFScript::InitModels() {
		SharedPtr< Texture > white = CreateWhiteTexture();
		SharedPtr< Texture > normal = 
			ResourceManager::Get()->GetOrCreateTexture(L"assets/sprites/tsnm/rock 4.dds");
		
		for (auto it = m_models.cbegin(); it != m_models.cend(); ++it) {
			(*it)->MakePassive();
			
			ShadedMaterial *material = (*it)->GetModel()->GetMaterial();
			material->SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));
			material->SetDiffuseReflectivityTexture(white);
			material->SetSpecularReflectivity(RGBSpectrum(1.0f, 1.0f, 1.0f));
			material->SetSpecularExponent(10.0f);
			material->SetExtraParameter(0, 0.5f);
			material->SetExtraParameter(1, 0.15f);
			material->SetExtraParameter(2, 0.04f);
			material->SetNormalTexture(normal);
		}

		(*m_models.cbegin())->MakeActive();
	}

	void BRDFScript::InitShaders() {
		m_shaders.push_back(CreateEmissiveShader());
		m_shaders.push_back(CreateLambertianShader());
		m_shaders.push_back(CreatePhongShader());
		m_shaders.push_back(CreateModifiedPhongShader());
		m_shaders.push_back(CreateBlinnPhongShader());
		m_shaders.push_back(CreateModifiedBlinnPhongShader());
		m_shaders.push_back(CreateWardShader());
		m_shaders.push_back(CreateWardDuerShader());
		m_shaders.push_back(CreateCookTorranceShader());
		m_shaders.push_back(CreateLambertianTSNMShader());
		m_shaders.push_back(CreatePhongTSNMShader());
		m_shaders.push_back(CreateModifiedPhongTSNMShader());
		m_shaders.push_back(CreateBlinnPhongTSNMShader());
		m_shaders.push_back(CreateModifiedBlinnPhongTSNMShader());
		m_shaders.push_back(CreateWardTSNMShader());
		m_shaders.push_back(CreateWardDuerTSNMShader());
		m_shaders.push_back(CreateCookTorranceTSNMShader());

		m_shader_names.emplace_back(L"Emissive");
		m_shader_names.emplace_back(L"Lambertian");
		m_shader_names.emplace_back(L"Phong");
		m_shader_names.emplace_back(L"Modified Phong");
		m_shader_names.emplace_back(L"Blinn-Phong");
		m_shader_names.emplace_back(L"Modified Blinn-Phong");
		m_shader_names.emplace_back(L"Ward");
		m_shader_names.emplace_back(L"Ward-Duer");
		m_shader_names.emplace_back(L"Cook-Torrance");
		m_shader_names.emplace_back(L"Lambertian + TSNM");
		m_shader_names.emplace_back(L"Phong + TSNM");
		m_shader_names.emplace_back(L"Modified Phong + TSNM");
		m_shader_names.emplace_back(L"Blinn-Phong + TSNM");
		m_shader_names.emplace_back(L"Modified Blinn-Phong + TSNM");
		m_shader_names.emplace_back(L"Ward + TSNM");
		m_shader_names.emplace_back(L"Ward-Duer + TSNM");
		m_shader_names.emplace_back(L"Cook-Torrance + TSNM");


		Assert(m_shaders.size() == m_shader_names.size());
	}

	void BRDFScript::SetShaders() const {
		const CombinedShader shader = m_shaders[m_shader_index];
		for (auto it = m_models.cbegin(); it != m_models.cend(); ++it) {
			(*it)->GetModel()->GetMaterial()->SetShader(shader);
		}
	}

	void BRDFScript::Update(double time) {
		UNUSED(time);
		
		const Keyboard * const keyboard = Keyboard::Get();

		// Switch model.
		if (keyboard->GetKeyPress(DIK_UP, false)) {
			m_models[m_model_index]->MakePassive();
			m_model_index = (m_model_index + 1) % m_models.size();
			m_models[m_model_index]->MakeActive();
		}
		
		// Switch shader.
		if (keyboard->GetKeyPress(DIK_RIGHT, false)) {
			m_shader_index = (m_shader_index + 1) % m_shaders.size();
			SetShaders();
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, false)) {
			m_shader_index = std::min(m_shader_index - 1, m_shaders.size() - 1);
			SetShaders();
		}

		m_text->SetText(L"\n\n\n\n\n");
		m_text->AppendText(m_shader_names[m_shader_index]);
	}
}