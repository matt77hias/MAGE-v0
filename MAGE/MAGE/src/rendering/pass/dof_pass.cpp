//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\dof_pass.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DOFPass::DOFPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_cs(CreateDepthOfFieldCS()) {}

	DOFPass::DOFPass(DOFPass &&pass) noexcept = default;

	DOFPass::~DOFPass() = default;

	void DOFPass::Dispatch(const Viewport &viewport) const noexcept {
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport.GetWidth(),  
			                                       GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport.GetHeight(), 
			                                       GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}