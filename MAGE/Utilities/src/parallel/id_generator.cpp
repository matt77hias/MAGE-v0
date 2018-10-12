//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "parallel\id_generator.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	U64 GetNextGuid() noexcept {
		static IdGenerator< U64 > s_guid_generator;
		return s_guid_generator.GetNextId();
	}
}