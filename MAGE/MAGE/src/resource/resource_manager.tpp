#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceManager
	//-------------------------------------------------------------------------

	template< typename... ConstructorArgsT >
	inline SharedPtr< ModelDescriptor > ResourceManager::GetOrCreateModelDescriptor(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_model_descriptor_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceManager::GetOrCreateBasicVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetOrCreateDerivedResource< BasicVertexShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceManager::GetOrCreateBasicPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetOrCreateDerivedResource< BasicPixelShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceManager::GetOrCreateTSNMVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetOrCreateDerivedResource< TSNMVertexShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceManager::GetOrCreateTSNMPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetOrCreateDerivedResource< TSNMPixelShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceManager::GetOrCreateSpriteVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetOrCreateDerivedResource< SpriteVertexShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceManager::GetOrCreateSpritePixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetOrCreateDerivedResource< SpritePixelShader, const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< SpriteFont > ResourceManager::GetOrCreateSpriteFont(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_sprite_font_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< Texture > ResourceManager::GetOrCreateTexture(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_texture_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VariableScript > ResourceManager::GetOrCreateVariableScript(
		const wstring &guid, ConstructorArgsT&&... args) {
		
		return m_variable_script_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	//-------------------------------------------------------------------------
	// Indirect GetOrCreateResource Methods
	//-------------------------------------------------------------------------

	template< typename... ConstructorArgsT >
	inline SharedPtr< ModelDescriptor > GetOrCreateModelDescriptor(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateModelDescriptor< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > GetOrCreateBasicVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateBasicVertexShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > GetOrCreateBasicPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateBasicPixelShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > GetOrCreateTSNMVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateTSNMVertexShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > GetOrCreateTSNMPixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateTSNMPixelShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > GetOrCreateSpriteVertexShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateSpriteVertexShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > GetOrCreateSpritePixelShader(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateSpritePixelShader< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< SpriteFont > GetOrCreateSpriteFont(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateSpriteFont< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< Texture > GetOrCreateTexture(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateTexture< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VariableScript > GetOrCreateVariableScript(
		const wstring &guid, ConstructorArgsT&&... args) {

		return GetResourceManager()->template
			GetOrCreateVariableScript< ConstructorArgsT... >(guid, std::forward< ConstructorArgsT >(args)...);
	}
}