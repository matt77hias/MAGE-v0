#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

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
	using ResourceMap = map< KeyT, WeakPtr< ResourceT > >;

	/**
	 A persistent resource map used by a persistent resource pool.

	 @tparam		KeyT
					The key type.
	 @tparam		ResourceT
					The resource type.
	 */
	template< typename KeyT, typename ResourceT >
	using PersistentResourceMap = map< KeyT, SharedPtr< ResourceT > >;

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
		ResourcePool(const ResourcePool< KeyT, ResourceT > &resource_pool) = delete;

		/**
		 Constructs a resource pool by moving the given resource pool.

		 @param[in]		resource_pool
						A reference to the resource pool to move.
		 */
		ResourcePool(ResourcePool< KeyT, ResourceT > &&resource_pool);

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
		ResourcePool< KeyT, ResourceT > &operator=(
			const ResourcePool< KeyT, ResourceT > &resource_pool) = delete;

		/**
		 Moves the given resource pool to this resource pool.

		 @param[in]		resource_pool
						A reference to the resource pool to move.
		 @return		A reference to the moved resource pool
						(i.e. this resource pool).
		 */
		ResourcePool< KeyT, ResourceT > &operator=(
			ResourcePool< KeyT, ResourceT > &&resource_pool) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the number of resources contained in this resource pool.
		 */
		size_t GetNumberOfResources() const;

		/**
		 Checks whether this resource pool contains a resource corresponding 
		 to the given key from this resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c true, if a resource is contained in
						this resource pool corresponding to the given key.
						@c false, otherwise.
		 */
		bool HasResource(const KeyT &key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c nullptr, if no resource is contained in 
						this resource pool corresponding to the given key.
		 @return		A pointer to the resource corresponding to
						the given key from this resource pool.
		 */
		SharedPtr< ResourceT > GetResource(const KeyT &key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this resource pool.
		 
		 If no resource is contained in this resource pool corresponding to the given key,
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

		 If no resource is contained in this resource pool corresponding to the given key,
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
		 A class of resources.

		 @pre			@c DerivedResourceT is a derived class of @c ResourceT.
		 @tparam		DerivedResourceT
						The derived resource type.
		 */
		template< typename DerivedResourceT >
		struct Resource final : public DerivedResourceT {

		public:

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs a resource.

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
			Resource(ResourcePool< KeyT, ResourceT > &resource_pool,
				const KeyT &resource_key, ConstructorArgsT&&... args);
			
			/**
			 Constructs a resource from the given resource.

			 @param[in]		resource
							A reference to the resource to copy.
			 */
			Resource(const Resource< DerivedResourceT > &resource) = delete;

			/**
			 Constructs a resource by moving the given resource poolentry .

			 @param[in]		resource
							A reference to the resource to move.
			 */
			Resource(Resource< DerivedResourceT > &&resource);

			/**
			 Destructs this resource.
			 */
			virtual ~Resource();

			//-----------------------------------------------------------------
			// Assignment Operators
			//-----------------------------------------------------------------

			/**
			 Copies the given resource to this resource.

			 @param[in]		resource
							A reference to the resource to copy.
			 @return		A reference to the copy of the given resource
							(i.e. this resource).
			 */
			Resource< DerivedResourceT > &operator=(
				const Resource< DerivedResourceT > &resource) = delete;
			
			/**
			 Moves the given resource to this resource.

			 @param[in]		resource
							A reference to the resource to move.
			 @return		A reference to the moved resource
							(i.e. this resource).
			 */
			Resource< DerivedResourceT > &operator=(
				Resource< DerivedResourceT > &&resource) = delete;

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			/**
			 A reference to the resource pool map containing this resource.
			 */
			ResourcePool< KeyT, ResourceT > &m_resource_pool;

			/**
			 The key of this resource in the resource pool map containing
			 this resource.
			 */
			const KeyT m_resource_key;
		};
	};

	//-------------------------------------------------------------------------
	// PersistentResourcePool
	//-------------------------------------------------------------------------

	/**
	 A class of persistent resource pools.

	 @tparam		KeyT
					The key type.
	 @tparam		ResourceT
					The resource type.
	 */
	template< typename KeyT, typename ResourceT >
	class PersistentResourcePool {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a persistent resource pool.
		 */
		PersistentResourcePool() = default;

		/**
		 Constructs a persistent resource pool from the given persistent resource pool.

		 @param[in]		resource_pool
						A reference to the persistent resource pool to copy.
		 */
		PersistentResourcePool(const PersistentResourcePool< KeyT, ResourceT > &resource_pool) = delete;

		/**
		 Constructs a persistent resource pool by moving the given persistent resource pool.

		 @param[in]		resource_pool
						A reference to the persistent resource pool to move.
		 */
		PersistentResourcePool(PersistentResourcePool< KeyT, ResourceT > &&resource_pool);

		/**
		 Destructs this persistent resource pool.
		 */
		virtual ~PersistentResourcePool();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given persistent resource pool to this persistent resource pool.

		 @param[in]		resource_pool
						A reference to the persistent resource pool to copy.
		 @return		A reference to the copy of the given persistent resource pool
						(i.e. this persistent resource pool).
		 */
		PersistentResourcePool< KeyT, ResourceT > &operator=(
			const PersistentResourcePool< KeyT, ResourceT > &resource_pool) = delete;

		/**
		 Moves the given persistent resource pool to this persistent resource pool.

		 @param[in]		resource_pool
						A reference to the persistent resource pool to move.
		 @return		A reference to the moved persistent resource pool
						(i.e. this persistent resource pool).
		 */
		PersistentResourcePool< KeyT, ResourceT > &operator=(
			PersistentResourcePool< KeyT, ResourceT > &&resource_pool) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the number of resources contained in this persistent resource pool.
		 */
		size_t GetNumberOfResources() const;

		/**
		 Checks whether this persistent resource pool contains a resource corresponding 
		 to the given key from this persistent resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c true, if a resource is contained in
						this persistent resource pool corresponding to the given key.
						@c false, otherwise.
		 */
		bool HasResource(const KeyT &key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this persistent resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c nullptr, if no resource is contained in 
						this persistent resource pool corresponding to the given key.
		 @return		A pointer to the resource corresponding to
						the given key from this persistent resource pool.
		 */
		SharedPtr< ResourceT > GetResource(const KeyT &key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this persistent resource pool.
		 
		 If no resource is contained in this persistent resource pool corresponding to the given key,
		 a new resource is created from the given arguments, added to this persistent resource pool
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
						the given key from this persistent resource pool.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreateResource(const KeyT &key, ConstructorArgsT&&... args);
		
		/**
		 Returns the resource corresponding to the given key from this persistent resource pool.

		 If no resource is contained in this persistent resource pool corresponding to the given key,
		 a new resource is created from the given arguments, added to this persistent resource pool
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
						the given key from this persistent resource pool.
		 */
		template< typename DerivedResourceT, typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreateDerivedResource(const KeyT &key, ConstructorArgsT&&... args);
		
		/**
		 Removes the resource corresponding to the given key from this persistent resource pool.

		 @param[in]		key
						A reference to the key of the resource to remove.
		 */
		void RemoveResource(const KeyT &key);

		/**
		 Removes all resources from this persistent resource pool.
		 */
		void RemoveAllResources();
		
	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The persistent resource map of this persistent resource pool.
		 */
		PersistentResourceMap< KeyT, ResourceT > m_resource_map;

		/**
		 The mutex for accessing the persistent resource map of this persistent resource pool.
		 */
		Mutex m_resource_map_mutex;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.tpp"

#pragma endregion