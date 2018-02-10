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
		explicit VoxelGrid(ID3D11Device3 *device, size_t resolution);
		VoxelGrid(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid(VoxelGrid &&voxel_grid) = default;
		~VoxelGrid() = default;

		VoxelGrid &operator=(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid &operator=(VoxelGrid &&voxel_grid) = delete;

		size_t GetResolution() const noexcept {
			return m_resolution;
		}

		void BindBeginVoxelizationBuffer(
			ID3D11DeviceContext4 *device_context) const noexcept;
		void BindEndVoxelizationBuffer(
			ID3D11DeviceContext4 *device_context) const noexcept;
		void BindBeginVoxelizationTexture(
			ID3D11DeviceContext4 *device_context) const noexcept;
		void BindEndVoxelizationTexture(
			ID3D11DeviceContext4 *device_context) const noexcept;

	private:

		void SetupVoxelGrid(ID3D11Device3 *device);

		void SetupStructuredBuffer(ID3D11Device3 *device);
		void SetupTexture(ID3D11Device3 *device);

		size_t m_resolution;

		ComPtr< ID3D11ShaderResourceView > m_buffer_srv;
		ComPtr< ID3D11UnorderedAccessView > m_buffer_uav;

		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
		ComPtr< ID3D11UnorderedAccessView > m_texture_uav;
	};
}