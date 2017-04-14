//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "script\location_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void LocationScript::Update(double delta_time) {
		UNUSED(delta_time);
		const XMFLOAT3 translation = m_transform->GetTranslation();
		const XMFLOAT3 rotation    = m_transform->GetRotation();

		wchar_t buffer[128];
		_snwprintf_s(buffer, _countof(buffer), L"T: %.2f %.2f %.2f\nR: %.2f %.2f %.2f",
			translation.x, translation.y, translation.z,
			rotation.x, rotation.y, rotation.z);
		const wstring text = buffer;

		m_text->SetText(text);
	}
}