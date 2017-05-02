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

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		fname
						A reference to the filename.
		 @param[in]		desc
						A reference to the mesh descriptor.
		 @throws		FormattedException
						Failed to create the model descriptor.
		 */
		template < typename VertexT >
		SharedPtr< ModelDescriptor > CreateModelDescriptor(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context, 
			const wstring &fname, const MeshDescriptor< VertexT > &desc);
		
		/**
		 Creates a lambertian vertex shader (if not existing).

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to create the lambertian vertex shader.
		 */
		SharedPtr< VertexShader > CreateLambertianVertexShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Creates a lambertian pixel shader (if not existing).

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to create the lambertian pixel shader.
		 */
		SharedPtr< PixelShader > CreateLambertianPixelShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Creates a sprite vertex shader (if not existing).

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to create the sprite vertex shader.
		 */
		SharedPtr< VertexShader > CreateSpriteVertexShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Creates a sprite pixel shader (if not existing).

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @throws		FormattedException
						Failed to create the sprite pixel shader.
		 */
		SharedPtr< PixelShader > CreateSpritePixelShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		
		/**
		 Creates a sprite font (if not existing).

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		fname
						A reference to the filename.
		 @param[in]		desc
						A reference to the sprite font descriptor.
		 @return		A pointer to the created sprite font.
		 @throws		FormattedException
						Failed to create the sprite font.
		 */
		SharedPtr< SpriteFont > CreateFont(ID3D11Device2 *device, const wstring &fname,
			const SpriteFontDescriptor &desc);
		
		/**
		 Creates a texture (if not existing).

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		fname
						A reference to the filename.
		 @return		A pointer to the created texture.
		 @throws		FormattedException
						Failed to create the texture.
		 */
		SharedPtr< Texture > CreateTexture(ID3D11Device2 *device, const wstring &fname);
		
		/**
		 Creates a variable script (if not existing).

		 @param[in]		fname
						A reference to the filename of the variable script.
		 @param[in]		import
						Flag indicating whether the variables of the variable script
						need to be imported.
		 @return		A pointer to the variable script.
		 @throws		FormattedException
						Failed to import the variable script from file
						(only possible if @a import is equal to @c true).
		 */
		SharedPtr< VariableScript > CreateVariableScript(const wstring &fname, bool import);

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
	// Resource Creation
	//-------------------------------------------------------------------------

	/**
	 Returns the rendering device.

	 @pre			The current engine must be loaded.
	 @return		A pointer to the rendering device.
	 */
	ID3D11Device2 *GetRenderingDevice();

	/**
	 Returns the rendering device context.

	 @pre			The current engine must be loaded.
	 @return		A pointer to the rendering device context.
	 */
	ID3D11DeviceContext2 *GetRenderingDeviceContext();

	/**
	 Returns the resource factory.

	 @pre			The current engine must be loaded.
	 @return		A pointer to the resource factory.
	 */
	ResourceFactory *GetResourceFactory();
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.tpp"

#pragma endregion