#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.hpp"
#include "resource\model\model_descriptor.hpp"
#include "resource\shader\shader.hpp"
#include "resource\font\sprite_font.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of resource managers.
	 */
	class ResourceManager {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------
		#pragma region

		/**
		 A struct of resource records.

		 @tparam		ResourceT
						The resource type.
		 */
		template< typename ResourceT, typename Enable = void >
		struct ResourceRecord;

		/**
		 A struct of non-shader resource records.

		 @tparam		ResourceT
						The resource type.
		 */
		template< typename ResourceT >
		struct ResourceRecord< ResourceT,
			typename std::enable_if_t< !is_shader_v< ResourceT > > > {

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			/**
			 The pool type of resource pools containing resources of the given
			 type.
			 */
			using pool_type = ResourcePool< std::wstring, const ResourceT >;
		};

		/**
		 A struct of shader resource records.

		 @tparam		ResourceT
						The resource type.
		 */
		template< typename ResourceT >
		struct ResourceRecord< ResourceT,
			typename std::enable_if_t< is_shader_v< ResourceT > > > {

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			/**
			 The pool type of resource pools containing vertex shaders.
			 */
			using pool_type = PersistentResourcePool< std::wstring, const ResourceT >;
		};

		/**
		 The pool type of resource pools containing resources of the given
		 type.

		 @tparam		ResourceT
						The resource type.
		 */
		template< typename ResourceT >
		using pool_type = typename ResourceRecord< ResourceT >::pool_type;

		/**
		 The key type of resource pools containing resources of the given
		 type.

		 @tparam		ResourceT
						The resource type.
		 */
		template< typename ResourceT >
		using key_type = typename pool_type< ResourceT >::key_type;

		/**
		 The value type of resource pools containing resources of the given
		 type.

		 @tparam		ResourceT
						The resource type.
		 */
		template< typename ResourceT >
		using value_type = typename pool_type< ResourceT >::value_type;

		#pragma endregion

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a resource manager.

		 @param[in]		device
						A reference to the device.
		 */
		ResourceManager(ID3D11Device& device);

		/**
		 Constructs a resource manager from the given resource manager.

		 @param[in]		manager
						A reference to the resource manager to copy.
		 */
		ResourceManager(const ResourceManager& manager) = delete;

		/**
		 Constructs a resource manager by moving the given resource manager.

		 @param[in]		manager
						A reference to the resource manager to move.
		 */
		ResourceManager(ResourceManager&& manager) noexcept;

		/**
		 Destructs this resource manager.
		 */
		~ResourceManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given resource manager to this resource manager.

		 @param[in]		manager
						A reference to the resource manager to copy.
		 @return		A reference to the copy of the given resource manager
						(i.e. this resource manager).
		 */
		ResourceManager& operator=(const ResourceManager& manager) = delete;

		/**
		 Moves the given resource manager to this resource manager.

		 @param[in]		manager
						A reference to the resource manager to move.
		 @return		A reference to the moved resource manager (i.e. this
						resource manager).
		 */
		ResourceManager& operator=(ResourceManager&& manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this resource manager contains a resource of the given
		 type corresponding to the given globally unique identifier.

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						A reference to the globally unique identifier of the
						resource.
		 @return		@c true if this resource managers contains a resource
						of the given type corresponding to the given globally
						unique identifier. @c false otherwise.
		 */
		template< typename ResourceT >
		[[nodiscard]]
		bool Contains(const typename key_type< ResourceT >& guid) noexcept;

		/**
		 Returns the resource of the given type corresponding to the given
		 globally unique identifier of this resource manager.

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						A reference to the globally unique identifier of the
						model descriptor.
		 @return		@c nullptr, if this resource managers does not contain
						a resource of the given type corresponding to the given
						globally unique identifier.
		 @return		A pointer to the resource.
		 */
		template< typename ResourceT >
		[[nodiscard]]
		SharedPtr< typename value_type< ResourceT > >
			Get(const typename key_type< ResourceT >& guid) noexcept;

		/**
		 Creates a model descriptor (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		VertexT
						The vertex type.
		 @tparam		IndexT
						The index type.
		 @param[in]		fname
						The filename (the globally unique identifier).
		 @param[in]		desc
						A reference to the mesh descriptor.
		 @param[in]		export_as_MDL
						@c true if the model descriptor needs to be exported as
						MDL file. @c false otherwise.
		 @return		A pointer to the model descriptor.
		 @throws		Exception
						Failed to create the model descriptor.
		 */
		template< typename ResourceT, typename VertexT, typename IndexT >
		typename std::enable_if_t< std::is_same_v< ModelDescriptor, ResourceT >,
			ModelDescriptorPtr > GetOrCreate(const std::wstring& fname,
											 const  MeshDescriptor< VertexT, IndexT >&
											 desc = MeshDescriptor< VertexT, IndexT >(),
											 bool export_as_MDL = false);

		/**
		 Creates a vertex shader (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled vertex shader.
		 @param[in]		input_element_descs
						The input element descriptors.
		 @return		A pointer to the vertex shader.
		 @throws		Exception
						Failed to create the vertex shader.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< VertexShader, ResourceT >,
			VertexShaderPtr > GetOrCreate(const std::wstring& guid,
										  const CompiledShader& compiled_shader,
										  gsl::span< const D3D11_INPUT_ELEMENT_DESC >
										  input_element_descs);

		/**
		 Creates a hull shader (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @return		A pointer to the hull shader.
		 @throws		Exception
						Failed to create the hull shader.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< HullShader, ResourceT >,
			HullShaderPtr > GetOrCreate(const std::wstring& guid,
										const CompiledShader& compiled_shader);

		/**
		 Creates a domain shader (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @return		A pointer to the domain shader.
		 @throws		Exception
						Failed to create the domain shader.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< DomainShader, ResourceT >,
			DomainShaderPtr > GetOrCreate(const std::wstring& guid,
										  const CompiledShader& compiled_shader);

		/**
		 Creates a geometry shader (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @return		A pointer to the geometry shader.
		 @throws		Exception
						Failed to create the geometry shader.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< GeometryShader, ResourceT >,
			GeometryShaderPtr > GetOrCreate(const std::wstring& guid,
											const CompiledShader& compiled_shader);

		/**
		 Creates a pixel shader (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @return		A pointer to the pixel shader.
		 @throws		Exception
						Failed to create the pixel shader.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< PixelShader, ResourceT >,
			PixelShaderPtr > GetOrCreate(const std::wstring& guid,
										 const CompiledShader& compiled_shader);

		/**
		 Creates a compute shader (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		compiled_shader
						A reference to the compiled shader.
		 @return		A pointer to the hull shader.
		 @throws		Exception
						Failed to create the compute shader.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< ComputeShader, ResourceT >,
			ComputeShaderPtr > GetOrCreate(const std::wstring& guid,
										   const CompiledShader& compiled_shader);

		/**
		 Creates a sprite font (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		fname
						The filename (the globally unique identifier).
		 @param[in]		desc
						A reference to the sprite font descriptor.
		 @return		A pointer to the sprite font.
		 @throws		Exception
						Failed to create the sprite font.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< SpriteFont, ResourceT >,
			SpriteFontPtr > GetOrCreate(const std::wstring& fname,
										const SpriteFontDescriptor& desc
										    = SpriteFontDescriptor());

		/**
		 Creates a texture (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		fname
						The filename (the globally unique identifier).
		 @return		A pointer to the texture.
		 @throws		Exception
						Failed to create the texture.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< Texture, ResourceT >,
			TexturePtr > GetOrCreate(const std::wstring& fname);

		/**
		 Creates a texture (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @param[in]		guid
						The globally unique identifier.
		 @param[in]		desc
						A reference to the texture descriptor.
		 @param[in]		initial_data
						A reference to the initial data.
		 @return		A pointer to the texture.
		 @throws		Exception
						Failed to create the texture.
		 */
		template< typename ResourceT >
		typename std::enable_if_t< std::is_same_v< Texture, ResourceT >,
			TexturePtr > GetOrCreate(const std::wstring& guid,
									 const D3D11_TEXTURE2D_DESC& desc,
									 const D3D11_SUBRESOURCE_DATA& initial_data);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the resource pool containing resources of the given type of
		 this resource manager.

		 @tparam		ResourceT
						The resource type.
		 @return		A reference to the the resource pool containing
						resources of the given type of this resource manager.
		 */
		template< typename ResourceT >
		[[nodiscard]]
		typename pool_type< ResourceT >& GetPool() noexcept;

		/**
		 Returns the resource pool containing resources of the given type of
		 this resource manager.

		 @tparam		ResourceT
						The resource type.
		 @return		A reference to the the resource pool containing
						resources of the given type of this resource manager.
		 */
		template< typename ResourceT >
		[[nodiscard]]
		const typename pool_type< ResourceT >& GetPool() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device of this resource manager.
		 */
		ID3D11Device& m_device;

		/**
		 The model descriptor resource pool of this resource manager.
		 */
		typename pool_type< ModelDescriptor > m_model_descriptor_pool;

		/**
		 The vertex shader resource pool of this resource manager.
		 */
		typename pool_type< VertexShader > m_vs_pool;

		/**
		 The hull shader resource pool of this resource manager.
		 */
		typename pool_type< HullShader > m_hs_pool;

		/**
		 The domain shader resource pool of this resource manager.
		 */
		typename pool_type< DomainShader > m_ds_pool;

		/**
		 The geometry shader resource pool of this resource manager.
		 */
		typename pool_type< GeometryShader > m_gs_pool;

		/**
		 The pixel shader resource pool of this resource manager.
		 */
		typename pool_type< PixelShader > m_ps_pool;

		/**
		 The compute shader resource pool of this resource manager.
		 */
		typename pool_type< ComputeShader > m_cs_pool;

		/**
		 The sprite font resource pool of this resource manager.
		 */
		typename pool_type< SpriteFont > m_sprite_font_pool;

		/**
		 The texture resource pool of this resource manager.
		 */
		typename pool_type< Texture > m_texture_pool;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\rendering_resource_manager.tpp"

#pragma endregion