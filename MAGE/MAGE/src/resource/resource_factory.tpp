#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------

	template < typename VertexT >
	SharedPtr< ModelDescriptor > ResourceFactory::CreateModelDescriptor(const wstring &fname, ID3D11Device2 &device, const MeshDescriptor< VertexT > &desc) {
		return m_model_descriptor_resource_pool->template GetResource< ID3D11Device2 &, const wstring &, const MeshDescriptor< VertexT > & >(fname, device, fname, desc);
	}
}