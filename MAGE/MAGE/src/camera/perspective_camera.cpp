//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\perspective_camera.hpp"
#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PerspectiveCamera::PerspectiveCamera(
		F32 fov_y) noexcept
		: PerspectiveCamera(fov_y,
			MAGE_DEFAULT_CAMERA_NEAR_Z,
			MAGE_DEFAULT_CAMERA_FAR_Z) {}

	PerspectiveCamera::PerspectiveCamera(
		F32 fov_y, F32 near_z, F32 far_z) noexcept
		: PerspectiveCamera(
			static_cast< F32 >(DisplayConfiguration::Get()->GetDisplayWidth()),
			static_cast< F32 >(DisplayConfiguration::Get()->GetDisplayHeight()),
			fov_y, near_z, far_z) {}

	PerspectiveCamera::PerspectiveCamera(F32 aspect_ratio,
		F32 fov_y, F32 near_z, F32 far_z) noexcept
		: Camera(near_z, far_z),
		m_aspect_ratio(aspect_ratio), 
		m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(F32 width, F32 height,
		F32 fov_y, F32 near_z, F32 far_z) noexcept
		: Camera(near_z, far_z),
		m_aspect_ratio(AspectRatioFromWidthAndHeight(width, height)), 
		m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(
		const PerspectiveCamera &camera) noexcept = default;

	PerspectiveCamera::PerspectiveCamera(
		PerspectiveCamera &&camera) noexcept = default;

	PerspectiveCamera::~PerspectiveCamera() = default;

	PerspectiveCamera &PerspectiveCamera::operator=(
		const PerspectiveCamera &camera) noexcept = default;

	PerspectiveCamera &PerspectiveCamera::operator=(
		PerspectiveCamera &&camera) noexcept = default;

	UniquePtr< Camera > PerspectiveCamera::CloneImplementation() const {
		return MakeUnique< PerspectiveCamera >(*this);
	}
}