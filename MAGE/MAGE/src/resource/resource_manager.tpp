#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename T >
	void ResourceManager< T >::AddResource(SharedPtr< T > resource) {
		if (!resource) {
			return;
		}
		const wstring &guid = resource->GetGuid();
		m_resources[guid] = resource;
	}

	template< typename T >
	void ResourceManager< T >::RemoveResource(const wstring &guid) {
		const map< wstring, SharedPtr< T > >::const_iterator it = m_resources.find(guid);
		if (it != m_resources.cend()) {
			m_resources.erase(it);
		}
	}

	template< typename T >
	void ResourceManager< T >::RemoveResource(SharedPtr< T > resource) {
		if (!resource) {
			return;
		}
		RemoveResource(resource.GetGuid());
	}

	template< typename T >
	void ResourceManager< T >::RemoveAllResources() {
		m.resources.clear();
	}

	template< typename T >
	SharedPtr< T > ResourceManager< T >::GetResource(const wstring &guid) const {
		const map< wstring, SharedPtr< T > >::const_iterator it = m_resources.find(guid);
		if (it != m_resources.cend()) {
			return it->second;
		}

		// Return nullptr if the resource was not found.
		return nullptr;
	}
}