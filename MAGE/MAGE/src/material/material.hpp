#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"
#include "texture\texture.hpp"
#include "logging\error.hpp"

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
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The index of the material specular exponent 
		 in the material parameters.
		 */
		static const u8 s_material_Ns_index = 0;

		/**
		 The index of the material Ward alpha value
		 in the material parameters.
		 */
		static const u8 s_material_Ward_alpha_index = 0;

		/**
		 The index of the material roughness
		 in the material parameters.
		 */
		static const u8 s_material_roughness_index = 0;

		/**
		 The index of the material reflection coefficient
		 in the material parameters.
		 */
		static const u8 s_material_reflection_coefficient_index = 1;

		/**
		 The index of the material index of refraction
		 in the material parameters.
		 */
		static const u8 s_material_index_of_refraction_index = 2;

		/**
		 The number of material parameters.
		 */
		static const u8 s_nb_material_parameters = 3;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a material.

		 @pre			The resource manager associated with the 
						current engine must be loaded.		
		 @param[in]		name
						A reference to the name of the material.		
		 */
		explicit Material(const string &name = "material");
		
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

		/**
		 Returns the name of this material.

		 @return		A reference to the name of this material.
		 */
		const string &GetName() const noexcept {
			return m_name;
		}
		
		/**
		 Sets the name of this material to the given name.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(const string &name) {
			m_name = name;
		}
		
		/**
		 Sets the name of this material to the given name.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(string &&name) {
			m_name = std::move(name);
		}

		/**
		 Checks whether this material interacts with light and light sources.

		 @return		@c true if this material interacts with light
						and light sources. @c false otherwise.
		 */
		bool InteractsWithLight() const noexcept {
			return m_light_interaction;
		}

		/**
		 Enables this material to interact with light and light sources.
		 */
		void EnableLightInteraction() noexcept {
			SetLightInteraction(true);
		}

		/**
		 Dissables this material to interact with light and light sources.
		 */
		void DissableLightInteraction() noexcept {
			SetLightInteraction(false);
		}

		/**
		 Sets the light interaction of this material to the given value.

		 @param[in]		light_interaction
						@c true if this material needs to interact 
						with light and light sources. 
						@c false otherwise.
		 */
		void SetLightInteraction(bool light_interaction) noexcept {
			m_light_interaction = light_interaction;
		}

		/**
		 Checks whether this material is opaque 
		 (i.e. contains alpha channel equal to 1.0).

		 @return		@c true if and only if this material is opaque.
						@c false otherwise.
		 */
		bool IsOpaque() const noexcept {
			return !IsTransparant();
		}

		/**
		 Checks whether this material is transparent
		 (i.e. contains alpha channel not equal to 1.0).

		 @return		@c true if and only if this material is transparent.
						@c false otherwise.
		 */
		bool IsTransparant() const noexcept {
			return m_transparent;
		}

		/**
		 Returns the transmission filter of this material.

		 @return		A reference to the transmission filter of this material.
		 */
		RGBSpectrum &GetTransmissionFilter() noexcept {
			return m_transmission_filter;
		}
		
		/**
		 Returns the transmission filter of this material.

		 @return		A reference to the transmission filter of this material.
		 */
		const RGBSpectrum &GetTransmissionFilter() const noexcept {
			return m_transmission_filter;
		}
		
		/**
		 Sets the transmission filter of this material to the given transmission filter.

		 @param[in]		transmission_filter
						A reference to the transmission filter.
		 */
		void SetTransmissionFilter(const RGBSpectrum &transmission_filter) noexcept {
			m_transmission_filter = transmission_filter;
		}
		
		/**
		 Sets the transmission filter of this material to the given transmission filter.

		 @param[in]		transmission_filter
						A reference to the transmission filter.
		 */
		void SetTransmissionFilter(RGBSpectrum &&transmission_filter) noexcept {
			m_transmission_filter = std::move(transmission_filter);
		}

		/**
		 Returns the diffuse reflectivity of this material.

		 @return		A reference to the diffuse reflectivity of this material.
		 */
		RGBSpectrum &GetDiffuseReflectivity() noexcept {
			return m_diffuse_reflectivity;
		}
		
		/**
		 Returns the diffuse reflectivity of this material.

		 @return		A reference to the diffuse reflectivity of this material.
		 */
		const RGBSpectrum &GetDiffuseReflectivity() const noexcept {
			return m_diffuse_reflectivity;
		}
		
		/**
		 Sets the diffuse reflectivity of this material to the given diffuse reflectivity.

		 @param[in]		diffuse_reflectivity
						A reference to the diffuse reflectivity.
		 */
		void SetDiffuseReflectivity(const RGBSpectrum &diffuse_reflectivity) noexcept {
			m_diffuse_reflectivity = diffuse_reflectivity;
		}
		
		/**
		 Sets the diffuse reflectivity of this material to the given diffuse reflectivity.

		 @param[in]		diffuse_reflectivity
						A reference to the diffuse reflectivity.
		 */
		void SetDiffuseReflectivity(RGBSpectrum &&diffuse_reflectivity) noexcept {
			m_diffuse_reflectivity = std::move(diffuse_reflectivity);
		}
		
		/**
		 Returns the diffuse reflectivity texture of this material.

		 @return		A pointer to the diffuse reflectivity texture of this material.
		 */
		SharedPtr< const Texture > GetDiffuseReflectivityTexture() const noexcept {
			return m_diffuse_reflectivity_texture;
		}
		
		/**
		 Returns the shader resource view of the diffuse reflectivity texture of this material.

		 @return		@c nullptr, if this material has no diffuse reflectivity texture.
		 @return		A pointer to the shader resource view of the diffuse reflectivity texture of this material.
		 */
		ID3D11ShaderResourceView *GetDiffuseReflectivitySRV() const noexcept {
			return m_diffuse_reflectivity_texture ? m_diffuse_reflectivity_texture->Get() : nullptr;
		}
		
		/**
		 Sets the diffuse reflectivity texture of this material to the given diffuse reflectivity texture.

		 @param[in]		diffuse_reflectivity_texture
						A reference to the diffuse reflectivity texture.
		 */
		void SetDiffuseReflectivityTexture(
			const SharedPtr< const Texture > &diffuse_reflectivity_texture) {
			
			m_diffuse_reflectivity_texture = diffuse_reflectivity_texture;
			UpdateTransparency();
		}
		
		/**
		 Returns the specular reflectivity of this material.

		 @return		A reference to the specular reflectivity of this material.
		 */
		RGBSpectrum &GetSpecularReflectivity() noexcept {
			return m_specular_reflectivity;
		}
		
		/**
		 Returns the specular reflectivity of this material.

		 @return		A reference to the specular reflectivity of this material.
		 */
		const RGBSpectrum &GetSpecularReflectivity() const noexcept {
			return m_specular_reflectivity;
		}
		
		/**
		 Sets the specular reflectivity of this material to the given specular reflectivity.

		 @param[in]		specular_reflectivity
						A reference to the specular reflectivity.
		 */
		void SetSpecularReflectivity(const RGBSpectrum &specular_reflectivity) noexcept {
			m_specular_reflectivity = specular_reflectivity;
		}
		
		/**
		 Sets the specular reflectivity of this material to the given specular reflectivity.

		 @param[in]		specular_reflectivity
						A reference to the specular reflectivity.
		 */
		void SetSpecularReflectivity(RGBSpectrum &&specular_reflectivity) noexcept {
			m_specular_reflectivity = std::move(specular_reflectivity);
		}
		
		/**
		 Returns the specular reflectivity texture of this material.

		 @return		A pointer to the specular reflectivity texture of this material.
		 */
		SharedPtr< const Texture > GetSpecularReflectivityTexture() const noexcept {
			return m_specular_reflectivity_texture;
		}
		
		/**
		 Returns the shader resource view of the specular reflectivity texture of this material.

		 @return		@c nullptr, if this material has no specular reflectivity texture.
		 @return		A pointer to the shader resource view of the specular reflectivity texture of this material.
		 */
		ID3D11ShaderResourceView *GetSpecularReflectivitySRV() const noexcept {
			return m_specular_reflectivity_texture ? m_specular_reflectivity_texture->Get() : nullptr;
		}
		
		/**
		 Sets the specular reflectivity texture of this material to the given specular reflectivity texture.

		 @param[in]		specular_reflectivity_texture
						A reference to the specular reflectivity texture.
		 */
		void SetSpecularReflectivityTexture(
			const SharedPtr< const Texture > &specular_reflectivity_texture) {
			
			m_specular_reflectivity_texture = specular_reflectivity_texture;
		}
		
		/**
		 Returns the dissolve of this material.

		 @return		The dissolve of this material.
		 */
		float GetDissolve() const noexcept {
			return m_dissolve;
		}
		
		/**
		 Sets the dissolve of this material to the given dissolve.

		 @param[in]		dissolve
						A reference to the dissolve.
		 */
		void SetDissolve(float dissolve) noexcept {
			m_dissolve = dissolve;
			UpdateTransparency();
		}
		
		/**
		 Returns the normal texture of this material.

		 @return		A pointer to the normal texture of this material.
		 */
		SharedPtr< const Texture > GetNormalTexture() const noexcept {
			return m_normal_texture;
		}
		
		/**
		 Returns the shader resource view of the normal texture of this material.

		 @return		@c nullptr, if this material has no normal texture.
		 @return		A pointer to the shader resource view of the normal texture of this material.
		 */
		ID3D11ShaderResourceView *GetNormalSRV() const noexcept {
			return m_normal_texture ? m_normal_texture->Get() : nullptr;
		}
		
		/**
		 Sets the normal texture of this material to the given normal texture.

		 @param[in]		normal_texture
						A reference to the normal texture.
		 */
		void SetNormalTexture(
			const SharedPtr< const Texture > &normal_texture) {
			
			m_normal_texture = normal_texture;
		}

		/**
		 Returns the displacement texture of this material.

		 @return		A pointer to the displacement texture of this material.
		 */
		SharedPtr< const Texture > GetDisplacementTexture() const noexcept {
			return m_displacement_texture;
		}
		
		/**
		 Returns the shader resource view of the displacement texture of this material.

		 @return		@c nullptr, if this material has no displacement texture.
		 @return		A pointer to the shader resource view of the displacement texture of this material.
		 */
		ID3D11ShaderResourceView *GetDisplacementSRV() const noexcept {
			return m_displacement_texture ? m_displacement_texture->Get() : nullptr;
		}
		
		/**
		 Sets the displacement texture of this material to the given displacement texture.

		 @param[in]		displacement_texture
						A reference to the displacement texture.
		 */
		void SetDisplacementTexture(
			const SharedPtr< const Texture > &displacement_texture) {
			
			m_displacement_texture = displacement_texture;
		}

		/**
		 Returns the decal texture of this material.

		 @return		A pointer to the decal texture of this material.
		 */
		SharedPtr< const Texture > GetDecalTexture() const noexcept {
			return m_decal_texture;
		}
		
		/**
		 Returns the decal resource view of the decal texture of this material.

		 @return		@c nullptr, if this material has no decal texture.
		 @return		A pointer to the shader resource view of the decal texture of this material.
		 */
		ID3D11ShaderResourceView *GetDecalSRV() const noexcept {
			return m_decal_texture ? m_decal_texture->Get() : nullptr;
		}
		
		/**
		 Sets the decal texture of this material to the given decal texture.

		 @param[in]		decal_texture
						A reference to the decal texture.
		 */
		void SetDecalTexture(
			const SharedPtr< const Texture > &decal_texture) {
			
			m_decal_texture = decal_texture;
		}
		
		/**
		 Returns the specular exponent of this material.

		 @return		The specular exponent of this material.
		*/
		float GetSpecularExponent() const noexcept {
			return GetMaterialParameter(s_material_Ns_index);
		}

		/**
		 Sets the specular exponent of this material to the given specular exponent.

		 @param[in]		specular_exponent
						A reference to the specular exponent.
		*/
		void SetSpecularExponent(float specular_exponent) noexcept {
			SetMaterialParameter(s_material_Ns_index, specular_exponent);
		}

		/**
		 Returns the index of refraction of this material.

		 @return		The index of refraction of this material.
		 */
		float GetIndexOfRefraction() const noexcept {
			return GetMaterialParameter(s_material_index_of_refraction_index);
		}

		/**
		 Sets the index of refraction of this material to the given index of refraction.

		 @param[in]		index_of_refraction
						A reference to the index of refraction.
		 */
		void SetIndexOfRefraction(float index_of_refraction) noexcept {
			SetMaterialParameter(s_material_index_of_refraction_index, index_of_refraction);
		}

		/**
		 Returns the material parameter of this material at the given index.

		 @pre			@a index @c < {@link mage::Material::s_nb_material_parameters}.
		 @param[in]		index
						The index.
		 @return		The material parameter of this material at the given index.
		 */
		float GetMaterialParameter(u8 index) const noexcept {
			Assert(index < s_nb_material_parameters);
			return m_material_parameters[index];
		}
		
		/**
		 Sets the material parameter of this material at the given index to the given value.

		 @pre			@a index @c < {@link mage::Material::s_nb_material_parameters}.
		 @param[in]		index
						The index.
		 @param[in]		value
						The value.
		 */
		void SetMaterialParameter(u8 index, float value) noexcept {
			Assert(index < s_nb_material_parameters);
			m_material_parameters[index] = value;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the transparency flag of this material.
		 */
		void UpdateTransparency() noexcept {
			m_transparent = (m_dissolve != 1.0f) || (m_diffuse_reflectivity_texture && m_diffuse_reflectivity_texture->HasAlpha());
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The name of this material.
		 */
		string m_name;

		/**
		 Flag indicating whether this material interacts
		 with light and light sources.
		 */
		bool m_light_interaction;

		/**
		 Flag indicating whether this material is transparent.
		 This flag is @c true if this material could contain 
		 transparent parts. @c false otherwise.
		 */
		bool m_transparent;

		/**
		 The transmission filter of this material.
		 
		 Any light passing through the material is filtered by 
		 the transmission filter, which only allows the specific 
		 colors to pass through.
		 */
		RGBSpectrum m_transmission_filter;

		/**
		 The diffuse reflectivity of this material.
		 */
		RGBSpectrum m_diffuse_reflectivity;

		/**
		 A pointer to the diffuse reflectivity texture of this material.
		 */
		SharedPtr< const Texture > m_diffuse_reflectivity_texture;

		/**
		 The specular reflectivity of this material.
		 */
		RGBSpectrum m_specular_reflectivity;

		/**
		 A pointer to the specular reflectivity texture of this material.
		 */
		SharedPtr< const Texture > m_specular_reflectivity_texture;

		/**
		 The amount this material dissolves into the background.

		 A factor of 1.0 is fully opaque.
		 A factor of 0.0 is fully dissolved (completely transparent).

		 Unlike a real transparent material, the dissolve does not depend upon
		 material thickness nor does it have any spectral character.
		 */
		float m_dissolve;

		/**
		 A pointer to the normal texture of this material.
		 */
		SharedPtr< const Texture > m_normal_texture;

		/**
		 A pointer to the displacement texture of this material.
		 */
		SharedPtr< const Texture > m_displacement_texture;

		/**
		 A pointer to the decal texture of this material.
		 */
		SharedPtr< const Texture > m_decal_texture;

		/**
		 The material parameters of this material.
		 */
		float m_material_parameters[s_nb_material_parameters];
	};
}