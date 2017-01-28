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
	 A class of indexed meshes.
	 */
	class IndexedMesh : Mesh {

	public:

		/**
		 Constructs an indexed mesh.

		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		name
						A reference to the name of the mesh.
		 @param[in]		path
						A reference to the path of the mesh.
		 */
		IndexedMesh(ID3D11Device2 *device, const string &name, const string &path = "./");

		/**
		Destructs this indexed mesh.
		*/
		virtual ~IndexedMesh();

		size_t GetNbVertices() const {
			return m_nb_vertices;
		}

		virtual HRESULT BindBuffers(ID3D11DeviceContext2 *device_context) const override;

		virtual HRESULT Draw(ID3D11DeviceContext2 *device_context) const override;

	protected:

		HRESULT InitializeBuffers(ID3D11Device2 *device);

		HRESULT UninitializeBuffers();

		HRESULT SetupVertexBuffer(ID3D11Device2 *device, const Vertex *vertices, size_t nb_vertices);

		HRESULT SetupIndexBuffer(ID3D11Device2 *device, const uint32_t *indices, size_t nb_indices);

		size_t m_nb_vertices;

		ID3D11Buffer *m_vertex_buffer;
		ID3D11Buffer *m_index_buffer;

	private:

		IndexedMesh(const IndexedMesh &indexed_mesh) = delete;
		IndexedMesh &operator=(const IndexedMesh &indexed_mesh) = delete;
	};
}