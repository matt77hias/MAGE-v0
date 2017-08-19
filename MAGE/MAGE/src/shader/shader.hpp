#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"
#include "shader\compiled_shader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// VertexShader
	//-------------------------------------------------------------------------

	/**
	 A class of vertex shaders.
	 */
	class VertexShader : public Resource< VertexShader > {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the vertex shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		buffer
						A pointer to the constant buffer.
		 */
		static void BindConstantBuffer(UINT slot, ID3D11Buffer *buffer) noexcept {
			BindConstantBuffers(slot, 1, &buffer);
		}

		/**
		 Binds an array of constant buffers to the vertex shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
						- @a slot.
		 @pre			@a buffers points to an array containing at least 
						@a nb_buffers pointers to a constant buffer.	
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting constant buffers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		nb_buffers
						The number of constant buffers in the array (ranges from 
						0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
						- @a slot).
		 @param[in]		buffer
						A pointer to an array of constant buffers.
		 */
		static void BindConstantBuffers(UINT slot, UINT nb_buffers, ID3D11Buffer * const *buffers) noexcept {
			GetRenderingDeviceContext()->VSSetConstantBuffers(slot, nb_buffers, buffers);
		}
		
		/**
		 Binds a shader resource view to the vertex shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		srv
						A pointer to the shader resource view.
		 */
		static void BindSRV(UINT slot, ID3D11ShaderResourceView *srv) noexcept {
			BindSRVs(slot, 1, &srv);
		}

		/**
		 Binds an array of shader resource views to the vertex shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
						- @a slot.
		 @pre			@a srvs points to an array containing at least 
						@a nb_srvs pointers to a shader resource view.				
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting shader resource views to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		nb_srvs
						The number of shader resource views in the array. Up 
						to a maximum of 128 slots are available for shader 
						resource views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		srvs
						A pointer to an array of shader resource views.
		 */
		static void BindSRVs(UINT slot, UINT nb_srvs, ID3D11ShaderResourceView * const *srvs) noexcept {
			GetRenderingDeviceContext()->VSSetShaderResources(slot, nb_srvs, srvs);
		}

		/**
		 Binds a sampler to the vertex shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the sampler to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		sampler
						A pointer to the sampler.
		 */
		static void BindSampler(UINT slot, ID3D11SamplerState *sampler) noexcept {
			BindSamplers(slot, 1, &sampler);
		}
		
		/**
		 Binds an array of samplers to the vertex shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
						- @a slot.
		 @pre			@a samplers points to an array containing at least 
						@a nb_samplers pointers to a sampler.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting samplers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		nb_samplers
						The number of samplers in the array. Each pipeline stage 
						has a total of 16 sampler slots available (ranges from 
						0 to @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - @a slot).
		 @param[in]		samplers
						A pointer to an array of samplers.
		 */
		static void BindSamplers(UINT slot, UINT nb_samplers, ID3D11SamplerState * const *samplers) noexcept {
			GetRenderingDeviceContext()->VSSetSamplers(slot, nb_samplers, samplers);
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a vertex shader.

		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_shader
						A pointer to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		 */
		explicit VertexShader(const wstring &guid,
			const CompiledShader *compiled_shader,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);

		/**
		 Constructs a vertex shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_shader
						A pointer to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to initialize this vertex shader.
		*/
		explicit VertexShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledShader *compiled_shader, 
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
		
		/**
		 Constructs a vertex shader from the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 */
		VertexShader(const VertexShader &vertex_shader) = delete;
		
		/**
		 Constructs a vertex shader by moving the given vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to move.
		 */
		VertexShader(VertexShader &&vertex_shader);
		
		/**
		 Destructs this vertex shader.
		 */
		virtual ~VertexShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given vertex shader to this vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 @return		A reference to the copy of the given vertex shader
						(i.e. this vertex shader).
		 */
		VertexShader &operator=(const VertexShader &vertex_shader) = delete;

		/**
		 Moves the given vertex shader to this vertex shader.

		 @param[in]		vertex_shader
						A reference to the vertex shader to copy.
		 @return		A reference to the moved vertex shader
						(i.e. this vertex shader).
		 */
		VertexShader &operator=(VertexShader &&vertex_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this vertex shader.
		 */
		void BindShader() const noexcept {
			m_device_context->IASetInputLayout(m_vertex_layout.Get());
			m_device_context->VSSetShader(m_vertex_shader.Get(), nullptr, 0);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this vertex shader.

		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @pre			@a input_element_desc is not equal to @c nullptr.
		 @pre			The array pointed to by @a input_element_desc
						contains @a nb_input_elements elements.
		 @param[in]		compiled_shader
						A pointer to the compiled vertex shader.
		 @param[in]		input_element_desc
						A pointer the input element descriptors.
		 @param[in]		nb_input_elements
						The number of elements contained in the
						given input element descriptor.
		 @throws		FormattedException
						Failed to setup this vertex shader.
		 */
		void SetupShader(const CompiledShader *compiled_shader,
			const D3D11_INPUT_ELEMENT_DESC *input_element_desc, uint32_t nb_input_elements);
			
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this vertex shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this vertex shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the vertex shader of this vertex shader.
		 */
		ComPtr< ID3D11VertexShader > m_vertex_shader;

		/**
		 A pointer to the input layout of this vertex shader.
		 */
		ComPtr< ID3D11InputLayout >  m_vertex_layout;
	};
	
	//-------------------------------------------------------------------------
	// HullShader
	//-------------------------------------------------------------------------

	/**
	 A class of hull shaders.
	 */
	class HullShader : public Resource< HullShader > {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the hull shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		buffer
						A pointer to the constant buffer.
		 */
		static void BindConstantBuffer(UINT slot, ID3D11Buffer *buffer) noexcept {
			BindConstantBuffers(slot, 1, &buffer);
		}

		/**
		 Binds an array of constant buffers to the hull shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
						- @a slot.
		 @pre			@a buffers points to an array containing at least 
						@a nb_buffers pointers to a constant buffer.	
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting constant buffers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		nb_buffers
						The number of constant buffers in the array (ranges from 
						0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
						- @a slot).
		 @param[in]		buffer
						A pointer to an array of constant buffers.
		 */
		static void BindConstantBuffers(UINT slot, UINT nb_buffers, ID3D11Buffer * const *buffers) noexcept {
			GetRenderingDeviceContext()->HSSetConstantBuffers(slot, nb_buffers, buffers);
		}
		
		/**
		 Binds a shader resource view to the hull shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		srv
						A pointer to the shader resource view.
		 */
		static void BindSRV(UINT slot, ID3D11ShaderResourceView *srv) noexcept {
			BindSRVs(slot, 1, &srv);
		}

		/**
		 Binds an array of shader resource views to the hull shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
						- @a slot.
		 @pre			@a srvs points to an array containing at least 
						@a nb_srvs pointers to a shader resource view.				
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting shader resource views to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		nb_srvs
						The number of shader resource views in the array. Up 
						to a maximum of 128 slots are available for shader 
						resource views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		srvs
						A pointer to an array of shader resource views.
		 */
		static void BindSRVs(UINT slot, UINT nb_srvs, ID3D11ShaderResourceView * const *srvs) noexcept {
			GetRenderingDeviceContext()->HSSetShaderResources(slot, nb_srvs, srvs);
		}

		/**
		 Binds a sampler to the hull shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the sampler to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		sampler
						A pointer to the sampler.
		 */
		static void BindSampler(UINT slot, ID3D11SamplerState *sampler) noexcept {
			BindSamplers(slot, 1, &sampler);
		}
		
		/**
		 Binds an array of samplers to the hull shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
						- @a slot.
		 @pre			@a samplers points to an array containing at least 
						@a nb_samplers pointers to a sampler.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting samplers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		nb_samplers
						The number of samplers in the array. Each pipeline stage 
						has a total of 16 sampler slots available (ranges from 
						0 to @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - @a slot).
		 @param[in]		samplers
						A pointer to an array of samplers.
		 */
		static void BindSamplers(UINT slot, UINT nb_samplers, ID3D11SamplerState * const *samplers) noexcept {
			GetRenderingDeviceContext()->HSSetSamplers(slot, nb_samplers, samplers);
		}
		
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a hull shader.

		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_shader
						A pointer to the compiled hull shader.
		 @throws		FormattedException
						Failed to initialize this hull shader.
		 */
		explicit HullShader(const wstring &guid, 
			const CompiledShader *compiled_shader);

		/**
		 Constructs a hull shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_shader
						A pointer to the compiled hull shader.
		 @throws		FormattedException
						Failed to initialize this hull shader.
		 */
		explicit HullShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledShader *compiled_shader);
		
		/**
		 Constructs a hull shader from the given hull shader.

		 @param[in]		hull_shader
						A reference to the hull shader to copy.
		 */
		HullShader(const HullShader &hull_shader) = delete;

		/**
		 Constructs a hull shader by moving the given hull shader.

		 @param[in]		hull_shader
						A reference to the hull shader to move.
		 */
		HullShader(HullShader &&hull_shader);

		/**
		 Destructs this hull shader.
		 */
		virtual ~HullShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given hull shader to this hull shader.

		 @param[in]		hull_shader
						A reference to the hull shader to copy.
		 @return		A reference to the copy of the given hull shader
						(i.e. this hull shader).
		 */
		HullShader &operator=(const HullShader &hull_shader) = delete;

		/**
		 Moves the given hull shader to this hull shader.

		 @param[in]		hull_shader
						A reference to the hull shader to move.
		 @return		A reference to the moved hull shader
						(i.e. this hull shader).
		 */
		HullShader &operator=(HullShader &&hull_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this hull shader.
		 */
		void BindShader() const noexcept {
			m_device_context->HSSetShader(m_hull_shader.Get(), nullptr, 0);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this hull shader.

		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		compiled_shader
						A pointer to the compiled hull shader.
		 @throws		FormattedException
						Failed to setup this hull shader.
		 */
		void SetupShader(const CompiledShader *compiled_shader);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this hull shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this hull shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the hull shader of this hull shader.
		 */
		ComPtr< ID3D11HullShader > m_hull_shader;
	};
	
	//-------------------------------------------------------------------------
	// DomainShader
	//-------------------------------------------------------------------------

	/**
	 A class of domain shaders.
	 */
	class DomainShader : public Resource< DomainShader > {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the domain shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		buffer
						A pointer to the constant buffer.
		 */
		static void BindConstantBuffer(UINT slot, ID3D11Buffer *buffer) noexcept {
			BindConstantBuffers(slot, 1, &buffer);
		}

		/**
		 Binds an array of constant buffers to the domain shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
						- @a slot.
		 @pre			@a buffers points to an array containing at least 
						@a nb_buffers pointers to a constant buffer.	
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting constant buffers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		nb_buffers
						The number of constant buffers in the array (ranges from 
						0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
						- @a slot).
		 @param[in]		buffer
						A pointer to an array of constant buffers.
		 */
		static void BindConstantBuffers(UINT slot, UINT nb_buffers, ID3D11Buffer * const *buffers) noexcept {
			GetRenderingDeviceContext()->DSSetConstantBuffers(slot, nb_buffers, buffers);
		}
		
		/**
		 Binds a shader resource view to the domain shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		srv
						A pointer to the shader resource view.
		 */
		static void BindSRV(UINT slot, ID3D11ShaderResourceView *srv) noexcept {
			BindSRVs(slot, 1, &srv);
		}

		/**
		 Binds an array of shader resource views to the domain shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
						- @a slot.
		 @pre			@a srvs points to an array containing at least 
						@a nb_srvs pointers to a shader resource view.				
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting shader resource views to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		nb_srvs
						The number of shader resource views in the array. Up 
						to a maximum of 128 slots are available for shader 
						resource views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		srvs
						A pointer to an array of shader resource views.
		 */
		static void BindSRVs(UINT slot, UINT nb_srvs, ID3D11ShaderResourceView * const *srvs) noexcept {
			GetRenderingDeviceContext()->DSSetShaderResources(slot, nb_srvs, srvs);
		}

		/**
		 Binds a sampler to the domain shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the sampler to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		sampler
						A pointer to the sampler.
		 */
		static void BindSampler(UINT slot, ID3D11SamplerState *sampler) noexcept {
			BindSamplers(slot, 1, &sampler);
		}
		
		/**
		 Binds an array of samplers to the domain shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
						- @a slot.
		 @pre			@a samplers points to an array containing at least 
						@a nb_samplers pointers to a sampler.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting samplers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		nb_samplers
						The number of samplers in the array. Each pipeline stage 
						has a total of 16 sampler slots available (ranges from 
						0 to @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - @a slot).
		 @param[in]		samplers
						A pointer to an array of samplers.
		 */
		static void BindSamplers(UINT slot, UINT nb_samplers, ID3D11SamplerState * const *samplers) noexcept {
			GetRenderingDeviceContext()->DSSetSamplers(slot, nb_samplers, samplers);
		}
		
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a domain shader.

		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_shader
						A pointer to the compiled domain shader.
		 @throws		FormattedException
						Failed to initialize this domain shader.
		 */
		explicit DomainShader(const wstring &guid, 
			const CompiledShader *compiled_shader);

		/**
		 Constructs a domain shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_shader
						A pointer to the compiled domain shader.
		 @throws		FormattedException
						Failed to initialize this domain shader.
		 */
		explicit DomainShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledShader *compiled_shader);
		
		/**
		 Constructs a domain shader from the given domain shader.

		 @param[in]		domain_shader
						A reference to the domain shader to copy.
		 */
		DomainShader(const DomainShader &domain_shader) = delete;

		/**
		 Constructs a domain shader by moving the given domain shader.

		 @param[in]		domain_shader
						A reference to the domain shader to move.
		 */
		DomainShader(DomainShader &&domain_shader);

		/**
		 Destructs this domain shader.
		 */
		virtual ~DomainShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given domain shader to this domain shader.

		 @param[in]		domain_shader
						A reference to the domain shader to copy.
		 @return		A reference to the copy of the given domain shader
						(i.e. this domain shader).
		 */
		DomainShader &operator=(const DomainShader &domain_shader) = delete;

		/**
		 Moves the given domain shader to this domain shader.

		 @param[in]		domain_shader
						A reference to the domain shader to move.
		 @return		A reference to the moved domain shader
						(i.e. this domain shader).
		 */
		DomainShader &operator=(DomainShader &&domain_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this domain shader.
		 */
		void BindShader() const noexcept {
			m_device_context->DSSetShader(m_domain_shader.Get(), nullptr, 0);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this domain shader.

		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		compiled_shader
						A pointer to the compiled domain shader.
		 @throws		FormattedException
						Failed to setup this domain shader.
		 */
		void SetupShader(const CompiledShader *compiled_shader);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this domain shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this domain shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the domain shader of this domain shader.
		 */
		ComPtr< ID3D11DomainShader > m_domain_shader;
	};
	
	//-------------------------------------------------------------------------
	// GeometryShader
	//-------------------------------------------------------------------------

	/**
	 A class of geometry shaders.
	 */
	class GeometryShader : public Resource< GeometryShader > {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the geometry shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		buffer
						A pointer to the constant buffer.
		 */
		static void BindConstantBuffer(UINT slot, ID3D11Buffer *buffer) noexcept {
			BindConstantBuffers(slot, 1, &buffer);
		}

		/**
		 Binds an array of constant buffers to the geometry shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
						- @a slot.
		 @pre			@a buffers points to an array containing at least 
						@a nb_buffers pointers to a constant buffer.	
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting constant buffers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		nb_buffers
						The number of constant buffers in the array (ranges from 
						0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
						- @a slot).
		 @param[in]		buffer
						A pointer to an array of constant buffers.
		 */
		static void BindConstantBuffers(UINT slot, UINT nb_buffers, ID3D11Buffer * const *buffers) noexcept {
			GetRenderingDeviceContext()->GSSetConstantBuffers(slot, nb_buffers, buffers);
		}
		
		/**
		 Binds a shader resource view to the geometry shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		srv
						A pointer to the shader resource view.
		 */
		static void BindSRV(UINT slot, ID3D11ShaderResourceView *srv) noexcept {
			BindSRVs(slot, 1, &srv);
		}

		/**
		 Binds an array of shader resource views to the geometry shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
						- @a slot.
		 @pre			@a srvs points to an array containing at least 
						@a nb_srvs pointers to a shader resource view.				
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting shader resource views to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		nb_srvs
						The number of shader resource views in the array. Up 
						to a maximum of 128 slots are available for shader 
						resource views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		srvs
						A pointer to an array of shader resource views.
		 */
		static void BindSRVs(UINT slot, UINT nb_srvs, ID3D11ShaderResourceView * const *srvs) noexcept {
			GetRenderingDeviceContext()->GSSetShaderResources(slot, nb_srvs, srvs);
		}

		/**
		 Binds a sampler to the geometry shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the sampler to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		sampler
						A pointer to the sampler.
		 */
		static void BindSampler(UINT slot, ID3D11SamplerState *sampler) noexcept {
			BindSamplers(slot, 1, &sampler);
		}
		
		/**
		 Binds an array of samplers to the geometry shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
						- @a slot.
		 @pre			@a samplers points to an array containing at least 
						@a nb_samplers pointers to a sampler.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting samplers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		nb_samplers
						The number of samplers in the array. Each pipeline stage 
						has a total of 16 sampler slots available (ranges from 
						0 to @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - @a slot).
		 @param[in]		samplers
						A pointer to an array of samplers.
		 */
		static void BindSamplers(UINT slot, UINT nb_samplers, ID3D11SamplerState * const *samplers) noexcept {
			GetRenderingDeviceContext()->GSSetSamplers(slot, nb_samplers, samplers);
		}
		
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a geometry shader.

		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_shader
						A pointer to the compiled geometry shader.
		 @throws		FormattedException
						Failed to initialize this geometry shader.
		 */
		explicit GeometryShader(const wstring &guid, 
			const CompiledShader *compiled_shader);

		/**
		 Constructs a geometry shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_shader
						A pointer to the compiled geometry shader.
		 @throws		FormattedException
						Failed to initialize this geometry shader.
		 */
		explicit GeometryShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledShader *compiled_shader);
		
		/**
		 Constructs a geometry shader from the given geometry shader.

		 @param[in]		geometry_shader
						A reference to the geometry shader to copy.
		 */
		GeometryShader(const GeometryShader &geometry_shader) = delete;

		/**
		 Constructs a geometry shader by moving the given geometry shader.

		 @param[in]		geometry_shader
						A reference to the geometry shader to move.
		 */
		GeometryShader(GeometryShader &&geometry_shader);

		/**
		 Destructs this geometry shader.
		 */
		virtual ~GeometryShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given geometry shader to this geometry shader.

		 @param[in]		geometry_shader
						A reference to the geometry shader to copy.
		 @return		A reference to the copy of the given geometry shader
						(i.e. this geometry shader).
		 */
		GeometryShader &operator=(const GeometryShader &geometry_shader) = delete;

		/**
		 Moves the given geometry shader to this geometry shader.

		 @param[in]		geometry_shader
						A reference to the geometry shader to move.
		 @return		A reference to the moved geometry shader
						(i.e. this geometry shader).
		 */
		GeometryShader &operator=(GeometryShader &&geometry_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this geometry shader.
		 */
		void BindShader() const noexcept {
			m_device_context->GSSetShader(m_geometry_shader.Get(), nullptr, 0);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this geometry shader.

		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		compiled_shader
						A pointer to the compiled geometry shader.
		 @throws		FormattedException
						Failed to setup this geometry shader.
		 */
		void SetupShader(const CompiledShader *compiled_shader);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this geometry shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this geometry shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the geometry shader of this geometry shader.
		 */
		ComPtr< ID3D11GeometryShader > m_geometry_shader;
	};
	
	//-------------------------------------------------------------------------
	// PixelShader
	//-------------------------------------------------------------------------

	/**
	 A class of pixel shaders.
	 */
	class PixelShader : public Resource< PixelShader > {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the pixel shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		buffer
						A pointer to the constant buffer.
		 */
		static void BindConstantBuffer(UINT slot, ID3D11Buffer *buffer) noexcept {
			BindConstantBuffers(slot, 1, &buffer);
		}

		/**
		 Binds an array of constant buffers to the pixel shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
						- @a slot.
		 @pre			@a buffers points to an array containing at least 
						@a nb_buffers pointers to a constant buffer.	
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting constant buffers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		nb_buffers
						The number of constant buffers in the array (ranges from 
						0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
						- @a slot).
		 @param[in]		buffer
						A pointer to an array of constant buffers.
		 */
		static void BindConstantBuffers(UINT slot, UINT nb_buffers, ID3D11Buffer * const *buffers) noexcept {
			GetRenderingDeviceContext()->PSSetConstantBuffers(slot, nb_buffers, buffers);
		}
		
		/**
		 Binds a shader resource view to the pixel shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		srv
						A pointer to the shader resource view.
		 */
		static void BindSRV(UINT slot, ID3D11ShaderResourceView *srv) noexcept {
			BindSRVs(slot, 1, &srv);
		}

		/**
		 Binds an array of shader resource views to the pixel shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
						- @a slot.
		 @pre			@a srvs points to an array containing at least 
						@a nb_srvs pointers to a shader resource view.				
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting shader resource views to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		nb_srvs
						The number of shader resource views in the array. Up 
						to a maximum of 128 slots are available for shader 
						resource views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		srvs
						A pointer to an array of shader resource views.
		 */
		static void BindSRVs(UINT slot, UINT nb_srvs, ID3D11ShaderResourceView * const *srvs) noexcept {
			GetRenderingDeviceContext()->PSSetShaderResources(slot, nb_srvs, srvs);
		}

		/**
		 Binds a sampler to the pixel shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the sampler to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		sampler
						A pointer to the sampler.
		 */
		static void BindSampler(UINT slot, ID3D11SamplerState *sampler) noexcept {
			BindSamplers(slot, 1, &sampler);
		}
		
		/**
		 Binds an array of samplers to the pixel shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
						- @a slot.
		 @pre			@a samplers points to an array containing at least 
						@a nb_samplers pointers to a sampler.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting samplers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		nb_samplers
						The number of samplers in the array. Each pipeline stage 
						has a total of 16 sampler slots available (ranges from 
						0 to @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - @a slot).
		 @param[in]		samplers
						A pointer to an array of samplers.
		 */
		static void BindSamplers(UINT slot, UINT nb_samplers, ID3D11SamplerState * const *samplers) noexcept {
			GetRenderingDeviceContext()->PSSetSamplers(slot, nb_samplers, samplers);
		}
		
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a pixel shader.

		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_shader
						A pointer to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit PixelShader(const wstring &guid, 
			const CompiledShader *compiled_shader);

		/**
		 Constructs a pixel shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_shader
						A pointer to the compiled pixel shader.
		 @throws		FormattedException
						Failed to initialize this pixel shader.
		 */
		explicit PixelShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledShader *compiled_shader);
		
		/**
		 Constructs a pixel shader from the given pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to copy.
		 */
		PixelShader(const PixelShader &pixel_shader) = delete;

		/**
		 Constructs a pixel shader by moving the given pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to move.
		 */
		PixelShader(PixelShader &&pixel_shader);

		/**
		 Destructs this pixel shader.
		 */
		virtual ~PixelShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given pixel shader to this pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to copy.
		 @return		A reference to the copy of the given pixel shader
						(i.e. this pixel shader).
		 */
		PixelShader &operator=(const PixelShader &pixel_shader) = delete;

		/**
		 Moves the given pixel shader to this pixel shader.

		 @param[in]		pixel_shader
						A reference to the pixel shader to move.
		 @return		A reference to the moved pixel shader
						(i.e. this pixel shader).
		 */
		PixelShader &operator=(PixelShader &&pixel_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this pixel shader.
		 */
		void BindShader() const noexcept {
			m_device_context->PSSetShader(m_pixel_shader.Get(), nullptr, 0);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this pixel shader.

		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		compiled_shader
						A pointer to the compiled pixel shader.
		 @throws		FormattedException
						Failed to setup this pixel shader.
		 */
		void SetupShader(const CompiledShader *compiled_shader);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this pixel shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this pixel shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the pixel shader of this pixel shader.
		 */
		ComPtr< ID3D11PixelShader > m_pixel_shader;
	};
	
	//-------------------------------------------------------------------------
	// ComputeShader
	//-------------------------------------------------------------------------

	/**
	 A class of compute shaders.
	 */
	class ComputeShader : public Resource< ComputeShader > {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		buffer
						A pointer to the constant buffer.
		 */
		static void BindConstantBuffer(UINT slot, ID3D11Buffer *buffer) noexcept {
			BindConstantBuffers(slot, 1, &buffer);
		}

		/**
		 Binds an array of constant buffers to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
						- @a slot.
		 @pre			@a buffers points to an array containing at least 
						@a nb_buffers pointers to a constant buffer.	
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting constant buffers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		nb_buffers
						The number of constant buffers in the array (ranges from 
						0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
						- @a slot).
		 @param[in]		buffer
						A pointer to an array of constant buffers.
		 */
		static void BindConstantBuffers(UINT slot, UINT nb_buffers, ID3D11Buffer * const *buffers) noexcept {
			GetRenderingDeviceContext()->CSSetConstantBuffers(slot, nb_buffers, buffers);
		}
		
		/**
		 Binds a shader resource view to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		srv
						A pointer to the shader resource view.
		 */
		static void BindSRV(UINT slot, ID3D11ShaderResourceView *srv) noexcept {
			BindSRVs(slot, 1, &srv);
		}

		/**
		 Binds an array of shader resource views to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
						- @a slot.
		 @pre			@a srvs points to an array containing at least 
						@a nb_srvs pointers to a shader resource view.				
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting shader resource views to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		nb_srvs
						The number of shader resource views in the array. Up 
						to a maximum of 128 slots are available for shader 
						resource views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		srvs
						A pointer to an array of shader resource views.
		 */
		static void BindSRVs(UINT slot, UINT nb_srvs, ID3D11ShaderResourceView * const *srvs) noexcept {
			GetRenderingDeviceContext()->CSSetShaderResources(slot, nb_srvs, srvs);
		}

		/**
		 Binds an unordered access view to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_1_UAV_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting unordered access views to (ranges from 0 to 
						@c D3D11_1_UAV_SLOT_COUNT - 1).
		 @param[in]		uav
						A pointer to the unordered access view.
		 */
		static void BindUAV(UINT slot, ID3D11UnorderedAccessView *uav) noexcept {
			BindUAVs(slot, 1, &uav);
		}

		/**
		 Binds an unordered access view created with 
		 @c D3D11_BUFFER_UAV_FLAG_APPEND or @c D3D11_BUFFER_UAV_FLAG_COUNTER
		 to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_1_UAV_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting unordered access views to (ranges from 0 to 
						@c D3D11_1_UAV_SLOT_COUNT - 1).
		 @param[in]		uav
						A pointer to the unordered access view.
		 @param[in]		initial_count
						The append and consume buffer offsets.
						A value of -1 indicates to keep the current offset.
		 */
		static void BindUAV(UINT slot, ID3D11UnorderedAccessView *uav, UINT initial_count) noexcept {
			BindUAVs(slot, 1, &uav, &initial_count);
		}

		/**
		 Binds an array of unordered access views to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_1_UAV_SLOT_COUNT.
		 @pre			@a nb_uavs < @c D3D11_1_UAV_SLOT_COUNT - @a slot.
		 @pre			@a uavs points to an array containing at least 
						@a nb_uavs pointers to an unordered access view.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting unordered access views to (ranges from 0 to 
						@c D3D11_1_UAV_SLOT_COUNT - 1).
		 @param[in]		nb_uavs
						The number of unordered access views in the array. Up 
						to a maximum of 64 slots are available for unordered 
						access views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		uavs
						A pointer to an array of unordered access views.
		 */
		static void BindUAVs(UINT slot, UINT nb_uavs, ID3D11UnorderedAccessView * const *uavs) noexcept {
			GetRenderingDeviceContext()->CSSetUnorderedAccessViews(slot, nb_uavs, uavs, nullptr);
		}

		/**
		 Binds an array of unordered access views created with 
		 @c D3D11_BUFFER_UAV_FLAG_APPEND or @c D3D11_BUFFER_UAV_FLAG_COUNTER
		 to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_1_UAV_SLOT_COUNT.
		 @pre			@a nb_uavs < @c D3D11_1_UAV_SLOT_COUNT - @a slot.
		 @pre			@a uavs points to an array containing at least 
						@a nb_uavs pointers to an unordered access view.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting unordered access views to (ranges from 0 
						to @c D3D11_1_UAV_SLOT_COUNT - 1).
		 @param[in]		nb_uavs
						The number of unordered access views in the array. Up 
						to a maximum of 64 slots are available for unordered 
						access views (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - @a slot).
		 @param[in]		uavs
						A pointer to an array of unordered access views.
		 @param[in]		initial_counts
						A pointer to an array of append and consume buffer offsets. 
						A value of -1 indicates to keep the current offset.
		 */
		static void BindUAVs(UINT slot, UINT nb_uavs, ID3D11UnorderedAccessView * const *uavs, 
			const UINT *initial_counts) noexcept {
			GetRenderingDeviceContext()->CSSetUnorderedAccessViews(slot, nb_uavs, uavs, initial_counts);
		}

		/**
		 Binds a sampler to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the sampler to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		sampler
						A pointer to the sampler.
		 */
		static void BindSampler(UINT slot, ID3D11SamplerState *sampler) noexcept {
			BindSamplers(slot, 1, &sampler);
		}
		
		/**
		 Binds an array of samplers to the compute shader.
		 
		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
						- @a slot.
		 @pre			@a samplers points to an array containing at least 
						@a nb_samplers pointers to a sampler.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting samplers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		nb_samplers
						The number of samplers in the array. Each pipeline stage 
						has a total of 16 sampler slots available (ranges from 
						0 to @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - @a slot).
		 @param[in]		samplers
						A pointer to an array of samplers.
		 */
		static void BindSamplers(UINT slot, UINT nb_samplers, ID3D11SamplerState * const *samplers) noexcept {
			GetRenderingDeviceContext()->CSSetSamplers(slot, nb_samplers, samplers);
		}
		
		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a compute shader.

		 @pre			The rendering device context associated with the 
						current engine must be loaded.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		compiled_shader
						A pointer to the compiled compute shader.
		 @throws		FormattedException
						Failed to initialize this compute shader.
		 */
		explicit ComputeShader(const wstring &guid, 
			const CompiledShader *compiled_shader);

		/**
		 Constructs a compute shader.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		guid
						A reference to the globally unique identifier.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		compiled_shader
						A pointer to the compiled compute shader.
		 @throws		FormattedException
						Failed to initialize this compute shader.
		 */
		explicit ComputeShader(const wstring &guid,
			ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const CompiledShader *compiled_shader);
		
		/**
		 Constructs a compute shader from the given compute shader.

		 @param[in]		compute_shader
						A reference to the compute shader to copy.
		 */
		ComputeShader(const ComputeShader &compute_shader) = delete;

		/**
		 Constructs a compute shader by moving the given compute shader.

		 @param[in]		compute_shader
						A reference to the compute shader to move.
		 */
		ComputeShader(ComputeShader &&compute_shader);

		/**
		 Destructs this compute shader.
		 */
		virtual ~ComputeShader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given compute shader to this compute shader.

		 @param[in]		compute_shader
						A reference to the compute shader to copy.
		 @return		A reference to the copy of the given compute shader
						(i.e. this compute shader).
		 */
		ComputeShader &operator=(const ComputeShader &compute_shader) = delete;

		/**
		 Moves the given compute shader to this compute shader.

		 @param[in]		compute_shader
						A reference to the compute shader to move.
		 @return		A reference to the moved compute shader
						(i.e. this compute shader).
		 */
		ComputeShader &operator=(ComputeShader &&compute_shader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds this compute shader.
		 */
		void BindShader() const noexcept {
			m_device_context->CSSetShader(m_compute_shader.Get(), nullptr, 0);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up this compute shader.

		 @pre			@a compiled_shader is not equal to @c nullptr.
		 @param[in]		compiled_shader
						A pointer to the compiled compute shader.
		 @throws		FormattedException
						Failed to setup this compute shader.
		 */
		void SetupShader(const CompiledShader *compiled_shader);
		
		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the device of this compute shader.
		 */
		ID3D11Device2 * const m_device;

		/**
		 A pointer to the device context of this compute shader.
		 */
		ID3D11DeviceContext2 * const m_device_context;

		/**
		 A pointer to the compute shader of this compute shader.
		 */
		ComPtr< ID3D11ComputeShader > m_compute_shader;
	};
}