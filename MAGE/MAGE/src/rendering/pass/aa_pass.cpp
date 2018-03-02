//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "rendering\pass\aa_pass.hpp"
#include "shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	AAPass::AAPass(ID3D11DeviceContext& device_context,
				   StateManager& state_manager,
				   ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_resource_manager(resource_manager) {}

	AAPass::AAPass(AAPass&& pass) noexcept = default;

	AAPass::~AAPass() = default;

	void AAPass::DispatchPreprocess(const Viewport& viewport, AADescriptor desc) {
		// CS: Bind the compute shader.
		switch (desc) {

		case AADescriptor::FXAA: {
			const auto cs = CreateAAPreprocessCS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		default: {
			return;
		}
		}

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport.GetWidth(),
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport.GetHeight(),
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}

	void AAPass::Dispatch(const Viewport& viewport, AADescriptor desc) {
		// CS: Bind the compute shader.
		switch (desc) {

		case AADescriptor::FXAA: {
			const auto cs = CreateFXAACS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		case AADescriptor::MSAA_2x:
		case AADescriptor::MSAA_4x:
		case AADescriptor::MSAA_8x: {
			const auto cs = CreateMSAAResolveCS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		case AADescriptor::SSAA_2x:
		case AADescriptor::SSAA_3x:
		case AADescriptor::SSAA_4x: {
			const auto cs = CreateSSAAResolveCS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		default: {
			return;
		}
		}

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport.GetWidth(),
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport.GetHeight(),
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}