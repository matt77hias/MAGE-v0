#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template<>
	[[nodiscard]]
	inline bool VariableScript
		::Contains< void >(const string& name) const noexcept {

		return m_variables.cend() != m_variables.find(name);
	}

	template< typename T >
	[[nodiscard]]
	bool VariableScript::Contains(const string& name) const noexcept {
		if (const auto it = m_variables.find(name);
			it != m_variables.end()) {

			return nullptr != std::get_if< T >(&it->second);
		}

		return false;
	}

	template< typename T >
	inline void VariableScript::Add(string name, T value) {
		m_variables.insert_or_assign(std::move(name), Value(std::move(value)));
	}

	template< typename T >
	[[nodiscard]]
	const T* VariableScript::GetValue(const string& name) const {
		if (const auto it = m_variables.find(name);
			it != m_variables.end()) {

			// Throws std::bad_variant_access if the variable corresponding to 
			// the given name has a different type.
			return &std::get< T >(it->second);
		}

		// Return nullptr if this variable script does not contain a 
		// variable corresponding to the given name.
		return nullptr;
	}

	template< typename T >
	void VariableScript::SetValue(const string& name, T value) {
		if (const auto it = m_variables.find(name); 
			it != m_variables.end()) {

			it->second = std::move(value);
		}
		else {
			Warning("%ls: Variable %s not found.", GetGuid(), name.c_str());
		}
	}
}