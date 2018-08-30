#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\mesh\mesh.hpp"
#include "renderer\buffer\buffer_lock.hpp"

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
namespace mage::rendering {

	/**
	 A class of primitive batch meshes.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 */
	template< typename VertexT, typename IndexT >
	class PrimitiveBatchMesh : public Mesh {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a primitive batch mesh.

		 @param[in]		device
						A reference to the device.
		 @param[in]		nb_vertices
						The number of vertices.
		 @param[in]		indices
						A reference to the vector containing the indices.
		 @param[in]		primitive_topology
						The primitive topology.
		 @throws		Exception
						Failed to setup the vertex buffer of the primitive batch 
						mesh.
		 @throws		Exception
						Failed to setup the index buffer of the primitive batch 
						mesh.
		 */
		explicit PrimitiveBatchMesh(ID3D11Device& device, 
			                        size_t nb_vertices,
			                        const std::vector< IndexT >& indices,
			                        D3D11_PRIMITIVE_TOPOLOGY primitive_topology 
			                        = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		/**
		 Constructs a primitive batch mesh from the given primitive batch mesh.

		 @param[in]		mesh
						A reference to the primitive batch mesh to copy.
		 */
		PrimitiveBatchMesh(const PrimitiveBatchMesh& mesh) = delete;

		/**
		 Constructs a primitive batch mesh by moving the given primitive batch 
		 mesh.

		 @param[in]		mesh
						A reference to the primitive batch mesh to move.
		 */
		PrimitiveBatchMesh(PrimitiveBatchMesh&& mesh) noexcept;

		/**
		 Destructs this primitive batch mesh.
		 */
		virtual ~PrimitiveBatchMesh();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given primitive batch mesh to this primitive batch mesh.

		 @param[in]		mesh
						A reference to the primitive batch mesh to copy.
		 @return		A reference to the copy of the given primitive batch 
						mesh (i.e. this primitive batch mesh).
		 */
		PrimitiveBatchMesh& operator=(const PrimitiveBatchMesh& mesh) = delete;

		/**
		 Moves the given primitive batch mesh to this primitive batch mesh.

		 @param[in]		mesh
						A reference to the primitive batch mesh to move.
		 @return		A reference to the moved primitive batch mesh (i.e. 
						this primitive batch mesh).
		 */
		PrimitiveBatchMesh& operator=(PrimitiveBatchMesh&& mesh) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Locks the vertex buffer of this primitive batch mesh.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		map_type
						The map type specifying the CPU's read and write 
						permissions for the vertex buffer of this primitive 
						batch mesh.
		 @param[out]	mapped_buffer
						A reference to map the vertex buffer of this primitive 
						batch mesh to.
		 @throws		Exception
						Failed to map the vertex buffer of this primitive batch 
						mesh.
		 */
		const BufferLock Lock(ID3D11DeviceContext& device_context, 
							  D3D11_MAP map_type, 
							  D3D11_MAPPED_SUBRESOURCE& mapped_buffer) {

			return BufferLock(device_context, *m_vertex_buffer.Get(), 
				              map_type, mapped_buffer);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up the vertex buffer of this primitive batch mesh.

		 @param[in]		device
						A reference to the device.
		 @param[in]		nb_vertices
						The number of vertices.
		 @throws		Exception
						Failed to setup the vertex buffer of this primitive 
						batch mesh.
		 */
		void SetupVertexBuffer(ID3D11Device& device, size_t nb_vertices);

		/**
		 Sets up the index buffer of this primitive batch mesh.

		 @param[in]		device
						A reference to the device.
		 @param[in]		indices
						A reference to the vector containing the indices.
		 @throws		Exception
						Failed to setup the index buffer of this primitive 
						batch mesh.
		 */
		void SetupIndexBuffer(ID3D11Device& device, 
			                  const std::vector< IndexT >& indices);
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\mesh\primitive_batch_mesh.tpp"

#pragma endregion
