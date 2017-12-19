#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceManager: Has
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline bool ResourceManager
		::Has< ModelDescriptor >(const wstring &guid) noexcept {
		return m_model_descriptor_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< VertexShader >(const wstring &guid) noexcept {
		return m_vs_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< HullShader >(const wstring &guid) noexcept {
		return m_hs_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< DomainShader >(const wstring &guid) noexcept {
		return m_ds_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< GeometryShader >(const wstring &guid) noexcept {
		return m_gs_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< PixelShader >(const wstring &guid) noexcept {
		return m_ps_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< ComputeShader >(const wstring &guid) noexcept {
		return m_cs_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< SpriteFont >(const wstring &guid) noexcept {
		return m_sprite_font_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< Texture >(const wstring &guid) noexcept {
		return m_texture_pool.HasResource(guid);
	}

	template<>
	inline bool ResourceManager
		::Has< VariableScript >(const wstring &guid) noexcept {
		return m_variable_script_pool.HasResource(guid);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ResourceManager: Get/GetMutable
	//-------------------------------------------------------------------------
	#pragma region

	template<>
	inline SharedPtr< const ModelDescriptor > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_model_descriptor_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const VertexShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_vs_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const HullShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_hs_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const DomainShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_ds_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const GeometryShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_gs_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const PixelShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_ps_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const ComputeShader > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_cs_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const SpriteFont > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_sprite_font_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< const Texture > ResourceManager
		::Get(const wstring &guid) noexcept {

		return m_texture_pool.GetResource(guid);
	}

	template<>
	inline SharedPtr< VariableScript > ResourceManager
		::GetMutable(const wstring &guid) noexcept {

		return m_variable_script_pool.GetResource(guid);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ResourceManager: GetOrCreate/GetOrCreateMutable
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< ModelDescriptor, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_model_descriptor_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< VertexShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_vs_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< HullShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_hs_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< DomainShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_ds_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< GeometryShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_gs_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< PixelShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_ps_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< ComputeShader, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_cs_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< SpriteFont, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_sprite_font_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< Texture, ResourceT >,
		SharedPtr< const ResourceT > > ResourceManager::GetOrCreate(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_texture_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ResourceT, typename... ConstructorArgsT >
	inline typename std::enable_if_t< std::is_same_v< VariableScript, ResourceT >,
		SharedPtr< ResourceT > > ResourceManager::GetOrCreateMutable(
			const wstring &guid, ConstructorArgsT&&... args) {

		return m_variable_script_pool.template
			GetOrCreateResource< wstring, ConstructorArgsT... >(
				guid, wstring(guid), std::forward< ConstructorArgsT >(args)...);
	}

	#pragma endregion
}