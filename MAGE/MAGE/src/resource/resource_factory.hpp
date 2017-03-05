#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_manager.hpp"
#include "shader\shader.hpp"
#include "texture\texture.hpp"
#include "scripting\variable_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Resource Creation
	//-------------------------------------------------------------------------

	CombinedShader CreateLambertianShader();
	SharedPtr< Texture > CreateTexture(const wstring &fname);
	SharedPtr< VariableScript > CreateVariableScript(const wstring &fname);

	//-------------------------------------------------------------------------
	// ResourceFactory
	//-------------------------------------------------------------------------
	
	class ResourceFactory {

	public:

		ResourceFactory();
		virtual ~ResourceFactory() = default;

		SharedPtr< VertexShader > CreateLambertianVertexShader(const RenderingDevice &device);
		SharedPtr< PixelShader > CreateLambertianPixelShader(const RenderingDevice &device);
		SharedPtr< Texture > CreateTexture(const RenderingDevice &device, const wstring &fname);
		SharedPtr< VariableScript > CreateVariableScript(const wstring &fname);

	private:

		ResourceFactory(const ResourceFactory &resource_factory) = delete;
		ResourceFactory &operator=(const ResourceFactory &resource_factory) = delete;

		UniquePtr< ResourceManager< VertexShader > > m_vertex_shader_resource_manager;
		UniquePtr< ResourceManager< PixelShader > > m_pixel_shader_resource_manager;
		UniquePtr< ResourceManager< Texture > > m_texture_resource_manager;
		UniquePtr< ResourceManager< VariableScript > > m_variable_script_resource_manager;
	};
}