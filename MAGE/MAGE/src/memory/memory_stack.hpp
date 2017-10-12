#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\types.hpp"

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
	class MemoryStack final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a memory stack with given size.

		 @param[in]		size
						The size in bytes.
		 @param[in]		alignment
						The alignment in bytes.
		 @throws		std::bad_alloc
						Failed to allocate the memory.
		 */
		explicit MemoryStack(size_t size, size_t alignment = 16);

		/**
		 Constructs a memory stack from the given memory stack.

		 @param[in]		stack
						A reference to the memory stack to copy.
		 */
		MemoryStack(const MemoryStack &stack) = delete;

		/**
		 Constructs a memory stack by moving the given memory stack.

		 @param[in]		stack
						A reference to the memory stack to move.
		 */
		MemoryStack(MemoryStack &&stack);
		
		/**
		 Destructs this memory stack.
		 */
		~MemoryStack();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given memory stack to this memory stack.

		 @param[in]		stack
						A reference to the memory stack to copy.
		 @return		A reference to the copy of the given memory stack (i.e. 
						this memory stack).
		 */
		MemoryStack &operator=(const MemoryStack &stack) = delete;

		/**
		 Moves the given memory stack to this memory stack.

		 @param[in]		stack
						A reference to the memory stack to move.
		 @return		A reference to the moved memory stack (i.e. this memory 
						stack).
		 */
		MemoryStack &operator=(MemoryStack &&stack) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the alignment of this memory stack.

		 @return		The alignment in bytes of this memory stack.
		 */
		size_t GetAlignment() const noexcept {
			return m_alignment;
		}

		/**
		 Returns the size (used + available) of this memory stack.

		 @return		The size (used + available) in bytes of this memory 
						stack.
		 */
		size_t GetSize() const noexcept {
			return m_size;
		}

		/**
		 Returns the used size of this memory stack.

		 @return		The used size in bytes of this memory stack.
		 */
		size_t GetUsedSize() const noexcept {
			return m_current - m_begin;
		}

		/**
		 Returns the available size of this memory stack.

		 @return		The available size in bytes of this memory stack.
		 */
		size_t GetAvailableSize() const noexcept {
			return GetSize() - GetUsedSize();
		}

		/**
		 Returns a pointer to the current position of this memory stack.

		 @return		A pointer to the current position of this memory stack.
		 */
		uintptr_t GetCurrentPtr() const noexcept {
			return m_current;
		}

		/**
		 Resets this memory stack.

		 The pointer to the current position of this memory stack will be reset
		 to the begin position of this memory stack.
		 */
		void Reset() noexcept;

		/**
		 Rolls this memory stack back to the given position.

		 @pre			The given @a ptr must be in the range of this memory
						stack.
		 @param[in]		ptr
						The pointer to the requested position of this memory 
						stack.
		 */
		void RollBack(uintptr_t ptr) noexcept;

		/**
		 Allocates a block of memory of the given size.

		 @param[in]		size
						The requested size in bytes to allocate in memory.
		 @return		@c nullptr if the allocation failed.
		 @return		A pointer to the memory block that was allocated.
		 */
		void *Alloc(size_t size) noexcept;

		/**
		 Allocates a block of memory.

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
			size_t count = 1, bool initialization = true) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The size in bytes of this memory stack.
		 */
		const size_t m_size;

		/**
		 The alignment in bytes of this memory stack.
		 */
		const size_t m_alignment;

		/**
		 A pointer to the begin of this memory stack.
		 */
		uintptr_t m_begin;

		/**
		 A pointer to the current position of this memory stack.
		 */
		uintptr_t m_current;
	};

	/**
	 A class of single-ended memory stacks.
	 */
	using SingleEndedMemoryStack = MemoryStack;

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
			size_t count = 1, bool initialization = true) noexcept;

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
			size_t count = 1, bool initialization = true) noexcept;

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