#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_factory.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed meshes.
	 */
	class Mesh {

	public:

		/**
		 Constructs a mesh.

		 @pre			@a vertices may not be equal to @c nullptr
		 @pre			@a indices may not be equal to @c nullptr
		 @tparam		VertexT
						The vertex type.
		 @param[in]		device
						A pointer to the rendering device.
		 @param[in]		vertices
						A pointer to an array of vertices.
		 @param[in]		nb_vertices
						The number of vertices.
		 @param[in]		indices
						A pointer to an array of indices.
		 @param[in]		nb_indices
						The number of indices.
		 */
		template < typename VertexT >
		Mesh(ComPtr< ID3D11Device2 > device, const VertexT *vertices, size_t nb_vertices, const uint32_t *indices, size_t nb_indices);

		/**
		 Constructs a mesh.

		 @pre			The number of vertices must be greater than zero.
		 @pre			The number of indices must be greater than zero.
		 @tparam		VertexT
						The vertex type.
		 @param[in]		device
						A pointer to the rendering device.
		 @param[in]		vertices
						A reference to a vector of vertices.
		 @param[in]		indices
						A reference to a vector of indices.
		 @param[in]		device
						A pointer to an D3D11 device.
		 */
		template < typename VertexT >
		Mesh(ComPtr< ID3D11Device2 > device, const vector< VertexT > &vertices, const vector< uint32_t > &indices)
			: Mesh(device, &vertices[0], vertices.size(), &indices[0], indices.size()) {}

		/**
		 Destructs this mesh.
		 */
		virtual ~Mesh() = default;

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


		void Render(ComPtr< ID3D11DeviceContext2 > device_context) const;

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
		 Initializes this mesh.

		 @pre			@a vertices may not be equal to @c nullptr
		 @pre			@a indices may not be equal to @c nullptr
		 @tparam		VertexT
						The vertex type.
		 @param[in]		device
						A pointer to the rendering device.
		 @param[in]		vertices
						A pointer to an array of vertices.
		 @param[in]		indices
						A pointer to an array of indices.
		 */
		template < typename VertexT >
		HRESULT InitializeMesh(ComPtr< ID3D11Device2 > device, const VertexT *vertices, const uint32_t *indices);

		/**
		 The size of the vertices of this mesh.
		 */
		size_t m_vertex_size;

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