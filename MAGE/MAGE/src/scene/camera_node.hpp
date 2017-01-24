#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of camera nodes.
	 */
	class CameraNode : public SceneNode {

	public:

		/**
		 Constructs a camera node with given camera and transform.

		 @pre			@a camera may not point to @c nullptr.
		 @param[in]		camera
						A pointer to the camera.
		 @param[in]		transform
						A reference to the transform.
		 */
		CameraNode(Camera *camera, const Transform &transform = Transform())
			: SceneNode(transform), m_camera(camera) {}
		
		/**
		 Destructs this camera node.
		 */
		virtual ~CameraNode() {
			SAFE_DELETE(m_camera);
		}

		/**
		 Returns the camera of this camera node.

		 @return		A pointer to the camera of this camera node.
		 */
		Camera *GetCamera() const {
			return m_camera;
		}

		/**
		 Accepts the given visitor.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		virtual void Accept(SceneNodeVisitor &visitor) override {
			visitor.VisitCameraNode(*this);
			PassToChilds(visitor);
		}
		
		/**
		 Accepts the given visitor.

		 @param[in]		visitor
						A reference to the visitor.
		 */
		virtual void Accept(SceneNodeVisitor &visitor) const override {
			visitor.VisitCameraNode(*this);
			PassToChilds(visitor);
		}

	protected:

		/**
		 A pointer to the camera of this camera node.
		 */
		Camera *m_camera;
	};
}
