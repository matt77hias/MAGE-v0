#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"
#include "rendering\aa_descriptor.hpp"
#include "math\transform\sprite_transform.hpp"

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

		[[nodiscard]] static const D3D11_VIEWPORT GetMaxViewport() noexcept;

		[[nodiscard]] static const D3D11_VIEWPORT 
			GetMaxViewport(U32 width, U32 height) noexcept {
			
			return GetMaxViewport(static_cast< F32 >(width), 
				                  static_cast< F32 >(height));
		}

		[[nodiscard]] static const D3D11_VIEWPORT 
			GetMaxViewport(F32 width, F32 height) noexcept {
			
			D3D11_VIEWPORT viewport = {};
			viewport.Width    = width;
			viewport.Height   = height;
			viewport.MaxDepth = 1.0f;
			return viewport;
		}

		[[nodiscard]] static const D3D11_VIEWPORT 
			GetMaxViewport(U32 width, U32 height, AADescriptor desc) noexcept {
			
			return GetMaxViewport(static_cast< F32 >(width),
				                  static_cast< F32 >(height), 
				                  desc);
		}

		[[nodiscard]] static const D3D11_VIEWPORT 
			GetMaxViewport(F32 width, F32 height, AADescriptor desc) noexcept {
			
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

		Viewport() noexcept
			: Viewport(GetMaxViewport()) {}

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
		
		Viewport(const Viewport &viewport) noexcept = default;
		
		Viewport(Viewport &&viewport) noexcept = default;

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

		Viewport &operator=(const Viewport &viewport) noexcept = default;
		
		Viewport &operator=(Viewport &&viewport) noexcept = default;

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
		[[nodiscard]] const D3D11_VIEWPORT &GetViewport() const noexcept {
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

		[[nodiscard]] F32 GetTopLeftX() const noexcept {
			return m_viewport.TopLeftX;
		}

		[[nodiscard]] F32 GetTopLeftY() const noexcept {
			return m_viewport.TopLeftY;
		}

		[[nodiscard]] const F32x2 GetTopLeft() const noexcept {
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

		[[nodiscard]] F32 GetNormalizedTopLeftX() const noexcept {
			return ConvertAbsoluteToNormalizedScreenX(GetTopLeftX());
		}

		[[nodiscard]] F32 GetNormalizedTopLeftY() const noexcept {
			return ConvertAbsoluteToNormalizedScreenY(GetTopLeftY());
		}

		[[nodiscard]] const F32x2 GetNormalizedTopLeft() const noexcept {
			return ConvertAbsoluteToNormalizedScreen(GetTopLeft());
		}

		void SetNormalizedTopLeftX(U32 x) noexcept {
			SetNormalizedTopLeftX(static_cast< F32 >(x));
		}

		void SetNormalizedTopLeftX(F32 x) noexcept {
			SetTopLeftX(ConvertNormalizedToAbsoluteScreenX(x));
		}

		void SetNormalizedTopLeftY(U32 y) noexcept {
			SetNormalizedTopLeftY(static_cast< F32 >(y));
		}

		void SetNormalizedTopLeftY(F32 y) noexcept {
			SetTopLeftY(ConvertNormalizedToAbsoluteScreenY(y));
		}

		void SetNormalizedTopLeft(U32 x, U32 y) noexcept {
			SetNormalizedTopLeftX(x);
			SetNormalizedTopLeftY(y);
		}

		void SetNormalizedTopLeft(U32x2 top_left) noexcept {
			SetNormalizedTopLeftX(top_left.m_x);
			SetNormalizedTopLeftY(top_left.m_y);
		}

		void SetNormalizedTopLeft(F32 x, F32 y) noexcept {
			SetNormalizedTopLeftX(x);
			SetNormalizedTopLeftY(y);
		}

		void SetNormalizedTopLeft(F32x2 top_left) noexcept {
			SetNormalizedTopLeftX(top_left.m_x);
			SetNormalizedTopLeftY(top_left.m_y);
		}

		[[nodiscard]] F32 GetWidth() const noexcept {
			return m_viewport.Width;
		}

		[[nodiscard]] F32 GetHeight() const noexcept {
			return m_viewport.Height;
		}

		[[nodiscard]] const F32x2 GetWidthAndHeight() const noexcept {
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

		[[nodiscard]] F32 GetNormalizedWidth() const noexcept {
			return ConvertAbsoluteToNormalizedScreenX(GetWidth());
		}

		[[nodiscard]] F32 GetNormalizedHeight() const noexcept {
			return ConvertAbsoluteToNormalizedScreenY(GetHeight());
		}

		[[nodiscard]] const F32x2 GetNormalizedWidthAndHeight() const noexcept {
			return ConvertAbsoluteToNormalizedScreen(GetWidthAndHeight());
		}

		void SetNormalizedWidth(U32 width) noexcept {
			SetNormalizedWidth(static_cast< F32 >(width));
		}

		void SetNormalizedWidth(F32 width) noexcept {
			SetWidth(ConvertNormalizedToAbsoluteScreenX(width));
		}

		void SetNormalizedHeight(U32 height) noexcept {
			SetNormalizedHeight(static_cast< F32 >(height));
		}

		void SetNormalizedHeight(F32 height) noexcept {
			SetHeight(ConvertNormalizedToAbsoluteScreenY(height));
		}

		void SetNormalizedWidthAndHeight(U32 width, U32 height) noexcept {
			SetNormalizedWidth(width);
			SetNormalizedHeight(height);
		}

		void SetNormalizedWidthAndHeight(U32x2 resolution) noexcept {
			SetNormalizedWidth(resolution.m_x);
			SetNormalizedHeight(resolution.m_y);
		}

		void SetNormalizedWidthAndHeight(F32 width, F32 height) noexcept {
			SetNormalizedWidth(width);
			SetNormalizedHeight(height);
		}

		void SetNormalizedWidthAndHeight(F32x2 resolution) noexcept {
			SetNormalizedWidth(resolution.m_x);
			SetNormalizedHeight(resolution.m_y);
		}

		[[nodiscard]] F32 GetMinimumDepth() const noexcept {
			return m_viewport.MinDepth;
		}

		void SetMinimumDepth(F32 min_depth) noexcept {
			m_viewport.MinDepth = min_depth;
		}

		[[nodiscard]] F32 GetMaximumDepth() const noexcept {
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
	 Returns the viewport transform for the given device context and rotation 
	 mode.

	 @pre			@a device_context is not equal to @c nullptr.
	 @param[in]		device_context
					A pointer to the device context.
	 @param[in]		rotation_mode
					The rotation mode.
	 @return		The viewport transform for 
					the given device context and rotation mode.
	 @throws		Exception
					A viewport needs to be set.
	 */
	[[nodiscard]] const XMMATRIX XM_CALLCONV 
		GetViewportTransform(ID3D11DeviceContext4 *device_context,
		                     DXGI_MODE_ROTATION rotation_mode 
			                 = DXGI_MODE_ROTATION_IDENTITY);

	/**
	 Returns the viewport transform for the given device context and rotation 
	 mode.

	 @pre			@a device_context is not equal to @c nullptr.
	 @pre			@a viewport is not equal to @c nullptr.
	 @param[in]		device_context
					A pointer to the device context.
	 @param[in]		rotation_mode
					The rotation mode.
	 @param[out]	viewport
					A pointer to the viewport.
	 @return		The viewport transform for
					the given device context and rotation mode.
	 @throws		Exception
					A viewport needs to be set.
	 */
	[[nodiscard]] const XMMATRIX XM_CALLCONV 
		GetViewportTransform(ID3D11DeviceContext4 *device_context,
			                 D3D11_VIEWPORT *viewport,
		                     DXGI_MODE_ROTATION rotation_mode
			                 = DXGI_MODE_ROTATION_IDENTITY);
	
	/**
	 Returns the viewport transform for the viewport and rotation mode.

	 @param[in]		viewport
					A reference to the viewport.
	 @param[in]		rotation_mode
					The rotation mode.
	 @return		The viewport transform for
					the given viewport and rotation mode.
	 */
	[[nodiscard]] const XMMATRIX XM_CALLCONV 
		GetViewportTransform(const D3D11_VIEWPORT &viewport, 
		                     DXGI_MODE_ROTATION rotation_mode 
			                 = DXGI_MODE_ROTATION_IDENTITY) noexcept;

	#pragma endregion
}