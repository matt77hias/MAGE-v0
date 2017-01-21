#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Camera {

	public:

		Camera(const XMMATRIX &view_to_projection, const Transform &transform = Transform()) 
			: m_view_to_projection(view_to_projection), m_transform(transform) {}
		virtual ~Camera() = 0;

		Transform &GetTransform() {
			return m_transform;
		}
		
		XMMATRIX GetViewToProjectionMatrix() const {
			return m_view_to_projection;
		}
			
	protected:

		Transform m_transform;

		XMMATRIX m_view_to_projection;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera/orthographic_camera.hpp"
#include "camera/perspective_camera.hpp"

#pragma endregion