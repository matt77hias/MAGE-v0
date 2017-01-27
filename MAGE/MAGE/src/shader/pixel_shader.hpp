#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <string>
namespace mage {
	using std::wstring;
}

#include <d3d11_2.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "support.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class PixelShader {

	public:

		PixelShader(ID3D11Device2 *device, const wstring &fname);
		virtual ~PixelShader();

	protected:

		HRESULT InitializeShader(ID3D11Device2 *device, const wstring &fname);
		HRESULT UninitializeShader();

		ID3D11PixelShader *m_pixel_shader;

	private:

		PixelShader(const PixelShader &pixel_shader) = delete;
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;
	};
}