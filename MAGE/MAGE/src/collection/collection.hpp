#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <vector>
namespace mage {
	using std::vector;
}

#include <set>
namespace mage {
	using std::set;
}

#include <list>
namespace mage {
	using std::list;
}

#include <map>
namespace mage {
	using std::map;
}
#include <unordered_map>
namespace mage {
	using std::unordered_map;
}

#include <utility>
namespace mage {
	using std::pair;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Removes from the given container all the elements that compare equal to the given predicate. 
	 This reduces the container size by the number of elements removed.

	 @tparam		ContainerT
					The type of container.
	 @tparam		PredicateT
					The type of predicate.
	 @param[in]		container
					A reference to the container.
	 @param[in]		predicate
					A reference to the predicate.
	 */
	template< typename ContainerT, typename PredicateT >
	void RemoveIf(ContainerT &container, const PredicateT &predicate);

	/**
	 Removes and destructs all the elements from the given container.

	 @tparam		ContainerT
					The type of container.
	 @param[in]		container
					A reference to the container.
	 */
	template< typename ContainerT >
	void RemoveAndDestructAllElements(ContainerT &container);

	/**
	 Removes and destructs all the second elements from the given container.

	 @tparam		ContainerT
					The type of container.
	 @param[in]		container
					A reference to the container.
	 */
	template< typename ContainerT >
	void RemoveAndDestructAllSecondElements(ContainerT &container);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.tpp"

#pragma endregion