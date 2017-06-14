#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <memory>
#include <wrl.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

// Pointer size macros
#ifndef MAGE_POINTER_SIZE
#if defined(__amd64__) || defined(_M_X64)
#define MAGE_X64
#define MAGE_POINTER_SIZE 8
#elif defined(__i386__) || defined(_M_IX86)
#define MAGE_X86
#define MAGE_POINTER_SIZE 4
#endif
#endif

// Memory management macros
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p) = nullptr; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p) = nullptr; } }

// Supresses C4100: unreferenced formal parameter
#define UNUSED(param) (void)(param)

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ComPtr
	//-------------------------------------------------------------------------

	/**
	 A class of smart pointers for managing shared-ownership COM resources.

	 @tparam		T
					The COM resource type.
	 */
	template < typename T >
	using ComPtr = Microsoft::WRL::ComPtr< T >;

	//-------------------------------------------------------------------------
	// SharedPointer
	//-------------------------------------------------------------------------

	/**
	 A class of smart pointers for managing shared-ownership memory resources.

	 @tparam		T
					The memory resource type.
	 */
	template < typename T >
	using SharedPtr = std::shared_ptr< T >;

	//-------------------------------------------------------------------------
	// WeakPointer
	//-------------------------------------------------------------------------

	/**
	 A class of smart pointers for referencing but not managing
	 shared-ownership memory resources.

	 @tparam		T
					The memory resource type.
	 */
	template < typename T >
	using WeakPtr = std::weak_ptr< T >;

	//-------------------------------------------------------------------------
	// UniquePointer
	//-------------------------------------------------------------------------

	/**
	 A class of smart pointers for managing exclusive-ownership memory resources.

	 @tparam		T
					The memory resource type.
	 */
	template < typename T >
	using UniquePtr = std::unique_ptr< T >;

	/**
	 Creates a unique pointer whose stored pointer is obtained
	 by statically casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
	template< typename T, typename U >
	inline UniquePtr< T > static_pointer_cast(UniquePtr< U > &&ptr) noexcept {
		return UniquePtr< T >(static_cast< T * >(ptr.release()));
	}

	/**
	 Creates a unique pointer whose stored pointer is obtained
	 by dynamically casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
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

	/**
	 Creates a unique pointer whose stored pointer is obtained
	 by const casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
	template< typename T, typename U >
	inline UniquePtr< T > const_pointer_cast(UniquePtr< U > &&ptr) noexcept {
		return UniquePtr< T >(const_cast< T * >(ptr.release()));
	}

	/**
	 Creates a unique pointer whose stored pointer is obtained
	 by reinterpret casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
	template< typename T, typename U >
	inline UniquePtr< T > reinterpret_pointer_cast(UniquePtr< U > &&ptr) noexcept {
		return UniquePtr< T >(reinterpret_cast< T * >(ptr.release()));
	}

	//-------------------------------------------------------------------------
	// UniqueHandle and SharedHandle
	//-------------------------------------------------------------------------

	/**
	 Destructs the given handle.

	 @param[in]		handle
					The handle to destruct.
	 */
	inline void DestructHandle(HANDLE handle) {
		if (handle) {
			CloseHandle(handle);
		}
	}

	/**
	 A struct of handle destructors (i.e. for closing handles).
	 */
	struct HandleCloser final {

		/**
		 Destructs the given handle.

		 @param[in]		handle
						The handle to destruct.
		 */
		void operator()(HANDLE handle) const {
			DestructHandle(handle);
		}
	};

	/**
	 A class of smart pointers for managing exclusive-ownership handle resources.
	 */
	using UniqueHandle = std::unique_ptr< void, HandleCloser >;

	/**
	 A class of smart pointers for managing shared-ownership handle resources.
	 */
	using SharedHandle = SharedPtr< void >;

	/**
	 Converts the given handle to a safe handle.

	 @param[in]		handle
					A handle.
	 @return		If the given handle is an invalid handle,
					@c nullptr is returned.
	 @return		Otherwise, the given handle is returned.

	 */
	inline HANDLE SafeHandle(HANDLE handle) noexcept {
		return (handle == INVALID_HANDLE_VALUE) ? nullptr : handle;
	}

	/**
	 Creates a shared handle for the given handle.

	 @param[in]		handle
					A handle.
	 @return		A shared handle for the given handle @a handle.
	 */
	inline SharedHandle CreateSharedHandle(HANDLE handle) {
		return SharedHandle(SafeHandle(handle), DestructHandle);
	}

	//-------------------------------------------------------------------------
	// UniqueFileStream
	//-------------------------------------------------------------------------

	/**
	 A struct of file stream destructors (i.e. for closing file streams).
	 */
	struct FileStreamCloser final {

		/**
		 Destructs the file stream.

		 @param[in]		stream
						A pointer to a file stream to destruct.
		 */
		void operator()(FILE *stream) const {
			if (stream) {
				fclose(stream);
			}
		}
	};

	/**
	 A class of smart pointers for managing exclusive-ownership file streams.
	 */
	using UniqueFileStream = std::unique_ptr< FILE, FileStreamCloser >;
}