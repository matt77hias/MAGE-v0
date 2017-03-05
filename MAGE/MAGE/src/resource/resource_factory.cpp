//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "shader\lambertian_shader.hpp"
#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------
	
	template < typename VertexT >
	SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc) {
		const RenderingDevice &device = g_engine->GetRenderer().GetDevice();
		ResourceFactory &factory = g_engine->GetResourceFactory();
		return factory.CreateModelDescriptor(fname, device, desc);
	}

	CombinedShader CreateLambertianShader() {
		const RenderingDevice &device = g_engine->GetRenderer().GetDevice();
		ResourceFactory &factory = g_engine->GetResourceFactory();
		SharedPtr< VertexShader > vs = factory.CreateLambertianVertexShader(device);
		SharedPtr< PixelShader > ps = factory.CreateLambertianPixelShader(device);
		return CombinedShader(vs, ps);
	}

	SharedPtr< Texture > CreateTexture(const wstring &fname) {
		const RenderingDevice &device = g_engine->GetRenderer().GetDevice();
		ResourceFactory &factory = g_engine->GetResourceFactory();
		return factory.CreateTexture(device, fname);
	}

	SharedPtr< VariableScript > CreateVariableScript(const wstring &fname) {
		ResourceFactory &factory = g_engine->GetResourceFactory();
		return factory.CreateVariableScript(fname);
	}

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------
	
	ResourceFactory::ResourceFactory()
		: m_model_descriptor_resource_manager(new ResourceManager< ModelDescriptor >()),
		m_vertex_shader_resource_manager(new ResourceManager< VertexShader >()), 
		m_pixel_shader_resource_manager(new ResourceManager< PixelShader >()), 
		m_texture_resource_manager(new ResourceManager< Texture >()), 
		m_variable_script_resource_manager(new ResourceManager< VariableScript >()) {}

	template < typename VertexT >
	SharedPtr< ModelDescriptor > ResourceFactory::CreateModelDescriptor(const wstring &fname, const RenderingDevice &device, const MeshDescriptor< VertexT > &desc) {
		SharedPtr< ModelDescriptor > resource = m_model_descriptor_resource_manager->GetResource(fname);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< ModelDescriptor >(new ModelDescriptor(device, fname, desc));
			// Store the new resource.
			m_model_descriptor_resource_manager->AddResource(resource);
		}
		return resource;
	}

	SharedPtr< VertexShader > ResourceFactory::CreateLambertianVertexShader(const RenderingDevice &device) {
		SharedPtr< VertexShader > resource = m_vertex_shader_resource_manager->GetResource(MAGE_FNAME_LAMBERTIAN_PS);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< VertexShader >(new LambertianVertexShader(device));
			// Store the new resource.
			m_vertex_shader_resource_manager->AddResource(resource);
		}
		return resource;
	}
	
	SharedPtr< PixelShader > ResourceFactory::CreateLambertianPixelShader(const RenderingDevice &device) {
		SharedPtr< PixelShader > resource = m_pixel_shader_resource_manager->GetResource(MAGE_FNAME_LAMBERTIAN_PS);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< PixelShader >(new LambertianPixelShader(device));
			// Store the new resource.
			m_pixel_shader_resource_manager->AddResource(resource);
		}
		return resource;
	}
	
	SharedPtr< Texture > ResourceFactory::CreateTexture(const RenderingDevice &device, const wstring &fname) {
		SharedPtr< Texture > resource = m_texture_resource_manager->GetResource(fname);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< Texture >(new Texture(device, fname));
			// Store the new resource.
			m_texture_resource_manager->AddResource(resource);
		}
		return resource;
	}
	
	SharedPtr< VariableScript > ResourceFactory::CreateVariableScript(const wstring &fname) {
		SharedPtr< VariableScript > resource = m_variable_script_resource_manager->GetResource(fname);
		if (!resource) {
			// Create a new resource.
			resource = SharedPtr< VariableScript >(new VariableScript(fname));
			// Store the new resource.
			m_variable_script_resource_manager->AddResource(resource);
		}
		return resource;
	}
}
