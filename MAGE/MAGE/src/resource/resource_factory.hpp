#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_manager.hpp"
#include "model\model_descriptor.hpp"
#include "shader\shader.hpp"
#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------
	
	class ResourceFactory {

	public:

		ResourceFactory();
		virtual ~ResourceFactory() = default;

		template < typename VertexT >
		SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, ID3D11Device2 &device, const MeshDescriptor< VertexT > &desc);
		SharedPtr< VertexShader > CreateLambertianVertexShader(ID3D11Device2 &device);
		SharedPtr< PixelShader > CreateLambertianPixelShader(ID3D11Device2 &device);
		SharedPtr< Texture > CreateTexture(ID3D11Device2 &device, const wstring &fname);
		SharedPtr< VariableScript > CreateVariableScript(const wstring &fname, bool import);

	private:

		ResourceFactory(const ResourceFactory &resource_factory) = delete;
		ResourceFactory &operator=(const ResourceFactory &resource_factory) = delete;

		UniquePtr< ResourceManager< ModelDescriptor > > m_model_descriptor_resource_manager;
		UniquePtr< ResourceManager< VertexShader > > m_vertex_shader_resource_manager;
		UniquePtr< ResourceManager< PixelShader > > m_pixel_shader_resource_manager;
		UniquePtr< ResourceManager< Texture > > m_texture_resource_manager;
		UniquePtr< ResourceManager< VariableScript > > m_variable_script_resource_manager;
	};

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------

	ID3D11Device2 &GetRenderingDevice();

	ResourceFactory &GetResourceFactory();
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.tpp"

#pragma endregion