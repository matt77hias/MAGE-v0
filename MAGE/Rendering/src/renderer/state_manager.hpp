#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// StateID
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 An enumeration of the different blend state identifiers.

	 This contains:
	 @c Opaque,
	 @c Alpha,
	 @c Additive,
	 @c Multiplicative,
	 @c BiMultiplicative,
	 @c Transparency and
	 @c AlphaToCoverage.
	 */
	enum class BlendStateID : U8 {
		Opaque = 0,
		Alpha,
		Additive,
		Multiplicative,
		BiMultiplicative,
		Transparency,
		AlphaToCoverage,
		Count
	};
		
	/**
	 An enumeration of the different depth stencil state identifiers.

	 This contains:
	 @c DepthNone,
	 @c GreaterEqualDepthReadWrite,
	 @c GreaterEqualDepthRead,
	 @c GreaterDepthReadWrite, 
	 @c GreaterDepthRead, 
	 @c LessEqualDepthReadWrite,
	 @c LessEqualDepthRead,
	 @c LessDepthReadWrite and
	 @c LessDepthRead.
	 */
	enum class DepthStencilStateID : U8 {
		DepthNone = 0,
		GreaterEqualDepthReadWrite,
		GreaterEqualDepthRead,
		GreaterDepthReadWrite,
		GreaterDepthRead,
		LessEqualDepthReadWrite,
		LessEqualDepthRead,
		LessDepthReadWrite,
		LessDepthRead,
		Count
	};
		
	/**
	 An enumeration of the different rasterizer state identifiers.

	 This contains:
	 @c NoCulling,
	 @c ClockwiseCulling,
	 @c CounterClockwiseCulling and
	 @c Wireframe.
	 */
	enum class RasterizerStateID : U8 {
		NoCulling = 0,
		ClockwiseCulling,
		CounterClockwiseCulling,
		Wireframe,
		Count
	};
		
	/**
	 An enumeration of the different sampler state identifiers.

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
	enum class SamplerStateID : U8 {
		PointWrap,
		PointClamp,
		PointMirror,
		LinearWrap,
		LinearClamp,
		LinearMirror,
		AnisotropicWrap,
		AnisotropicClamp,
		AnisotropicMirror,
		PCF,
		Count
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// StateManager
	//-------------------------------------------------------------------------
	#pragma region

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
		StateManager& operator=(StateManager&& manager) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Binds the persistent state of this state manager.

		 @param[in]		device_context
						A reference to the device context.
		 */
		void BindPersistentState(ID3D11DeviceContext& device_context) const noexcept;

		/**
		 Binds the given blend state of this state manager.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		id
						The blend state identifier.
		 */
		void Bind(ID3D11DeviceContext& device_context, 
				  BlendStateID id) const noexcept {

			Pipeline::OM::BindBlendState(device_context, Get(id));
		}

		/**
		 Binds the given depth-stencil state of this state manager.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		id
						The depth-stencil state identifier.
		 */
		void Bind(ID3D11DeviceContext& device_context, 
				  DepthStencilStateID id) const noexcept {

			Pipeline::OM::BindDepthStencilState(device_context, Get(id));
		}

		
		/**
		 Binds the given rasterizer state of this state manager.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		id
						The rasterizer state identifier.
		 */
		void Bind(ID3D11DeviceContext& device_context, 
				  RasterizerStateID id) const noexcept {

			Pipeline::RS::BindState(device_context, Get(id));
		}

		/**
		 Binds the point sampler state with wrapping of this state manager.

		 @pre			@c SLOT_SAMPLER_VARIABLE_START <= @a slot.
		 @pre			@a slot < @c SLOT_SAMPLER_VARIABLE_END.
		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set the 
						sampler to (ranges from @c SLOT_SAMPLER_VARIABLE_START 
						to @c SLOT_SAMPLER_VARIABLE_END).
		 @param[in]		id
						The sampler state identifier.
		 */
		template< typename PipelineStageT >
		void BindPointWrapSamplerStateID(ID3D11DeviceContext& device_context, 
										 U32 slot, SamplerStateID id) const noexcept {

			PipelineStageT::BindSampler(device_context, slot, Get(id));
		}
		
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
		 Returns the blend state of this state manager associated to the given 
		 identifier.

		 @param[in]		id
						The blend state identifier.
		 @return		A pointer to the blend state of this state manager 
						associated to the given identifier.
		 */
		[[nodiscard]]
		ID3D11BlendState* Get(BlendStateID id) const noexcept {
			const auto& state = m_blend_states[static_cast< size_t >(id)];
			return state.Get();
		}

		/**
		 Returns and releases the address of the blend state of this state 
		 manager associated to the given identifier.

		 @param[in]		id
						The blend state identifier.
		 @return		A pointer to a pointer to the blend state of this state 
						manager associated to the given identifier.
		 */
		[[nodiscard]]
		NotNull< ID3D11BlendState** > 
			ReleaseAndGetAddressOf(BlendStateID id) noexcept {

			auto& state = m_blend_states[static_cast< size_t >(id)];
			return NotNull< ID3D11BlendState** >(state.ReleaseAndGetAddressOf());
		}
		
		/**
		 Returns the depth stencil state of this state manager associated to 
		 the given identifier.

		 @param[in]		id
						The depth stencil identifier.
		 @return		A pointer to the depth stencil state of this state 
						manager associated to the given identifier.
		 */
		[[nodiscard]]
		ID3D11DepthStencilState* Get(DepthStencilStateID id) const noexcept {
			const auto& state = m_depth_stencil_states[static_cast< size_t >(id)];
			
			return state.Get();
		}
		
		/**
		 Returns and releases the address of the depth stencil state of this 
		 state manager associated to the given identifier.

		 @param[in]		id
						The depth stencil identifier.
		 @return		A pointer to a pointer to the depth stencil state of 
						this state manager associated to the given identifier.
		 */
		[[nodiscard]]
		NotNull< ID3D11DepthStencilState** > 
			ReleaseAndGetAddressOf(DepthStencilStateID id) noexcept {
			
			auto& state = m_depth_stencil_states[static_cast< size_t >(id)];
			return NotNull< ID3D11DepthStencilState** >(state.ReleaseAndGetAddressOf());
		}
		
		/**
		 Returns the rasterizer state of this state manager associated to the 
		 given identifier.

		 @param[in]		id
						The rasterizer identifier.
		 @return		A pointer to the rasterizer state of this state manager 
						associated to the given identifier.
		 */
		[[nodiscard]]
		ID3D11RasterizerState* Get(RasterizerStateID id) const noexcept {
			const auto& state = m_rasterizer_states[static_cast< size_t >(id)];
			return state.Get();
		}
		
		/**
		 Returns and releases the address of the rasterizer state of this state 
		 manager associated to the given identifier.

		 @param[in]		id
						The rasterizer state identifier.
		 @return		A pointer to a pointer to the rasterizer state of this 
						state manager associated to the given identifier.
		 */
		[[nodiscard]]
		NotNull< ID3D11RasterizerState** > 
			ReleaseAndGetAddressOf(RasterizerStateID id) noexcept {
			
			auto& state = m_rasterizer_states[static_cast< size_t >(id)];
			return NotNull< ID3D11RasterizerState** >(state.ReleaseAndGetAddressOf());
		}
		
		/**
		 Returns the sampler state of this state manager associated to the 
		 given identifier.

		 @param[in]		id
						The sampler state identifier.
		 @return		A pointer to the sampler state of this state manager 
						associated to the given identifier.
		 */
		[[nodiscard]]
		ID3D11SamplerState* Get(SamplerStateID id) const noexcept {
			const auto& state = m_sampler_states[static_cast< size_t >(id)];
			return state.Get();
		}
		
		/**
		 Returns and releases the address of the sampler state of this state 
		 manager associated to the given identifier.

		 @param[in]		id
						The sampler state identifier.
		 @return		A pointer to a pointer to the sampler state of this 
						state manager associated to the given identifier.
		 */
		[[nodiscard]]
		NotNull< ID3D11SamplerState** > 
			ReleaseAndGetAddressOf(SamplerStateID id) noexcept {

			auto& state = m_sampler_states[static_cast< size_t >(id)];
			return NotNull< ID3D11SamplerState** >(state.ReleaseAndGetAddressOf());
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
			static_cast< size_t >(BlendStateID::Count)];

		/**
		 An array containing pointers to the depth stencil states of this state 
		 manager.
		 */
		ComPtr< ID3D11DepthStencilState > m_depth_stencil_states[
			static_cast< size_t >(DepthStencilStateID::Count)];

		/**
		 An array containing pointers to the rasterizer states of this state 
		 manager.
		 */
		ComPtr< ID3D11RasterizerState > m_rasterizer_states[
			static_cast< size_t >(RasterizerStateID::Count)];
		
		/**
		 An array containing pointers to the sampler states of this state 
		 manager.
		 */
		ComPtr< ID3D11SamplerState > m_sampler_states[
			static_cast< size_t >(SamplerStateID::Count)];
	};

	#pragma endregion
}
