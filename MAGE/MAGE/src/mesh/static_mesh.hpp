#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of static meshes.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 */
	template< typename VertexT, typename IndexT >
	class StaticMesh : public Mesh {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a static mesh.

		 @pre			The device associated with the current engine 
						must be loaded.
		 @pre			The number of vertices must be greater than zero.
		 @pre			The number of indices must be greater than zero.
		 @param[in]		vertices
						A vector containing the vertices.
		 @param[in]		indices
						A vector containing the indices.
		 @param[in]		primitive_topology
						The primitive topology.
		 @throws		Exception
						Failed to setup the vertex buffer of the static mesh.
		 @throws		Exception
						Failed to setup the index buffer of the static mesh.
		 */
		explicit StaticMesh(std::vector< VertexT > vertices,
			                std::vector< IndexT >  indices,
			                D3D11_PRIMITIVE_TOPOLOGY primitive_topology 
			                = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		/**
		 Constructs a static mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			The number of vertices must be greater than zero.
		 @pre			The number of indices must be greater than zero.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		vertices
						A vector containing the vertices.
		 @param[in]		indices
						A vector containing the indices.
		 @param[in]		primitive_topology
						The primitive topology.
		 @throws		Exception
						Failed to setup the vertex buffer of the static mesh.
		 @throws		Exception
						Failed to setup the index buffer of the static mesh.
		 */
		explicit StaticMesh(ID3D11Device *device,
			                std::vector< VertexT > vertices,
			                std::vector< IndexT >  indices,
			                D3D11_PRIMITIVE_TOPOLOGY primitive_topology 
			                = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		/**
		 Constructs a static mesh from the given static mesh.

		 @param[in]		mesh
						A reference to the static mesh to copy.
		 */
		StaticMesh(const StaticMesh &mesh) = delete;

		/**
		 Constructs a static mesh by moving the given static mesh.

		 @param[in]		mesh
						A reference to the static mesh to move.
		 */
		StaticMesh(StaticMesh &&mesh) noexcept;

		/**
		 Destructs this static mesh.
		 */
		virtual ~StaticMesh();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given static mesh to this static mesh.

		 @param[in]		mesh
						A reference to the static mesh to copy.
		 @return		A reference to the copy of the given static mesh (i.e. 
						this static mesh).
		 */
		StaticMesh &operator=(const StaticMesh &mesh) = delete;

		/**
		 Moves the given static mesh to this static mesh.

		 @param[in]		mesh
						A reference to the static mesh to move.
		 @return		A reference to the moved static mesh (i.e. this static 
						mesh).
		 */
		StaticMesh &operator=(StaticMesh &&mesh) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up the vertex buffer of this static mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @throws		Exception
						Failed to setup the vertex buffer of this static mesh.
		 */
		void SetupVertexBuffer(ID3D11Device *device);

		/**
		 Sets up the index buffer of this static mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @throws		Exception
						Failed to setup the index buffer of this static mesh.
		 */
		void SetupIndexBuffer(ID3D11Device *device);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 The vector containing the vertices of this static mesh.
		 */
		std::vector< VertexT > m_vertices;

		/**
		 The vector containing the indices of this static mesh.
		 */
		std::vector< IndexT > m_indices;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.tpp"

#pragma endregion