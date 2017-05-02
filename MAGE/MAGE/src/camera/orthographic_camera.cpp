//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\orthographic_camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	OrthographicCamera::OrthographicCamera(
		float width, float height, float near_z, float far_z)
		: Camera(near_z, far_z),
		m_width(width), m_height(height) {}

	OrthographicCamera::OrthographicCamera(const OrthographicCamera &camera) = default;

	OrthographicCamera::OrthographicCamera(OrthographicCamera &&camera) = default;

	OrthographicCamera::~OrthographicCamera() = default;

	OrthographicCamera &OrthographicCamera::operator=(const OrthographicCamera &camera) = default;

	OrthographicCamera &OrthographicCamera::operator=(OrthographicCamera &&camera) = default;

	SharedPtr< Camera > OrthographicCamera::CloneImplementation() const {
		return SharedPtr< OrthographicCamera >(new OrthographicCamera(*this));
	}

	SharedPtr< OrthographicCamera > CreateOrthographicCamera(
		float width, float height, float near_z, float far_z) {
		return SharedPtr< OrthographicCamera >(
			new OrthographicCamera(width, height, near_z, far_z));
	}
}