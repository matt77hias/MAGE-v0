#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of scene node visitors.
	 */
	class SceneNodeVisitor {

	public:

		/**
		 Destructs this scene node visitor.
		 */
		virtual ~SceneNodeVisitor() {}

		/**
		 Visits the given camera node.

		 @param[in]		camera_node
						The camera node.
		 */
		virtual void VisitCameraNode(CameraNode &camera_node) {
			UNUSED(camera_node);
		}
		
		/**
		 Visits the given camera node.

		 @param[in]		camera_node
						The camera node.
		 */
		virtual void VisitCameraNode(const CameraNode &camera_node) {
			UNUSED(camera_node);
		}

	protected:

		/**
		 Constructs a scene node visitor.
		 */
		SceneNodeVisitor() {}
	};
}