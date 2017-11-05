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
	 A class of rendering output managers.
	 */
	class RenderingOutputManager final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the rendering output manager of the rendering manager 
		 associated with the current engine.

		 @pre			The rendering manager associated with the current 
						engine must be loaded.
		 @return		A pointer to the rendering output manager of the 
						rendering manager associated with the current engine.
		 */
		static const RenderingOutputManager *Get() noexcept;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a rendering output manager.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[in]		width
						The width in pixels of the back buffer.
		 @param[in]		height
						The height in pixels of the back buffer.
		 @param[in]		desc
						The Anti-Aliasing descriptor.
		 @throws		FormattedException
						Failed to setup the rendering outputs of this rendering 
						output manager.
		 */
		explicit RenderingOutputManager(ID3D11Device2 *device, 
			U32 width, U32 height, AADescriptor desc);

		/**
		 Constructs a rendering output manager from the given rendering output 
		 manager.

		 @param[in]		rendering_output_manager
						A reference to the rendering output manager to copy.
		 */
		RenderingOutputManager(
			const RenderingOutputManager &rendering_output_manager) = delete;

		/**
		 Constructs a rendering output manager by moving the given rendering 
		 output manager.

		 @param[in]		rendering_output_manager
						A reference to the rendering output manager to move.
		 */
		RenderingOutputManager(
			RenderingOutputManager &&rendering_output_manager);

		/**
		 Destructs this rendering output manager.
		 */
		~RenderingOutputManager();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given rendering output manager to this rendering output 
		 manager.

		 @param[in]		rendering_output_manager
						A reference to the rendering output manager to copy.
		 @return		A reference to the copy of the given rendering output 
						manager (i.e. this rendering output manager).
		 */
		RenderingOutputManager &operator=(
			const RenderingOutputManager &rendering_output_manager) = delete;

		/**
		 Moves the given rendering output manager to this rendering output 
		 manager.

		 @param[in]		rendering_output_manager
						A reference to the rendering output manager to move.
		 @return		A reference to the moved rendering output manager
						(i.e. this rendering output manager).
		 */
		RenderingOutputManager &operator=(
			RenderingOutputManager &&rendering_output_manager) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void Clear(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindBegin(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindBeginGBuffer(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindEndGBuffer(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindBeginDeferred(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindEndDeferred(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindBeginForward(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindEndForward(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindBeginResolve(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindEndResolve(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindPingPong(ID3D11DeviceContext2 *device_context) const noexcept;
		void BindEnd(ID3D11DeviceContext2 *device_context) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		enum struct SRVIndex {
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

		enum struct RTVIndex {
			HDR                 = 0,
			GBuffer_BaseColor   = 1,
			GBuffer_Material    = 2,
			GBuffer_Normal      = 3,
			PostProcessing_HDR0 = 4,
			PostProcessing_HDR1 = 5,
			Count               = 6
		};

		enum struct UAVIndex {
			HDR                   = 0,
			PostProcessing_HDR0   = 1,
			PostProcessing_HDR1   = 2,
			PostProcessing_Normal = 3,
			PostProcessing_Depth  = 4,
			Count                 = 5
		};

		ID3D11ShaderResourceView *GetSRV(SRVIndex index) const noexcept {
			return m_srvs[static_cast< size_t >(index)].Get();
		}
		
		ID3D11ShaderResourceView **ReleaseAndGetAddressOfSRV(SRVIndex index) noexcept {
			return m_srvs[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}
		
		ID3D11RenderTargetView *GetRTV(RTVIndex index) const noexcept {
			return m_rtvs[static_cast< size_t >(index)].Get();
		}
		
		ID3D11RenderTargetView **ReleaseAndGetAddressOfRTV(RTVIndex index) noexcept {
			return m_rtvs[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}
		
		ID3D11UnorderedAccessView *GetUAV(UAVIndex index) const noexcept {
			return m_uavs[static_cast< size_t >(index)].Get();
		}
		
		ID3D11UnorderedAccessView **ReleaseAndGetAddressOfUAV(UAVIndex index) noexcept {
			return m_uavs[static_cast< size_t >(index)].ReleaseAndGetAddressOf();
		}

		void SetupBuffers(ID3D11Device2 *device, 
			U32 width, U32 height, AADescriptor desc);

		void SetupBuffer(ID3D11Device2 *device, 
			U32 width, U32 height, U32 nb_samples, DXGI_FORMAT format,
			ID3D11ShaderResourceView **srv, ID3D11RenderTargetView **rtv, 
			ID3D11UnorderedAccessView **uav);

		void SetupDepthBuffer(ID3D11Device2 *device, 
			U32 width, U32 height, U32 nb_samples);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

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