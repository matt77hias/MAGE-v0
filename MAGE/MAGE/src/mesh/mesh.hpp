#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "resource\resource.hpp"
#include "math\vertex.hpp"
#include "collection\collection.hpp"

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
	class Mesh : Resource {

	public:

		/**
		 Constructs a mesh.

		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		name
						A reference to the name of the mesh.
		 @param[in]		path
						A reference to the path of the mesh.
		 @param[in]		invert_handedness
						Flag indicating whether the handness of the 
						coordinate system of the mesh should be inverted.
		 @param[in]		clockwise_order
						Flag indicating whether the vertices of triangles
						should be in clockwise order.
		 */
		Mesh(ComPtr< ID3D11Device2 > device, const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH,
			bool invert_handedness = false, bool clockwise_order = true);

		/**
		 Destructs this mesh.
		 */
		virtual ~Mesh() = default;

		void Update(ComPtr< ID3D11DeviceContext2 > device_context) const;

		/**
		 Returns the number of indices of this mesh.

		 @return		The number of indices of this mesh.
		 */
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}

	protected:

		HRESULT InitializeBuffers(ComPtr< ID3D11Device2 > device, bool invert_handedness, bool clockwise_order);
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