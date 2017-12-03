#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	StaticMesh::StaticMesh(StaticMesh &&static_mesh) noexcept = default;

	StaticMesh::~StaticMesh() = default;
}