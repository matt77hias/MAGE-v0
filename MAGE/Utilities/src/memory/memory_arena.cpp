//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "memory\memory_arena.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	MemoryArena::MemoryArena(std::size_t maximum_block_size,
							 std::size_t alignment)
		: m_alignment(alignment),
		m_maximum_block_size(maximum_block_size),
		m_current_block(0u, nullptr),
		m_current_block_pos(0u),
		m_used_blocks(),
		m_available_blocks() {}

	MemoryArena::MemoryArena(MemoryArena&& arena) = default;

	MemoryArena::~MemoryArena() {
		FreeAligned(GetCurrentBlockPtr());

		for (const auto& block : m_used_blocks) {
			FreeAligned(block.second);
		}

		for (const auto& block : m_available_blocks) {
			FreeAligned(block.second);
		}
	}

	[[nodiscard]]
	std::size_t MemoryArena::GetTotalBlockSize() const noexcept {
		auto size = GetCurrentBlockSize();

		for (const auto& block : m_used_blocks) {
			size += block.first;
		}

		for (const auto& block : m_available_blocks) {
			size += block.first;
		}

		return size;
	}

	void MemoryArena::Reset() {
		using std::begin;

		m_current_block_pos = 0u;
		m_current_block     = { 0u, nullptr };
		m_available_blocks.splice(begin(m_available_blocks), m_used_blocks);
	}

	void* MemoryArena::Alloc(std::size_t size) {
		using std::begin;
		using std::end;

		// Round up the given size to minimum machine alignment.
		size = ((size + 15u) & (~15u));

		if (m_current_block_pos + size > GetCurrentBlockSize()) {

			// Store current block (if existing) as used block.
			if (GetCurrentBlockPtr()) {
				m_used_blocks.push_back(m_current_block);
			}

			// Fetch new block from available blocks (if possible).
			for (auto it = begin(m_available_blocks);
				 it != end(m_available_blocks); ++it) {

				if (it->first >= size) {
					m_current_block = *it;
					m_available_blocks.erase(it);
					break;
				}
			}

			// Allocate new block (if needed).
			if (!GetCurrentBlockPtr()) {
				// Allocate new block.
				const auto alloc_size = std::max(size, GetMaximumBlockSize());
				const auto alloc_ptr  = AllocAlignedData< U8 >(alloc_size, m_alignment);

				if (!alloc_ptr) {
					// The allocation failed.
					return nullptr;
				}

				m_current_block = { alloc_size, alloc_ptr };
			}

			m_current_block_pos = 0u;
		}

		const auto ptr = static_cast< void* >(
			m_current_block.second + m_current_block_pos);

		m_current_block_pos += size;

		return ptr;
	}
}