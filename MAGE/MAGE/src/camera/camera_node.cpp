//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	CameraNode::CameraNode(const string &name, UniquePtr< Camera > &&camera)
		: Node(), m_name(name), m_camera(std::move(camera)) {}
	
	CameraNode::CameraNode(const CameraNode &camera_node) 
		: Node(camera_node), m_name(camera_node.m_name),
		m_camera(camera_node.GetCamera()->Clone()) {}
	
	CameraNode::CameraNode(CameraNode &&camera_node) = default;
	
	CameraNode::~CameraNode() = default;
}