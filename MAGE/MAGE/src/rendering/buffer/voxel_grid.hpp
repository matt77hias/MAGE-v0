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

	class VoxelGrid final {

	public:

		explicit VoxelGrid(size_t resolution);
		explicit VoxelGrid(D3D11Device *device, size_t resolution);
		VoxelGrid(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid(VoxelGrid &&voxel_grid) = default;
		~VoxelGrid() = default;

		VoxelGrid &operator=(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid &operator=(VoxelGrid &&voxel_grid) = delete;

		size_t GetResolution() const noexcept {
			return m_resolution;
		}

		void BindBeginVoxelizationBuffer(
			D3D11DeviceContext *device_context) const noexcept;
		void BindEndVoxelizationBuffer(
			D3D11DeviceContext *device_context) const noexcept;
		void BindBeginVoxelizationTexture(
			D3D11DeviceContext *device_context) const noexcept;
		void BindEndVoxelizationTexture(
			D3D11DeviceContext *device_context) const noexcept;

	private:

		void SetupVoxelGrid(D3D11Device *device);

		void SetupStructuredBuffer(D3D11Device *device);
		void SetupTexture(D3D11Device *device);

		size_t m_resolution;

		ComPtr< ID3D11ShaderResourceView > m_buffer_srv;
		ComPtr< ID3D11UnorderedAccessView > m_buffer_uav;

		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
		ComPtr< ID3D11UnorderedAccessView > m_texture_uav;
	};
}