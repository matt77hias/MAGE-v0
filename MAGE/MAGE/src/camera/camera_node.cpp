//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.hpp"
#include "rendering\renderer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	CameraNode::CameraNode(const string &name, UniquePtr< Camera > &&camera)
		: SceneNode(name), 
		m_camera(std::move(camera)),
		m_viewport(Renderer::Get()->GetMaxViewport()) {}
	
	CameraNode::CameraNode(const CameraNode &camera_node) 
		: SceneNode(camera_node), 
		m_camera(camera_node.GetCamera()->Clone()),
		m_viewport(camera_node.m_viewport) {}
	
	CameraNode::CameraNode(CameraNode &&camera_node) = default;
	
	CameraNode::~CameraNode() = default;
}