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
		m_shaders(), m_model_index(0), m_shader_index(0),
		m_mat_emissive(), m_mat_basic(), m_mat_tsnm() {

		Assert(m_settings);
		Assert(m_text);

		InitMaterials();
		InitModels();
		InitShaders();
	}

	BRDFScript::BRDFScript(BRDFScript &&script) = default;

	BRDFScript::~BRDFScript() {
		m_models.clear();
		m_shaders.clear();
	}

	void BRDFScript::InitMaterials() {
		auto white = CreateWhiteTexture();
		auto tsnm = ResourceManager::Get()->GetOrCreateTexture(L"assets/sprites/tsnm/rock 4.dds");

		m_mat_emissive.DissableLightInteraction();
		m_mat_emissive.SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));
		
		m_mat_basic.SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));
		m_mat_basic.SetDiffuseReflectivityTexture(white);
		m_mat_basic.SetSpecularReflectivity(RGBSpectrum(1.0f, 1.0f, 1.0f));
		m_mat_basic.SetSpecularReflectivityTexture(white);
		m_mat_basic.SetSpecularExponent(10.0f);
		m_mat_basic.SetExtraParameter(0, 0.5f);
		m_mat_basic.SetExtraParameter(1, 0.15f);
		m_mat_basic.SetExtraParameter(2, 0.04f);

		m_mat_tsnm = m_mat_basic;
		m_mat_tsnm.SetNormalTexture(tsnm);
	}

	void BRDFScript::InitModels() noexcept {
		for (const auto &node : m_models) {
			node->MakePassive();
		}

		m_models[0]->MakeActive();
	}

	void BRDFScript::InitShaders() noexcept {
		m_shaders.reserve(17);
		m_shaders.emplace_back(ShaderType::Emissive);
		m_shaders.emplace_back(ShaderType::Lambertian);
		m_shaders.emplace_back(ShaderType::Phong);
		m_shaders.emplace_back(ShaderType::ModifiedPhong);
		m_shaders.emplace_back(ShaderType::BlinnPhong);
		m_shaders.emplace_back(ShaderType::ModifiedBlinnPhong);
		m_shaders.emplace_back(ShaderType::Ward);
		m_shaders.emplace_back(ShaderType::WardDuer);
		m_shaders.emplace_back(ShaderType::CookTorrance);
		m_shaders.emplace_back(ShaderType::TSNMLambertian);
		m_shaders.emplace_back(ShaderType::TSNMPhong);
		m_shaders.emplace_back(ShaderType::TSNMModifiedPhong);
		m_shaders.emplace_back(ShaderType::TSNMBlinnPhong);
		m_shaders.emplace_back(ShaderType::TSNMModifiedBlinnPhong);
		m_shaders.emplace_back(ShaderType::TSNMWard);
		m_shaders.emplace_back(ShaderType::TSNMWardDuer);
		m_shaders.emplace_back(ShaderType::TSNMCookTorrance);

		SetShader();
	}

	void BRDFScript::SetMaterial(const Material &material) noexcept {
		for (const auto &node : m_models) {
			node->GetModel()->SetMaterial(material);
		}
	}

	void BRDFScript::SetShader() noexcept {

		switch (m_shaders[m_shader_index]) {
		
		case ShaderType::Emissive: {
			SetMaterial(m_mat_emissive);
			break;
		}
		case ShaderType::Lambertian: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::Lambertian);
			break;
		}
		case ShaderType::Phong: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::Phong);
			break;
		}
		case ShaderType::ModifiedPhong: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::ModifiedPhong);
			break;
		}
		case ShaderType::BlinnPhong: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::BlinnPhong);
			break;
		}
		case ShaderType::ModifiedBlinnPhong: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::ModifiedBlinnPhong);
			break;
		}
		case ShaderType::Ward: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::Ward);
			break;
		}
		case ShaderType::WardDuer: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::WardDuer);
			break;
		}
		case ShaderType::CookTorrance: {
			SetMaterial(m_mat_basic);
			m_settings->SetBRDF(BRDFType::CookTorrance);
			break;
		}
		case ShaderType::TSNMLambertian: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::Lambertian);
			break;
		}
		case ShaderType::TSNMPhong: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::Phong);
			break;
		}
		case ShaderType::TSNMModifiedPhong: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::ModifiedPhong);
			break;
		}
		case ShaderType::TSNMBlinnPhong: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::BlinnPhong);
			break;
		}
		case ShaderType::TSNMModifiedBlinnPhong: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::ModifiedBlinnPhong);
			break;
		}
		case ShaderType::TSNMWard: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::Ward);
			break;
		}
		case ShaderType::TSNMWardDuer: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::WardDuer);
			break;
		}
		case ShaderType::TSNMCookTorrance: {
			SetMaterial(m_mat_tsnm);
			m_settings->SetBRDF(BRDFType::CookTorrance);
			break;
		}
		}
	}

	void BRDFScript::PrintText() {
		switch (m_shaders[m_shader_index]) {

		case ShaderType::Emissive: {
			m_text->SetText(L"\n\n\n\n\nEmissive");
			break;
		}
		case ShaderType::Lambertian: {
			m_text->SetText(L"\n\n\n\n\nLambertian");
			break;
		}
		case ShaderType::Phong: {
			m_text->SetText(L"\n\n\n\n\nPhong");
			break;
		}
		case ShaderType::ModifiedPhong: {
			m_text->SetText(L"\n\n\n\n\nModified Phong");
			break;
		}
		case ShaderType::BlinnPhong: {
			m_text->SetText(L"\n\n\n\n\nBlinn-Phong");
			break;
		}
		case ShaderType::ModifiedBlinnPhong: {
			m_text->SetText(L"\n\n\n\n\nModified Blinn-Phong");
			break;
		}
		case ShaderType::Ward: {
			m_text->SetText(L"\n\n\n\n\nWard");
			break;
		}
		case ShaderType::WardDuer: {
			m_text->SetText(L"\n\n\n\n\nWard-Duer");
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
		case ShaderType::TSNMPhong: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Phong");
			break;
		}
		case ShaderType::TSNMModifiedPhong: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Modified Phong");
			break;
		}
		case ShaderType::TSNMBlinnPhong: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Blinn-Phong");
			break;
		}
		case ShaderType::TSNMModifiedBlinnPhong: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Modified Blinn-Phong");
			break;
		}
		case ShaderType::TSNMWard: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Ward");
			break;
		}
		case ShaderType::TSNMWardDuer: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Ward-Duer");
			break;
		}
		case ShaderType::TSNMCookTorrance: {
			m_text->SetText(L"\n\n\n\n\nTSNM + Cook-Torrance");
			break;
		}
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
		else if (keyboard->GetKeyPress(DIK_DOWN, false)) {
			m_models[m_model_index]->MakePassive();
			m_model_index = std::min(m_model_index - 1, m_models.size() - 1);
			m_models[m_model_index]->MakeActive();
		}

		// Switch shader.
		if (keyboard->GetKeyPress(DIK_RIGHT, false)) {
			m_shader_index = (m_shader_index + 1) % m_shaders.size();
			SetShader();
		}
		else if (keyboard->GetKeyPress(DIK_LEFT, false)) {
			m_shader_index = std::min(m_shader_index - 1, m_shaders.size() - 1);
			SetShader();
		}

		PrintText();
	}
}