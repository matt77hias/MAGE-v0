#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Big Endian
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Reads a @c DataT element from the given big endian byte array.

	 @tparam		DataT
					The data type.
	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(DataT) 
					bytes.
	 @param[in]		bytes
					A pointer to a big endian byte array.
	 @return		The @c DataT element represented by the big endian byte 
					array @a bytes.
	 */
	template< typename DataT >
	const DataT BytesBigEndianTo(const U8 *bytes) noexcept {
		Assert(bytes);
		return *reinterpret_cast< const DataT * >(bytes);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Little Endian
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Reads a @c DataT element from the given little endian byte array.

	 @tparam		DataT
					The data type.
	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(DataT) 
					bytes.
	 @param[in]		bytes
					A pointer to a little endian byte array.
	 @return		The @c DataT element represented by the little endian byte 
					array @a bytes.
	 */
	template< typename DataT >
	const DataT BytesLittleEndianTo(const U8 *bytes) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// Binary Conversion Utilities: Big | Little Endian
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Reads a @c DataT element from the given byte array.

	 @tparam		DataT
					The data type.
	 @pre			@a bytes is not equal to @c nullptr.
	 @pre			The given byte array must contain at least @c sizeof(DataT) 
					bytes.
	 @param[in]		bytes
					A pointer to a byte array.
	 @param[in]		big_endian
					@c true if the given byte array should be interpreted as 
					big endian. @c false otherwise (i.e. little endian).
	 @return		The @c DataT element represented by the byte array 
					@a bytes.
	 */
	template< typename DataT >
	inline const DataT BytesTo(const U8 *bytes, bool big_endian) noexcept {
		Assert(bytes);
		return (big_endian) ? BytesBigEndianTo< DataT >(bytes)
			                : BytesLittleEndianTo< DataT >(bytes);
	}

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\binary_utils.tpp"

#pragma endregion
