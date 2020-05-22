#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <algorithm>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Erases all the elements of the given container that satisfy the given
	 predicate.

	 @tparam		ContainerT
					The container type.
	 @tparam		PredicateT
					The predicate type.
	 @param[in,out]	container
					A reference to the container.
	 @param[in]		predicate
					A reference to the predicate.
	 @return		The iterator following the last removed element.
	 */
	template< typename ContainerT, typename PredicateT >
	inline decltype(auto) EraseIf(ContainerT& container,
								  PredicateT&& predicate) {

		// Erase-Remove Idiom
		return container.erase(std::remove_if(container.begin(), container.end(),
											  std::forward< PredicateT >(predicate)),
							   container.end());
	}
}