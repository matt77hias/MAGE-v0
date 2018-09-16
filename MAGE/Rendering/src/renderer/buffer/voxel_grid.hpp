#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\camera\viewport.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	class VoxelGrid {

	public:

		explicit VoxelGrid(ID3D11Device& device, std::size_t resolution);
		VoxelGrid(const VoxelGrid& voxel_grid) = delete;
		VoxelGrid(VoxelGrid&& voxel_grid) noexcept;
		~VoxelGrid();

		VoxelGrid& operator=(const VoxelGrid& voxel_grid) = delete;
		VoxelGrid& operator=(VoxelGrid&& voxel_grid) noexcept;

		[[nodiscard]]
		std::size_t GetResolution() const noexcept {
			return m_resolution;
		}

		void BindBeginVoxelizationBuffer(
			ID3D11DeviceContext& device_context) const noexcept;
		void BindEndVoxelizationBuffer(
			ID3D11DeviceContext& device_context) const noexcept;
		void BindBeginVoxelizationTexture(
			ID3D11DeviceContext& device_context) const noexcept;
		void BindEndVoxelizationTexture(
			ID3D11DeviceContext& device_context) const noexcept;

	private:

		void SetupVoxelGrid(ID3D11Device& device);

		void SetupStructuredBuffer(ID3D11Device& device);
		void SetupTexture(ID3D11Device& device);

		std::size_t m_resolution;
		Viewport m_viewport;

		ComPtr< ID3D11ShaderResourceView > m_buffer_srv;
		ComPtr< ID3D11UnorderedAccessView > m_buffer_uav;

		ComPtr< ID3D11ShaderResourceView > m_texture_srv;
		ComPtr< ID3D11UnorderedAccessView > m_texture_uav;
	};
}