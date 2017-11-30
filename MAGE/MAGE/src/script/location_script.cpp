//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\location_script.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	LocationScript::LocationScript(TransformNode *transform, SpriteText *text)
		: BehaviorScript(), m_transform(transform), m_text(text) {

		Assert(m_transform);
		Assert(m_text);
	}
	
	LocationScript::LocationScript(LocationScript &&script) = default;
	
	LocationScript::~LocationScript() = default;

	void LocationScript::Update([[maybe_unused]] F64 delta_time) {
		const F32x3 translation = m_transform->GetTranslation();
		const F32x3 rotation    = m_transform->GetRotation();

		wchar_t buffer[128];
		_snwprintf_s(buffer, _countof(buffer), 
			L"T: %.2f %.2f %.2f\nR: %.2f %.2f %.2f",
			translation.m_x, translation.m_y, translation.m_z,
			rotation.m_x, rotation.m_y, rotation.m_z);
		
		m_text->SetText(buffer);
	}
}