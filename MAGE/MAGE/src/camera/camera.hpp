#pragma once

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_CAMERA_FOV_Y XM_PIDIV2
#define MAGE_DEFAULT_CAMERA_NEAR_Z 0.01f
#define MAGE_DEFAULT_CAMERA_FAR_Z 100.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Camera {

	public:

		CameraTransform &GetTransform() {
			return m_transform;
		}
		const CameraTransform &GetTransform() const {
			return m_transform;
		}
		
		float GetWidth() const {
			return m_width;
		}
		void SetWidth(float width) {
			m_width = width;
			UpdateViewToProjectionMatrix();
		}
		float GetHeight() const {
			return m_height;
		}
		void SetHeight(float height) {
			m_height = height;
			UpdateViewToProjectionMatrix();
		}
		void SetWidthAndHeight(float width, float height) {
			m_width = width;
			m_height = height;
			UpdateViewToProjectionMatrix();
		}

		float GetNearZ() const {
			return m_near_z;
		}
		void SetNearZ(float near_z) {
			m_near_z = near_z;
			UpdateViewToProjectionMatrix();
		}
		float GetFarZ() const {
			return m_far_z;
		}
		void SetFarZ(float far_z) {
			m_far_z = far_z;
			UpdateViewToProjectionMatrix();
		}
		void SetNearAndFarZ(float near_z, float far_z) {
			m_near_z = near_z;
			m_far_z = far_z;
			UpdateViewToProjectionMatrix();
		}

		XMMATRIX GetViewToProjectionMatrix() const {
			return m_view_to_projection;
		}
			
	protected:

		Camera(const XMMATRIX &view_to_projection, 
			float width, float height, float near_z = MAGE_DEFAULT_CAMERA_NEAR_Z, float far_z = MAGE_DEFAULT_CAMERA_FAR_Z,
			const CameraTransform &transform = CameraTransform())
			: m_view_to_projection(view_to_projection), 
			m_width(width), m_height(height), m_near_z(near_z), m_far_z(far_z),
			m_transform(transform) {}
		virtual ~Camera() {}

		virtual void UpdateViewToProjectionMatrix() = 0;

		CameraTransform m_transform;

		float m_width;
		float m_height;
		float m_near_z;
		float m_far_z;

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