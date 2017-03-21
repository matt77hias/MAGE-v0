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
		SharedPtr< ModelDescriptor > resource = m_model_descriptor_resource_manager->GetResource(fname);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< ModelDescriptor >(new ModelDescriptor(device, fname, desc));
			// Store the new resource.
			m_model_descriptor_resource_manager->AddResource(resource);
		}
		return resource;
	}
}