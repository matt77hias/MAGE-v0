#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	enum BRDFType {
		BRDFType_Unknown = 0,
		BRDFType_Emissive,
		BRDFType_Lambertian,
		BRDFType_Phong,
		BRDFType_ModifiedPhong,
		BRDFType_BlinnPhong,
		BRDFType_ModifiedBlinnPhong,
		BRDFType_Ward,
		BRDFType_WardDuer,
		BRDFType_CookTorrance
	};

	const CombinedShader DeduceShader(const Material &material, BRDFType brdf);

	/**
	 A struct of shaded materials.
	 */
	struct ShadedMaterial final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shaded material.

		 @param[in]		material
						A reference to the material.
		 @param[in]		brdf
						The brdf type.
		 */
		explicit ShadedMaterial(const Material &material, BRDFType brdf = BRDFType_Unknown);

		/**
		 Constructs a shaded material.

		 @param[in]		material
						A reference to the material.
		 @param[in]		shader
						A reference to the shader.
		 */
		explicit ShadedMaterial(const Material &material, const CombinedShader &shader);

		/**
		 Constructs a shaded material from the given shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to copy.
		 */
		ShadedMaterial(const ShadedMaterial &shaded_material) = default;

		/**
		 Constructs a shaded material by moving the given shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to move.
		 */
		ShadedMaterial(ShadedMaterial &&shaded_material) = default;

		/**
		 Destructs this shaded material.
		 */
		~ShadedMaterial() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shaded material to this shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to copy.
		 @return		A reference to the copy of the given shaded material
						(i.e. this shaded material).
		 */
		ShadedMaterial &operator=(const ShadedMaterial &shaded_material) = default;

		/**
		 Moves the given shaded material to this shaded material.

		 @param[in]		shaded_material
						A reference to the shaded material to move.
		 @return		A reference to the moved shaded material
						(i.e. this shaded material).
		 */
		ShadedMaterial &operator=(ShadedMaterial &&shaded_material) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Prepares this shaded material for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 @param[in]		lighting
						A reference to the lighting buffer.
		 */
		void PrepareShading(ID3D11Buffer *transform, const Lighting &lighting) const {
			m_shader.PrepareShading(transform, m_material, lighting);
		}

		/**
		 Returns the material of this shaded material.

		 @return		A reference to the material of this shaded material.
		 */
		const Material &GetMaterial() const {
			return m_material;
		}

		/**
		 Sets the material of this shaded material to the given material.

		 @param[in]		material
						A reference to the material.
		 */
		void SetMaterial(const Material &material) {
			m_material = material;
		}

		const string &GetName() const {
			return m_material.GetName();
		}
		void SetName(const string &name) {
			m_material.SetName(name);
		}

		RGBSpectrum &GetTransmissionFilter() {
			return m_material.GetTransmissionFilter();
		}
		const RGBSpectrum &GetTransmissionFilter() const {
			return m_material.GetTransmissionFilter();
		}
		void SetTransmissionFilter(const RGBSpectrum &transmission_filter) {
			m_material.SetTransmissionFilter(transmission_filter);
		}

		RGBSpectrum &GetAmbientReflectivity() {
			return m_material.GetAmbientReflectivity();
		}
		const RGBSpectrum &GetAmbientReflectivity() const {
			return m_material.GetAmbientReflectivity();
		}
		void SetAmbientReflectivity(const RGBSpectrum &ambient_reflectivity) {
			m_material.SetAmbientReflectivity(ambient_reflectivity);
		}
		SharedPtr< Texture > GetAmbientReflectivityTexture() const {
			return m_material.GetAmbientReflectivityTexture();
		}
		ID3D11ShaderResourceView *GetAmbientReflectivitySRV() const {
			return m_material.GetAmbientReflectivitySRV();
		}
		ID3D11ShaderResourceView * const *GetAmbientReflectivitySRVAddress() const {
			return m_material.GetAmbientReflectivitySRVAddress();
		}
		void SetAmbientReflectivityTexture(SharedPtr< Texture > ambient_reflectivity_texture) {
			m_material.SetAmbientReflectivityTexture(ambient_reflectivity_texture);
		}

		RGBSpectrum &GetDiffuseReflectivity() {
			return m_material.GetDiffuseReflectivity();
		}
		const RGBSpectrum &GetDiffuseReflectivity() const {
			return m_material.GetDiffuseReflectivity();
		}
		void SetDiffuseReflectivity(const RGBSpectrum &diffuse_reflectivity) {
			m_material.SetDiffuseReflectivity(diffuse_reflectivity);
		}
		SharedPtr< Texture > GetDiffuseReflectivityTexture() const {
			return m_material.GetDiffuseReflectivityTexture();
		}
		ID3D11ShaderResourceView *GetDiffuseReflectivitySRV() const {
			return m_material.GetDiffuseReflectivitySRV();
		}
		ID3D11ShaderResourceView * const *GetDiffuseReflectivitySRVAddress() const {
			return m_material.GetDiffuseReflectivitySRVAddress();
		}
		void SetDiffuseReflectivityTexture(SharedPtr< Texture > diffuse_reflectivity_texture) {
			m_material.SetDiffuseReflectivityTexture(diffuse_reflectivity_texture);
		}

		RGBSpectrum &GetSpecularReflectivity() {
			return m_material.GetSpecularReflectivity();
		}
		const RGBSpectrum &GetSpecularReflectivity() const {
			return m_material.GetSpecularReflectivity();
		}
		void SetSpecularReflectivity(const RGBSpectrum &specular_reflectivity) {
			m_material.SetSpecularReflectivity(specular_reflectivity);
		}
		SharedPtr< Texture > GetSpecularReflectivityTexture() const {
			return m_material.GetSpecularReflectivityTexture();
		}
		ID3D11ShaderResourceView *GetSpecularReflectivitySRV() const {
			return m_material.GetSpecularReflectivitySRV();
		}
		ID3D11ShaderResourceView * const *GetSpecularReflectivitySRVAddress() const {
			return m_material.GetSpecularReflectivitySRVAddress();
		}
		void SetSpecularReflectivityTexture(SharedPtr< Texture > specular_reflectivity_texture) {
			m_material.SetSpecularReflectivityTexture(specular_reflectivity_texture);
		}

		float GetSpecularExponent() const {
			return m_material.GetSpecularExponent();
		}
		void SetSpecularExponent(float specular_exponent) {
			m_material.SetSpecularExponent(specular_exponent);
		}
		SharedPtr< Texture > GetSpecularExponentTexture() const {
			return m_material.GetSpecularExponentTexture();
		}
		ID3D11ShaderResourceView *GetSpecularExponentSRV() const {
			return m_material.GetSpecularExponentSRV();
		}
		ID3D11ShaderResourceView * const *GetSpecularExponentSRVAddress() const {
			return m_material.GetSpecularExponentSRVAddress();
		}
		void SetSpecularExponentTexture(SharedPtr< Texture > specular_exponent_texture) {
			m_material.SetSpecularExponentTexture(specular_exponent_texture);
		}

		float GetDissolve() const {
			return m_material.GetDissolve();
		}
		void SetDissolve(float dissolve) {
			m_material.SetDissolve(dissolve);
		}
		SharedPtr< Texture > GetDissolveTexture() const {
			return m_material.GetDissolveTexture();
		}
		ID3D11ShaderResourceView *GetDissolveSRV() const {
			return m_material.GetDissolveSRV();
		}
		ID3D11ShaderResourceView * const *GetDissolveSRVAddress() const {
			return m_material.GetDissolveSRVAddress();
		}
		void SetDissolveTexture(SharedPtr< Texture > dissolve_texture) {
			m_material.SetDissolveTexture(dissolve_texture);
		}

		float GetIndexOfRefraction() const {
			return m_material.GetIndexOfRefraction();
		}
		void SetIndexOfRefraction(float index_of_refraction) {
			m_material.SetIndexOfRefraction(index_of_refraction);
		}

		SharedPtr< Texture > GetDecalTexture() const {
			return m_material.GetDecalTexture();
		}
		ID3D11ShaderResourceView *GetDecalSRV() const {
			return m_material.GetDecalSRV();
		}
		ID3D11ShaderResourceView * const *GetDecalSRVAddress() const {
			return m_material.GetDecalSRVAddress();
		}
		void SetDecalTexture(SharedPtr< Texture > decal_texture) {
			m_material.SetDecalTexture(decal_texture);
		}

		SharedPtr< Texture > GetDisplacementTexture() const {
			return m_material.GetDisplacementTexture();
		}
		ID3D11ShaderResourceView *GetDisplacementSRV() const {
			return m_material.GetDisplacementSRV();
		}
		ID3D11ShaderResourceView * const *GetDisplacementSRVAddress() const {
			return m_material.GetDisplacementSRVAddress();
		}
		void SetDisplacementTexture(SharedPtr< Texture > displacement_texture) {
			m_material.SetDisplacementTexture(displacement_texture);
		}

		SharedPtr< Texture > GetNormalTexture() const {
			return m_material.GetNormalTexture();
		}
		ID3D11ShaderResourceView *GetNormalSRV() const {
			return m_material.GetNormalSRV();
		}
		ID3D11ShaderResourceView * const *GetNormalSRVAddress() const {
			return m_material.GetNormalSRVAddress();
		}
		void SetNormalTexture(SharedPtr< Texture > normal_texture) {
			m_material.SetNormalTexture(normal_texture);
		}

		float GetParameter1() const {
			return m_material.GetParameter1();
		}
		void SetParameter1(float param1) {
			m_material.SetParameter1(param1);
		}
		float GetParameter2() const {
			return m_material.GetParameter2();
		}
		void SetParameter2(float param2) {
			m_material.SetParameter2(param2);
		}
		float GetParameter3() const {
			return m_material.GetParameter3();
		}
		void SetParameter3(float param3) {
			m_material.SetParameter3(param3);
		}
		float GetParameter4() const {
			return m_material.GetParameter4();
		}
		void SetParameter4(float param4) {
			m_material.SetParameter4(param4);
		}

		/**
		 Returns the shader of this shaded material.

		 @return		A reference to the shader of this shaded material.
		 */
		const CombinedShader &GetShader() const {
			return m_shader;
		}

		/**
		 Sets the shader of this shaded material to the given shader.

		 @param[in]		shader
						A reference to the shader.
		 */
		void SetShader(const CombinedShader &shader) {
			m_shader = shader;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SetDefaultTextures();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The shader of this shaded material.
		 */
		CombinedShader m_shader;

		bool m_automatic_shader_selection;

		BRDFType m_brdf;

		/**
		 The material of this shaded material.
		 */
		Material m_material;
	};
}