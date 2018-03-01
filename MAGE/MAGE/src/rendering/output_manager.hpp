#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\swap_chain.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of output managers.
	 */
	class OutputManager final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a output manager.

		 @pre			@a device is not equal to @c nullptr.
		 @pre			@a display_configuration is not equal to @c nullptr.
		 @pre			@a swap_chain is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		display_configuration
						A pointer to the display configuration.
		  @param[in]	swap_chain
						A pointer to the swap chain.
		 @throws		Exception
						Failed to setup the rendering outputs of this output 
						manager.
		 */
		explicit OutputManager(ID3D11Device *device, 
							   DisplayConfiguration *display_configuration,
							   SwapChain *swap_chain);

		/**
		 Constructs a output manager from the given output manager.

		 @param[in]		manager
						A reference to the output manager to copy.
		 */
		OutputManager(const OutputManager &manager) = delete;

		/**
		 Constructs a output manager by moving the given output manager.

		 @param[in]		manager
						A reference to the output manager to move.
		 */
		OutputManager(OutputManager &&manager) noexcept;

		/**
		 Destructs this output manager.
		 */
		~OutputManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given output manager to this output manager.

		 @param[in]		manager
						A reference to the output manager to copy.
		 @return		A reference to the copy of the given output manager 
						(i.e. this output manager).
		 */
		OutputManager &operator=(const OutputManager &manager) = delete;

		/**
		 Moves the given output manager to this output manager.

		 @param[in]		manager
						A reference to the output manager to move.
		 @return		A reference to the moved output manager (i.e. this 
						output manager).
		 */
		OutputManager &operator=(OutputManager &&manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindBegin(ID3D11DeviceContext *device_context) const noexcept;
		void BindBeginGBuffer(ID3D11DeviceContext *device_context) const noexcept;
		void BindEndGBuffer(ID3D11DeviceContext *device_context) const noexcept;
		void BindBeginDeferred(ID3D11DeviceContext *device_context) const noexcept;
		void BindEndDeferred(ID3D11DeviceContext *device_context) const noexcept;
		void BindBeginForward(ID3D11DeviceContext *device_context) const noexcept;
		void BindEndForward(ID3D11DeviceContext *device_context) const noexcept;
		void BindBeginResolve(ID3D11DeviceContext *device_context) const noexcept;
		void BindEndResolve(ID3D11DeviceContext *device_context) const noexcept;
		void BindBeginPostProcessing(ID3D11DeviceContext *device_context) const noexcept;
		void BindPingPong(ID3D11DeviceContext *device_context) const noexcept;
		void BindEnd(ID3D11DeviceContext *device_context) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		enum class SRVIndex : U8 {
			HDR                   = 0,
			GBuffer_BaseColor     = 1,
			GBuffer_Material      = 2,
			GBuffer_Normal        = 3,
			GBuffer_Depth         = 4,
			PostProcessing_HDR0   = 5,
			PostProcessing_HDR1   = 6,
			PostProcessing_Normal = 7,
			PostProcessing_Depth  = 8,
			Count                 = 9
		};

		enum class RTVIndex : U8 {
			HDR                 = 0,
			GBuffer_BaseColor   = 1,
			GBuffer_Material    = 2,
			GBuffer_Normal      = 3,
			PostProcessing_HDR0 = 4,
			PostProcessing_HDR1 = 5,
			Count               = 6
		};

		enum class UAVIndex : U8 {
			HDR                   = 0,
			PostProcessing_HDR0   = 1,
			PostProcessing_HDR1   = 2,
			PostProcessing_Normal = 3,
			PostProcessing_Depth  = 4,
			Count                 = 5
		};

		[[nodiscard]]ID3D11ShaderResourceView *
			GetSRV(SRVIndex index) const noexcept {

			return m_srvs[static_cast< size_t >(index)].Get();
		}
		
		[[nodiscard]]ID3D11ShaderResourceView **
			ReleaseAndGetAddressOfSRV(SRVIndex index) noexcept {

			return m_srvs[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}
		
		[[nodiscard]]ID3D11RenderTargetView *
			GetRTV(RTVIndex index) const noexcept {

			return m_rtvs[static_cast< size_t >(index)].Get();
		}
		
		[[nodiscard]]ID3D11RenderTargetView **
			ReleaseAndGetAddressOfRTV(RTVIndex index) noexcept {

			return m_rtvs[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}
		
		[[nodiscard]]ID3D11UnorderedAccessView *
			GetUAV(UAVIndex index) const noexcept {

			return m_uavs[static_cast< size_t >(index)].Get();
		}
		
		[[nodiscard]]ID3D11UnorderedAccessView **
			ReleaseAndGetAddressOfUAV(UAVIndex index) noexcept {

			return m_uavs[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}

		void SetupBuffers();

		void SetupBuffer(U32 width, 
			             U32 height, 
			             U32 nb_samples, 
			             DXGI_FORMAT format,
			             ID3D11ShaderResourceView **srv, 
			             ID3D11RenderTargetView **rtv, 
			             ID3D11UnorderedAccessView **uav);

		void SetupDepthBuffer(U32 width, 
			                  U32 height, 
			                  U32 nb_samples);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		DisplayConfiguration * const m_display_configuration;
		ID3D11Device * const m_device;
		SwapChain * const m_swap_chain;

		ComPtr< ID3D11ShaderResourceView > m_srvs[
			static_cast< size_t >(SRVIndex::Count)];

		ComPtr< ID3D11RenderTargetView > m_rtvs[
			static_cast< size_t >(RTVIndex::Count)];

		ComPtr< ID3D11UnorderedAccessView > m_uavs[
			static_cast< size_t >(UAVIndex::Count)];

		ComPtr< ID3D11DepthStencilView > m_dsv;

		mutable bool m_hdr0_to_hdr1;

		bool m_msaa;
		bool m_ssaa;
	};
}