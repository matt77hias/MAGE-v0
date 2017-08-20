#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.hpp"
#include "model\model_descriptor.hpp"
#include "shader\shader.hpp"
#include "font\sprite_font.hpp"
#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of resource managers.
	 */
	class ResourceManager {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the resource manager associated with the current engine.

		 @pre			The resource manager associated with the 
						current engine must be loaded.
		 @return		A pointer to the resource manager associated
						with the current engine.
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

		 @param[in]		resource_factory
						A reference to the resource manager to copy.
		 */
		ResourceManager(const ResourceManager &resource_factory) = delete;
		
		/**
		 Constructs a resource manager by moving the given resource manager.

		 @param[in]		resource_factory
						A reference to the resource manager to move.
		 */
		ResourceManager(ResourceManager &&resource_factory);
		
		/**
		 Destructs this resource manager.
		 */
		virtual ~ResourceManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given resource manager to this resource manager.

		 @param[in]		resource_factory
						A reference to the resource manager to copy.
		 @return		A reference to the copy of the given resource manager
						(i.e. this resource manager).
		 */
		ResourceManager &operator=(const ResourceManager &resource_factory) = delete;
		
		/**
		 Moves the given resource manager to this resource manager.

		 @param[in]		resource_factory
						A reference to the resource manager to move.
		 @return		A reference to the moved resource manager
						(i.e. this resource manager).
		 */
		ResourceManager &operator=(ResourceManager &&resource_factory) = delete;
		
		//---------------------------------------------------------------------
		// Member Methods: HasModelDescriptor
		//---------------------------------------------------------------------

		/**
		 Checks whether this resource manager contains a model descriptor 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the 
						model descriptor.
		 @return		@c true if this resource managers contains
						a model descriptor corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasModelDescriptor(const wstring &guid) noexcept;
		
		/**
		 Checks whether this resource manager contains a vertex shader 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						vertex shader.
		 @return		@c true if this resource managers contains
						a vertex shader corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasVS(const wstring &guid) noexcept;

		/**
		 Checks whether this resource manager contains a hull shader 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						hull shader.
		 @return		@c true if this resource managers contains
						a hull shader corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasHS(const wstring &guid) noexcept;

		/**
		 Checks whether this resource manager contains a domain shader 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						domain shader.
		 @return		@c true if this resource managers contains
						a domain shader corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasDS(const wstring &guid) noexcept;

		/**
		 Checks whether this resource manager contains a geometry shader 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						geometry shader.
		 @return		@c true if this resource managers contains
						a geometry shader corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasGS(const wstring &guid) noexcept;

		/**
		 Checks whether this resource manager contains a pixel shader 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						pixel shader.
		 @return		@c true if this resource managers contains
						a pixel shader corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasPS(const wstring &guid) noexcept;

		/**
		 Checks whether this resource manager contains a compute shader 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						compute shader.
		 @return		@c true if this resource managers contains
						a compute shader corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasCS(const wstring &guid) noexcept;
		
		/**
		 Checks whether this resource manager contains a sprite font 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						sprite font.
		 @return		@c true if this resource managers contains
						a sprite font corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasSpriteFont(const wstring &guid) noexcept;
		
		/**
		 Checks whether this resource manager contains a texture 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						texture.
		 @return		@c true if this resource managers contains
						a texture corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasTexture(const wstring &guid) noexcept;
		
		/**
		 Checks whether this resource manager contains a variable script 
		 corresponding to the given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						variable script.
		 @return		@c true if this resource managers contains
						a variable script corresponding to the given 
						globally unique identifier.
						@c false otherwise.
		 */
		bool HasVariableScript(const wstring &guid) noexcept;
		
		//---------------------------------------------------------------------
		// Member Methods: GetModelDescriptor
		//---------------------------------------------------------------------

		/**
		 Returns the model descriptor corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the 
						model descriptor.
		 @return		@c nullptr, if this resource managers does not contain
						a model descriptor corresponding to the given globally
						unique identifier.
		 @return		A pointer to the model descriptor.
		 */
		SharedPtr< const ModelDescriptor > GetModelDescriptor(const wstring &guid) noexcept;
		
		/**
		 Returns the vertex shader corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						vertex shader.
		 @return		@c nullptr, if this resource managers does not contain
						a vertex shader corresponding to the given globally
						unique identifier.
		 @return		A pointer to the vertex shader.
		 */
		SharedPtr< const VertexShader > GetVS(const wstring &guid) noexcept;

		/**
		 Returns the hull shader corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						hull shader.
		 @return		@c nullptr, if this resource managers does not contain
						a hull shader corresponding to the given globally
						unique identifier.
		 @return		A pointer to the hull shader.
		 */
		SharedPtr< const HullShader > GetHS(const wstring &guid) noexcept;

		/**
		 Returns the domain shader corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						domain shader.
		 @return		@c nullptr, if this resource managers does not contain
						a domain shader corresponding to the given globally
						unique identifier.
		 @return		A pointer to the domain shader.
		 */
		SharedPtr< const DomainShader > GetDS(const wstring &guid) noexcept;

		/**
		 Returns the geometry shader corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						geometry shader.
		 @return		@c nullptr, if this resource managers does not contain
						a geometry shader corresponding to the given globally
						unique identifier.
		 @return		A pointer to the geometry shader.
		 */
		SharedPtr< const GeometryShader > GetGS(const wstring &guid) noexcept;

		/**
		 Returns the pixel shader corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						pixel shader.
		 @return		@c nullptr, if this resource managers does not contain
						a pixel shader corresponding to the given globally
						unique identifier.
		 @return		A pointer to the pixel shader.
		 */
		SharedPtr< const PixelShader > GetPS(const wstring &guid) noexcept;

		/**
		 Returns the compute shader corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						compute shader.
		 @return		@c nullptr, if this resource managers does not contain
						a compute shader corresponding to the given globally
						unique identifier.
		 @return		A pointer to the compute shader.
		 */
		SharedPtr< const ComputeShader > GetCS(const wstring &guid) noexcept;
		
		/**
		 Returns the sprite font corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						sprite font.
		 @return		@c nullptr, if this resource managers does not contain
						a sprite font corresponding to the given globally
						unique identifier.
		 @return		A pointer to the sprite font.
		 */
		SharedPtr< SpriteFont > GetSpriteFont(const wstring &guid) noexcept;
		
		/**
		 Returns the texture corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						texture.
		 @return		@c nullptr, if this resource managers does not contain
						a texture corresponding to the given globally
						unique identifier.
		 @return		A pointer to the texture.
		 */
		SharedPtr< const Texture > GetTexture(const wstring &guid) noexcept;
		
		/**
		 Returns the variable script corresponding to the given globally 
		 unique identifier of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the
						variable script.
		 @return		@c nullptr, if this resource managers does not contain
						a variable script corresponding to the given globally
						unique identifier.
		 @return		A pointer to the variable script.
		 */
		SharedPtr< VariableScript > GetVariableScript(const wstring &guid) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: GetOrCreateModelDescriptor
		//---------------------------------------------------------------------

		/**
		 Creates a model descriptor (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the model descriptor
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the 
						model descriptor.
		 @param[in]		args
						A reference to the constructor arguments for the model 
						descriptor (excluding the globally unique identifier).
		 @return		A pointer to the model descriptor.
		 @throws		FormattedException
						Failed to create the model descriptor.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const ModelDescriptor > GetOrCreateModelDescriptor(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a vertex shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the vertex shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						vertex shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						vertex shader (excluding the globally unique identifier).
		 @return		A pointer to the vertex shader.
		 @throws		FormattedException
						Failed to create the vertex shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const VertexShader > GetOrCreateVS(
			const wstring &guid, ConstructorArgsT&&... args);

		/**
		 Creates a hull shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the hull shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						hull shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						hull shader (excluding the globally unique identifier).
		 @return		A pointer to the hull shader.
		 @throws		FormattedException
						Failed to create the hull shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const HullShader > GetOrCreateHS(
			const wstring &guid, ConstructorArgsT&&... args);

		/**
		 Creates a domain shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the domain shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						domain shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						domain shader (excluding the globally unique identifier).
		 @return		A pointer to the domain shader.
		 @throws		FormattedException
						Failed to create the domain shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const DomainShader > GetOrCreateDS(
			const wstring &guid, ConstructorArgsT&&... args);

		/**
		 Creates a geometry shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the geometry shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						geometry shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						geometry shader (excluding the globally unique identifier).
		 @return		A pointer to the geometry shader.
		 @throws		FormattedException
						Failed to create the geometry shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const GeometryShader > GetOrCreateGS(
			const wstring &guid, ConstructorArgsT&&... args);

		/**
		 Creates a pixel shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the pixel shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						pixel shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						pixel shader (excluding the globally unique identifier).
		 @return		A pointer to the pixel shader.
		 @throws		FormattedException
						Failed to create the pixel shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const PixelShader > GetOrCreatePS(
			const wstring &guid, ConstructorArgsT&&... args);

		/**
		 Creates a compute shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the compute shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						compute shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						compute shader (excluding the globally unique identifier).
		 @return		A pointer to the compute shader.
		 @throws		FormattedException
						Failed to create the compute shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const ComputeShader > GetOrCreateCS(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a sprite font (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the sprite font
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						sprite font.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						font (excluding the globally unique identifier).
		 @return		A pointer to the sprite font.
		 @throws		FormattedException
						Failed to create the sprite font.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< SpriteFont > GetOrCreateSpriteFont(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a texture (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the texture
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						texture.
		 @param[in]		args
						A reference to the constructor arguments for the texture
						(excluding the globally unique identifier).
		 @return		A pointer to the texture.
		 @throws		FormattedException
						Failed to create the texture.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< const Texture > GetOrCreateTexture(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a variable script (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the variable script
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						variable script.
		 @param[in]		args
						A reference to the constructor arguments for the variable
						script (excluding the globally unique identifier).
		 @return		A pointer to the variable script.
		 @throws		FormattedException
						Failed to create the variable script.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VariableScript > GetOrCreateVariableScript(
			const wstring &guid, ConstructorArgsT&&... args);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the model descriptor resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, const ModelDescriptor > > m_model_descriptor_resource_pool;

		/**
		 A pointer to the vertex shader resource pool of this resource manager.
		 */
		UniquePtr< PersistentResourcePool< wstring, const VertexShader > > m_vs_resource_pool;

		/**
		 A pointer to the hull shader resource pool of this resource manager.
		 */
		UniquePtr< PersistentResourcePool< wstring, const HullShader > > m_hs_resource_pool;

		/**
		 A pointer to the domain shader resource pool of this resource manager.
		 */
		UniquePtr< PersistentResourcePool< wstring, const DomainShader > > m_ds_resource_pool;

		/**
		 A pointer to the geometry shader resource pool of this resource manager.
		 */
		UniquePtr< PersistentResourcePool< wstring, const GeometryShader > > m_gs_resource_pool;

		/**
		 A pointer to the pixel shader resource pool of this resource manager.
		 */
		UniquePtr< PersistentResourcePool< wstring, const PixelShader > > m_ps_resource_pool;

		/**
		 A pointer to the compute shader resource pool of this resource manager.
		 */
		UniquePtr< PersistentResourcePool< wstring, const ComputeShader > > m_cs_resource_pool;

		/**
		 A pointer to the sprite font resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, SpriteFont > > m_sprite_font_resource_pool;

		/**
		 A pointer to the texture resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, const Texture > > m_texture_resource_pool;

		/**
		 A pointer to the variable script resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, VariableScript > > m_variable_script_resource_pool;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_manager.tpp"

#pragma endregion