#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of reference counted objects.
	 */
	class ReferenceCounted {

	public:

		/**
		 Increments the reference count of this reference counted object.

		 @return				The final reference count of this reference counted object.
		 */
		inline uint32_t IncrementReferenceCount() {
			return (uint32_t)AtomicAdd(&m_reference_count, 1);
		}
		
		/**
		 Decrements the reference count of this reference counted object.

		 @return				The final reference count of this reference counted object.
		 */
		inline uint32_t DecrementReferenceCount() {
			return (uint32_t)AtomicAdd(&m_reference_count, -1);
		}

	protected:

		/**
		 Constructs a reference counted object.
		*/
		ReferenceCounted() : m_reference_count(0) {}

	private:
		/**
		 The reference count of this reference counted object.
		 */
		AtomicInt32 m_reference_count;
	};

	/**
	 A class of references.

	 @tparam		T		The type of reference.
	 */
	template < typename T >
	class Reference {

	public:

		/**
		 Constructs a reference for the given pointer.

		 @param[in]		ptr			The pointer.
		 */
		Reference(T *ptr = NULL) : m_ptr(ptr) {
			if (m_ptr) {
				m_ptr->IncrementReferenceCount();
			}
		}
		
		/**
		 Constructs a reference from the given reference.

		 @param[in]		reference	The reference.
		 */
		Reference(const Reference< T > &reference) : m_ptr(reference.m_ptr) {
			if (m_ptr) {
				m_ptr->IncrementReferenceCount();
			}
		}
		
		/**
		 Destructs this reference.
		 */
		virtual ~Reference() {
			if (m_ptr && m_ptr->DecrementReferenceCount() == 0) {
				delete m_ptr;
			}
		}
		
		/**
		 Copies the given pointer into a reference.

		 @param[in]		pointer		The pointer.
		 @return					A reference for @a pointer.
		 */
		Reference &operator=(T *ptr) {
			if (ptr) {
				ptr->IncrementReferenceCount();
			}
			if (m_ptr && (m_ptr->DecrementReferenceCount() == 0)) {
				delete m_ptr;
			}
			m_ptr = ptr;
			return *this;
		}

		/**
		 Copies the given reference into a reference.

		 @param[in]		reference	The reference.
		 @return					A reference for @a reference.
		 */
		Reference &operator=(const Reference< T > &reference) {
			if (reference.m_ptr) {
				reference.m_ptr->IncrementReferenceCount();
			}
			if (m_ptr && (m_ptr->DecrementReferenceCount() == 0)) {
				delete m_ptr;
			}
			m_ptr = reference.m_ptr;
			return *this;
		}

		/**
		 Dereferences this reference.

		 @return					The pointer of this reference.
		 */
		T *operator->() { 
			return m_ptr; 
		}
		
		/**
		 Dereferences this reference.

		 @return					The pointer of this reference.
		 */
		const T *operator->() const { 
			return m_ptr; 
		}
	
		/**
		 Returns the pointer of this reference.

		 @return					The pointer of this reference.
		 */
		const T *GetPtr() const { 
			return m_ptr; 
		}

		/**
		 Checks whether the pointer of this reference does not point to @c NULL.

		 @return					@c true if the pointer of this reference does not
									point to @c NULL.
									@c false otherwise.	
		 */
		operator bool() const { 
			return m_ptr != NULL; 
		}

	private:

		/**
		 The pointer of this reference.
		 */
		T *m_ptr;
	};
}
