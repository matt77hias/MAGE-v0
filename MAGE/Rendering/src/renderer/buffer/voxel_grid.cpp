//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\buffer\voxel_grid.hpp"
#include "renderer\factory.hpp"
#include "exception\exception.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	VoxelGrid::VoxelGrid(ID3D11Device& device, std::size_t resolution)
		: m_resolution(resolution), 
		m_viewport(U32x2(static_cast< U32 >(resolution), 
						 static_cast< U32 >(resolution))),
		m_buffer_srv(), 
		m_buffer_uav(), 
		m_texture_srv(), 
		m_texture_uav() {

		SetupVoxelGrid(device);
	}

	VoxelGrid::VoxelGrid(VoxelGrid&& voxel_grid) noexcept = default;

	VoxelGrid::~VoxelGrid() = default;

	VoxelGrid& VoxelGrid::operator=(VoxelGrid&& voxel_grid) noexcept = default;

	void VoxelGrid::SetupVoxelGrid(ID3D11Device& device) {
		SetupStructuredBuffer(device);
		SetupTexture(device);
	}

	void VoxelGrid::SetupStructuredBuffer(ID3D11Device& device) {
		const auto nb_voxels = m_resolution * m_resolution * m_resolution;

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
			
			auto data = DynamicArray< U8 >(buffer_desc.ByteWidth);
			memset(data.data(), 0, data.size());

			D3D11_SUBRESOURCE_DATA init_data = {};
			init_data.pSysMem = data.data();

			const HRESULT result = device.CreateBuffer(
				&buffer_desc, &init_data, buffer.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Structured buffer creation failed: {:08X}.", result);
		}

		// Create the SRV.
		{
			// Create he SRV descriptor.
			D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc = {};
			srv_desc.Format              = DXGI_FORMAT_UNKNOWN;
			srv_desc.ViewDimension       = D3D11_SRV_DIMENSION_BUFFER;
			srv_desc.Buffer.FirstElement = 0u;
			srv_desc.Buffer.NumElements  = static_cast< U32 >(nb_voxels);
			
			const HRESULT result = device.CreateShaderResourceView(
				buffer.Get(), &srv_desc, m_buffer_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "SRV creation failed: {:08X}.", result);
		}

		// Create the UAV.
		{
			// Create ther UAV descriptor.
			D3D11_UNORDERED_ACCESS_VIEW_DESC uav_desc = {};
			uav_desc.Format              = DXGI_FORMAT_UNKNOWN;
			uav_desc.ViewDimension       = D3D11_UAV_DIMENSION_BUFFER;
			uav_desc.Buffer.FirstElement = 0u;
			uav_desc.Buffer.NumElements  = static_cast< U32 >(nb_voxels);

			const HRESULT result = device.CreateUnorderedAccessView(
				buffer.Get(), &uav_desc, m_buffer_uav.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "UAV creation failed: {:08X}.", result);
		}
	}

	void VoxelGrid::SetupTexture(ID3D11Device& device) {
		ComPtr< ID3D11Texture3D > texture;

		// Create the texture.
		{
			// Create the texture descriptor.
			D3D11_TEXTURE3D_DESC texture_desc = {};
			texture_desc.BindFlags = D3D11_BIND_RENDER_TARGET 
				                   | D3D11_BIND_SHADER_RESOURCE
								   | D3D11_BIND_UNORDERED_ACCESS;
			texture_desc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
			texture_desc.Width     = static_cast< U32 >(m_resolution);
			texture_desc.Height    = static_cast< U32 >(m_resolution);
			texture_desc.Depth     = static_cast< U32 >(m_resolution);
			texture_desc.MipLevels = 0u;
			texture_desc.Format    = DXGI_FORMAT_R16G16B16A16_FLOAT;
			// GPU:    read +    write
			// CPU: no read + no write
			texture_desc.Usage     = D3D11_USAGE_DEFAULT;
			
			const HRESULT result = device.CreateTexture3D(
				&texture_desc, nullptr, texture.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "Texture 3D creation failed: {:08X}.", result);
		}

		// Create the SRV.
		{
			const HRESULT result = device.CreateShaderResourceView(
				texture.Get(), nullptr, m_texture_srv.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "SRV creation failed: {:08X}.", result);
		}

		// Create the UAV.
		{
			const HRESULT result = device.CreateUnorderedAccessView(
				texture.Get(), nullptr, m_texture_uav.ReleaseAndGetAddressOf());
			ThrowIfFailed(result, "UAV creation failed: {:08X}.", result);
		}
	}

	void VoxelGrid::BindBeginVoxelizationBuffer(
		ID3D11DeviceContext& device_context) const noexcept {
		
		Pipeline::VS::BindSRV(device_context, SLOT_SRV_VOXEL_TEXTURE,
							  nullptr);
		Pipeline::PS::BindSRV(device_context, SLOT_SRV_VOXEL_TEXTURE,
							  nullptr);
		Pipeline::CS::BindSRV(device_context, SLOT_SRV_VOXEL_TEXTURE,
							  nullptr);

		Pipeline::OM::BindRTVAndDSVAndUAV(device_context, nullptr, nullptr, 
										  SLOT_UAV_VOXEL_BUFFER, 
										  m_buffer_uav.Get());

		m_viewport.Bind(device_context);
	}

	void VoxelGrid::BindEndVoxelizationBuffer(
		ID3D11DeviceContext& device_context) const noexcept {

		Pipeline::OM::BindRTVAndDSVAndUAV(device_context, nullptr, nullptr, 
										  SLOT_UAV_VOXEL_BUFFER, 
										  nullptr);
	}

	void VoxelGrid::BindBeginVoxelizationTexture(
		ID3D11DeviceContext& device_context) const noexcept {

		Pipeline::CS::BindUAV(device_context, SLOT_UAV_VOXEL_BUFFER, 
							  m_buffer_uav.Get());
		Pipeline::CS::BindUAV(device_context, SLOT_UAV_VOXEL_TEXTURE, 
							  m_texture_uav.Get());
	}

	void VoxelGrid::BindEndVoxelizationTexture(
		ID3D11DeviceContext& device_context) const noexcept {

		Pipeline::CS::BindUAV(device_context, SLOT_UAV_VOXEL_BUFFER, 
							  nullptr);
		Pipeline::CS::BindUAV(device_context, SLOT_UAV_VOXEL_TEXTURE, 
							  nullptr);

		device_context.GenerateMips(m_texture_srv.Get());

		Pipeline::VS::BindSRV(device_context, SLOT_SRV_VOXEL_TEXTURE, 
							  m_texture_srv.Get());
		Pipeline::PS::BindSRV(device_context, SLOT_SRV_VOXEL_TEXTURE,
							  m_texture_srv.Get());
		Pipeline::CS::BindSRV(device_context, SLOT_SRV_VOXEL_TEXTURE,
							  m_texture_srv.Get());
	}
}