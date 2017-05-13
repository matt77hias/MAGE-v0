#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"
#include "texture\texture.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of materials.
	 */
	struct Material final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a material.

		 @param[in]		name
						A reference to the name of the material.
		 */
		explicit Material(const string &name)
			: m_name(name), m_transmission_filter(),
			m_ambient_reflectivity(), m_ambient_reflectivity_texture(),
			m_diffuse_reflectivity(), m_diffuse_reflectivity_texture(),
			m_specular_reflectivity(), m_specular_reflectivity_texture(),
			m_specular_exponent(1.0f), m_specular_exponent_texture(),
			m_dissolve(1.0f), m_dissolve_texture(),
			m_index_of_refraction(1.0f), m_decal_texture(),
			m_displacement_texture(), m_normal_texture(),
			m_param1(0.0f), m_param2(0.0f), m_param3(0.0f), m_param4(0.0f) {}
		
		/**
		 Constructs a material from the given material.

		 @param[in]		material
						A reference to the material to copy.
		 */
		Material(const Material &material) = default;
		
		/**
		 Constructs a material by moving the given material.
		 
		 @param[in]		material
						A reference to the material to move.
		 */
		Material(Material &&material) = default;
		
		/**
		 Destructs this material.
		 */
		~Material() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given material to this material.

		 @param[in]		material
						A reference to the material to copy.
		 @return		A reference to the copy of the given material
						(i.e. this material).
		 */
		Material &operator=(const Material &material) = default;

		/**
		 Moves the given material to this material.

		 @param[in]		material
						A reference to the material to move.
		 @return		A reference to the moved material
						(i.e. this material).
		 */
		Material &operator=(Material &&material) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		const string &GetName() const noexcept {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}

		RGBSpectrum &GetTransmissionFilter() noexcept {
			return m_transmission_filter;
		}
		const RGBSpectrum &GetTransmissionFilter() const noexcept {
			return m_transmission_filter;
		}
		void SetTransmissionFilter(const RGBSpectrum &transmission_filter) noexcept {
			m_transmission_filter = transmission_filter;
		}

		RGBSpectrum &GetAmbientReflectivity() noexcept {
			return m_ambient_reflectivity;
		}
		const RGBSpectrum &GetAmbientReflectivity() const noexcept {
			return m_ambient_reflectivity;
		}
		void SetAmbientReflectivity(const RGBSpectrum &ambient_reflectivity) noexcept {
			m_ambient_reflectivity = ambient_reflectivity;
		}
		SharedPtr< Texture > GetAmbientReflectivityTexture() const noexcept {
			return m_ambient_reflectivity_texture;
		}
		ID3D11ShaderResourceView *GetAmbientReflectivitySRV() const noexcept {
			return m_ambient_reflectivity_texture ? m_ambient_reflectivity_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetAmbientReflectivitySRVAddress() const noexcept {
			return m_ambient_reflectivity_texture ? m_ambient_reflectivity_texture->GetAddress() : nullptr;
		}
		void SetAmbientReflectivityTexture(SharedPtr< Texture > ambient_reflectivity_texture) {
			m_ambient_reflectivity_texture = ambient_reflectivity_texture;
		}
		
		RGBSpectrum &GetDiffuseReflectivity() noexcept {
			return m_diffuse_reflectivity;
		}
		const RGBSpectrum &GetDiffuseReflectivity() const noexcept {
			return m_diffuse_reflectivity;
		}
		void SetDiffuseReflectivity(const RGBSpectrum &diffuse_reflectivity) noexcept {
			m_diffuse_reflectivity = diffuse_reflectivity;
		}
		SharedPtr< Texture > GetDiffuseReflectivityTexture() const noexcept {
			return m_diffuse_reflectivity_texture;
		}
		ID3D11ShaderResourceView *GetDiffuseReflectivitySRV() const noexcept {
			return m_diffuse_reflectivity_texture ? m_diffuse_reflectivity_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetDiffuseReflectivitySRVAddress() const noexcept {
			return m_diffuse_reflectivity_texture ? m_diffuse_reflectivity_texture->GetAddress() : nullptr;
		}
		void SetDiffuseReflectivityTexture(SharedPtr< Texture > diffuse_reflectivity_texture) {
			m_diffuse_reflectivity_texture = diffuse_reflectivity_texture;
		}
		
		RGBSpectrum &GetSpecularReflectivity() noexcept {
			return m_specular_reflectivity;
		}
		const RGBSpectrum &GetSpecularReflectivity() const noexcept {
			return m_specular_reflectivity;
		}
		void SetSpecularReflectivity(const RGBSpectrum &specular_reflectivity) noexcept {
			m_specular_reflectivity = specular_reflectivity;
		}
		SharedPtr< Texture > GetSpecularReflectivityTexture() const noexcept {
			return m_specular_reflectivity_texture;
		}
		ID3D11ShaderResourceView *GetSpecularReflectivitySRV() const noexcept {
			return m_specular_reflectivity_texture ? m_specular_reflectivity_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetSpecularReflectivitySRVAddress() const noexcept {
			return m_specular_reflectivity_texture ? m_specular_reflectivity_texture->GetAddress() : nullptr;
		}
		void SetSpecularReflectivityTexture(SharedPtr< Texture > specular_reflectivity_texture) {
			m_specular_reflectivity_texture = specular_reflectivity_texture;
		}
		
		float GetSpecularExponent() const noexcept {
			return m_specular_exponent;
		}
		void SetSpecularExponent(float specular_exponent) noexcept {
			m_specular_exponent = specular_exponent;
		}
		SharedPtr< Texture > GetSpecularExponentTexture() const noexcept {
			return m_specular_exponent_texture;
		}
		ID3D11ShaderResourceView *GetSpecularExponentSRV() const noexcept {
			return m_specular_exponent_texture ? m_specular_exponent_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetSpecularExponentSRVAddress() const noexcept {
			return m_specular_exponent_texture ? m_specular_exponent_texture->GetAddress() : nullptr;
		}
		void SetSpecularExponentTexture(SharedPtr< Texture > specular_exponent_texture) {
			m_specular_exponent_texture = specular_exponent_texture;
		}

		float GetDissolve() const noexcept {
			return m_dissolve;
		}
		void SetDissolve(float dissolve) noexcept {
			m_dissolve = dissolve;
		}
		SharedPtr< Texture > GetDissolveTexture() const noexcept {
			return m_dissolve_texture;
		}
		ID3D11ShaderResourceView *GetDissolveSRV() const noexcept {
			return m_dissolve_texture ? m_dissolve_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetDissolveSRVAddress() const noexcept {
			return m_dissolve_texture ? m_dissolve_texture->GetAddress() : nullptr;
		}
		void SetDissolveTexture(SharedPtr< Texture > dissolve_texture) {
			m_dissolve_texture = dissolve_texture;
		}

		float GetIndexOfRefraction() const noexcept {
			return m_index_of_refraction;
		}
		void SetIndexOfRefraction(float index_of_refraction) noexcept {
			m_index_of_refraction = index_of_refraction;
		}

		SharedPtr< Texture > GetDecalTexture() const noexcept {
			return m_decal_texture;
		}
		ID3D11ShaderResourceView *GetDecalSRV() const noexcept {
			return m_decal_texture ? m_decal_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetDecalSRVAddress() const noexcept {
			return m_decal_texture ? m_decal_texture->GetAddress() : nullptr;
		}
		void SetDecalTexture(SharedPtr< Texture > decal_texture) {
			m_decal_texture = decal_texture;
		}
		
		SharedPtr< Texture > GetDisplacementTexture() const noexcept {
			return m_displacement_texture;
		}
		ID3D11ShaderResourceView *GetDisplacementSRV() const noexcept {
			return m_displacement_texture ? m_displacement_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetDisplacementSRVAddress() const noexcept {
			return m_displacement_texture ? m_displacement_texture->GetAddress() : nullptr;
		}
		void SetDisplacementTexture(SharedPtr< Texture > displacement_texture) {
			m_displacement_texture = displacement_texture;
		}

		SharedPtr< Texture > GetNormalTexture() const noexcept {
			return m_normal_texture;
		}
		ID3D11ShaderResourceView *GetNormalSRV() const noexcept {
			return m_normal_texture ? m_normal_texture->Get() : nullptr;
		}
		ID3D11ShaderResourceView * const *GetNormalSRVAddress() const noexcept {
			return m_normal_texture ? m_normal_texture->GetAddress() : nullptr;
		}
		void SetNormalTexture(SharedPtr< Texture > normal_texture) {
			m_normal_texture = normal_texture;
		}

		float GetParameter1() const noexcept {
			return m_param1;
		}
		void SetParameter1(float param1) noexcept {
			m_param1 = param1;
		}
		float GetParameter2() const noexcept {
			return m_param2;
		}
		void SetParameter2(float param2) noexcept {
			m_param2 = param2;
		}
		float GetParameter3() const noexcept {
			return m_param3;
		}
		void SetParameter3(float param3) noexcept {
			m_param3 = param3;
		}
		float GetParameter4() const noexcept {
			return m_param4;
		}
		void SetParameter4(float param4) noexcept {
			m_param4 = param4;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The name of this material.
		 */
		string m_name;

		/**
		 The transmission filter of this material.
		 
		 Any light passing through the material is filtered by the transmission 
		 filter, which only allows the specific colors to pass through.
		 */
		RGBSpectrum m_transmission_filter;

		/**
		 The ambient reflectivity of this material.
		 */
		RGBSpectrum m_ambient_reflectivity;

		/**
		 A pointer to the ambient reflectivity texture of this material.
		 */
		SharedPtr< Texture > m_ambient_reflectivity_texture;

		/**
		 The diffuse reflectivity of this material.
		 */
		RGBSpectrum m_diffuse_reflectivity;

		/**
		 A pointer to the diffuse reflectivity texture of this material.
		 */
		SharedPtr< Texture > m_diffuse_reflectivity_texture;

		/**
		 The specular reflectivity of this material.
		 */
		RGBSpectrum m_specular_reflectivity;

		/**
		 A pointer to the specular reflectivity texture of this material.
		 */
		SharedPtr< Texture > m_specular_reflectivity_texture;

		/**
		 The specular exponent (surface roughness) of this material.

		 A high exponent results in a tight, concentrated highlight.
		 Values normally range from 0 to 1000.
		 */
		float m_specular_exponent;

		/**
		 A pointer to the specular exponent texture of this material.
		 */
		SharedPtr< Texture > m_specular_exponent_texture;

		/**
		 The amount this material dissolves into the background.

		 A factor of 1.0 is fully opaque.
		 A factor of 0.0 is fully dissolved (completely transparent).

		 Unlike a real transparent material, the dissolve does not depend upon
		 material thickness nor does it have any spectral character.
		 */
		float m_dissolve;

		/**
		 A pointer to the dissolve texture of this material.
		 */
		SharedPtr< Texture > m_dissolve_texture;

		/**
		 The index of refraction (optical density) of this material.
		 */
		float m_index_of_refraction;

		/**
		 A pointer to the decal texture of this material.
		 */
		SharedPtr< Texture > m_decal_texture;

		/**
		 A pointer to the displacement texture of this material.
		 */
		SharedPtr< Texture > m_displacement_texture;

		/**
		 A pointer to the normal texture of this material.
		 */
		SharedPtr< Texture > m_normal_texture;

		/**
		 The first material parameter of this material.
		 */
		float m_param1;

		/**
		 The second material parameter of this material.
		 */
		float m_param2;

		/**
		 The thirth material parameter of this material.
		 */
		float m_param3;

		/**
		 The fourth material parameter of this material.
		 */
		float m_param4;
	};
}