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
		F32 width, F32 height, F32 near_z, F32 far_z)
		: Camera(near_z, far_z),
		m_width(width), m_height(height) {}

	OrthographicCamera::OrthographicCamera(
		const OrthographicCamera &camera) = default;

	OrthographicCamera::OrthographicCamera(
		OrthographicCamera &&camera) = default;

	OrthographicCamera::~OrthographicCamera() = default;

	OrthographicCamera &OrthographicCamera::operator=(
		const OrthographicCamera &camera) = default;

	OrthographicCamera &OrthographicCamera::operator=(
		OrthographicCamera &&camera) = default;

	UniquePtr< Camera > OrthographicCamera::CloneImplementation() const {
		return MakeUnique< OrthographicCamera >(*this);
	}
}