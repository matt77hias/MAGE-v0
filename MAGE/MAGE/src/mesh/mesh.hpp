#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "collection\collection.hpp"
#include "resource\resource.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed meshes.
	 
	 @tparam		T
					The vertex type.
	 */
	template < typename Vertex >
	class Mesh : public Resource {

	public:

		/**
		 Constructs a mesh.

		 @pre			@a vertices may not be equal to @c nullptr
		 @pre			@a indices may not be equal to @c nullptr
		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		fname
						A reference to the file name of the mesh.
		 @param[in]		vertices
						A pointer to an array of vertices.
		 @param[in]		nb_vertices
						The number of vertices.
		 @param[in]		indices
						A pointer to an array of indices.
		 @param[in]		nb_indices
						The number of indices.
		 */
		Mesh(ComPtr< ID3D11Device2 > device, const wstring &fname, const Vertex *vertices, size_t nb_vertices, const uint32_t *indices, size_t nb_indices);

		/**
		 Constructs a mesh.

		 @pre			The number of vertices must be greater than zero.
		 @pre			The number of indices must be greater than zero.
		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		fname
						A reference to the file name of the mesh.
		 @param[in]		vertices
						A reference to a vector of vertices.
		 @param[in]		indices
						A reference to a vector of indices.
		 @param[in]		device
						A pointer to an D3D11 device.
		 */
		Mesh(ComPtr< ID3D11Device2 > device, const wstring &fname, const vector< Vertex > &vertices, const vector< uint32_t > &indices)
			: Mesh(device, fname, &vertices[0], vertices.size(), &indices[0], indices.size()) {}

		/**
		 Destructs this mesh.
		 */
		virtual ~Mesh() = default;

		void Update(ComPtr< ID3D11DeviceContext2 > device_context) const;

		/**
		 Returns the number of vertices of this mesh.

		 @return		The number of vertices of this mesh.
		 */
		size_t GetNumberOfVertices() const {
			return m_nb_vertices;
		}

		/**
		 Returns the number of indices of this mesh.

		 @return		The number of indices of this mesh.
		 */
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}

	protected:

		HRESULT SetupVertexBuffer(ComPtr< ID3D11Device2 > device, const Vertex *vertices, size_t nb_vertices);
		HRESULT SetupIndexBuffer(ComPtr< ID3D11Device2 > device, const uint32_t *indices, size_t nb_indices);

	private:

		/**
		 Constructs a mesh from the given mesh.

		 @param[in]		mesh
						A reference to the mesh.
		 */
		Mesh(const Mesh &mesh) = delete;

		/**
		 Copies the given mesh to this mesh.

		 @param[in]		mesh
						A reference to the mesh to copy from.
		 @return		A reference to the copy of the given mesh
						(i.e. this mesh).
		 */
		Mesh &operator=(const Mesh &mesh) = delete;

		/**
		 The number of vertices of this mesh.
		 */
		size_t m_nb_vertices;

		/**
		 The number of indices of this mesh.
		 */
		size_t m_nb_indices;

		/**
		 A pointer to the vertex buffer of this mesh.
		 */
		ComPtr< ID3D11Buffer > m_vertex_buffer;

		/**
		 A pointer to the index buffer of this mesh.
		 */
		ComPtr< ID3D11Buffer > m_index_buffer;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.tpp"

#pragma endregion