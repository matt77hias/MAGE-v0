#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\model\model_output.hpp"
#include "resource\mesh\mesh_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <filesystem>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {
	// Forward declaration.
	class ResourceManager;
}

namespace mage::rendering::loader {

	/**
	 Imports a mesh from the OBJ file associated with the given path.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 @param[in]		path
					A reference to the path.
	 @param[in]		resource_manager
					A reference to the resource manager.
	 @param[in,out]	model_output
					A reference to the model output.
	 @param[in]		mesh_desc
					A reference to the mesh descriptor.
	 @throws		Exception
					Failed to import the mesh from file.
	 */
	template< typename VertexT, typename IndexT >
	void ImportOBJMeshFromFile(const std::filesystem::path& path, 
							   ResourceManager& resource_manager, 
							   ModelOutput< VertexT, IndexT >& model_output, 
							   const MeshDescriptor< VertexT, IndexT >& 
							   mesh_desc = MeshDescriptor< VertexT, IndexT >());
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\obj\obj_loader.tpp"

#pragma endregion