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
	
	ResourceManager::ResourceManager()
		: m_model_descriptor_resource_pool(std::make_unique< ResourcePool< wstring, ModelDescriptor > >()),
		m_vertex_shader_resource_pool(std::make_unique< ResourcePool< wstring, VertexShader > >()),
		m_pixel_shader_resource_pool(std::make_unique< ResourcePool< wstring, PixelShader > >()),
		m_sprite_font_resource_pool(std::make_unique< ResourcePool< wstring, SpriteFont > >()),
		m_texture_resource_pool(std::make_unique< ResourcePool< wstring, Texture > >()),
		m_variable_script_resource_pool(std::make_unique< ResourcePool< wstring, VariableScript > >()) {}

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
	// ResourceManager: GetModelDescriptor
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
	// ResourceManager: GetModelDescriptor
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
	
	//---------------------------------------------------------------------
	// Indirect HasResource Methods
	//---------------------------------------------------------------------

	bool HasModelDescriptor(const wstring &guid) noexcept {
		return GetResourceManager()->HasModelDescriptor(guid);
	}
	
	bool HasBasicVertexShader(const wstring &guid) noexcept {
		return GetResourceManager()->HasBasicVertexShader(guid);
	}
	
	bool HasBasicPixelShader(const wstring &guid) noexcept {
		return GetResourceManager()->HasBasicPixelShader(guid);
	}

	bool HasTSNMVertexShader(const wstring &guid) noexcept {
		return GetResourceManager()->HasTSNMVertexShader(guid);
	}

	bool HasTSNMPixelShader(const wstring &guid) noexcept {
		return GetResourceManager()->HasTSNMPixelShader(guid);
	}
	
	bool HasSpriteVertexShader(const wstring &guid) noexcept {
		return GetResourceManager()->HasSpriteVertexShader(guid);
	}
	
	bool HasSpritePixelShader(const wstring &guid) noexcept {
		return GetResourceManager()->HasSpritePixelShader(guid);
	}
	
	bool HasSpriteFont(const wstring &guid) noexcept {
		return GetResourceManager()->HasSpriteFont(guid);
	}
	
	bool HasTexture(const wstring &guid) noexcept {
		return GetResourceManager()->HasTexture(guid);
	}
	
	bool HasVariableScript(const wstring &guid) noexcept {
		return GetResourceManager()->HasVariableScript(guid);
	}
	
	//---------------------------------------------------------------------
	// Indirect GetResource Methods
	//---------------------------------------------------------------------

	SharedPtr< ModelDescriptor > GetModelDescriptor(const wstring &guid) noexcept {
		return GetResourceManager()->GetModelDescriptor(guid);
	}
	
	SharedPtr< VertexShader > GetBasicVertexShader(const wstring &guid) noexcept {
		return GetResourceManager()->GetBasicVertexShader(guid);
	}
	
	SharedPtr< PixelShader > GetBasicPixelShader(const wstring &guid) noexcept {
		return GetResourceManager()->GetBasicPixelShader(guid);
	}

	SharedPtr< VertexShader > GetTSNMVertexShader(const wstring &guid) noexcept {
		return GetResourceManager()->GetTSNMVertexShader(guid);
	}

	SharedPtr< PixelShader > GetTSNMPixelShader(const wstring &guid) noexcept {
		return GetResourceManager()->GetTSNMPixelShader(guid);
	}
	
	SharedPtr< VertexShader > GetSpriteVertexShader(const wstring &guid) noexcept {
		return GetResourceManager()->GetSpriteVertexShader(guid);
	}
	
	SharedPtr< PixelShader > GetSpritePixelShader(const wstring &guid) noexcept {
		return GetResourceManager()->GetSpritePixelShader(guid);
	}
	
	SharedPtr< SpriteFont > GetSpriteFont(const wstring &guid) noexcept {
		return GetResourceManager()->GetSpriteFont(guid);
	}
	
	SharedPtr< Texture > GetTexture(const wstring &guid) noexcept {
		return GetResourceManager()->GetTexture(guid);
	}
	
	SharedPtr< VariableScript > GetVariableScript(const wstring &guid) noexcept {
		return GetResourceManager()->GetVariableScript(guid);
	}
	
	//---------------------------------------------------------------------
	// GetResourceManager
	//---------------------------------------------------------------------
	
	ResourceManager *GetResourceManager() noexcept {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());

		return g_engine->GetResourceManager();
	}
}
