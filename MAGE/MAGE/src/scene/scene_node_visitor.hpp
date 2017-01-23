#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SceneNodeVisitor {

	public:

		virtual ~SceneNodeVisitor() {}

		virtual void VisitCameraNode(CameraNode &camera_node) const = 0;
		virtual void VisitCameraNode(const CameraNode &camera_node) const = 0;

	protected:

		SceneNodeVisitor() {}
	};
}