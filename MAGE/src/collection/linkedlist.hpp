#pragma once

//-----------------------------------------------------------------------------
// (Doubly) linked list
//-----------------------------------------------------------------------------
template< typename T > 
class LinkedList {

public:

	//-------------------------------------------------------------------------
	// Element of a linked list
	//-------------------------------------------------------------------------
	struct LinkedListElement {

	public:
		LinkedListElement(T *data) : data(data), next(NULL), prev(NULL) {}

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

		// Pointer to the data held in this element
		T *data;
		// Pointer to the next element in the linked list
		LinkedListElement *next;
		// Pointer to the previous element in the linked list
		LinkedListElement *prev;
	};
	//-------------------------------------------------------------------------

	LinkedList() : m_first(NULL), m_last(NULL),
		m_iterate(NULL), m_size(0) {}

	virtual ~LinkedList() {
		Empty< false >();
	}

	// Adds the given data to the end of this linked list.
	T *Add(T *data) {
		if (data == NULL) {
			return NULL;
		}

		if (m_first == NULL) {
			m_first = new LinkedListElement(data);
			m_last = m_first;
		} 
		else {
			m_last->next = new LinkedListElement(element);
			m_last->next->prev = m_last;
			m_last = m_last->next;
		}

		++m_size;

		return m_last->data;
	}
	// Inserts the given data into this linked list just before next_element.
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
	// Inserts the given data into this linked list just after prev_element.
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
	
	// Removes the given data from this linked list.
	template < typename bool no_data_destruction >
	void Remove(T **data) {
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

				if (no_data_destruction) {
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
	// Destroys all the elements in this linked list.
	template < typename bool no_data_destruction >
	void Empty() {
		while (m_last != NULL) {
			LinkedListElement *temp = m_last;
			m_last = m_last->prev;
			
			if (no_data_destruction) {
				temp->data = NULL;
			}
			delete temp;
		}
		m_first = m_last = m_iterate = NULL;
		m_size = 0;
	}

	// Returns the data of the first element in this linked list.
	T *GetFirst() const {
		return (m_first) ? m_first->data : NULL;
	}
	// Returns the data of the last element in this linked list.
	T *GetLast() const {
		return (m_last) ? m_last->data : NULL;
	}
	// Returns the data of the previous element in this linked list 
	// from the element corresponding to the given data.
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
	// Returns the data of the next element in this linked list 
	// from the element corresponding to the given data.
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
	// Returns the data of the element in this linked list 
	// positioned at the given index.
	T *GetAt(uint64_t index) const {
		if (index >= m_size) {
			return NULL;
		}

		LinkedListElement *temp = m_first;
		for (uint64_t i = 0; i < index; ++i)
			m_temp = m_temp->next;
		return m_temp->data;
	}
	// Returns the data of a random element from this linked list
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
	// Returns the data of the current element in this linked list.
	T *GetCurrent() const {
		return (m_iterate) ? m_iterate->data : NULL;
	}
	// Iterates through the elements in this linked list
	// and returns the data of the current element in this linked list.
	T *Iterate(bool restart = false) const {
		m_iterate = (restart || m_iterate == NULL) ? m_first : m_iterate->next
			return (m_iterate) ? m_iterate->data : NULL;
	}

	// Returns the (complete) element in this linked list
	// corresponding to the given data
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
	
	// Returns the size of this linked list
	uint64_t GetSize() const {
		return m_size;
	}

private:
	// Pointer to first element in this linked list
	LinkedListElement *m_first;
	// Pointer to last element in this linked list
	LinkedListElement *m_last;
	// Pointer used for iterating this linked list
	mutable LinkedListElement *m_iterate;

	// Total number of elements in this linked list
	uint64_t m_size;
};