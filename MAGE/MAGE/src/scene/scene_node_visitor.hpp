#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "support.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declarations
	class CameraNode;

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
		 Check whether the visit of this visitor should be terminated.

		 @return		@c true if the visit of this visitor should be terminated.
						@c false otherwise.
		 */
		bool IsVisitTerminated() const {
			return m_terminated;
		}

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
		SceneNodeVisitor() : m_terminated(false) {}

		/**
		 Terminates the visit of this visitor. 
		 */
		void TerminateVisit() {
			m_terminated = true;
		}

	private:

		/**
		 Flag indicating whether the visit of this visitor should be terminated.
		 This allows for early termination (i.e. search operation).
		 */
		bool m_terminated;
	};
}