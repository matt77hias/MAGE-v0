#pragma once

//-------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

#ifndef MAGE_HAS_64_BIT_ATOMICS
#if (MAGE_POINTER_SIZE == 8)
#define MAGE_HAS_64_BIT_ATOMICS
#endif
#endif

typedef volatile LONG AtomicInt32;
#ifdef MAGE_HAS_64_BIT_ATOMICS
typedef volatile LONGLONG AtomicInt64;
#endif

//-------------------------------------------------------------------------
// 32 Bit Integers
//-------------------------------------------------------------------------
inline int32_t AtomicAdd(AtomicInt32 *v, int32_t delta) {
#if (MAGE_POINTER_SIZE == 8)
	return InterlockedAdd(v, delta);
#else
	int32_t result;
	_ReadWriteBarrier();
	__asm {
		__asm mov edx, v
		__asm mov eax, delta
		__asm lock xadd[edx], eax
		__asm mov result, eax
	}
	_ReadWriteBarrier();
	return result + delta;
#endif
}

inline int32_t AtomicCompareAndSwap(AtomicInt32 *v, int32_t new_value, int32_t old_value) {
	return InterlockedCompareExchange(v, new_value, old_value);
}

template <typename T>
inline T *AtomicCompareAndSwapPointer(T **v, T *new_value, T *old_value) {
	return InterlockedCompareExchange(v, new_value, old_value);
}

//-------------------------------------------------------------------------
// 64 Bit Integers
//-------------------------------------------------------------------------
#ifdef MAGE_HAS_64_BIT_ATOMICS
inline int64_t AtomicAdd(AtomicInt64 *v, int64_t delta) {
	return InterlockedAdd64(v, delta);
}

inline int64_t AtomicCompareAndSwap(AtomicInt64 *v, int64_t new_value, int64_t old_value) {
	return InterlockedCompareExchange64(v, new_value, old_value);
}
#endif

//-------------------------------------------------------------------------
// Floats
//-------------------------------------------------------------------------
inline float AtomicAdd(volatile float *v, float delta) {
	union bits { float f; int32_t i; };
	bits old_value, new_value;
	do {
#if (defined(__i386__) || defined(__amd64__))
		__asm__ __volatile__("pause\n");
#endif
		old_value.f = *v;
		new_value.f = old_value.f + delta;
	} while (AtomicCompareAndSwap((AtomicInt32 *)v, new_value.i, old_value.i) != old_value.i);
	return new_value.f;
}