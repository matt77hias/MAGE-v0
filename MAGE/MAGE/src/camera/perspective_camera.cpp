//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "rendering\display_configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_FOV_Y XM_PIDIV2

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PerspectiveCamera::PerspectiveCamera() noexcept
		: Camera(),
		m_aspect_ratio(AspectRatioFromWidthAndHeight(
			static_cast< F32 >(DisplayConfiguration::Get()->GetDisplayWidth()),
			static_cast< F32 >(DisplayConfiguration::Get()->GetDisplayHeight()))),
		m_fov_y(MAGE_DEFAULT_FOV_Y) {}

	PerspectiveCamera::PerspectiveCamera(
		const PerspectiveCamera &camera) = default;

	PerspectiveCamera::PerspectiveCamera(
		PerspectiveCamera &&camera) noexcept = default;

	PerspectiveCamera::~PerspectiveCamera() = default;

	PerspectiveCamera &PerspectiveCamera
		::operator=(const PerspectiveCamera &camera) = default;

	PerspectiveCamera &PerspectiveCamera
		::operator=(PerspectiveCamera &&camera) noexcept = default;
}