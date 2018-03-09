#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\state.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ElementT, typename... ConstructorArgsT >
	inline ProxyPtr< ElementT > AddElement(AlignedVector< ElementT >& elements, 
										   ConstructorArgsT&&... args) {
		size_t index = 0;
		for (auto& element : elements) {
			if (State::Terminated == element.GetState()) {
				element = ElementT(std::forward< ConstructorArgsT >(args)...);
				return ProxyPtr< ElementT >(elements, index);
			}

			++index;
		}

		elements.emplace_back(std::forward< ConstructorArgsT >(args)...);
		return ProxyPtr< ElementT >(elements, index);
	}

	template< typename ElementT, typename BaseT, typename... ConstructorArgsT >
	inline ProxyPtr< ElementT > AddElementPtr(AlignedVector< UniquePtr< BaseT > >& elements, 
											  ConstructorArgsT&&... args) {
		size_t index = 0;
		for (auto& element : elements) {
			if (State::Terminated == element->GetState()) {
				element = MakeUnique< ElementT >(
					std::forward< ConstructorArgsT >(args)...);
				return ProxyPtr< ElementT >([&elements, index]() noexcept {
						return static_cast< ElementT* >(elements[index].get());
				});
			}

			++index;
		}

		elements.push_back(MakeUnique< ElementT >(
			std::forward< ConstructorArgsT >(args)...));
		return ProxyPtr< ElementT >([&elements, index]() noexcept {
				return static_cast< ElementT * >(elements[index].get());
		});
	}
}