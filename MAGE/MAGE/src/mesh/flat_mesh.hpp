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
	 A class of flat meshes.
	 */
	class FlatMesh : Mesh {

	public:

		/**
		 Constructs a flat mesh.

		 @param[in]		device
						A pointer to an D3D11 device.
		 @param[in]		name
						A reference to the name of the mesh.
		 @param[in]		path
						A reference to the path of the mesh.
		 */
		FlatMesh(ComPtr< ID3D11Device2 > device, const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);

		/**
		 Destructs this flat mesh.
		 */
		virtual ~FlatMesh() {}

		size_t GetNbVertices() const {
			return m_nb_vertices;
		}

		virtual HRESULT BindBuffers(ComPtr< ID3D11DeviceContext2 > device_context) const override;

		virtual HRESULT Draw(ComPtr< ID3D11DeviceContext2 > device_context) const override;

	protected:

		HRESULT InitializeBuffers(ComPtr< ID3D11Device2 > device);

		HRESULT SetupVertexBuffer(ComPtr< ID3D11Device2 > device, const Vertex *vertices, size_t nb_vertices);

		size_t m_nb_vertices;

		ComPtr< ID3D11Buffer > m_vertex_buffer;

	private:

		/**
		 Constructs a flat mesh from the given flat mesh.

		 @param[in]		flat_mesh
						A reference to the flat mesh.
		 */
		FlatMesh(const FlatMesh &flat_mesh) = delete;

		/**
		 Copies the given flat mesh to this flat mesh.

		 @param[in]		flat_mesh
						A reference to the flat mesh to copy from.
		 @return		A reference to the copy of the given flat mesh
						(i.e. this flat mesh).
		 */
		FlatMesh &operator=(const FlatMesh &flat_mesh) = delete;
	};
}