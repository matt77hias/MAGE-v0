#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>
#include <mutex>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourcePool
	//-------------------------------------------------------------------------
	#pragma region

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
		// Class Member Types
		//---------------------------------------------------------------------

		/**
		 The key type of resource pools.
		 */
		using key_type = KeyT;

		/**
		 The value type of resource pools.
		 */
		using value_type = ResourceT;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a resource pool.
		 */
		ResourcePool() = default;

		/**
		 Constructs a resource pool from the given resource pool.

		 @param[in]		pool
						A reference to the resource pool to copy.
		 */
		ResourcePool(const ResourcePool& pool) = delete;

		/**
		 Constructs a resource pool by moving the given resource pool.

		 @param[in]		pool
						A reference to the resource pool to move.
		 */
		ResourcePool(ResourcePool&& pool) noexcept;

		/**
		 Destructs this resource pool.
		 */
		~ResourcePool() noexcept {
			RemoveAll();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given resource pool to this resource pool.

		 @param[in]		pool
						A reference to the resource pool to copy.
		 @return		A reference to the copy of the given resource pool
						(i.e. this resource pool).
		 */
		ResourcePool& operator=(const ResourcePool& pool) = delete;

		/**
		 Moves the given resource pool to this resource pool.

		 @param[in]		pool
						A reference to the resource pool to move.
		 @return		A reference to the moved resource pool (i.e. this
						resource pool).
		 */
		ResourcePool& operator=(ResourcePool&& pool) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this resource pool is empty.

		 @return		@c true if this resource pool is empty. @c false
						otherwise.
		 */
		[[nodiscard]]
		bool empty() const noexcept;

		/**
		 Returns the number of resources contained in this resource pool.
		 */
		[[nodiscard]]
		std::size_t size() const noexcept;

		/**
		 Checks whether this resource pool contains a resource corresponding
		 to the given key from this resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c true, if a resource is contained in this resource
						pool corresponding to the given key. @c false,
						otherwise.
		 */
		[[nodiscard]]
		bool Contains(const KeyT& key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this
		 resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c nullptr, if no resource is contained in this
						resource pool corresponding to the given key.
		 @return		A pointer to the resource corresponding to the given key
						from this resource pool.
		 */
		[[nodiscard]]
		SharedPtr< ResourceT > Get(const KeyT& key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this resource
		 pool.

		 If no resource is contained in this resource pool corresponding to the
		 given key, a new resource is created from the given arguments, added
		 to this resource pool and returned.

		 @tparam		ConstructorArgsT
						The argument types for creating a new resource of type
						@c ResourceT.
		 @param[in]		key
						A reference to the key of the resource.
		 @param[in]		args
						The arguments for creating a new resource
						of type @c ResourceT.
		 @return		A pointer to the resource corresponding to the given
						key from this resource pool.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreate(const KeyT& key,
			                               ConstructorArgsT&&... args);

		/**
		 Returns the resource corresponding to the given key from this resource
		 pool.

		 If no resource is contained in this resource pool corresponding to the
		 given key, a new resource is created from the given arguments, added
		 to this resource pool and returned.

		 @pre			@c DerivedResourceT is a derived class of @c ResourceT.
		 @tparam		DerivedResourceT
						The derived resource type.
		 @tparam		ConstructorArgsT
						The argument types for creating a new resource of type
						@c DerivedResourceT.
		 @param[in]		key
						A reference to the key of the resource.
		 @param[in]		args
						The arguments for creating a new resource of type
						@c DerivedResourceT.
		 @return		A pointer to the resource corresponding to the given
						key from this resource pool.
		 */
		template< typename DerivedResourceT, typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreateDerived(const KeyT& key,
			                                      ConstructorArgsT&&... args);

		/**
		 Removes the resource corresponding to the given key from this resource
		 pool.

		 @param[in]		key
						A reference to the key of the resource to remove.
		 */
		void Remove(const KeyT& key);

		/**
		 Removes all resources from this resource pool.
		 */
		void RemoveAll() noexcept;

	private:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		/**
		 A resource map used by a resource pool.
		 */
		using ResourceMap = std::map< KeyT, WeakPtr< ResourceT > >;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The resource map of this resource pool.
		 */
		ResourceMap m_resource_map;

		/**
		 The mutex for accessing the resource map of this resource pool.
		 */
		mutable std::mutex m_mutex;

		/**
		 A class of resources.

		 @pre			@c DerivedResourceT is a derived class of @c ResourceT.
		 @tparam		DerivedResourceT
						The derived resource type.
		 */
		template< typename DerivedResourceT >
		class Resource : public DerivedResourceT {

		public:

			static_assert(std::is_base_of_v< ResourceT, DerivedResourceT >);

			//-----------------------------------------------------------------
			// Constructors and Destructors
			//-----------------------------------------------------------------

			/**
			 Constructs a resource.

			 @tparam		ConstructorArgsT
							The argument types for creating a new resource of
							type @c DerivedResourceT.
			 @param[in]		resource_pool
							A reference to the resource pool.
			 @param[in]		resource_key
							A reference to the key of the resource in the
							given resource pool.
			 @param[in]		args
							The arguments for creating a new resource of type
							@c DerivedResourceT.
			 */
			template< typename... ConstructorArgsT >
			Resource(ResourcePool& resource_pool,
				     const KeyT& resource_key,
				     ConstructorArgsT&&... args);

			/**
			 Constructs a resource from the given resource.

			 @param[in]		resource
							A reference to the resource to copy.
			 */
			Resource(const Resource& resource) = delete;

			/**
			 Constructs a resource by moving the given resource poolentry .

			 @param[in]		resource
							A reference to the resource to move.
			 */
			Resource(Resource&& resource);

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
			 @return		A reference to the copy of the given resource (i.e.
							this resource).
			 */
			Resource& operator=(const Resource& resource) = delete;

			/**
			 Moves the given resource to this resource.

			 @param[in]		resource
							A reference to the resource to move.
			 @return		A reference to the moved resource (i.e. this
							resource).
			 */
			Resource& operator=(Resource&& resource) = delete;

		private:

			//-----------------------------------------------------------------
			// Member Variables
			//-----------------------------------------------------------------

			/**
			 A reference to the resource pool map containing this resource.
			 */
			ResourcePool& m_resource_pool;

			/**
			 The key of this resource in the resource pool map containing
			 this resource.
			 */
			KeyT m_resource_key;
		};
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// PersistentResourcePool
	//-------------------------------------------------------------------------
	#pragma region

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
		// Class Member Types
		//---------------------------------------------------------------------

		/**
		 The key type of persistent resource pools.
		 */
		using key_type = KeyT;

		/**
		 The value type of persistent resource pools.
		 */
		using value_type = ResourceT;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a persistent resource pool.
		 */
		PersistentResourcePool() = default;

		/**
		 Constructs a persistent resource pool from the given persistent
		 resource pool.

		 @param[in]		pool
						A reference to the persistent resource pool to copy.
		 */
		PersistentResourcePool(const PersistentResourcePool& pool) = delete;

		/**
		 Constructs a persistent resource pool by moving the given persistent
		 resource pool.

		 @param[in]		pool
						A reference to the persistent resource pool to move.
		 */
		PersistentResourcePool(PersistentResourcePool&& pool) noexcept;

		/**
		 Destructs this persistent resource pool.
		 */
		~PersistentResourcePool() noexcept {
			RemoveAll();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given persistent resource pool to this persistent resource
		 pool.

		 @param[in]		pool
						A reference to the persistent resource pool to copy.
		 @return		A reference to the copy of the given persistent resource
						pool (i.e. this persistent resource pool).
		 */
		PersistentResourcePool& operator=(
			const PersistentResourcePool& pool) = delete;

		/**
		 Moves the given persistent resource pool to this persistent resource
		 pool.

		 @param[in]		pool
						A reference to the persistent resource pool to move.
		 @return		A reference to the moved persistent resource pool (i.e.
						this persistent resource pool).
		 */
		PersistentResourcePool& operator=(
			PersistentResourcePool&& pool) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this persistent resource pool is empty.

		 @return		@c true if this persistent resource pool is empty.
						@c false otherwise.
		 */
		[[nodiscard]]
		bool empty() const noexcept;

		/**
		 Returns the number of resources contained in this persistent resource
		 pool.
		 */
		[[nodiscard]]
		std::size_t size() const noexcept;

		/**
		 Checks whether this persistent resource pool contains a resource
		 corresponding to the given key from this persistent resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c true, if a resource is contained in
						this persistent resource pool corresponding to the
						given key. @c false, otherwise.
		 */
		[[nodiscard]]
		bool Contains(const KeyT& key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this
		 persistent resource pool.

		 @param[in]		key
						A reference to the key of the resource.
		 @return		@c nullptr, if no resource is contained in this
						persistent resource pool corresponding to the given
						key.
		 @return		A pointer to the resource corresponding to
						the given key from this persistent resource pool.
		 */
		[[nodiscard]]
		SharedPtr< ResourceT > Get(const KeyT& key) noexcept;

		/**
		 Returns the resource corresponding to the given key from this
		 persistent resource pool.

		 If no resource is contained in this persistent resource pool
		 corresponding to the given key, a new resource is created from the
		 given arguments, added to this persistent resource pool and returned.

		 @tparam		ConstructorArgsT
						The argument types for creating a new resource of type
						@c ResourceT.
		 @param[in]		key
						A reference to the key of the resource.
		 @param[in]		args
						The arguments for creating a new resource of type
						@c ResourceT.
		 @return		A pointer to the resource corresponding to the given
						key from this persistent resource pool.
		 */
		template< typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreate(const KeyT& key,
			                               ConstructorArgsT&&... args);

		/**
		 Returns the resource corresponding to the given key from this
		 persistent resource pool.

		 If no resource is contained in this persistent resource pool
		 corresponding to the given key, a new resource is created from the
		 given arguments, added to this persistent resource pool and returned.

		 @pre			@c DerivedResourceT is a derived class of @c ResourceT.
		 @tparam		DerivedResourceT
						The derived resource type.
		 @tparam		ConstructorArgsT
						The argument types for creating a new resource of type
						@c DerivedResourceT.
		 @param[in]		key
						A reference to the key of the resource.
		 @param[in]		args
						The arguments for creating a new resource of type
						@c DerivedResourceT.
		 @return		A pointer to the resource corresponding to the given
						key from this persistent resource pool.
		 */
		template< typename DerivedResourceT, typename... ConstructorArgsT >
		SharedPtr< ResourceT > GetOrCreateDerived(const KeyT& key,
			                                      ConstructorArgsT&&... args);

		/**
		 Removes the resource corresponding to the given key from this
		 persistent resource pool.

		 @param[in]		key
						A reference to the key of the resource to remove.
		 */
		void Remove(const KeyT& key);

		/**
		 Removes all resources from this persistent resource pool.
		 */
		void RemoveAll() noexcept;

	private:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		/**
		 A resource map used by a persistent resource pool.
		 */
		using ResourceMap = std::map< KeyT, SharedPtr< ResourceT > >;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The resource map of this persistent resource pool.
		 */
		ResourceMap m_resource_map;

		/**
		 The mutex for accessing the resource map of this persistent resource
		 pool.
		 */
		mutable std::mutex m_mutex;
	};

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_pool.tpp"

#pragma endregion