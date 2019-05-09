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

		const auto width  = (0u < resolution[0]) ? 2.0f / resolution[0] : 0.0f;
		const auto height = (0u < resolution[1]) ? 2.0f / resolution[1] : 0.0f;

		// x =  Sx . [0,W] - 1 =  2/W . [0,W] - 1 = [0, 2] - 1 = [-1,  1]
		// y = -Sy . [0,H] + 1 = -2/H . [0,H] + 1 = [0,-2] + 1 = [ 1, -1]

		return {
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
	class Viewport {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit Viewport() noexcept
			: m_viewport{} {}

		explicit Viewport(const U32x2& size) noexcept
			: Viewport(GetMaxViewport(size)) {}

		explicit Viewport(const U32x2& size, AntiAliasing aa) noexcept
			: Viewport(GetMaxViewport(size, aa)) {}

		explicit Viewport(D3D11_VIEWPORT viewport) noexcept
			: m_viewport(std::move(viewport)) {}

		Viewport(const Viewport& viewport) noexcept = default;

		Viewport(Viewport&& viewport) noexcept = default;

		explicit Viewport(Viewport viewport, AntiAliasing aa) noexcept
			: Viewport(std::move(viewport)) {

			const auto multiplier = GetResolutionMultiplier(aa);
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
						A reference to the viewport.
		*/
		void SetViewport(const D3D11_VIEWPORT& viewport) noexcept {
			m_viewport = viewport;
		}

		[[nodiscard]]
		const S32x2 GetTopLeft() const noexcept {
			return { static_cast< S32 >(m_viewport.TopLeftX),
				     static_cast< S32 >(m_viewport.TopLeftY) };
		}

		void SetTopLeft(S32 x, S32 y) noexcept {
			m_viewport.TopLeftX = static_cast< F32 >(x);
			m_viewport.TopLeftY = static_cast< F32 >(y);
		}

		void SetTopLeft(const S32x2& top_left) noexcept {
			SetTopLeft(top_left[0], top_left[1]);
		}

		[[nodiscard]]
		const U32x2 GetSize() const noexcept {
			return { static_cast< U32 >(m_viewport.Width),
				     static_cast< U32 >(m_viewport.Height) };
		}

		void SetSize(U32 x, U32 y) noexcept {
			m_viewport.Width  = static_cast< F32 >(x);
			m_viewport.Height = static_cast< F32 >(y);
		}

		void SetSize(const U32x2& size) noexcept {
			SetSize(size[0], size[1]);
		}

		[[nodiscard]]
		const F32x2 GetDepthRange() const noexcept {
			return { m_viewport.MinDepth, m_viewport.MaxDepth };
		}

		void SetDepthRange(F32 min_depth, F32 max_depth) noexcept {
			m_viewport.MinDepth = min_depth;
			m_viewport.MaxDepth = max_depth;
		}

		void SetDepthRange(const F32x2& range) noexcept {
			SetDepthRange(range[0], range[1]);
		}

		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetViewportTransform() const noexcept {
			return mage::rendering::GetViewportTransform(GetSize());
		}

	private:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		static const D3D11_VIEWPORT GetMaxViewport(const U32x2& size) noexcept {
			D3D11_VIEWPORT viewport = {};
			viewport.Width    = static_cast< F32 >(size[0]);
			viewport.Height   = static_cast< F32 >(size[1]);
			viewport.MaxDepth = 1.0f;
			return viewport;
		}

		[[nodiscard]]
		static const D3D11_VIEWPORT GetMaxViewport(const U32x2& size,
												   AntiAliasing aa) noexcept {

			const auto multiplier = GetResolutionMultiplier(aa);

			D3D11_VIEWPORT viewport = GetMaxViewport(size);
			viewport.Width  *= multiplier;
			viewport.Height *= multiplier;
			return viewport;
		}


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