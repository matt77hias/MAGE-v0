//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\voxelization_pass.hpp"
#include "renderer\state_manager.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	VoxelizationPass::VoxelizationPass(ID3D11Device& device,
									   ID3D11DeviceContext& device_context,
									   StateManager& state_manager,
									   ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_resource_manager(resource_manager),
		m_rs(),
		m_vs(CreateVoxelizationVS(resource_manager)),
		m_gs(CreateVoxelizationGS(resource_manager)),
		m_cs(CreateVoxelizationCS(resource_manager)),
		m_voxel_grid(MakeUnique< VoxelGrid >(device, 1u)) {

		SetupRasterizerState(device);
	}

	VoxelizationPass::VoxelizationPass(VoxelizationPass&& pass) noexcept = default;

	VoxelizationPass::~VoxelizationPass() = default;

	VoxelizationPass& VoxelizationPass
		::operator=(VoxelizationPass&& pass) noexcept = default;

	void VoxelizationPass::SetupRasterizerState(ID3D11Device& device) {
		D3D11_RASTERIZER_DESC2 desc = {};
		desc.CullMode          = D3D11_CULL_NONE;
		desc.FillMode          = D3D11_FILL_SOLID;
		desc.DepthClipEnable   = TRUE;
		desc.MultisampleEnable = TRUE;
		desc.ForcedSampleCount = 8u;

		ComPtr< ID3D11Device  > device0(&device);
		ComPtr< ID3D11Device3 > device3;
		{
			// Get the ID3D11Device3.
			const HRESULT result = device0.As(&device3);
			ThrowIfFailed(result,
						  "ID3D11Device3 creation failed: {:08X}.", result);
		}

		// Create the ID3D11RasterizerState2.
		{
			const HRESULT result 
				= device3->CreateRasterizerState2(&desc, 
												  m_rs.ReleaseAndGetAddressOf());
			ThrowIfFailed(result,
						  "ID3D11RasterizerState2 creation failed: {:08X}.", result);
		}
	}

	void VoxelizationPass::SetupVoxelGrid(std::size_t resolution) {
		if (m_voxel_grid->GetResolution() != resolution) {
			ComPtr< ID3D11Device > device;
			m_device_context.get().GetDevice(device.ReleaseAndGetAddressOf());
			m_voxel_grid = MakeUnique< VoxelGrid >(*device.Get(), resolution);
		}
	}

	void VoxelizationPass::BindFixedState() const noexcept {
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		m_gs->BindShader(m_device_context);
		// RS: Bind the rasterization state.
		Pipeline::RS::BindState(m_device_context, m_rs.Get());
		// OM: Bind the depth-stencil state.
		m_state_manager.get().Bind(m_device_context, 
								   DepthStencilStateID::DepthNone);
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context, 
								   BlendStateID::Opaque);
	}

	void XM_CALLCONV VoxelizationPass::Render(const World& world,
											  FXMMATRIX world_to_projection,
											  std::size_t resolution) {
		SetupVoxelGrid(resolution);

		m_voxel_grid->BindBeginVoxelizationBuffer(m_device_context);
		Render(world, world_to_projection);
		m_voxel_grid->BindEndVoxelizationBuffer(m_device_context);

		m_voxel_grid->BindBeginVoxelizationTexture(m_device_context);
		Dispatch();
		m_voxel_grid->BindEndVoxelizationTexture(m_device_context);
	}

	void XM_CALLCONV VoxelizationPass::Render(const World& world,
											  FXMMATRIX world_to_projection) const {
		// Bind the fixed opaque state.
		BindFixedState();

		constexpr bool transparency = false;
		
		//---------------------------------------------------------------------
		// All emissive models.
		//---------------------------------------------------------------------
		{
			const PixelShaderPtr ps = CreateVoxelizationEmissivePS(m_resource_manager);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !material.IsEmissive()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All models with no TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = false;
			const PixelShaderPtr ps = CreateVoxelizationPS(m_resource_manager, 
														   tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr != material.GetNormalSRV()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All models with TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = true;
			const PixelShaderPtr ps = CreateVoxelizationPS(m_resource_manager, 
														   tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		world.ForEach< Model >([this, world_to_projection](const Model& model) {

			const auto& material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| material.IsEmissive()
				|| nullptr == material.GetNormalSRV()
				|| material.GetBaseColor()[3] < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV VoxelizationPass::Render(const Model& model, 
											  FXMMATRIX world_to_projection) const noexcept {

		const auto& transform            = model.GetOwner()->GetTransform();
		const auto  object_to_world      = transform.GetObjectToWorldMatrix();
		const auto  object_to_projection = object_to_world * world_to_projection;

		// Apply view frustum culling.
		if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) { 
			return;
		}

		const auto& material             = model.GetMaterial();

		// Bind the constant buffer of the model.
		model.BindBuffer< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
		model.BindBuffer< Pipeline::PS >(m_device_context, SLOT_CBUFFER_MODEL);
		// Bind the SRVs of the model.
		static_assert(SLOT_SRV_MATERIAL == SLOT_SRV_BASE_COLOR + 1);
		static_assert(SLOT_SRV_NORMAL   == SLOT_SRV_BASE_COLOR + 2);
		ID3D11ShaderResourceView* const srvs[] = {
			material.GetBaseColorSRV(),
			material.GetMaterialSRV(),
			material.GetNormalSRV()
		};
		Pipeline::PS::BindSRVs(m_device_context, SLOT_SRV_BASE_COLOR, 
							   static_cast< U32 >(std::size(srvs)), srvs);
		// Bind the mesh of the model.
		model.BindMesh(m_device_context);
		// Draw the model.
		model.Draw(m_device_context);
	}

	void VoxelizationPass::Dispatch() const noexcept {
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);

		// Dispatch.
		const auto nb_groups = GetNumberOfGroups(
			static_cast< U32 >(m_voxel_grid->GetResolution()), 
			GROUP_SIZE_3D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups, nb_groups, nb_groups);
	}
}
