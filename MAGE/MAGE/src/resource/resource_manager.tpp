#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceManager: Contains
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline bool ResourceManager
		::Contains< ModelDescriptor >(const wstring &guid) noexcept {
		return m_model_descriptor_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< VertexShader >(const wstring &guid) noexcept {
		return m_vs_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< HullShader >(const wstring &guid) noexcept {
		return m_hs_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< DomainShader >(const wstring &guid) noexcept {
		return m_ds_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< GeometryShader >(const wstring &guid) noexcept {
		return m_gs_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< PixelShader >(const wstring &guid) noexcept {
		return m_ps_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< ComputeShader >(const wstring &guid) noexcept {
		return m_cs_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< SpriteFont >(const wstring &guid) noexcept {
		return m_sprite_font_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< Texture >(const wstring &guid) noexcept {
		return m_texture_pool.Contains(guid);
	}

	template<>
	inline bool ResourceManager
		::Contains< VariableScript >(const wstring &guid) noexcept {
		return m_variable_script_pool.Contains(guid);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ResourceManager: Get/GetMutable
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline SharedPtr< const ModelDescriptor > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_model_descriptor_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const VertexShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_vs_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const HullShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_hs_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const DomainShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_ds_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const GeometryShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_gs_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const PixelShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_ps_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const ComputeShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_cs_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const SpriteFont > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_sprite_font_pool.Get(guid);
	}

	template<>
	inline SharedPtr< const Texture > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_texture_pool.Get(guid);
	}

	template<>
	inline SharedPtr< VariableScript > ResourceManager
		::GetMutable(const wstring &guid) noexcept {

		return m_variable_script_pool.Get(guid);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ResourceManager: GetOrCreate/GetOrCreateMutable
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< ModelDescriptor, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_model_descriptor_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< VertexShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_vs_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< HullShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_hs_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< DomainShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_ds_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< GeometryShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_gs_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< PixelShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_ps_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< ComputeShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_cs_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< SpriteFont, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_sprite_font_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< Texture, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_texture_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< VariableScript, ResourceT >,
		SharedPtr< ResourceT > > ResourceManager::GetOrCreateMutable(
			const wstring &guid, ConstructorArgsT &&...args) {

		return m_variable_script_pool.template
			GetOrCreate< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	#pragma endregion
}