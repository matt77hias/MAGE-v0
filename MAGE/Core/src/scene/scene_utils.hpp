#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\vector.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ElementT, typename... ConstructorArgsT >
	ProxyPtr< ElementT > AddElement(AlignedVector< ElementT >& elements,
									ConstructorArgsT&&... args);

	template< typename ElementT, typename BaseT, typename... ConstructorArgsT >
	ProxyPtr< ElementT > AddElementPtr(AlignedVector< UniquePtr< BaseT > >& elements,
									   ConstructorArgsT&&... args);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_utils.tpp"

#pragma endregion