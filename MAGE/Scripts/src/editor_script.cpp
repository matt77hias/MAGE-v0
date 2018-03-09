//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "editor_script.hpp"
#include "editor\widget.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	EditorScript::EditorScript() = default;

	EditorScript::EditorScript(const EditorScript& script) = default;

	EditorScript::EditorScript(EditorScript&& script) noexcept = default;
	
	EditorScript::~EditorScript() = default;

	EditorScript& EditorScript
		::operator=(const EditorScript& script) noexcept = default;

	EditorScript& EditorScript
		::operator=(EditorScript&& script) noexcept = default;


	void EditorScript::Update([[maybe_unused]] F64 delta_time) {
		editor::DrawGraph(*SceneManager::Get()->GetScene());
		editor::DrawInspector();
	}

	void EditorScript::Close() {
		editor::SetSelected();
	}
}