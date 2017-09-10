#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"
#include "rendering\pipeline.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct GBuffer final {

	public:

		GBuffer();
		explicit GBuffer(ID3D11Device2 *device);
		GBuffer(const GBuffer &buffer) = delete;
		GBuffer(GBuffer &&buffer) = default;
		~GBuffer() = default;

		GBuffer &operator=(const GBuffer &buffer) = delete;
		GBuffer &operator=(GBuffer &&buffer) = delete;

		void BindPacking(ID3D11DeviceContext2 *device_context) noexcept;
		void BindUnpacking(ID3D11DeviceContext2 *device_context) noexcept;
		void BindRestore(ID3D11DeviceContext2 *device_context) noexcept;

	private:

		enum struct GBufferIndex {
			Diffuse  = 0,
			Specular = 1,
			Normal   = 2,
			Depth    = 3,
			Count    = 4
		};

		static constexpr UINT GetNumberOfRTVs() noexcept {
			return static_cast< UINT >(GBufferIndex::Count) - 1u;
		}
		static constexpr UINT GetNumberOfSRVs() noexcept {
			return static_cast< UINT >(GBufferIndex::Count);
		}

		void SetupBuffers(ID3D11Device2 *device);
		void SetupDepthBuffer(ID3D11Device2 *device,
			UINT width, UINT height);
		void SetupDiffuseBuffer(ID3D11Device2 *device,
			UINT width, UINT height);
		void SetupSpecularBuffer(ID3D11Device2 *device,
			UINT width, UINT height);
		void SetupNormalBuffer(ID3D11Device2 *device,
			UINT width, UINT height);
		void SetupBuffer(ID3D11Device2 *device, UINT index,
			UINT width, UINT height, DXGI_FORMAT format);
		void SetupOutputBuffer(ID3D11Device2 *device,
			UINT width, UINT height);
		
		// GBuffer
		ComPtr< ID3D11DepthStencilView >   m_dsv;
		ComPtr< ID3D11RenderTargetView >   m_rtvs[static_cast< UINT >(GBufferIndex::Count) - 1u];
		ComPtr< ID3D11ShaderResourceView > m_srvs[static_cast< UINT >(GBufferIndex::Count)];

		// Output
		ComPtr< ID3D11UnorderedAccessView > m_image_uav;
		ComPtr< ID3D11ShaderResourceView >  m_image_srv;
	};
}
