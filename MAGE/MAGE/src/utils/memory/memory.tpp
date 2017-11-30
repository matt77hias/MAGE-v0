#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SharedPointer
	//-------------------------------------------------------------------------

	template< typename T, typename... ConstructorArgsT >
	inline SharedPtr< T > MakeShared(ConstructorArgsT&&... args) {
		return std::make_shared< T >(std::forward< ConstructorArgsT >(args)...);
	}

	template< typename T, typename... ConstructorArgsT >
	inline SharedPtr< T > MakeAllocatedShared(ConstructorArgsT&&... args) {
		return SharedPtr< T >(new T(std::forward< ConstructorArgsT >(args)...));
	}

	//-------------------------------------------------------------------------
	// UniquePointer
	//-------------------------------------------------------------------------

	template< typename T, typename... ConstructorArgsT >
	inline UniquePtr< T > MakeUnique(ConstructorArgsT&&... args) {
		return std::make_unique< T >(std::forward< ConstructorArgsT >(args)...);
	}

	template< typename T, typename U >
	inline UniquePtr< T > static_pointer_cast(UniquePtr< U > &&ptr) noexcept {
		return UniquePtr< T >(static_cast< T * >(ptr.release()));
	}

	template< typename T, typename U >
	inline UniquePtr< T > dynamic_pointer_cast(UniquePtr< U > &&ptr) noexcept {
		U * const stored_ptr = ptr.release();
		T * const converted_stored_ptr = dynamic_cast< T * >(stored_ptr);
		if (converted_stored_ptr) {
			return UniquePtr< T >(converted_stored_ptr);
		}
		else {
			ptr.reset(stored_ptr);
			return UniquePtr< T >(nullptr);
		}
	}

	template< typename T, typename U >
	inline UniquePtr< T > const_pointer_cast(UniquePtr< U > &&ptr) noexcept {
		return UniquePtr< T >(const_cast< T * >(ptr.release()));
	}

	template< typename T, typename U >
	inline UniquePtr< T > reinterpret_pointer_cast(UniquePtr< U > &&ptr) noexcept {
		return UniquePtr< T >(reinterpret_cast< T * >(ptr.release()));
	}
}