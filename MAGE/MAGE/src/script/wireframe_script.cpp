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
		: BehaviorScript(), m_solid(true) {}

	WireframeScript::WireframeScript(WireframeScript &&script) = default;
	
	WireframeScript::~WireframeScript() = default;

	void WireframeScript::Update(double delta_time) {
		UNUSED(delta_time);
		
		const Keyboard * const keyboard = g_engine->GetInputManager()->GetKeyboard();
		if (keyboard->GetKeyPress(DIK_SPACE)) {
			m_solid = !m_solid;
			
			const Renderer *renderer = g_engine->GetRenderer();
			if (m_solid) {
				renderer->GetRenderingState3D()->SetCullCounterClockwiseRasterizerState();
				renderer->GetRenderingState2D()->SetCullCounterClockwiseRasterizerState();
			}
			else {
				renderer->GetRenderingState3D()->SetWireframeRasterizerState();
				renderer->GetRenderingState2D()->SetWireframeRasterizerState();
			}
		}
	}
}