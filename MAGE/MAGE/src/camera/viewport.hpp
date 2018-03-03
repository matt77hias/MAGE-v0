#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"
#include "rendering\rendering.hpp"
#include "rendering\aa_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Viewport
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of viewports.
	 */
	class Viewport final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		static const D3D11_VIEWPORT GetMaxViewport(U32 width, U32 height) noexcept {
			return GetMaxViewport(static_cast< F32 >(width), 
				                  static_cast< F32 >(height));
		}

		[[nodiscard]]
		static const D3D11_VIEWPORT GetMaxViewport(F32 width, F32 height) noexcept {
			D3D11_VIEWPORT viewport = {};
			viewport.Width    = width;
			viewport.Height   = height;
			viewport.MaxDepth = 1.0f;
			return viewport;
		}

		[[nodiscard]]
		static const D3D11_VIEWPORT GetMaxViewport(U32 width, U32 height, 
												   AADescriptor desc) noexcept {
			
			return GetMaxViewport(static_cast< F32 >(width),
				                  static_cast< F32 >(height), 
				                  desc);
		}

		[[nodiscard]]
		static const D3D11_VIEWPORT GetMaxViewport(F32 width, F32 height, 
												   AADescriptor desc) noexcept {
			
			const auto multiplier = GetResolutionMultiplier(desc);

			D3D11_VIEWPORT viewport = {};
			viewport.Width    = multiplier * width;
			viewport.Height   = multiplier * height;
			viewport.MaxDepth = 1.0f;
			return viewport;
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit Viewport(U32 width, U32 height) noexcept
			: Viewport(GetMaxViewport(width, height)) {}

		explicit Viewport(F32 width, F32 height) noexcept
			: Viewport(GetMaxViewport(width, height)) {}
		
		explicit Viewport(U32 width, U32 height, AADescriptor desc) noexcept
			: Viewport(GetMaxViewport(width, height, desc)) {}

		explicit Viewport(F32 width, F32 height, AADescriptor desc) noexcept
			: Viewport(GetMaxViewport(width, height, desc)) {}

		explicit Viewport(D3D11_VIEWPORT viewport) noexcept
			: m_viewport(std::move(viewport)) {}
		
		Viewport(const Viewport& viewport) noexcept = default;
		
		Viewport(Viewport&& viewport) noexcept = default;

		explicit Viewport(Viewport viewport, AADescriptor desc) noexcept
			: Viewport(std::move(viewport)) {

			const auto multiplier = GetResolutionMultiplier(desc);
			m_viewport.TopLeftX *= multiplier;
			m_viewport.TopLeftY *= multiplier;
			m_viewport.Width    *= multiplier;
			m_viewport.Height   *= multiplier;
		}

		~Viewport() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Viewport& operator=(const Viewport& viewport) noexcept = default;
		
		Viewport& operator=(Viewport&& viewport) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindViewport(ID3D11DeviceContext& device_context) const noexcept {
			Pipeline::RS::BindViewport(device_context, &m_viewport);
		}

		/**
		 Returns the viewport of this viewport.

		 @return		A reference to the viewport of this viewport.
		 */
		[[nodiscard]]
		const D3D11_VIEWPORT& GetViewport() const noexcept {
			return m_viewport;
		}

		/**
		Sets the viewport of this viewport to the given viewport.

		@param[in]		viewport
						The viewport.
		*/
		void SetViewport(D3D11_VIEWPORT viewport) noexcept {
			m_viewport = std::move(viewport);
		}

		[[nodiscard]]
		F32 GetTopLeftX() const noexcept {
			return m_viewport.TopLeftX;
		}

		[[nodiscard]]
		F32 GetTopLeftY() const noexcept {
			return m_viewport.TopLeftY;
		}

		[[nodiscard]]
		const F32x2 GetTopLeft() const noexcept {
			return F32x2(GetTopLeftX(), GetTopLeftY());
		}

		void SetTopLeftX(U32 x) noexcept {
			SetTopLeftX(static_cast< F32 >(x));
		}

		void SetTopLeftX(F32 x) noexcept {
			m_viewport.TopLeftX = x;
		}

		void SetTopLeftY(U32 y) noexcept {
			SetTopLeftY(static_cast< F32 >(y));
		}

		void SetTopLeftY(F32 y) noexcept {
			m_viewport.TopLeftY = y;
		}

		void SetTopLeft(U32 x, U32 y) noexcept {
			SetTopLeftX(x);
			SetTopLeftY(y);
		}

		void SetTopLeft(U32x2 top_left) noexcept {
			SetTopLeftX(top_left.m_x);
			SetTopLeftY(top_left.m_y);
		}

		void SetTopLeft(F32 x, F32 y) noexcept {
			SetTopLeftX(x);
			SetTopLeftY(y);
		}

		void SetTopLeft(F32x2 top_left) noexcept {
			SetTopLeftX(top_left.m_x);
			SetTopLeftY(top_left.m_y);
		}

		[[nodiscard]]
		F32 GetWidth() const noexcept {
			return m_viewport.Width;
		}

		[[nodiscard]]
		F32 GetHeight() const noexcept {
			return m_viewport.Height;
		}

		[[nodiscard]]
		const F32x2 GetWidthAndHeight() const noexcept {
			return F32x2(GetWidth(), GetHeight());
		}

		void SetWidth(U32 width) noexcept {
			SetWidth(static_cast< F32 >(width));
		}

		void SetWidth(F32 width) noexcept {
			m_viewport.Width = width;
		}

		void SetHeight(U32 height) noexcept {
			SetHeight(static_cast< F32 >(height));
		}

		void SetHeight(F32 height) noexcept {
			m_viewport.Height = height;
		}

		void SetWidthAndHeight(U32 width, U32 height) noexcept {
			SetWidth(width);
			SetHeight(height);
		}

		void SetWidthAndHeight(U32x2 resolution) noexcept {
			SetWidth(resolution.m_x);
			SetHeight(resolution.m_y);
		}

		void SetWidthAndHeight(F32 width, F32 height) noexcept {
			SetWidth(width);
			SetHeight(height);
		}

		void SetWidthAndHeight(F32x2 resolution) noexcept {
			SetWidth(resolution.m_x);
			SetHeight(resolution.m_y);
		}

		[[nodiscard]]
		F32 GetMinimumDepth() const noexcept {
			return m_viewport.MinDepth;
		}

		void SetMinimumDepth(F32 min_depth) noexcept {
			m_viewport.MinDepth = min_depth;
		}

		[[nodiscard]]
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

	#pragma endregion

	//-------------------------------------------------------------------------
	// Viewport Transformations
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Returns the viewport transform for the given viewport.

	 @param[in]		viewport
					A reference to the viewport.
	 @return		The viewport transform for the given viewport.
	 */
	[[nodiscard]]
	const XMMATRIX XM_CALLCONV 
		GetViewportTransform(const D3D11_VIEWPORT& viewport) noexcept {

		const auto width  = (viewport.Width  > 0.0f) ?
							2.0f / viewport.Width  : 0.0f;
		const auto height = (viewport.Height > 0.0f) ?
							2.0f / viewport.Height : 0.0f;

		// x =  Sx . [0,W] - 1 =  2/W . [0,W] - 1 = [0, 2] - 1 = [-1,  1]
		// y = -Sy . [0,H] + 1 = -2/H . [0,H] + 1 = [0,-2] + 1 = [ 1, -1]
		
		return XMMATRIX {
			width,    0.0f, 0.0f, 0.0f,
			 0.0f, -height, 0.0f, 0.0f,
			 0.0f,    0.0f, 1.0f, 0.0f,
			-1.0f,    1.0f, 0.0f, 1.0f
		};
	}

	#pragma endregion
}