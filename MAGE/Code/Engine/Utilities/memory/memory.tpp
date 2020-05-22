#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SharedPtr
	//-------------------------------------------------------------------------
	#pragma region

	template< typename T, typename... ConstructorArgsT >
	inline SharedPtr< T > MakeShared(ConstructorArgsT&&... args) {
		return std::make_shared< T >(std::forward< ConstructorArgsT >(args)...);
	}

	template< typename T, typename... ConstructorArgsT >
	inline SharedPtr< T > MakeAllocatedShared(ConstructorArgsT&&... args) {
		return SharedPtr< T >(new T{ std::forward< ConstructorArgsT >(args)... });
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// UniquePtr
	//-------------------------------------------------------------------------
	#pragma region

	template< typename T, typename... ConstructorArgsT >
	inline UniquePtr< T > MakeUnique(ConstructorArgsT&&... args) {
		return std::make_unique< T >(std::forward< ConstructorArgsT >(args)...);
	}

	template< typename ToT, typename FromT >
	inline UniquePtr< ToT > static_pointer_cast(UniquePtr< FromT >&& ptr) noexcept {
		return UniquePtr< ToT >(static_cast< ToT* >(ptr.release()));
	}

	template< typename ToT, typename FromT >
	inline UniquePtr< ToT > dynamic_pointer_cast(UniquePtr< FromT >&& ptr) noexcept {
		const auto stored_ptr = ptr.release();
		const auto converted_stored_ptr = dynamic_cast< ToT* >(stored_ptr);
		if (converted_stored_ptr) {
			return UniquePtr< ToT >(converted_stored_ptr);
		}
		else {
			ptr.reset(stored_ptr);
			return UniquePtr< ToT >(nullptr);
		}
	}

	template< typename ToT, typename FromT >
	inline UniquePtr< ToT > const_pointer_cast(UniquePtr< FromT >&& ptr) noexcept {
		return UniquePtr< ToT >(const_cast< ToT* >(ptr.release()));
	}

	template< typename ToT, typename FromT >
	inline UniquePtr< ToT > reinterpret_pointer_cast(UniquePtr< FromT >&& ptr) noexcept {
		return UniquePtr< ToT >(reinterpret_cast< ToT* >(ptr.release()));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ProxyPtr
	//-------------------------------------------------------------------------
	#pragma region

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > static_pointer_cast(const ProxyPtr< FromT >& ptr) noexcept {
		return ProxyPtr< ToT >([getter(ptr.m_getter)]() noexcept {
			return static_cast< ToT* >(getter());
		});
	}

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > static_pointer_cast(ProxyPtr< FromT >&& ptr) noexcept {
		return ProxyPtr< ToT >([getter(std::move(ptr.m_getter))]() noexcept {
			return static_cast< ToT* >(getter());
		});
	}

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > dynamic_pointer_cast(const ProxyPtr< FromT >& ptr) noexcept {
		return ProxyPtr< ToT >([getter(ptr.m_getter)]() noexcept {
			return dynamic_cast< ToT* >(getter());
		});
	}

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > dynamic_pointer_cast(ProxyPtr< FromT >&& ptr) noexcept {
		return ProxyPtr< ToT >([getter(std::move(ptr.m_getter))]() noexcept {
			return dynamic_cast< ToT* >(getter());
		});
	}

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > const_pointer_cast(const ProxyPtr< FromT >& ptr) noexcept {
		return ProxyPtr< ToT >([getter(ptr.m_getter)]() noexcept {
			return const_cast< ToT* >(getter());
		});
	}

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > const_pointer_cast(ProxyPtr< FromT >&& ptr) noexcept {
		return ProxyPtr< ToT >([getter(std::move(ptr.m_getter))]() noexcept {
			return const_cast< ToT* >(getter());
		});
	}

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > reinterpret_pointer_cast(const ProxyPtr< FromT >& ptr) noexcept {
		return ProxyPtr< ToT >([getter(ptr.m_getter)]() noexcept {
			return reinterpret_cast< ToT* >(getter());
		});
	}

	template< typename ToT, typename FromT >
	inline ProxyPtr< ToT > reinterpret_pointer_cast(ProxyPtr< FromT >&& ptr) noexcept {
		return ProxyPtr< ToT >([getter(std::move(ptr.m_getter))]() noexcept {
			return reinterpret_cast< ToT* >(getter());
		});
	}

	#pragma endregion
}