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
		F32 width, F32 height, F32 near_z, F32 far_z) noexcept
		: Camera(near_z, far_z),
		m_width(width), m_height(height) {}

	OrthographicCamera::OrthographicCamera(
		const OrthographicCamera &camera) noexcept = default;

	OrthographicCamera::OrthographicCamera(
		OrthographicCamera &&camera) noexcept = default;

	OrthographicCamera::~OrthographicCamera() = default;

	OrthographicCamera &OrthographicCamera::operator=(
		const OrthographicCamera &camera) noexcept = default;

	OrthographicCamera &OrthographicCamera::operator=(
		OrthographicCamera &&camera) noexcept = default;

	UniquePtr< Camera > OrthographicCamera::CloneImplementation() const {
		return MakeUnique< OrthographicCamera >(*this);
	}
}