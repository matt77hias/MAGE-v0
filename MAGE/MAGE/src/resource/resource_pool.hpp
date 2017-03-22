#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "collection\collection.hpp"
#include "parallel\lock.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename KeyT, typename ResourceT >
	using ResourceMap = map< KeyT, WeakPtr< ResourceT > >;

	template< typename KeyT, typename ResourceT, typename... ConstructorArgsT >
	class ResourcePool {

	public:

		ResourcePool() {
			m_resource_map_mutex = Mutex::Create();
		}
		virtual ~ResourcePool() {
			Mutex::Destroy(m_resource_map_mutex);
		}

		size_t GetNumberOfResources() const;
		SharedPtr< ResourceT > GetResource(KeyT key, ConstructorArgsT... args);
		void RemoveResource(KeyT key);
		
	private:

		ResourcePool(const ResourcePool &resource_pool) = delete;
		ResourcePool &operator=(const ResourcePool &resource_pool) = delete;

		ResourceMap< KeyT, ResourceT > m_resource_map;
		Mutex *m_resource_map_mutex;

		struct DerivedResource final : public ResourceT {

		public:

			DerivedResource(ResourcePool< KeyT, ResourceT, ConstructorArgsT... > &resource_pool,
				KeyT resource_key, ConstructorArgsT... args)
				: ResourceT(args...), m_resource_pool(resource_pool), m_resource_key(resource_key) {}
			virtual ~DerivedResource() {
				m_resource_pool.RemoveResource(m_resource_key);
			}

		private:

			DerivedResource(const DerivedResource &resource) = delete;
			DerivedResource &operator=(const DerivedResource &resource) = delete;

			ResourcePool< KeyT, ResourceT, ConstructorArgsT... > &m_resource_pool;
			KeyT m_resource_key;
		};
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.tpp"

#pragma endregion