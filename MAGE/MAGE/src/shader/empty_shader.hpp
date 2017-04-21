#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "shader\shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// EmptyVertexShader
	//-------------------------------------------------------------------------

	class EmptyVertexShader : public VertexShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit EmptyVertexShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &fname, const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements)
			: VertexShader(device, device_context, fname, input_element_desc, nb_input_elements) {}
		EmptyVertexShader(const EmptyVertexShader &vertex_shader) = delete;
		EmptyVertexShader(EmptyVertexShader &&vertex_shader) = default;
		virtual ~EmptyVertexShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		EmptyVertexShader &operator=(const EmptyVertexShader &vertex_shader) = delete;
		EmptyVertexShader &operator=(EmptyVertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void PrepareShading(const XMMATRIX &transform) const override final;
		virtual void PrepareShading(const Material &material, const LightBuffer &lighting, const TransformBuffer &transform_buffer) const override final;
	};

	//-------------------------------------------------------------------------
	// EmptyPixelShader
	//-------------------------------------------------------------------------

	class EmptyPixelShader : public PixelShader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit EmptyPixelShader(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &fname)
			: PixelShader(device, device_context, fname) {}
		EmptyPixelShader(const EmptyPixelShader &pixel_shader) = delete;
		EmptyPixelShader(EmptyPixelShader &&pixel_shader) = default;
		virtual ~EmptyPixelShader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		EmptyPixelShader &operator=(const EmptyPixelShader &pixel_shader) = delete;
		EmptyPixelShader &operator=(EmptyPixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void PrepareShading(ID3D11ShaderResourceView * const *texture) const override final;
		virtual void PrepareShading(const Material &material, const LightBuffer &lighting) const override final;
	};
}