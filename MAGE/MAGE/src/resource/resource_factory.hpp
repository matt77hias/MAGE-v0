#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.hpp"
#include "model\model_descriptor.hpp"
#include "shader\basic_shader.hpp"
#include "shader\tsnm_shader.hpp"
#include "shader\sprite_shader.hpp"
#include "font\sprite_font.hpp"
#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------

	/**
	 A class of resource factories.
	 */
	class ResourceFactory {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a resource factory.
		 */
		ResourceFactory();
		
		/**
		 Constructs a resource factory from the given resource factory.

		 @param[in]		resource_factory
						A reference to the resource factory to copy.
		 */
		ResourceFactory(const ResourceFactory &resource_factory) = delete;
		
		/**
		 Constructs a resource factory by moving the given resource factory.

		 @param[in]		resource_factory
						A reference to the resource factory to move.
		 */
		ResourceFactory(ResourceFactory &&resource_factory);
		
		/**
		 Destructs this resource factory.
		 */
		virtual ~ResourceFactory();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given resource factory to this resource factory.

		 @param[in]		resource_factory
						A reference to the resource factory to copy.
		 @return		A reference to the copy of the given resource factory
						(i.e. this resource factory).
		 */
		ResourceFactory &operator=(const ResourceFactory &resource_factory) = delete;
		
		/**
		 Moves the given resource factory to this resource factory.

		 @param[in]		resource_factory
						A reference to the resource factory to move.
		 @return		A reference to the moved resource factory
						(i.e. this resource factory).
		 */
		ResourceFactory &operator=(ResourceFactory &&resource_factory) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Creates a model descriptor (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the model descriptor.
		 @param[in]		key
						A reference to the key of the model descriptor.
		 @param[in]		args
						A reference to the constructor arguments 
						for the model descriptor.
		 @return		A pointer to the model descriptor.
		 @throws		FormattedException
						Failed to create the model descriptor.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< ModelDescriptor > CreateModelDescriptor(
			const wstring &key, ConstructorArgsT&&... args);
		
		/**
		 Creates a basic vertex shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the basic vertex shader.
		 @param[in]		key
						A reference to the key of the basic vertex shader.
		 @param[in]		args
						A reference to the constructor arguments 
						for the basic vertex shader.
		 @return		A pointer to the basic vertex shader.
		 @throws		FormattedException
						Failed to create the basic vertex shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VertexShader > CreateBasicVertexShader(
			const wstring &key, ConstructorArgsT&&... args);
		
		/**
		 Creates a basic pixel shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the basic pixel shader.
		 @param[in]		key
						A reference to the key of the basic pixel shader.
		 @param[in]		args
						A reference to the constructor arguments 
						for the basic pixel shader.
		 @return		A pointer to the basic pixel shader.
		 @throws		FormattedException
						Failed to create the basic pixel shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< PixelShader > CreateBasicPixelShader(
			const wstring &key, ConstructorArgsT&&... args);

		/**
		 Creates a tangent-space-normal-map vertex shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the tangent-space-normal-map vertex shader.
		 @param[in]		key
						A reference to the key of the tangent-space-normal-map vertex shader.
		 @param[in]		args
						A reference to the constructor arguments 
						for the tangent-space-normal-map vertex shader.
		 @return		A pointer to the tangent-space-normal-map vertex shader.
		 @throws		FormattedException
						Failed to create the tangent-space-normal-map vertex shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VertexShader > CreateTSNMVertexShader(
			const wstring &key, ConstructorArgsT&&... args);

		/**
		 Creates a tangent-space-normal-map pixel shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the tangent-space-normal-map pixel shader.
		 @param[in]		key
						A reference to the key of the tangent-space-normal-map pixel shader.
		 @param[in]		args
						A reference to the constructor arguments 
						for the tangent-space-normal-map pixel shader.
		 @return		A pointer to the tangent-space-normal-map pixel shader.
		 @throws		FormattedException
						Failed to create the tangent-space-normal-map pixel shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< PixelShader > CreateTSNMPixelShader(
			const wstring &key, ConstructorArgsT&&... args);
		
		/**
		 Creates a sprite vertex shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the sprite vertex shader.
		 @param[in]		key
						A reference to the key of the sprite vertex shader.
		 @param[in]		args
						A reference to the constructor arguments 
						for the sprite vertex shader.
		 @return		A pointer to the sprite vertex shader.
		 @throws		FormattedException
						Failed to create the sprite vertex shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VertexShader > CreateSpriteVertexShader(
			const wstring &key, ConstructorArgsT&&... args);
		
		/**
		 Creates a sprite pixel shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the sprite pixel shader.
		 @param[in]		key
						A reference to the key of the sprite pixel shader.
		 @param[in]		args
						A reference to the constructor arguments 
						for the sprite pixel shader.
		 @return		A pointer to the sprite pixel shader.
		 @throws		FormattedException
						Failed to create the sprite pixel shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< PixelShader > CreateSpritePixelShader(
			const wstring &key, ConstructorArgsT&&... args);
		
		/**
		 Creates a sprite font (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the sprite font.
		 @param[in]		key
						A reference to the key of the sprite font.
		 @param[in]		args
						A reference to the constructor arguments 
						for the sprite font.
		 @return		A pointer to the sprite font.
		 @throws		FormattedException
						Failed to create the sprite font.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< SpriteFont > CreateFont(
			const wstring &key, ConstructorArgsT&&... args);
		
		/**
		 Creates a texture (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the texture.
		 @param[in]		key
						A reference to the key of the texture.
		 @param[in]		args
						A reference to the constructor arguments 
						for the texture.
		 @return		A pointer to the texture.
		 @throws		FormattedException
						Failed to create the texture.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< Texture > CreateTexture(
			const wstring &key, ConstructorArgsT&&... args);
		
		/**
		 Creates a variable script (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the variable script.
		 @param[in]		key
						A reference to the key of the variable script.
		 @param[in]		args
						A reference to the constructor arguments 
						for the variable script.
		 @return		A pointer to the variable script.
		 @throws		FormattedException
						Failed to import the variable script from file
						(only possible if @a import is equal to @c true).
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VariableScript > CreateVariableScript(
			const wstring &key, ConstructorArgsT&&... args);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the model descriptor resource pool of this resource factory.
		 */
		UniquePtr< ResourcePool< wstring, ModelDescriptor > > m_model_descriptor_resource_pool;

		/**
		 A pointer to the vertex shader resource pool of this resource factory.
		 */
		UniquePtr< ResourcePool< wstring, VertexShader > > m_vertex_shader_resource_pool;
		
		/**
		 A pointer to the pixel shader resource pool of this resource factory.
		 */
		UniquePtr< ResourcePool< wstring, PixelShader > > m_pixel_shader_resource_pool;

		/**
		 A pointer to the sprite font resource pool of this resource factory.
		 */
		UniquePtr< ResourcePool< wstring, SpriteFont > > m_font_resource_pool;

		/**
		 A pointer to the texture resource pool of this resource factory.
		 */
		UniquePtr< ResourcePool< wstring, Texture > > m_texture_resource_pool;

		/**
		 A pointer to the variable script resource pool of this resource factory.
		 */
		UniquePtr< ResourcePool< wstring, VariableScript > > m_variable_script_resource_pool;
	};

	//-------------------------------------------------------------------------
	// Resource Factory Methods
	//-------------------------------------------------------------------------

	/**
	 Returns the resource factory.

	 @pre			The current engine must be loaded.
	 @return		A pointer to the resource factory.
	 */
	ResourceFactory *GetResourceFactory() noexcept;

	/**
	 Creates a model descriptor (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the model descriptor.
	 @param[in]		key
					A reference to the key of the model descriptor.
	 @param[in]		args
					A reference to the constructor arguments
					for the model descriptor.
	 @return		A pointer to the model descriptor.
	 @throws		FormattedException
					Failed to create the model descriptor.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< ModelDescriptor > CreateModelDescriptor(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a basic vertex shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the basic vertex shader.
	 @param[in]		key
					A reference to the key of the basic vertex shader.
	 @param[in]		args
					A reference to the constructor arguments
					for the basic vertex shader.
	 @return		A pointer to the basic vertex shader.
	 @throws		FormattedException
					Failed to create the basic vertex shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< VertexShader > CreateBasicVertexShader(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a basic pixel shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the basic pixel shader.
	 @param[in]		key
					A reference to the key of the basic pixel shader.
	 @param[in]		args
					A reference to the constructor arguments
					for the basic pixel shader.
	 @return		A pointer to the basic pixel shader.
	 @throws		FormattedException
					Failed to create the basic pixel shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< PixelShader > CreateBasicPixelShader(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a tangent-space-normal-map vertex shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the tangent-space-normal-map vertex shader.
	 @param[in]		key
					A reference to the key of the tangent-space-normal-map vertex shader.
	 @param[in]		args
					A reference to the constructor arguments
					for the tangent-space-normal-map vertex shader.
	 @return		A pointer to the tangent-space-normal-map vertex shader.
	 @throws		FormattedException
					Failed to create the tangent-space-normal-map vertex shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< VertexShader > CreateTSNMVertexShader(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a tangent-space-normal-map pixel shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the tangent-space-normal-map pixel shader.
	 @param[in]		key
					A reference to the key of the tangent-space-normal-map pixel shader.
	 @param[in]		args
					A reference to the constructor arguments
					for the tangent-space-normal-map pixel shader.
	 @return		A pointer to the tangent-space-normal-map pixel shader.
	 @throws		FormattedException
					Failed to create the tangent-space-normal-map pixel shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< PixelShader > CreateTSNMPixelShader(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a sprite vertex shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the sprite vertex shader.
	 @param[in]		key
					A reference to the key of the sprite vertex shader.
	 @param[in]		args
					A reference to the constructor arguments
					for the sprite vertex shader.
	 @return		A pointer to the sprite vertex shader.
	 @throws		FormattedException
					Failed to create the sprite vertex shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< VertexShader > CreateSpriteVertexShader(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a sprite pixel shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the sprite pixel shader.
	 @param[in]		key
					A reference to the key of the sprite pixel shader.
	 @param[in]		args
					A reference to the constructor arguments
					for the sprite pixel shader.
	 @return		A pointer to the sprite pixel shader.
	 @throws		FormattedException
					Failed to create the sprite pixel shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< PixelShader > CreateSpritePixelShader(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a sprite font (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the sprite font.
	 @param[in]		key
					A reference to the key of the sprite font.
	 @param[in]		args
					A reference to the constructor arguments
					for the sprite font.
	 @return		A pointer to the sprite font.
	 @throws		FormattedException
					Failed to create the sprite font.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< SpriteFont > CreateFont(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a texture (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the texture.
	 @param[in]		key
					A reference to the key of the texture.
	 @param[in]		args
					A reference to the constructor arguments
					for the texture.
	 @return		A pointer to the texture.
	 @throws		FormattedException
					Failed to create the texture.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< Texture > CreateTexture(
		const wstring &key, ConstructorArgsT&&... args);

	/**
	 Creates a variable script (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the variable script.
	 @param[in]		key
					A reference to the key of the variable script.
	 @param[in]		args
					A reference to the constructor arguments
					for the variable script.
	 @return		A pointer to the variable script.
	 @throws		FormattedException
					Failed to import the variable script from file
					(only possible if @a import is equal to @c true).
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< VariableScript > CreateVariableScript(
		const wstring &key, ConstructorArgsT&&... args);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.tpp"

#pragma endregion