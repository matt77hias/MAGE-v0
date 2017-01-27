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

	class VertexShader {

	public:

		VertexShader(ID3D11Device2 *device, const wstring &fname);
		virtual ~VertexShader();

	protected:

		HRESULT InitializeShader(ID3D11Device2 *device, const wstring &fname);
		HRESULT UninitializeShader();

		ID3D11VertexShader *m_vertex_shader;

	private:

		VertexShader(const VertexShader &vertex_shader) = delete;
		VertexShader &operator=(const VertexShader &vertex_shader) = delete;
	};
}