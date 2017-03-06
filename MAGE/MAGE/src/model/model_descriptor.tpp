#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	 template < typename VertexT >
	 ModelDescriptor::ModelDescriptor(const RenderingDevice &device, const wstring &fname, const MeshDescriptor< VertexT > &desc) 
		 : Resource(fname) {
		 
		 ModelOutput< VertexT > buffer;
		 const HRESULT result_load = LoadModelFromFile(fname, buffer, desc);
		 if (FAILED(result_load)) {
			 Error("Model loading failed: %ld.", result_load);
			 return;
		 }

		 m_mesh = SharedPtr< Mesh >(new Mesh(device, buffer.vertex_buffer, buffer.index_buffer));
		 m_materials = buffer.material_buffer;
		 m_model_parts = buffer.model_parts;
	 }
}