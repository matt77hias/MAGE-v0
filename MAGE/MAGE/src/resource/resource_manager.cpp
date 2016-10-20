//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "engine.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename T >
	T *ResourceManager< T >::Add(const string &name, const string &path) {
		T *resource;

		// If the element already exists, then return a pointer to it.
		resource = GetResource(name, path);
		if (resource) {
			resource->IncrementResourceReferenceCount();
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

	
	template < typename T >
	void ResourceManager< T >::Remove(T **resource) {
		Assert(*resource);

		// If the resource is no long being used then destroy it.
		if (*resource->DecrementResourceReferenceCount() == 0) {
			m_resources->Remove(resource);
		}
	}

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