#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct Material {

	public:

		XMFLOAT3 m_ambient_reflectivity;
		XMFLOAT3 m_diffuse_color;
		XMFLOAT3 m_specular_color;
		XMFLOAT3 m_specular_exponent;

	

	};
}