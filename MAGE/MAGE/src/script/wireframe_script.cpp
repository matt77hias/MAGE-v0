//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\wireframe_script.hpp"
#include "input\keyboard.hpp"
#include "rendering\renderer.hpp"

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
		
		//TODO

		const Keyboard * const keyboard = Keyboard::Get();
		if (keyboard->GetKeyPress(DIK_SPACE)) {
			m_solid = !m_solid;
			
			if (m_solid) {
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_3D)) {
					//SetCullCounterClockwiseRasterizerState();
				}
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_2D)) {
					//SetCullCounterClockwiseRasterizerState();
				}
			}
			else {
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_3D)) {
					//SetWireframeRasterizerState();
				}
				if (static_cast< unsigned int >(m_mode) & static_cast< unsigned int >(WireframeMode::Mode_2D)) {
					//SetWireframeRasterizerState();
				}
			}
		}
	}
}