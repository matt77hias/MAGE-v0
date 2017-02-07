#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	SharedPtr< T > ResourceManager< T >::AddResource(const wstring &name, const wstring &path) {
		// If the element already exists, then return a pointer to it.
		SharedPtr< T > resource = GetResource(name, path);
		if (resource) {
			return resource;
		}

		// Create the resource, preferably through the application specific
		// function if it is available.
		if (CreateResource) {
			CreateResource(&resource, name, path);
		}
		else {
			resource = new T(name, path);
		}

		// Add the new resource to this resource manager.
		m_resources.push_back(resource);

		// Return a pointer to the added resource.
		return resource;
	}

	template< typename T >
	void ResourceManager< T >::RemoveResource(SharedPtr< T > resource) {
		m_resources.remove(resource);
	}

	template< typename T >
	SharedPtr< T > ResourceManager< T >::GetResource(const wstring &name, const wstring &path) const {
		// Iterate the resources looking for the specified resource.
		for (list< SharedPtr< T > >::iterator it = m_resources.begin(); it != m_resources.end(); ++it) {
			if ((*it)->GetName() == name && (*it)->getPath() == path) {
				return *it;
			}
		}
		// Return nullptr if the resource was not found.
		return nullptr;
	}
}