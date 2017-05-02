//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "core\loadable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Loadable::Loadable(bool loaded)
		: m_loaded(loaded) {}

	Loadable::Loadable(const Loadable &loadable) = default;

	Loadable::Loadable(Loadable &&loadable) = default;

	Loadable &Loadable::operator=(const Loadable &loadable) = default;

	Loadable &Loadable::operator=(Loadable &&loadable) = default;

	Loadable::~Loadable() = default;
}