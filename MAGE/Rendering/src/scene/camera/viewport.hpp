#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"
#include "renderer\configuration.hpp"
#include "renderer\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// Viewport Transformations
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Returns the viewport transform for the given viewport.

	 @param[in]		resolution
					The resolution of the viewport.
	 @return		The viewport transform for the given viewport.
	 */
	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV 
		GetViewportTransform(const U32x2& resolution) noexcept {

		const auto width  = (0 < resolution.m_x) ? 2.0f / resolution.m_x : 0.0f;
		const auto height = (0 < resolution.m_y) ? 2.0f / resolution.m_y : 0.0f;

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
		static const D3D11_VIEWPORT GetMaxViewport(const U32x2& resolution) noexcept {
			D3D11_VIEWPORT viewport = {};
			viewport.Width    = static_cast< F32 >(resolution.m_x);
			viewport.Height   = static_cast< F32 >(resolution.m_y);
			viewport.MaxDepth = 1.0f;
			return viewport;
		}

		[[nodiscard]]
		static const D3D11_VIEWPORT GetMaxViewport(const U32x2& resolution,
												   AADescriptor desc) noexcept {
			
			const auto multiplier = GetResolutionMultiplier(desc);

			D3D11_VIEWPORT viewport = GetMaxViewport(resolution);
			viewport.Width  *= multiplier;
			viewport.Height *= multiplier;
			return viewport;
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit Viewport() noexcept
			: m_viewport{} {}

		explicit Viewport(const U32x2& resolution) noexcept
			: Viewport(GetMaxViewport(resolution)) {}
		
		explicit Viewport(const U32x2& resolution, AADescriptor desc) noexcept
			: Viewport(GetMaxViewport(resolution, desc)) {}

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

		void Bind(ID3D11DeviceContext& device_context) const noexcept {
			Pipeline::RS::BindViewport(device_context, m_viewport);
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
		U32 GetTopLeftX() const noexcept {
			return static_cast< U32 >(m_viewport.TopLeftX);
		}

		[[nodiscard]]
		U32 GetTopLeftY() const noexcept {
			return static_cast< U32 >(m_viewport.TopLeftY);
		}

		[[nodiscard]]
		const U32x2 GetTopLeft() const noexcept {
			return U32x2(GetTopLeftX(), GetTopLeftY());
		}

		void SetTopLeftX(U32 x) noexcept {
			m_viewport.TopLeftX = static_cast< F32 >(x);
		}

		void SetTopLeftY(U32 y) noexcept {
			m_viewport.TopLeftY = static_cast< F32 >(y);
		}

		void SetTopLeft(U32 x, U32 y) noexcept {
			SetTopLeftX(x);
			SetTopLeftY(y);
		}

		void SetTopLeft(const U32x2& top_left) noexcept {
			SetTopLeftX(top_left.m_x);
			SetTopLeftY(top_left.m_y);
		}

		[[nodiscard]]
		U32 GetWidth() const noexcept {
			return static_cast< U32 >(m_viewport.Width);
		}

		[[nodiscard]]
		U32 GetHeight() const noexcept {
			return static_cast< U32 >(m_viewport.Height);
		}

		[[nodiscard]]
		const U32x2 GetResolution() const noexcept {
			return U32x2(GetWidth(), GetHeight());
		}

		void SetWidth(U32 width) noexcept {
			m_viewport.Width = static_cast< F32 >(width);
		}

		void SetHeight(U32 height) noexcept {
			m_viewport.Height = static_cast< F32 >(height);
		}

		void SetResolution(U32 width, U32 height) noexcept {
			SetWidth(width);
			SetHeight(height);
		}

		void SetResolution(const U32x2& resolution) noexcept {
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

		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetViewportTransform() const noexcept {
			return mage::rendering::GetViewportTransform(GetResolution());
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
}