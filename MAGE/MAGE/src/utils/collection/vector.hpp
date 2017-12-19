#pragma region

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\memory\allocation.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>

#pragma endregion

//-----------------------------------------------------------------------------
// Type Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	using AlignedVector = std::vector< T, AlignedAllocator< T > >;
}