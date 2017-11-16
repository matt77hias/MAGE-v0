//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.hpp"
#include "rendering\display_configuration.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	CameraNode::CameraNode(string name, UniquePtr< Camera > &&camera)
		: Node(std::move(name)), 
		m_camera(std::move(camera)),
		m_settings(MakeUnique< CameraSettings >()), 
		m_viewport() {
		
		Assert(m_camera);
	}
	
	CameraNode::CameraNode(const CameraNode &camera_node) 
		: Node(camera_node), 
		m_camera(camera_node.m_camera->Clone()),
		m_settings(MakeUnique< CameraSettings >(*camera_node.m_settings)),
		m_viewport(camera_node.m_viewport) {}
	
	CameraNode::CameraNode(CameraNode &&camera_node) = default;
	
	CameraNode::~CameraNode() = default;

	const Viewport CameraNode::GetSSViewport() const noexcept {
		const AADescriptor desc 
			= DisplayConfiguration::Get()->GetAADescriptor();
		return Viewport(m_viewport, desc);
	}
}