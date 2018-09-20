#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <list>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of memory arenas.
	 */
	class MemoryArena {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a memory arena with the given block size.

		 @param[in]		maximum_block_size
						The maximum block size in bytes.
		 @param[in]		alignment
						The alignment in bytes.
		 */
		explicit MemoryArena(std::size_t maximum_block_size,
							 std::size_t alignment);

		/**
		 Constructs a memory arena from the given memory arena.

		 @param[in]		arena
						A reference to the memory arena to copy.
		 */
		MemoryArena(const MemoryArena& arena) = delete;

		/**
		 Constructs a memory arena by moving the given memory arena.

		 @param[in]		arena
						A reference to the memory arena to move.
		 */
		MemoryArena(MemoryArena&& arena);

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
		 @return		A reference to the copy of the given memory arena (i.e.
						this memory arena).
		 */
		MemoryArena& operator=(const MemoryArena& arena) = delete;

		/**
		 Moves the given memory arena to this memory arena.

		 @param[in]		arena
						A reference to the memory arena to move.
		 @return		A reference to the moved memory arena (i.e. this memory
						arena).
		 */
		MemoryArena& operator=(MemoryArena&& arena) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the alignment of this memory arena.

		 @return		The alignment in bytes of this memory arena.
		 */
		[[nodiscard]]
		std::size_t GetAlignment() const noexcept {
			return m_alignment;
		}

		/**
		 Returns the maximum block size of this memory arena.

		 @return		The maximum block size in bytes of this memory arena.
		 */
		[[nodiscard]]
		std::size_t GetMaximumBlockSize() const noexcept {
			return m_maximum_block_size;
		}

		/**
		 Returns the block size (in bytes) of the current block of this memory
		 arena.

		 @return		The block size (in bytes) of the current block of this
						memory arena.
		 */
		[[nodiscard]]
		std::size_t GetCurrentBlockSize() const noexcept {
			return m_current_block.first;
		}

		/**
		 Returns the block size (in bytes) of all blocks of this memory arena.

		 @return		The block size (in bytes) of all blocks of this memory
						arena.
		 */
		[[nodiscard]]
		std::size_t GetTotalBlockSize() const noexcept;

		/**
		 Returns a pointer to the current block of this memory arena.

		 @return		A pointer to the current block of this memory arena.
		 */
		[[nodiscard]]
		void* GetCurrentBlockPtr() const noexcept {
			return static_cast< void* >(m_current_block.second);
		}

		/**
		 Resets this memory arena.
		 */
		void Reset();

		/**
		 Allocates a block of memory of the given size on this memory arena.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated. The
						pointer is a multiple of the alignment.
		 */
		void* Alloc(std::size_t size);

		/**
		 Allocates a block of memory on this memory arena.

		 @tparam		T
						The data type.
		 @param[in]		count
						The number of objects of type @c T to allocate in
						memory.
		 @param[in]		initialization
						Flag indicating whether the objects need to be
						initialized (i.e. the constructor needs to be called).
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated. The
						pointer is a multiple of the alignment.
		 @note			The objects will be constructed with their default
						empty constructor.
		 */
		template< typename T >
		T* AllocData(std::size_t count = 1u, bool initialization = false);

		//---------------------------------------------------------------------
		// Allocators
		//---------------------------------------------------------------------

		/**
		 A class of allocators for memory arenas.

		 @tparam		T
						The data type.
		 */
		template< typename T >
		class Allocator {

		public:

			//-----------------------------------------------------------------
			// Class Member Types
			//-----------------------------------------------------------------

			using value_type = T;

			using size_type = std::size_t;

			using difference_type = std::ptrdiff_t;

			using propagate_on_container_move_assignment = std::true_type;

			using is_always_equal = std::false_type;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs an allocator from the given allocator.

			 @param[in]		allocator
							A reference to the allocator to copy.
			 */
			Allocator(const Allocator& allocator) noexcept = default;

			/**
			 Constructs an allocator by moving the given allocator.

			 @param[in]		allocator
							A reference to the allocator to move.
			 */
			Allocator(Allocator&& allocator) noexcept = default;

			/**
			 Constructs an allocator from the given allocator.

			 @tparam		U
							The data type.
			 @param[in]		allocator
							A reference to the allocator to copy.
			 */
			template< typename U >
			Allocator(const Allocator< U >& allocator) noexcept
				: m_memory_arena(allocator.m_memory_arena) {}

			/**
			 Destructs this allocator.
			 */
			~Allocator() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			/**
			 Copies the given allocator to this allocator.

			 @param[in]		allocator
							A reference to the allocator to copy.
			 @return		A reference to the copy of the given allocator
							(i.e. this allocator).
			 */
			Allocator& operator=(const Allocator& allocator) = delete;

			/**
			 Moves the given allocator to this allocator.

			 @param[in]		allocator
							A reference to the allocator to move.
			 @return		A reference to the moved allocator (i.e. this
							allocator).
			 */
			Allocator& operator=(Allocator&& allocator) noexcept = default;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			/**
			 Allocates a block of storage with a size large enough to contain
			 @a count elements of type @c T, and returns a pointer to the first
			 element.

			 @param[in]		count
							The number of objects of type @c T to allocate in
							memory.
			 @return		A pointer to the memory block that was allocated.
							The pointer is a multiple of the alignment.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			T* allocate(std::size_t count) {
				const auto ptr = m_memory_arena->AllocData< T >(count);
				if (!ptr) {
					throw std::bad_alloc();
				}

				return ptr;
			}

			/**
			 Allocates a block of storage with a size large enough to contain
			 @a count elements of type @c T, and returns a pointer to the first
			 element.

			 @param[in]		count
							The number of objects of type @c T to allocate in
							memory.
			 @param[in]		hint
							Either @c nullptr or a value previously obtained by
							another call to
							{@link mage::MemoryArena::Allocator<T>::allocate(std::size_t)}
							and not yet freed with
							{@link mage::MemoryArena::Allocator<T>::deallocate(T*, std::size_t)}.
							When not equal to @c nullptr, this value may be
							used as a hint to improve performance by allocating
							the new block near the one specified. The address
							of an adjacent element is often a good choice.
			 @return		A pointer to the memory block that was allocated. The
							pointer is a multiple of the alignment.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			T* allocate(std::size_t count,
						[[maybe_unused]] const void* hint) {

				return allocate(count);
			}

			/**
			 Releases a block of storage previously allocated with
			 {@link mage::MemoryArena::Allocator<T>::allocate(std::size_t)}
			 and not yet released.

			 @param[in]		data
							A pointer to the memory block that needs to be
							released.
			 @param[in]		count
							The number of objects of type @c T allocated on the call
							to allocate this block of storage.
			 @note			The elements in the array are not destroyed.
			 */
			void deallocate([[maybe_unused]] T* data,
				            [[maybe_unused]] std::size_t count) const noexcept {}

			/**
			 Compares this allocator to the given allocator for equality.

			 @tparam		U
							The data type.
			 @param[in]		rhs
							A reference to the allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							allocator can be deallocated from the given
							allocator, and vice versa. @c false otherwise.
			 */
			template< typename U >
			[[nodiscard]]
			bool operator==(const Allocator< U >& rhs) const noexcept {
				return m_memory_arena == rhs.m_memory_arena;
			}

			/**
			 Compares this allocator to the given allocator for non-equality.

			 @tparam		U
							The data type.
			 @param[in]		rhs
							A reference to the allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							allocator cannot be deallocated from the given
							allocator, and vice versa. @c false otherwise.
			 */
			template< typename U >
			[[nodiscard]]
			bool operator!=(const Allocator< U >& rhs) const noexcept {
				return !(*this == rhs);
			}

		private:

			//-----------------------------------------------------------------
			// Friends
			//-----------------------------------------------------------------

			friend class MemoryArena;

			//-----------------------------------------------------------------
			// Constructors
			//-----------------------------------------------------------------

			/**
			 Constructs an allocator.

			 @param[in]		memory_arena
							A pointer to the memory arena.
			 */
			explicit Allocator(NotNull< MemoryArena* > memory_arena) noexcept
				: m_memory_arena(memory_arena) {}

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			/**
			 A pointer to the memory arena of this allocator.
			 */
			NotNull< MemoryArena* > m_memory_arena;
		};

		/**
		 Returns an allocator for this memory arena.

		 @tparam		T
						The data type of the allocator.
		 @return		An allocator for this memory arena.
		 */
		template< typename T >
		[[nodiscard]]
		Allocator< T > GetAllocator() noexcept{
			return Allocator< T >(this);
		}

	private:

		//---------------------------------------------------------------------
		// Type Aliases
		//---------------------------------------------------------------------

		/**
		 A type definition for a memory block.
		 */
		using MemoryBlock = std::pair< std::size_t, U8* >;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The alignment in bytes of this memory arena.
		 */
		const std::size_t m_alignment;

		/**
		 The maximum block size in bytes of this memory arena.
		 */
		const std::size_t m_maximum_block_size;

		/**
		 The current block of this memory arena.
		 */
		MemoryBlock m_current_block;

		/**
		 The current block position of this memory arena.
		 */
		std::size_t m_current_block_pos;

		/**
		 A collection containing the used blocks of this memory arena.
		 */
		std::list< MemoryBlock > m_used_blocks;

		/**
		 A collection containing the available blocks of this memory arena.
		 */
		std::list< MemoryBlock > m_available_blocks;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory_arena.tpp"

#pragma endregion