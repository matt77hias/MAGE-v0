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
	
	class ResourceFactory {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ResourceFactory();
		ResourceFactory(const ResourceFactory &resource_factory) = delete;
		ResourceFactory(ResourceFactory &&resource_factory) = default;
		virtual ~ResourceFactory();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ResourceFactory &operator=(const ResourceFactory &resource_factory) = delete;
		ResourceFactory &operator=(ResourceFactory &&resource_factory) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		template < typename VertexT >
		SharedPtr< ModelDescriptor > CreateModelDescriptor(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context, 
			const wstring &fname, const MeshDescriptor< VertexT > &desc);
		
		SharedPtr< VertexShader > CreateLambertianVertexShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SharedPtr< PixelShader > CreateLambertianPixelShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SharedPtr< VertexShader > CreateSpriteVertexShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SharedPtr< PixelShader > CreateSpritePixelShader(
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context);
		SharedPtr< SpriteFont > CreateFont(ID3D11Device2 *device, const wstring &fname,
			const SpriteFontDescriptor &desc);
		SharedPtr< Texture > CreateTexture(ID3D11Device2 *device, const wstring &fname);
		SharedPtr< VariableScript > CreateVariableScript(const wstring &fname, bool import);

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		UniquePtr< ResourcePool< wstring, ModelDescriptor > > m_model_descriptor_resource_pool;
		UniquePtr< ResourcePool< wstring, VertexShader > >    m_vertex_shader_resource_pool;
		UniquePtr< ResourcePool< wstring, PixelShader > >     m_pixel_shader_resource_pool;
		UniquePtr< ResourcePool< wstring, SpriteFont > >      m_font_resource_pool;
		UniquePtr< ResourcePool< wstring, Texture > >         m_texture_resource_pool;
		UniquePtr< ResourcePool< wstring, VariableScript > >  m_variable_script_resource_pool;
	};

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------

	ID3D11Device2 *GetRenderingDevice();
	ID3D11DeviceContext2 *GetRenderingDeviceContext();
	ResourceFactory *GetResourceFactory();
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.tpp"

#pragma endregion