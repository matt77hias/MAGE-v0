#pragma once

#include "parallel/atomic.hpp"

//-------------------------------------------------------------------------
// ReferenceCounted
//-------------------------------------------------------------------------
class ReferenceCounted {

public:
	ReferenceCounted() : m_reference_count(0) {}

	AtomicInt32 m_reference_count;
};


//-------------------------------------------------------------------------
// Reference
//-------------------------------------------------------------------------
template <typename T> 
class Reference {

public:
	Reference(T *ptr = NULL) : m_ptr(ptr) {
		if (m_ptr) {
			AtomicAdd(&m_ptr->m_reference_count, 1);
		}
	}
	Reference(const Reference<T> &reference) : m_ptr(reference.m_ptr) {
		if (m_ptr) {
			AtomicAdd(&m_ptr->m_reference_count, 1);
		}
	}
	virtual ~Reference() {
		if (m_ptr && AtomicAdd(&m_ptr->m_reference_count, -1) == 0) {
			delete m_ptr;
		}
	}
	Reference &operator=(T *ptr) {
		if (ptr) {
			AtomicAdd(&ptr->m_reference_count, 1);
		}
		if (m_ptr && AtomicAdd(&m_ptr->m_reference_count, -1) == 0) {
			delete m_ptr;
		}
		m_ptr = ptr;
		return *this;
	}
	Reference &operator=(const Reference<T> &reference) {
		if (reference.m_ptr) {
			AtomicAdd(&ptr->m_reference_count, 1);
		}
		if (m_ptr && AtomicAdd(&m_ptr->m_reference_count, -1) == 0) {
			delete m_ptr;
		}
		m_ptr = reference.m_ptr;
		return *this;
	}
	
	T *operator->() { return m_ptr; }
	const T *operator->() const { return m_ptr; }
	const T *GetPtr() const { return m_ptr; }
	
	operator bool() const { return m_ptr != NULL; }
	
private:
	T *m_ptr;
};
