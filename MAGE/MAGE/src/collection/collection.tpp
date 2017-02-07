#pragma once

//-----------------------------------------------------------------------------
// System Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ContainerT, typename PredicateT >
	void RemoveIf(ContainerT &container, const PredicateT &predicate) {
		auto it = container.begin();
		while (it != container.end()) {
			if (predicate(*it)) {
				it = container.erase(it);
			}
			else {
				++it;
			}
		}
	}

	template< typename ContainerT >
	void RemoveAndDestructAllElements(ContainerT &container) {
		auto it = container.begin();
		while (it != container.end()) {
			delete (*it);
			it = container.erase(it);
		}
	}
}