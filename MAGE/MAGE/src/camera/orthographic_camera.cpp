//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "camera\orthographic_camera.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	SharedPtr< Camera > CreateOrthographicCamera(const string &name, 
		float width, float height, float near_z, float far_z) {
		return SharedPtr< Camera >(new OrthographicCamera(name, width, height, near_z, far_z));
	}
}