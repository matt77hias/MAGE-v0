#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"

#pragma endregion

//-------------------------------------------------------------------------
// System Includes
//-------------------------------------------------------------------------
#pragma region

#include <stdint.h>
#include <intrin.h> // _ReadWriteBarrier

// _ReadWriteBarrier effectively blocks an optimization of reads and writes 
// to global memory. This can be useful to ensure the state of global variables 
// at a particular point in the code for multithreaded applications.

#pragma endregion

//-------------------------------------------------------------------------
// Engine Defines
//-------------------------------------------------------------------------
#pragma region

#ifndef MAGE_HAS_64_BIT_ATOMICS
#if (MAGE_POINTER_SIZE == 8)
#define MAGE_HAS_64_BIT_ATOMICS
#endif
#endif

typedef volatile LONG AtomicInt32;
#ifdef MAGE_HAS_64_BIT_ATOMICS
typedef volatile LONGLONG AtomicInt64;
#endif

#pragma endregion

//-------------------------------------------------------------------------
// Engine Declarations and Definitions
//-------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Pointers
	//-------------------------------------------------------------------------

	/**
	 Performs an atomic compare-and-exchange operation on the specified pointers.
	 The function compares the original pointer against a given comparand pointer
	 and exchanges the original pointer with a given exchange pointer in case of equality.


	 @param[in, out]	destination
	 @param[in]		exchange
					The exchange pointer.
	 @param[in]		comparand
					The pointer to compare to @a destination.
	 @return		The function returns the initial pointer of @a destination.
	 */
	template <typename T>
	inline T *AtomicCompareAndSwapPointer(T **destination, T *exchange, T *comparand) {
		return InterlockedCompareExchangePointer(destination, exchange, comparand);
	}

	//-------------------------------------------------------------------------
	// 32 Bit Integers
	//-------------------------------------------------------------------------

	/**
	 Performs an atomic addition operation on the specified values.

	 @param[in, out]	addend
					A pointer to the first operand. This value will be 
					replaced with the result of the operation.
	 @param[in]		value
					The second operand.
	 @return		The function returns the result of the operation.
	 */
	inline int32_t AtomicAdd(AtomicInt32 *addend, int32_t value) {
#if (MAGE_POINTER_SIZE == 8)
		return InterlockedAdd(addend, value);
#else
		int32_t result;
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
	 and exchanges the original value with a given exchange value in case of equality.

	 @param[in, out]	destination
	 @param[in]		exchange
					The exchange value.
	 @param[in]		comparand
					The value to compare to @a destination.
	 @return		The function returns the initial value of @a destination.
	 */
	inline int32_t AtomicCompareAndSwap(AtomicInt32 *destination, int32_t exchange, int32_t comparand) {
		return InterlockedCompareExchange(destination, exchange, comparand);
	}

	//-------------------------------------------------------------------------
	// 64 Bit Integers
	//-------------------------------------------------------------------------
#ifdef MAGE_HAS_64_BIT_ATOMICS

	/**
	 Performs an atomic addition operation on the specified values.

	 @param[in, out]	addend
					A pointer to the first operand. This value will be
					replaced with the result of the operation.
	 @param[in]		value
					The second operand.
	 @return		The function returns the result of the operation.
	 */
	inline int64_t AtomicAdd(AtomicInt64 *addend, int64_t value) {
		return InterlockedAdd64(addend, value);
	}

	/**
	 Performs an atomic compare-and-exchange operation on the specified values.
	 The function compares the original value against a given comparand value
	 and exchanges the original value with a given exchange value in case of equality.

	 @param[in, out]	destination
	 @param[in]		exchange
					The exchange value.
	 @param[in]		comparand
					The value to compare to @a destination.
	 @return		The function returns the initial value of @a destination.
	 */
	inline int64_t AtomicCompareAndSwap(AtomicInt64 *destination, int64_t exchange, int64_t comparand) {
		return InterlockedCompareExchange64(destination, exchange, comparand);
	}
#endif

	//-------------------------------------------------------------------------
	// Floats
	//-------------------------------------------------------------------------
	
	/**
	 Performs an atomic addition operation on the specified values.

	 @param[in, out]	addend
					A pointer to the first operand. This value will be
					replaced with the result of the operation.
	 @param[in]		value
					The second operand.
	 @return		The function returns the result of the operation.
	 */
	inline float AtomicAdd(volatile float *addend, float value) {
		union bits { float f; int32_t i; };
		bits old_value, new_value;

		do {
#if (defined(__i386__) || defined(__amd64__))
			__asm__ __volatile__("pause\n");
#endif
			old_value.f = *addend;
			new_value.f = old_value.f + value;
		} while (AtomicCompareAndSwap((AtomicInt32 *)addend, new_value.i, old_value.i) != old_value.i);
		// Cast the pointer (not the referred value)
		
		return new_value.f;
	}
}