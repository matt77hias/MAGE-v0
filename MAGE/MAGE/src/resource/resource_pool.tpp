#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename KeyT, typename ResourceT, typename... ConstructorArgsT >
	size_t ResourcePool< KeyT, ResourceT, ConstructorArgsT... >::GetNumberOfResources() const {
		MutexLock lock(*m_mutex);

		return m_resource_map.size();
	}

	template< typename KeyT, typename ResourceT, typename... ConstructorArgsT >
	SharedPtr< ResourceT > ResourcePool< KeyT, ResourceT, ConstructorArgsT... >::GetResource(KeyT key, ConstructorArgsT... args) {
		MutexLock lock(*m_mutex);

		auto it = m_resource_map.find(key);
		if (it != m_resource_map.end()) {
			auto resource = it->second.lock();
			if (resource) {
				return resource;
			}
			else {
				m_resource_map.erase(it);
			}
		}

		auto new_resource = SharedPtr< DerivedResource >(new DerivedResource(m_resource_map, key, args...));
		m_resource_map[key] = new_resource;
		return new_resource;
	}

	template< typename KeyT, typename ResourceT, typename... ConstructorArgsT >
	void ResourcePool< KeyT, ResourceT, ConstructorArgsT... >::RemoveResource(KeyT key) {
		MutexLock lock(*m_mutex);

		auto it = m_resource_map.find(key);
		if (it != m_resource_map.end() && it->second.expired()) {
			m_resource_map.erase(it);
		}
	}
}