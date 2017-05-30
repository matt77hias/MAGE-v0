#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"
#include "math\bounding_volume.hpp"
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

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a static mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a vertices points to an array of at least @a nb_vertices vertices.
		 @pre			@a nb_vertices must be greater than zero.
		 @pre			@a indices points to an array of at least @a nb_indices indices.
		 @pre			@a nb_indices must be greater than zero.
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

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
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
		 @throws		FormattedException
						Failed to setup the vertex buffer of the static mesh.
		 @throws		FormattedException
						Failed to setup the index buffer of the static mesh.
		 */
		template < typename VertexT >
		explicit StaticMesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const vector< VertexT > &vertices, const vector< uint32_t > &indices);

		/**
		 Constructs a static mesh from the given static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh to copy.
		 */
		StaticMesh(const StaticMesh &static_mesh) = delete;

		/**
		 Constructs a static mesh by moving the given static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh to move.
		 */
		StaticMesh(StaticMesh &&static_mesh);

		/**
		 Destructs this static mesh.
		 */
		virtual ~StaticMesh();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given static mesh to this static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh to copy.
		 @return		A reference to the copy of the given static mesh
						(i.e. this static mesh).
		 */
		StaticMesh &operator=(const StaticMesh &static_mesh) = delete;

		/**
		 Moves the given static mesh to this static mesh.

		 @param[in]		static_mesh
						A reference to the static mesh to move.
		 @return		A reference to the moved static mesh
						(i.e. this static mesh).
		 */
		StaticMesh &operator=(StaticMesh &&static_mesh) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the AABB of this static mesh.

		 @return		A reference to the AABB of this static mesh.
		 */
		const AABB &GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		 Returns the BS of this static mesh.

		 @return		A reference to the BS of this static mesh.
		 */
		const BS &GetBS() const noexcept {
			return m_bs;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up the bounding volumes of this static mesh.

		 @pre			@a vertices points to an array of at least @a nb_vertices vertices.
		 @pre			@a nb_vertices must be greater than zero.
		 @tparam		VertexT
						The vertex type.
		 @param[in]		vertices
						A pointer to an array of vertices.
		 @param[in]		nb_vertices
						The number of vertices.
		 */
		template < typename VertexT >
		void SetupBoundingVolumes(const VertexT *vertices, size_t nb_vertices) noexcept;

		/**
		 Sets up the vertex buffer of this static mesh.

		 @pre			@a vertices points to an array of at least @a nb_vertices vertices.
		 @pre			@a nb_vertices must be greater than zero.
		 @tparam		VertexT
						The vertex type.
		 @param[in]		vertices
						A pointer to an array of vertices.
		 @param[in]		nb_vertices
						The number of vertices.
		 @throws		FormattedException
						Failed to setup the vertex buffer of this static mesh.
		 */
		template < typename VertexT >
		void SetupVertexBuffer(const VertexT *vertices, size_t nb_vertices);

		/**
		 Sets up the index buffer of this static mesh.

		 @pre			@a indices points to an array of at least @a nb_indices indices.
		 @pre			@a nb_indices must be greater than zero.
		 @param[in]		indices
						A pointer to an array of indices.
		 @param[in]		nb_indices
						The number of indices.
		 @throws		FormattedException
						Failed to setup the index buffer of this static mesh.
		 */
		void SetupIndexBuffer(const uint32_t *indices, size_t nb_indices);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The AABB of this static mesh.
		 */
		AABB m_aabb;

		/**
		 The BS of this static mesh.
		 */
		BS m_bs;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.tpp"

#pragma endregion