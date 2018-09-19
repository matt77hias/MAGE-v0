#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	template<>
	[[nodiscard]]
	inline bool VariableScript
		::Contains< void >(std::string_view name) const noexcept {

		return m_variables.cend() != m_variables.find(name);
	}

	template< typename T >
	[[nodiscard]]
	bool VariableScript::Contains(std::string_view name) const noexcept {
		if (const auto it = m_variables.find(name);
			it != m_variables.end()) {

			return nullptr != std::get_if< T >(&it->second);
		}

		return false;
	}

	template< typename T >
	inline void VariableScript::Add(std::string name, T value) {
		m_variables.insert_or_assign(std::move(name), std::move(value));
	}

	template< typename T >
	[[nodiscard]]
	const T* VariableScript::GetValue(std::string_view name) const {
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
	void VariableScript::SetValue(std::string_view name, T value) {
		if (const auto it = m_variables.find(name); 
			it != m_variables.end()) {

			it->second = std::move(value);
		}
		else {
			Warning("{}: Variable {} not found.", GetGuid(), name);
		}
	}
}