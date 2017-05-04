//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "camera\perspective_camera.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PerspectiveCamera::PerspectiveCamera(float aspect_ratio,
		float fov_y, float near_z, float far_z)
		: Camera(near_z, far_z),
		m_aspect_ratio(aspect_ratio), m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(float width, float height,
		float fov_y, float near_z, float far_z)
		: Camera(near_z, far_z),
		m_aspect_ratio(width / height), m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera &camera) = default;

	PerspectiveCamera::PerspectiveCamera(PerspectiveCamera &&camera) = default;

	PerspectiveCamera::~PerspectiveCamera() = default;

	PerspectiveCamera &PerspectiveCamera::operator=(const PerspectiveCamera &camera) = default;

	PerspectiveCamera &PerspectiveCamera::operator=(PerspectiveCamera &&camera) = default;

	UniquePtr< Camera > PerspectiveCamera::CloneImplementation() const {
		return UniquePtr< PerspectiveCamera >(new PerspectiveCamera(*this));
	}

	SharedPtr< PerspectiveCamera > CreatePerspectiveCamera(float fov_y, float near_z, float far_z) {
		Assert(g_engine);
		const Renderer *render = g_engine->GetRenderer();
		Assert(render);
		const float width  = static_cast< float >(render->GetWidth());
		const float height = static_cast< float >(render->GetHeight());
		return SharedPtr< PerspectiveCamera >(new PerspectiveCamera(width, height, fov_y, near_z, far_z));
	}
}