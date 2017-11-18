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
		vector< Variable > variable_buffer;
		ImportVariableScriptFromFile(fname, variable_buffer);
		for (const auto &variable : variable_buffer) {
			m_variables.emplace(variable.GetName(), variable);
		}
	}

	void VariableScript::ExportScript(const wstring &fname) const {
		vector< Variable > variable_buffer;
		for (const auto &variable : m_variables) {
			variable_buffer.push_back(variable.second);
		}

		ExportVariableScriptToFile(fname, variable_buffer);
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