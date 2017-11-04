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
		F32 fov_y)
		: PerspectiveCamera(fov_y,
			MAGE_DEFAULT_CAMERA_NEAR_Z,
			MAGE_DEFAULT_CAMERA_FAR_Z) {}

	PerspectiveCamera::PerspectiveCamera(
		F32 fov_y, F32 near_z, F32 far_z)
		: PerspectiveCamera(
			static_cast< F32 >(DisplayConfiguration::Get()->GetRenderingWidth()),
			static_cast< F32 >(DisplayConfiguration::Get()->GetRenderingHeight()),
			fov_y, near_z, far_z) {}

	PerspectiveCamera::PerspectiveCamera(F32 aspect_ratio,
		F32 fov_y, F32 near_z, F32 far_z)
		: Camera(near_z, far_z),
		m_aspect_ratio(aspect_ratio), 
		m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(F32 width, F32 height,
		F32 fov_y, F32 near_z, F32 far_z)
		: Camera(near_z, far_z),
		m_aspect_ratio(AspectRatioFromWidthAndHeight(width, height)), 
		m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(
		const PerspectiveCamera &camera) = default;

	PerspectiveCamera::PerspectiveCamera(
		PerspectiveCamera &&camera) = default;

	PerspectiveCamera::~PerspectiveCamera() = default;

	PerspectiveCamera &PerspectiveCamera::operator=(
		const PerspectiveCamera &camera) = default;

	PerspectiveCamera &PerspectiveCamera::operator=(
		PerspectiveCamera &&camera) = default;

	UniquePtr< Camera > PerspectiveCamera::CloneImplementation() const {
		return MakeUnique< PerspectiveCamera >(*this);
	}
}