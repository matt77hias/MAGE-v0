#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of flat meshes.
	 */
	class FlatMesh : Mesh {

	public:

		/**
		 Constructs a flat mesh.

		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		name
						A reference to the name of the mesh.
		 @param[in]		path
						A reference to the path of the mesh.
		 */
		FlatMesh(ID3D11Device2 *device, const string &name, const string &path = "./");

		/**
		 Destructs this flat mesh.
		 */
		virtual ~FlatMesh();

		virtual HRESULT BindBuffers(ID3D11DeviceContext2 *device_context) override;

	protected:

		HRESULT InitializeBuffers(ID3D11Device2 *device);

		HRESULT UninitializeBuffers();

		HRESULT SetupVertexBuffer(ID3D11Device2 *device, const Vertex *vertices, size_t nb_vertices);

		ID3D11Buffer *m_vertex_buffer;
	};
}