#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SceneNodeVisitor {

	public:

		virtual ~SceneNodeVisitor() {}

		virtual void VisitCameraNode(CameraNode &camera_node) {
			UNUSED(camera_node);
		}
		virtual void VisitCameraNode(const CameraNode &camera_node) {
			UNUSED(camera_node);
		}

	protected:

		SceneNodeVisitor() {}
	};
}