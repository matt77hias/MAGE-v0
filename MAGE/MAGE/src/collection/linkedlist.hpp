#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of (doubly) linked lists.

	 @tparam	T
				The type of data stored in the linked list.
	 */
	template< typename T >
	class LinkedList {

	public:

		/**
		 A struct of elements of a {@link mage::LinkedList<T>}.
		*/
		struct LinkedListElement {

		public:

			/**
			 Constructs a linked list element associated with the given data.

			 @param[in]		data
							The data to associate with.
			*/
			LinkedListElement(T *data) : data(data), next(NULL), prev(NULL) {}

			/**
			 Destructs this linked list element.
			 */
			virtual ~LinkedListElement() {
				delete data;

				// Maintain linked list
				if (next) {
					// Let this next element's prev point to this prev
					// prev <--> this <--> next ==> prev <-- next
					next->prev = prev;
				}
				if (prev) {
					// Let this previous element's next point to this prev
					// prev <--> this <--> next ==> prev --> next
					prev->next = next;
				}
			}

			/**
			 Pointer to the data held in this element.
			 */
			T *data;

			/**
			 Pointer to the next element in the linked list.
			 */
			LinkedListElement *next;

			/**
			 Pointer to the previous element in the linked list.
			 */
			LinkedListElement *prev;
		};

		/**
		 A struct of forward iterators for a {@link mage::LinkedList<T>}.
		 */
		struct LinkedListIterator {

		public:

			/**
			 Constructs a linked list iterator starting from the given first element of a linked list.

			 @param[in]		first
							A pointer to the first element of a linked list.
			 */
			LinkedListIterator(LinkedListElement *first) : m_next(first) {}
			
			/**
			 Destructs this linked list iterator.
			 */
			virtual ~LinkedListIterator() {}

			/**
			 Checks whether there is a next element in the linked list 
			 of this linked list iterator.

			 @return		@c true if there is a next element in the linked list 
							of this linked list iterator. 
							@c false otherwise.
			 */
			bool HasNext() const {
				return (m_next != NULL);
			}
			/**
			 Returns a pointer to the data of the next element in the linked list
			 of this linked list iterator.

			 @return		A pointer to the data of the next element in the linked list
							of this linked list iterator.
			 */
			T *Next() {
				if (!HasNext()) {
					return NULL;
				}
				T *result = m_next->data;
				m_next = m_next->next;
				return result;
			}

		private:

			/**
			 Pointer to the next element in the linked list.
			 */
			LinkedListElement *m_next;
		};

		/**
		 Constructs an empty linked list.
		 */
		LinkedList() : m_first(NULL), m_last(NULL), m_size(0) {}

		/**
		 Destructs this linked list.

		 @note			The data associated with the elements in this
						linked list will be destructed as well.
		 */
		virtual ~LinkedList() {
			Empty();
		}

		/**
		 Adds the given data to the end of this linked list.

		 @param[in]		data
						A pointer to the data.
		 @return		A pointer to the data.
		 */
		T *Add(T *data) {
			if (data == NULL) {
				return NULL;
			}

			if (m_first == NULL) {
				m_first = new LinkedListElement(data);
				m_last = m_first;
			}
			else {
				m_last->next = new LinkedListElement(data);
				m_last->next->prev = m_last;
				m_last = m_last->next;
			}

			++m_size;

			return m_last->data;
		}
		
		/**
		 Inserts the given data into this linked list just before 
		 the given element in this linked list.

		 @param[in]		data
						A pointer to the data.
		 @param[in]		next_element		
						A pointer to the next element in this linked list.
		 @return		A pointer to the data.
		 */
		T *InsertBefore(T *data, LinkedListElement *next_element) {
			LinkedListElement *temp = next_element->prev;

			++m_size;

			if (temp == NULL) {
				m_first = new LinkedListElement(data);
				m_first->next = next_element;
				next_element->prev = m_first;
				return m_first->data;
			}
			else {
				temp->next = new LinkedListElement(data);
				temp->next->prev = temp;
				temp->next->next = next_element;
				next_element->prev = temp->next;
				return temp->next->data;
			}
		}
		
		/**
		 Inserts the given data into this linked list just after
		 the given element in this linked list.

		 @param[in]		data
						A pointer to the data.
		 @param[in]		prev_element
						A pointer to the previous element in this linked list.
		 @return		A pointer to the data.
		 */
		T *InsertAfter(T *data, LinkedListElement *prev_element) {
			LinkedListElement *temp = prev_element->next;

			++m_size;

			if (temp == NULL) {
				m_last = new LinkedListElement(data);
				m_last->prev = prev_element;
				prev_element->next = m_last;
				return m_last->data;
			}
			else {
				temp->prev = new LinkedListElement(data);
				temp->prev->next = temp;
				temp->prev->prev = prev_element;
				prev_element->next = temp->prev;
				return temp->prev->data;
			}
		}

		/**
		 Removes the given data from this linked list.

		 @param[in, out]	data
						A pointer to a pointer to the data
						which will point to @c NULL after removal.
		 @param[in]		data_destruction
						if @c true the data will be destructed.
						if @c false the data will not be destructed.
		*/
		void Remove(T **data, bool data_destruction = true) {
			LinkedListElement *temp = m_first;
			while (temp != NULL) {
				if (temp->data == *data) {
					if (temp == m_first) {
						m_first = m_first->next;
						if (m_first)
							m_first->prev = NULL;
					}
					if (temp == m_last) {
						m_last = m_last->prev;
						if (m_last)
							m_last->next = NULL;
					}

					if (!data_destruction) {
						temp->data = NULL;
						delete temp;
					}
					else {
						delete temp;
						*data = NULL;
					}

					m_size--;

					return;
				}
				temp = temp->next;
			}
		}

		/**
		 Destroys all the elements in this linked list.

		 @param[in]		data_destruction
						if @c true the data associated with the
						elements in this linkedlist will be destructed.
						if @c false the data associated with the
						elements in this linkedlist will not be destructed.
		 */
		void Empty(bool data_destruction = true) {
			while (m_last != NULL) {
				LinkedListElement *temp = m_last;
				m_last = m_last->prev;

				if (!data_destruction) {
					temp->data = NULL;
				}
				delete temp;
			}
			m_first = m_last = NULL;
			m_size = 0;
		}

		/**
		 Returns a pointer to the data of the first element in this linked list.

		 @return		@c NULL if this linked list contains no elements.
		 @return		A pointer to the data of the first element in this
						linked list.
		 */
		T *GetFirst() const {
			return (m_first) ? m_first->data : NULL;
		}

		/**
		 Returns a pointer to the data of the last element in this linked list.

		 @return		@c NULL if this linked list contains no elements.
		 @return		A pointer to the data of the last element in this
						linked list.
		 */
		T *GetLast() const {
			return (m_last) ? m_last->data : NULL;
		}

		/**
		 Returns a pointer to the data of the previous element in this linked list
		 from the element corresponding to the given data.

		 @param[in]		data
						A pointer to the data.
		 @return		@c NULL if @a data is associated with the last element
						in this linked list.
		 @return		A pointer to the data of the previous element in this
						linked list from the element corresponding to @a data.
		 */
		T *GetPrevious(T *data) const {
			LinkedListElement *temp = m_last;
			while (temp != NULL) {
				if (temp->data == data) {
					return (temp->prev == NULL) ? NULL : m_temp->prev->data;
				}

				temp = temp->prev;
			}

			return NULL;
		}

		/**
		 Returns a pointer to the data of the next element in this linked list
		 from the element corresponding to the given data.

		 @param[in]		data
						A pointer to the data.
		 @return		@c NULL if @a data is associated with the first element
						in this linked list.
		 @return		A pointer to the data of the next element in this 
						linked list from the element corresponding to @a data.
		 */
		T *GetNext(T *data) const {
			LinkedListElement *temp = m_first;
			while (temp != NULL) {
				if (temp->data == data) {
					return (temp->next == NULL) ? NULL : m_temp->next->data;
				}

				temp = temp->next;
			}

			return NULL;
		}

		/**
		 Returns a pointer to the data of the element in this linked list at the given index.

		 @param[in]		index
						The index of the element.
		 @return		@c NULL if the index is out of bounds.
		 @return		A pointer to the data of the element in this linked list at index @a index.
		 */
		T *GetAt(uint64_t index) const {
			if (index >= m_size) {
				return NULL;
			}

			LinkedListElement *temp = m_first;
			for (uint64_t i = 0; i < index; ++i)
				m_temp = m_temp->next;
			return m_temp->data;
		}
		
		/**
		 Returns a pointer to the data of a random element in this linked list.

		 @return		A pointer to the data of a random element in this linked list.
		 */
		T *GetRandom() const {
			switch (m_size) {
			case 0:
				return NULL;
			case 1:
				return m_first->data;
			default:
				const uint64_t index = rand() * m_size / RAND_MAX;
				return GetAt(index);
			}
		}
		
		/**
		 Returns a forward iterator for this linked list.

		 @return		An iterator for this linked list.			
		 */
		LinkedListIterator GetIterator() const {
			return LinkedListIterator(m_first);
		}

		/**
		 Returns the (complete) element in this linked list associated with the given data.

		 @param[in]		data
						A pointer to the data.
		 @return		@c NULL if no element in this linkedlist
						is associated with the given data.
		 @return		The (complete) element in this linked list 
						associated with @a data.	
		 */
		LinkedListElement *GetCompleteLinkedListElement(T *data) const {
			LinkedListElement *temp = m_first;
			while (temp != NULL) {
				if (temp->data == data) {
					return temp;
				}
				temp = temp->next;
			}
			return NULL;
		}

		/**
		 Returns the size of this linked list.

		 @return		The size of this linked list.
		 */
		uint64_t GetSize() const {
			return m_size;
		}

	private:
		
		/** 
		 Pointer to first element in this linked list.
		 */
		LinkedListElement *m_first;
		
		/** 
		 Pointer to last element in this linked list. 
		 */
		LinkedListElement *m_last;
		
		/** 
		 Total number of elements in this linked list.
		 */
		uint64_t m_size;
	};
}