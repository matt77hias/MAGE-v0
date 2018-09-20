//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\voxel_grid_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	VoxelGridPass::VoxelGridPass(ID3D11DeviceContext& device_context,
								 StateManager& state_manager,
								 ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_vs(CreateVoxelGridVS(resource_manager)),
		m_gs(CreateVoxelGridGS(resource_manager)),
		m_ps(CreateVoxelGridPS(resource_manager)) {}

	VoxelGridPass::VoxelGridPass(VoxelGridPass&& pass) noexcept = default;

	VoxelGridPass::~VoxelGridPass() = default;

	VoxelGridPass& VoxelGridPass
		::operator=(VoxelGridPass&& pass) noexcept = default;

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
		m_state_manager.get().Bind(m_device_context,
								   RasterizerStateID::CounterClockwiseCulling);
		// PS: Bind the pixel shader.
		m_ps->BindShader(m_device_context);
		// OM: Bind the depth stencil state.
		#ifdef DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context,
								   DepthStencilStateID::LessEqualDepthReadWrite);
		#else  // DISABLE_INVERTED_Z_BUFFER
		m_state_manager.get().Bind(m_device_context,
								   DepthStencilStateID::GreaterEqualDepthReadWrite);
		#endif // DISABLE_INVERTED_Z_BUFFER
		// OM: Bind the blend state.
		m_state_manager.get().Bind(m_device_context,
								   BlendStateID::Opaque);
	}

	void VoxelGridPass::Render(std::size_t resolution) const noexcept {
		// Bind the fixed state.
		BindFixedState();

		const auto nb_voxels = static_cast< U32 >(resolution *
												  resolution *
												  resolution);

		// Draw the voxel grid.
		Pipeline::Draw(m_device_context, nb_voxels, 0u);
	}
}