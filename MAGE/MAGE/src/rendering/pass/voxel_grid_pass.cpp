//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\voxel_grid_pass.hpp"
#include "rendering\rendering_state_manager.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VoxelGridPass::VoxelGridPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_vs(CreateVoxelGridVS()), 
		m_gs(CreateVoxelGridGS()),
		m_ps(CreateVoxelGridPS()) {}

	VoxelGridPass::VoxelGridPass(VoxelGridPass &&pass) noexcept = default;

	VoxelGridPass::~VoxelGridPass() = default;

	void VoxelGridPass::BindFixedState() const noexcept {
		// IA: Bind the primitive topology.
		Pipeline::IA::BindPrimitiveTopology(m_device_context, 
											D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		// VS: Bind the vertex shader.
		m_vs->BindShader(m_device_context);
		// HS: Bind the hull shader.
		Pipeline::HS::BindShader(m_device_context, nullptr);
		// DS: Bind the domain shader.
		Pipeline::DS::BindShader(m_device_context, nullptr);
		// GS: Bind the geometry shader.
		m_gs->BindShader(m_device_context);
		// RS: Bind the rasterization state.
		RenderingStateManager::Get()->BindCullNoneRasterizerState(m_device_context);
		//RenderingStateManager::Get()->BindCullCounterClockwiseRasterizerState(m_device_context);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindLessEqualDepthReadWriteDepthStencilState(m_device_context);
		#else  // DISABLE_INVERTED_Z_BUFFER
		RenderingStateManager::Get()->BindGreaterEqualDepthReadWriteDepthStencilState(m_device_context);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		RenderingStateManager::Get()->BindOpaqueBlendState(m_device_context);
	}

	void VoxelGridPass::Render(size_t resolution) const noexcept {
		// Bind the fixed state.
		BindFixedState();

		const auto nb_voxels 
			= static_cast< U32 >(resolution * resolution * resolution);

		// Draw the voxel grid.
		Pipeline::Draw(m_device_context, nb_voxels, 0u);
	}
}