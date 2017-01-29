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
	 A class of meshes.
	 */
	class Mesh : public Resource {

	public:

		/**
		 Constructs a mesh.

		 @param[in]		name
						A reference to the name of the mesh.
		 @param[in]		path
						A reference to the path of the mesh.
		*/
		Mesh(const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH)
			: Resource(name, path) {}

		/**
		 Destructs this mesh.
		 */
		virtual ~Mesh() {}

		virtual HRESULT BindBuffers(ComPtr< ID3D11DeviceContext2 > device_context) const = 0;

		virtual HRESULT Draw(ComPtr< ID3D11DeviceContext2 > device_context) const = 0;

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