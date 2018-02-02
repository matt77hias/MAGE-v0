//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VoxelizationPass *VoxelizationPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetVoxelizationPass();
	}

	VoxelizationPass::VoxelizationPass()
		: m_voxel_grid(),
		m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateVoxelizationVS()),
		m_gs(CreateVoxelizationGS()),
		m_ps{ 
			CreateVoxelizationPS(BRDFType::Unknown, false), 
			CreateVoxelizationPS(BRDFType::Unknown, true)
		},
		m_cs(CreateVoxelizationCS()),
		m_bound_ps(PSIndex::Count), 
		m_brdf(BRDFType::Unknown),
		m_model_buffer() {}

	VoxelizationPass::VoxelizationPass(
		VoxelizationPass &&pass) noexcept = default;

	VoxelizationPass::~VoxelizationPass() = default;

	void VoxelizationPass::UpdatePSs(BRDFType brdf) {
		if (m_brdf != brdf) {
			m_brdf = brdf;
			m_ps[static_cast< size_t >(PSIndex::BRDF)] 
				= CreateVoxelizationPS(brdf, false);
			m_ps[static_cast< size_t >(PSIndex::BRDF_TSNM)] 
				= CreateVoxelizationPS(brdf, true);
		}
	}

	void VoxelizationPass::BindPS(PSIndex index) noexcept {
		if (m_bound_ps != index) {
			m_ps[static_cast< size_t >(index)]->BindShader(m_device_context);
			m_bound_ps = index;
		}
	}

	void VoxelizationPass::BindPS(const Material &material) noexcept {
		if (material.GetNormalSRV()) {
			BindPS(PSIndex::BRDF_TSNM);
		}
		else {
			BindPS(PSIndex::BRDF);
		}
	}

	void XM_CALLCONV VoxelizationPass::BindModelData(FXMMATRIX object_to_view, 
													 CXMMATRIX view_to_object,
													 CXMMATRIX texture_transform,
													 const Material &material) {
		ModelBuffer buffer;
		// Transforms
		buffer.m_transform.m_object_to_view    = XMMatrixTranspose(object_to_view);
		buffer.m_transform.m_normal_to_view    = view_to_object;
		buffer.m_transform.m_texture_transform = XMMatrixTranspose(texture_transform);
		// Material
		buffer.m_base_color = RGBA(material.GetBaseColor());
		buffer.m_roughness  = material.GetRoughness();
		buffer.m_metalness  = material.GetMetalness();
		
		// Update the model buffer.
		m_model_buffer.UpdateData(m_device_context, buffer);
		// Bind the model buffer.
		m_model_buffer.Bind< Pipeline::VS >(m_device_context, SLOT_CBUFFER_MODEL);
		m_model_buffer.Bind< Pipeline::PS >(m_device_context, SLOT_CBUFFER_MODEL);

		// Bind the base color SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_BASE_COLOR, material.GetBaseColorSRV());
		// Bind the material SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_MATERIAL, material.GetMaterialSRV());
		// Bind the normal SRV.
		Pipeline::PS::BindSRV(m_device_context,
			SLOT_SRV_NORMAL, material.GetNormalSRV());
	}

	void VoxelizationPass::BindFixedState(BRDFType brdf) {
		// Reset the bound pixel shader index.
		m_bound_ps = PSIndex::Count;
		// Update the pixel shaders.
		UpdatePSs(brdf);

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
											  CXMMATRIX world_to_view,
											  CXMMATRIX view_to_world) {
		// Process the models.
		scene.ForEach< Model >([this, world_to_projection, world_to_view, view_to_world](const Model &model) {
			const Material &material            = model.GetMaterial();
			
			if (State::Active != model.GetState()
				|| !material.InteractsWithLight()
				|| material.GetBaseColor().m_w < TRANSPARENCY_THRESHOLD) {
				return;
			}
			
			const Transform &transform          = model.GetOwner()->GetTransform();
			const XMMATRIX object_to_world      = transform.GetObjectToWorldMatrix();
			const XMMATRIX object_to_projection = object_to_world * world_to_projection;

			// Apply view frustum culling.
			if (BoundingFrustum::Cull(object_to_projection, model.GetAABB())) {
				return;
			}

			const XMMATRIX object_to_view       = object_to_world * world_to_view;
			const XMMATRIX world_to_object      = transform.GetWorldToObjectMatrix();
			const XMMATRIX view_to_object       = view_to_world * world_to_object;
			const XMMATRIX texture_transform    = model.GetTextureTransform().GetTransformMatrix();

			// Bind the model data.
			BindModelData(object_to_view, view_to_object, texture_transform, material);
			// Bind the pixel shader.
			BindPS(model.GetMaterial());
			// Bind the model mesh.
			model.BindMesh(m_device_context);
			// Draw the model.
			model.Draw(m_device_context);
		});
	}
	
	void VoxelizationPass::Dispatch() {
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);

		// Dispatch.
		const auto nb_groups = static_cast< U32 >(ceil(0.25f * m_voxel_grid.GetResolution()));
		Pipeline::Dispatch(m_device_context, nb_groups, nb_groups, nb_groups);
	}
}