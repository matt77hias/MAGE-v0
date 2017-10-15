#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"
#include "rendering\rendering.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Pipeline
	//-------------------------------------------------------------------------

	// The (rendering and compute) pipeline and all of its stages are wrapped 
	// as class member methods instead of using (inner)namespaces. This allows
	// the passing of the pipeline or one of its stages as template arguments.

	/**
	 The (rendering and compute) pipeline.
	 */
	struct Pipeline final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods: Device and DeviceContext
		//---------------------------------------------------------------------

		/**
		 The supported feature levels.
		 */
		static const D3D_FEATURE_LEVEL s_feature_levels[2];

		/**
		 Returns the device.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the device.
		 */
		static ID3D11Device2 *GetDevice() noexcept;

		/**
		 Returns the immediate device context.

		 @pre			The rendering manager associated with the current engine 
						must be loaded.
		 @return		A pointer to the immediate device context.
		 */
		static ID3D11DeviceContext2 *GetImmediateDeviceContext() noexcept;

		//---------------------------------------------------------------------
		// Class Member Methods: Drawing and Dispatching
		//---------------------------------------------------------------------

		static void DrawAuto(ID3D11DeviceContext2 *device_context) noexcept {
			device_context->DrawAuto();
			OnDraw();
		}

		static void Draw(ID3D11DeviceContext2 *device_context,
			U32 nb_vertices, U32 vertex_start) noexcept {

			device_context->Draw(nb_vertices, vertex_start);
			OnDraw();
		}

		static void DrawInstanced(ID3D11DeviceContext2 *device_context,
			U32 nb_indices_per_instance, U32 nb_instances,
			U32 vertex_start, U32 instance_start = 0u) noexcept {

			device_context->DrawInstanced(nb_indices_per_instance,
				nb_instances, vertex_start, instance_start);
			OnDraw();
		}

		static void DrawIndexed(ID3D11DeviceContext2 *device_context,
			U32 nb_indices, U32 index_start, U32 index_offset = 0u) noexcept {

			device_context->DrawIndexed(nb_indices, index_start, index_offset);
			OnDraw();
		}

		static void DrawIndexedInstanced(ID3D11DeviceContext2 *device_context,
			U32 nb_indices_per_instance, U32 nb_instances, U32 index_start, 
			U32 index_offset = 0u, U32 instance_start = 0u) noexcept {

			device_context->DrawIndexedInstanced(nb_indices_per_instance,
				nb_instances, index_start, index_offset, instance_start);
			OnDraw();
		}

		static void Dispatch(ID3D11DeviceContext2 *device_context,
			U32 nb_thread_groups_x, U32 nb_thread_groups_y, 
			U32 nb_thread_groups_z) noexcept {

			device_context->Dispatch(
				nb_thread_groups_x, nb_thread_groups_y, nb_thread_groups_z);
		}

		static void DrawInstancedIndirect(
			ID3D11DeviceContext2 *device_context, ID3D11Buffer *buffer, 
			U32 byte_offset) noexcept {

			device_context->DrawInstancedIndirect(buffer, byte_offset);
			OnDraw();
		}

		static void DrawIndexedInstancedIndirect(
			ID3D11DeviceContext2 *device_context, ID3D11Buffer *buffer, 
			U32 byte_offset) noexcept {

			device_context->DrawIndexedInstancedIndirect(buffer, byte_offset);
			OnDraw();
		}

		static void DispatchIndirect(
			ID3D11DeviceContext2 *device_context, ID3D11Buffer *buffer, 
			U32 byte_offset) noexcept {

			device_context->DispatchIndirect(buffer, byte_offset);
		}

		static HRESULT Map(ID3D11DeviceContext2 *device_context,
			ID3D11Resource *resource, U32 subresource,
			D3D11_MAP map_type, U32 map_flags,
			D3D11_MAPPED_SUBRESOURCE *mapped_resource) noexcept {

			return device_context->Map(resource, subresource, 
				map_type, map_flags, mapped_resource);
		}

		static void Unmap(ID3D11DeviceContext2 *device_context,
			ID3D11Resource *resource, U32 subresource) noexcept {

			device_context->Unmap(resource, subresource);
		}
		
		static void UpdateSubresource(ID3D11DeviceContext2 *device_context,
			ID3D11Resource *dst_resource, U32 dst_subresource,
			const void *src_data, U32 src_row_pitch, U32 src_depth_pitch,
			const D3D11_BOX *dst_box = nullptr) noexcept {

			device_context->UpdateSubresource(dst_resource, dst_subresource,
				dst_box, src_data, src_row_pitch, src_depth_pitch);
		}

		//---------------------------------------------------------------------
		// Class Member Methods: Shaders
		//---------------------------------------------------------------------

		/**
		 Binds a constant buffer to all shader stages.
		 
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		buffer
						A pointer to the constant buffer.
		 */
		static void BindConstantBuffer(ID3D11DeviceContext2 *device_context,
			U32 slot, ID3D11Buffer *buffer) noexcept {
				
			VS::BindConstantBuffer(device_context, slot, buffer);
			HS::BindConstantBuffer(device_context, slot, buffer);
			DS::BindConstantBuffer(device_context, slot, buffer);
			GS::BindConstantBuffer(device_context, slot, buffer);
			PS::BindConstantBuffer(device_context, slot, buffer);
			CS::BindConstantBuffer(device_context, slot, buffer);
		}
		
		/**
		 Binds an array of constant buffers to all shader stages.
		 
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
		 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
						- @a slot.
		 @pre			@a buffers points to an array containing at least 
						@a nb_buffers pointers to a constant buffer.	
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to begin 
						setting constant buffers to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 @param[in]		nb_buffers
						The number of constant buffers in the array (ranges from 
						0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
						- @a slot).
		 @param[in]		buffers
						A pointer to an array of constant buffers.
		 */
		static void BindConstantBuffers(ID3D11DeviceContext2 *device_context,
			U32 slot, U32 nb_buffers, 
			ID3D11Buffer * const *buffers) noexcept {
				
			VS::BindConstantBuffers(device_context, slot, nb_buffers, buffers);
			HS::BindConstantBuffers(device_context, slot, nb_buffers, buffers);
			DS::BindConstantBuffers(device_context, slot, nb_buffers, buffers);
			GS::BindConstantBuffers(device_context, slot, nb_buffers, buffers);
			PS::BindConstantBuffers(device_context, slot, nb_buffers, buffers);
			CS::BindConstantBuffers(device_context, slot, nb_buffers, buffers);
		}
		
		/**
		 Binds a shader resource view to all shader stages.
		 
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the shader resource view to (ranges from 0 to 
						@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
		 @param[in]		srv
						A pointer to the shader resource view.
		 */
		static void BindSRV(ID3D11DeviceContext2 *device_context,
			U32 slot, ID3D11ShaderResourceView *srv) noexcept {
				
			VS::BindSRV(device_context, slot, srv);
			HS::BindSRV(device_context, slot, srv);
			DS::BindSRV(device_context, slot, srv);
			GS::BindSRV(device_context, slot, srv);
			PS::BindSRV(device_context, slot, srv);
			CS::BindSRV(device_context, slot, srv);
		}

		/**
		 Binds an array of shader resource views to all shaders stage.
		 
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
		 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
						- @a slot.
		 @pre			@a srvs points to an array containing at least 
						@a nb_srvs pointers to a shader resource view.				
		 @param[in]		device_context
						A pointer to the device context.
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
		static void BindSRVs(ID3D11DeviceContext2 *device_context, 
			U32 slot, U32 nb_srvs, 
			ID3D11ShaderResourceView * const *srvs) noexcept {
				
			VS::BindSRVs(device_context, slot, nb_srvs, srvs);
			HS::BindSRVs(device_context, slot, nb_srvs, srvs);
			DS::BindSRVs(device_context, slot, nb_srvs, srvs);
			GS::BindSRVs(device_context, slot, nb_srvs, srvs);
			PS::BindSRVs(device_context, slot, nb_srvs, srvs);
			CS::BindSRVs(device_context, slot, nb_srvs, srvs);
		}

		/**
		 Binds a sampler to all shader stages.
		 
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @param[in]		device_context
						A pointer to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the sampler to (ranges from 0 to 
						@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
		 @param[in]		sampler
						A pointer to the sampler.
		 */
		static void BindSampler(ID3D11DeviceContext2 *device_context, 
			U32 slot, ID3D11SamplerState *sampler) noexcept {
				
			VS::BindSampler(device_context, slot, sampler);
			HS::BindSampler(device_context, slot, sampler);
			DS::BindSampler(device_context, slot, sampler);
			GS::BindSampler(device_context, slot, sampler);
			PS::BindSampler(device_context, slot, sampler);
			CS::BindSampler(device_context, slot, sampler);
		}
		
		/**
		 Binds an array of samplers to all shader stages.
		 
		 @pre			@a device_context is not equal to @c nullptr.
		 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
		 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
						- @a slot.
		 @pre			@a samplers points to an array containing at least 
						@a nb_samplers pointers to a sampler.
		 @param[in]		device_context
						A pointer to the device context.
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
		static void BindSamplers(ID3D11DeviceContext2 *device_context, 
			U32 slot, U32 nb_samplers, 
			ID3D11SamplerState * const *samplers) noexcept {
				
			VS::BindSamplers(device_context, slot, nb_samplers, samplers);
			HS::BindSamplers(device_context, slot, nb_samplers, samplers);
			DS::BindSamplers(device_context, slot, nb_samplers, samplers);
			GS::BindSamplers(device_context, slot, nb_samplers, samplers);
			PS::BindSamplers(device_context, slot, nb_samplers, samplers);
			CS::BindSamplers(device_context, slot, nb_samplers, samplers);
		}
		
		//---------------------------------------------------------------------
		// IA
		//---------------------------------------------------------------------

		/**
		 The input assembler stage.
		 */
		struct IA final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------

			static void BindIndexBuffer(ID3D11DeviceContext2 *device_context,
				ID3D11Buffer *buffer, DXGI_FORMAT format, 
				U32 offset = 0u) noexcept {

				device_context->IASetIndexBuffer(buffer, format, offset);
			}

			static void BindVertexBuffer(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11Buffer *buffer, U32 stride, 
				U32 offset = 0u) noexcept {

				ID3D11Buffer * const buffers[1] = { buffer };

				BindVertexBuffers(device_context,
					slot, 1u, buffers, &stride, &offset);
			}
			
			static void BindVertexBuffers(ID3D11DeviceContext2 *device_context,
				U32 slot, U32 nb_buffers, ID3D11Buffer * const *buffers,
				const U32 *strides, const U32 *offsets) noexcept {

				device_context->IASetVertexBuffers(
					slot, nb_buffers, buffers, strides, offsets);
			}

			static void BindPrimitiveTopology(ID3D11DeviceContext2 *device_context,
				D3D11_PRIMITIVE_TOPOLOGY topology) noexcept {

				device_context->IASetPrimitiveTopology(topology);
			}

			static void BindInputLayout(ID3D11DeviceContext2 *device_context,
				ID3D11InputLayout *input_layout) noexcept {

				device_context->IASetInputLayout(input_layout);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			IA &operator=(const IA &ia) = delete;
			IA &operator=(IA &&ia) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			IA() = delete;
			IA(const IA &ia) = delete;
			IA(IA &&ia) = delete;
			~IA() = delete;
		};

		//---------------------------------------------------------------------
		// VS
		//---------------------------------------------------------------------

		/**
		 The vertex shader stage.
		 */
		struct VS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------
			
			/**
			 Binds a vertex shader to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the vertex shader.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11VertexShader *shader) noexcept {
					
				BindShader(device_context, shader, nullptr, 0u);
			}
			
			/**
			 Binds a vertex shader to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the vertex shader.
			 @param[in]		class_instances
							A pointer to an array of class-instance interfaces.
			 @param[in]		nb_class_instances
							The numberof class-instance interfaces.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11VertexShader *shader, 
				ID3D11ClassInstance * const *class_instances, 
				U32 nb_class_instances) noexcept {
				
				device_context->VSSetShader(shader, 
					class_instances, nb_class_instances);
			}
			
			/**
			 Binds a constant buffer to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the constant buffer to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		buffer
							A pointer to the constant buffer.
			 */
			static void BindConstantBuffer(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11Buffer *buffer) noexcept {
					
				ID3D11Buffer * const buffers[1] = { buffer };
				BindConstantBuffers(device_context, slot, 1u, buffers);
			}
			
			/**
			 Binds an array of constant buffers to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
							- @a slot.
			 @pre			@a buffers points to an array containing at least 
							@a nb_buffers pointers to a constant buffer.	
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to begin 
							setting constant buffers to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		nb_buffers
							The number of constant buffers in the array (ranges from 
							0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
							- @a slot).
			 @param[in]		buffers
							A pointer to an array of constant buffers.
			 */
			static void BindConstantBuffers(ID3D11DeviceContext2 *device_context,
				U32 slot, U32 nb_buffers, 
				ID3D11Buffer * const *buffers) noexcept {
					
				device_context->VSSetConstantBuffers(slot, nb_buffers, buffers);
			}
			
			/**
			 Binds a shader resource view to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the shader resource view to (ranges from 0 to 
							@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
			 @param[in]		srv
							A pointer to the shader resource view.
			 */
			static void BindSRV(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11ShaderResourceView *srv) noexcept {
					
				ID3D11ShaderResourceView * const srvs[1] = { srv };
				BindSRVs(device_context, slot, 1u, srvs);
			}
			
			/**
			 Binds an array of shader resource views to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
							- @a slot.
			 @pre			@a srvs points to an array containing at least 
							@a nb_srvs pointers to a shader resource view.				
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSRVs(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_srvs, 
				ID3D11ShaderResourceView * const *srvs) noexcept {
					
				device_context->VSSetShaderResources(slot, nb_srvs, srvs);
			}
			
			/**
			 Binds a sampler to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the sampler to (ranges from 0 to 
							@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
			 @param[in]		sampler
							A pointer to the sampler.
			 */
			static void BindSampler(ID3D11DeviceContext2 *device_context, 
				U32 slot, ID3D11SamplerState *sampler) noexcept {
					
				ID3D11SamplerState * const samplers[1] = { sampler };
				BindSamplers(device_context, slot, 1u, samplers);
			}
			
			/**
			 Binds an array of samplers to the vertex shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
							- @a slot.
			 @pre			@a samplers points to an array containing at least 
							@a nb_samplers pointers to a sampler.
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSamplers(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_samplers, 
				ID3D11SamplerState * const *samplers) noexcept {
					
				device_context->VSSetSamplers(slot, nb_samplers, samplers);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			VS &operator=(const VS &vs) = delete;
			VS &operator=(VS &&vs) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			VS() = delete;
			VS(const VS &vs) = delete;
			VS(VS &&vs) = delete;
			~VS() = delete;
		};

		//---------------------------------------------------------------------
		// DS
		//---------------------------------------------------------------------

		/**
		 The domain shader stage.
		 */
		struct DS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------
			
			/**
			 Binds a domain shader to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the domain shader.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11DomainShader *shader) noexcept {
					
				BindShader(device_context, shader, nullptr, 0u);
			}
			
			/**
			 Binds a domain shader to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the domain shader.
			 @param[in]		class_instances
							A pointer to an array of class-instance interfaces.
			 @param[in]		nb_class_instances
							The numberof class-instance interfaces.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11DomainShader *shader, 
				ID3D11ClassInstance * const *class_instances, 
				U32 nb_class_instances) noexcept {
				
				device_context->DSSetShader(shader, 
					class_instances, nb_class_instances);
			}
			
			/**
			 Binds a constant buffer to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the constant buffer to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		buffer
							A pointer to the constant buffer.
			 */
			static void BindConstantBuffer(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11Buffer *buffer) noexcept {
					
				ID3D11Buffer * const buffers[1] = { buffer };
				BindConstantBuffers(device_context, slot, 1u, buffers);
			}
			
			/**
			 Binds an array of constant buffers to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
							- @a slot.
			 @pre			@a buffers points to an array containing at least 
							@a nb_buffers pointers to a constant buffer.	
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to begin 
							setting constant buffers to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		nb_buffers
							The number of constant buffers in the array (ranges from 
							0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
							- @a slot).
			 @param[in]		buffers
							A pointer to an array of constant buffers.
			 */
			static void BindConstantBuffers(ID3D11DeviceContext2 *device_context,
				U32 slot, U32 nb_buffers, 
				ID3D11Buffer * const *buffers) noexcept {
					
				device_context->DSSetConstantBuffers(slot, nb_buffers, buffers);
			}
			
			/**
			 Binds a shader resource view to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the shader resource view to (ranges from 0 to 
							@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
			 @param[in]		srv
							A pointer to the shader resource view.
			 */
			static void BindSRV(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11ShaderResourceView *srv) noexcept {
					
				ID3D11ShaderResourceView * const srvs[1] = { srv };
				BindSRVs(device_context, slot, 1u, srvs);
			}

			/**
			 Binds an array of shader resource views to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
							- @a slot.
			 @pre			@a srvs points to an array containing at least 
							@a nb_srvs pointers to a shader resource view.				
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSRVs(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_srvs, 
				ID3D11ShaderResourceView * const *srvs) noexcept {
					
				device_context->DSSetShaderResources(slot, nb_srvs, srvs);
			}

			/**
			 Binds a sampler to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the sampler to (ranges from 0 to 
							@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
			 @param[in]		sampler
							A pointer to the sampler.
			 */
			static void BindSampler(ID3D11DeviceContext2 *device_context, 
				U32 slot, ID3D11SamplerState *sampler) noexcept {
					
				ID3D11SamplerState * const samplers[1] = { sampler };
				BindSamplers(device_context, slot, 1u, samplers);
			}
			
			/**
			 Binds an array of samplers to the domain shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
							- @a slot.
			 @pre			@a samplers points to an array containing at least 
							@a nb_samplers pointers to a sampler.
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSamplers(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_samplers, 
				ID3D11SamplerState * const *samplers) noexcept {
					
				device_context->DSSetSamplers(slot, nb_samplers, samplers);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			DS &operator=(const DS &ds) = delete;
			DS &operator=(DS &&ds) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			DS() = delete;
			DS(const DS &ds) = delete;
			DS(DS &&ds) = delete;
			~DS() = delete;
		};

		//---------------------------------------------------------------------
		// TS
		//---------------------------------------------------------------------

		/**
		 The tesselator stage.
		 */
		struct TS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			TS &operator=(const TS &TS) = delete;
			TS &operator=(TS &&TS) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			TS() = delete;
			TS(const TS &TS) = delete;
			TS(TS &&TS) = delete;
			~TS() = delete;
		};

		//---------------------------------------------------------------------
		// HS
		//---------------------------------------------------------------------

		/**
		 The hull shader stage.
		 */
		struct HS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------
			
			/**
			 Binds a hull shader to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the hull shader.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11HullShader *shader) noexcept {
					
				BindShader(device_context, shader, nullptr, 0u);
			}
			
			/**
			 Binds a hull shader to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the hull shader.
			 @param[in]		class_instances
							A pointer to an array of class-instance interfaces.
			 @param[in]		nb_class_instances
							The numberof class-instance interfaces.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11HullShader *shader, 
				ID3D11ClassInstance * const *class_instances, 
				U32 nb_class_instances) noexcept {
				
				device_context->HSSetShader(shader, 
					class_instances, nb_class_instances);
			}
			
			/**
			 Binds a constant buffer to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the constant buffer to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		buffer
							A pointer to the constant buffer.
			 */
			static void BindConstantBuffer(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11Buffer *buffer) noexcept {
					
				ID3D11Buffer * const buffers[1] = { buffer };
				BindConstantBuffers(device_context, slot, 1u, buffers);
			}
			
			/**
			 Binds an array of constant buffers to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
							- @a slot.
			 @pre			@a buffers points to an array containing at least 
							@a nb_buffers pointers to a constant buffer.	
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to begin 
							setting constant buffers to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		nb_buffers
							The number of constant buffers in the array (ranges from 
							0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
							- @a slot).
			 @param[in]		buffers
							A pointer to an array of constant buffers.
			 */
			static void BindConstantBuffers(ID3D11DeviceContext2 *device_context,
				U32 slot, U32 nb_buffers, 
				ID3D11Buffer * const *buffers) noexcept {
					
				device_context->HSSetConstantBuffers(slot, nb_buffers, buffers);
			}
			
			/**
			 Binds a shader resource view to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the shader resource view to (ranges from 0 to 
							@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
			 @param[in]		srv
							A pointer to the shader resource view.
			 */
			static void BindSRV(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11ShaderResourceView *srv) noexcept {
					
				ID3D11ShaderResourceView * const srvs[1] = { srv };
				BindSRVs(device_context, slot, 1u, srvs);
			}
			
			/**
			 Binds an array of shader resource views to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
							- @a slot.
			 @pre			@a srvs points to an array containing at least 
							@a nb_srvs pointers to a shader resource view.				
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSRVs(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_srvs, 
				ID3D11ShaderResourceView * const *srvs) noexcept {
					
				device_context->HSSetShaderResources(slot, nb_srvs, srvs);
			}

			/**
			 Binds a sampler to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the sampler to (ranges from 0 to 
							@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
			 @param[in]		sampler
							A pointer to the sampler.
			 */
			static void BindSampler(ID3D11DeviceContext2 *device_context, 
				U32 slot, ID3D11SamplerState *sampler) noexcept {
					
				ID3D11SamplerState * const samplers[1] = { sampler };
				BindSamplers(device_context, slot, 1u, samplers);
			}
			
			/**
			 Binds an array of samplers to the hull shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
							- @a slot.
			 @pre			@a samplers points to an array containing at least 
							@a nb_samplers pointers to a sampler.
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSamplers(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_samplers, 
				ID3D11SamplerState * const *samplers) noexcept {
					
				device_context->HSSetSamplers(slot, nb_samplers, samplers);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			HS &operator=(const HS &hs) = delete;
			HS &operator=(HS &&hs) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			HS() = delete;
			HS(const HS &hs) = delete;
			HS(HS &&hs) = delete;
			~HS() = delete;
		};

		//---------------------------------------------------------------------
		// GS
		//---------------------------------------------------------------------

		/**
		 The geometry shader stage.
		 */
		struct GS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------
			
			/**
			 Binds a geometry shader to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the geometry shader.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11GeometryShader *shader) noexcept {
					
				BindShader(device_context, shader, nullptr, 0u);
			}
			
			/**
			 Binds a geometry shader to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the geometry shader.
			 @param[in]		class_instances
							A pointer to an array of class-instance interfaces.
			 @param[in]		nb_class_instances
							The numberof class-instance interfaces.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11GeometryShader *shader, 
				ID3D11ClassInstance * const *class_instances, 
				U32 nb_class_instances) noexcept {
				
				device_context->GSSetShader(shader, 
					class_instances, nb_class_instances);
			}
			
			/**
			 Binds a constant buffer to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the constant buffer to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		buffer
							A pointer to the constant buffer.
			 */
			static void BindConstantBuffer(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11Buffer *buffer) noexcept {
					
				ID3D11Buffer * const buffers[1] = { buffer };
				BindConstantBuffers(device_context, slot, 1u, buffers);
			}
			
			/**
			 Binds an array of constant buffers to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
							- @a slot.
			 @pre			@a buffers points to an array containing at least 
							@a nb_buffers pointers to a constant buffer.	
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to begin 
							setting constant buffers to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		nb_buffers
							The number of constant buffers in the array (ranges from 
							0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
							- @a slot).
			 @param[in]		buffers
							A pointer to an array of constant buffers.
			 */
			static void BindConstantBuffers(ID3D11DeviceContext2 *device_context,
				U32 slot, U32 nb_buffers, 
				ID3D11Buffer * const *buffers) noexcept {
					
				device_context->GSSetConstantBuffers(slot, nb_buffers, buffers);
			}
			
			/**
			 Binds a shader resource view to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the shader resource view to (ranges from 0 to 
							@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
			 @param[in]		srv
							A pointer to the shader resource view.
			 */
			static void BindSRV(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11ShaderResourceView *srv) noexcept {
					
				ID3D11ShaderResourceView * const srvs[1] = { srv };
				BindSRVs(device_context, slot, 1u, srvs);
			}
			
			/**
			 Binds an array of shader resource views to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
							- @a slot.
			 @pre			@a srvs points to an array containing at least 
							@a nb_srvs pointers to a shader resource view.				
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSRVs(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_srvs, 
				ID3D11ShaderResourceView * const *srvs) noexcept {
					
				device_context->GSSetShaderResources(slot, nb_srvs, srvs);
			}
			
			/**
			 Binds a sampler to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the sampler to (ranges from 0 to 
							@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
			 @param[in]		sampler
							A pointer to the sampler.
			 */
			static void BindSampler(ID3D11DeviceContext2 *device_context, 
				U32 slot, ID3D11SamplerState *sampler) noexcept {
					
				ID3D11SamplerState * const samplers[1] = { sampler };
				BindSamplers(device_context, slot, 1u, samplers);
			}
			
			/**
			 Binds an array of samplers to the geometry shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
							- @a slot.
			 @pre			@a samplers points to an array containing at least 
							@a nb_samplers pointers to a sampler.
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSamplers(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_samplers, 
				ID3D11SamplerState * const *samplers) noexcept {
					
				device_context->GSSetSamplers(slot, nb_samplers, samplers);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			GS &operator=(const GS &gs) = delete;
			GS &operator=(GS &&gs) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			GS() = delete;
			GS(const GS &gs) = delete;
			GS(GS &&gs) = delete;
			~GS() = delete;
		};

		//---------------------------------------------------------------------
		// SO
		//---------------------------------------------------------------------

		/**
		 The stream output stage.
		 */
		struct SO final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			SO &operator=(const SO &SO) = delete;
			SO &operator=(SO &&SO) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			SO() = delete;
			SO(const SO &SO) = delete;
			SO(SO &&SO) = delete;
			~SO() = delete;
		};

		//---------------------------------------------------------------------
		// RS
		//---------------------------------------------------------------------

		/**
		 The rasterizer stage.
		 */
		struct RS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------

			static void BindScissorRectangle(ID3D11DeviceContext2 *device_context,
				const D3D11_RECT *rectangle) noexcept {
				
				BindScissorRectangles(device_context, 1u, rectangle);
			}
			
			static void BindScissorRectangles(ID3D11DeviceContext2 *device_context,
				U32 nb_rectangles, const D3D11_RECT *rectangles) noexcept {

				device_context->RSSetScissorRects(nb_rectangles, rectangles);
			}
			
			static void BindState(ID3D11DeviceContext2 *device_context,
				ID3D11RasterizerState *state) noexcept {

				device_context->RSSetState(state);
			}
			
			static void GetBoundViewports(ID3D11DeviceContext2 *device_context,
				U32 *nb_viewports, D3D11_VIEWPORT *viewports) noexcept {

				device_context->RSGetViewports(nb_viewports, viewports);
			}
			
			static void BindViewport(ID3D11DeviceContext2 *device_context,
				const D3D11_VIEWPORT *viewport) noexcept {
				
				BindViewports(device_context, 1u, viewport);
			}
			
			static void BindViewports(ID3D11DeviceContext2 *device_context,
				U32 nb_viewports, const D3D11_VIEWPORT *viewports) noexcept {

				device_context->RSSetViewports(nb_viewports, viewports);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			RS &operator=(const RS &rs) = delete;
			RS &operator=(RS &&rs) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			RS() = delete;
			RS(const RS &rs) = delete;
			RS(RS &&rs) = delete;
			~RS() = delete;
		};

		//---------------------------------------------------------------------
		// PS
		//---------------------------------------------------------------------

		/**
		 The pixel shader stage.
		 */
		struct PS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------
			
			/**
			 Binds a pixel shader to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the pixel shader.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11PixelShader *shader) noexcept {
					
				BindShader(device_context, shader, nullptr, 0u);
			}
			
			/**
			 Binds a pixel shader to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the pixel shader.
			 @param[in]		class_instances
							A pointer to an array of class-instance interfaces.
			 @param[in]		nb_class_instances
							The numberof class-instance interfaces.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11PixelShader *shader, 
				ID3D11ClassInstance * const *class_instances, 
				U32 nb_class_instances) noexcept {
				
				device_context->PSSetShader(shader, 
					class_instances, nb_class_instances);
			}
			
			/**
			 Binds a constant buffer to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the constant buffer to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		buffer
							A pointer to the constant buffer.
			 */
			static void BindConstantBuffer(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11Buffer *buffer) noexcept {
					
				ID3D11Buffer * const buffers[1] = { buffer };
				BindConstantBuffers(device_context, slot, 1u, buffers);
			}
			
			/**
			 Binds an array of constant buffers to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
							- @a slot.
			 @pre			@a buffers points to an array containing at least 
							@a nb_buffers pointers to a constant buffer.	
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to begin 
							setting constant buffers to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		nb_buffers
							The number of constant buffers in the array (ranges from 
							0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
							- @a slot).
			 @param[in]		buffers
							A pointer to an array of constant buffers.
			 */
			static void BindConstantBuffers(ID3D11DeviceContext2 *device_context,
				U32 slot, U32 nb_buffers, 
				ID3D11Buffer * const *buffers) noexcept {
					
				device_context->PSSetConstantBuffers(slot, nb_buffers, buffers);
			}
			
			/**
			 Binds a shader resource view to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the shader resource view to (ranges from 0 to 
							@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
			 @param[in]		srv
							A pointer to the shader resource view.
			 */
			static void BindSRV(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11ShaderResourceView *srv) noexcept {
					
				ID3D11ShaderResourceView * const srvs[1] = { srv };
				BindSRVs(device_context, slot, 1u, srvs);
			}

			/**
			 Binds an array of shader resource views to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
							- @a slot.
			 @pre			@a srvs points to an array containing at least 
							@a nb_srvs pointers to a shader resource view.				
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSRVs(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_srvs, 
				ID3D11ShaderResourceView * const *srvs) noexcept {
					
				device_context->PSSetShaderResources(slot, nb_srvs, srvs);
			}
			
			/**
			 Binds a sampler to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the sampler to (ranges from 0 to 
							@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
			 @param[in]		sampler
							A pointer to the sampler.
			 */
			static void BindSampler(ID3D11DeviceContext2 *device_context, 
				U32 slot, ID3D11SamplerState *sampler) noexcept {
					
				ID3D11SamplerState * const samplers[1] = { sampler };
				BindSamplers(device_context, slot, 1u, samplers);
			}
			
			/**
			 Binds an array of samplers to the pixel shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
							- @a slot.
			 @pre			@a samplers points to an array containing at least 
							@a nb_samplers pointers to a sampler.
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSamplers(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_samplers, 
				ID3D11SamplerState * const *samplers) noexcept {
					
				device_context->PSSetSamplers(slot, nb_samplers, samplers);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			PS &operator=(const PS &ps) = delete;
			PS &operator=(PS &&ps) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			PS() = delete;
			PS(const PS &ps) = delete;
			PS(PS &&ps) = delete;
			~PS() = delete;
		};

		//---------------------------------------------------------------------
		// OM
		//---------------------------------------------------------------------

		/**
		 The output merger stage.
		 */
		struct OM final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------

			static void BindDepthStencilState(ID3D11DeviceContext2 *device_context,
				ID3D11DepthStencilState *state, U32 stencil_ref = 0u) noexcept {
				
				device_context->OMSetDepthStencilState(state, stencil_ref);
			}

			static void BindBlendState(ID3D11DeviceContext2 *device_context,
				ID3D11BlendState *state, 
				U32 sample_mask = 0xffffffff) noexcept {
				
				BindBlendState(device_context, state, nullptr, sample_mask);
			}
			
			static void BindBlendState(ID3D11DeviceContext2 *device_context,
				ID3D11BlendState *state, const F32 blend_factor[4], 
				U32 sample_mask = 0xffffffff) noexcept {
				
				device_context->OMSetBlendState(state, blend_factor, sample_mask);
			}

			static void BindRTVAndDSV(ID3D11DeviceContext2 *device_context,
				ID3D11RenderTargetView *rtv, ID3D11DepthStencilView *dsv) noexcept {
				
				if (rtv) {
					ID3D11RenderTargetView * const rtvs[1] = { rtv };
					BindRTVsAndDSV(device_context, 1u, rtvs, dsv);
				}
				else {
					BindRTVsAndDSV(device_context, 0u, nullptr, dsv);
				}
			}
			
			static void BindRTVsAndDSV(ID3D11DeviceContext2 *device_context,
				U32 nb_views, ID3D11RenderTargetView * const *rtvs, 
				ID3D11DepthStencilView *dsv) noexcept {
				
				device_context->OMSetRenderTargets(nb_views, rtvs, dsv);
			}
			
			static void BindRTVAndDSVAndUAV(ID3D11DeviceContext2 *device_context,
				ID3D11RenderTargetView *rtv, ID3D11DepthStencilView *dsv,
				U32 uav_slot, ID3D11UnorderedAccessView *uav,
				U32 initial_count = 0u) noexcept {
				
				if (rtv) {
					ID3D11RenderTargetView * const rtvs[1] = { rtv };

					if (uav) {
						ID3D11UnorderedAccessView * const uavs[1] = { uav };
						const U32 initial_counts[1] = { initial_count };

						BindRTVsAndDSVAndUAVs(device_context,
							1u, rtvs, dsv, uav_slot, 1u, uavs, initial_counts);
					}
					else {
						BindRTVsAndDSVAndUAVs(device_context,
							1u, rtvs, dsv, uav_slot, 0u, nullptr, nullptr);
					}
				}
				else {

					if (uav) {
						ID3D11UnorderedAccessView * const uavs[1] = { uav };
						const U32 initial_counts[1] = { initial_count };

						BindRTVsAndDSVAndUAVs(device_context,
							0u, nullptr, dsv, uav_slot, 1u, uavs, initial_counts);
					}
					else {
						BindRTVsAndDSVAndUAVs(device_context,
							0u, nullptr, dsv, uav_slot, 0u, nullptr, nullptr);
					}
				}
			}
			
			static void BindRTVsAndDSVAndUAV(ID3D11DeviceContext2 *device_context,
				U32 nb_views, ID3D11RenderTargetView * const *rtvs, 
				ID3D11DepthStencilView *dsv, U32 uav_slot, 
				ID3D11UnorderedAccessView *uav, U32 initial_count = 0u) noexcept {
				
				if (uav) {
					ID3D11UnorderedAccessView * const uavs[1] = { uav };
					const U32 initial_counts[1] = { initial_count };

					BindRTVsAndDSVAndUAVs(device_context,
						nb_views, rtvs, dsv, uav_slot, 1u, uavs, initial_counts);
				}
				else {
					BindRTVsAndDSVAndUAVs(device_context,
						nb_views, rtvs, dsv, uav_slot, 0u, nullptr, nullptr);
				}
			}
			
			static void BindRTVsAndDSVAndUAVs(ID3D11DeviceContext2 *device_context,
				U32 nb_views, ID3D11RenderTargetView * const *rtvs, 
				ID3D11DepthStencilView *dsv, U32 uav_slot, U32 nb_uavs, 
				ID3D11UnorderedAccessView * const *uavs,
				const U32 *initial_counts = nullptr) noexcept {
				
				device_context->OMSetRenderTargetsAndUnorderedAccessViews(
					nb_views, rtvs, dsv, uav_slot, nb_uavs, uavs, initial_counts);
			}

			static void ClearRTV(ID3D11DeviceContext2 *device_context,
				ID3D11RenderTargetView *rtv) noexcept {
				
				static const F32 rgba[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
				device_context->ClearRenderTargetView(rtv, rgba);
			}

			static void ClearRTV(ID3D11DeviceContext2 *device_context,
				ID3D11RenderTargetView *rtv, const F32 rgba[4]) noexcept {

				device_context->ClearRenderTargetView(rtv, rgba);
			}
			
			static void ClearDSV(ID3D11DeviceContext2 *device_context,
				ID3D11DepthStencilView *dsv, 
				F32 depth = 1.0f, U8 stencil = 0u) noexcept {

				device_context->ClearDepthStencilView(
				dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
			}
			
			static void ClearDepthOfDSV(ID3D11DeviceContext2 *device_context,
				ID3D11DepthStencilView *dsv, F32 depth = 1.0f) noexcept {

				device_context->ClearDepthStencilView(
				dsv, D3D11_CLEAR_DEPTH, depth, 0u);
			}
			
			static void ClearStencilOfDSV(ID3D11DeviceContext2 *device_context, 
				ID3D11DepthStencilView *dsv, U8 stencil = 0u) noexcept {

				device_context->ClearDepthStencilView(
				dsv, D3D11_CLEAR_STENCIL, 1.0f, stencil);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			OM &operator=(const OM &om) = delete;
			OM &operator=(OM &&om) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			OM() = delete;
			OM(const OM &om) = delete;
			OM(OM &&om) = delete;
			~OM() = delete;
		};

		//---------------------------------------------------------------------
		// CS
		//---------------------------------------------------------------------

		/**
		 The compute shader stage.
		 */
		struct CS final {

		public:

			//-----------------------------------------------------------------
			// Class Member Methods
			//-----------------------------------------------------------------
			
			/**
			 Binds a compute shader to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the compute shader.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11ComputeShader *shader) noexcept {
					
				BindShader(device_context, shader, nullptr, 0u);
			}
			
			/**
			 Binds a compute shader to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		shader
							A pointer to the compute shader.
			 @param[in]		class_instances
							A pointer to an array of class-instance interfaces.
			 @param[in]		nb_class_instances
							The numberof class-instance interfaces.
			 */
			static void BindShader(ID3D11DeviceContext2 *device_context,
				ID3D11ComputeShader *shader, 
				ID3D11ClassInstance * const *class_instances, 
				U32 nb_class_instances) noexcept {
				
				device_context->CSSetShader(shader, 
					class_instances, nb_class_instances);
			}
			
			/**
			 Binds a constant buffer to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the constant buffer to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		buffer
							A pointer to the constant buffer.
			 */
			static void BindConstantBuffer(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11Buffer *buffer) noexcept {
					
				ID3D11Buffer * const buffers[1] = { buffer };
				BindConstantBuffers(device_context, slot, 1u, buffers);
			}
			
			/**
			 Binds an array of constant buffers to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT.
			 @pre			@a nb_buffers < @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT
							- @a slot.
			 @pre			@a buffers points to an array containing at least 
							@a nb_buffers pointers to a constant buffer.	
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to begin 
							setting constant buffers to (ranges from 0 to 
							@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
			 @param[in]		nb_buffers
							The number of constant buffers in the array (ranges from 
							0 to @c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT  
							- @a slot).
			 @param[in]		buffers
							A pointer to an array of constant buffers.
			 */
			static void BindConstantBuffers(ID3D11DeviceContext2 *device_context,
				U32 slot, U32 nb_buffers, ID3D11Buffer * const *buffers) noexcept {
					
				device_context->CSSetConstantBuffers(slot, nb_buffers, buffers);
			}
			
			/**
			 Binds a shader resource view to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the shader resource view to (ranges from 0 to 
							@c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT - 1).
			 @param[in]		srv
							A pointer to the shader resource view.
			 */
			static void BindSRV(ID3D11DeviceContext2 *device_context,
				U32 slot, ID3D11ShaderResourceView *srv) noexcept {
					
				ID3D11ShaderResourceView * const srvs[1] = { srv };
				BindSRVs(device_context, slot, 1u, srvs);
			}
			
			/**
			 Binds an array of shader resource views to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT.
			 @pre			@a nb_srvs < @c D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT
							- @a slot.
			 @pre			@a srvs points to an array containing at least 
							@a nb_srvs pointers to a shader resource view.				
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSRVs(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_srvs, 
				ID3D11ShaderResourceView * const *srvs) noexcept {
					
				device_context->CSSetShaderResources(slot, nb_srvs, srvs);
			}
			
			/**
			 Binds an unordered access view to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_1_UAV_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to begin 
							setting unordered access views to (ranges from 0 to 
							@c D3D11_1_UAV_SLOT_COUNT - 1).
			 @param[in]		uav
							A pointer to the unordered access view.
			 @param[in]		initial_count
							The append and consume buffer offsets.
							This is only used for unordered access views created with
							@c D3D11_BUFFER_UAV_FLAG_APPEND or @c D3D11_BUFFER_UAV_FLAG_COUNTER.
			 */
			static void BindUAV(ID3D11DeviceContext2 *device_context, 
				U32 slot, ID3D11UnorderedAccessView *uav, 
				U32 initial_count = 0u) noexcept {
					
				ID3D11UnorderedAccessView * const uavs[1] = { uav };
				BindUAVs(device_context, slot, 1u, uavs, &initial_count);
			}
			
			/**
			 Binds an array of unordered access views to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_1_UAV_SLOT_COUNT.
			 @pre			@a nb_uavs < @c D3D11_1_UAV_SLOT_COUNT - @a slot.
			 @pre			@a uavs points to an array containing at least 
							@a nb_uavs pointers to an unordered access view.
			 @param[in]		device_context
							A pointer to the device context.
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
							This is only used for unordered access views created with
							@c D3D11_BUFFER_UAV_FLAG_APPEND or @c D3D11_BUFFER_UAV_FLAG_COUNTER.
			 */
			static void BindUAVs(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_uavs, 
				ID3D11UnorderedAccessView * const *uavs, 
				const U32 *initial_counts = nullptr) noexcept {
					
				device_context->CSSetUnorderedAccessViews(slot, nb_uavs, uavs, initial_counts);
			}
			
			/**
			 Binds a sampler to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @param[in]		device_context
							A pointer to the device context.
			 @param[in]		slot
							The index into the device's zero-based array to set 
							the sampler to (ranges from 0 to 
							@c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT - 1).
			 @param[in]		sampler
							A pointer to the sampler.
			 */
			static void BindSampler(ID3D11DeviceContext2 *device_context, 
				U32 slot, ID3D11SamplerState *sampler) noexcept {
					
				ID3D11SamplerState * const samplers[1] = { sampler };
				BindSamplers(device_context, slot, 1u, samplers);
			}
			
			/**
			 Binds an array of samplers to the compute shader stage.
			 
			 @pre			@a device_context is not equal to @c nullptr.
			 @pre			@a slot < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT.
			 @pre			@a nb_samplers < @c D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT 
							- @a slot.
			 @pre			@a samplers points to an array containing at least 
							@a nb_samplers pointers to a sampler.
			 @param[in]		device_context
							A pointer to the device context.
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
			static void BindSamplers(ID3D11DeviceContext2 *device_context, 
				U32 slot, U32 nb_samplers, 
				ID3D11SamplerState * const *samplers) noexcept {
					
				device_context->CSSetSamplers(slot, nb_samplers, samplers);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			CS &operator=(const CS &cs) = delete;
			CS &operator=(CS &&cs) = delete;

		private:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			CS() = delete;
			CS(const CS &cs) = delete;
			CS(CS &&cs) = delete;
			~CS() = delete;
		};

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Pipeline &operator=(const Pipeline &pipeline) = delete;
		Pipeline &operator=(Pipeline &&pipeline) = delete;

	private:

		static void OnDraw() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		Pipeline() = delete;
		Pipeline(const Pipeline &pipeline) = delete;
		Pipeline(Pipeline &&pipeline) = delete;
		~Pipeline() = delete;
	};
}