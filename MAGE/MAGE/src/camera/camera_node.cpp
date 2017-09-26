//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	CameraNode::CameraNode(const string &name, UniquePtr< Camera > &&camera)
		: SceneNode(name), m_camera(std::move(camera)), 
		m_settings(MakeUnique< CameraSettings >()), m_viewport() {
		
		Assert(m_camera);
	}
	
	CameraNode::CameraNode(const CameraNode &camera_node) 
		: SceneNode(camera_node), 
		m_camera(camera_node.m_camera->Clone()),
		m_settings(MakeUnique< CameraSettings >(*camera_node.m_settings)),
		m_viewport(camera_node.m_viewport) {}
	
	CameraNode::CameraNode(CameraNode &&camera_node) = default;
	
	CameraNode::~CameraNode() = default;
}