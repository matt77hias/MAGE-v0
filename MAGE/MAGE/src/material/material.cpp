#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"
#include "texture\texture_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Material::Material(const string &name)
		: m_name(name), m_light_interaction(true), m_transparent(), m_transmission_filter(RGBSpectrum(1.0f)),
		m_diffuse_reflectivity(RGBSpectrum(1.0f)),  m_diffuse_reflectivity_texture(CreateWhiteTexture()),
		m_specular_reflectivity(RGBSpectrum(1.0f)), m_specular_reflectivity_texture(CreateBlackTexture()),
		m_dissolve(1.0f), m_normal_texture(), m_displacement_texture(), m_decal_texture(), 
		m_material_parameters{ 1.0f, 1.0f, 1.0f } {

		UpdateTransparency();
	}
}