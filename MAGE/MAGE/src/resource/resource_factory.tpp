#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------

	template< typename... ConstructorArgsT >
	inline SharedPtr< ModelDescriptor > ResourceFactory::CreateModelDescriptor(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_model_descriptor_resource_pool->template
			GetResource< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceFactory::CreateBasicVertexShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetDerivedResource< BasicVertexShader, ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceFactory::CreateBasicPixelShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetDerivedResource< BasicPixelShader, ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceFactory::CreateTSNMVertexShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetDerivedResource< TSNMVertexShader, ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceFactory::CreateTSNMPixelShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetDerivedResource< TSNMPixelShader, ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > ResourceFactory::CreateSpriteVertexShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_vertex_shader_resource_pool->template
			GetDerivedResource< SpriteVertexShader, ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > ResourceFactory::CreateSpritePixelShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_pixel_shader_resource_pool->template
			GetDerivedResource< SpritePixelShader, ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< SpriteFont > ResourceFactory::CreateFont(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_font_resource_pool->template
			GetResource< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< Texture > ResourceFactory::CreateTexture(
		const wstring &key, ConstructorArgsT&&... args) {

		return m_texture_resource_pool->template
			GetResource< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VariableScript > ResourceFactory::CreateVariableScript(
		const wstring &key, ConstructorArgsT&&... args) {
		
		return m_variable_script_resource_pool->template
			GetResource< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	//-------------------------------------------------------------------------
	// Resource Factory Methods
	//-------------------------------------------------------------------------

	template< typename... ConstructorArgsT >
	inline SharedPtr< ModelDescriptor > CreateModelDescriptor(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateModelDescriptor< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > CreateBasicVertexShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateBasicVertexShader< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > CreateBasicPixelShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateBasicPixelShader< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > CreateTSNMVertexShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateTSNMVertexShader< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > CreateTSNMPixelShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateTSNMPixelShader< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VertexShader > CreateSpriteVertexShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateSpriteVertexShader< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< PixelShader > CreateSpritePixelShader(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateSpritePixelShader< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< SpriteFont > CreateFont(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateFont< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< Texture > CreateTexture(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateTexture< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VariableScript > CreateVariableScript(
		const wstring &key, ConstructorArgsT&&... args) {

		return GetResourceFactory()->template
			CreateVariableScript< ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}
}