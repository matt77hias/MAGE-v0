//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shaded_material.hpp"
#include "shader\basic_shader_factory.hpp"
#include "shader\bump_shader_factory.hpp"
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
				return CreateLambertianBumpShader();
			case BRDFType::Phong:
				return CreatePhongBumpShader();
			case BRDFType::ModifiedPhong:
				return CreateModifiedPhongBumpShader();
			case BRDFType::BlinnPhong:
				return CreateBlinnPhongBumpShader();
			case BRDFType::ModifiedBlinnPhong:
				return CreateModifiedBlinnPhongBumpShader();
			case BRDFType::Ward:
				return CreateWardBumpShader();
			case BRDFType::WardDuer:
				return CreateWardDuerBumpShader();
			case BRDFType::CookTorrance:
				return CreateCookTorranceBumpShader();
			default:
				const RGBSpectrum specular = material.GetSpecularReflectivity();
				const float specular_sum = specular.x + specular.y + specular.z;
				if (specular_sum > 0.0f) {
					return CreateModifiedBlinnPhongBumpShader();
				}
				else {
					return CreateLambertianBumpShader();
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