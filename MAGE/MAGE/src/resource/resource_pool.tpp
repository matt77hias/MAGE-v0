#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename KeyT, typename ResourceT >
	size_t ResourcePool< KeyT, ResourceT >::GetNumberOfResources() const {
		MutexLock lock(m_resource_map_mutex);
		return m_resource_map.size();
	}

	template< typename KeyT, typename ResourceT >
	template< typename... ConstructorArgsT >
	SharedPtr< ResourceT > ResourcePool< KeyT, ResourceT >::GetResource(KeyT key, ConstructorArgsT&&... args) {
		return GetDerivedResource< ResourceT, ConstructorArgsT... >(key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename KeyT, typename ResourceT >
	template< typename DerivedResourceT, typename... ConstructorArgsT >
	SharedPtr< ResourceT > ResourcePool< KeyT, ResourceT >::GetDerivedResource(KeyT key, ConstructorArgsT&&... args) {
		MutexLock lock(m_resource_map_mutex);

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

		auto new_resource = SharedPtr< ResourcePoolEntry< DerivedResourceT > >(
			new ResourcePoolEntry< DerivedResourceT >(*this, key, std::forward< ConstructorArgsT >(args)...));
		m_resource_map[key] = new_resource;
		return new_resource;
	}

	template< typename KeyT, typename ResourceT >
	void ResourcePool< KeyT, ResourceT >::RemoveResource(KeyT key) {
		MutexLock lock(m_resource_map_mutex);

		auto it = m_resource_map.find(key);
		if (it != m_resource_map.end() && it->second.expired()) {
			m_resource_map.erase(it);
		}
	}

	template< typename KeyT, typename ResourceT >
	void ResourcePool< KeyT, ResourceT >::RemoveAllResources() {
		MutexLock lock(m_resource_map_mutex);

		m_resource_map.clear();
	}
}