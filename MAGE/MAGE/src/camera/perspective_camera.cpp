//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	PerspectiveCamera::PerspectiveCamera(float fov_y, float near_z, float far_z)
		: PerspectiveCamera(
			static_cast< float >(g_engine->GetRenderer()->GetWidth()),
			static_cast< float >(g_engine->GetRenderer()->GetHeight()),
			fov_y, near_z, far_z) {}

	PerspectiveCamera::PerspectiveCamera(float aspect_ratio,
		float fov_y, float near_z, float far_z)
		: Camera(near_z, far_z),
		m_aspect_ratio(aspect_ratio), m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(float width, float height,
		float fov_y, float near_z, float far_z)
		: Camera(near_z, far_z),
		m_aspect_ratio(AspectRatioFromWidthAndHeight(width, height)), m_fov_y(fov_y) {}

	PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera &camera) = default;

	PerspectiveCamera::PerspectiveCamera(PerspectiveCamera &&camera) = default;

	PerspectiveCamera::~PerspectiveCamera() = default;

	PerspectiveCamera &PerspectiveCamera::operator=(const PerspectiveCamera &camera) = default;

	PerspectiveCamera &PerspectiveCamera::operator=(PerspectiveCamera &&camera) = default;

	UniquePtr< Camera > PerspectiveCamera::CloneImplementation() const {
		return std::make_unique< PerspectiveCamera >(*this);
	}
}