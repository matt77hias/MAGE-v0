//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine_setup.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	EngineSetup::EngineSetup(HINSTANCE hinstance, const wstring &name)
		: m_hinstance(hinstance), m_name(name) {

		Assert(hinstance);
	}
}