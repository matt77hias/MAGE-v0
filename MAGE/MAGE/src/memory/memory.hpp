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
#if defined(__amd64__) || defined(_M_X64)
#define MAGE_X64
#define MAGE_POINTER_SIZE 8
#elif defined(__i386__) || defined(_M_IX86)
#define MAGE_X86
#define MAGE_POINTER_SIZE 4
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
#pragma region

	/**
	 A class of smart pointers for managing shared-ownership COM resources.

	 @tparam		T
					The COM resource type.
	 */
	template < typename T >
	using ComPtr = Microsoft::WRL::ComPtr< T >;

#pragma endregion

	//-------------------------------------------------------------------------
	// SharedPointer
	//-------------------------------------------------------------------------
#pragma region

	/**
	 A class of smart pointers for managing shared-ownership memory resources.

	 @tparam		T
					The memory resource type.
	 */
	template < typename T >
	using SharedPtr = std::shared_ptr< T >;

	/**
	 Constructs an object of type T. 

	 No custom allocator is used for constructing the object of type T.

	 @tparam		T
					The type.
	 @tparam		ConstructorArgsT
					The constructor argument types of the camera.
	 @return		A shared pointer to the constructed object of type T.
	 */
	template< typename T, typename... ConstructorArgsT >
	SharedPtr< T > MakeShared(ConstructorArgsT&&... args);

	/**
	 Constructs an object of type T.

	 The custom allocator is used for constructing the object of type T.

	 @tparam		T
					The type.
	 @tparam		ConstructorArgsT
					The constructor argument types of the camera.
	 @return		A shared pointer to the constructed object of type T.
	 */
	template< typename T, typename... ConstructorArgsT >
	SharedPtr< T > MakeAllocatedShared(ConstructorArgsT&&... args);

#pragma endregion

	//-------------------------------------------------------------------------
	// WeakPointer
	//-------------------------------------------------------------------------
#pragma region

	/**
	 A class of smart pointers for referencing but not managing 
	 shared-ownership memory resources.

	 @tparam		T
					The memory resource type.
	 */
	template < typename T >
	using WeakPtr = std::weak_ptr< T >;

#pragma endregion

	//-------------------------------------------------------------------------
	// UniquePointer
	//-------------------------------------------------------------------------
#pragma region

	/**
	 A class of smart pointers for managing exclusive-ownership memory 
	 resources.

	 @tparam		T
					The memory resource type.
	 */
	template < typename T, typename DeleterT = std::default_delete< T > >
	using UniquePtr = std::unique_ptr< T, DeleterT >;

	/**
	 Constructs a non-array type T. This overload only participates in overload 
	 resolution if T is not an array type.

	 @tparam		T
					The type.
	 @tparam		ConstructorArgsT
					The constructor argument types of the camera.
	 @return		A unique pointer to the constructed non-array type T.
	 */
	template< typename T, typename... ConstructorArgsT >
	typename std::enable_if< !std::is_array< T >::value, 
		UniquePtr< T > >::type MakeUnique(ConstructorArgsT&&... args);
	
	/**
	 Constructs an array of unknown bound T. This overload only participates 
	 in overload resolution if T is an array of unknown bound.

	 @tparam		T
					The type.
	 @param[in]		count
					The number of elements of the array to construct.
	 @return		A unique pointer to the constructed array of unknown bound T.
	 */
	template< typename T >
	typename std::enable_if< std::is_array< T >::value && std::extent< T >::value == 0,
		UniquePtr< T > >::type MakeUnique(size_t count);

	/**
	 Constructs an array of known bound T. This overload only participates
	 in overload resolution if T is an array of known bound.

	 @tparam		T
					The type.
	 @param[in]		count
					The number of elements of the array to construct.
	 @return		A unique pointer to the constructed array of known bound T.
	 */
	template< typename T >
	typename std::enable_if< std::extent< T >::value != 0,
		UniquePtr< T > >::type MakeUnique(size_t count) = delete;
	
	/**
	 Creates a unique pointer whose stored pointer is obtained by statically 
	 casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
	template< typename T, typename U >
	inline UniquePtr< T > static_pointer_cast(UniquePtr< U > &&ptr) noexcept;

	/**
	 Creates a unique pointer whose stored pointer is obtained by dynamically 
	 casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
	template< typename T, typename U >
	inline UniquePtr< T > dynamic_pointer_cast(UniquePtr< U > &&ptr) noexcept;

	/**
	 Creates a unique pointer whose stored pointer is obtained by const 
	 casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
	template< typename T, typename U >
	inline UniquePtr< T > const_pointer_cast(UniquePtr< U > &&ptr) noexcept;

	/**
	 Creates a unique pointer whose stored pointer is obtained by reinterpret 
	 casting the stored pointer of the given unique pointer.

	 @tparam		T
					The conversion to-type.
	 @tparam		U
					The conversion from-type.
	 @param[in]		ptr
					The unique pointer to move.
	 @return		The moved unique pointer.
	 */
	template< typename T, typename U >
	inline UniquePtr< T > reinterpret_pointer_cast(UniquePtr< U > &&ptr) noexcept;

#pragma endregion

	//-------------------------------------------------------------------------
	// UniqueHandle and SharedHandle
	//-------------------------------------------------------------------------
#pragma region

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
	 A class of smart pointers for managing exclusive-ownership handle 
	 resources.
	 */
	using UniqueHandle = UniquePtr< void, HandleCloser >;

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

#pragma endregion

	//-------------------------------------------------------------------------
	// UniqueFileStream
	//-------------------------------------------------------------------------
#pragma region

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
	using UniqueFileStream = UniquePtr< FILE, FileStreamCloser >;

#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.tpp"

#pragma endregion