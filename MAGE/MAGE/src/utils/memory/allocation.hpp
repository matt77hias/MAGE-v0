#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <malloc.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Allocates memory on a given alignment boundary of the given size.
	 
	 @pre			@a alignment must be an integer power of 2.
	 @param[in]		size
					The requested size in bytes to allocate in memory.
	 @param[in]		alignment
					The alignment in bytes.
	 @return		@c nullptr if the allocation failed.
	 @return		A pointer to the memory block that was allocated. The 
					pointer is a multiple of the given alignment.
	 */
	inline void *AllocAligned(size_t size, size_t alignment) noexcept {
		return _aligned_malloc(size, alignment);
	}

	/**
	 Allocates memory on a given alignment boundary.

	 @tparam		DataT
					The type of objects to allocate in memory.
	 @param[in]		count
					The number of objects of type @c DataT to allocate in 
					memory.
	 @param[in]		alignment
					The alignment in bytes.
	 @return		@c nullptr if the allocation failed.
	 @return		A pointer to the memory block that was allocated. The 
					pointer is a multiple of the given alignment.
	 */
	template < typename DataT >
	inline DataT *AllocAlignedData(size_t count, size_t alignment) noexcept {
		return static_cast< DataT * >(AllocAligned(count * sizeof(DataT), alignment));
	}

	/**
	 Frees a block of memory that was allocated with 
	 {@link mage::AllocAligned(size_t, size_t)} or 
	 {@link mage::AllocAlignedData<DataT>(size_t, size_t)}.
	
	 @param[in]		ptr
					A pointer to the memory block that was allocated.
	 */
	inline void FreeAligned(void *ptr) noexcept {
		if (!ptr) {
			return;
		}

		_aligned_free(ptr);
	}

	/**
	 A struct of aligned allocators.

	 @tparam		DataT
					The data type.
	 @tparam		AlignmentS
					The alignment size in bytes.
	 */
	template< typename DataT, size_t AlignmentS = __alignof(DataT) >
	struct AlignedAllocator final {
		
	public:

		//---------------------------------------------------------------------
		// Type Declarations and Definitions
		//---------------------------------------------------------------------

		/**
		 The element type of aligned allocators.
		 */
		using value_type = DataT;

		/**
		 The pointer to element of aligned allocators.
		 */
		using pointer =  DataT *;

		/**
		 The reference to element of aligned allocators.
		 */
		using reference = DataT &;

		/**
		 The pointer to constant element of aligned allocators.
		 */
		using const_pointer = const DataT *;

		/**
		 The reference to constant element of aligned allocators.
		 */
		using const_reference = const DataT &;
		
		/**
		 The size type of elements of aligned allocators.
		 */
		using size_type = size_t;

		/**
		 The difference between two pointers to elements of aligned allocators.
		 */
		using difference_type = ptrdiff_t;

		/**
		 A struct of equivalent aligned allocators for other elements with the 
		 same alignment.

		 @tparam		DataU
						The data type.
		 */
		template< typename DataU >
		struct rebind final {

		public:

			/**
			 The equivalent aligned allocator for elements of type @c DataU with 
			 the same alignment as the aligned allocator for elements of type 
			 @c DataT.
			 */
			using other = AlignedAllocator< DataU, AlignmentS >;

			/**
			 Copies the given aligned allocator to this aligned allocator.

			 @param[in]		r
							A reference to the aligned allocator to copy.
			 @return		A reference to the copy of the given aligned 
							allocator (i.e. this aligned allocator).
			 */
			rebind &operator=(const rebind &r) = delete;

			/**
			 Moves the given aligned allocator to this aligned allocator.

			 @param[in]		r
							A reference to the aligned allocator to move.
			 @return		A reference to the moved aligned allocator (i.e. 
							this aligned allocator).
			 */
			rebind &operator=(rebind &&r) = delete;

		private:

			/**
			 Constructs an aligned allocator.
			 */
			rebind() = delete;

			/**
			 Constructs an aligned allocator from the given aligned allocator.

			 @param[in]		r
							A reference to the aligned allocator to copy.
			 */
			rebind(const rebind &r) = delete;

			/**
			 Constructs an aligned allocator by moving the given aligned 
			 allocator.

			 @param[in]		r
							A reference to the aligned allocator to move.
			 */
			rebind(rebind &&r) = delete;

			/**
			 Destructs this aligned allocator.
			 */
			~rebind() = delete;
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an aligned allocator.
		 */
		AlignedAllocator() noexcept = default;
		
		/**
		 Constructs an aligned allocator from the given aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to copy.
		 */
		AlignedAllocator(const AlignedAllocator &allocator) noexcept = default;
		
		/**
		 Constructs an aligned allocator by moving the given aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to move.
		 */
		AlignedAllocator(AlignedAllocator &&allocator) noexcept = default;
		
		/**
		 Constructs an aligned allocator from the given aligned allocator.

		 @tparam		DataU
						The data type.
		 @param[in]		allocator
						A reference to the aligned allocator to copy.
		 */
		template< typename DataU >
		AlignedAllocator(
			const AlignedAllocator< DataU, AlignmentS > &allocator) noexcept {}
		
		/**
		 Destructs this aligned allocator.
		 */
		~AlignedAllocator() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given aligned allocator to this aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to copy.
		 @return		A reference to the copy of the given aligned allocator 
						(i.e. this aligned allocator).
		 */
		AlignedAllocator &operator=(
			const AlignedAllocator &allocator) noexcept = delete;

		/**
		 Moves the given aligned allocator to this aligned allocator.

		 @param[in]		allocator
						A reference to the aligned allocator to move.
		 @return		A reference to the moved aligned allocator (i.e. this 
						aligned allocator).
		 */
		AlignedAllocator &operator=(
			AlignedAllocator &&allocator) noexcept = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

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
		 Returns the maximum number of elements, each of member type @c DataT 
		 that could potentially be allocated by a call to member allocate.
		 */
		size_t max_size() const noexcept {
			return (static_cast< size_t >(0) - static_cast< size_t >(1)) 
				/ sizeof(DataT);
		}

		/**
		 Attempts to allocate a block of storage with a size large enough to 
		 contain @a count elements of type @c DataT, and returns a pointer to 
		 the first element.

		 @param[in]		count
						The number of element objects of type @c DataT to 
						allocate in memory.
		 @return		A pointer to the memory block that was allocated. The 
						pointer is a multiple of the alignment @c AlignmentS.
		 @throws		std::bad_alloc
						Failed to allocate the memory block.
		 */
		DataT *allocate(size_t count) const {
			DataT * const data = AllocAlignedData(count, AlignmentS);
			if (!data) {
				throw std::bad_alloc();
			}

			return data;
		}

		/**
		 Attempts to allocate a block of storage with a size large enough to 
		 contain @a count elements of type @c DataT, and returns a pointer to 
		 the first element.

		 @param[in]		count
						The number of element objects of type @c DataT to 
						allocate in memory.
		 @param[in]		hint
						Either @c nullptr or a value previously obtained by 
						another call to 
						{@link mage::AlignedAllocator<DataT,size_t>::allocate(size_t)}
						or
						{@link mage::AlignedAllocator<DataT,size_t>::allocate<DataU>(size_t, const DataU*)} 
						and not yet freed with 
						{@link mage::AlignedAllocator<DataT,size_t>::deallocate(DataT*, size_t)}. 
						When not equal to @c nullptr, this value 
						may be used as a hint to improve performance by 
						allocating the new block near the one specified. 
						The address of an adjacent element is often a good 
						choice.
		 @return		A pointer to the memory block that was allocated. The 
						pointer is a multiple of the alignment @c AlignmentS.
		 @throws		std::bad_alloc
						Failed to allocate the memory block.
		 */
		template< typename DataU >
		DataT *allocate(size_t count, const DataU *hint) const {
			(void)hint;
			return allocate(count);
		}

		/**
		 Releases a block of storage previously allocated with 
		 {@link mage::AlignedAllocator<DataT,size_t>::allocate(size_t)}
		 or 
		 {@link mage::AlignedAllocator<DataT,size_t>::allocate<DataU>(size_t, const DataU*)}
		 and not yet released. 
		 
		 @param[in]		data
						A pointer to the memory block that needs to be 
						released.
		 @param[in]		count
						The number of element objects allocated on the call to 
						allocate for this block of storage.
		 @note			The elements in the array are not destroyed.
		 */
		void deallocate(DataT *data, size_t count) const {
			(void)count;
			FreeAligned((void *)data);
		}
		
		/**
		 Constructs an element object of type @c DataU on the location pointed 
		 by the given pointer.

		 @tparam		DataU
						The element type.
		 @tparam		ConstructorArgsT
						The constructor argument types of the element object of
						type @c DataU.
		 @param[in]		data
						The pointer to the location.
		 @param[in]		args
						A reference to the constructor arguments for the 
						constructing the element object of type @c DataU.
		 @note			This does not allocate storage space for the element. It 
						should already be available at @a ptr.
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
		 @note			This does not deallocate the storage for the element.
		 */
		template< typename DataU >
		void destroy(DataU *data) const {
			data->~DataU();
		}
	
		/**
		 Compares this aligned allocator to the given aligned allocator for 
		 equality.

		 @param[in]		rhs
						A reference to the aligned allocator to compare with.
		 @return		@c true if and only if storage allocated from this
						aligned allocator can be deallocated from the given
						aligned allocator, and vice versa. This is always the
						case for stateless allocators. @c false otherwise.
		 */
		bool operator==(const AlignedAllocator &rhs) const noexcept {
			return true;
		}

		/**
		 Compares this aligned allocator to the given aligned allocator for 
		 non-equality.

		 @param[in]		rhs
						A reference to the aligned allocator to compare with.
		 @return		@c true if and only if storage allocated from this
						aligned allocator cannot be deallocated from the given
						aligned allocator, and vice versa. This is never the
						case for stateless allocators. @c false otherwise.
		 */
		bool operator!=(const AlignedAllocator &rhs) const noexcept {
			return false;
		}
	};
}