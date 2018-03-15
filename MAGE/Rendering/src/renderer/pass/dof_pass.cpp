//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\dof_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	DOFPass::DOFPass(ID3D11DeviceContext& device_context,
					 StateManager& state_manager,
					 ResourceManager& resource_manager)
		: m_device_context(device_context), 
		m_state_manager(state_manager), 
		m_cs(CreateDepthOfFieldCS(resource_manager)) {}

	DOFPass::DOFPass(DOFPass&& pass) noexcept = default;

	DOFPass::~DOFPass() = default;

	DOFPass& DOFPass::operator=(DOFPass&& pass) noexcept = default;

	void DOFPass::Dispatch(const U32x2& viewport_size) const noexcept {
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport_size.m_x,
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport_size.m_y,
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}