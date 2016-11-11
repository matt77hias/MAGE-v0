//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Renderer::Renderer(HWND hwindow) : 
		m_loaded(false), m_hwindow(hwindow), 
		m_render_target_view(NULL), m_swap_chain2(NULL), m_device_context2(NULL), m_device2(NULL) {

		const HRESULT result_device = InitDevice();
		if (FAILED(result_device)) {
			return;
		}

		m_loaded = true;
	}

	Renderer::~Renderer() {

		// Reset any device context to the default settings. 
		if (m_device_context2) {
			m_device_context2->ClearState();
		}

		// Release D3D11 components.
		SAFE_RELEASE(m_depth_stencil);
		SAFE_RELEASE(m_depth_stencil_view);
		SAFE_RELEASE(m_render_target_view);
		SAFE_RELEASE(m_swap_chain2);
		SAFE_RELEASE(m_device_context2);
		SAFE_RELEASE(m_device2);
	}

	HRESULT Renderer::InitDevice() {

		return S_OK;
	}
}