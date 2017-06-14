//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shaded_material.hpp"
#include "shader\basic_shader_factory.hpp"
#include "shader\tsnm_shader_factory.hpp"
#include "texture\texture_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	const CombinedShader DeduceShader(const Material &material, BRDFType brdf) {
		
		if (material.GetNormalTexture()) {
			switch (brdf) {

			case BRDFType::Lambertian:
				return CreateLambertianTSNMShader();
			case BRDFType::Phong:
				return CreatePhongTSNMShader();
			case BRDFType::ModifiedPhong:
				return CreateModifiedPhongTSNMShader();
			case BRDFType::BlinnPhong:
				return CreateBlinnPhongTSNMShader();
			case BRDFType::ModifiedBlinnPhong:
				return CreateModifiedBlinnPhongTSNMShader();
			case BRDFType::Ward:
				return CreateWardTSNMShader();
			case BRDFType::WardDuer:
				return CreateWardDuerTSNMShader();
			case BRDFType::CookTorrance:
				return CreateCookTorranceTSNMShader();
			default:
				const RGBSpectrum specular = material.GetSpecularReflectivity();
				const float specular_sum = specular.x + specular.y + specular.z;
				if (specular_sum > 0.0f) {
					return CreateModifiedBlinnPhongTSNMShader();
				}
				else {
					return CreateLambertianTSNMShader();
				}
			}
		}
		else {
			switch (brdf) {

			case BRDFType::Emissive:
				return CreateEmissiveShader();
			case BRDFType::Lambertian:
				return CreateLambertianShader();
			case BRDFType::Phong:
				return CreatePhongShader();
			case BRDFType::ModifiedPhong:
				return CreateModifiedPhongShader();
			case BRDFType::BlinnPhong:
				return CreateBlinnPhongShader();
			case BRDFType::ModifiedBlinnPhong:
				return CreateModifiedBlinnPhongShader();
			case BRDFType::Ward:
				return CreateWardShader();
			case BRDFType::WardDuer:
				return CreateWardDuerShader();
			case BRDFType::CookTorrance:
				return CreateCookTorranceShader();
			default:
				const RGBSpectrum specular = material.GetSpecularReflectivity();
				const float specular_sum = specular.x + specular.y + specular.z;
				if (specular_sum > 0.0f) {
					return CreateModifiedBlinnPhongShader();
				}
				else {
					return CreateLambertianShader();
				}
			}
		}
	}

	ShadedMaterial::ShadedMaterial(const Material &material, BRDFType brdf)
		: m_shader(DeduceShader(material, brdf)), m_automatic_shader_selection(true),
		m_brdf(brdf), m_material(material) {

		SetDefaultTextures();
	}

	ShadedMaterial::ShadedMaterial(const Material &material, const CombinedShader &shader)
		: m_shader(shader), m_automatic_shader_selection(false),
		m_brdf(BRDFType::Unknown), m_material(material) {

		SetDefaultTextures();
	}

	void ShadedMaterial::SetDefaultTextures() {
		const SharedPtr< Texture > white = CreateWhiteTexture();
		
		if (!GetDiffuseReflectivitySRV()) {
			SetDiffuseReflectivityTexture(white);
		}
		if (!GetSpecularReflectivitySRV()) {
			SetSpecularReflectivityTexture(white);
		}
	} 
}