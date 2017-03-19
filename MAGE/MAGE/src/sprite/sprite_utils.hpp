#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	inline XMVECTOR XMVectorLeftTopRightBottom(const RECT &rect) {
		const XMVECTOR v = XMLoadInt4(reinterpret_cast<const uint32_t *>(&rect));
		return XMConvertVectorIntToFloat(v, 0);
	}
	inline XMVECTOR XMVectorLeftTopWidthHeight(const RECT &rect) {
		const XMVECTOR v = XMVectorLeftTopRightBottom(rect);
		return v - XMVectorPermute< 0, 1, 4, 5 >(XMVectorZero(), v);

	}

	XMMATRIX GetViewportTransform(ID3D11DeviceContext *device_context, DXGI_MODE_ROTATION rotation_mode);
	XMMATRIX GetViewportTransform(ID3D11DeviceContext *device_context, DXGI_MODE_ROTATION rotation_mode, D3D11_VIEWPORT **viewport);
	XMMATRIX GetViewportTransform(const D3D11_VIEWPORT &viewport, DXGI_MODE_ROTATION rotation_mode);
}