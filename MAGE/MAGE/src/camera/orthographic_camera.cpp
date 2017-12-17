//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_WIDTH  2.0f
#define MAGE_DEFAULT_HEIGHT 2.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	OrthographicCamera::OrthographicCamera() noexcept
		: Camera(),
		m_width(MAGE_DEFAULT_WIDTH), 
		m_height(MAGE_DEFAULT_HEIGHT) {}

	OrthographicCamera::OrthographicCamera(
		const OrthographicCamera &camera) noexcept = default;

	OrthographicCamera::OrthographicCamera(
		OrthographicCamera &&camera) noexcept = default;

	OrthographicCamera::~OrthographicCamera() = default;

	OrthographicCamera &OrthographicCamera
		::operator=(const OrthographicCamera &camera) noexcept = default;

	OrthographicCamera &OrthographicCamera
		::operator=(OrthographicCamera &&camera) noexcept = default;
}