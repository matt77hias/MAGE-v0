//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\perspective_camera.hpp"
#include "rendering\renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PerspectiveCamera::PerspectiveCamera(
		f32 fov_y)
		: PerspectiveCamera(fov_y,
			MAGE_DEFAULT_CAMERA_NEAR_Z,
			MAGE_DEFAULT_CAMERA_FAR_Z) {}

	PerspectiveCamera::PerspectiveCamera(
		f32 fov_y, f32 near_z, f32 far_z)
		: PerspectiveCamera(
			static_cast< f32 >(Renderer::Get()->GetWidth()),
			static_cast< f32 >(Renderer::Get()->GetHeight()),
			fov_y, near_z, far_z) {}

	PerspectiveCamera::PerspectiveCamera(f32 aspect_ratio,
		f32 fov_y, f32 near_z, f32 far_z)
		: Camera(near_z, far_z),
		m_aspect_ratio(aspect_ratio), 
		m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(f32 width, f32 height,
		f32 fov_y, f32 near_z, f32 far_z)
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