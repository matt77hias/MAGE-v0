#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "resource\resource.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct CameraTransformBuffer final {
		XMMATRIX world_to_view;
		XMMATRIX view_to_projection;
	};

	struct ModelTransformBuffer final {
		XMMATRIX model_to_world;
	};

	class VertexShader : public Resource {

	public:

		VertexShader(ComPtr< ID3D11Device2 > device, const wstring &fname, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		virtual ~VertexShader() {}

		void Update(ComPtr< ID3D11DeviceContext2 > device_context, 
			const CameraTransformBuffer &camera, const ModelTransformBuffer &model);

	protected:

		HRESULT InitializeShader(ComPtr< ID3D11Device2 > device, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
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