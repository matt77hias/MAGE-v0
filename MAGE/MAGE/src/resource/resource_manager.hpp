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
	// ResourceManager
	//-------------------------------------------------------------------------

	/**
	 A class of resource managers.
	 */
	class ResourceManager {

	public:

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
		// Member Methods
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
		SharedPtr< ModelDescriptor > CreateModelDescriptor(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a basic vertex shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the basic vertex shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						basic vertex shader.
		 @param[in]		args
						A reference to the constructor arguments for the basic
	 					vertex shader (excluding the globally unique identifier).
		 @return		A pointer to the basic vertex shader.
		 @throws		FormattedException
						Failed to create the basic vertex shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VertexShader > CreateBasicVertexShader(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a basic pixel shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the basic pixel shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						basic pixel shader.
		 @param[in]		args
						A reference to the constructor arguments for the basic
						pixel shader (excluding the globally unique identifier).
		 @return		A pointer to the basic pixel shader.
		 @throws		FormattedException
						Failed to create the basic pixel shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< PixelShader > CreateBasicPixelShader(
			const wstring &guid, ConstructorArgsT&&... args);

		/**
		 Creates a tsnm vertex shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the tsnm vertex shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						tsnm vertex shader.
		 @param[in]		args
						A reference to the constructor arguments for the tsnm
						vertex shader (excluding the globally unique identifier).
		 @return		A pointer to the tsnm vertex shader.
		 @throws		FormattedException
						Failed to create the tsnm vertex shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VertexShader > CreateTSNMVertexShader(
			const wstring &guid, ConstructorArgsT&&... args);

		/**
		 Creates a tsnm pixel shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the tsnm pixel shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						tsnm pixel shader.
		 @param[in]		args
						A reference to the constructor arguments for the tsnm
						pixel shader (excluding the globally unique identifier).
		 @return		A pointer to the tsnm pixel shader.
		 @throws		FormattedException
						Failed to create the tsnm pixel shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< PixelShader > CreateTSNMPixelShader(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a sprite vertex shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the sprite vertex shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						sprite vertex shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						vertex shader (excluding the globally unique identifier).
		 @return		A pointer to the sprite vertex shader.
		 @throws		FormattedException
						Failed to create the sprite vertex shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< VertexShader > CreateSpriteVertexShader(
			const wstring &guid, ConstructorArgsT&&... args);
		
		/**
		 Creates a sprite pixel shader (if not existing).

		 @tparam		ConstructorArgsT
						The constructor argument types of the sprite pixel shader
						(excluding the type of the globally unique identifier).
		 @param[in]		guid
						A reference to the globally unique identifier of the
						sprite pixel shader.
		 @param[in]		args
						A reference to the constructor arguments for the sprite
						pixel shader (excluding the globally unique identifier).
		 @return		A pointer to the sprite pixel shader.
		 @throws		FormattedException
						Failed to create the sprite pixel shader.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< PixelShader > CreateSpritePixelShader(
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
		SharedPtr< SpriteFont > CreateSpriteFont(
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
		SharedPtr< Texture > CreateTexture(
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
		SharedPtr< VariableScript > CreateVariableScript(
			const wstring &guid, ConstructorArgsT&&... args);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the model descriptor resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, ModelDescriptor > > m_model_descriptor_resource_pool;

		/**
		 A pointer to the vertex shader resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, VertexShader > > m_vertex_shader_resource_pool;
		
		/**
		 A pointer to the pixel shader resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, PixelShader > > m_pixel_shader_resource_pool;

		/**
		 A pointer to the sprite font resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, SpriteFont > > m_font_resource_pool;

		/**
		 A pointer to the texture resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, Texture > > m_texture_resource_pool;

		/**
		 A pointer to the variable script resource pool of this resource manager.
		 */
		UniquePtr< ResourcePool< wstring, VariableScript > > m_variable_script_resource_pool;
	};

	//-------------------------------------------------------------------------
	// ResourceManager Indirect Methods
	//-------------------------------------------------------------------------

	/**
	 Returns the resource manager.

	 @pre			The current engine must be loaded.
	 @return		A pointer to the resource manager.
	 */
	ResourceManager *GetResourceManager() noexcept;

	/**
	 Creates a model descriptor (if not existing).

	 @pre			The current engine must be loaded.
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
	SharedPtr< ModelDescriptor > CreateModelDescriptor(
		const wstring &guid, ConstructorArgsT&&... args);
	
	/**
	 Creates a basic vertex shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the basic vertex shader
					(excluding the type of the globally unique identifier).
	 @param[in]		guid
					A reference to the globally unique identifier of the
					basic vertex shader.
	 @param[in]		args
					A reference to the constructor arguments for the basic
					vertex shader (excluding the globally unique identifier).
	 @return		A pointer to the basic vertex shader.
	 @throws		FormattedException
					Failed to create the basic vertex shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< VertexShader > CreateBasicVertexShader(
		const wstring &guid, ConstructorArgsT&&... args);
	
	/**
	 Creates a basic pixel shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the basic pixel shader
					(excluding the type of the globally unique identifier).
	 @param[in]		guid
					A reference to the globally unique identifier of the
					basic pixel shader.
	 @param[in]		args
					A reference to the constructor arguments for the basic
					pixel shader (excluding the globally unique identifier).
	 @return		A pointer to the basic pixel shader.
	 @throws		FormattedException
					Failed to create the basic pixel shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< PixelShader > CreateBasicPixelShader(
		const wstring &guid, ConstructorArgsT&&... args);

	/**
	 Creates a tsnm vertex shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the tsnm vertex shader
					(excluding the type of the globally unique identifier).
	 @param[in]		guid
					A reference to the globally unique identifier of the
					tsnm vertex shader.
	 @param[in]		args
					A reference to the constructor arguments for the tsnm
					vertex shader (excluding the globally unique identifier).
	 @return		A pointer to the tsnm vertex shader.
	 @throws		FormattedException
					Failed to create the tsnm vertex shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< VertexShader > CreateTSNMVertexShader(
		const wstring &guid, ConstructorArgsT&&... args);

	/**
	 Creates a tsnm pixel shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the tsnm pixel shader
					(excluding the type of the globally unique identifier).
	 @param[in]		guid
					A reference to the globally unique identifier of the
					tsnm pixel shader.
	 @param[in]		args
					A reference to the constructor arguments for the tsnm
					pixel shader (excluding the globally unique identifier).
	 @return		A pointer to the tsnm pixel shader.
	 @throws		FormattedException
					Failed to create the tsnm pixel shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< PixelShader > CreateTSNMPixelShader(
		const wstring &guid, ConstructorArgsT&&... args);
	
	/**
	 Creates a sprite vertex shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the sprite vertex shader
					(excluding the type of the globally unique identifier).
	 @param[in]		guid
					A reference to the globally unique identifier of the
					sprite vertex shader.
	 @param[in]		args
					A reference to the constructor arguments for the sprite
					vertex shader (excluding the globally unique identifier).
	 @return		A pointer to the sprite vertex shader.
	 @throws		FormattedException
					Failed to create the sprite vertex shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< VertexShader > CreateSpriteVertexShader(
		const wstring &guid, ConstructorArgsT&&... args);
	
	/**
	 Creates a sprite pixel shader (if not existing).

	 @pre			The current engine must be loaded.
	 @tparam		ConstructorArgsT
					The constructor argument types of the sprite pixel shader
					(excluding the type of the globally unique identifier).
	 @param[in]		guid
					A reference to the globally unique identifier of the
					sprite pixel shader.
	 @param[in]		args
					A reference to the constructor arguments for the sprite
					pixel shader (excluding the globally unique identifier).
	 @return		A pointer to the sprite pixel shader.
	 @throws		FormattedException
					Failed to create the sprite pixel shader.
	 */
	template< typename... ConstructorArgsT >
	SharedPtr< PixelShader > CreateSpritePixelShader(
		const wstring &guid, ConstructorArgsT&&... args);
	
	/**
	 Creates a sprite font (if not existing).

	 @pre			The current engine must be loaded.
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
	SharedPtr< SpriteFont > CreateSpriteFont(
		const wstring &guid, ConstructorArgsT&&... args);
	
	/**
	 Creates a texture (if not existing).

	 @pre			The current engine must be loaded.
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
	SharedPtr< Texture > CreateTexture(
		const wstring &guid, ConstructorArgsT&&... args);
	
	/**
	 Creates a variable script (if not existing).

	 @pre			The current engine must be loaded.
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
	SharedPtr< VariableScript > CreateVariableScript(
		const wstring &guid, ConstructorArgsT&&... args);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_manager.tpp"

#pragma endregion