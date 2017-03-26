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
		ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context, 
		const wstring &fname, const MeshDescriptor< VertexT > &desc) {
		return m_model_descriptor_resource_pool->template 
			GetResource< ComPtr< ID3D11Device2 > &, ComPtr< ID3D11DeviceContext2 > &, const wstring &, const MeshDescriptor< VertexT > & >(fname, device, device_context, fname, desc);
	}
}