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
	
	template < typename T >
	inline void VariableScript::AddVariable(const string &name, VariableType type, const T *value) {
		m_variables[name] = new Variable(type, name, value);
	}

	template < typename T >
	const T *VariableScript::GetValueOfVariable(const string &name) const {
		const map< string, Variable * >::const_iterator it = m_variables.find(name);
		if (it != m_variables.end()) {
			return (T *)(it->second->GetValue());
		}

		// Return nullptr if the variable was not found.
		return nullptr;
	}

	template < typename T >
	void VariableScript::SetValueOfVariable(const string &name, const T *value) {
		const map< string, Variable * >::iterator it = m_variables.find(name);
		if (it != m_variables.end()) {
			it->second->SetValue(value);
			return;
		}

		Warning("Variable %s not found.", name.c_str());
	}
}