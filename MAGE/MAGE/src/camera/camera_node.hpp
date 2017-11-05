#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"
#include "camera\camera.hpp"
#include "camera\camera_settings.hpp"
#include "camera\viewport.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// CameraNode
	//-------------------------------------------------------------------------

	/**
	 A class of camera nodes.
	 */
	class CameraNode : public SceneNode {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this camera node.
		 */
		virtual ~CameraNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given camera node to this camera node.

		 @param[in]		camera_node
						A reference to the camera node to copy.
		 @return		A reference to the copy of the given camera node (i.e. 
						this camera node).
		 */
		CameraNode &operator=(const CameraNode &camera_node) = delete;
		
		/**
		 Moves the given camera node to this camera node.

		 @param[in]		camera_node
						A reference to the camera node to move.
		 @return		A reference to the moved camera node (i.e. this camera 
						node).
		 */
		CameraNode &operator=(CameraNode &&camera_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this camera node.

		 @return		A pointer to the clone of this camera node.
		 */
		UniquePtr< CameraNode > Clone() const {
			return static_pointer_cast< CameraNode >(CloneImplementation());
		}
		
		/**
		 Returns the camera of this camera node.

		 @return		A pointer to the camera of this camera node.	
		 */
		Camera *GetCamera() noexcept {
			return m_camera.get();
		}
		
		/**
		 Returns the camera of this camera node.

		 @return		A pointer to the camera of this camera node.
		 */
		const Camera *GetCamera() const noexcept {
			return m_camera.get();
		}

		/**
		 Returns the camera settings of this camera node.

		 @return		A pointer to the camera settings of this camera node.	
		 */
		CameraSettings *GetSettings() noexcept {
			return m_settings.get();
		}
		
		/**
		 Returns the camera settings of this camera node.

		 @return		A pointer to the camera settings of this camera node.
		 */
		const CameraSettings *GetSettings() const noexcept {
			return m_settings.get();
		}

		/**
		 Returns the viewport of this camera node.

		 @return		A reference to the viewport of this camera node.
		 */
		Viewport &GetViewport() noexcept {
			return m_viewport;
		}

		/**
		 Returns the viewport of this camera node.

		 @return		A reference to the viewport of this camera node.
		 */
		const Viewport &GetViewport() const noexcept {
			return m_viewport;
		}

		/**
		 Returns the super-sampled viewport of this camera node.

		 @pre			The rendering manager associated with the current
						engine must be loaded.
		 @return		The super-sampled viewport of this camera node.
		 */
		const Viewport GetSSViewport() const noexcept;

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera node.

		 @pre			@a camera refers to a non @c nullptr.
		 @param[in]		name
						A reference to the name.
		 @param[in]		camera
						A reference to the camera to move.
		 */
		explicit CameraNode(const string &name, UniquePtr< Camera > &&camera);
		
		/**
		 Constructs a camera node from the given camera node.

		 @param[in]		camera_node
						A reference to the camera node to copy.
		 */
		CameraNode(const CameraNode &camera_node);
		
		/**
		 Constructs a camera node by moving the given camera node.

		 @param[in]		camera_node
						A reference to the camera node to move.
		 */
		CameraNode(CameraNode &&camera_node);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this camera node.

		 @return		A pointer to the clone of this camera node.
		 */
		virtual UniquePtr< Node > CloneImplementation() const override = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the camera of this camera node.
		 */
		UniquePtr< Camera > m_camera;

		/**
		 A pointer to the camera settings of this camera node.
		 */
		UniquePtr< CameraSettings > m_settings;

		/**
		 The viewport of this camera node.
		 */
		Viewport m_viewport;
	};

	//-------------------------------------------------------------------------
	// DerivedCameraNode
	//-------------------------------------------------------------------------

	/**
	 A class of derived camera nodes.

	 @tparam		CameraT
					The camera type.
	 */
	template< typename CameraT >
	class DerivedCameraNode final : public CameraNode {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a derived camera node.

		 @tparam		ConstructorArgsT
						The constructor argument types of the camera.
		 @param[in]		name
						A reference to the name.
		 @param[in]		args
						A reference to the constructor arguments for the 
						camera.
		 */
		template< typename... ConstructorArgsT >
		explicit DerivedCameraNode(
			const string &name, ConstructorArgsT&&... args);
		
		/**
		 Constructs a derived camera node.

		 @pre			@a camera refers to a non @c nullptr.
		 @param[in]		name
						A reference to the name.
		 @param[in]		camera
						A reference to the camera to move.
		 */
		explicit DerivedCameraNode(
			const string &name, UniquePtr< CameraT > &&camera);
		
		/**
		 Constructs a derived camera node from the given derived camera node.

		 @param[in]		camera_node
						A reference to the derived camera node to copy.
		 */
		DerivedCameraNode(const DerivedCameraNode &camera_node);
		
		/**
		 Constructs a derived camera node by moving the given derived camera 
		 node.

		 @param[in]		camera_node
						A reference to the derived camera node to move.
		 */
		DerivedCameraNode(DerivedCameraNode &&camera_node);
		
		/**
		 Destructs this derived camera node.
		 */
		virtual ~DerivedCameraNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given derived camera node to this derived camera node.

		 @param[in]		camera_node
						A reference to the derived camera node to copy.
		 @return		A reference to the copy of the given derived camera 
						node (i.e. this derived camera node).
		 */
		DerivedCameraNode &operator=(
			const DerivedCameraNode &camera_node) = delete;
		
		/**
		 Moves the given derived camera node to this derived camera node.

		 @param[in]		camera_node
						A reference to the derived camera node to move.
		 @return		A reference to the moved derived camera node (i.e. this 
						derived camera node).
		 */
		DerivedCameraNode &operator=(
			DerivedCameraNode &&camera_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this derived camera node.

		 @return		A pointer to the clone of this derived camera node.
		 */
		UniquePtr< DerivedCameraNode > Clone() const {
			return static_pointer_cast< DerivedCameraNode >(CloneImplementation());
		}

		/**
		 Returns the camera of this derived camera node.

		 @return		A pointer to the camera of this derived camera node.
		 */
		CameraT *GetCamera() noexcept {
			return static_cast< CameraT * >(CameraNode::GetCamera());
		}

		/**
		 Returns the camera of this derived camera node.

		 @return		A pointer to the camera of this derived camera node.
		 */
		const CameraT *GetCamera() const noexcept {
			return static_cast< const CameraT * >(CameraNode::GetCamera());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this derived camera node.

		 @return		A pointer to the clone of this derived camera node.
		 */
		virtual UniquePtr< Node > CloneImplementation() const override;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.tpp"

#pragma endregion