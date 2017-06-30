#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceManager
	//-------------------------------------------------------------------------

	template< typename... ConstructorArgsT >
	inline SharedPtr< ModelDescriptor > ResourceManager::CreateModelDescriptor(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_model_descriptor_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceManager::CreateBasicVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetOrCreateDerivedResource< BasicVertexShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceManager::CreateBasicPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetOrCreateDerivedResource< BasicPixelShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceManager::CreateTSNMVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetOrCreateDerivedResource< TSNMVertexShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceManager::CreateTSNMPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetOrCreateDerivedResource< TSNMPixelShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceManager::CreateSpriteVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetOrCreateDerivedResource< SpriteVertexShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceManager::CreateSpritePixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetOrCreateDerivedResource< SpritePixelShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< SpriteFont > ResourceManager::CreateSpriteFont(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_font_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< Texture > ResourceManager::CreateTexture(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_texture_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VariableScript > ResourceManager::CreateVariableScript(
		const wstring &guid, ConstructorArgsT&&... args) {
		
		return m_variable_script_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	//-------------------------------------------------------------------------
	// ResourceManager Indirect Methods
	//-------------------------------------------------------------------------

	template< typename... ConstructorArgsT >
	inline SharedPtr< ModelDescriptor > CreateModelDescriptor(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateModelDescriptor< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > CreateBasicVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateBasicVertexShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > CreateBasicPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateBasicPixelShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > CreateTSNMVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateTSNMVertexShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > CreateTSNMPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateTSNMPixelShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > CreateSpriteVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateSpriteVertexShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > CreateSpritePixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateSpritePixelShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< SpriteFont > CreateSpriteFont(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateSpriteFont< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< Texture > CreateTexture(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateTexture< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VariableScript > CreateVariableScript(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			CreateVariableScript< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}
}