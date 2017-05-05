//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "shader\compiled_shader_factory.hpp"
#include "shader\basic_shader.hpp"
#include "shader\sprite_shader.hpp"

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
		m_font_resource_pool(new ResourcePool< wstring, SpriteFont >()),
		m_texture_resource_pool(new ResourcePool< wstring, Texture >()),
		m_variable_script_resource_pool(new ResourcePool< wstring, VariableScript >()) {}

	ResourceFactory::ResourceFactory(ResourceFactory &&resource_factory) = default;

	ResourceFactory::~ResourceFactory() {
		m_model_descriptor_resource_pool->RemoveAllResources();
		m_vertex_shader_resource_pool->RemoveAllResources();
		m_pixel_shader_resource_pool->RemoveAllResources();
		m_font_resource_pool->RemoveAllResources();
		m_texture_resource_pool->RemoveAllResources();
		m_variable_script_resource_pool->RemoveAllResources();
	}

	SharedPtr< VertexShader > ResourceFactory::CreateBasicVertexShader(
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledVertexShader &compiled_vertex_shader) {
		return m_vertex_shader_resource_pool->template 
			GetDerivedResource< BasicVertexShader, ID3D11Device2 *&, ID3D11DeviceContext2 *&, const CompiledVertexShader & >
								(compiled_vertex_shader.m_name, device, device_context, compiled_vertex_shader);
	}
	
	SharedPtr< PixelShader > ResourceFactory::CreateBasicPixelShader(
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
		const CompiledPixelShader &compiled_pixel_shader) {
		return m_pixel_shader_resource_pool->template 
			GetDerivedResource< BasicPixelShader, ID3D11Device2 *&, ID3D11DeviceContext2 *&, const CompiledPixelShader & >
								(compiled_pixel_shader.m_name, device, device_context, compiled_pixel_shader);
	}
	
	SharedPtr< VertexShader > ResourceFactory::CreateSpriteVertexShader(
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context) {
		return m_vertex_shader_resource_pool->template
			GetDerivedResource< SpriteVertexShader, ID3D11Device2 *&, ID3D11DeviceContext2 *& >
								(MAGE_GUID_SPRITE_VS, device, device_context);
	}
	
	SharedPtr< PixelShader > ResourceFactory::CreateSpritePixelShader(
		ID3D11Device2 *device, ID3D11DeviceContext2 *device_context) {
		return m_pixel_shader_resource_pool->template
			GetDerivedResource< SpritePixelShader, ID3D11Device2 *&, ID3D11DeviceContext2 *& >
								(MAGE_GUID_SPRITE_PS, device, device_context);
	}
	
	SharedPtr< SpriteFont > ResourceFactory::CreateFont(
		ID3D11Device2 *device, const wstring &fname, const SpriteFontDescriptor &desc) {
		return m_font_resource_pool->template
			GetResource< ID3D11Device2 *&, const wstring &, const SpriteFontDescriptor & >(fname, device, fname, desc);
	}
	
	SharedPtr< Texture > ResourceFactory::CreateTexture(
		ID3D11Device2 *device, const wstring &fname) {
		return m_texture_resource_pool->template 
			GetResource< ID3D11Device2 *&, const wstring & >(fname, device, fname);
	}
	
	SharedPtr< VariableScript > ResourceFactory::CreateVariableScript(const wstring &fname, bool import) {
		return m_variable_script_resource_pool->template 
			GetResource< const wstring &, const bool & >(fname, fname, import);
	}

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------

	ID3D11Device2 *GetRenderingDevice() {
		Assert(g_engine);
		Assert(g_engine->GetRenderer());
		return g_engine->GetRenderer()->GetDevice();
	}
	
	ID3D11DeviceContext2 *GetRenderingDeviceContext() {
		Assert(g_engine);
		Assert(g_engine->GetRenderer());
		return g_engine->GetRenderer()->GetDeviceContext();
	}
	
	ResourceFactory *GetResourceFactory() {
		Assert(g_engine);
		return g_engine->GetResourceFactory();
	}
}
