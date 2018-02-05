//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\rendering_manager.hpp"
#include "shader\shader_factory.hpp"
#include "logging\error.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	AAPass *AAPass::Get() {
		Assert(Renderer::Get());

		return Renderer::Get()->GetAAPass();
	}

	AAPass::AAPass()
		: m_device_context(Pipeline::GetImmediateDeviceContext()),
		m_preprocess_cs(), 
		m_cs(), 
		m_aa_desc(AADescriptor::None) {}

	AAPass::AAPass(AAPass &&pass) noexcept = default;

	AAPass::~AAPass() = default;

	void AAPass::UpdateCSs(AADescriptor desc) {
		if (m_aa_desc == desc) {
			return;
		}
		
		switch (desc) {
		
		case AADescriptor::FXAA: {
			m_preprocess_cs = CreateAAPreprocessCS();
			m_cs            = CreateFXAACS();
			break;
		}

		case AADescriptor::MSAA_2x:
		case AADescriptor::MSAA_4x:
		case AADescriptor::MSAA_8x: {
			m_preprocess_cs = nullptr;
			m_cs            = CreateMSAAResolveCS();
			break;
		}

		case AADescriptor::SSAA_2x:
		case AADescriptor::SSAA_3x:
		case AADescriptor::SSAA_4x: {
			m_preprocess_cs = nullptr;
			m_cs            = CreateSSAAResolveCS();
			break;
		}
		
		default: {
			m_preprocess_cs = nullptr;
			m_cs            = nullptr;
			break;
		}

		}
	}

	void AAPass::DispatchPreprocess(const Viewport &viewport, AADescriptor desc) {
		// Update the compute shaders.
		UpdateCSs(desc);
		if (!m_preprocess_cs) {
			return;
		}

		// CS: Bind the compute shader.
		m_preprocess_cs->BindShader(m_device_context);

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport.GetWidth(),
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport.GetHeight(),
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}

	void AAPass::Dispatch(const Viewport &viewport, AADescriptor desc) {
		// Update the compute shaders.
		UpdateCSs(desc);
		if (!m_cs) {
			return;
		}

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