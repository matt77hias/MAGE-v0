//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BehaviorScript::BehaviorScript() noexcept = default;

	BehaviorScript::BehaviorScript(
		const BehaviorScript &script) noexcept = default;

	BehaviorScript::BehaviorScript(BehaviorScript &&script) noexcept = default;

	BehaviorScript::~BehaviorScript() = default;

	BehaviorScript &BehaviorScript
		::operator=(BehaviorScript &&script) noexcept = default;

	void BehaviorScript::Load() {}

	void BehaviorScript::FixedUpdate() {}

	void BehaviorScript::Update([[maybe_unused]] F64 delta_time) {}

	void BehaviorScript::Close() {}
}