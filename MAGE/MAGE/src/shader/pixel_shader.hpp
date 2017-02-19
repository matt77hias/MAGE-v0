#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "resource\resource.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class PixelShader : public Resource {

	public:

		PixelShader(const wstring &fname, ComPtr< ID3D11Device2 > device);
		virtual ~PixelShader() {}
		
		void Update(ComPtr< ID3D11DeviceContext2 > device_context);

	protected:

		HRESULT InitializeShader(ComPtr< ID3D11Device2 > device);

		ComPtr< ID3D11PixelShader > m_pixel_shader;

	private:

		PixelShader(const PixelShader &pixel_shader) = delete;
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;
	};
}