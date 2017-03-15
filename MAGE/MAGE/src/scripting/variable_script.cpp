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
			const HRESULT result_import = ImportScript();
			if (FAILED(result_import)) {
				Error("Variable script import failed: %08X.", result_import);
				return;
			}
		}
	}

	VariableScript::~VariableScript() {
		RemoveAllVariables();
	}

	HRESULT VariableScript::ImportScript(const wstring &fname) {
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		vector< Variable * > variable_buffer;
		
		const HRESULT result_import = ImportVariableScriptFromFile(filename, variable_buffer);

		for (vector< Variable * >::const_iterator it = variable_buffer.cbegin(); it != variable_buffer.cend(); ++it) {
			m_variables[(*it)->GetName()] = *it;
		}

		return result_import;
	}

	HRESULT VariableScript::ExportScript(const wstring &fname) {
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		vector< Variable * > variable_buffer;

		for (map< string, Variable * >::const_iterator it = m_variables.cbegin(); it != m_variables.cend(); ++it) {
			variable_buffer.push_back(it->second);
		}

		return ExportVariableScriptToFile(filename, variable_buffer);
	}

	void VariableScript::RemoveVariable(const string &name) {
		const map< string, Variable * >::iterator it = m_variables.find(name);
		if (it != m_variables.end()) {
			delete it->second;
			m_variables.erase(it);
		}
	}

	void VariableScript::RemoveAllVariables() {
		RemoveAndDestructAllSecondElements(m_variables);
	}

	SharedPtr< VariableScript > CreateVariableScript(const wstring &fname, bool import) {
		ResourceFactory &factory = GetResourceFactory();
		return factory.CreateVariableScript(fname, import);
	}
}