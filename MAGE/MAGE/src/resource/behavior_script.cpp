//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "memory\memory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BehaviorScript::BehaviorScript() 
		: m_active(true), m_terminated(false) {}

	BehaviorScript::BehaviorScript(const BehaviorScript &script) = default;

	BehaviorScript::BehaviorScript(BehaviorScript &&script) = default;

	BehaviorScript::~BehaviorScript() = default;

	void BehaviorScript::FixedUpdate() {}

	void BehaviorScript::Update(double delta_time) {
		UNUSED(delta_time);
	}

	void BehaviorScript::SetActive(bool active) noexcept {
		if (active && m_terminated) {
			return;
		}

		if (m_active == active) {
			return;
		}

		m_active = active;

		OnActiveChange();
	}

	void BehaviorScript::OnActiveChange() noexcept {}

	void BehaviorScript::Terminate() noexcept {
		if (m_terminated) {
			return;
		}

		m_terminated = true;
		m_active = false;

		OnActiveChange();
	}
}