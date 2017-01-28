#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"

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
		SceneNodeVisitor() 
			: m_terminated(false) {}

		/**
		 Constructs a scene node visitor from the given scene node visitor.

		 @param[in]		visitor
						A reference to the scene node visitor.
		 */
		SceneNodeVisitor(const SceneNodeVisitor &visitor) 
			: m_terminated(visitor.m_terminated) {}


		/**
		 Copies the given scene node visitor to this scene node visitor.

		 @param[in]		visitor
						A reference to the scene node visitor to copy from.
		 @return		A reference to the copy of the given scene node visitor
						(i.e. this scene node visitor).
		 */
		SceneNodeVisitor &operator=(const SceneNodeVisitor &visitor) = delete;

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