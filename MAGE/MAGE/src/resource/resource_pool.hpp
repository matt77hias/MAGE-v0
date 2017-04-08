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

	template< typename KeyT, typename ResourceT >
	class ResourcePool {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ResourcePool() = default;
		ResourcePool(const ResourcePool &resource_pool) = delete;
		ResourcePool(ResourcePool &&resource_pool) = default;
		virtual ~ResourcePool() {
			RemoveAllResources();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		ResourcePool &operator=(const ResourcePool &resource_pool) = delete;
		ResourcePool &operator=(ResourcePool &&resource_pool) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		size_t GetNumberOfResources() const;

		template< typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetResource(KeyT key, ConstructorArgsT&&... args);
		template< typename DerivedResourceT, typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetDerivedResource(KeyT key, ConstructorArgsT&&... args);
		
		void RemoveResource(KeyT key);
		void RemoveAllResources();
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ResourceMap< KeyT, ResourceT > m_resource_map;
		Mutex m_resource_map_mutex;

		template< typename DerivedResourceT >
		struct ResourcePoolEntry final : public DerivedResourceT {

		public:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			template< typename... ConstructorArgsT >
			ResourcePoolEntry(ResourcePool< KeyT, ResourceT > &resource_pool,
				KeyT resource_key, ConstructorArgsT&&... args)
				: DerivedResourceT(std::forward< ConstructorArgsT >(args)...), 
				m_resource_pool(resource_pool), m_resource_key(resource_key) {}
			ResourcePoolEntry(const ResourcePoolEntry &resource) = delete;
			ResourcePoolEntry(ResourcePoolEntry &&resource) = delete;

			virtual ~ResourcePoolEntry() {
				m_resource_pool.RemoveResource(m_resource_key);
			}

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			ResourcePoolEntry &operator=(const ResourcePoolEntry &resource) = delete;
			ResourcePoolEntry &operator=(ResourcePoolEntry &&resource) = delete;

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			ResourcePool< KeyT, ResourceT > &m_resource_pool;
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