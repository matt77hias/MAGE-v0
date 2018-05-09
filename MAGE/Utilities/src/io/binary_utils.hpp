#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	/**
	 Reads a @c T element from the given big endian byte array.

	 @pre			The given byte array must contain at least @c sizeof(T) 
					bytes.
	 @tparam		T
					The data type.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c T element represented by the big endian byte array 
					@a bytes.
	 */
	template< typename T >
	[[nodiscard]]
	inline const T BytesBigEndianTo(NotNull< const U8* > bytes) noexcept {
		return *reinterpret_cast< const T* >(bytes.get());
	}

	/**
	 Reads a @c T element from the given little endian byte array.

	 @pre			The given byte array must contain at least @c sizeof(T) 
					bytes.
	 @tparam		T
					The data type.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c T element represented by the little endian byte 
					array @a bytes.
	 */
	template< typename T >
	[[nodiscard]]
	const T BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept;

	/**
	 Reads a @c T element from the given byte array.

	 @pre			The given byte array must contain at least @c sizeof(T) 
					bytes.
	 @tparam		T
					The data type.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					@c true if the given byte array should be interpreted as 
					big endian. @c false otherwise (i.e. little endian).
	 @return		The @c T element represented by the byte array @a bytes.
	 */
	template< typename T >
	[[nodiscard]]
	inline const T BytesTo(NotNull< const U8* > bytes, bool big_endian) noexcept {
		return (big_endian) ? BytesBigEndianTo< T >(bytes)
			                : BytesLittleEndianTo< T >(bytes);
	}
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_utils.tpp"

#pragma endregion
