#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"

#pragma endregion

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

		size_t GetNbVertices() const {
			return m_nb_vertices;
		}

		virtual HRESULT BindBuffers(ID3D11DeviceContext2 *device_context) const override;

		virtual HRESULT Draw(ID3D11DeviceContext2 *device_context) const override;

	protected:

		HRESULT InitializeBuffers(ID3D11Device2 *device);

		HRESULT UninitializeBuffers();

		HRESULT SetupVertexBuffer(ID3D11Device2 *device, const Vertex *vertices, size_t nb_vertices);

		size_t m_nb_vertices;

		ID3D11Buffer *m_vertex_buffer;

	private:

		FlatMesh(const FlatMesh &flat_mesh) = delete;
		FlatMesh &operator=(const FlatMesh &flat_mesh) = delete;
	};
}