//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "camera\perspective_camera.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SharedPtr< Camera > CreatePerspectiveCamera(const string &name, float fov_y, float near_z, float far_z) {
		Assert(g_engine);
		const Renderer *render = g_engine->GetRenderer();
		Assert(render);
		const float width  = static_cast< float >(render->GetWidth());
		const float height = static_cast< float >(render->GetHeight());
		return SharedPtr< Camera >(new PerspectiveCamera(name, width, height, fov_y, near_z, far_z));
	}
}