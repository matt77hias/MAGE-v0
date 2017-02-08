#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "file\file_utils.hpp"

#pragma endregion

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
		m_resources[resource.GetFilename()] = resource;

		// Return a pointer to the added resource.
		return resource;
	}

	template< typename T >
	void ResourceManager< T >::RemoveResource(SharedPtr< T > resource) {
		RemoveResource(resource.GetName(), resource.GetPath());
	}

	template< typename T >
	void ResourceManager< T >::RemoveResource(const wstring &name, const wstring &path) {
		const wstring fname = GetFilename(name, path);
		const map< wstring, SharedPtr< T > >::const_iterator it = m_resources.find(fname);
		if (it != m_resources.cend()) {
			m_resources.erase(it);
		}
	}

	template< typename T >
	void ResourceManager< T >::RemoveAllResources() {
		m.resources.clear();
	}

	template< typename T >
	SharedPtr< T > ResourceManager< T >::GetResource(const wstring &name, const wstring &path) const {
		const wstring fname = GetFilename(name, path);
		const map< wstring, SharedPtr< T > >::iterator it = m_resources.find(fname);
		if (it != m_resources.end()) {
			return it->second;
		}

		// Return nullptr if the resource was not found.
		return nullptr;
	}
}