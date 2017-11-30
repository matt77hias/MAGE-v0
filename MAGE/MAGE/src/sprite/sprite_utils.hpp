#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Converts the given @c RECT (left, top, right, bottom) to a @c XMVECTOR 
	 (left, top, right, bottom).

	 @param[in]		rect
					A reference to the rectangle.
	 @return		A @c XMVECTOR  (left, top, right, bottom) representing the 
					given @c RECT (left, top, right, bottom).
	 */
	inline const XMVECTOR XM_CALLCONV XMVectorLeftTopRightBottom(
		const RECT &rect) noexcept {
		
		const XMVECTOR v = XMLoadInt4(reinterpret_cast< const U32 * >(&rect));
		return XMConvertVectorIntToFloat(v, 0);
	}

	/**
	 Converts the given @c RECT (left, top, right, bottom) to a @c XMVECTOR 
	 (left, top, width, height).

	 @param[in]		rect
					A reference to the rectangle.
	 @return		A @c XMVECTOR  (left, top, width, height) representing the 
					given @c RECT (left, top, right, bottom).
	 */
	inline const XMVECTOR XM_CALLCONV XMVectorLeftTopWidthHeight(
		const RECT &rect) noexcept {

		const XMVECTOR v = XMVectorLeftTopRightBottom(rect);
		return v - XMVectorPermute< 0, 1, 4, 5 >(XMVectorZero(), v);

	}

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
	 @throws		FormattedException
					A viewport needs to be set.
	 */
	const XMMATRIX XM_CALLCONV GetViewportTransform(
		ID3D11DeviceContext4 *device_context,
		DXGI_MODE_ROTATION rotation_mode);

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
	 @throws		FormattedException
					A viewport needs to be set.
	 */
	const XMMATRIX XM_CALLCONV GetViewportTransform(
		ID3D11DeviceContext4 *device_context,
		DXGI_MODE_ROTATION rotation_mode, 
		D3D11_VIEWPORT *viewport);
	
	/**
	 Returns the viewport transform for the viewport and rotation mode.

	 @param[in]		viewport
					A reference to the viewport.
	 @param[in]		rotation_mode
					The rotation mode.
	 @return		The viewport transform for
					the given viewport and rotation mode.
	 */
	const XMMATRIX GetViewportTransform(
		const D3D11_VIEWPORT &viewport, 
		DXGI_MODE_ROTATION rotation_mode) noexcept;
}