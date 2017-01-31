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
	 */
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
		 */
		Mesh(ComPtr< ID3D11Device2 > device, const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);

		/**
		 Destructs this mesh.
		 */
		virtual ~Mesh() {}

		size_t GetNbVertices() const {
			return m_nb_vertices;
		}

		HRESULT BindBuffers(ComPtr< ID3D11DeviceContext2 > device_context) const;
		HRESULT Draw(ComPtr< ID3D11DeviceContext2 > device_context) const;

	protected:

		HRESULT InitializeBuffers(ComPtr< ID3D11Device2 > device);
		HRESULT SetupVertexBuffer(ComPtr< ID3D11Device2 > device, const Vertex *vertices, size_t nb_vertices);
		HRESULT SetupIndexBuffer(ComPtr< ID3D11Device2 > device, const uint32_t *indices, size_t nb_indices);

		size_t m_nb_vertices;

		ComPtr< ID3D11Buffer > m_vertex_buffer;
		ComPtr< ID3D11Buffer > m_index_buffer;

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
	};
}