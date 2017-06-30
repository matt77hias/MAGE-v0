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

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	/**
	 A resource map used by a resource pool.

	 @tparam		KeyT
					The key type.
	 @tparam		ResourceT
					The resource type.
	 */
	template< typename KeyT, typename ResourceT >
	using ResourceMap = map< const KeyT, WeakPtr< ResourceT > >;

	//-------------------------------------------------------------------------
	// ResourcePool
	//-------------------------------------------------------------------------

	/**
	 A class of resource pools.

	 @tparam		KeyT
					The key type.
	 @tparam		ResourceT
					The resource type.
	 */
	template< typename KeyT, typename ResourceT >
	class ResourcePool {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a resource pool.
		 */
		ResourcePool() = default;

		/**
		 Constructs a resource pool from the given resource pool.

		 @param[in]		resource_pool
						A reference to the resource pool to copy.
		 */
		ResourcePool(const ResourcePool &resource_pool) = delete;

		/**
		 Constructs a resource pool by moving the given resource pool.

		 @param[in]		resource_pool
						A reference to the resource pool to move.
		 */
		ResourcePool(ResourcePool &&resource_pool);

		/**
		 Destructs this resource pool.
		 */
		virtual ~ResourcePool();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given resource pool to this resource pool.

		 @param[in]		resource_pool
						A reference to the resource pool to copy.
		 @return		A reference to the copy of the given resource pool
						(i.e. this resource pool).
		 */
		ResourcePool &operator=(const ResourcePool &resource_pool) = delete;

		/**
		 Moves the given resource pool to this resource pool.

		 @param[in]		resource_pool
						A reference to the resource pool to move.
		 @return		A reference to the moved resource pool
						(i.e. this resource pool).
		 */
		ResourcePool &operator=(ResourcePool &&resource_pool) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the number of resources contained in this resource pool.
		 */
		size_t GetNumberOfResources() const;

		/**
		 Returns the resource corresponding to the given key from this resource pool.
		 
		 If no resource is contained in this resource pool corresponding to the given key
		 a new resource is created from the given arguments, added to this resource pool
		 and returned.

		 @tparam		ConstructorArgsT
						The argument types for creating a new resource 
						of type @c ResourceT.
		 @param[in]		key
						A reference to the key of the resource.
		 @param[in]		args
						The arguments for creating a new resource
						of type @c ResourceT.
		 @return		A pointer to the resource corresponding to 
						the given key from this resource pool.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreateResource(const KeyT &key, ConstructorArgsT&&... args);
		
		/**
		 Returns the resource corresponding to the given key from this resource pool.

		 If no resource is contained in this resource pool corresponding to the given key
		 a new resource is created from the given arguments, added to this resource pool
		 and returned.

		 @pre			@c DerivedResourceT is a derived class of @c ResourceT.
		 @tparam		DerivedResourceT
						The derived resource type.
		 @tparam		ConstructorArgsT
						The argument types for creating a new resource
						of type @c DerivedResourceT.
		 @param[in]		key
						A reference to the key of the resource.
		 @param[in]		args
						The arguments for creating a new resource
						of type @c DerivedResourceT.
		 @return		A pointer to the resource corresponding to
						the given key from this resource pool.
		 */
		template< typename DerivedResourceT, typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreateDerivedResource(const KeyT &key, ConstructorArgsT&&... args);
		
		/**
		 Removes the resource corresponding to the given key from this resource pool.

		 @param[in]		key
						A reference to the key of the resource to remove.
		 */
		void RemoveResource(const KeyT &key);

		/**
		 Removes all resources from this resource pool.
		 */
		void RemoveAllResources();
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The resource map of this resource pool.
		 */
		ResourceMap< KeyT, ResourceT > m_resource_map;

		/**
		 The mutex for accessing the resource map of this resource pool.
		 */
		Mutex m_resource_map_mutex;

		/**
		 A class of resource pool entries.

		 @pre			@c DerivedResourceT is a derived class of @c ResourceT.
		 @tparam		DerivedResourceT
						The derived resource type.
		 */
		template< typename DerivedResourceT >
		struct ResourcePoolEntry final : public DerivedResourceT {

		public:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs a resource pool entry.

			 @tparam		ConstructorArgsT
							The argument types for creating a new resource
							of type @c DerivedResourceT.
			 @param[in]		resource_pool
							A reference to the resource pool.
			 @param[in]		resource_key
							A reference to the key of the resource 
							in the given resource pool.
			 @param[in]		args
							The arguments for creating a new resource
							of type @c DerivedResourceT.
			 */
			template< typename... ConstructorArgsT >
			ResourcePoolEntry(ResourcePool< KeyT, ResourceT > &resource_pool,
				const KeyT &resource_key, ConstructorArgsT&&... args);
			
			/**
			 Constructs a resource pool entry from the given resource pool entry.

			 @param[in]		resource
							A reference to the resource pool entry to copy.
			 */
			ResourcePoolEntry(const ResourcePoolEntry &resource) = delete;

			/**
			 Constructs a resource pool entry by moving the given resource poolentry .

			 @param[in]		resource
							A reference to the resource pool entry to move.
			 */
			ResourcePoolEntry(ResourcePoolEntry &&resource);

			/**
			 Destructs this resource pool entry.
			 */
			virtual ~ResourcePoolEntry();

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			/**
			 Copies the given resource pool entry to this resource pool entry.

			 @param[in]		resource
							A reference to the resource pool entry to copy.
			 @return		A reference to the copy of the given resource pool entry
							(i.e. this resource pool entry).
			 */
			ResourcePoolEntry &operator=(const ResourcePoolEntry &resource) = delete;
			
			/**
			 Moves the given resource pool entry to this resource pool entry.

			 @param[in]		resource
							A reference to the resource pool entry to move.
			 @return		A reference to the moved resource pool entry
							(i.e. this resource pool entry).
			 */
			ResourcePoolEntry &operator=(ResourcePoolEntry &&resource) = delete;

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			/**
			 A reference to the resource pool map containing this resource pool entry.
			 */
			ResourcePool< KeyT, ResourceT > &m_resource_pool;

			/**
			 The key of this resource pool entry in the resource pool map containing
			 this resource pool entry.
			 */
			const KeyT m_resource_key;
		};
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.tpp"

#pragma endregion