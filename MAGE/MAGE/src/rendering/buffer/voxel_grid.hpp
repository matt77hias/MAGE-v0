#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\viewport.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class VoxelGrid final {

	public:

		explicit VoxelGrid(size_t resolution);
		explicit VoxelGrid(ID3D11Device *device, size_t resolution);
		VoxelGrid(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid(VoxelGrid &&voxel_grid) = default;
		~VoxelGrid() = default;

		VoxelGrid &operator=(const VoxelGrid &voxel_grid) = delete;
		VoxelGrid &operator=(VoxelGrid &&voxel_grid) = delete;

		size_t GetResolution() const noexcept {
			return m_resolution;
		}

		void BindViewport(D3D11DeviceContext *device_context) const noexcept {
			m_viewport.BindViewport(device_context);
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

		void SetupVoxelGrid(ID3D11Device *device);

		void SetupStructuredBuffer(ID3D11Device *device);
		void SetupTexture(ID3D11Device *device);

		size_t m_resolution;
		Viewport m_viewport;

		ComPtr< ID3D11ShaderResourceView > m_buffer_srv;
		ComPtr< ID3D11UnorderedAccessView > m_buffer_uav;

		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
		ComPtr< ID3D11UnorderedAccessView > m_texture_uav;
	};
}