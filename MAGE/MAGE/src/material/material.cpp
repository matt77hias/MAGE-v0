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
		: m_name(name), m_light_interaction(true),
		m_transparent(), m_transmission_filter(),
		m_diffuse_reflectivity(), m_diffuse_reflectivity_texture(CreateWhiteTexture()),
		m_specular_reflectivity(), m_specular_reflectivity_texture(CreateBlackTexture()),
		m_specular_exponent(1.0f), m_specular_exponent_texture(),
		m_dissolve(1.0f), m_index_of_refraction(1.0f),
		m_decal_texture(), m_displacement_texture(), m_normal_texture(),
		m_extra_parameters{} {
		UpdateTransparency();
	}
}