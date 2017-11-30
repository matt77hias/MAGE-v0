#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template< typename T >
	bool VariableScript::HasVariableOfType(const string &name) const noexcept {
		if (const auto it = m_variables.find(name);
			it != m_variables.end()) {

			return nullptr != std::get_if< T >(&it->second);
		}

		return false;
	}

	template< typename T >
	inline void VariableScript::AddVariable(string name, T value) {
		m_variables.insert_or_assign(std::move(name), Value(std::move(value)));
	}

	template< typename T >
	const T *VariableScript::GetValueOfVariable(const string &name) const {
		if (const auto it = m_variables.find(name);
			it != m_variables.end()) {

			return &std::get< T >(it->second);
		}

		// Return nullptr if the variable was not found.
		return nullptr;
	}

	template< typename T >
	void VariableScript::SetValueOfVariable(const string &name, T value) {
		if (const auto it = m_variables.find(name); 
			it != m_variables.end()) {

			it->second = std::move(value);
		}
		else {
			Warning("Variable %s not found.", name.c_str());
		}
	}
}