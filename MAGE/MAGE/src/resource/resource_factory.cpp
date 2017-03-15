//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"
#include "shader\lambertian_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------
	
	ResourceFactory::ResourceFactory()
		: m_model_descriptor_resource_manager(new ResourceManager< ModelDescriptor >()),
		m_vertex_shader_resource_manager(new ResourceManager< VertexShader >()), 
		m_pixel_shader_resource_manager(new ResourceManager< PixelShader >()), 
		m_texture_resource_manager(new ResourceManager< Texture >()), 
		m_variable_script_resource_manager(new ResourceManager< VariableScript >()) {}

	SharedPtr< VertexShader > ResourceFactory::CreateLambertianVertexShader(ComPtr< ID3D11Device2 > device) {
		SharedPtr< VertexShader > resource = m_vertex_shader_resource_manager->GetResource(MAGE_GUID_LAMBERTIAN_VS);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< VertexShader >(new LambertianVertexShader(device));
			// Store the new resource.
			m_vertex_shader_resource_manager->AddResource(resource);
		}
		return resource;
	}
	
	SharedPtr< PixelShader > ResourceFactory::CreateLambertianPixelShader(ComPtr< ID3D11Device2 > device) {
		SharedPtr< PixelShader > resource = m_pixel_shader_resource_manager->GetResource(MAGE_GUID_LAMBERTIAN_PS);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< PixelShader >(new LambertianPixelShader(device));
			// Store the new resource.
			m_pixel_shader_resource_manager->AddResource(resource);
		}
		return resource;
	}
	
	SharedPtr< Texture > ResourceFactory::CreateTexture(ComPtr< ID3D11Device2 > device, const wstring &fname) {
		SharedPtr< Texture > resource = m_texture_resource_manager->GetResource(fname);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< Texture >(new Texture(device, fname));
			// Store the new resource.
			m_texture_resource_manager->AddResource(resource);
		}
		return resource;
	}
	
	SharedPtr< VariableScript > ResourceFactory::CreateVariableScript(const wstring &fname, bool import) {
		SharedPtr< VariableScript > resource = m_variable_script_resource_manager->GetResource(fname);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< VariableScript >(new VariableScript(fname, import));
			// Store the new resource.
			m_variable_script_resource_manager->AddResource(resource);
		}
		return resource;
	}

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------

	ComPtr< ID3D11Device2 > GetRenderingDevice() {
		Assert(g_engine);
		return g_engine->GetRenderer().GetDevice();
	}

	ResourceFactory &GetResourceFactory() {
		Assert(g_engine);
		return g_engine->GetResourceFactory();
	}
}
