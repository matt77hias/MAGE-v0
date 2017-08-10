#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "rendering\rendering.hpp"
#include "core\engine_statistics.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of indexed meshes.
	 */
	class Mesh {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this mesh.
		 */
		virtual ~Mesh();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given mesh to this mesh.

		 @param[in]		mesh
						A reference to the mesh to copy.
		 @return		A reference to the copy of the given mesh
						(i.e. this mesh).
		 */
		Mesh &operator=(const Mesh &mesh) = delete;

		/**
		 Moves the given mesh to this mesh.

		 @param[in]		mesh
						A reference to the mesh to move.
		 @return		A reference to the moved mesh
						(i.e. this mesh).
		 */
		Mesh &operator=(Mesh &&mesh) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the size (in bytes) of the vertices of this mesh.

		 @return		The vertex size (in bytes) of this mesh.
		 */
		size_t GetVertexSize() const noexcept {
			return m_vertex_size;
		}

		/**
		 Returns the number of vertices of this mesh.

		 @return		The number of vertices of this mesh.
		 */
		size_t GetNumberOfVertices() const noexcept {
			return m_nb_vertices;
		}

		/**
		 Returns the number of indices of this mesh.

		 @return		The number of indices of this mesh.
		 */
		size_t GetNumberOfIndices() const noexcept {
			return m_nb_indices;
		}

		/**
		 Returns the index format of this mesh.

		 @return		The index format of this mesh.
		 */
		DXGI_FORMAT GetIndexFormat() const noexcept {
			return m_index_format;
		}

		/**
		 Returns the primitive topology of this mesh.

		 @return		The primitive topology of this mesh.	
		 */
		D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() const noexcept {
			return m_primitive_topology;
		}

		/**
		 Prepares the drawing of this mesh.

		 The vertex buffer, index buffer and primitive topology of this mesh
		 will be bound to the input-assembler stage.
		 */
		void PrepareDrawing() const {
			UINT stride = static_cast< UINT >(m_vertex_size);
			UINT offset = 0;
			m_device_context->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);
			m_device_context->IASetIndexBuffer(m_index_buffer.Get(), m_index_format, 0);
			m_device_context->IASetPrimitiveTopology(m_primitive_topology);
		}

		/**
		 Draws this complete mesh.
		 */
		void Draw() const {
			m_device_context->DrawIndexed(static_cast< UINT >(m_nb_indices), 0, 0);
			
			EngineStatistics::Get()->IncrementNumberOfDrawCalls();
		}
		
		/**
		 Draws a submesh of this mesh.

		 @param[in]		start_index
						The start index.
		 @param[in]		nb_indices
						The number of indices.
		 */
		void Draw(size_t start_index, size_t nb_indices) const {
			m_device_context->DrawIndexed(static_cast< UINT >(nb_indices), static_cast< UINT >(start_index), 0);
			
			EngineStatistics::Get()->IncrementNumberOfDrawCalls();
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a mesh.

		 @pre			The current engine must be loaded.
		 @param[in]		vertex_size
						The vertex size.
		 @param[in]		index_format
						The index format.
		 @param[in]		primitive_topology
						The primitive topology.
		 */
		explicit Mesh(size_t vertex_size, DXGI_FORMAT index_format, 
			D3D11_PRIMITIVE_TOPOLOGY primitive_topology);

		/**
		 Constructs a mesh.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		vertex_size
						The vertex size.
		 @param[in]		index_format
						The index format.
		 @param[in]		primitive_topology
						The primitive topology.
		 */
		explicit Mesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context, 
			size_t vertex_size, DXGI_FORMAT index_format,
			D3D11_PRIMITIVE_TOPOLOGY primitive_topology);

		/**
		 Constructs a mesh from the given mesh.

		 @param[in]		mesh
						A reference to the mesh to copy.
		 */
		Mesh(const Mesh &mesh) = delete;

		/**
		 Constructs a mesh by moving the given mesh.

		 @param[in]		mesh
						A reference to the mesh to move.
		 */
		Mesh(Mesh &&mesh);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets the number of vertices of this mesh to the given number.

		 @param[in]		nb_vertices
						The number of vertices of this mesh.
		 */
		void SetNumberOfVertices(size_t nb_vertices) noexcept {
			m_nb_vertices = nb_vertices;
		}

		/**
		 Sets the number of indices of this mesh to the given number.

		 @param[in]		nb_indices
						The number of indices of this mesh.
		 */
		void SetNumberOfIndices(size_t nb_indices) noexcept {
			m_nb_indices = nb_indices;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this mesh.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this mesh.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex buffer of this mesh.
		 */
		ComPtr< ID3D11Buffer > m_vertex_buffer;

		/**
		 A pointer to the index buffer of this mesh.
		 */
		ComPtr< ID3D11Buffer > m_index_buffer;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The vertex size of this mesh.
		 */
		const size_t m_vertex_size;

		/**
		 The number of vertices of this mesh.
		 */
		size_t m_nb_vertices;

		/**
		 The number of indices of this mesh.
		 */
		size_t m_nb_indices;

		/**
		 The index format of this mesh.
		 */
		const DXGI_FORMAT m_index_format;

		/**
		 The primitive topology of this mesh.
		 */
		const D3D11_PRIMITIVE_TOPOLOGY m_primitive_topology;
	};
}