//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\engine_setup.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	EngineSetup::EngineSetup(HINSTANCE hinstance, wstring name)
		: m_hinstance(hinstance), m_name(std::move(name)) {

		Assert(m_hinstance);
	}

	EngineSetup::EngineSetup(const EngineSetup &setup) = default;

	EngineSetup::EngineSetup(EngineSetup &&setup) = default;

	EngineSetup::~EngineSetup() = default;
}