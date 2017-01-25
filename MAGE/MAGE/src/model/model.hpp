#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class Model : public Resource {

	public:

		/**
		 Constructs a variable script.

		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		name
						A reference to the name of the model.
		 @param[in]		path
						A reference to the path of the model.
		*/
		Model(ID3D11Device2 *device, const string &name, const string &path = "./");

		/**
		 Destructs this model.
		 */
		virtual ~Model();

		HRESULT BindBuffers(ID3D11DeviceContext2 *device_context);

	protected:

		HRESULT InitializeBuffers(ID3D11Device2 *device);

		HRESULT UninitializeBuffers();

		HRESULT SetupVertexBuffer(ID3D11Device2 *device, const Vertex *vertices, size_t nb_vertices);

		HRESULT SetupIndexBuffer(ID3D11Device2 *device, const uint32_t *indices, size_t nb_indices);

		ID3D11Buffer *m_vertex_buffer;
		ID3D11Buffer *m_index_buffer;
	};
}