#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
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

		void BindRTVsAndDSV(ID3D11DeviceContext2 *device_context) noexcept;
		void BindSRVs(ID3D11DeviceContext2 *device_context, UINT slot) noexcept;
		void ClearRTVsAndDSV(ID3D11DeviceContext2 *device_context) noexcept;

	private:

		enum struct GBufferIndex {
			Normal   = 0,
			Diffuse  = 1,
			Specular = 2,
			Depth    = 3,
			Count    = 4
		};

		static constexpr UINT GetNumberOfRTVs() noexcept {
			return GetNumberOfSRVs() - 1;
		}
		
		static constexpr UINT GetNumberOfSRVs() noexcept {
			return static_cast< size_t >(GBufferIndex::Count);
		}

		void SetupBuffers(ID3D11Device2 *device);
		void SetupBuffer(ID3D11Device2 *device, UINT index,
			UINT width, UINT height, DXGI_FORMAT format);
		void SetupDepthBuffer(ID3D11Device2 *device,
			UINT width, UINT height);

		ComPtr< ID3D11RenderTargetView > m_rtvs[static_cast< size_t >(GBufferIndex::Count) - 1];
		ComPtr< ID3D11DepthStencilView > m_dsv;
		ComPtr< ID3D11ShaderResourceView > m_srvs[static_cast< size_t >(GBufferIndex::Count)];
	};
}
