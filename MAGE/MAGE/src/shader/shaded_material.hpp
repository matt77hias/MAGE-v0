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

	/**
	 An enumeration of the different Bidirectional Reflection Distribution Functions (BRDFs).

	 This contains:
	 @c Unknown,
	 @c Emissive,
	 @c Lambertian,
	 @c Phong, 
	 @c ModifiedPhong, 
	 @c BlinnPhong, and 
	 @c ModifiedBlinnPhong.
	 
	 Emperical BRDFs:
	 @c Ward and
	 @c WardDuer.

	 Physically-based BRDFs:
	 @c CookTorrance.
	 */
	enum struct BRDFType {
		Unknown = 0,
		Emissive,
		Lambertian,				// Diffuse component
		Phong,					// Diffuse + Specular component
		ModifiedPhong,			// Diffuse + Specular component
		BlinnPhong,				// Diffuse + Specular component
		ModifiedBlinnPhong,		// Diffuse + Specular component
		Ward,					// Diffuse + Specular component
		WardDuer,				// Diffuse + Specular component
		CookTorrance			// Diffuse + Specular component
	};

	/**
	 Deduces an appropriate shader for the given material and brdf.

	 @param[in]		material
					A reference to the material.
	 @param[in]		brdf
					The brdf.
	 @return		A shader matching the given material and brdf. 
	 */
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
		explicit ShadedMaterial(const Material &material, BRDFType brdf = BRDFType::Unknown);

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
		const Material &GetMaterial() const noexcept {
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

		/**
		 Sets the material of this shaded material to the given material.

		 @param[in]		material
						A reference to the material.
		 */
		void SetMaterial(Material &&material) {
			m_material = std::move(material);
		}

		/**
		 Returns the name of this shaded material.

		 @return		A reference to the name of this shaded material.
		 */
		const string &GetName() const noexcept {
			return m_material.GetName();
		}
		
		/**
		 Sets the name of this shaded material to the given name.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(const string &name) {
			m_material.SetName(name);
		}
		
		/**
		 Sets the name of this shaded material to the given name.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(string &&name) {
			m_material.SetName(std::move(name));
		}

		/**
		 Returns the transmission filter of this shaded material.

		 @return		A reference to the transmission filter of this shaded material.
		 */
		RGBSpectrum &GetTransmissionFilter() noexcept {
			return m_material.GetTransmissionFilter();
		}
		
		/**
		 Returns the transmission filter of this shaded material.

		 @return		A reference to the transmission filter of this shaded material.
		 */
		const RGBSpectrum &GetTransmissionFilter() const noexcept {
			return m_material.GetTransmissionFilter();
		}
		
		/**
		 Sets the transmission filter of this shaded material to the given transmission filter.

		 @param[in]		transmission_filter
						A reference to the transmission filter.
		 */
		void SetTransmissionFilter(const RGBSpectrum &transmission_filter) {
			m_material.SetTransmissionFilter(transmission_filter);
		}
		
		/**
		 Sets the transmission filter of this shaded material to the given transmission filter.

		 @param[in]		transmission_filter
						A reference to the transmission filter.
		 */
		void SetTransmissionFilter(RGBSpectrum &&transmission_filter) {
			m_material.SetTransmissionFilter(std::move(transmission_filter));
		}

		/**
		 Returns the ambient reflectivity of this shaded material.

		 @return		A reference to the ambient reflectivity of this shaded material.
		 */
		RGBSpectrum &GetAmbientReflectivity() noexcept {
			return m_material.GetAmbientReflectivity();
		}
		
		/**
		 Returns the ambient reflectivity of this shaded material.

		 @return		A reference to the ambient reflectivity of this shaded material.
		 */
		const RGBSpectrum &GetAmbientReflectivity() const noexcept {
			return m_material.GetAmbientReflectivity();
		}
		
		/**
		 Sets the ambient reflectivity of this shaded material to the given ambient reflectivity.

		 @param[in]		ambient_reflectivity
						A reference to the ambient reflectivity.
		 */
		void SetAmbientReflectivity(const RGBSpectrum &ambient_reflectivity) noexcept {
			m_material.SetAmbientReflectivity(ambient_reflectivity);
		}
		
		/**
		 Sets the ambient reflectivity of this shaded material to the given ambient reflectivity.

		 @param[in]		ambient_reflectivity
						A reference to the ambient reflectivity.
		 */
		void SetAmbientReflectivity(RGBSpectrum &&ambient_reflectivity) noexcept {
			m_material.SetAmbientReflectivity(std::move(ambient_reflectivity));
		}
		
		/**
		 Returns the ambient reflectivity texture of this shaded material.

		 @return		A pointer to the ambient reflectivity texture of this shaded material.
		 */
		SharedPtr< Texture > GetAmbientReflectivityTexture() const noexcept {
			return m_material.GetAmbientReflectivityTexture();
		}
		
		/**
		 Returns the shader resource view of the ambient reflectivity texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no ambient reflectivity texture.
		 @return		A pointer to the shader resource view of the ambient reflectivity texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetAmbientReflectivitySRV() const noexcept {
			return m_material.GetAmbientReflectivitySRV();
		}
		
		/**
		 Returns the address of the shader resource view of the ambient reflectivity texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no ambient reflectivity texture.
		 @return		The address of the shader resource view of the ambient reflectivity texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetAmbientReflectivitySRVAddress() const noexcept {
			return m_material.GetAmbientReflectivitySRVAddress();
		}
		
		/**
		 Sets the ambient reflectivity texture of this shaded material to the given ambient reflectivity texture.

		 @param[in]		ambient_reflectivity_texture
						A reference to the ambient reflectivity texture.
		 */
		void SetAmbientReflectivityTexture(SharedPtr< Texture > ambient_reflectivity_texture) {
			m_material.SetAmbientReflectivityTexture(ambient_reflectivity_texture);
		}

		/**
		 Returns the diffuse reflectivity of this shaded material.

		 @return		A reference to the diffuse reflectivity of this shaded material.
		 */
		RGBSpectrum &GetDiffuseReflectivity() noexcept {
			return m_material.GetDiffuseReflectivity();
		}
		
		/**
		 Returns the diffuse reflectivity of this shaded material.

		 @return		A reference to the diffuse reflectivity of this shaded material.
		 */
		const RGBSpectrum &GetDiffuseReflectivity() const noexcept {
			return m_material.GetDiffuseReflectivity();
		}
		
		/**
		 Sets the diffuse reflectivity of this shaded material to the given diffuse reflectivity.

		 @param[in]		diffuse_reflectivity
						A reference to the diffuse reflectivity.
		 */
		void SetDiffuseReflectivity(const RGBSpectrum &diffuse_reflectivity) noexcept {
			m_material.SetDiffuseReflectivity(diffuse_reflectivity);
		}
		
		/**
		 Sets the diffuse reflectivity of this shaded material to the given diffuse reflectivity.

		 @param[in]		diffuse_reflectivity
						A reference to the diffuse reflectivity.
		 */
		void SetDiffuseReflectivity(RGBSpectrum &&diffuse_reflectivity) noexcept {
			m_material.SetDiffuseReflectivity(std::move(diffuse_reflectivity));
		}
		
		/**
		 Returns the diffuse reflectivity texture of this shaded material.

		 @return		A pointer to the diffuse reflectivity texture of this shaded material.
		 */
		SharedPtr< Texture > GetDiffuseReflectivityTexture() const noexcept {
			return m_material.GetDiffuseReflectivityTexture();
		}
		
		/**
		 Returns the shader resource view of the diffuse reflectivity texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no diffuse reflectivity texture.
		 @return		A pointer to the shader resource view of the diffuse reflectivity texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetDiffuseReflectivitySRV() const noexcept {
			return m_material.GetDiffuseReflectivitySRV();
		}
		
		/**
		 Returns the address of the shader resource view of the diffuse reflectivity texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no diffuse reflectivity texture.
		 @return		The address of the shader resource view of the diffuse reflectivity texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetDiffuseReflectivitySRVAddress() const noexcept {
			return m_material.GetDiffuseReflectivitySRVAddress();
		}
		
		/**
		 Sets the diffuse reflectivity texture of this shaded material to the given diffuse reflectivity texture.

		 @param[in]		diffuse_reflectivity_texture
						A reference to the diffuse reflectivity texture.
		 */
		void SetDiffuseReflectivityTexture(SharedPtr< Texture > diffuse_reflectivity_texture) {
			m_material.SetDiffuseReflectivityTexture(diffuse_reflectivity_texture);
		}

		/**
		Returns the specular reflectivity of this shaded material.

		@return		A reference to the specular reflectivity of this shaded material.
		*/
		RGBSpectrum &GetSpecularReflectivity() noexcept {
			return m_material.GetSpecularReflectivity();
		}
		
		/**
		Returns the specular reflectivity of this shaded material.

		@return		A reference to the specular reflectivity of this shaded material.
		*/
		const RGBSpectrum &GetSpecularReflectivity() const noexcept {
			return m_material.GetSpecularReflectivity();
		}
		
		/**
		 Sets the specular reflectivity of this shaded material to the given specular reflectivity.

		 @param[in]		specular_reflectivity
						A reference to the specular reflectivity.
		 */
		void SetSpecularReflectivity(const RGBSpectrum &specular_reflectivity) noexcept {
			m_material.SetSpecularReflectivity(specular_reflectivity);
		}
		
		/**
		 Sets the specular reflectivity of this shaded material to the given specular reflectivity.

		 @param[in]		specular_reflectivity
						A reference to the specular reflectivity.
		 */
		void SetSpecularReflectivity(RGBSpectrum &&specular_reflectivity) noexcept {
			m_material.SetSpecularReflectivity(std::move(specular_reflectivity));
		}
		
		/**
		 Returns the specular reflectivity texture of this shaded material.

		 @return		A pointer to the specular reflectivity texture of this shaded material.
		 */
		SharedPtr< Texture > GetSpecularReflectivityTexture() const noexcept {
			return m_material.GetSpecularReflectivityTexture();
		}
		
		/**
		 Returns the shader resource view of the specular reflectivity texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no specular reflectivity texture.
		 @return		A pointer to the shader resource view of the specular reflectivity texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetSpecularReflectivitySRV() const noexcept {
			return m_material.GetSpecularReflectivitySRV();
		}
		
		/**
		 Returns the address of the shader resource view of the specular reflectivity texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no specular reflectivity texture.
		 @return		The address of the shader resource view of the specular reflectivity texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetSpecularReflectivitySRVAddress() const noexcept {
			return m_material.GetSpecularReflectivitySRVAddress();
		}
		
		/**
		 Sets the specular reflectivity texture of this shaded material to the given specular reflectivity texture.

		 @param[in]		specular_reflectivity_texture
						A reference to the specular reflectivity texture.
		 */
		void SetSpecularReflectivityTexture(SharedPtr< Texture > specular_reflectivity_texture) {
			m_material.SetSpecularReflectivityTexture(specular_reflectivity_texture);
		}

		/**
		 Returns the specular exponent of this shaded material.

		 @return		The specular exponent of this shaded material.
		 */
		float GetSpecularExponent() const noexcept {
			return m_material.GetSpecularExponent();
		}
		
		/**
		 Sets the specular exponent of this shaded material to the given specular exponent.

		 @param[in]		specular_exponent
						A reference to the specular exponent.
		 */
		void SetSpecularExponent(float specular_exponent) noexcept {
			m_material.SetSpecularExponent(specular_exponent);
		}
		
		/**
		 Returns the specular exponent texture of this shaded material.

		 @return		A pointer to the specular exponent texture of this shaded material.
		 */
		SharedPtr< Texture > GetSpecularExponentTexture() const noexcept {
			return m_material.GetSpecularExponentTexture();
		}
		
		/**
		 Returns the shader resource view of the specular exponent texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no specular exponent texture.
		 @return		A pointer to the shader resource view of the specular exponent texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetSpecularExponentSRV() const noexcept {
			return m_material.GetSpecularExponentSRV();
		}
		
		/**
		 Returns the address of the shader resource view of the specular exponent texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no specular exponent texture.
		 @return		The address of the shader resource view of the specular exponent texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetSpecularExponentSRVAddress() const noexcept {
			return m_material.GetSpecularExponentSRVAddress();
		}
		
		/**
		 Sets the specular exponent texture of this shaded material to the given specular exponent texture.

		 @param[in]		specular_exponent_texture
						A reference to the specular exponent texture.
		 */
		void SetSpecularExponentTexture(SharedPtr< Texture > specular_exponent_texture) {
			m_material.SetSpecularExponentTexture(specular_exponent_texture);
		}

		/**
		 Returns the dissolve of this shaded material.

		 @return		The dissolve of this shaded material.
		 */
		float GetDissolve() const noexcept {
			return m_material.GetDissolve();
		}
		
		/**
		 Sets the dissolve of this shaded material to the given dissolve.

		 @param[in]		dissolve
						A reference to the dissolve.
		 */
		void SetDissolve(float dissolve) noexcept {
			m_material.SetDissolve(dissolve);
		}
		
		/**
		 Returns the dissolve texture of this shaded material.

		 @return		A pointer to the dissolve texture of this shaded material.
		 */
		SharedPtr< Texture > GetDissolveTexture() const noexcept {
			return m_material.GetDissolveTexture();
		}
		
		/**
		 Returns the shader resource view of the dissolve texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no dissolve texture.
		 @return		A pointer to the shader resource view of the dissolve texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetDissolveSRV() const noexcept {
			return m_material.GetDissolveSRV();
		}
		
		/**
		 Returns the address of the shader resource view of the dissolve texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no dissolve texture.
		 @return		The address of the shader resource view of the dissolve texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetDissolveSRVAddress() const noexcept {
			return m_material.GetDissolveSRVAddress();
		}
		
		/**
		 Sets the dissolve texture of this shaded material to the given dissolve texture.

		 @param[in]		dissolve_texture
						A reference to the dissolve texture.
		 */
		void SetDissolveTexture(SharedPtr< Texture > dissolve_texture) {
			m_material.SetDissolveTexture(dissolve_texture);
		}

		/**
		 Returns the index of refraction of this shaded material.

		 @return		The index of refraction of this shaded material.
		 */
		float GetIndexOfRefraction() const noexcept {
			return m_material.GetIndexOfRefraction();
		}
		
		/**
		 Sets the index of refraction of this shaded material to the given index of refraction.

		 @param[in]		index_of_refraction
						A reference to the index of refraction.
		 */
		void SetIndexOfRefraction(float index_of_refraction) noexcept {
			m_material.SetIndexOfRefraction(index_of_refraction);
		}

		/**
		 Returns the decal texture of this shaded material.

		 @return		A pointer to the decal texture of this shaded material.
		 */
		SharedPtr< Texture > GetDecalTexture() const noexcept {
			return m_material.GetDecalTexture();
		}
		
		/**
		 Returns the decal resource view of the decal texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no decal texture.
		 @return		A pointer to the shader resource view of the decal texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetDecalSRV() const noexcept {
			return m_material.GetDecalSRV();
		}
		
		/**
		 Returns the address of the shader resource view of the decal texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no decal texture.
		 @return		The address of the shader resource view of the decal texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetDecalSRVAddress() const noexcept {
			return m_material.GetDecalSRVAddress();
		}
		
		/**
		 Sets the decal texture of this shaded material to the given decal texture.

		 @param[in]		decal_texture
						A reference to the decal texture.
		 */
		void SetDecalTexture(SharedPtr< Texture > decal_texture) {
			m_material.SetDecalTexture(decal_texture);
		}

		/**
		 Returns the displacement texture of this shaded material.

		 @return		A pointer to the displacement texture of this shaded material.
		 */
		SharedPtr< Texture > GetDisplacementTexture() const noexcept {
			return m_material.GetDisplacementTexture();
		}
		
		/**
		 Returns the shader resource view of the displacement texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no displacement texture.
		 @return		A pointer to the shader resource view of the displacement texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetDisplacementSRV() const noexcept {
			return m_material.GetDisplacementSRV();
		}
		
		/**
		 Returns the address of the shader resource view of the displacement texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no displacement texture.
		 @return		The address of the shader resource view of the displacement texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetDisplacementSRVAddress() const noexcept {
			return m_material.GetDisplacementSRVAddress();
		}
		
		/**
		 Sets the displacement texture of this shaded material to the given displacement texture.

		 @param[in]		displacement_texture
						A reference to the displacement texture.
		 */
		void SetDisplacementTexture(SharedPtr< Texture > displacement_texture) {
			m_material.SetDisplacementTexture(displacement_texture);
		}

		/**
		 Returns the normal texture of this shaded material.

		 @return		A pointer to the normal texture of this shaded material.
		 */
		SharedPtr< Texture > GetNormalTexture() const noexcept {
			return m_material.GetNormalTexture();
		}
		
		/**
		 Returns the shader resource view of the normal texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no normal texture.
		 @return		A pointer to the shader resource view of the normal texture of this shaded material.
		 */
		ID3D11ShaderResourceView *GetNormalSRV() const noexcept {
			return m_material.GetNormalSRV();
		}
		
		/**
		 Returns the address of the shader resource view of the normal texture of this shaded material.

		 @return		@c nullptr, if this shaded material has no normal texture.
		 @return		The address of the shader resource view of the normal texture of this shaded material.
		 */
		ID3D11ShaderResourceView * const *GetNormalSRVAddress() const noexcept {
			return m_material.GetNormalSRVAddress();
		}
		
		/**
		 Sets the normal texture of this shaded material to the given normal texture.

		 @param[in]		normal_texture
						A reference to the normal texture.
		 */
		void SetNormalTexture(SharedPtr< Texture > normal_texture) {
			m_material.SetNormalTexture(normal_texture);
		}

		/**
		 Returns the extra parameter of this shaded material at the given index.

		 @pre			@a index @c < {@link mage::Material::nb_extra_parameters}.
		 @param[in]		index
						The index.
		 @return		The extra parameter of this shaded material at the given index.
		 */
		float GetExtraParameter(size_t index) const noexcept {
			return m_material.GetExtraParameter(index);
		}

		/**
		 Sets the extra parameter of this shaded material at the given index to the given value.

		 @pre			@a index @c < {@link mage::Material::nb_extra_parameters}.
		 @param[in]		index
						The index.
		 @param[in]		value
						The value.
		 */
		void SetExtraParameter(size_t index, float value) noexcept {
			m_material.SetExtraParameter(index, value);
		}

		/**
		 Returns the shader of this shaded material.

		 @return		A reference to the shader of this shaded material.
		 */
		const CombinedShader &GetShader() const noexcept {
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

		/**
		 Sets the shader of this shaded material to the given shader.

		 @param[in]		shader
						A reference to the shader.
		 */
		void SetShader(CombinedShader &&shader) {
			m_shader = std::move(shader);
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