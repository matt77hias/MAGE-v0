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
		m_font_resource_pool(std::make_unique< ResourcePool< wstring, SpriteFont > >()),
		m_texture_resource_pool(std::make_unique< ResourcePool< wstring, Texture > >()),
		m_variable_script_resource_pool(std::make_unique< ResourcePool< wstring, VariableScript > >()) {}

	ResourceManager::ResourceManager(ResourceManager &&resource_factory) = default;

	ResourceManager::~ResourceManager() {
		m_model_descriptor_resource_pool->RemoveAllResources();
		m_vertex_shader_resource_pool->RemoveAllResources();
		m_pixel_shader_resource_pool->RemoveAllResources();
		m_font_resource_pool->RemoveAllResources();
		m_texture_resource_pool->RemoveAllResources();
		m_variable_script_resource_pool->RemoveAllResources();
	}

	ResourceManager *GetResourceManager() noexcept {
		Assert(g_engine);
		Assert(g_engine->IsLoaded());

		return g_engine->GetResourceManager();
	}
}
