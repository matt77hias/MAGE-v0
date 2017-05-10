//-----------------------------------------------------------------------------
// Game Includes
//-----------------------------------------------------------------------------
#pragma region

#include "samples\brdf\brdf_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\bump_shader_factory.hpp"
#include "texture\texture_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Game Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BRDFScript::BRDFScript(SpriteText *text, const vector< ModelNode * > &models)
		: m_text(text), m_models(models), m_shaders(), m_shader_names(),
		m_model_index(0), m_shader_index(0) {

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
		SharedPtr< Texture > normal = CreateTexture(L"assets/sprites/bump/rock 4.dds");
		
		for (auto it = m_models.cbegin(); it != m_models.cend(); ++it) {
			(*it)->MakePassive();
			
			Material &material = (*it)->GetModel()->GetMaterial();
			material.m_diffuse_reflectivity         = RGBSpectrum(1.0f, 0.0f, 0.0f);
			material.m_diffuse_reflectivity_texture = white;
			material.m_specular_reflectivity        = RGBSpectrum(1.0f, 1.0f, 1.0f);
			material.m_specular_exponent            = 10.0f;
			material.m_normal_texture				= normal;
		}

		(*m_models.cbegin())->MakeActive();
	}

	void BRDFScript::InitShaders() {
		m_shaders.push_back(CreateDiffuseShader());
		m_shaders.push_back(CreateLambertianShader());
		m_shaders.push_back(CreatePhongShader());
		m_shaders.push_back(CreateModifiedPhongShader());
		m_shaders.push_back(CreateBlinnPhongShader());
		m_shaders.push_back(CreateModifiedBlinnPhongShader());
		m_shaders.push_back(CreateLambertianBumpShader());
		m_shaders.push_back(CreatePhongBumpShader());
		m_shaders.push_back(CreateModifiedPhongBumpShader());
		m_shaders.push_back(CreateBlinnPhongBumpShader());
		m_shaders.push_back(CreateModifiedBlinnPhongBumpShader());

		m_shader_names.push_back(L"Diffuse");
		m_shader_names.push_back(L"Lambertian");
		m_shader_names.push_back(L"Phong");
		m_shader_names.push_back(L"Modified Phong");
		m_shader_names.push_back(L"Blinn-Phong");
		m_shader_names.push_back(L"Modified Blinn-Phong");
		m_shader_names.push_back(L"Lambertian + Bump");
		m_shader_names.push_back(L"Phong + Bump");
		m_shader_names.push_back(L"Modified Phong + Bump");
		m_shader_names.push_back(L"Blinn-Phong + Bump");
		m_shader_names.push_back(L"Modified Blinn-Phong + Bump");

		Assert(m_shaders.size() == m_shader_names.size());
	}

	void BRDFScript::SetShaders() const {
		const CombinedShader shader = m_shaders[m_shader_index];
		for (auto it = m_models.cbegin(); it != m_models.cend(); ++it) {
			(*it)->GetModel()->GetShadedMaterial()->SetShader(shader);
		}
	}

	void BRDFScript::Update(double time) {
		UNUSED(time);
		
		const Keyboard * const keyboard = g_engine->GetInputManager()->GetKeyboard();

		// Switch model.
		if (keyboard->GetKeyPress(DIK_SPACE, false)) {
			m_models[m_model_index]->MakePassive();
			m_model_index = (m_model_index + 1) % m_models.size();
			m_models[m_model_index]->MakeActive();
		}
		
		// Switch shader.
		if (keyboard->GetKeyPress(DIK_RALT, false)) {
			m_shader_index = (m_shader_index + 1) % m_shaders.size();
			SetShaders();
		}
		else if (keyboard->GetKeyPress(DIK_LALT, false)) {
			m_shader_index = std::min(m_shader_index - 1, m_shaders.size() - 1);
			SetShaders();
		}

		m_text->SetText(L"\n\n\n");
		m_text->AppendText(m_shader_names[m_shader_index]);
	}
}