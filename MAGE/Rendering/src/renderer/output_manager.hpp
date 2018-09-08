#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\swap_chain.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A class of output managers.
	 */
	class OutputManager {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a output manager.

		 @param[in]		device
						A reference to the device.
		 @param[in]		display_configuration
						A reference to the display configuration.
		  @param[in]	swap_chain
						A reference to the swap chain.
		 @throws		Exception
						Failed to setup the rendering outputs of this output 
						manager.
		 */
		explicit OutputManager(ID3D11Device& device, 
							   DisplayConfiguration& display_configuration,
							   SwapChain& swap_chain);

		/**
		 Constructs a output manager from the given output manager.

		 @param[in]		manager
						A reference to the output manager to copy.
		 */
		OutputManager(const OutputManager& manager) = delete;

		/**
		 Constructs a output manager by moving the given output manager.

		 @param[in]		manager
						A reference to the output manager to move.
		 */
		OutputManager(OutputManager&& manager) noexcept;

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
		OutputManager& operator=(const OutputManager& manager) = delete;

		/**
		 Moves the given output manager to this output manager.

		 @param[in]		manager
						A reference to the output manager to move.
		 @return		A reference to the moved output manager (i.e. this 
						output manager).
		 */
		OutputManager& operator=(OutputManager&& manager) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void BindBegin(ID3D11DeviceContext& device_context) const noexcept;
		void BindBeginViewport(ID3D11DeviceContext& device_context) const noexcept;
		void BindBeginGBuffer(ID3D11DeviceContext& device_context) const noexcept;
		void BindEndGBuffer(ID3D11DeviceContext& device_context) const noexcept;
		void BindBeginDeferred(ID3D11DeviceContext& device_context) const noexcept;
		void BindEndDeferred(ID3D11DeviceContext& device_context) const noexcept;
		void BindBeginForward(ID3D11DeviceContext& device_context) const noexcept;
		void BindEndForward(ID3D11DeviceContext& device_context) const noexcept;
		void BindBeginResolve(ID3D11DeviceContext& device_context) const noexcept;
		void BindEndResolve(ID3D11DeviceContext& device_context) const noexcept;
		void BindBeginPostProcessing(ID3D11DeviceContext& device_context) const noexcept;
		void BindPingPong(ID3D11DeviceContext& device_context) const noexcept;
		void BindEndPostProcessing(ID3D11DeviceContext& device_context) const noexcept;
		void BindEndViewport(ID3D11DeviceContext& device_context) const noexcept;
		void BindGUI(ID3D11DeviceContext& device_context) const noexcept;
		void BindEnd(ID3D11DeviceContext& device_context) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		enum class SRVIndex : U8 {
			HDR = 0,
			GBuffer_BaseColor,
			GBuffer_Material,
			GBuffer_Normal,
			GBuffer_Depth,
			PostProcessing_HDR0,
			PostProcessing_HDR1,
			PostProcessing_Normal,
			PostProcessing_Depth,
			LDR,
			Count
		};

		enum class RTVIndex : U8 {
			HDR = 0,
			GBuffer_BaseColor,
			GBuffer_Material,
			GBuffer_Normal,
			PostProcessing_HDR0,
			PostProcessing_HDR1,
			LDR,
			Count
		};

		enum class UAVIndex : U8 {
			HDR = 0,
			PostProcessing_HDR0,
			PostProcessing_HDR1,
			PostProcessing_Normal,
			PostProcessing_Depth,
			LDR,
			Count
		};

		[[nodiscard]]
		ID3D11ShaderResourceView* GetSRV(SRVIndex index) const noexcept {
			return m_srvs[static_cast< size_t >(index)].Get();
		}
		
		[[nodiscard]]
		NotNull< ID3D11ShaderResourceView** > 
			ReleaseAndGetAddressOfSRV(SRVIndex index) noexcept {

			auto& srv = m_srvs[static_cast< size_t >(index)];
			return NotNull< ID3D11ShaderResourceView** >(srv.ReleaseAndGetAddressOf());
		}
		
		[[nodiscard]]
		ID3D11RenderTargetView* GetRTV(RTVIndex index) const noexcept {
			return m_rtvs[static_cast< size_t >(index)].Get();
		}
		
		[[nodiscard]]
		NotNull< ID3D11RenderTargetView** > 
			ReleaseAndGetAddressOfRTV(RTVIndex index) noexcept {

			auto& rtv = m_rtvs[static_cast< size_t >(index)];
			return NotNull< ID3D11RenderTargetView** >(rtv.ReleaseAndGetAddressOf());
		}
		
		[[nodiscard]]
		ID3D11UnorderedAccessView* GetUAV(UAVIndex index) const noexcept {
			return m_uavs[static_cast< size_t >(index)].Get();
		}
		
		[[nodiscard]]
		NotNull< ID3D11UnorderedAccessView** > 
			ReleaseAndGetAddressOfUAV(UAVIndex index) noexcept {

			auto& uav = m_uavs[static_cast< size_t >(index)];
			return NotNull< ID3D11UnorderedAccessView** >(uav.ReleaseAndGetAddressOf());
		}

		void SetupBuffers();

		void SetupBuffer(const U32x3& resolution, 
			             DXGI_FORMAT format,
			             ID3D11ShaderResourceView** srv, 
			             ID3D11RenderTargetView** rtv, 
			             ID3D11UnorderedAccessView** uav);

		void SetupDepthBuffer(const U32x3& resolution);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		std::reference_wrapper< DisplayConfiguration > m_display_configuration;
		std::reference_wrapper< ID3D11Device > m_device;
		std::reference_wrapper< SwapChain > m_swap_chain;

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