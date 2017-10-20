//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine.hpp"
#include "logging\error.hpp"

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

		return Engine::Get()->GetResourceManager();
	}

	ResourceManager::ResourceManager()
		: m_model_descriptor_resource_pool(
			MakeUnique< ResourcePool< wstring, const ModelDescriptor > >()),
		m_vs_resource_pool(
			MakeUnique< PersistentResourcePool< wstring, const VertexShader > >()),
		m_hs_resource_pool(
			MakeUnique< PersistentResourcePool< wstring, const HullShader > >()),
		m_ds_resource_pool(
			MakeUnique< PersistentResourcePool< wstring, const DomainShader > >()),
		m_gs_resource_pool(
			MakeUnique< PersistentResourcePool< wstring, const GeometryShader > >()),
		m_ps_resource_pool(
			MakeUnique< PersistentResourcePool< wstring, const PixelShader > >()),
		m_cs_resource_pool(
			MakeUnique< PersistentResourcePool< wstring, const ComputeShader > >()),
		m_sprite_font_resource_pool(
			MakeUnique< ResourcePool< wstring, SpriteFont > >()),
		m_texture_resource_pool(
			MakeUnique< ResourcePool< wstring, const Texture > >()),
		m_variable_script_resource_pool(
			MakeUnique< ResourcePool< wstring, VariableScript > >()) {}

	ResourceManager::ResourceManager(
		ResourceManager &&resource_factory) = default;

	ResourceManager::~ResourceManager() = default;

	//---------------------------------------------------------------------
	// ResourceManager: HasResource
	//---------------------------------------------------------------------

	bool ResourceManager::HasModelDescriptor(const wstring &guid) noexcept {
		return m_model_descriptor_resource_pool->HasResource(guid);
	}
	
	bool ResourceManager::HasVS(const wstring &guid) noexcept {
		return m_vs_resource_pool->HasResource(guid);
	}

	bool ResourceManager::HasHS(const wstring &guid) noexcept {
		return m_hs_resource_pool->HasResource(guid);
	}

	bool ResourceManager::HasDS(const wstring &guid) noexcept {
		return m_ds_resource_pool->HasResource(guid);
	}

	bool ResourceManager::HasGS(const wstring &guid) noexcept {
		return m_gs_resource_pool->HasResource(guid);
	}

	bool ResourceManager::HasPS(const wstring &guid) noexcept {
		return m_ps_resource_pool->HasResource(guid);
	}

	bool ResourceManager::HasCS(const wstring &guid) noexcept {
		return m_cs_resource_pool->HasResource(guid);
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

	SharedPtr< const ModelDescriptor > ResourceManager::GetModelDescriptor(
		const wstring &guid) noexcept {
		
		return m_model_descriptor_resource_pool->GetResource(guid);
	}
	
	SharedPtr< const VertexShader > ResourceManager::GetVS(
		const wstring &guid) noexcept {
		
		return m_vs_resource_pool->GetResource(guid);
	}

	SharedPtr< const HullShader > ResourceManager::GetHS(
		const wstring &guid) noexcept {
		
		return m_hs_resource_pool->GetResource(guid);
	}
	
	SharedPtr< const DomainShader > ResourceManager::GetDS(
		const wstring &guid) noexcept {
		
		return m_ds_resource_pool->GetResource(guid);
	}

	SharedPtr< const GeometryShader > ResourceManager::GetGS(
		const wstring &guid) noexcept {
		
		return m_gs_resource_pool->GetResource(guid);
	}

	SharedPtr< const PixelShader > ResourceManager::GetPS(
		const wstring &guid) noexcept {
		
		return m_ps_resource_pool->GetResource(guid);
	}

	SharedPtr< const ComputeShader > ResourceManager::GetCS(
		const wstring &guid) noexcept {
		
		return m_cs_resource_pool->GetResource(guid);
	}
	
	SharedPtr< SpriteFont > ResourceManager::GetSpriteFont(
		const wstring &guid) noexcept {
		
		return m_sprite_font_resource_pool->GetResource(guid);
	}
	
	SharedPtr< const Texture > ResourceManager::GetTexture(
		const wstring &guid) noexcept {
		
		return m_texture_resource_pool->GetResource(guid);
	}
	
	SharedPtr< VariableScript > ResourceManager::GetVariableScript(
		const wstring &guid) noexcept {
		
		return m_variable_script_resource_pool->GetResource(guid);
	}
}
