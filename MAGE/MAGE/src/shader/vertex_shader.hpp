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
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	static struct CameraTransformBuffer final {
		XMMATRIX world_to_view;
		XMMATRIX view_to_projection;
	};

	static struct ModelTransformBuffer final {
		XMMATRIX model_to_world;
	};

	class VertexShader : Resource {

	public:

		VertexShader(ComPtr< ID3D11Device2 >, 
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, size_t nb_input_elements,
			const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);
		virtual ~VertexShader() {}

		void Update(ComPtr< ID3D11DeviceContext2 > device_context, 
			CameraTransformBuffer camera, ModelTransformBuffer model);

	protected:

		HRESULT InitializeShader(ComPtr< ID3D11Device2 > device, 
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, size_t nb_input_elements);
		HRESULT SetupBuffers(ComPtr< ID3D11Device2 > device);

		ComPtr< ID3D11VertexShader > m_vertex_shader;
		ComPtr< ID3D11InputLayout > m_vertex_layout;
		ComPtr< ID3D11Buffer > m_cb_camera;
		ComPtr< ID3D11Buffer > m_cb_model;

	private:

		VertexShader(const VertexShader &vertex_shader) = delete;
		VertexShader &operator=(const VertexShader &vertex_shader) = delete;
	};
}