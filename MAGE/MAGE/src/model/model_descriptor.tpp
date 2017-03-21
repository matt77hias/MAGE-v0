#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	 template < typename VertexT >
	 ModelDescriptor::ModelDescriptor(ID3D11Device2 &device, const wstring &fname, const MeshDescriptor< VertexT > &desc)
		 : FileResource(fname) {
		 
		 ModelOutput< VertexT > buffer;
		 const HRESULT result_load = LoadModelFromFile(fname, buffer, desc);
		 if (FAILED(result_load)) {
			 Error("Model loading failed: %08X.", result_load);
			 return;
		 }

		 m_mesh = SharedPtr< Mesh >(new Mesh(device, buffer.vertex_buffer, buffer.index_buffer));
		 m_materials = buffer.material_buffer;
		 m_model_parts = buffer.model_parts;
	 }

	 // Forward declarations
	 class ResourceFactory;
	 ID3D11Device2 &GetModelRenderingDevice();
	 ResourceFactory &GetModelResourceFactory();

	 template < typename VertexT >
	 SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc) {
		 ID3D11Device2 &device = GetModelRenderingDevice();
		 ResourceFactory &factory = GetModelResourceFactory();
		 return factory.CreateModelDescriptor(fname, device, desc);
	 }
}