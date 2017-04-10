//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"
#include "camera\orthographic_camera.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SharedPtr< Camera > CreateOrthographicCamera(const string &name, float near_z, float far_z) {
		Assert(g_engine);
		Assert(g_engine->GetRenderer());
		const float width  = static_cast< float >(g_engine->GetRenderer()->GetWidth());
		const float height = static_cast< float >(g_engine->GetRenderer()->GetHeight());
		return SharedPtr< Camera >(new OrthographicCamera(name, width, height, near_z, far_z));
	}
}