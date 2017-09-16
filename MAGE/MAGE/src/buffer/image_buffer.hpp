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

	struct ImageBuffer final {

	public:

		ImageBuffer();
		explicit ImageBuffer(ID3D11Device2 *device);
		ImageBuffer(const ImageBuffer &buffer) = delete;
		ImageBuffer(ImageBuffer &&buffer) = default;
		~ImageBuffer() = default;

		ImageBuffer &operator=(const ImageBuffer &buffer) = delete;
		ImageBuffer &operator=(ImageBuffer &&buffer) = delete;

		void BindPacking(ID3D11DeviceContext2 *device_context) noexcept;
		void BindUnpacking(ID3D11DeviceContext2 *device_context) noexcept;

	private:

		void SetupBuffer(ID3D11Device2 *device, UINT width, UINT height);

		ComPtr< ID3D11UnorderedAccessView > m_uav;
		ComPtr< ID3D11ShaderResourceView >  m_srv;
	};
}