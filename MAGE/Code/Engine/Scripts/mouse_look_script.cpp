//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mouse_look_script.hpp"
#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	MouseLookScript::MouseLookScript()
		: BehaviorScript(),
		m_locked(false),
		m_axes(RotationAxes::MouseXAndY),
		m_sensitivity(F32x2(1.8f, 1.8f)),
		m_minimum_rotation(F32x2(-XM_PI / 3.0f, -XM_PI)),
		m_maximum_rotation(F32x2( XM_PI / 3.0f,  XM_PI)),
		m_direction(F32x2(1.0f, 1.0f)) {}

	MouseLookScript::MouseLookScript(
		const MouseLookScript& script) noexcept = default;

	MouseLookScript::MouseLookScript(
		MouseLookScript&& script) noexcept = default;

	MouseLookScript::~MouseLookScript() = default;

	MouseLookScript& MouseLookScript::operator=(
		const MouseLookScript& script) noexcept = default;

	MouseLookScript& MouseLookScript::operator=(
		MouseLookScript&& script) noexcept = default;

	void MouseLookScript::Load([[maybe_unused]] Engine& engine) {
		ThrowIfFailed(HasOwner(),
					  "This script needs to be attached to a node.");
	}

	void MouseLookScript::Update([[maybe_unused]] Engine& engine) {
		const auto delta_time
			= static_cast< F32 >(engine.GetTime().GetWallClockDeltaTime().count());
		const auto& input_manager = engine.GetInputManager();
		const auto& keyboard      = input_manager.GetKeyboard();

		if (keyboard.IsActivated(DIK_F2)) {
			m_locked = !m_locked;
		}
		if (m_locked) {
			return;
		}

		const auto& mouse         = input_manager.GetMouse();
		auto& transform           = GetOwner()->GetTransform();

		const auto rotation = XMLoad(m_sensitivity) * XMLoad(m_direction) * delta_time
			                * XMVectorSwizzle< 1u, 0u, 1u, 0u >(XMLoad(mouse.GetDelta()));
		switch (m_axes) {

		case RotationAxes::MouseXAndY: {
			transform.AddRotationX(XMVectorGetX(rotation),
								   m_minimum_rotation[0u],
								   m_maximum_rotation[0u]);
			transform.AddRotationY(XMVectorGetY(rotation),
								   m_minimum_rotation[1u],
								   m_maximum_rotation[1u]);
			break;
		}

		case RotationAxes::MouseX: {
			transform.AddRotationY(XMVectorGetY(rotation),
								   m_minimum_rotation[1u],
								   m_maximum_rotation[1u]);
			break;
		}

		case RotationAxes::MouseY: {
			transform.AddRotationX(XMVectorGetX(rotation),
								   m_minimum_rotation[0u],
								   m_maximum_rotation[0u]);
			break;
		}
		}
	}
}