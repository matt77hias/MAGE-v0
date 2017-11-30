#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"
#include "rendering\aa_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class Viewport final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		static const D3D11_VIEWPORT GetMaxViewport() noexcept;

		static const D3D11_VIEWPORT GetMaxViewport(
			U32 width, U32 height) noexcept {
			
			return GetMaxViewport(static_cast< F32 >(width), 
				                  static_cast< F32 >(height));
		}

		static const D3D11_VIEWPORT GetMaxViewport(
			F32 width, F32 height) noexcept {
			
			D3D11_VIEWPORT viewport = {};
			viewport.Width    = width;
			viewport.Height   = height;
			viewport.MaxDepth = 1.0f;
			return viewport;
		}

		static const D3D11_VIEWPORT GetMaxViewport(
			U32 width, U32 height, AADescriptor desc) noexcept {
			
			return GetMaxViewport(static_cast< F32 >(width),
				                  static_cast< F32 >(height), 
				                  desc);
		}

		static const D3D11_VIEWPORT GetMaxViewport(
			F32 width, F32 height, AADescriptor desc) noexcept {
			
			const U32 multiplier = GetResolutionMultiplier(desc);

			D3D11_VIEWPORT viewport = {};
			viewport.Width    = multiplier * width;
			viewport.Height   = multiplier * height;
			viewport.MaxDepth = 1.0f;
			return viewport;
		}

		static F32 NormalizeWidth(F32 x) noexcept;

		static F32 NormalizeHeight(F32 x) noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		Viewport()
			: Viewport(GetMaxViewport()) {}

		explicit Viewport(U32 width, U32 height)
			: Viewport(GetMaxViewport(width, height)) {}

		explicit Viewport(F32 width, F32 height)
			: Viewport(GetMaxViewport(width, height)) {}
		
		explicit Viewport(U32 width, U32 height, AADescriptor desc)
			: Viewport(GetMaxViewport(width, height, desc)) {}

		explicit Viewport(F32 width, F32 height, AADescriptor desc)
			: Viewport(GetMaxViewport(width, height, desc)) {}

		explicit Viewport(D3D11_VIEWPORT viewport)
			: m_viewport(std::move(viewport)) {}
		
		Viewport(const Viewport &viewport) = default;
		
		Viewport(Viewport &&viewport) = default;

		explicit Viewport(Viewport viewport, AADescriptor desc)
			: Viewport(std::move(viewport)) {

			const U32 multiplier = GetResolutionMultiplier(desc);
			m_viewport.TopLeftX *= multiplier;
			m_viewport.TopLeftY *= multiplier;
			m_viewport.Width    *= multiplier;
			m_viewport.Height   *= multiplier;
		}

		~Viewport() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Viewport &operator=(const Viewport &viewport) = default;
		
		Viewport &operator=(Viewport &&viewport) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindViewport(ID3D11DeviceContext4 *device_context) const noexcept {
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
						The viewport.
		*/
		void SetViewport(D3D11_VIEWPORT viewport) noexcept {
			m_viewport = std::move(viewport);
		}

		F32 GetTopLeftX() const noexcept {
			return m_viewport.TopLeftX;
		}

		F32 GetTopLeftY() const noexcept {
			return m_viewport.TopLeftY;
		}

		const F32x2 GetTopLeft() const noexcept {
			return F32x2(m_viewport.TopLeftX, m_viewport.TopLeftY);
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

		F32 GetWidth() const noexcept {
			return m_viewport.Width;
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

		F32 GetHeight() const noexcept {
			return m_viewport.Height;
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

		F32 GetMinimumDepth() const noexcept {
			return m_viewport.MinDepth;
		}

		void SetMinimumDepth(F32 min_depth) noexcept {
			m_viewport.MinDepth = min_depth;
		}

		F32 GetMaximumDepth() const noexcept {
			return m_viewport.MaxDepth;
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