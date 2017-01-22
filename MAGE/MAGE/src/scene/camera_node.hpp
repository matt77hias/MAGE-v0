#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class CameraNode : private SceneNode {

	public:

		CameraNode(Camera *camera) 
			: SceneNode(), m_camera(camera) {}
		virtual ~CameraNode() {
			SAFE_DELETE(m_camera);
		}

		Camera *GetCamera() const {
			return m_camera;
		}

		virtual Transform &GetTransform() {
			return m_camera->GetTransform();
		}
		virtual const Transform &GetTransform() const {
			return m_camera->GetTransform();
		}

	protected:

		Camera *m_camera;
	};
}
