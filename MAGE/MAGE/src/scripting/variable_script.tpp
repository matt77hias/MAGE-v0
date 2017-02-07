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
	void VariableScript::AddVariable(const string &name, VariableType type, const T *value) {
		m_variables.push_back(new Variable(name, type, value));
	}

	template < typename T >
	const T *VariableScript::GetValueOfVariable(const string &name) const {
		// Iterate the states looking for the specified variable.
		for (list< Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
			if ((*it)->GetName() == name) {
				return (T *)((*it)->GetValue());
			}
		}

		return nullptr;
	}

	template < typename T >
	void VariableScript::SetValueOfVariable(const string &name, const T *value) {
		// Iterate the variables looking for the specified variable.
		for (list< Variable * >::iterator it = m_variables.begin(); it != m_variables.end(); ++it) {
			if ((*it)->GetName() == name) {
				(*it)->SetValue(value);
				return;
			}
		}
		
		Warning("Variable %s not found.", name.c_str());
	}
}