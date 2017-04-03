#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed static meshes.
	 */
	class StaticMesh : public Mesh {

	public:

		/**
		 Constructs a static mesh.

		 @pre			@a vertices may not be equal to @c nullptr
		 @pre			@a indices may not be equal to @c nullptr
		 @tparam		VertexT
						The vertex type.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
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
		explicit StaticMesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const VertexT *vertices, size_t nb_vertices, 
			const uint32_t *indices, size_t nb_indices);

		/**
		 Constructs a static mesh.

		 @pre			The number of vertices must be greater than zero.
		 @pre			The number of indices must be greater than zero.
		 @tparam		VertexT
						The vertex type.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		vertices
						A reference to a vector of vertices.
		 @param[in]		indices
						A reference to a vector of indices.
		 */
		template < typename VertexT >
		explicit StaticMesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const vector< VertexT > &vertices, const vector< uint32_t > &indices)
			: StaticMesh(device, device_context, 
				vertices.data(), vertices.size(), 
				indices.data(), indices.size()) {}

		/**
		 Constructs a static mesh from the given static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh.
		 */
		StaticMesh(StaticMesh &&static_mesh) = default;

		/**
		 Destructs this static mesh.
		 */
		virtual ~StaticMesh() = default;

	private:

		/**
		 Constructs a static mesh from the given static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh.
		 */
		StaticMesh(const StaticMesh &static_mesh) = delete;

		/**
		 Copies the given static mesh to this static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh to copy from.
		 @return		A reference to the copy of the given static mesh
						(i.e. this static mesh).
		 */
		StaticMesh &operator=(const StaticMesh &static_mesh) = delete;

		/**
		 Copies the given static mesh to this static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh to copy from.
		 @return		A reference to the copy of the given static mesh
						(i.e. this static mesh).
		 */
		StaticMesh &operator=(StaticMesh &&static_mesh) = delete;

		/**
		 Sets up the vertex buffer of this static mesh.

		 @pre			@a vertices may not be equal to @c nullptr
		 @tparam		VertexT
						The vertex type.
		 @param[in]		vertices
						A pointer to an array of vertices.
		 @param[in]		nb_vertices
						The number of vertices.
		 */
		template < typename VertexT >
		HRESULT SetupVertexBuffer(const VertexT *vertices, size_t nb_vertices);

		/**
		 Sets up the index buffer of this static mesh.

		 @pre			@a indices may not be equal to @c nullptr
		 @param[in]		indices
						A pointer to an array of indices.
		 @param[in]		nb_indices
						The number of indices.
		 */
		HRESULT SetupIndexBuffer(const uint32_t *indices, size_t nb_indices);
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.tpp"

#pragma endregion