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

#define MAGE_DEFAULT_NEAR_Z          0.01f
#define MAGE_DEFAULT_FAR_Z          100.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Camera::Camera() noexcept
		: Component(), 
		m_near_z(MAGE_DEFAULT_NEAR_Z),
		m_far_z(MAGE_DEFAULT_FAR_Z),
		m_lens(),
		m_viewport(),
		m_settings() {}

	Camera::Camera(const Camera &camera) noexcept = default;

	Camera::Camera(Camera &&camera) noexcept = default;

	Camera::~Camera() = default;

	Camera &Camera::operator=(const Camera &camera) noexcept = default;

	Camera &Camera::operator=(Camera &&camera) noexcept = default;

	const Viewport Camera::GetSSViewport() const noexcept {
		const AADescriptor desc
			= DisplayConfiguration::Get()->GetAADescriptor();
		return Viewport(m_viewport, desc);
	}
}