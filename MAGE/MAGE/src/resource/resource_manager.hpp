#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.hpp"
#include "model\model_descriptor.hpp"
#include "shader\shader.hpp"
#include "sprite\font\sprite_font.hpp"
#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of resource managers.
	 */
	class ResourceManager final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the resource manager associated with the current engine.

		 @pre			The current engine must exist.
		 @return		A pointer to the resource manager associated with the 
						current engine.
		 */
		static ResourceManager *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a resource manager.
		 */
		ResourceManager();
		
		/**
		 Constructs a resource manager from the given resource manager.

		 @param[in]		manager
						A reference to the resource manager to copy.
		 */
		ResourceManager(const ResourceManager &manager) = delete;
		
		/**
		 Constructs a resource manager by moving the given resource manager.

		 @param[in]		manager
						A reference to the resource manager to move.
		 */
		ResourceManager(ResourceManager &&manager) = delete;
		
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
		ResourceManager &operator=(const ResourceManager &manager) = delete;
		
		/**
		 Moves the given resource manager to this resource manager.

		 @param[in]		manager
						A reference to the resource manager to move.
		 @return		A reference to the moved resource manager (i.e. this 
						resource manager).
		 */
		ResourceManager &operator=(ResourceManager &&manager) = delete;
		
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
		bool Contains(const wstring &guid) noexcept;
		
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
		SharedPtr< const ResourceT > Get(const wstring &guid) noexcept;
		
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
		SharedPtr< ResourceT > GetMutable(const wstring &guid) noexcept;

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< ModelDescriptor, ResourceT >, 
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< VertexShader, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< HullShader, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< DomainShader, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< GeometryShader, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< PixelShader, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< ComputeShader, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< SpriteFont, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);

		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< Texture, ResourceT >,
			SharedPtr< const ResourceT > > GetOrCreate(const wstring &guid, 
			                                           ConstructorArgsT &&...args);
		
		/**
		 Creates a resource of the given type (if not existing).

		 @tparam		ResourceT
						The resource type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the resource 
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						resource.
		 @param[in]		args
						A reference to the constructor arguments for the 
						resource (excluding the globally unique identifier).
		 @return		A pointer to the resource.
		 @throws		Exception
						Failed to create the resource.
		 */
		template< typename ResourceT, typename... ConstructorArgsT >
		typename std::enable_if_t< std::is_same_v< VariableScript, ResourceT >,
			SharedPtr< ResourceT > > GetOrCreateMutable(const wstring &guid,
				                                        ConstructorArgsT &&...args);
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The model descriptor resource pool of this resource manager.
		 */
		ResourcePool< wstring, const ModelDescriptor > m_model_descriptor_pool;

		/**
		 The vertex shader resource pool of this resource manager.
		 */
		PersistentResourcePool< wstring, const VertexShader > m_vs_pool;

		/**
		 The hull shader resource pool of this resource manager.
		 */
		PersistentResourcePool< wstring, const HullShader > m_hs_pool;

		/**
		 The domain shader resource pool of this resource manager.
		 */
		PersistentResourcePool< wstring, const DomainShader > m_ds_pool;

		/**
		 The geometry shader resource pool of this resource manager.
		 */
		PersistentResourcePool< wstring, const GeometryShader > m_gs_pool;

		/**
		 The pixel shader resource pool of this resource manager.
		 */
		PersistentResourcePool< wstring, const PixelShader > m_ps_pool;

		/**
		 The compute shader resource pool of this resource manager.
		 */
		PersistentResourcePool< wstring, const ComputeShader > m_cs_pool;

		/**
		 The sprite font resource pool of this resource manager.
		 */
		ResourcePool< wstring, const SpriteFont > m_sprite_font_pool;

		/**
		 The texture resource pool of this resource manager.
		 */
		ResourcePool< wstring, const Texture > m_texture_pool;

		/**
		 The variable script resource pool of this resource manager.
		 */
		ResourcePool< wstring, VariableScript > m_variable_script_pool;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_manager.tpp"

#pragma endregion