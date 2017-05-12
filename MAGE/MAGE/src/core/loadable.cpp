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

	Loadable::Loadable(bool loaded) noexcept
		: m_loaded(loaded) {}

	Loadable::Loadable(const Loadable &loadable) noexcept = default;

	Loadable::Loadable(Loadable &&loadable) noexcept = default;

	Loadable &Loadable::operator=(const Loadable &loadable) noexcept = default;

	Loadable &Loadable::operator=(Loadable &&loadable) noexcept = default;

	Loadable::~Loadable() noexcept = default;
}