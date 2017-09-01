#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	UniquePtr< const StaticMesh > CreateLineCube();

	UniquePtr< const StaticMesh > CreateScreenQuad();
}