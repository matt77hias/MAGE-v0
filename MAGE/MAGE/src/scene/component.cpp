//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"
#include "parallel\id_generator.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Component::Component() noexcept
		: m_state(State::Active),
		m_guid(IdGenerator::GetNextGuid()),
		m_owner() {}

	Component::Component(const Component &component) noexcept
		: m_state(component.m_state),
		m_guid(IdGenerator::GetNextGuid()),
		m_owner() {}

	Component::Component(Component &&component) noexcept = default;

	Component::~Component() = default;

	Component &Component::operator=(const Component &component) noexcept {
		m_state = component.m_state;
		return *this;
	}

	Component &Component::operator=(Component &&component) noexcept = default;

	void Component::SetState(State state) noexcept {
		if (State::Terminated == state) {
			return;
		}
		
		if (HasOwner() && State::Terminated == m_owner->GetState()) {
			m_state = State::Terminated;
		}
		else {
			m_state = state;
		}
	}
}