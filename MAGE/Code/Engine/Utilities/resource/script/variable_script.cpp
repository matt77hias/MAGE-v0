//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\script\variable_script.hpp"
#include "loaders\variable_script_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableScript::VariableScript(std::wstring fname, bool import)
		: Resource< VariableScript >(std::move(fname)),
		m_variables() {

		if (import) {
			ImportScript();
		}
	}

	VariableScript::VariableScript(VariableScript&& variable_script) noexcept
		: Resource< VariableScript >(std::move(variable_script)),
		m_variables(std::move(variable_script.m_variables)) {}

	VariableScript::~VariableScript() = default;

	VariableScript& VariableScript
		::operator=(VariableScript&& variable_script) noexcept {
		Resource< VariableScript >::operator=(std::move(variable_script));

		m_variables = std::move(variable_script.m_variables);
		return *this;
	}

	void VariableScript::ImportScript(const std::filesystem::path& path) {
		loader::ImportVariableScriptFromFile(path, m_variables);
	}

	void VariableScript::ExportScript(const std::filesystem::path& path) const {
		loader::ExportVariableScriptToFile(path, m_variables);
	}

	void VariableScript::Remove(std::string_view name) {
		if (const auto it = m_variables.find(name);
			it != m_variables.end()) {

			m_variables.erase(it);
		}
	}
}