//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\buffer\voxel_grid.hpp"
#include "rendering\rendering_factory.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VoxelGrid::VoxelGrid(size_t resolution)
		: VoxelGrid(Pipeline::GetDevice(), resolution) {}

	VoxelGrid::VoxelGrid(ID3D11Device5 *device, size_t resolution)
		: m_resolution(resolution) {

		SetupVoxelGrid(device);
	}

	void VoxelGrid::SetupVoxelGrid(ID3D11Device5 *device) {
		Assert(device);

		SetupVoxelGridStructuredBuffer(device);
		SetupVoxelGridTexture(device);
	}

	void VoxelGrid::SetupVoxelGridStructuredBuffer(ID3D11Device5 *device) {
		Assert(device);

		const size_t nb_voxels = m_resolution * m_resolution * m_resolution;

		ComPtr< ID3D11Buffer > buffer;
		
		// Create the structured buffer.
		{
			// Create the buffer descriptor.
			D3D11_BUFFER_DESC buffer_desc = {};
			buffer_desc.BindFlags           = D3D11_BIND_SHADER_RESOURCE 
											| D3D11_BIND_UNORDERED_ACCESS;
			buffer_desc.MiscFlags           = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
			buffer_desc.ByteWidth           = static_cast< U32 >(2u * sizeof(U32) * nb_voxels);
			buffer_desc.StructureByteStride = static_cast< U32 >(2u * sizeof(U32));
			// GPU:    read +    write
			// CPU: no read + no write
			buffer_desc.Usage               = D3D11_USAGE_DEFAULT;
			
			const HRESULT result = device->CreateBuffer(
				&buffer_desc, nullptr, buffer.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Structured buffer creation failed: %08X.", result);
		}

		// Create the SRV.
		{
			// Create he SRV descriptor.
			D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
			srv_desc.Format              = DXGI_FORMAT_UNKNOWN;
			srv_desc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
			srv_desc.Buffer.FirstElement = 0u;
			srv_desc.Buffer.NumElements  = static_cast< U32 >(nb_voxels);
			
			const HRESULT result = device->CreateShaderResourceView(
				buffer.Get(), &srv_desc, m_grid_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "SRV creation failed: %08X.", result);
		}

		// Create the UAV.
		{
			// Create ther UAV descriptor.
			D3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc = {};
			uav_desc.Format              = DXGI_FORMAT_UNKNOWN;
			uav_desc.ViewDimension       = D3D11_UAV_DIMENSION_BUFFER;
			uav_desc.Buffer.FirstElement = 0u;
			uav_desc.Buffer.NumElements  = static_cast< U32 >(nb_voxels);

			const HRESULT result = device->CreateUnorderedAccessView(
				buffer.Get(), &uav_desc, m_grid_uav.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "UAV creation failed: %08X.", result);
		}
	}

	void VoxelGrid::SetupVoxelGridTexture(ID3D11Device5 *device) {
		Assert(device);

		ComPtr< ID3D11Texture3D > texture;

		// Create the texture.
		{
			// Create the texture descriptor.
			D3D11_TEXTURE3D_DESC texture_desc = {};
			texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE
								   | D3D11_BIND_UNORDERED_ACCESS;
			texture_desc.Width     = static_cast< U32 >(m_resolution);
			texture_desc.Height    = static_cast< U32 >(m_resolution);
			texture_desc.Depth     = static_cast< U32 >(m_resolution);
			texture_desc.MipLevels = 0u;
			texture_desc.Format    = DXGI_FORMAT_R16G16B16A16_FLOAT;
			// GPU:    read +    write
			// CPU: no read + no write
			texture_desc.Usage     = D3D11_USAGE_DEFAULT;
			
			const HRESULT result = device->CreateTexture3D(
				&texture_desc, nullptr, texture.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture 3D creation failed: %08X.", result);
		}

		// Create the SRV.
		{
			const HRESULT result = device->CreateShaderResourceView(
				texture.Get(), nullptr, m_texture_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "SRV creation failed: %08X.", result);
		}

		// Create the UAV.
		{
			const HRESULT result = device->CreateUnorderedAccessView(
				texture.Get(), nullptr, m_texture_uav.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "UAV creation failed: %08X.", result);
		}
	}
}