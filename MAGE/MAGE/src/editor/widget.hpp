#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {
	
	// Forward declarations.
	class Scene;
	class Node;
}

namespace mage::editor {

	void SetSelected(ProxyPtr< Node > node = nullptr) noexcept;

	void DrawGraph(Scene &scene);

	void DrawInspector();
}