#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\transform_node.hpp"

// Cameras
#include "camera\orthographic_camera.hpp"
#include "camera\perspective_camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class CameraNode : public Node {

	public:

		virtual ~CameraNode();
		
		CameraNode &operator=(const CameraNode &camera_node) = delete;
		
		CameraNode &operator=(CameraNode &&camera_node) = delete;

		UniquePtr< CameraNode > Clone() const {
			return static_pointer_cast< CameraNode >(CloneImplementation());
		}
		
		const string &GetName() const {
			return m_name;
		}
		
		void SetName(const string &name) {
			m_name = name;
		}
		
		Camera *GetCamera() {
			return m_camera.get();
		}
		
		const Camera *GetCamera() const {
			return m_camera.get();
		}

	protected:

		explicit CameraNode(const string &name, UniquePtr< Camera > &&camera);
		
		CameraNode(const CameraNode &camera_node);
		
		CameraNode(CameraNode &&camera_node);

	private:

		virtual UniquePtr< Node > CloneImplementation() const override = 0;

		string m_name;
		
		UniquePtr< Camera > m_camera;
	};

	template< typename CameraT >
	class DerivedCameraNode final : public CameraNode {

	public:

		explicit DerivedCameraNode(const string &name);
		
		explicit DerivedCameraNode(const string &name, UniquePtr< CameraT > &&camera);
		
		DerivedCameraNode(const DerivedCameraNode &camera_node);
		
		DerivedCameraNode(DerivedCameraNode &&camera_node);
		
		virtual ~DerivedCameraNode();
		
		DerivedCameraNode &operator=(const DerivedCameraNode &camera_node) = delete;
		
		DerivedCameraNode &operator=(DerivedCameraNode &&camera_node) = delete;

		UniquePtr< DerivedCameraNode > Clone() const {
			return static_pointer_cast< DerivedCameraNode >(CloneImplementation());
		}

		CameraT *GetCamera() {
			return static_cast< CameraT * >(CameraNode::GetCamera());
		}

		const CameraT *GetCamera() const {
			return static_cast< const CameraT * >(CameraNode::GetCamera());
		}

	private:

		virtual UniquePtr< Node > CloneImplementation() const override;
	};

	typedef DerivedCameraNode< OrthographicCamera > OrthographicCameraNode;
	typedef DerivedCameraNode< PerspectiveCamera > PerspectiveCameraNode;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.tpp"

#pragma endregion