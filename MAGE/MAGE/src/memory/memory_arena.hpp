#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of memory arenas.
	 */
	class MemoryArena final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a memory arena with given block size.

		 @param[in]		maximum_block_size
						The maximum block size in bytes.
		 */
		explicit MemoryArena(size_t maximum_block_size = 32768);

		/**
		 Constructs a memory arena from the given memory arena.

		 @param[in]		arena
						A reference to the memory arena to copy.
		 */
		MemoryArena(const MemoryArena &arena) = delete;

		/**
		 Constructs a memory arena by moving the given memory arena.

		 @param[in]		arena
						A reference to the memory arena to move.
		 */
		MemoryArena(MemoryArena &&arena);
		
		/**
		 Destructs this memory arena.
		 */
		~MemoryArena();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given memory arena to this memory arena.

		 @param[in]		arena
						A reference to the memory arena to copy.
		 @return		A reference to the copy of the given memory arena
						(i.e. this memory arena).
		 */
		MemoryArena &operator=(const MemoryArena &arena) = delete;

		/**
		 Moves the given memory arena to this memory arena.

		 @param[in]		arena
						A reference to the memory arena to move.
		 @return		A reference to the moved memory arena
						(i.e. this memory arena).
		 */
		MemoryArena &operator=(MemoryArena &&arena) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the maximum block size of this memory arena.

		 @return		The maximum block size of this memory arena.
		 */
		size_t GetMaximumBlockSize() const {
			return m_maximum_block_size;
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
		size_t GetTotalBlockSize() const;

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
		void Reset();

		/**
		 Allocates a block of memory of the given size.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 */
		void *Alloc(size_t size);

		/**
		 Allocates a block of memory.

		 @tparam		DataT
						The type of objects to allocate in memory.
		 @param[in]		count
						The number of objects of type @c DataT to allocate in memory.
		 @param[in]		initialization
						Flag indicating whether the objects need to be initialized
						(i.e. the constructor needs to be called).
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 @note			The objects will be constructed with their default empty constructor.
		 */
		template< typename DataT >
		DataT *Alloc(size_t count = 1, bool initialization = true);

	private:

		//---------------------------------------------------------------------
		// Type Aliases
		//---------------------------------------------------------------------

		/**
		 A type definition for a memory block.
		 */
		using MemoryBlock = pair< size_t, char * >;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The maximum block size of this memory arena.
		 */
		const size_t m_maximum_block_size;

		/**
		 A pointer to the current block of this memory arena.
		 */
		MemoryBlock m_current_block;

		/**
		 The current block position of this memory arena.
		 */
		size_t m_current_block_pos;
		
		/**
		 A collection containing the used blocks of this memory arena.
		 */
		list< MemoryBlock > m_used_blocks;

		/**
		 A collection containing the available blocks of this memory arena.
		 */
		list< MemoryBlock > m_available_blocks;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory_arena.tpp"

#pragma endregion