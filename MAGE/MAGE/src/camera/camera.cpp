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

	constexpr Camera::Camera(F32 near_z, F32 far_z)
		: m_near_z(near_z), m_far_z(far_z),
		m_lens_radius(0.0f), m_focal_length(far_z), 
		m_max_coc_radius(10.0f) {}

	constexpr Camera::Camera(const Camera &camera) = default;

	constexpr Camera::Camera(Camera &&camera) = default;

	Camera::~Camera() = default;

	constexpr Camera &Camera::operator=(const Camera &camera) = default;

	constexpr Camera &Camera::operator=(Camera &&camera) = default;
}