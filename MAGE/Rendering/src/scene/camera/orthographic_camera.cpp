//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\camera\orthographic_camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	OrthographicCamera::OrthographicCamera(ID3D11Device& device)
		: Camera(device),
		m_width(1.0f), 
		m_height(1.0f) {}

	OrthographicCamera::OrthographicCamera(
		OrthographicCamera&& camera) noexcept = default;

	OrthographicCamera::~OrthographicCamera() = default;

	OrthographicCamera& OrthographicCamera
		::operator=(OrthographicCamera&& camera) noexcept = default;
}