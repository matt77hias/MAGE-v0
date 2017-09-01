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
		mat_emissive.SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));

		Material mat_bp;
		mat_bp.SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));
		mat_bp.SetSpecularReflectivityTexture(white);
		mat_bp.SetSpecularExponent(10.0f);
		Material mat_bp_tsnm = mat_bp;
		mat_bp_tsnm.SetNormalTexture(tsnm);

		Material mat_wd;
		mat_wd.SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));
		mat_wd.SetSpecularReflectivityTexture(white);
		mat_wd.SetMaterialParameter(Material::s_material_Ward_alpha_index, 0.5f);
		Material mat_wd_tsnm = mat_wd;
		mat_wd_tsnm.SetNormalTexture(tsnm);

		Material mat_ct;
		mat_ct.SetDiffuseReflectivity(RGBSpectrum(1.0f, 0.0f, 0.0f));
		mat_ct.SetSpecularReflectivityTexture(white);
		mat_ct.SetMaterialParameter(Material::s_material_roughness_index, 0.15f);
		mat_ct.SetMaterialParameter(Material::s_material_reflection_coefficient_index, 0.04f);
		Material mat_ct_tsnm = mat_ct;
		mat_ct_tsnm.SetNormalTexture(tsnm);

		m_shaders.reserve(17);
		m_shaders.emplace_back(std::make_pair(ShaderType::Emissive,               mat_emissive));
		m_shaders.emplace_back(std::make_pair(ShaderType::Lambertian,             mat_bp));
		m_shaders.emplace_back(std::make_pair(ShaderType::Phong,                  mat_bp));
		m_shaders.emplace_back(std::make_pair(ShaderType::ModifiedPhong,          mat_bp));
		m_shaders.emplace_back(std::make_pair(ShaderType::BlinnPhong,             mat_bp));
		m_shaders.emplace_back(std::make_pair(ShaderType::ModifiedBlinnPhong,     mat_bp));
		m_shaders.emplace_back(std::make_pair(ShaderType::Ward,                   mat_wd));
		m_shaders.emplace_back(std::make_pair(ShaderType::WardDuer,               mat_wd));
		m_shaders.emplace_back(std::make_pair(ShaderType::CookTorrance,           mat_ct));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMLambertian,         mat_bp_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMPhong,              mat_bp_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMModifiedPhong,      mat_bp_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMBlinnPhong,         mat_bp_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMModifiedBlinnPhong, mat_bp_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMWard,               mat_wd_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMWardDuer,           mat_wd_tsnm));
		m_shaders.emplace_back(std::make_pair(ShaderType::TSNMCookTorrance,       mat_ct_tsnm));

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

		case ShaderType::Lambertian: {
			m_settings->SetBRDF(BRDFType::Lambertian);
			break;
		}
		case ShaderType::Phong: {
			m_settings->SetBRDF(BRDFType::Phong);
			break;
		}
		case ShaderType::ModifiedPhong: {
			m_settings->SetBRDF(BRDFType::ModifiedPhong);
			break;
		}
		case ShaderType::BlinnPhong: {
			m_settings->SetBRDF(BRDFType::BlinnPhong);
			break;
		}
		case ShaderType::ModifiedBlinnPhong: {
			m_settings->SetBRDF(BRDFType::ModifiedBlinnPhong);
			break;
		}
		case ShaderType::Ward: {
			m_settings->SetBRDF(BRDFType::Ward);
			break;
		}
		case ShaderType::WardDuer: {
			m_settings->SetBRDF(BRDFType::WardDuer);
			break;
		}
		case ShaderType::CookTorrance: {
			m_settings->SetBRDF(BRDFType::CookTorrance);
			break;
		}
		case ShaderType::TSNMLambertian: {
			m_settings->SetBRDF(BRDFType::Lambertian);
			break;
		}
		case ShaderType::TSNMPhong: {
			m_settings->SetBRDF(BRDFType::Phong);
			break;
		}
		case ShaderType::TSNMModifiedPhong: {
			m_settings->SetBRDF(BRDFType::ModifiedPhong);
			break;
		}
		case ShaderType::TSNMBlinnPhong: {
			m_settings->SetBRDF(BRDFType::BlinnPhong);
			break;
		}
		case ShaderType::TSNMModifiedBlinnPhong: {
			m_settings->SetBRDF(BRDFType::ModifiedBlinnPhong);
			break;
		}
		case ShaderType::TSNMWard: {
			m_settings->SetBRDF(BRDFType::Ward);
			break;
		}
		case ShaderType::TSNMWardDuer: {
			m_settings->SetBRDF(BRDFType::WardDuer);
			break;
		}
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