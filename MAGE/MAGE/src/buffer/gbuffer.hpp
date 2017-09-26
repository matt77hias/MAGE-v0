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

	private:

		enum struct GBufferIndex {
			Diffuse  = 0,
			Specular = 1,
			Normal   = 2,
			Depth    = 3,
			Count    = 4
		};

		static constexpr size_t GetNumberOfRTVs() noexcept {
			return static_cast< size_t >(GBufferIndex::Count) - 1u;
		}
		static constexpr size_t GetNumberOfSRVs() noexcept {
			return static_cast< size_t >(GBufferIndex::Count);
		}

		void SetupBuffers(ID3D11Device2 *device);
		void SetupDepthBuffer(ID3D11Device2 *device,
			u32 width, u32 height);
		void SetupDiffuseBuffer(ID3D11Device2 *device,
			u32 width, u32 height);
		void SetupSpecularBuffer(ID3D11Device2 *device,
			u32 width, u32 height);
		void SetupNormalBuffer(ID3D11Device2 *device,
			u32 width, u32 height);
		void SetupBuffer(ID3D11Device2 *device, u32 index,
			u32 width, u32 height, DXGI_FORMAT format);

		ComPtr< ID3D11DepthStencilView >   m_dsv;
		ComPtr< ID3D11RenderTargetView >   m_rtvs[
			static_cast< size_t >(GBufferIndex::Count) - 1u];
		ComPtr< ID3D11ShaderResourceView > m_srvs[
			static_cast< size_t >(GBufferIndex::Count)];
	};
}
