#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	 template < typename VertexT >
	 ModelDescriptor::ModelDescriptor(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		 const wstring &fname, const MeshDescriptor< VertexT > &desc)
		 : FileResource(fname), m_mesh(), m_materials(), m_model_parts() {
		 
		 ModelOutput< VertexT > buffer;
		 const HRESULT result_load = ImportModelFromFile(fname, buffer, desc);
		 if (FAILED(result_load)) {
			 Error("Model loading failed: %08X.", result_load);
			 return;
		 }

		 //ExportModelToFile(L"assets/models/model/model.mdl", buffer);

		 m_mesh        = SharedPtr< StaticMesh >(new StaticMesh(device, device_context, buffer.m_vertex_buffer, buffer.m_index_buffer));
		 m_materials   = std::move(buffer.m_material_buffer);
		 m_model_parts = std::move(buffer.m_model_parts);
	 }

	 template< typename ActionT >
	 inline void ModelDescriptor::ForEachMaterial(ActionT action) const {
		 for (vector< Material >::const_iterator it = m_materials.cbegin(); it != m_materials.cend(); ++it) {
			 action(*it);
		 }
	 }

	 template< typename ActionT >
	 inline void ModelDescriptor::ForEachModelPart(ActionT action) const {
		 for (vector< ModelPart >::const_iterator it = m_model_parts.cbegin(); it != m_model_parts.cend(); ++it) {
			 action(*it);
		 }
	 }

	 // Forward declarations
	 class ResourceFactory;
	 ID3D11Device2 *GetModelRenderingDevice();
	 ID3D11DeviceContext2 *GetModelRenderingDeviceContext();
	 ResourceFactory *GetModelResourceFactory();

	 template < typename VertexT >
	 SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc) {
		 ID3D11Device2 *device = GetModelRenderingDevice();
		 ID3D11DeviceContext2 *device_context = GetModelRenderingDeviceContext();
		 ResourceFactory *factory = GetModelResourceFactory();
		 return factory->CreateModelDescriptor(device, device_context, fname, desc);
	 }
}