#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light_node.hpp"
#include "light\ambient_light.hpp"
#include "light\directional_light.hpp"
#include "light\omni_light.hpp"
#include "light\spot_light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	/**
	 A class of ambient light nodes.
	 */
	using AmbientLightNode = DerivedLightNode< AmbientLight >;

	/**
	 A class of directional light nodes.
	 */
	using DirectionalLightNode = DerivedLightNode< DirectionalLight >;

	/**
	 A class of omni light nodes.
	 */
	using OmniLightNode = DerivedLightNode< OmniLight >;

	/**
	 A class of spotlight nodes.
	 */
	using SpotLightNode = DerivedLightNode< SpotLight >;
}
