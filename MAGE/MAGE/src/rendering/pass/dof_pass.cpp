//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "utils\logging\error.hpp"

// Include HLSL bindings.
#include "..\..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	DOFPass *DOFPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetDOFPass();
	}

	DOFPass::DOFPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_cs(CreateDepthOfFieldCS()) {}

	DOFPass::DOFPass(DOFPass &&render_pass) = default;

	DOFPass::~DOFPass() = default;

	void DOFPass::Dispatch(const Viewport &viewport) const noexcept {
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);

		// Dispatch.
		const U32 nb_groups_x = static_cast< U32 >(ceil(viewport.GetWidth()
				              / static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		const U32 nb_groups_y = static_cast< U32 >(ceil(viewport.GetHeight()
				              / static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}