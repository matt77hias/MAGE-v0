//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "stdafx.h"

namespace mage {

	//-----------------------------------------------------------------------------
	// ResourceManager
	//-----------------------------------------------------------------------------

	// Adds a new resource to this resource manager.
	template < typename T >
	T *ResourceManager< T >::Add(const string &name, const string &path) {
		T *resource;

		// If the element already exists, then return a pointer to it.
		resource = GetResource(name, path);
		if (resource) {
			resource->IncrementResourceCount();
			return resource;
		}

		// Create the resource, preferably through the application specific
		// function if it is available.
		if (CreateResource != NULL) {
			CreateResource(&resource, name, path);
		}
		else {
			resource = new T(name, path);
		}

		// Add the new resource to this resource manager and return a pointer to it.
		return m_resources->Add(resource);
	}

	// Removes the given resource from this resource manager.
	template < typename T >
	void ResourceManager< T >::Remove(T **resource) {
		Assert(*resource);

		// If the resource is no long being used then destroy it.
		if (*resource->DecrementReferenceCount() == 0)
			m_resources->Remove(resource);
	}

	// Returns a resource of this resource manager by its filename (given name and path).
	template < typename T >
	T *ResourceManager< T >::GetResource(const string &name, const string &path) const {
		// Iterate the resources looking for the specified resource.
		const LinkedList< T >::LinkedListIterator it = m_resources->GetIterator();
		while (it.HasNext()) {
			const T *next = it.Next();
			if (next->GetName() == name && next->getPath() == path) {
				return next;
			}
		}
		// Return NULL if the resource was not found.
		return NULL;
	}
}