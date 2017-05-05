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
namespace mage {

	// Unique Pointer type definition.
	template < typename T >
	using UniquePtr = std::unique_ptr< T >;

	using std::make_unique;

	// Shared Pointer type definition.
	template < typename T >
	using SharedPtr = std::shared_ptr< T >;

	using std::make_shared;

	// Weak Pointer type definition.
	template < typename T >
	using WeakPtr = std::weak_ptr< T >;
}

#include <wrl.h>
namespace mage {

	// COM Pointer type definition.
	template < typename T >
	using ComPtr = Microsoft::WRL::ComPtr< T >;
}

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
#pragma region

namespace mage {

	//-------------------------------------------------------------------------
	// UniquePointer
	//-------------------------------------------------------------------------

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
	inline UniquePtr< T > static_pointer_cast(UniquePtr< U > &&ptr) {
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
	inline UniquePtr< T > dynamic_pointer_cast(UniquePtr< U > &&ptr) {
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
	inline UniquePtr< T > const_pointer_cast(UniquePtr< U > &&ptr) {
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
	inline UniquePtr< T > reinterpret_pointer_cast(UniquePtr< U > &&ptr) {
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
	
	// Unique Pointer for handles.
	typedef std::unique_ptr< void, HandleCloser > UniqueHandle;
	// Shared Point for handles.
	typedef SharedPtr< void > SharedHandle;

	/**
	 Converts the given handle to a safe handle.

	 @param[in]		handle
					A handle.
	 @return		If the given handle is an invalid handle, 
					@c nullptr is returned.
	 @return		Otherwise, the given handle is returned.
					
	 */
	inline HANDLE SafeHandle(HANDLE handle) {
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

	// Unique Pointer for file streams.
	typedef std::unique_ptr< FILE, FileStreamCloser > UniqueFileStream;
}

#pragma endregion