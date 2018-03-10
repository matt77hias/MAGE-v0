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
	 Reads a @c DataT element from the given big endian byte array.

	 @pre			The given byte array must contain at least @c sizeof(DataT) 
					bytes.
	 @tparam		DataT
					The data type.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c DataT element represented by the big endian byte 
					array @a bytes.
	 */
	template< typename DataT >
	[[nodiscard]]
	inline const DataT BytesBigEndianTo(NotNull< const U8* > bytes) noexcept {
		return *reinterpret_cast< const DataT* >(bytes.get());
	}

	/**
	 Reads a @c DataT element from the given little endian byte array.

	 @pre			The given byte array must contain at least @c sizeof(DataT) 
					bytes.
	 @tparam		DataT
					The data type.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c DataT element represented by the little endian byte 
					array @a bytes.
	 */
	template< typename DataT >
	[[nodiscard]]
	const DataT BytesLittleEndianTo(NotNull< const U8* > bytes) noexcept;

	/**
	 Reads a @c DataT element from the given byte array.

	 @pre			The given byte array must contain at least @c sizeof(DataT) 
					bytes.
	 @tparam		DataT
					The data type.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					@c true if the given byte array should be interpreted as 
					big endian. @c false otherwise (i.e. little endian).
	 @return		The @c DataT element represented by the byte array 
					@a bytes.
	 */
	template< typename DataT >
	[[nodiscard]]
	inline const DataT BytesTo(NotNull< const U8* > bytes, 
							   bool big_endian) noexcept {
		
		return (big_endian) ? BytesBigEndianTo< DataT >(bytes)
			                : BytesLittleEndianTo< DataT >(bytes);
	}
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_utils.tpp"

#pragma endregion
