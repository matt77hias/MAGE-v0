//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\voxelization_pass.hpp"
#include "rendering\rendering_state_manager.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_VOXEL_GRID_RESOLUTION 1

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VoxelizationPass::VoxelizationPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateVoxelizationVS()),
		m_gs(CreateVoxelizationGS()),
		m_cs(CreateVoxelizationCS()),
		m_voxel_grid(MakeUnique< VoxelGrid >(
			MAGE_DEFAULT_VOXEL_GRID_RESOLUTION)) {}

	VoxelizationPass::VoxelizationPass(
		VoxelizationPass &&pass) noexcept = default;

	VoxelizationPass::~VoxelizationPass() = default;

	void VoxelizationPass::SetupVoxelGrid(size_t resolution) {
		if (m_voxel_grid->GetResolution() != resolution) {
			m_voxel_grid = MakeUnique< VoxelGrid >(resolution);
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
		RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// OM: Bind the depth-stencil state.
		RenderingStateManager::Get()->BindDepthNoneDepthStencilState(m_device_context);
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void XM_CALLCONV VoxelizationPass::Render(const Scene &scene,
											  FXMMATRIX world_to_projection,
											  BRDFType brdf,
											  size_t resolution) {
		SetupVoxelGrid(resolution);

		m_voxel_grid->BindBeginVoxelizationBuffer(m_device_context);
		m_voxel_grid->BindViewport(m_device_context);
		Render(scene, world_to_projection, brdf);
		m_voxel_grid->BindEndVoxelizationBuffer(m_device_context);

		m_voxel_grid->BindBeginVoxelizationTexture(m_device_context);
		Dispatch();
		m_voxel_grid->BindEndVoxelizationTexture(m_device_context);
	}

	void XM_CALLCONV VoxelizationPass::Render(const Scene &scene,
											  FXMMATRIX world_to_projection, 
											  BRDFType brdf) const {
		// Bind the fixed opaque state.
		BindFixedState();

		constexpr bool transparency = false;
		
		//---------------------------------------------------------------------
		// All models with no TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = false;
			const PixelShaderPtr ps = CreateVoxelizationPS(brdf, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		scene.ForEach< Model >([this, world_to_projection](const Model &model) {

			const auto &material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !material.InteractsWithLight()
				|| nullptr != material.GetNormalSRV()
				|| material.GetBaseColor().m_w < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});

		//---------------------------------------------------------------------
		// All models with TSNM.
		//---------------------------------------------------------------------
		{
			constexpr bool tsnm = true;
			const PixelShaderPtr ps = CreateVoxelizationPS(brdf, tsnm);
			// PS: Bind the pixel shader.
			ps->BindShader(m_device_context);
		}

		// Process the models.
		scene.ForEach< Model >([this, world_to_projection](const Model &model) {

			const auto &material = model.GetMaterial();

			if (State::Active != model.GetState()
				|| !material.InteractsWithLight()
				|| nullptr == material.GetNormalSRV()
				|| material.GetBaseColor().m_w < TRANSPARENCY_THRESHOLD) {
				return;
			}

			Render(model, world_to_projection);
		});
	}

	void XM_CALLCONV VoxelizationPass::Render(const Model &model, 
											  FXMMATRIX world_to_projection) const noexcept {

		const auto &transform           = model.GetOwner()->GetTransform();
		const auto object_to_world      = transform.GetObjectToWorldMatrix();
		const auto object_to_projection = object_to_world * world_to_projection;

		// Apply view frustum culling.
		if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) { 
			return;
		}

		const auto &material            = model.GetMaterial();

		// Bind the constant buffer of the model.
		model.BindBuffer< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
		model.BindBuffer< Pipeline::PS >(m_device_context, SLOT_CBUFFER_MODEL);
		// Bind the SRVs of the model.
		static_assert(SLOT_SRV_MATERIAL == SLOT_SRV_BASE_COLOR + 1);
		static_assert(SLOT_SRV_NORMAL   == SLOT_SRV_BASE_COLOR + 2);
		ID3D11ShaderResourceView * const srvs[] = {
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
			static_cast< U32 >(m_voxel_grid->GetResolution()), GROUP_SIZE_3D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups, nb_groups, nb_groups);
	}
}
