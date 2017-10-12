//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory_stack.hpp"
#include "memory\allocation.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// MemoryStack
	//-------------------------------------------------------------------------

	SingleEndedMemoryStack::SingleEndedMemoryStack(
		size_t size, size_t alignment)
		: m_alignment(alignment), m_size(size), 
		m_begin(), m_current() {

		void * const ptr = AllocAligned(m_size, m_alignment);
		if (!ptr) {
			throw std::bad_alloc();
		}

		m_begin = reinterpret_cast< uintptr_t >(ptr);
		Reset();
	}

	SingleEndedMemoryStack::SingleEndedMemoryStack(
		SingleEndedMemoryStack &&stack) = default;

	SingleEndedMemoryStack::~SingleEndedMemoryStack() {
		FreeAligned(reinterpret_cast< void * >(m_begin));
	}

	void SingleEndedMemoryStack::Reset() noexcept {
		m_current = m_begin;
	}

	void SingleEndedMemoryStack::RollBack(uintptr_t ptr) noexcept {
		Assert(m_begin <= ptr && ptr <= m_current);
		
		m_current = ptr;
	}

	void *SingleEndedMemoryStack::Alloc(size_t size) noexcept {
		if (GetAvailableSize() < size) {
			// The allocation failed.
			return nullptr;
		}
		
		void * const ptr = reinterpret_cast< void * >(m_current);
		m_current += size;
		return ptr;
	}

	//-------------------------------------------------------------------------
	// DoubleEndedMemoryStack
	//-------------------------------------------------------------------------

	DoubleEndedMemoryStack::DoubleEndedMemoryStack(
		size_t size, size_t alignment)
		: m_alignment(alignment), m_size(size),
		m_begin(), m_current_low(), m_current_high() {

		void * const ptr = AllocAligned(m_size, m_alignment);
		if (!ptr) {
			throw std::bad_alloc();
		}

		m_begin = reinterpret_cast< uintptr_t >(ptr);
		Reset();
	}

	DoubleEndedMemoryStack::DoubleEndedMemoryStack(
		DoubleEndedMemoryStack &&stack) = default;

	DoubleEndedMemoryStack::~DoubleEndedMemoryStack() {
		FreeAligned(reinterpret_cast< void * >(m_begin));
	}

	void DoubleEndedMemoryStack::Reset() noexcept {
		m_current_low  = m_begin;
		m_current_high = m_begin + m_size;
	}

	void DoubleEndedMemoryStack::RollBackLow(uintptr_t ptr) noexcept {
		Assert(m_begin <= ptr && ptr <= m_current_low);
		
		m_current_low = ptr;
	}

	void DoubleEndedMemoryStack::RollBackHigh(uintptr_t ptr) noexcept {
		Assert(m_current_high <= ptr && ptr <= m_begin + m_size);
		
		m_current_high = ptr;
	}

	void *DoubleEndedMemoryStack::AllocLow(size_t size) noexcept {
		if (GetAvailableSize() < size) {
			// The allocation failed.
			return nullptr;
		}

		void * const ptr = reinterpret_cast< void * >(m_current_low);
		m_current_low += size;
		return ptr;
	}

	void *DoubleEndedMemoryStack::AllocHigh(size_t size) noexcept {
		if (GetAvailableSize() < size) {
			// The allocation failed.
			return nullptr;
		}

		void * const ptr = reinterpret_cast< void * >(m_current_high);
		m_current_high -= size;
		return ptr;
	}
}