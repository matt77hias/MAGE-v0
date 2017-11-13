#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceManager
	//-------------------------------------------------------------------------

	template< typename... ConstructorArgsT >
	inline SharedPtr< const ModelDescriptor > ResourceManager::GetOrCreateModelDescriptor(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_model_descriptor_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const VertexShader > ResourceManager::GetOrCreateVS(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_vs_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const HullShader > ResourceManager::GetOrCreateHS(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_hs_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const DomainShader > ResourceManager::GetOrCreateDS(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_ds_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const GeometryShader > ResourceManager::GetOrCreateGS(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_gs_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const PixelShader > ResourceManager::GetOrCreatePS(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_ps_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const ComputeShader > ResourceManager::GetOrCreateCS(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_cs_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const SpriteFont > ResourceManager::GetOrCreateSpriteFont(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_sprite_font_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< const Texture > ResourceManager::GetOrCreateTexture(
		const wstring &guid, ConstructorArgsT&&... args) {

		return m_texture_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename... ConstructorArgsT >
	inline SharedPtr< VariableScript > ResourceManager::GetOrCreateVariableScript(
		const wstring &guid, ConstructorArgsT&&... args) {
		
		return m_variable_script_resource_pool->template
			GetOrCreateResource< const wstring &, ConstructorArgsT... >(
				guid, guid, std::forward< ConstructorArgsT >(args)...);
	}
}