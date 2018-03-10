//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\script\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	BehaviorScript::BehaviorScript() noexcept = default;

	BehaviorScript::BehaviorScript(
		const BehaviorScript& script) noexcept = default;

	BehaviorScript::BehaviorScript(BehaviorScript&& script) noexcept = default;

	BehaviorScript::~BehaviorScript() = default;

	BehaviorScript& BehaviorScript
		::operator=(const BehaviorScript& script) noexcept = default;

	BehaviorScript& BehaviorScript
		::operator=(BehaviorScript&& script) noexcept = default;

	void BehaviorScript::Load([[maybe_unused]] Engine& engine) {}

	void BehaviorScript::FixedUpdate([[maybe_unused]] Engine& engine) {}

	void BehaviorScript::Update([[maybe_unused]] Engine& engine, 
								[[maybe_unused]] F64 delta_time) {}

	void BehaviorScript::Close([[maybe_unused]] Engine& engine) {}
}