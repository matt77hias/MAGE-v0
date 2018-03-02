#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of state managers.
	 */
	class StateManager final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a state manager.

		 @param[in]		device
						A reference to the device.
		 @throws		Exception
						Failed to setup the rendering states of this state 
						manager.
		 */
		explicit StateManager(ID3D11Device& device);

		/**
		 Constructs a state manager from the given state manager.

		 @param[in]		manager
						A reference to the state manager to copy.
		 */
		StateManager(const StateManager& manager) = delete;

		/**
		 Constructs a state manager by moving the given state manager.

		 @param[in]		manager
						A reference to the state manager to move.
		 */
		StateManager(StateManager&& manager) noexcept;

		/**
		 Destructs this state manager.
		 */
		~StateManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given state manager to this state manager.

		 @param[in]		manager
						A reference to the state manager to copy.
		 @return		A reference to the copy of the given state manager 
						(i.e. this state manager).
		 */
		StateManager& operator=(const StateManager& manager) = delete;

		/**
		 Moves the given state manager to this state manager.

		 @param[in]		manager
						A reference to the state manager to move.
		 @return		A reference to the moved state manager (i.e. this state 
						manager).
		 */
		StateManager& operator=(StateManager&& manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the persistent state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 @throws		Exception
						Failed to bind the persistent state of this state 
						manager.
		 */
		void BindPersistentState(ID3D11DeviceContext& 
								 device_context) const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Blend States
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Binds the opaque blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindOpaqueBlendState(ID3D11DeviceContext& 
								  device_context) const noexcept {

			Pipeline::OM::BindBlendState(device_context, 
										 Get(BlendStateIndex::Opaque));
		}

		/**
		 Binds the alpha blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindAlphaBlendState(ID3D11DeviceContext& 
								 device_context) const noexcept {

			Pipeline::OM::BindBlendState(device_context, 
										 Get(BlendStateIndex::Alpha));
		}

		/**
		 Binds the additive blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindAdditiveBlendState(ID3D11DeviceContext& 
									device_context) const noexcept {

			Pipeline::OM::BindBlendState(device_context, 
										 Get(BlendStateIndex::Additive));
		}
		
		/**
		 Binds the multiplicative blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindMultiplicativeBlendState(ID3D11DeviceContext& 
										  device_context) const noexcept {

			Pipeline::OM::BindBlendState(device_context, 
										 Get(BlendStateIndex::Multiplicative));
		}

		/**
		 Binds the bi-multiplicative blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindBiMultiplicativeBlendState(ID3D11DeviceContext& 
											device_context) const noexcept {

			Pipeline::OM::BindBlendState(device_context, 
										 Get(BlendStateIndex::BiMultiplicative));
		}

		/**
		 Binds the transparency blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindTransparencyBlendState(ID3D11DeviceContext& 
										device_context) const noexcept {

			Pipeline::OM::BindBlendState(device_context, 
										 Get(BlendStateIndex::Transparency));
		}

		/**
		 Binds the alpha-to-coverage blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindAlphaToCoverageBlendState(ID3D11DeviceContext& 
										   device_context) const noexcept {

			Pipeline::OM::BindBlendState(device_context, 
										 Get(BlendStateIndex::AlphaToCoverage));
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Depth Stencil States
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Binds the no-depth stencil state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindDepthNoneDepthStencilState(ID3D11DeviceContext& 
											device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::DepthNone));
		}

		#ifdef DISABLE_INVERTED_Z_BUFFER

		/**
		 Binds the less-equal, read-write depth stencil state of this state 
		 manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindLessEqualDepthReadWriteDepthStencilState(ID3D11DeviceContext& 
														  device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::LessEqualDepthReadWrite));
		}

		/**
		 Binds the less-equal, read depth stencil state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindLessEqualDepthReadDepthStencilState(ID3D11DeviceContext& 
													 device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::LessEqualDepthRead));
		}

		/**
		 Binds the less, read-write depth stencil state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindLessDepthReadWriteDepthStencilState(ID3D11DeviceContext& 
													 device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::LessDepthReadWrite));
		}

		/**
		 Binds the less, read depth stencil state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindLessDepthReadDepthStencilState(ID3D11DeviceContext& 
												device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::LessDepthRead));
		}

		#else  // DISABLE_INVERTED_Z_BUFFER

		/**
		 Binds the greater-equal, read-write depth stencil state of this state 
		 manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindGreaterEqualDepthReadWriteDepthStencilState(ID3D11DeviceContext& 
															 device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::GreaterEqualDepthReadWrite));
		}

		/**
		 Binds the greater-equal, read depth stencil state of this state 
		 manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindGreaterEqualDepthReadDepthStencilState(ID3D11DeviceContext& 
														device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::GreaterEqualDepthRead));
		}

		/**
		 Binds the greater, read-write depth stencil state of this state 
		 manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindGreaterDepthReadWriteDepthStencilState(ID3D11DeviceContext& 
														device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::GreaterDepthReadWrite));
		}

		/**
		 Binds the greater, read depth stencil state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindGreaterDepthReadDepthStencilState(ID3D11DeviceContext& 
												   device_context) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context,
				Get(DepthStencilStateIndex::GreaterDepthRead));
		}

		#endif // DISABLE_INVERTED_Z_BUFFER

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rasterizer States
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Binds the no-culling rasterizer state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindCullNoneRasterizerState(ID3D11DeviceContext& 
										 device_context) const noexcept {

			Pipeline::RS::BindState(device_context, 
				Get(RasterizerStateIndex::NoCulling));
		}

		/**
		 Binds the clockwise-culling rasterizer state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindCullClockwiseRasterizerState(ID3D11DeviceContext& 
											  device_context) const noexcept {
			
			Pipeline::RS::BindState(device_context, 
				Get(RasterizerStateIndex::ClockwiseCulling));
		}

		/**
		 Binds the counter-clockwise-culling rasterizer state of this state 
		 manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindCullCounterClockwiseRasterizerState(ID3D11DeviceContext& 
													 device_context) const noexcept {

			Pipeline::RS::BindState(device_context,
				Get(RasterizerStateIndex::CounterClockwiseCulling));
		}

		/**
		 Binds the wireframe rasterizer state of this state manager.

		 @param[in]		device_context
						A reference to the device context
		 */
		void BindWireframeRasterizerState(ID3D11DeviceContext& 
										  device_context) const noexcept {

			Pipeline::RS::BindState(device_context,
				Get(RasterizerStateIndex::Wireframe));
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Sampler States
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Binds the point sampler state with wrapping of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindPointWrapSamplerState(ID3D11DeviceContext& device_context, 
			                           U32 slot) const noexcept;
		
		/**
		 Binds the point sampler state with clamping of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindPointClampSamplerState(ID3D11DeviceContext& device_context, 
			                            U32 slot) const noexcept;
		
		/**
		 Binds the point sampler state with mirroring of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindPointMirrorSamplerState(ID3D11DeviceContext& device_context, 
			                             U32 slot) const noexcept;
		
		/**
		 Binds the linear sampler state with wrapping of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindLinearWrapSamplerState(ID3D11DeviceContext& device_context, 
			                            U32 slot) const noexcept;
		
		/**
		 Binds the linear sampler state with clamping of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindLinearClampSamplerState(ID3D11DeviceContext& device_context, 
			                             U32 slot) const noexcept;
		
		/**
		 Binds the linear sampler state with mirroring of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindLinearMirrorSamplerState(ID3D11DeviceContext& device_context, 
			                              U32 slot) const noexcept;

		/**
		 Binds the anisotropic sampler state with wrapping of this state 
		 manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindAnisotropicWrapSamplerState(ID3D11DeviceContext& device_context, 
			                                 U32 slot) const noexcept;
		
		/**
		 Binds the anisotropic sampler state with clamping of this state 
		 manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindAnisotropicClampSamplerState(ID3D11DeviceContext& device_context, 
			                                  U32 slot) const noexcept;
		
		/**
		 Binds the anisotropic sampler state with mirroring of this state 
		 manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindAnisotropicMirrorSamplerState(ID3D11DeviceContext& device_context, 
			                                   U32 slot) const noexcept;

		/**
		 Binds the PCF sampler state of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 */
		template< typename PipelineStageT >
		void BindPCFSamplerState(ID3D11DeviceContext& device_context, 
			                     U32 slot) const noexcept;
		
		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Setup the rendering states (blend, depth stencil, rasterizer, sampler)
		 of this state manager.

		 @throws		Exception
						Failed to setup the rendering states of this state 
						manager.
		 */
		void SetupRenderingStates();

		/**
		 Setup the blend states of this state manager.

		 @throws		Exception
						Failed to setup the blend states of this state manager.
		 */
		void SetupBlendStates();
		
		/**
		 Setup the depth stencil states of this state manager.

		 @throws		Exception
						Failed to setup the depth stencil states of state 
						manager.
		 */
		void SetupDepthStencilStates();
		
		/**
		 Setup the rasterizer states of this state manager.

		 @throws		Exception
						Failed to setup the rasterizer states of this state 
						manager.
		 */
		void SetupRasterizerStates();
		
		/**
		 Setup the samplers states of this state manager.

		 @throws		Exception
						Failed to setup the samplers states of this state 
						manager.
		 */
		void SetupSamplerStates();
		
		/**
		 An enumeration of the different blend state indices for state 
		 managers.

		 This contains:
		 @c Opaque,
		 @c Alpha,
		 @c Additive,
		 @c Multiplicative,
		 @c BiMultiplicative,
		 @c Transparency and
		 @c AlphaToCoverage.
		 */
		enum class BlendStateIndex : U8 {
			Opaque           = 0,
			Alpha            = 1,
			Additive         = 2,
			Multiplicative   = 3,
			BiMultiplicative = 4,
			Transparency     = 5,
			AlphaToCoverage  = 6,
			Count            = 7
		};
		
		/**
		 An enumeration of the different depth stencil state indices for 
		 state managers.

		 This contains:
		 @c DepthNone,
		 @c GreaterEqualDepthReadWrite,
		 @c GreaterEqualDepthRead,
		 @c GreaterDepthReadWrite and
		 @c GreaterDepthRead.
		 */
		enum class DepthStencilStateIndex : U8 {
			DepthNone                  = 0,
			#ifdef DISABLE_INVERTED_Z_BUFFER
			LessEqualDepthReadWrite    = 1,
			LessEqualDepthRead         = 2,
			LessDepthReadWrite         = 3,
			LessDepthRead              = 4,
			#else  // DISABLE_INVERTED_Z_BUFFER
			GreaterEqualDepthReadWrite = 1,
			GreaterEqualDepthRead      = 2,
			GreaterDepthReadWrite      = 3,
			GreaterDepthRead           = 4,
			#endif // DISABLE_INVERTED_Z_BUFFER
			Count                      = 5
		};
		
		/**
		 An enumeration of the different rasterizer state indices for state 
		 managers.

		 This contains:
		 @c NoCulling,
		 @c ClockwiseCulling,
		 @c CounterClockwiseCulling and
		 @c Wireframe.
		 */
		enum class RasterizerStateIndex : U8 {
			NoCulling               = 0,
			ClockwiseCulling        = 1,
			CounterClockwiseCulling = 2,
			Wireframe               = 3,
			Count                   = 4
		};
		
		/**
		 An enumeration of the different sampler state indices for state 
		 managers.

		 This contains:
		 @c PointWrap,
		 @c PointClamp,
		 @c PointMirror,
		 @c LinearWrap,
		 @c LinearClamp,
		 @c LinearMirror,
		 @c AnisotropicWrap,
		 @c AnisotropicClamp,
		 @c AnisotropicMirror and.
		 @c PCF.
		 */
		enum class SamplerStateIndex : U8 {
			PointWrap         = 0,
			PointClamp        = 1,
			PointMirror       = 2,
			LinearWrap        = 3,
			LinearClamp       = 4,
			LinearMirror      = 5,
			AnisotropicWrap   = 6,
			AnisotropicClamp  = 7,
			AnisotropicMirror = 8,
			PCF               = 9,
			Count             = 10
		};
		
		/**
		 Returns the blend state of this state manager associated to the given 
		 index.

		 @param[in]		index
						The blend state index.
		 @return		A pointer to the blend state of this state manager 
						associated to the given index.
		 */
		[[nodiscard]]
		ID3D11BlendState* Get(BlendStateIndex index) const noexcept {
			return m_blend_states[static_cast< size_t >(index)].Get();
		}

		/**
		 Returns and releases the address of the blend state of this state 
		 manager associated to the given index.

		 @param[in]		index
						The blend state index.
		 @return		A pointer to a pointer to the blend state of this state 
						manager associated to the given index.
		 */
		[[nodiscard]]
		NotNull< ID3D11BlendState** > 
			ReleaseAndGetAddressOf(BlendStateIndex index) noexcept {

			return m_blend_states[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}
		
		/**
		 Returns the depth stencil state of this state manager associated to 
		 the given index.

		 @param[in]		index
						The depth stencil state index.
		 @return		A pointer to the depth stencil state of this state 
						manager associated to the given index.
		 */
		[[nodiscard]]
		ID3D11DepthStencilState* Get(DepthStencilStateIndex index) const noexcept {
			return m_depth_stencil_states[static_cast< size_t >(index)].Get();
		}
		
		/**
		 Returns and releases the address of the depth stencil state of this 
		 state manager associated to the given index.

		 @param[in]		index
						The depth stencil state index.
		 @return		A pointer to a pointer to the depth stencil state of 
						this state manager associated to the given index.
		 */
		[[nodiscard]]
		NotNull< ID3D11DepthStencilState** > 
			ReleaseAndGetAddressOf(DepthStencilStateIndex index) noexcept {
			
			return m_depth_stencil_states[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}
		
		/**
		 Returns the rasterizer state of this state manager associated to the 
		 given index.

		 @param[in]		index
						The rasterizer state index.
		 @return		A pointer to the rasterizer state of this state manager 
						associated to the given index.
		 */
		[[nodiscard]]
		ID3D11RasterizerState* Get(RasterizerStateIndex index) const noexcept {
			return m_rasterizer_states[static_cast< size_t >(index)].Get();
		}
		
		/**
		 Returns and releases the address of the rasterizer state of this state 
		 manager associated to the given index.

		 @param[in]		index
						The rasterizer state index.
		 @return		A pointer to a pointer to the rasterizer state of this 
						state manager associated to the given index.
		 */
		[[nodiscard]]
		NotNull< ID3D11RasterizerState** > 
			ReleaseAndGetAddressOf(RasterizerStateIndex index) noexcept {
			
			return m_rasterizer_states[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}
		
		/**
		 Returns the sampler state of this state manager associated to the 
		 given index.

		 @param[in]		index
						The sampler state index.
		 @return		A pointer to the sampler state of this state manager 
						associated to the given index.
		 */
		[[nodiscard]]
		ID3D11SamplerState* Get(SamplerStateIndex index) const noexcept {
			return m_sampler_states[static_cast< size_t >(index)].Get();
		}
		
		/**
		 Returns and releases the address of the sampler state of this state 
		 manager associated to the given index.

		 @param[in]		index
						The sampler state index.
		 @return		A pointer to a pointer to the sampler state of this 
						state manager associated to the given index.
		 */
		[[nodiscard]]
		NotNull< ID3D11SamplerState** > 
			ReleaseAndGetAddressOf(SamplerStateIndex index) noexcept {

			return m_sampler_states[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the device of this state manager.
		 */
		std::reference_wrapper< ID3D11Device > m_device;

		/**
		 An array containing pointers to the blend states of this state 
		 manager.
		 */
		ComPtr< ID3D11BlendState > m_blend_states[
			static_cast< size_t >(BlendStateIndex::Count)];

		/**
		 An array containing pointers to the depth stencil states of this state 
		 manager.
		 */
		ComPtr< ID3D11DepthStencilState > m_depth_stencil_states[
			static_cast< size_t >(DepthStencilStateIndex::Count)];

		/**
		 An array containing pointers to the rasterizer states of this state 
		 manager.
		 */
		ComPtr< ID3D11RasterizerState > m_rasterizer_states[
			static_cast< size_t >(RasterizerStateIndex::Count)];
		
		/**
		 An array containing pointers to the sampler states of this state 
		 manager.
		 */
		ComPtr< ID3D11SamplerState > m_sampler_states[
			static_cast< size_t >(SamplerStateIndex::Count)];
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\state_manager.tpp"

#pragma endregion
