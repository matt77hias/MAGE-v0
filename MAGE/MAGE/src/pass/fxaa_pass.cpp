//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "resource\resource_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "..\..\shaders\hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	FXAAPass *FXAAPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetFXAAPass();
	}

	FXAAPass::FXAAPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_cs(CreateFXAACS()) {}

	FXAAPass::FXAAPass(FXAAPass &&render_pass) = default;

	FXAAPass::~FXAAPass() = default;

	void FXAAPass::BindFixedState() const noexcept {
		// CS: Bind the compute shader.
		m_cs->BindShader(m_device_context);
	}

	void FXAAPass::Render(const Viewport &viewport) {

		// Dispatch.
		const U32 nb_groups_x
			= static_cast< U32 >(ceil(viewport.GetWidth()
				/ static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		const U32 nb_groups_y
			= static_cast< U32 >(ceil(viewport.GetHeight()
				/ static_cast< F32 >(GROUP_SIZE_DEFAULT)));
		m_device_context->Dispatch(nb_groups_x, nb_groups_y, 1u);
	}
}