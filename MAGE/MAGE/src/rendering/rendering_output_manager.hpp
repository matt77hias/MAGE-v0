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
		 @throws		FormattedException
						Failed to setup the rendering outputs of this rendering 
						output manager.
		 */
		explicit RenderingOutputManager(
			ID3D11Device2 *device, U32 width, U32 height);

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
		void BindEnd(ID3D11DeviceContext2 *device_context) const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		enum struct SRVIndex {
			GBuffer_BaseColor = 0,
			GBuffer_Material  = 1,
			GBuffer_Normal    = 2,
			GBuffer_Depth     = 3,
			HDR0              = 4,
			HDR1              = 5,
			Count             = 6
		};

		enum struct RTVIndex {
			GBuffer_BaseColor = 0,
			GBuffer_Material  = 1,
			GBuffer_Normal    = 2,
			HDR0              = 3,
			HDR1              = 4,
			Count             = 5
		};

		enum struct UAVIndex {
			HDR0  = 0,
			HDR1  = 1,
			Count = 2
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

		void SetupBuffers(ID3D11Device2 *device, U32 width, U32 height);

		void SetupBuffer(ID3D11Device2 *device, U32 width, U32 height, 
			DXGI_FORMAT format, ID3D11ShaderResourceView **srv,
			ID3D11RenderTargetView **rtv, ID3D11UnorderedAccessView **uav);

		void SetupDepthBuffer(ID3D11Device2 *device, U32 width, U32 height);

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
	};
}