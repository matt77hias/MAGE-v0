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

	class VertexShader : Resource {

	public:

		VertexShader(ComPtr< ID3D11Device2 >, const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);
		virtual ~VertexShader() {}

	protected:

		HRESULT InitializeShader(ComPtr< ID3D11Device2 >);

		ComPtr< ID3D11VertexShader > m_vertex_shader;

	private:

		VertexShader(const VertexShader &vertex_shader) = delete;
		VertexShader &operator=(const VertexShader &vertex_shader) = delete;
	};
}