//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\node.hpp"
#include "scene\camera\perspective_camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	PerspectiveCamera::PerspectiveCamera(ID3D11Device& device)
		: Camera(device),
		m_aspect_ratio(AspectRatioFromWidthAndHeight(1.0f, 1.0f)),
		m_fov_y(XM_PIDIV2) {}

	PerspectiveCamera::PerspectiveCamera(
		PerspectiveCamera&& camera) noexcept = default;

	PerspectiveCamera::~PerspectiveCamera() = default;

	PerspectiveCamera& PerspectiveCamera
		::operator=(PerspectiveCamera&& camera) noexcept = default;
}