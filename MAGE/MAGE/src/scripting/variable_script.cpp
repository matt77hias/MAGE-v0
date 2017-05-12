//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_factory.hpp"
#include "scripting\variable_script_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableScript::VariableScript(const wstring &fname, bool import)
		: FileResource(fname) {

		if (import) {
			ImportScript();
		}
	}

	VariableScript::VariableScript(VariableScript &&variable_script) = default;

	VariableScript::~VariableScript() {
		RemoveAllVariables();
	}

	void VariableScript::ImportScript(const wstring &fname) {
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		
		vector< Variable > variable_buffer;
		ImportVariableScriptFromFile(filename, variable_buffer);
		for (auto it = variable_buffer.cbegin(); it != variable_buffer.cend(); ++it) {
			m_variables.insert(pair< const string, Variable >(it->GetName(), *it));
		}
	}

	void VariableScript::ExportScript(const wstring &fname) {
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		
		vector< Variable > variable_buffer;
		for (auto it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
			variable_buffer.push_back(it->second);
		}
		ExportVariableScriptToFile(filename, variable_buffer);
	}

	void VariableScript::RemoveVariable(const string &name) {
		const auto it = m_variables.find(name);
		if (it != m_variables.end()) {
			m_variables.erase(it);
		}
	}

	void VariableScript::RemoveAllVariables() {
		m_variables.clear();
	}

	SharedPtr< VariableScript > CreateVariableScript(const wstring &fname, bool import) {
		ResourceFactory *factory = GetResourceFactory();
		return factory->CreateVariableScript(fname, import);
	}
}