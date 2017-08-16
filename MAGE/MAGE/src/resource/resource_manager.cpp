//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceManager
	//-------------------------------------------------------------------------
	
	ResourceManager *ResourceManager::Get() noexcept {
		Assert(Engine::Get());
		Assert(Engine::Get()->GetResourceManager());

		return Engine::Get()->GetResourceManager();
	}

	ResourceManager::ResourceManager()
		: m_model_descriptor_resource_pool(MakeUnique< ResourcePool< wstring, ModelDescriptor > >()),
		m_vertex_shader_resource_pool(MakeUnique< ResourcePool< wstring, VertexShader > >()),
		m_pixel_shader_resource_pool(MakeUnique< ResourcePool< wstring, PixelShader > >()),
		m_sprite_font_resource_pool(MakeUnique< ResourcePool< wstring, SpriteFont > >()),
		m_texture_resource_pool(MakeUnique< ResourcePool< wstring, Texture > >()),
		m_variable_script_resource_pool(MakeUnique< ResourcePool< wstring, VariableScript > >()) {}

	ResourceManager::ResourceManager(ResourceManager &&resource_factory) = default;

	ResourceManager::~ResourceManager() {
		m_model_descriptor_resource_pool->RemoveAllResources();
		m_vertex_shader_resource_pool->RemoveAllResources();
		m_pixel_shader_resource_pool->RemoveAllResources();
		m_sprite_font_resource_pool->RemoveAllResources();
		m_texture_resource_pool->RemoveAllResources();
		m_variable_script_resource_pool->RemoveAllResources();
	}

	//---------------------------------------------------------------------
	// ResourceManager: HasResource
	//---------------------------------------------------------------------

	bool ResourceManager::HasModelDescriptor(const wstring &guid) noexcept {
		return m_model_descriptor_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasBasicVertexShader(const wstring &guid) noexcept {
		return m_vertex_shader_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasBasicPixelShader(const wstring &guid) noexcept {
		return m_pixel_shader_resource_pool->HasResource(guid);
	}

	bool ResourceManager::HasTSNMVertexShader(const wstring &guid) noexcept {
		return m_vertex_shader_resource_pool->HasResource(guid);
	}

	bool ResourceManager::HasTSNMPixelShader(const wstring &guid) noexcept {
		return m_pixel_shader_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasSpriteVertexShader(const wstring &guid) noexcept {
		return m_vertex_shader_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasSpritePixelShader(const wstring &guid) noexcept {
		return m_pixel_shader_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasSpriteFont(const wstring &guid) noexcept {
		return m_sprite_font_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasTexture(const wstring &guid) noexcept {
		return m_texture_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasVariableScript(const wstring &guid) noexcept {
		return m_variable_script_resource_pool->HasResource(guid);
	}
		
	//---------------------------------------------------------------------
	// ResourceManager: GetResource
	//---------------------------------------------------------------------

	SharedPtr< ModelDescriptor > ResourceManager::GetModelDescriptor(const wstring &guid) noexcept {
		return m_model_descriptor_resource_pool->GetResource(guid);
	}
	
	SharedPtr< VertexShader > ResourceManager::GetBasicVertexShader(const wstring &guid) noexcept {
		return m_vertex_shader_resource_pool->GetResource(guid);
	}
	
	SharedPtr< PixelShader > ResourceManager::GetBasicPixelShader(const wstring &guid) noexcept {
		return m_pixel_shader_resource_pool->GetResource(guid);
	}

	SharedPtr< VertexShader > ResourceManager::GetTSNMVertexShader(const wstring &guid) noexcept {
		return m_vertex_shader_resource_pool->GetResource(guid);
	}

	SharedPtr< PixelShader > ResourceManager::GetTSNMPixelShader(const wstring &guid) noexcept {
		return m_pixel_shader_resource_pool->GetResource(guid);
	}
	
	SharedPtr< VertexShader > ResourceManager::GetSpriteVertexShader(const wstring &guid) noexcept {
		return m_vertex_shader_resource_pool->GetResource(guid);
	}
	
	SharedPtr< PixelShader > ResourceManager::GetSpritePixelShader(const wstring &guid) noexcept {
		return m_pixel_shader_resource_pool->GetResource(guid);
	}
	
	SharedPtr< SpriteFont > ResourceManager::GetSpriteFont(const wstring &guid) noexcept {
		return m_sprite_font_resource_pool->GetResource(guid);
	}
	
	SharedPtr< Texture > ResourceManager::GetTexture(const wstring &guid) noexcept {
		return m_texture_resource_pool->GetResource(guid);
	}
	
	SharedPtr< VariableScript > ResourceManager::GetVariableScript(const wstring &guid) noexcept {
		return m_variable_script_resource_pool->GetResource(guid);
	}
}
