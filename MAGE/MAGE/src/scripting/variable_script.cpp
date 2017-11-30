//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script.hpp"
#include "loaders\variable_script_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableScript::VariableScript(wstring fname, bool import)
		: Resource< VariableScript >(std::move(fname)),
		m_variables() {

		if (import) {
			ImportScript();
		}
	}

	VariableScript::VariableScript(VariableScript &&variable_script) = default;

	VariableScript::~VariableScript() = default;

	void VariableScript::ImportScript(const wstring &fname) {
		ImportVariableScriptFromFile(fname, m_variables);
	}

	void VariableScript::ExportScript(const wstring &fname) const {
		ExportVariableScriptToFile(fname, m_variables);
	}

	bool VariableScript::HasVariable(const string &name) const noexcept {
		return m_variables.cend() != m_variables.find(name);
	}

	void VariableScript::RemoveVariable(const string &name) {
		if (const auto it = m_variables.find(name); 
			it != m_variables.end()) {

			m_variables.erase(it);
		}
	}

	void VariableScript::RemoveAllVariables() noexcept {
		m_variables.clear();
	}
}