//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "renderer\pass\aa_pass.hpp"
#include "resource\shader\shader_factory.hpp"

// Include HLSL bindings.
#include "hlsl.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	AAPass::AAPass(ID3D11DeviceContext& device_context,
				   StateManager& state_manager,
				   ResourceManager& resource_manager)
		: m_device_context(device_context),
		m_state_manager(state_manager),
		m_resource_manager(resource_manager) {}

	AAPass::AAPass(AAPass&& pass) noexcept = default;

	AAPass::~AAPass() = default;

	AAPass& AAPass::operator=(AAPass&& pass) noexcept = default;

	void AAPass::DispatchPreprocess(const U32x2& viewport_size,
									AntiAliasing aa) {

		// CS: Bind the compute shader.
		switch (aa) {

		case AntiAliasing::FXAA: {
			const auto cs = CreateAAPreprocessCS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		default: {
			return;
		}
		}

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport_size[0],
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport_size[1],
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}

	void AAPass::Dispatch(const U32x2& viewport_size,
						  AntiAliasing aa) {

		// CS: Bind the compute shader.
		switch (aa) {

		case AntiAliasing::FXAA: {
			const auto cs = CreateFXAACS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		case AntiAliasing::MSAA_2x:
		case AntiAliasing::MSAA_4x:
		case AntiAliasing::MSAA_8x: {
			const auto cs = CreateMSAAResolveCS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		case AntiAliasing::SSAA_2x:
		case AntiAliasing::SSAA_3x:
		case AntiAliasing::SSAA_4x: {
			const auto cs = CreateSSAAResolveCS(m_resource_manager);
			cs->BindShader(m_device_context);
			break;
		}

		default: {
			return;
		}
		}

		// Dispatch the pass.
		const auto nb_groups_x = GetNumberOfGroups(viewport_size[0],
												   GROUP_SIZE_2D_DEFAULT);
		const auto nb_groups_y = GetNumberOfGroups(viewport_size[1],
												   GROUP_SIZE_2D_DEFAULT);
		Pipeline::Dispatch(m_device_context, nb_groups_x, nb_groups_y, 1u);
	}
}