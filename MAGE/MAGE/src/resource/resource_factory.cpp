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
		: m_model_descriptor_resource_pool(new ResourcePool< wstring, ModelDescriptor >()),
		m_vertex_shader_resource_pool(new ResourcePool< wstring, VertexShader >()),
		m_pixel_shader_resource_pool(new ResourcePool< wstring, PixelShader >()),
		m_texture_resource_pool(new ResourcePool< wstring, Texture >()),
		m_variable_script_resource_pool(new ResourcePool< wstring, VariableScript >()) {}

	ResourceFactory::~ResourceFactory() {
		m_model_descriptor_resource_pool->RemoveAllResources();
		m_vertex_shader_resource_pool->RemoveAllResources();
		m_pixel_shader_resource_pool->RemoveAllResources();
		m_texture_resource_pool->RemoveAllResources();
		m_variable_script_resource_pool->RemoveAllResources();
	}

	SharedPtr< VertexShader > ResourceFactory::CreateLambertianVertexShader(
		ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context) {
		return m_vertex_shader_resource_pool->template 
			GetDerivedResource< LambertianVertexShader, ComPtr< ID3D11Device2 > &, ComPtr< ID3D11DeviceContext2 > & >(MAGE_GUID_LAMBERTIAN_VS, device, device_context);
	}
	SharedPtr< PixelShader > ResourceFactory::CreateLambertianPixelShader(
		ComPtr< ID3D11Device2 > device, ComPtr< ID3D11DeviceContext2 > device_context) {
		return m_pixel_shader_resource_pool->template 
			GetDerivedResource< LambertianPixelShader, ComPtr< ID3D11Device2 > &, ComPtr< ID3D11DeviceContext2 > & >(MAGE_GUID_LAMBERTIAN_PS, device, device_context);
	}
	SharedPtr< Texture > ResourceFactory::CreateTexture(
		ComPtr< ID3D11Device2 > device, const wstring &fname) {
		return m_texture_resource_pool->template 
			GetResource< ComPtr< ID3D11Device2 > &, const wstring & >(fname, device, fname);
	}
	SharedPtr< VariableScript > ResourceFactory::CreateVariableScript(const wstring &fname, bool import) {
		return m_variable_script_resource_pool->template 
			GetResource< const wstring &, const bool & >(fname, fname, import);
	}

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------

	ComPtr< ID3D11Device2 > GetRenderingDevice() {
		Assert(g_engine);
		return g_engine->GetRenderer().GetDevice();
	}
	ComPtr< ID3D11DeviceContext2 > GetRenderingDeviceContext() {
		Assert(g_engine);
		return g_engine->GetRenderer().GetDeviceContext();
	}
	ResourceFactory &GetResourceFactory() {
		Assert(g_engine);
		return g_engine->GetResourceFactory();
	}
}
