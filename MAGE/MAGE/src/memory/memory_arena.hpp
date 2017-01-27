#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "support.hpp"
#include "memory\allocation.hpp"
#include "collection\collection.hpp"

#pragma endregion

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

		 @param[in]		block_size
						The maximum block size in bytes.
		 */
		MemoryArena(size_t block_size = 32768) : 
			m_block_size(block_size), m_current_block_pos(0),
			m_current_block(pair< size_t, char * >(0, nullptr)) {
		}
		
		/**
		 Destructs the given memory arena.
		 */
		virtual ~MemoryArena() {
			FreeAligned(GetCurrentBlockPtr());
			for (const pair< size_t, char * > &block : m_used_blocks) {
				FreeAligned(block.second);
			}
			for (const pair< size_t, char * > &block : m_available_blocks) {
				FreeAligned(block.second);
			}
		}

		/**
		 Returns the maximum block size of this memory arena.

		 @return		The maximum block size of this memory arena.
		 */
		size_t GetBlockSize() const {
			return m_block_size;
		}

		/**
		 Returns the block size (in bytes) of the current block of this memory arena.

		 @return		The block size (in bytes) of the current block of this memory arena.
		 */
		size_t GetCurrentBlockSize() const {
			return m_current_block.first;
		}

		/**
		 Returns the block size (in bytes) of all blocks of this memory arena.

		 @return		The block size (in bytes) of all blocks of this memory arena.
		 */
		size_t GetTotalBlockSize() const {
			size_t size = GetCurrentBlockSize();
			for (const pair< size_t, char * > &block : m_used_blocks) {
				size += block.first;
			}
			for (const pair< size_t, char * > &block : m_available_blocks) {
				size += block.first;
			}
			return size;
		}

		/**
		 Returns a pointer to the current block of this memory arena.

		 @return		A pointer to the current block of this memory arena.
		 */
		char *GetCurrentBlockPtr() const {
			return m_current_block.second;
		}

		/**
		 Resets this memory arena.
		 */
		void Reset() {
			m_current_block_pos = 0;
			m_current_block = pair< size_t, char * >(0, nullptr);
			m_available_blocks.splice(m_available_blocks.begin(), m_used_blocks);
		}

		/**
		 Allocates a block of memory of the given size.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 */
		void *Alloc(size_t size) {
			// Round up size to minimum machine alignment
			size = ((size + 15) & (~15));
			
			if (m_current_block_pos + size > GetCurrentBlockSize()) {
				// Store current block (if existing) as used block.
				if (GetCurrentBlockPtr()) {
					m_used_blocks.push_back(m_current_block);
				}
				
				// Fetch new block from available blocks.
				for (list< pair< size_t, char * > >::iterator it = m_available_blocks.begin(); it != m_available_blocks.end(); ++it) {
					if (it->first >= size) {
						m_current_block = *it;
						m_available_blocks.erase(it);
						break;
					}
				}
				
				if (!GetCurrentBlockPtr()) {
					// Allocate new block.
					const size_t alloc_size = max(size, GetBlockSize());
					char *alloc_ptr = AllocAligned< char >(alloc_size);
					m_current_block = pair< size_t, char * >(alloc_size, alloc_ptr);
				}

				m_current_block_pos = 0;
			}

			void *ptr = GetCurrentBlockPtr() + m_current_block_pos;
			m_current_block_pos += size;
			return ptr;
		}

		/**
		 Allocates a block of memory.

		 @tparam		T
						The type of objects to allocate in memory.
		 @param[in]		count
						The number of objects of type @c T to allocate in memory.
		 @param[in]		initialization
						Flag indicating whether the objects need to be initialized
						(i.e. the constructor needs to be called).
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 @note			The objects will be constructed with their default empty constructor.
		 */
		template<typename T>
		T *Alloc(size_t count = 1, bool initialization = true) {
			// Allocation
			T *ptr = (T *)Alloc(count * sizeof(T));

			if (ptr == nullptr) {
				// The allocation failed.
				return nullptr;
			}

			// Initialization
			if (initialization) {
				for (size_t i = 0; i < count; ++i) {
					new (&ptr[i]) T();
				}
			}
			return ptr;
		}

	protected:

		/**
		 Constructs a memory arena from the given memory arena.

		 @param[in]		arena
						The memory arena.
		 */
		MemoryArena(const MemoryArena &arena) = delete;

		/**
		 Copies the given memory arena to this memory arena.

		 @param[in]		arena
						The memory arena.
		 */
		MemoryArena &operator=(const MemoryArena &arena) = delete;
		
		/**
		 The fixed block size of this memory arena.
		 */
		const size_t m_block_size;

		/**
		 The current block position of this memory arena.
		 */
		size_t m_current_block_pos;

		/**
		 A pointer to the current block of this memory arena.
		 */
		pair< size_t, char * > m_current_block;
		
		/**
		 Pointers to the used blocks of this memory arena.
		 */
		list< pair< size_t, char * > > m_used_blocks;

		/**
		 Pointers to the available blocks of this memory arena.
		 */
		list< pair< size_t, char * > > m_available_blocks;
	};
}
