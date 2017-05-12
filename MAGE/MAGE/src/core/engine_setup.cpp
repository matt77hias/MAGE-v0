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

	EngineSetup::EngineSetup(HINSTANCE hinstance, const wstring &name) noexcept
		: m_hinstance(hinstance), m_name(name) {

		Assert(m_hinstance);
	}

	EngineSetup::EngineSetup(const EngineSetup &setup) = default;

	EngineSetup::EngineSetup(EngineSetup &&setup) = default;

	EngineSetup::~EngineSetup() noexcept = default;
}