#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// IA
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// VS
	//-------------------------------------------------------------------------

	/**
	 The vertex shader stage.
	 */
	struct VS final {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the vertex shader stage.
		 
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
			ID3D11Buffer * const buffers[1] = { buffer };
			BindConstantBuffers(slot, 1, buffers);
		}

		/**
		 Binds an array of constant buffers to the vertex shader stage.
		 
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
		 Binds a shader resource view to the vertex shader stage.
		 
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
			ID3D11ShaderResourceView * const srvs[1] = { srv };
			BindSRVs(slot, 1, srvs);
		}

		/**
		 Binds an array of shader resource views to the vertex shader stage.
		 
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
		 Binds a sampler to the vertex shader stage.
		 
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
			ID3D11SamplerState * const samplers[1] = { sampler };
			BindSamplers(slot, 1, samplers);
		}
		
		/**
		 Binds an array of samplers to the vertex shader stage.
		 
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
		// Assignment Operators
		//---------------------------------------------------------------------

		VS &operator=(const VS &vs) = delete;
		VS &operator=(VS &&vs) = delete;
		
	private:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		VS() = delete;
		VS(const VS &vs) = delete;
		VS(VS &&vs) = delete;
		~VS() = delete;
	};
	
	//-------------------------------------------------------------------------
	// HS
	//-------------------------------------------------------------------------

	/**
	 The hull shader stage.
	 */
	struct HS final {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the hull shader stage.
		 
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
			ID3D11Buffer * const buffers[1] = { buffer };
			BindConstantBuffers(slot, 1, buffers);
		}

		/**
		 Binds an array of constant buffers to the hull shader stage.
		 
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
		 Binds a shader resource view to the hull shader stage.
		 
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
			ID3D11ShaderResourceView * const srvs[1] = { srv };
			BindSRVs(slot, 1, srvs);
		}

		/**
		 Binds an array of shader resource views to the hull shader stage.
		 
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
		 Binds a sampler to the hull shader stage.
		 
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
			ID3D11SamplerState * const samplers[1] = { sampler };
			BindSamplers(slot, 1, samplers);
		}
		
		/**
		 Binds an array of samplers to the hull shader stage.
		 
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
		// Assignment Operators
		//---------------------------------------------------------------------

		HS &operator=(const HS &hs) = delete;
		HS &operator=(HS &&hs) = delete;

	private:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		HS() = delete;
		HS(const VS &hs) = delete;
		HS(HS &&hs) = delete;
		~HS() = delete;
	};
	
	//-------------------------------------------------------------------------
	// TS
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// DS
	//-------------------------------------------------------------------------

	/**
	 The domain shader stage.
	 */
	struct DS final {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the domain shader stage.
		 
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
			ID3D11Buffer * const buffers[1] = { buffer };
			BindConstantBuffers(slot, 1, buffers);
		}

		/**
		 Binds an array of constant buffers to the domain shader stage.
		 
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
		 Binds a shader resource view to the domain shader stage.
		 
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
			ID3D11ShaderResourceView * const srvs[1] = { srv };
			BindSRVs(slot, 1, srvs);
		}

		/**
		 Binds an array of shader resource views to the domain shader stage.
		 
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
		 Binds a sampler to the domain shader stage.
		 
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
			ID3D11SamplerState * const samplers[1] = { sampler };
			BindSamplers(slot, 1, samplers);
		}
		
		/**
		 Binds an array of samplers to the domain shader stage.
		 
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
		// Assignment Operators
		//---------------------------------------------------------------------

		DS &operator=(const DS &ds) = delete;
		DS &operator=(DS &&ds) = delete;

	private:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		DS() = delete;
		DS(const DS &ds) = delete;
		DS(DS &&ds) = delete;
		~DS() = delete;
	};
	
	//-------------------------------------------------------------------------
	// GS
	//-------------------------------------------------------------------------

	/**
	 The geometry shader stage.
	 */
	struct GS final {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the geometry shader stage.
		 
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
			ID3D11Buffer * const buffers[1] = { buffer };
			BindConstantBuffers(slot, 1, buffers);
		}

		/**
		 Binds an array of constant buffers to the geometry shader stage.
		 
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
		 Binds a shader resource view to the geometry shader stage.
		 
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
			ID3D11ShaderResourceView * const srvs[1] = { srv };
			BindSRVs(slot, 1, srvs);
		}

		/**
		 Binds an array of shader resource views to the geometry shader stage.
		 
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
		 Binds a sampler to the geometry shader stage.
		 
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
			ID3D11SamplerState * const samplers[1] = { sampler };
			BindSamplers(slot, 1, samplers);
		}
		
		/**
		 Binds an array of samplers to the geometry shader stage.
		 
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
		// Assignment Operators
		//---------------------------------------------------------------------

		GS &operator=(const GS &gs) = delete;
		GS &operator=(GS &&gs) = delete;

	private:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		GS() = delete;
		GS(const GS &gs) = delete;
		GS(GS &&gs) = delete;
		~GS() = delete;
	};
	
	//-------------------------------------------------------------------------
	// SS
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// RS
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	// PS
	//-------------------------------------------------------------------------

	/**
	 The pixel shader stage.
	 */
	struct PS final {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the pixel shader stage.
		 
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
			ID3D11Buffer * const buffers[1] = { buffer };
			BindConstantBuffers(slot, 1, buffers);
		}

		/**
		 Binds an array of constant buffers to the pixel shader stage.
		 
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
		 Binds a shader resource view to the pixel shader stage.
		 
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
			ID3D11ShaderResourceView * const srvs[1] = { srv };
			BindSRVs(slot, 1, srvs);
		}

		/**
		 Binds an array of shader resource views to the pixel shader stage.
		 
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
		 Binds a sampler to the pixel shader stage.
		 
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
			ID3D11SamplerState * const samplers[1] = { sampler };
			BindSamplers(slot, 1, samplers);
		}
		
		/**
		 Binds an array of samplers to the pixel shader stage.
		 
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
		// Assignment Operators
		//---------------------------------------------------------------------

		PS &operator=(const PS &ps) = delete;
		PS &operator=(PS &&ps) = delete;

	private:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		PS() = delete;
		PS(const PS &ps) = delete;
		PS(PS &&ps) = delete;
		~PS() = delete;
	};
	
	//-------------------------------------------------------------------------
	// CS
	//-------------------------------------------------------------------------

	/**
	 The compute shader stage.
	 */
	struct CS final {

	public:
	
		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------
	
		/**
		 Binds a constant buffer to the compute shader stage.
		 
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
			ID3D11Buffer * const buffers[1] = { buffer };
			BindConstantBuffers(slot, 1, buffers);
		}

		/**
		 Binds an array of constant buffers to the compute shader stage.
		 
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
		 Binds a shader resource view to the compute shader stage.
		 
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
			ID3D11ShaderResourceView * const srvs[1] = { srv };
			BindSRVs(slot, 1, srvs);
		}

		/**
		 Binds an array of shader resource views to the compute shader stage.
		 
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
		 Binds an unordered access view to the compute shader stage.
		 
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
			ID3D11UnorderedAccessView * const uavs[1] = { uav };
			BindUAVs(slot, 1, uavs);
		}

		/**
		 Binds an unordered access view created with 
		 @c D3D11_BUFFER_UAV_FLAG_APPEND or @c D3D11_BUFFER_UAV_FLAG_COUNTER
		 to the compute shader stage.
		 
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
			ID3D11UnorderedAccessView * const uavs[1] = { uav };
			BindUAVs(slot, 1, uavs, &initial_count);
		}

		/**
		 Binds an array of unordered access views to the compute shader stage.
		 
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
		 to the compute shader stage.
		 
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
		 Binds a sampler to the compute shader stage.
		 
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
			ID3D11SamplerState * const samplers[1] = { sampler };
			BindSamplers(slot, 1, samplers);
		}
		
		/**
		 Binds an array of samplers to the compute shader stage.
		 
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
		// Assignment Operators
		//---------------------------------------------------------------------

		CS &operator=(const CS &cs) = delete;
		CS &operator=(CS &&cs) = delete;

	private:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		CS() = delete;
		CS(const CS &cs) = delete;
		CS(CS &&cs) = delete;
		~CS() = delete;
	};

	//-------------------------------------------------------------------------
	// OM
	//-------------------------------------------------------------------------
}