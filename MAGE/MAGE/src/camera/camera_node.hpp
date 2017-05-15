#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"

// Cameras
#include "camera\orthographic_camera.hpp"
#include "camera\perspective_camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class CameraNode : public SceneNode {

	public:

		virtual ~CameraNode();
		
		CameraNode &operator=(const CameraNode &camera_node) = delete;
		
		CameraNode &operator=(CameraNode &&camera_node) = delete;

		UniquePtr< CameraNode > Clone() const {
			return static_pointer_cast< CameraNode >(CloneImplementation());
		}
		
		Camera *GetCamera() noexcept {
			return m_camera.get();
		}
		
		const Camera *GetCamera() const noexcept {
			return m_camera.get();
		}

	protected:

		explicit CameraNode(const string &name, UniquePtr< Camera > &&camera);
		
		CameraNode(const CameraNode &camera_node);
		
		CameraNode(CameraNode &&camera_node);

	private:

		virtual UniquePtr< Node > CloneImplementation() const override = 0;

		UniquePtr< Camera > m_camera;
	};

	template< typename CameraT >
	class DerivedCameraNode final : public CameraNode {

	public:

		template< typename... ConstructorArgsT >
		explicit DerivedCameraNode(const string &name, ConstructorArgsT&&... args);
		
		explicit DerivedCameraNode(const string &name, UniquePtr< CameraT > &&camera);
		
		DerivedCameraNode(const DerivedCameraNode &camera_node);
		
		DerivedCameraNode(DerivedCameraNode &&camera_node);
		
		virtual ~DerivedCameraNode();
		
		DerivedCameraNode &operator=(const DerivedCameraNode &camera_node) = delete;
		
		DerivedCameraNode &operator=(DerivedCameraNode &&camera_node) = delete;

		UniquePtr< DerivedCameraNode > Clone() const {
			return static_pointer_cast< DerivedCameraNode >(CloneImplementation());
		}

		CameraT *GetCamera() noexcept {
			return static_cast< CameraT * >(CameraNode::GetCamera());
		}

		const CameraT *GetCamera() const noexcept {
			return static_cast< const CameraT * >(CameraNode::GetCamera());
		}

	private:

		virtual UniquePtr< Node > CloneImplementation() const override;
	};

	using OrthographicCameraNode = DerivedCameraNode< OrthographicCamera >;
	using PerspectiveCameraNode  = DerivedCameraNode< PerspectiveCamera >;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.tpp"

#pragma endregion