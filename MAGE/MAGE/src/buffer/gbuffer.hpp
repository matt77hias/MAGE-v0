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
			Count    = 3
		};

		static constexpr UINT GetNumberOfRTVs() noexcept {
			return static_cast< UINT >(GBufferIndex::Count);
		}
		static constexpr UINT GetNumberOfSRVs() noexcept {
			return static_cast< UINT >(GBufferIndex::Count);
		}

		void SetupBuffers(ID3D11Device2 *device);
		void SetupBuffer(ID3D11Device2 *device, UINT index,
			UINT width, UINT height, DXGI_FORMAT format);

		ComPtr< ID3D11RenderTargetView >   m_rtvs[static_cast< UINT >(GBufferIndex::Count)];
		ComPtr< ID3D11ShaderResourceView > m_srvs[static_cast< UINT >(GBufferIndex::Count)];
	};
}
