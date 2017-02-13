//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\variable_script_loader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	VariableScript::VariableScript(const wstring &fname)
		: Resource(fname) {
		ImportScript();
	}

	VariableScript::~VariableScript() {
		RemoveAllVariables();
	}

	HRESULT VariableScript::ImportScript(const wstring &fname) {
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		return ImportVariableScriptFromFile(filename, *this);
	}

	HRESULT VariableScript::ExportScript(const wstring &fname) {
		const wstring &filename = (fname != L"") ? fname : GetFilename();
		return ExportVariableScriptToFile(filename, *this);
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
}