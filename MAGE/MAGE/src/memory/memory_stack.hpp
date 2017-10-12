#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// MemoryStack
	//-------------------------------------------------------------------------

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
		explicit SingleEndedMemoryStack(size_t size, size_t alignment = 16);

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
		SingleEndedMemoryStack(SingleEndedMemoryStack &&stack);
		
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
		DataT *AllocData(
			size_t count = 1, bool initialization = false) noexcept;

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

			/**
			 The pointer to element of allocators.
			 */
			using pointer =  DataT *;

			/**
			 The reference to element of allocators.
			 */
			using reference = DataT &;

			/**
			 The pointer to constant element of allocators.
			 */
			using const_pointer = const DataT *;

			/**
			 The reference to constant element of allocators.
			 */
			using const_reference = const DataT &;
		
			/**
			 The size type of elements of allocators.
			 */
			using size_type = size_t;

			/**
			 The difference between two pointers to elements of allocators.
			 */
			using difference_type = ptrdiff_t;

			/**
			 A struct of equivalent allocators for other elements.

			 @tparam		DataU
							The data type.
			 */
			template< typename DataU >
			struct rebind final {

			public:

				/**
				 The equivalent allocator for elements of type @c DataU.
				 */
				using other = Allocator< DataU >;

				/**
				 Copies the given allocator to this allocator.

				 @param[in]		allocator
								A reference to the allocator to copy.
				 @return		A reference to the copy of the given aligned 
								allocator (i.e. this allocator).
				 */
				rebind< DataU > &operator=(const rebind< DataU > &r) = delete;

				/**
				 Moves the given allocator to this allocator.

				 @param[in]		allocator
								A reference to the allocator to move.
				 @return		A reference to the moved allocator (i.e. 
								this allocator).
				 */
				rebind< DataU > &operator=(rebind< DataU > &&r) = delete;

			private:

				/**
				 Constructs an allocator.
				 */
				rebind() = delete;

				/**
				 Constructs an allocator from the given allocator.

				 @param[in]		allocator
								A reference to the allocator to copy.
				 */
				rebind(const rebind< DataU > &r) = delete;

				/**
				 Constructs an allocator by moving the given aligned 
				 allocator.

				 @param[in]		allocator
								A reference to the allocator to move.
				 */
				rebind(rebind< DataU > &&r) = delete;

				/**
				 Destructs this allocator.
				 */
				~rebind() = delete;
			};

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs an allocator from the given allocator.

			 @param[in]		allocator
							A reference to the allocator to copy.
			 */
			Allocator(const Allocator< DataT > &allocator) noexcept = default;
		
			/**
			 Constructs an allocator by moving the given allocator.

			 @param[in]		allocator
							A reference to the allocator to move.
			 */
			Allocator(Allocator< DataT > &&allocator) noexcept = default;
		
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
			Allocator< DataT > &operator=(
				const Allocator< DataT > &allocator) noexcept = delete;

			/**
			 Moves the given allocator to this allocator.

			 @param[in]		allocator
							A reference to the allocator to move.
			 @return		A reference to the moved allocator (i.e. this 
							allocator).
			 */
			Allocator< DataT > &operator=(
				Allocator< DataT > &&allocator) noexcept = delete;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			/**
			 Returns the address of the given data.

			 @param[in]		data
							A reference to the data.
			 @return		A pointer to the given data.
			 */
			DataT *address(DataT &data) const noexcept {
				return &data;
			}
		
			/**
			 Returns the address of the given data.

			 @param[in]		data
							A reference to the data.
			 @return		A pointer to the given data.
			 */
			const DataT *address(const DataT &data) const noexcept {
				return &data;
			}

			/**
			 Returns the maximum number of elements, each of member type 
			 @c DataT that could potentially be allocated by a call to member 
			 allocate.
			 */
			size_t max_size() const noexcept {
				return m_memory_stack->GetSize() / sizeof(DataT);
			}

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
							{@link mage::SingleEndedMemoryStack::Allocator<DataT>::deallocate(DataT*,size_t)}. 
							When not equal to @c nullptr, this value 
							may be used as a hint to improve performance by 
							allocating the new block near the one specified. 
							The address of an adjacent element is often a good 
							choice.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			template< typename DataU >
			DataT *allocate(size_t count, const DataU *hint) const {
				UNUSED(hint);
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
			void deallocate(DataT *data, size_t count) const {
				UNUSED(data);
				UNUSED(count);
			}
		
			/**
			 Constructs an element object of type @c DataU on the location 
			 pointed by the given pointer.

			 @tparam		DataU
							The element type.
			 @tparam		ConstructorArgsT
							The constructor argument types of the element 
							object of type @c DataU.
			 @param[in]		data
							The pointer to the location.
			 @param[in]		args
							A reference to the constructor arguments for the 
							constructing the element object of type @c DataU.
			 @note			This does not allocate storage space for the 
							element. It should already be available at @a ptr.
			 */
			template< typename DataU, typename... ConstructorArgsT >
			void construct(DataU *data, ConstructorArgsT&&... args) const {
				new ((void *)data) DataU(std::forward< ConstructorArgsT >(args)...);
			}

			/**
			 Destroys in-place the element pointed by the given pointer.
		
			 @tparam		DataU
							The element type.
			 @param[in]		data
							The pointer to the element.
			 @note			This does not deallocate the storage for the 
							element.
			 */
			template< typename DataU >
			void destroy(DataU *data) const {
				data->~DataU();
			}
	
			/**
			 Compares this allocator to the given allocator for equality.

			 @param[in]		rhs
							A reference to the allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							allocator can be deallocated from the given
							allocator, and vice versa. @c false otherwise.
			 */
			bool operator==(const Allocator< DataT > &rhs) const noexcept {
				return m_memory_stack = rhs.m_memory_stack;
			}

			/**
			 Compares this allocator to the given allocator for non-equality.

			 @param[in]		rhs
							A reference to the allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							allocator cannot be deallocated from the given
							allocator, and vice versa. @c false otherwise.
			 */
			bool operator!=(const Allocator< DataT > &rhs) const noexcept {
				return m_memory_stack != rhs.m_memory_stack;
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
			SingleEndedMemoryStack * const m_memory_stack;
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

	/**
	 A class of single-ended memory stacks.
	 */
	using MemoryStack = SingleEndedMemoryStack;

	//-------------------------------------------------------------------------
	// DoubleEndedMemoryStack
	//-------------------------------------------------------------------------

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
		explicit DoubleEndedMemoryStack(size_t size, size_t alignment = 16);

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
		DoubleEndedMemoryStack(DoubleEndedMemoryStack &&stack);
		
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
		DataT *AllocDataLow(
			size_t count = 1, bool initialization = false) noexcept;

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
		DataT *AllocDataHigh(
			size_t count = 1, bool initialization = false) noexcept;

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

			/**
			 The pointer to element of low allocators.
			 */
			using pointer =  DataT *;

			/**
			 The reference to element of low allocators.
			 */
			using reference = DataT &;

			/**
			 The pointer to constant element of low allocators.
			 */
			using const_pointer = const DataT *;

			/**
			 The reference to constant element of low allocators.
			 */
			using const_reference = const DataT &;
		
			/**
			 The size type of elements of low allocators.
			 */
			using size_type = size_t;

			/**
			 The difference between two pointers to elements of low allocators.
			 */
			using difference_type = ptrdiff_t;

			/**
			 A struct of equivalent low allocators for other elements.

			 @tparam		DataU
							The data type.
			 */
			template< typename DataU >
			struct rebind final {

			public:

				/**
				 The equivalent low allocator for elements of type @c DataU.
				 */
				using other = LowAllocator< DataU >;

				/**
				 Copies the given low allocator to this low allocator.

				 @param[in]		low allocator
								A reference to the low allocator to copy.
				 @return		A reference to the copy of the given aligned 
								low allocator (i.e. this low allocator).
				 */
				rebind< DataU > &operator=(const rebind< DataU > &r) = delete;

				/**
				 Moves the given low allocator to this low allocator.

				 @param[in]		low allocator
								A reference to the low allocator to move.
				 @return		A reference to the moved low allocator (i.e. 
								this low allocator).
				 */
				rebind< DataU > &operator=(rebind< DataU > &&r) = delete;

			private:

				/**
				 Constructs an low allocator.
				 */
				rebind() = delete;

				/**
				 Constructs an low allocator from the given low allocator.

				 @param[in]		low allocator
								A reference to the low allocator to copy.
				 */
				rebind(const rebind< DataU > &r) = delete;

				/**
				 Constructs an low allocator by moving the given aligned 
				 low allocator.

				 @param[in]		low allocator
								A reference to the low allocator to move.
				 */
				rebind(rebind< DataU > &&r) = delete;

				/**
				 Destructs this low allocator.
				 */
				~rebind() = delete;
			};

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs a low allocator from the given low allocator.

			 @param[in]		low_allocator
							A reference to the low allocator to copy.
			 */
			LowAllocator(
				const LowAllocator< DataT > &low_allocator) noexcept = default;
		
			/**
			 Constructs a low allocator by moving the given low allocator.

			 @param[in]		low_allocator
							A reference to the low allocator to move.
			 */
			LowAllocator(
				LowAllocator< DataT > &&low_allocator) noexcept = default;
		
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
			LowAllocator< DataT > &operator=(
				const LowAllocator< DataT > &low_allocator) noexcept = delete;

			/**
			 Moves the given low allocator to this low allocator.

			 @param[in]		low_allocator
							A reference to the low allocator to move.
			 @return		A reference to the moved low allocator (i.e. this 
							low allocator).
			 */
			LowAllocator< DataT > &operator=(
				LowAllocator< DataT > &&low_allocator) noexcept = delete;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			/**
			 Returns the address of the given data.

			 @param[in]		data
							A reference to the data.
			 @return		A pointer to the given data.
			 */
			DataT *address(DataT &data) const noexcept {
				return &data;
			}
		
			/**
			 Returns the address of the given data.

			 @param[in]		data
							A reference to the data.
			 @return		A pointer to the given data.
			 */
			const DataT *address(const DataT &data) const noexcept {
				return &data;
			}

			/**
			 Returns the maximum number of elements, each of member type 
			 @c DataT that could potentially be allocated by a call to member 
			 allocate.
			 */
			size_t max_size() const noexcept {
				return m_memory_stack->GetSize() / sizeof(DataT);
			}

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
							{@link mage::DoubleEndedMemoryStack::LowAllocator<DataT>::deallocate(DataT*,size_t)}. 
							When not equal to @c nullptr, this value 
							may be used as a hint to improve performance by 
							allocating the new block near the one specified. 
							The address of an adjacent element is often a good 
							choice.
			 @return		A pointer to the memory block that was allocated.
			 @throws		std::bad_alloc
							Failed to allocate the memory block.
			 */
			template< typename DataU >
			DataT *allocate(size_t count, const DataU *hint) const {
				UNUSED(hint);
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
			void deallocate(DataT *data, size_t count) const {
				UNUSED(data);
				UNUSED(count);
			}
		
			/**
			 Constructs an element object of type @c DataU on the location 
			 pointed by the given pointer.

			 @tparam		DataU
							The element type.
			 @tparam		ConstructorArgsT
							The constructor argument types of the element 
							object of type @c DataU.
			 @param[in]		data
							The pointer to the location.
			 @param[in]		args
							A reference to the constructor arguments for the 
							constructing the element object of type @c DataU.
			 @note			This does not allocate storage space for the 
							element. It should already be available at @a ptr.
			 */
			template< typename DataU, typename... ConstructorArgsT >
			void construct(DataU *data, ConstructorArgsT&&... args) const {
				new ((void *)data) DataU(std::forward< ConstructorArgsT >(args)...);
			}

			/**
			 Destroys in-place the element pointed by the given pointer.
		
			 @tparam		DataU
							The element type.
			 @param[in]		data
							The pointer to the element.
			 @note			This does not deallocate the storage for the 
							element.
			 */
			template< typename DataU >
			void destroy(DataU *data) const {
				data->~DataU();
			}
	
			/**
			 Compares this low allocator to the given low allocator for 
			 equality.

			 @param[in]		rhs
							A reference to the low allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							low allocator can be deallocated from the given
							low allocator, and vice versa. @c false otherwise.
			 */
			bool operator==(const LowAllocator< DataT > &rhs) const noexcept {
				return m_memory_stack = rhs.m_memory_stack;
			}

			/**
			 Compares this low allocator to the given low allocator for 
			 non-equality.

			 @param[in]		rhs
							A reference to the low allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							low allocator cannot be deallocated from the given
							low allocator, and vice versa. @c false otherwise.
			 */
			bool operator!=(const LowAllocator< DataT > &rhs) const noexcept {
				return m_memory_stack != rhs.m_memory_stack;
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
			DoubleEndedMemoryStack * const m_memory_stack;
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

			/**
			 The pointer to element of high allocators.
			 */
			using pointer =  DataT *;

			/**
			 The reference to element of high allocators.
			 */
			using reference = DataT &;

			/**
			 The pointer to constant element of high allocators.
			 */
			using const_pointer = const DataT *;

			/**
			 The reference to constant element of high allocators.
			 */
			using const_reference = const DataT &;
		
			/**
			 The size type of elements of high allocators.
			 */
			using size_type = size_t;

			/**
			 The difference between two pointers to elements of high 
			 allocators.
			 */
			using difference_type = ptrdiff_t;

			/**
			 A struct of equivalent high allocators for other elements.

			 @tparam		DataU
							The data type.
			 */
			template< typename DataU >
			struct rebind final {

			public:

				/**
				 The equivalent high allocator for elements of type @c DataU.
				 */
				using other = HighAllocator< DataU >;

				/**
				 Copies the given high allocator to this high allocator.

				 @param[in]		high allocator
								A reference to the high allocator to copy.
				 @return		A reference to the copy of the given aligned 
								high allocator (i.e. this high allocator).
				 */
				rebind< DataU > &operator=(const rebind< DataU > &r) = delete;

				/**
				 Moves the given high allocator to this high allocator.

				 @param[in]		high allocator
								A reference to the high allocator to move.
				 @return		A reference to the moved high allocator (i.e. 
								this high allocator).
				 */
				rebind< DataU > &operator=(rebind< DataU > &&r) = delete;

			private:

				/**
				 Constructs an high allocator.
				 */
				rebind() = delete;

				/**
				 Constructs an high allocator from the given high allocator.

				 @param[in]		high allocator
								A reference to the high allocator to copy.
				 */
				rebind(const rebind< DataU > &r) = delete;

				/**
				 Constructs an high allocator by moving the given aligned 
				 high allocator.

				 @param[in]		high allocator
								A reference to the high allocator to move.
				 */
				rebind(rebind< DataU > &&r) = delete;

				/**
				 Destructs this high allocator.
				 */
				~rebind() = delete;
			};

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs a high allocator from the given high allocator.

			 @param[in]		high_allocator
							A reference to the high allocator to copy.
			 */
			HighAllocator(
				const HighAllocator< DataT > &high_allocator) noexcept = default;
		
			/**
			 Constructs a high allocator by moving the given high allocator.

			 @param[in]		high_allocator
							A reference to the high allocator to move.
			 */
			HighAllocator(
				HighAllocator< DataT > &&high_allocator) noexcept = default;
		
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
			HighAllocator< DataT > &operator=(
				const HighAllocator< DataT > &high_allocator) noexcept = delete;

			/**
			 Moves the given high allocator to this high allocator.

			 @param[in]		high_allocator
							A reference to the high allocator to move.
			 @return		A reference to the moved high allocator (i.e. this 
							high allocator).
			 */
			HighAllocator< DataT > &operator=(
				HighAllocator< DataT > &&high_allocator) noexcept = delete;

			//-----------------------------------------------------------------
			// Member Methods
			//-----------------------------------------------------------------

			/**
			 Returns the address of the given data.

			 @param[in]		data
							A reference to the data.
			 @return		A pointer to the given data.
			 */
			DataT *address(DataT &data) const noexcept {
				return &data;
			}
		
			/**
			 Returns the address of the given data.

			 @param[in]		data
							A reference to the data.
			 @return		A pointer to the given data.
			 */
			const DataT *address(const DataT &data) const noexcept {
				return &data;
			}

			/**
			 Returns the maximum number of elements, each of member type 
			 @c DataT that could potentially be allocated by a call to member 
			 allocate.
			 */
			size_t max_size() const noexcept {
				return m_memory_stack->GetSize() / sizeof(DataT);
			}

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
			template< typename DataU >
			DataT *allocate(size_t count, const DataU *hint) const {
				UNUSED(hint);
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
			void deallocate(DataT *data, size_t count) const {
				UNUSED(data);
				UNUSED(count);
			}
		
			/**
			 Constructs an element object of type @c DataU on the location 
			 pointed by the given pointer.

			 @tparam		DataU
							The element type.
			 @tparam		ConstructorArgsT
							The constructor argument types of the element 
							object of type @c DataU.
			 @param[in]		data
							The pointer to the location.
			 @param[in]		args
							A reference to the constructor arguments for the 
							constructing the element object of type @c DataU.
			 @note			This does not allocate storage space for the 
							element. It should already be available at @a ptr.
			 */
			template< typename DataU, typename... ConstructorArgsT >
			void construct(DataU *data, ConstructorArgsT&&... args) const {
				new ((void *)data) DataU(std::forward< ConstructorArgsT >(args)...);
			}

			/**
			 Destroys in-place the element pointed by the given pointer.
		
			 @tparam		DataU
							The element type.
			 @param[in]		data
							The pointer to the element.
			 @note			This does not deallocate the storage for the 
							element.
			 */
			template< typename DataU >
			void destroy(DataU *data) const {
				data->~DataU();
			}
	
			/**
			 Compares this high allocator to the given high allocator for 
			 equality.

			 @param[in]		rhs
							A reference to the high allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							high allocator can be deallocated from the given
							high allocator, and vice versa. @c false otherwise.
			 */
			bool operator==(const HighAllocator< DataT > &rhs) const noexcept {
				return m_memory_stack = rhs.m_memory_stack;
			}

			/**
			 Compares this high allocator to the given high allocator for 
			 non-equality.

			 @param[in]		rhs
							A reference to the high allocator to compare with.
			 @return		@c true if and only if storage allocated from this
							high allocator cannot be deallocated from the given
							high allocator, and vice versa. @c false otherwise.
			 */
			bool operator!=(const HighAllocator< DataT > &rhs) const noexcept {
				return m_memory_stack != rhs.m_memory_stack;
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
			DoubleEndedMemoryStack * const m_memory_stack;
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
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory_stack.tpp"

#pragma endregion