//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\logging.hpp"
#include "memory\allocation.hpp"
#include "memory\memory_stack.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// MemoryStack
	//-------------------------------------------------------------------------
	#pragma region

	SingleEndedMemoryStack::SingleEndedMemoryStack(std::size_t size,
												   std::size_t alignment)
		: m_alignment(alignment),
		m_size(size),
		m_begin(),
		m_current() {

		const auto ptr = AllocAligned(m_size, m_alignment);
		if (!ptr) {
			throw std::bad_alloc();
		}

		m_begin = reinterpret_cast< std::uintptr_t >(ptr);
		Reset();
	}

	SingleEndedMemoryStack::SingleEndedMemoryStack(
		SingleEndedMemoryStack&& stack) noexcept = default;

	SingleEndedMemoryStack::~SingleEndedMemoryStack() {
		FreeAligned((void*)m_begin);
	}

	void SingleEndedMemoryStack::Reset() noexcept {
		RollBack(m_begin);
	}

	void SingleEndedMemoryStack::RollBack(std::uintptr_t ptr) noexcept {
		Assert(m_begin <= ptr && ptr <= m_current);

		m_current = ptr;
	}

	void* SingleEndedMemoryStack::Alloc(std::size_t size) noexcept {
		if (GetAvailableSize() < size) {
			// The allocation failed.
			return nullptr;
		}

		const auto ptr = (void*)m_current;
		m_current += size;
		return ptr;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// DoubleEndedMemoryStack
	//-------------------------------------------------------------------------
	#pragma region

	DoubleEndedMemoryStack::DoubleEndedMemoryStack(std::size_t size,
												   std::size_t alignment)
		: m_alignment(alignment),
		m_size(size),
		m_begin(),
		m_current_low(),
		m_current_high() {

		const auto ptr = AllocAligned(m_size, m_alignment);
		if (!ptr) {
			throw std::bad_alloc();
		}

		m_begin = reinterpret_cast< std::uintptr_t >(ptr);
		Reset();
	}

	DoubleEndedMemoryStack::DoubleEndedMemoryStack(
		DoubleEndedMemoryStack&& stack) noexcept = default;

	DoubleEndedMemoryStack::~DoubleEndedMemoryStack() {
		FreeAligned((void*)m_begin);
	}

	void DoubleEndedMemoryStack::Reset() noexcept {
		RollBackLow(m_begin);
		RollBackHigh(m_begin + m_size - 1u);
	}

	void DoubleEndedMemoryStack::RollBackLow(std::uintptr_t ptr) noexcept {
		Assert(m_begin <= ptr && ptr <= m_current_low);

		m_current_low = ptr;
	}

	void DoubleEndedMemoryStack::RollBackHigh(std::uintptr_t ptr) noexcept {
		Assert(m_current_high <= ptr && ptr < m_begin + m_size);

		m_current_high = ptr;
	}

	void* DoubleEndedMemoryStack::AllocLow(std::size_t size) noexcept {
		if (GetAvailableSize() < size) {
			// The allocation failed.
			return nullptr;
		}

		const auto ptr = (void*)m_current_low;
		m_current_low += size;
		return ptr;
	}

	void* DoubleEndedMemoryStack::AllocHigh(std::size_t size) noexcept {
		if (GetAvailableSize() < size) {
			// The allocation failed.
			return nullptr;
		}

		const auto ptr = (void*)m_current_high;
		m_current_high -= size;
		return ptr;
	}

	#pragma endregion
}