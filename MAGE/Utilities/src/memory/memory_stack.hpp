#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// SingleEndedMemoryStack
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of single-ended memory stacks.
	 */
	class SingleEndedMemoryStack final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a single-ended memory stack with given size.

		 @param[in]		size
						The size in bytes.
		 @param[in]		alignment
						The alignment in bytes.
		 @throws		std::bad_alloc
						Failed to allocate the memory.
		 */
		explicit SingleEndedMemoryStack(size_t size, size_t alignment);

		/**
		 Constructs a single-ended memory stack from the given single-ended 
		 memory stack.

		 @param[in]		stack
						A reference to the single-ended memory stack to copy.
		 */
		SingleEndedMemoryStack(const SingleEndedMemoryStack &stack) = delete;

		/**
		 Constructs a single-ended memory stack by moving the given 
		 single-ended memory stack.

		 @param[in]		stack
						A reference to the single-ended memory stack to move.
		 */
		SingleEndedMemoryStack(SingleEndedMemoryStack &&stack) noexcept;
		
		/**
		 Destructs this single-ended memory stack.
		 */
		~SingleEndedMemoryStack();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given single-ended memory stack to this single-ended memory 
		 stack.

		 @param[in]		stack
						A reference to the single-ended memory stack to copy.
		 @return		A reference to the copy of the given single-ended memory 
						stack (i.e. this single-ended memory stack).
		 */
		SingleEndedMemoryStack &operator=(
			const SingleEndedMemoryStack &stack) = delete;

		/**
		 Moves the given single-ended memory stack to this single-ended memory 
		 stack.

		 @param[in]		stack
						A reference to the single-ended memory stack to move.
		 @return		A reference to the moved single-ended memory stack 
						(i.e. this single-ended memory stack).
		 */
		SingleEndedMemoryStack &operator=(
			SingleEndedMemoryStack &&stack) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the alignment of this single-ended memory stack.

		 @return		The alignment in bytes of this single-ended memory 
						stack.
		 */
		size_t GetAlignment() const noexcept {
			return m_alignment;
		}

		/**
		 Returns the size (used + available) of this single-ended memory stack.

		 @return		The size (used + available) in bytes of this 
						single-ended memory stack.
		 */
		size_t GetSize() const noexcept {
			return m_size;
		}

		/**
		 Returns the used size of this single-ended memory stack.

		 @return		The used size in bytes of this single-ended memory 
						stack.
		 */
		size_t GetUsedSize() const noexcept {
			return m_current - m_begin;
		}

		/**
		 Returns the available size of this single-ended memory stack.

		 @return		The available size in bytes of this single-ended memory 
						stack.
		 */
		size_t GetAvailableSize() const noexcept {
			return GetSize() - GetUsedSize();
		}

		/**
		 Returns a pointer to the current position of this single-ended memory 
		 stack.

		 @return		A pointer to the current position of this single-ended 
						memory stack.
		 */
		uintptr_t GetCurrentPtr() const noexcept {
			return m_current;
		}

		/**
		 Resets this memory stack.

		 The pointer to the current position of this single-ended memory stack 
		 will be reset to the begin position of this single-ended memory stack.
		 */
		void Reset() noexcept;

		/**
		 Rolls this single-ended memory stack back to the given position.

		 @pre			The given @a ptr must be in the range of this 
						single-ended memory stack.
		 @param[in]		ptr
						The pointer to the requested position of this 
						single-ended memory stack.
		 */
		void RollBack(uintptr_t ptr) noexcept;

		/**
		 Allocates a block of memory of the given size on this single-ended 
		 memory stack.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 */
		void *Alloc(size_t size) noexcept;

		/**
		 Allocates a block of memory on this single-ended memory stack.

		 @tparam		DataT
						The type of objects to allocate in memory.
		 @param[in]		count
						The number of objects of type @c DataT to allocate in 
						memory.
		 @param[in]		initialization
						Flag indicating whether the objects need to be 
						initialized (i.e. the constructor needs to be called).
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 @note			The objects will be constructed with their default 
						empty constructor.
		 */
		template< typename DataT >
		DataT *AllocData(size_t count = 1, 
			             bool initialization = false) noexcept;

		//---------------------------------------------------------------------
		// Allocators
		//---------------------------------------------------------------------

		/**
		 A struct of allocators for single-ended memory stacks.

		 @tparam		DataT
						The data type.
		 */
		template< typename DataT >
		struct Allocator final {
		
		public:

			//-----------------------------------------------------------------
			// Type Declarations and Definitions
			//-----------------------------------------------------------------

			/**
			 The element type of allocators.
			 */
			using value_type = DataT;

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
			Allocator(const Allocator &allocator) noexcept = default;
		
			/**
			 Constructs an allocator by moving the given allocator.

			 @param[in]		allocator
							A reference to the allocator to move.
			 */
			Allocator(Allocator &&allocator) noexcept = default;
		
			/**
			 Constructs an allocator from the given allocator.

			 @tparam		DataU
							The data type.
			 @param[in]		allocator
							A reference to the allocator to copy.
			 */
			template< typename DataU >
			Allocator(const Allocator< DataU > &allocator) noexcept
				: m_memory_stack(allocator.m_memory_stack) {}
		
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
			Allocator &operator=(const Allocator &allocator) = delete;

			/**
			 Moves the given allocator to this allocator.

			 @param[in]		allocator
							A reference to the allocator to move.
			 @return		A reference to the moved allocator (i.e. this 
							allocator).
			 */
			Allocator &operator=(Allocator &&allocator) noexcept = default;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			/**
			 Attempts to allocate a block of storage with a size large enough to 
			 contain @a count elements of type @c DataT, and returns a pointer 
			 to the first element.

			 @param[in]		count
							The number of element objects of type @c DataT to 
							allocate in memory.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			DataT *allocate(size_t count) const {
				DataT * const data = m_memory_stack->AllocData(count);
				if (!data) {
					throw std::bad_alloc();
				}

				return data;
			}

			/**
			 Attempts to allocate a block of storage with a size large enough 
			 to contain @a count elements of type @c DataT, and returns a 
			 pointer to the first element.

			 @param[in]		count
							The number of element objects of type @c DataT to 
							allocate in memory.
			 @param[in]		hint
							Either @c nullptr or a value previously obtained by 
							another call to 
							{@link mage::SingleEndedMemoryStack::Allocator<DataT>::allocate(size_t)}
							or
							{@link mage::SingleEndedMemoryStack::Allocator<DataT>::allocate<DataU>(size_t, const DataU*)} 
							and not yet freed with 
							{@link mage::SingleEndedMemoryStack::Allocator<DataT>::deallocate(DataT*, size_t)}. 
							When not equal to @c nullptr, this value 
							may be used as a hint to improve performance by 
							allocating the new block near the one specified. 
							The address of an adjacent element is often a good 
							choice.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			DataT *allocate(size_t count, 
				[[maybe_unused]] const void *hint) const {

				return allocate(count);
			}

			/**
			 Releases a block of storage previously allocated with 
			 {@link mage::SingleEndedMemoryStack::Allocator<DataT>::allocate(size_t)}
			 or 
			 {@link mage::SingleEndedMemoryStack::Allocator<DataT>::allocate<DataU>(size_t, const DataU*)}
			 and not yet released. 
		 
			 @param[in]		data
							A pointer to the memory block that needs to be 
							released.
			 @param[in]		count
							The number of element objects allocated on the call 
							to allocate for this block of storage.
			 @note			The elements in the array are not destroyed.
			 */
			void deallocate([[maybe_unused]] DataT *data, 
				[[maybe_unused]] size_t count) const noexcept {}
		
			/**
			 Compares this allocator to the given allocator for equality.

			 @tparam		DataU
							The data type.
			 @param[in]		rhs
							A reference to the allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							allocator can be deallocated from the given
							allocator, and vice versa. @c false otherwise.
			 */
			template< typename DataU >
			bool operator==(const Allocator< DataU > &rhs) const noexcept {
				return m_memory_stack == rhs.m_memory_stack;
			}

			/**
			 Compares this allocator to the given allocator for non-equality.

			 @tparam		DataU
							The data type.
			 @param[in]		rhs
							A reference to the allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							allocator cannot be deallocated from the given
							allocator, and vice versa. @c false otherwise.
			 */
			template< typename DataU >
			bool operator!=(const Allocator< DataU > &rhs) const noexcept {
				return !(*this == rhs);
			}

		private:

			//-----------------------------------------------------------------
			// Friends
			//-----------------------------------------------------------------

			friend class SingleEndedMemoryStack;

			//-----------------------------------------------------------------
			// Constructors
			//-----------------------------------------------------------------

			/**
			 Constructs an allocator.

			 @pre			@a memory_stack is not equal to @c nullptr.
			 @param[in]		memory_stack
							A pointer to the memory stack.
			 */
			explicit Allocator(SingleEndedMemoryStack *memory_stack) noexcept
				: m_memory_stack(memory_stack) {
				Assert(m_memory_stack);
			}

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			/**
			 A pointer to the memory stack of this allocator.
			 */
			SingleEndedMemoryStack *m_memory_stack;
		};

		/**
		 Returns an allocator for this single-ended memory stack.

		 @tparam		DataT
						The data type of the allocator.
		 @return		An allocator for this single-ended memory stack.
		 */
		template< typename DataT >
		Allocator< DataT > GetAllocator() const noexcept{
			return Allocator< DataT >(this);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The size in bytes of this single-ended memory stack.
		 */
		const size_t m_size;

		/**
		 The alignment in bytes of this single-ended memory stack.
		 */
		const size_t m_alignment;

		/**
		 A pointer to the begin of this single-ended memory stack.
		 */
		uintptr_t m_begin;

		/**
		 A pointer to the current position of this single-ended memory stack.
		 */
		uintptr_t m_current;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// DoubleEndedMemoryStack
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of double-ended memory stacks.
	 */
	class DoubleEndedMemoryStack final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a double-ended memory stack with given size.

		 @param[in]		size
						The size in bytes.
		 @param[in]		alignment
						The alignment in bytes.
		 @throws		std::bad_alloc
						Failed to allocate the memory.
		 */
		explicit DoubleEndedMemoryStack(size_t size, size_t alignment);

		/**
		 Constructs a double-ended memory stack from the given double-ended 
		 memory stack.

		 @param[in]		stack
						A reference to the double-ended memory stack to copy.
		 */
		DoubleEndedMemoryStack(const DoubleEndedMemoryStack &stack) = delete;

		/**
		 Constructs a double-ended memory stack by moving the given 
		 double-ended memory stack.

		 @param[in]		stack
						A reference to the double-ended memory stack to move.
		 */
		DoubleEndedMemoryStack(DoubleEndedMemoryStack &&stack) noexcept;
		
		/**
		 Destructs this double-ended memory stack.
		 */
		~DoubleEndedMemoryStack();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given double-ended memory stack to this double-ended memory 
		 stack.

		 @param[in]		stack
						A reference to the double-ended memory stack to copy.
		 @return		A reference to the copy of the given double-ended 
						memory stack (i.e. this double-ended memory stack).
		 */
		DoubleEndedMemoryStack &operator=(
			const DoubleEndedMemoryStack &stack) = delete;

		/**
		 Moves the given double-ended memory stack to this double-ended memory 
		 stack.

		 @param[in]		stack
						A reference to the double-ended memory stack to move.
		 @return		A reference to the moved double-ended memory stack 
						(i.e. this memory stack).
		 */
		DoubleEndedMemoryStack &operator=(
			DoubleEndedMemoryStack &&stack) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the alignment of this double-ended memory stack.

		 @return		The alignment in bytes of this double-ended memory 
						stack.
		 */
		size_t GetAlignment() const noexcept {
			return m_alignment;
		}

		/**
		 Returns the size (used + available) of this double-ended memory stack.

		 @return		The size (used + available) in bytes of this memory 
						stack.
		 */
		size_t GetSize() const noexcept {
			return m_size;
		}

		/**
		 Returns the used size of this double-ended memory stack.

		 @return		The used size in bytes of this double-ended memory 
						stack.
		 */
		size_t GetUsedSize() const noexcept {
			return m_size - m_current_high + m_current_low;
		}

		/**
		 Returns the used low size of this double-ended memory stack.

		 @return		The used high size in bytes of this double-ended memory 
						stack.
		 */
		size_t GetUsedLowSize() const noexcept {
			return m_current_low - m_begin;
		}

		/**
		 Returns the used high size of this double-ended memory stack.

		 @return		The used low size in bytes of this double-ended memory 
						stack.
		 */
		size_t GetUsedHighSize() const noexcept {
			return m_begin + m_size - m_current_high;
		}

		/**
		 Returns the available size of this double-ended memory stack.

		 @return		The available size in bytes of this double-ended memory 
						stack.
		 */
		size_t GetAvailableSize() const noexcept {
			return GetSize() - GetUsedSize();
		}

		/**
		 Returns a pointer to the current low position of this double-ended 
		 memory stack.

		 @return		A pointer to the current low position of this 
						double-ended memory stack.
		 */
		uintptr_t GetCurrentLowPtr() const noexcept {
			return m_current_low;
		}

		/**
		 Returns a pointer to the current high position of this double-ended 
		 memory stack.

		 @return		A pointer to the current high position of this 
						double-ended memory stack.
		 */
		uintptr_t GetCurrentHighPtr() const noexcept {
			return m_current_high;
		}

		/**
		 Resets this double-ended memory stack.

		 The pointer to the current low position of this double-ended memory 
		 stack will be reset to the begin position of this double-ended memory 
		 stack. The pointer to the current high position of this double-ended 
		 memory stack will be reset to the end position of this double-ended 
		 memory stack.
		 */
		void Reset() noexcept;

		/**
		 Rolls this double-ended memory stack back to the given low position.

		 @pre			The given @a ptr must be in the range of this memory
						stack.
		 @param[in]		ptr
						The pointer to the requested low position of this 
						memory stack.
		 */
		void RollBackLow(uintptr_t ptr) noexcept;

		/**
		 Rolls this double-ended memory stack back to the given high position.

		 @pre			The given @a ptr must be in the range of this memory
						stack.
		 @param[in]		ptr
						The pointer to the requested high position of this 
						memory stack.
		 */
		void RollBackHigh(uintptr_t ptr) noexcept;

		/**
		 Allocates a block of memory of the given size on the low side of this 
		 memory stack.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 */
		void *AllocLow(size_t size) noexcept;

		/**
		 Allocates a block of memory of the given size on the high side of this 
		 memory stack.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 */
		void *AllocHigh(size_t size) noexcept;

		/**
		 Allocates a block of memory on the low side of this memory stack.

		 @tparam		DataT
						The type of objects to allocate in memory.
		 @param[in]		count
						The number of objects of type @c DataT to allocate in 
						memory.
		 @param[in]		initialization
						Flag indicating whether the objects need to be 
						initialized (i.e. the constructor needs to be called).
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 @note			The objects will be constructed with their default 
						empty constructor.
		 */
		template< typename DataT >
		DataT *AllocDataLow(size_t count = 1, 
			                bool initialization = false) noexcept;

		/**
		 Allocates a block of memory on the high side of this memory stack.

		 @tparam		DataT
						The type of objects to allocate in memory.
		 @param[in]		count
						The number of objects of type @c DataT to allocate in 
						memory.
		 @param[in]		initialization
						Flag indicating whether the objects need to be 
						initialized (i.e. the constructor needs to be called).
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 @note			The objects will be constructed with their default 
						empty constructor.
		 */
		template< typename DataT >
		DataT *AllocDataHigh(size_t count = 1, 
			                 bool initialization = false) noexcept;

		//---------------------------------------------------------------------
		// Allocators
		//---------------------------------------------------------------------

		/**
		 A struct of low allocators for double-ended memory stacks.

		 @tparam		DataT
						The data type.
		 */
		template< typename DataT >
		struct LowAllocator final {
		
		public:

			//-----------------------------------------------------------------
			// Type Declarations and Definitions
			//-----------------------------------------------------------------

			/**
			 The element type of low allocators.
			 */
			using value_type = DataT;

			using propagate_on_container_move_assignment = std::true_type;
			using is_always_equal = std::false_type;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs a low allocator from the given low allocator.

			 @param[in]		low_allocator
							A reference to the low allocator to copy.
			 */
			LowAllocator(const LowAllocator &low_allocator) noexcept = default;
		
			/**
			 Constructs a low allocator by moving the given low allocator.

			 @param[in]		low_allocator
							A reference to the low allocator to move.
			 */
			LowAllocator(LowAllocator &&low_allocator) noexcept = default;
		
			/**
			 Constructs a low allocator from the given low allocator.

			 @tparam		DataU
							The data type.
			 @param[in]		low_allocator
							A reference to the low allocator to copy.
			 */
			template< typename DataU >
			LowAllocator(const LowAllocator< DataU > &low_allocator) noexcept
				: m_memory_stack(low_allocator.m_memory_stack) {}
		
			/**
			 Destructs this low allocator.
			 */
			~LowAllocator() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			/**
			 Copies the given low allocator to this low allocator.

			 @param[in]		low_allocator
							A reference to the low allocator to copy.
			 @return		A reference to the copy of the given low allocator 
							(i.e. this low allocator).
			 */
			LowAllocator &operator=(
				const LowAllocator &low_allocator) = delete;

			/**
			 Moves the given low allocator to this low allocator.

			 @param[in]		low_allocator
							A reference to the low allocator to move.
			 @return		A reference to the moved low allocator (i.e. this 
							low allocator).
			 */
			LowAllocator &operator=(
				LowAllocator &&low_allocator) noexcept = default;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			/**
			 Attempts to allocate a block of storage with a size large enough 
			 to contain @a count elements of type @c DataT, and returns a 
			 pointer to the first element.

			 @param[in]		count
							The number of element objects of type @c DataT to 
							allocate in memory.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			DataT *allocate(size_t count) const {
				DataT * const data = m_memory_stack->AllocDataLow(count);
				if (!data) {
					throw std::bad_alloc();
				}

				return data;
			}

			/**
			 Attempts to allocate a block of storage with a size large enough 
			 to contain @a count elements of type @c DataT, and returns a 
			 pointer to the first element.

			 @param[in]		count
							The number of element objects of type @c DataT to 
							allocate in memory.
			 @param[in]		hint
							Either @c nullptr or a value previously obtained by 
							another call to 
							{@link mage::DoubleEndedMemoryStack::LowAllocator<DataT>::allocate(size_t)}
							or
							{@link mage::DoubleEndedMemoryStack::LowAllocator<DataT>::allocate<DataU>(size_t, const DataU*)} 
							and not yet freed with 
							{@link mage::DoubleEndedMemoryStack::LowAllocator<DataT>::deallocate(DataT*, size_t)}. 
							When not equal to @c nullptr, this value 
							may be used as a hint to improve performance by 
							allocating the new block near the one specified. 
							The address of an adjacent element is often a good 
							choice.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			DataT *allocate(size_t count, 
				[[maybe_unused]] const void *hint) const {

				return allocate(count);
			}

			/**
			 Releases a block of storage previously allocated with 
			 {@link mage::DoubleEndedMemoryStack::LowAllocator<DataT>::allocate(size_t)}
			 or 
			 {@link mage::DoubleEndedMemoryStack::LowAllocator<DataT>::allocate<DataU>(size_t, const DataU*)}
			 and not yet released. 
		 
			 @param[in]		data
							A pointer to the memory block that needs to be 
							released.
			 @param[in]		count
							The number of element objects allocated on the call 
							to allocate for this block of storage.
			 @note			The elements in the array are not destroyed.
			 */
			void deallocate([[maybe_unused]] DataT *data, 
				[[maybe_unused]] size_t count) const noexcept {}
		
			/**
			 Compares this low allocator to the given low allocator for 
			 equality.

			 @tparam		DataU
							The data type.
			 @param[in]		rhs
							A reference to the low allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							low allocator can be deallocated from the given
							low allocator, and vice versa. @c false otherwise.
			 */
			template< typename DataU >
			bool operator==(const LowAllocator< DataU > &rhs) const noexcept {
				return m_memory_stack == rhs.m_memory_stack;
			}

			/**
			 Compares this low allocator to the given low allocator for 
			 non-equality.

			 @tparam		DataU
							The data type.
			 @param[in]		rhs
							A reference to the low allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							low allocator cannot be deallocated from the given
							low allocator, and vice versa. @c false otherwise.
			 */
			template< typename DataU >
			bool operator!=(const LowAllocator< DataU > &rhs) const noexcept {
				return !(*this == rhs);
			}

		private:

			//-----------------------------------------------------------------
			// Friends
			//-----------------------------------------------------------------

			friend class DoubleEndedMemoryStack;

			//-----------------------------------------------------------------
			// Constructors
			//-----------------------------------------------------------------

			/**
			 Constructs a low allocator.

			 @pre			@a memory_stack is not equal to @c nullptr.
			 @param[in]		memory_stack
							A pointer to the memory stack.
			 */
			explicit LowAllocator(DoubleEndedMemoryStack *memory_stack) noexcept
				: m_memory_stack(memory_stack) {
				Assert(m_memory_stack);
			}

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			/**
			 A pointer to the memory stack of this low allocator.
			 */
			DoubleEndedMemoryStack *m_memory_stack;
		};

		/**
		 A struct of high allocators for double-ended memory stacks.

		 @tparam		DataT
						The data type.
		 */
		template< typename DataT >
		struct HighAllocator final {
		
		public:

			//-----------------------------------------------------------------
			// Type Declarations and Definitions
			//-----------------------------------------------------------------

			/**
			 The element type of high allocators.
			 */
			using value_type = DataT;

			using propagate_on_container_move_assignment = std::true_type;
			using is_always_equal = std::false_type;

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs a high allocator from the given high allocator.

			 @param[in]		high_allocator
							A reference to the high allocator to copy.
			 */
			HighAllocator(const HighAllocator &high_allocator) noexcept = default;
		
			/**
			 Constructs a high allocator by moving the given high allocator.

			 @param[in]		high_allocator
							A reference to the high allocator to move.
			 */
			HighAllocator(HighAllocator &&high_allocator) noexcept = default;
		
			/**
			 Constructs a high allocator from the given high allocator.

			 @tparam		DataU
							The data type.
			 @param[in]		high_allocator
							A reference to the high_allocator to copy.
			 */
			template< typename DataU >
			HighAllocator(const HighAllocator< DataU > &high_allocator) noexcept
				: m_memory_stack(high_allocator.m_memory_stack) {}
		
			/**
			 Destructs this high allocator.
			 */
			~HighAllocator() = default;

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			/**
			 Copies the given high allocator to this high allocator.

			 @param[in]		high_allocator
							A reference to the high allocator to copy.
			 @return		A reference to the copy of the given high allocator 
							(i.e. this high allocator).
			 */
			HighAllocator &operator=(
				const HighAllocator &high_allocator) = delete;

			/**
			 Moves the given high allocator to this high allocator.

			 @param[in]		high_allocator
							A reference to the high allocator to move.
			 @return		A reference to the moved high allocator (i.e. this 
							high allocator).
			 */
			HighAllocator &operator=(
				HighAllocator &&high_allocator) noexcept = default;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			/**
			 Attempts to allocate a block of storage with a size large enough to 
			 contain @a count elements of type @c DataT, and returns a pointer 
			 to the first element.

			 @param[in]		count
							The number of element objects of type @c DataT to 
							allocate in memory.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			DataT *allocate(size_t count) const {
				DataT * const data = m_memory_stack->AllocDataHigh(count);
				if (!data) {
					throw std::bad_alloc();
				}

				return data;
			}

			/**
			 Attempts to allocate a block of storage with a size large enough 
			 to contain @a count elements of type @c DataT, and returns a 
			 pointer to  the first element.

			 @param[in]		count
							The number of element objects of type @c DataT to 
							allocate in memory.
			 @param[in]		hint
							Either @c nullptr or a value previously obtained by 
							another call to 
							{@link mage::DoubleEndedMemoryStack::HighAllocator<DataT>::allocate(size_t)}
							or
							{@link mage::DoubleEndedMemoryStack::HighAllocator<DataT>::allocate<DataU>(size_t, const DataU*)} 
							and not yet freed with 
							{@link mage::DoubleEndedMemoryStack::HighAllocator<DataT>::deallocate(DataT*,size_t)}. 
							When not equal to @c nullptr, this value 
							may be used as a hint to improve performance by 
							allocating the new block near the one specified. 
							The address of an adjacent element is often a good 
							choice.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			DataT *allocate(size_t count, 
				[[maybe_unused]] const void *hint) const {

				return allocate(count);
			}

			/**
			 Releases a block of storage previously allocated with 
			 {@link mage::DoubleEndedMemoryStack::HighAllocator<DataT>::allocate(size_t)}
			 or 
			 {@link mage::DoubleEndedMemoryStack::HighAllocator<DataT>::allocate<DataU>(size_t, const DataU*)}
			 and not yet released. 
		 
			 @param[in]		data
							A pointer to the memory block that needs to be 
							released.
			 @param[in]		count
							The number of element objects allocated on the call 
							to allocate for this block of storage.
			 @note			The elements in the array are not destroyed.
			 */
			void deallocate([[maybe_unused]] DataT *data, 
				[[maybe_unused]] size_t count) const noexcept {}
		
			/**
			 Compares this high allocator to the given high allocator for 
			 equality.

			 @tparam		DataU
							The data type.
			 @param[in]		rhs
							A reference to the high allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							high allocator can be deallocated from the given
							high allocator, and vice versa. @c false otherwise.
			 */
			template< typename DataU >
			bool operator==(const HighAllocator< DataU > &rhs) const noexcept {
				return m_memory_stack == rhs.m_memory_stack;
			}

			/**
			 Compares this high allocator to the given high allocator for 
			 non-equality.

			 @tparam		DataU
							The data type.
			 @param[in]		rhs
							A reference to the high allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							high allocator cannot be deallocated from the given
							high allocator, and vice versa. @c false otherwise.
			 */
			template< typename DataU >
			bool operator!=(const HighAllocator< DataU > &rhs) const noexcept {
				return !(*this == rhs);
			}

		private:

			//-----------------------------------------------------------------
			// Friends
			//-----------------------------------------------------------------

			friend class DoubleEndedMemoryStack;

			//-----------------------------------------------------------------
			// Constructors
			//-----------------------------------------------------------------

			/**
			 Constructs a high allocator.

			 @pre			@a memory_stack is not equal to @c nullptr.
			 @param[in]		memory_stack
							A pointer to the memory stack.
			 */
			explicit HighAllocator(DoubleEndedMemoryStack *memory_stack) noexcept
				: m_memory_stack(memory_stack) {
				Assert(m_memory_stack);
			}

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			/**
			 A pointer to the memory stack of this high allocator.
			 */
			DoubleEndedMemoryStack *m_memory_stack;
		};

		/**
		 Returns a low allocator for this single-ended memory stack.

		 @tparam		DataT
						The data type of the allocator.
		 @return		A low allocator for this single-ended memory stack.
		 */
		template< typename DataT >
		LowAllocator< DataT > GetLowAllocator() const noexcept{
			return LowAllocator< DataT >(this);
		}

		/**
		 Returns a high allocator for this single-ended memory stack.

		 @tparam		DataT
						The data type of the allocator.
		 @return		A high allocator for this single-ended memory stack.
		 */
		template< typename DataT >
		HighAllocator< DataT > GetHighAllocator() const noexcept{
			return HighAllocator< DataT >(this);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The size in bytes of this double-ended memory stack.
		 */
		const size_t m_size;

		/**
		 The alignment in bytes of this double-ended memory stack.
		 */
		const size_t m_alignment;

		/**
		 A pointer to the begin of this double-ended memory stack.
		 */
		uintptr_t m_begin;

		/**
		 A pointer to the current low position of this double-ended memory 
		 stack.
		 */
		uintptr_t m_current_low;

		/**
		 A pointer to the current high position of this double-ended memory 
		 stack.
		 */
		uintptr_t m_current_high;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// MemoryStack
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of single-ended memory stacks.
	 */
	using MemoryStack = SingleEndedMemoryStack;

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory_stack.tpp"

#pragma endregion