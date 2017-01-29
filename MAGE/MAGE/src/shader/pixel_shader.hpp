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

#include "memory\memory.hpp"
#include "resource\resource.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class PixelShader : Resource {

	public:

		PixelShader(ComPtr< ID3D11Device2 > device, const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);
		virtual ~PixelShader() {}

	protected:

		HRESULT InitializeShader(ComPtr< ID3D11Device2 > device);

		ComPtr< ID3D11PixelShader > m_pixel_shader;

	private:

		PixelShader(const PixelShader &pixel_shader) = delete;
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;
	};
}