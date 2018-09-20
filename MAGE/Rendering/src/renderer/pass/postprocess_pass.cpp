//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\postprocess_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	PostProcessPass::PostProcessPass(ID3D11DeviceContext& device_context,
									 StateManager& state_manager,
									 ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_resource_manager(resource_manager),
		m_dof_cs(CreateDepthOfFieldCS(resource_manager)) {}

	PostProcessPass::PostProcessPass(PostProcessPass&& pass) noexcept = default;

	PostProcessPass::~PostProcessPass() = default;

	PostProcessPass& PostProcessPass
		::operator=(PostProcessPass&& pass) noexcept = default;

	void PostProcessPass::DispatchDOF(const U32x2& viewport_size) const noexcept {
		// CS: Bind the compute shader.
		m_dof_cs->BindShader(m_device_context);

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport_size[0],
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport_size[1],
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}

	void PostProcessPass::DispatchLDR(const U32x2& viewport_size,
									  ToneMapping tone_mapping) const noexcept {

		// CS: Bind the compute shader.
		const auto cs = CreateLowDynamicRangeCS(m_resource_manager,
												tone_mapping);
		cs->BindShader(m_device_context);

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport_size[0],
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport_size[1],
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}