#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"
#include "memory\memory.hpp"
#include "string\string.hpp"
#include "material\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct Material {

	public:

		Material(float specular_exponent = 0.0f, float dissolve = 1.0f, float index_of_refraction = 1.0f, const string &name = "")
			: m_specular_exponent(specular_exponent), 
			m_dissolve(dissolve), 
			m_index_of_refraction(index_of_refraction),
			m_name(name) {}
		Material(const Material &material) = default;
		~Material() = default;

		Material &operator=(const Material &material) = default;

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
		 The ambient reflectivity map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_ambient_reflectivity_map;

		/**
		 The diffuse reflectivity of this material.
		 */
		RGBSpectrum m_diffuse_reflectivity;

		/**
		 The diffuse reflectivity map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_diffuse_reflectivity_map;

		/**
		 The specular reflectivity of this material.
		 */
		RGBSpectrum m_specular_reflectivity;

		/**
		 The specular reflectivity map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_specular_reflectivity_map;

		/**
		 The specular exponent (surface roughness) of this material.

		 A high exponent results in a tight, concentrated highlight.
		 Values normally range from 0 to 1000.
		 */
		float m_specular_exponent;

		/**
		 The specular exponent map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_specular_exponent_map;

		/**
		 The amount this material dissolves into the background.

		 A factor of 1.0 is fully opaque.
		 A factor of 0.0 is fully dissolved (completely transparent).

		 Unlike a real transparent material, the dissolve does not depend upon
		 material thickness nor does it have any spectral character.
		 */
		float m_dissolve;

		/**
		 The dissolve map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_dissolve_map;

		/**
		 The index of refraction (optical density) of this material.
		 */
		float m_index_of_refraction;

		/**
		 The decal map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_decal_map;

		/**
		 The displacement map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_displacement_map;

		/**
		 The bump map of this material.
		 */
		ComPtr< ID3D11ShaderResourceView > m_bump_map;
	};
}