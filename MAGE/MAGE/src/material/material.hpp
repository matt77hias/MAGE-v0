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
			m_specular_exponent(0.0f), m_specular_exponent_texture(),
			m_dissolve(1.0f), m_dissolve_texture(),
			m_index_of_refraction(1.0f), m_decal_texture(),
			m_displacement_texture(), m_bump_texture() {}
		
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
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The name of this material.
		 */
		string m_name;

		/**
		 A pointer to the transmission filter of this material.
		 
		 Any light passing through the material is filtered by the transmission 
		 filter, which only allows the specific colors to pass through.
		 */
		RGBSpectrum m_transmission_filter;

		/**
		 A pointer to the ambient reflectivity of this material.
		 */
		RGBSpectrum m_ambient_reflectivity;

		/**
		 A pointer to the ambient reflectivity texture of this material.
		 */
		SharedPtr< Texture > m_ambient_reflectivity_texture;

		/**
		 A pointer to the diffuse reflectivity of this material.
		 */
		RGBSpectrum m_diffuse_reflectivity;

		/**
		 A pointer to the diffuse reflectivity texture of this material.
		 */
		SharedPtr< Texture > m_diffuse_reflectivity_texture;

		/**
		 A pointer to the specular reflectivity of this material.
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
		 A pointer to the bump texture of this material.
		 */
		SharedPtr< Texture > m_bump_texture;
	};
}