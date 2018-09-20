#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// ResourceManager: GetPool
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ResourceT >
	[[nodiscard]]
	inline ResourceManager::pool_type< ResourceT >&
		ResourceManager::GetPool() noexcept {

		// This member method is non-const
		// => this object instance is non-const
		// => const_cast is safe.

		return const_cast< pool_type< ResourceT >& >(
			static_cast< const ResourceManager* >(this)->GetPool< ResourceT >());
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< ModelDescriptor >&
		ResourceManager::GetPool< ModelDescriptor >() const noexcept {

		return m_model_descriptor_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< VertexShader >&
		ResourceManager::GetPool< VertexShader >() const noexcept {

		return m_vs_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< HullShader >&
		ResourceManager::GetPool< HullShader >() const noexcept {

		return m_hs_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< DomainShader >&
		ResourceManager::GetPool< DomainShader >() const noexcept {

		return m_ds_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< GeometryShader >&
		ResourceManager::GetPool< GeometryShader >() const noexcept {

		return m_gs_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< PixelShader >&
		ResourceManager::GetPool< PixelShader >() const noexcept {

		return m_ps_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< ComputeShader >&
		ResourceManager::GetPool< ComputeShader >() const noexcept {

		return m_cs_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< SpriteFont >&
		ResourceManager::GetPool< SpriteFont >() const noexcept {

		return m_sprite_font_pool;
	}

	template<>
	[[nodiscard]]
	inline const ResourceManager::pool_type< Texture >&
		ResourceManager::GetPool< Texture >() const noexcept {

		return m_texture_pool;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ResourceManager: Remaining
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ResourceT >
	[[nodiscard]]
	inline bool
		ResourceManager::Contains(const key_type< ResourceT >& guid) noexcept {

		return GetPool< ResourceT >().Contains(guid);
	}

	template< typename ResourceT >
	[[nodiscard]]
	inline SharedPtr< ResourceManager::value_type< ResourceT > >
		ResourceManager::Get(const key_type< ResourceT >& guid) noexcept {

		return GetPool< ResourceT >().Get(guid);
	}


	template< typename ResourceT, typename VertexT, typename IndexT >
	inline typename std::enable_if_t< std::is_same_v< ModelDescriptor, ResourceT >,
		ModelDescriptorPtr >
		ResourceManager::GetOrCreate(const std::wstring& fname,
									 const MeshDescriptor< VertexT, IndexT >& desc,
									 bool export_as_MDL) {

		return GetPool< ResourceT >().GetOrCreate(fname, m_device, *this,
												  key_type< ResourceT >(fname),
												  desc, export_as_MDL);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< VertexShader, ResourceT >,
		VertexShaderPtr >
		ResourceManager::GetOrCreate(const std::wstring& guid,
									 const CompiledShader& compiled_shader,
									 gsl::span< const D3D11_INPUT_ELEMENT_DESC >
									 input_element_descs) {

		return GetPool< ResourceT >().GetOrCreate(guid, m_device,
												  key_type< ResourceT >(guid),
												  compiled_shader,
												  input_element_descs);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< HullShader, ResourceT >,
		HullShaderPtr >
		ResourceManager::GetOrCreate(const std::wstring& guid,
									 const CompiledShader& compiled_shader) {

		return GetPool< ResourceT >().GetOrCreate(guid, m_device,
												  key_type< ResourceT >(guid),
												  compiled_shader);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< DomainShader, ResourceT >,
		DomainShaderPtr >
		ResourceManager::GetOrCreate(const std::wstring& guid,
									 const CompiledShader& compiled_shader) {

		return GetPool< ResourceT >().GetOrCreate(guid, m_device,
												  key_type< ResourceT >(guid),
												  compiled_shader);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< GeometryShader, ResourceT >,
		GeometryShaderPtr >
		ResourceManager::GetOrCreate(const std::wstring& guid,
									 const CompiledShader& compiled_shader) {

		return GetPool< ResourceT >().GetOrCreate(guid, m_device,
												  key_type< ResourceT >(guid),
												  compiled_shader);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< PixelShader, ResourceT >,
		PixelShaderPtr >
		ResourceManager::GetOrCreate(const std::wstring& guid,
									 const CompiledShader& compiled_shader) {

		return GetPool< ResourceT >().GetOrCreate(guid, m_device,
												  key_type< ResourceT >(guid),
												  compiled_shader);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< ComputeShader, ResourceT >,
		ComputeShaderPtr >
		ResourceManager::GetOrCreate(const std::wstring& guid,
									 const CompiledShader& compiled_shader) {

		return GetPool< ResourceT >().GetOrCreate(guid, m_device,
												  key_type< ResourceT >(guid),
												  compiled_shader);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< SpriteFont, ResourceT >,
		SpriteFontPtr >
		ResourceManager::GetOrCreate(const std::wstring& fname,
									 const SpriteFontDescriptor& desc) {

		return GetPool< ResourceT >().GetOrCreate(fname, m_device,
												  key_type< ResourceT >(fname),
												  desc);
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< Texture, ResourceT >,
		TexturePtr >
		ResourceManager::GetOrCreate(const std::wstring& fname) {

		return GetPool< ResourceT >().GetOrCreate(fname, m_device,
												  key_type< ResourceT >(fname));
	}

	template< typename ResourceT >
	inline typename std::enable_if_t< std::is_same_v< Texture, ResourceT >,
		TexturePtr >
		ResourceManager::GetOrCreate(const std::wstring& guid,
									 const D3D11_TEXTURE2D_DESC& desc,
									 const D3D11_SUBRESOURCE_DATA& initial_data) {

		return GetPool< ResourceT >().GetOrCreate(guid, m_device,
												  key_type< ResourceT >(guid),
												  desc, initial_data);
	}

	#pragma endregion
}