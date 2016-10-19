#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of memory arena's.
	 */
	class MemoryArena {

	public:

		/**
		 Constructs a memory arena with given block size.

		 @param[in]		block_size		The block size in bytes.
		 */
		MemoryArena(uint32_t block_size = 32768) : m_block_size(block_size), m_current_block_pos(0) {
			m_current_block = AllocAligned<char>(m_block_size);
		}
		
		/**
		 Destructs the given memory arena.
		 */
		~MemoryArena() {
			FreeAligned(m_current_block);
			for (size_t i = 0; i < m_used_blocks.size(); ++i) {
				FreeAligned(m_used_blocks[i]);
			}
			for (size_t i = 0; i < m_available_blocks.size(); ++i) {
				FreeAligned(m_available_blocks[i]);
			}
		}

		/**
		 Frees all blocks of this memory arena.
		 */
		void FreeAll() {
			// Reposition the current block position
			// to the begin position of the current block
			m_current_block_pos = 0;
			// Make all used blocks available
			while (m_used_blocks.size()) {
				m_available_blocks.push_back(m_used_blocks.back());
				m_used_blocks.pop_back();
			}
		}

		/**
		 Allocates a block of memory of the given size.

		 @param[in]		size	The requested size in bytes to allocate in memory.
		 @return				@c NULL if the allocation failed.
		 @return				A pointer to the memory block that was allocated.
		 */
		void *Alloc(uint32_t size) {
			// Round up size to minimum machine alignment
			size = ((size + 15) & (~15));
			if (m_current_block_pos + size > m_block_size) {
				// Get new block of memory for this memory arena
				if (m_available_blocks.size() && size <= m_block_size) {
					m_used_blocks.push_back(m_current_block);
					m_current_block = m_available_blocks.back();
					m_available_blocks.pop_back();
				}
				else {
					char *ptr = AllocAligned<char>(max(size, m_block_size));
					
					if (ptr == NULL) {
						// The allocation failed.
						return NULL;
					}

					m_used_blocks.push_back(m_current_block);
					m_current_block = ptr;
				}
				m_current_block_pos = 0;
			}
			void *ptr = m_current_block + m_current_block_pos;
			m_current_block_pos += size;
			return ptr;
		}

		/**
		 Allocates a block of memory.

		 @tparam		T		The type of objects to allocate in memory.
		 @param[in]		count	The number of objects of type @c T to allocate in memory.
		 @return				@c NULL if the allocation failed.
		 @return				A pointer to the memory block that was allocated.
		 @note					The objects will be constructed with their default empty constructor.
		 */
		template<typename T>
		T *Alloc(uint32_t count = 1) {
			// Allocation
			T *ptr = (T *)Alloc(count * sizeof(T));

			if (ptr == NULL) {
				// The allocation failed.
				return NULL;
			}

			// Initialization
			for (size_t i = 0; i < count; ++i) {
				new (&ptr[i]) T();
			}
			return ptr;
		}

	private:
		
		/**
		 The current block position of this memory arena.
		 */
		uint32_t m_current_block_pos;

		/**
		 The fixed block size of this memory arena.
		 */
		const uint32_t m_block_size;
		
		/**
		 A pointer to the current block of this memory arena.
		 */
		char *m_current_block;
		
		/**
		 Pointers to the used blocks of this memory arena.
		 */
		vector<char *> m_used_blocks;

		/**
		 Pointers to the available blocks of this memory arena.
		 */
		vector<char *> m_available_blocks;
	};
}
