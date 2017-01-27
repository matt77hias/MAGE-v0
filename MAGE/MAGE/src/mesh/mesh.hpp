#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

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
		Mesh(const string &name, const string &path = "./")
			: Resource(name, path) {}

		/**
		 Destructs this mesh.
		 */
		virtual ~Mesh() {}

		virtual HRESULT BindBuffers(ID3D11DeviceContext2 *device_context) const = 0;

		virtual HRESULT Draw(ID3D11DeviceContext2 *device_context) const = 0;

	private:

		Mesh(const Mesh &mesh) = delete;
		Mesh &operator=(const Mesh &mesh) = delete;
	};
}