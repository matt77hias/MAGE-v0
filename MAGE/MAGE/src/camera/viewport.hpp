#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct Viewport final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		static const D3D11_VIEWPORT GetMaxViewport() noexcept;

		static F32 NormalizeWidth(F32 x) noexcept;

		static F32 NormalizeHeight(F32 x) noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		Viewport()
			: Viewport(GetMaxViewport()) {}
		
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

		void BindViewport(ID3D11DeviceContext2 *device_context) const noexcept {
			Pipeline::RS::BindViewport(device_context, &m_viewport);
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
		void SetMaximumViewport() noexcept {
			SetViewport(GetMaxViewport());
		}

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

		void SetTopLeft(U32 x, U32 y) noexcept {
			m_viewport.TopLeftX = static_cast< F32 >(x);
			m_viewport.TopLeftY = static_cast< F32 >(y);
		}

		void SetTopLeft(F32 x, F32 y) noexcept {
			m_viewport.TopLeftX = x;
			m_viewport.TopLeftY = y;
		}

		void SetNormalizedTopLeft(F32 x, F32 y) noexcept {
			SetTopLeft(NormalizeWidth(x), NormalizeHeight(y));
		}

		void SetWidth(U32 width) noexcept {
			m_viewport.Width = static_cast< F32 >(width);
		}

		void SetWidth(F32 width) noexcept {
			m_viewport.Width = width;
		}

		void SetNormalizedWidth(F32 width) noexcept {
			SetWidth(NormalizeWidth(width));
		}

		void SetHeight(U32 height) noexcept {
			m_viewport.Height = static_cast< F32 >(height);
		}

		void SetHeight(F32 height) noexcept {
			m_viewport.Height = height;
		}

		void SetNormalizedHeight(F32 height) noexcept {
			SetHeight(NormalizeHeight(height));
		}

		void SetWidthAndHeight(U32 width, U32 height) noexcept {
			SetWidth(width);
			SetHeight(height);
		}

		void SetWidthAndHeight(F32 width, F32 height) noexcept {
			SetWidth(width);
			SetHeight(height);
		}

		void SetNormalizedWidthAndHeight(F32 width, F32 height) noexcept {
			SetWidth(NormalizeWidth(width));
			SetHeight(NormalizeHeight(height));
		}

		void SetMinimumDepth(F32 min_depth) noexcept {
			m_viewport.MinDepth = min_depth;
		}

		void SetMaximumDepth(F32 max_depth) noexcept {
			m_viewport.MaxDepth = max_depth;
		}

		void SetDepth(F32 min_depth, F32 max_depth) noexcept {
			SetMinimumDepth(min_depth);
			SetMaximumDepth(max_depth);
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