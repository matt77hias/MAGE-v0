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

	VariableScript &VariableScript::operator=(
		VariableScript &&variable_script) noexcept = default;

	void VariableScript::ImportScript(const wstring &fname) {
		loader::ImportVariableScriptFromFile(fname, m_variables);
	}

	void VariableScript::ExportScript(const wstring &fname) const {
		loader::ExportVariableScriptToFile(fname, m_variables);
	}

	void VariableScript::Remove(const string &name) {
		if (const auto it = m_variables.find(name); 
			it != m_variables.end()) {

			m_variables.erase(it);
		}
	}
}