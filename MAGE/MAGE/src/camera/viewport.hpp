#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct Viewport final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		Viewport();
		explicit Viewport(const D3D11_VIEWPORT &viewport)
			: m_viewport(viewport) {}
		explicit Viewport(D3D11_VIEWPORT &&viewport)
			: m_viewport(std::move(viewport)) {}
		Viewport(const Viewport &viewport) = default;
		Viewport(Viewport &&viewport) = default;
		~Viewport() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Viewport &operator=(const Viewport &viewport) = default;
		Viewport &operator=(Viewport &&viewport) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindViewport() const noexcept {
			GetRenderingDeviceContext()->RSSetViewports(1, &m_viewport);
		}

		/**
		 Returns the viewport of this viewport.

		 @return		A reference to the viewport of this viewport.
		 */
		const D3D11_VIEWPORT &GetViewport() const noexcept {
			return m_viewport;
		}

		/**
		 Sets the viewport of this viewport to the maximum viewport.
		 */
		void SetMaximumViewport() noexcept;

		/**
		Sets the viewport of this viewport to the given viewport.

		@param[in]		viewport
						A reference to the viewport.
		*/
		void SetViewport(const D3D11_VIEWPORT &viewport) noexcept {
			m_viewport = viewport;
		}

		/**
		 Sets the viewport of this viewport to the given viewport.

		 @param[in]		viewport
						A reference to the viewport.
		 */
		void SetViewport(D3D11_VIEWPORT &&viewport) noexcept {
			m_viewport = std::move(viewport);
		}

		void SetTopLeft(uint32_t x, uint32_t y) noexcept {
			m_viewport.TopLeftX = static_cast< FLOAT >(x);
			m_viewport.TopLeftY = static_cast< FLOAT >(y);
		}

		void SetTopLeft(float x, float y) noexcept {
			m_viewport.TopLeftX = static_cast< FLOAT >(x);
			m_viewport.TopLeftY = static_cast< FLOAT >(y);
		}

		void SetWidth(uint32_t width) noexcept {
			m_viewport.Width = static_cast< FLOAT >(width);
		}

		void SetWidth(float width) noexcept {
			m_viewport.Width = static_cast< FLOAT >(width);
		}

		void SetHeight(uint32_t height) noexcept {
			m_viewport.Height = static_cast< FLOAT >(height);
		}

		void SetHeight(float height) noexcept {
			m_viewport.Height = static_cast< FLOAT >(height);
		}

		void SetWidthAndHeight(uint32_t width, uint32_t height) noexcept {
			m_viewport.Width  = static_cast< FLOAT >(width);
			m_viewport.Height = static_cast< FLOAT >(height);
		}

		void SetWidthAndHeight(float width, float height) noexcept {
			m_viewport.Width  = static_cast< FLOAT >(width);
			m_viewport.Height = static_cast< FLOAT >(height);
		}

		void SetDepth(float min_depth, float max_depth) noexcept {
			m_viewport.MinDepth = static_cast< FLOAT >(min_depth);
			m_viewport.MaxDepth = static_cast< FLOAT >(max_depth);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 The viewport of this viewport.
		 */
		D3D11_VIEWPORT m_viewport;
	};
}