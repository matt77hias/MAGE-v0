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

		static f32 NormalizeWidth(f32 x) noexcept;

		static f32 NormalizeHeight(f32 x) noexcept;

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

		void SetTopLeft(u32 x, u32 y) noexcept {
			m_viewport.TopLeftX = static_cast< f32 >(x);
			m_viewport.TopLeftY = static_cast< f32 >(y);
		}

		void SetTopLeft(f32 x, f32 y) noexcept {
			m_viewport.TopLeftX = x;
			m_viewport.TopLeftY = y;
		}

		void SetNormalizedTopLeft(f32 x, f32 y) noexcept {
			SetTopLeft(NormalizeWidth(x), NormalizeHeight(y));
		}

		void SetWidth(u32 width) noexcept {
			m_viewport.Width = static_cast< f32 >(width);
		}

		void SetWidth(f32 width) noexcept {
			m_viewport.Width = width;
		}

		void SetNormalizedWidth(f32 width) noexcept {
			SetWidth(NormalizeWidth(width));
		}

		void SetHeight(u32 height) noexcept {
			m_viewport.Height = static_cast< f32 >(height);
		}

		void SetHeight(f32 height) noexcept {
			m_viewport.Height = height;
		}

		void SetNormalizedHeight(f32 height) noexcept {
			SetHeight(NormalizeHeight(height));
		}

		void SetWidthAndHeight(u32 width, u32 height) noexcept {
			SetWidth(width);
			SetHeight(height);
		}

		void SetWidthAndHeight(f32 width, f32 height) noexcept {
			SetWidth(width);
			SetHeight(height);
		}

		void SetNormalizedWidthAndHeight(f32 width, f32 height) noexcept {
			SetWidth(NormalizeWidth(width));
			SetHeight(NormalizeHeight(height));
		}

		void SetMinimumDepth(f32 min_depth) noexcept {
			m_viewport.MinDepth = min_depth;
		}

		void SetMaximumDepth(f32 max_depth) noexcept {
			m_viewport.MaxDepth = max_depth;
		}

		void SetDepth(f32 min_depth, f32 max_depth) noexcept {
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