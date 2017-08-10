//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\wireframe_script.hpp"
#include "core\engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	WireframeScript::WireframeScript()
		: BehaviorScript(), m_mode(WireframeMode::Mode_3Dand2D), m_solid(true) {}

	WireframeScript::WireframeScript(WireframeScript &&script) = default;
	
	WireframeScript::~WireframeScript() = default;

	void WireframeScript::Update(double delta_time) {
		UNUSED(delta_time);
		
		const Keyboard * const keyboard = Keyboard::Get();
		if (keyboard->GetKeyPress(DIK_SPACE)) {
			m_solid = !m_solid;
			
			const Renderer *renderer = g_engine->GetRenderer();
			if (m_solid) {
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_3D)) {
					renderer->GetRenderingState3D()->SetCullCounterClockwiseRasterizerState();
				}
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_2D)) {
					renderer->GetRenderingState2D()->SetCullCounterClockwiseRasterizerState();
				}
			}
			else {
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_3D)) {
					renderer->GetRenderingState3D()->SetWireframeRasterizerState();
				}
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_2D)) {
					renderer->GetRenderingState2D()->SetWireframeRasterizerState();
				}
			}
		}
	}
}