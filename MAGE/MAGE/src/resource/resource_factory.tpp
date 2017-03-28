#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------

	template < typename VertexT >
	SharedPtr< ModelDescriptor > ResourceFactory::CreateModelDescriptor(
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const wstring &fname, const MeshDescriptor< VertexT > &desc) {
		return m_model_descriptor_resource_pool->template 
			GetResource< ID3D11Device2 *&, ID3D11DeviceContext2 *&, const wstring &, const MeshDescriptor< VertexT > & >(fname, device, device_context, fname, desc);
	}
}