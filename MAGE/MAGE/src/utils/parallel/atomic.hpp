#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\type\types.hpp"

#pragma endregion

//-------------------------------------------------------------------------
// System Includes
//-------------------------------------------------------------------------
#pragma region

#include <intrin.h> // _ReadWriteBarrier

// _ReadWriteBarrier effectively blocks an optimization of reads and writes 
// to global memory. This can be useful to ensure the state of global 
// variables at a particular point in the code for multithreaded 
// applications.

#pragma endregion

//-------------------------------------------------------------------------
// Engine Defines
//-------------------------------------------------------------------------
#pragma region

#if (MAGE_POINTER_SIZE == 8)
#define MAGE_HAS_64_BIT_ATOMICS
#endif

#pragma endregion

//-------------------------------------------------------------------------
// Engine Declarations and Definitions
//-------------------------------------------------------------------------
namespace mage {

	/**
	 Atomic 32-bit integer value.
	 */
	using AtomicS32 = volatile LONG;

#ifdef MAGE_HAS_64_BIT_ATOMICS
	/**
	 Atomic 64-bit integer value.
	 */
	using AtomicS64 = volatile LONGLONG;
#endif

	//-------------------------------------------------------------------------
	// Pointers
	//-------------------------------------------------------------------------

	/**
	 Performs an atomic compare-and-exchange operation on the specified 
	 pointers. The function compares the original pointer against a given 
	 comparand pointer and exchanges the original pointer with a given exchange 
	 pointer in case of equality.

	 @tparam		The type of pointer.
	 @pre			@a destination is not equal to @c nullptr.
	 @pre			@a exchange is not equal to @c nullptr.
	 @param[in,out]	destination
					A pointer to a pointer to the destination value.
	 @param[in]		exchange
					The exchange pointer.
	 @param[in]		comparand
					The pointer to compare to @a destination.
	 @return		The function returns the initial pointer of @a destination.
	 */
	template< typename T >
	__forceinline T *AtomicCompareAndSwapPointer(
		T **destination, T *exchange, T *comparand) noexcept {
		
		return InterlockedCompareExchangePointer(
			destination, exchange, comparand);
	}

	//-------------------------------------------------------------------------
	// 32 Bit Integers
	//-------------------------------------------------------------------------

	/**
	 Performs an atomic addition operation on the specified values.

	 @pre			@a addend is not equal to @c nullptr.
	 @param[in,out]	addend
					A pointer to the first operand. This value will be replaced 
					with the result of the operation.
	 @param[in]		value
					The second operand.
	 @return		The function returns the result of the operation.
	 */
	__forceinline S32 AtomicAdd(AtomicS32 *addend, S32 value) noexcept {

#if (MAGE_POINTER_SIZE == 8)
		return InterlockedAdd(addend, value);
#else
		S32 result;
		_ReadWriteBarrier();
		__asm {
			__asm mov edx, addend
			__asm mov eax, value
			__asm lock xadd[edx], eax
			__asm mov result, eax
		}
		_ReadWriteBarrier();
		return result + value;
#endif
	}

	/**
	 Performs an atomic compare-and-exchange operation on the specified values. 
	 The function compares the original value against a given comparand value
	 and exchanges the original value with a given exchange value in case of 
	 equality.

	 @pre			@a destination is not equal to @c nullptr.
	 @param[in,out]	destination
					A pointer to the destination value.
	 @param[in]		exchange
					The exchange value.
	 @param[in]		comparand
					The value to compare to @a destination.
	 @return		The function returns the initial value of @a destination.
	 */
	__forceinline S32 AtomicCompareAndSwap(
		AtomicS32 *destination, S32 exchange, S32 comparand) noexcept {
		
		return InterlockedCompareExchange(destination, exchange, comparand);
	}

	//-------------------------------------------------------------------------
	// 64 Bit Integers
	//-------------------------------------------------------------------------
#ifdef MAGE_HAS_64_BIT_ATOMICS

	/**
	 Performs an atomic addition operation on the specified values.

	 @pre			@a addend is not equal to @c nullptr.
	 @param[in,out]	addend
					A pointer to the first operand. This value will be replaced 
					with the result of the operation.
	 @param[in]		value
					The second operand.
	 @return		The function returns the result of the operation.
	 */
	__forceinline S64 AtomicAdd(AtomicS64 *addend, S64 value) noexcept {
		return InterlockedAdd64(addend, value);
	}

	/**
	 Performs an atomic compare-and-exchange operation on the specified values.
	 The function compares the original value against a given comparand value
	 and exchanges the original value with a given exchange value in case of 
	 equality.

	 @pre			@a destination is not equal to @c nullptr.
	 @param[in,out]	destination
					A pointer to the destination value.
	 @param[in]		exchange
					The exchange value.
	 @param[in]		comparand
					The value to compare to @a destination.
	 @return		The function returns the initial value of @a destination.
	 */
	__forceinline S64 AtomicCompareAndSwap(
		AtomicS64 *destination, S64 exchange, S64 comparand) noexcept {
		
		return InterlockedCompareExchange64(destination, exchange, comparand);
	}
#endif

	//-------------------------------------------------------------------------
	// Floats
	//-------------------------------------------------------------------------
	
	/**
	 Performs an atomic addition operation on the specified values.

	 @pre			@a addend is not equal to @c nullptr.
	 @param[in,out]	addend
					A pointer to the first operand. This value will be replaced 
					with the result of the operation.
	 @param[in]		value
					The second operand.
	 @return		The function returns the result of the operation.
	 */
	__forceinline F32 AtomicAdd(volatile F32 *addend, F32 value) noexcept {
		
		union bits { 
			F32 f; 
			S32 i; 
		};
		
		bits old_value;
		bits new_value;

		do {

#if (defined(__i386__) || defined(__amd64__))
			__asm__ __volatile__("pause\n");
#endif
			old_value.f = *addend;
			new_value.f = old_value.f + value;

		} while (AtomicCompareAndSwap(
			(AtomicS32 *)addend, new_value.i, old_value.i) != old_value.i);
		
		return new_value.f;
	}
}