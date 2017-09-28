//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Camera::Camera(F32 near_z, F32 far_z)
		: m_near_z(near_z), m_far_z(far_z) {}

	Camera::Camera(const Camera &camera) = default;

	Camera::Camera(Camera &&camera) = default;

	Camera::~Camera() = default;

	Camera &Camera::operator=(const Camera &camera) = default;

	Camera &Camera::operator=(Camera &&camera) = default;
}