#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ResourcePool
	//-------------------------------------------------------------------------
	#pragma region

	template< typename KeyT, typename ResourceT >
	ResourcePool< KeyT, ResourceT >::ResourcePool(ResourcePool&& pool) noexcept
		: m_mutex() {

		const std::scoped_lock< std::mutex > lock(pool.m_mutex);

		m_resource_map = std::move(pool.m_resource_map);
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]
	inline bool ResourcePool< KeyT, ResourceT >::empty() const noexcept {
		const std::scoped_lock< std::mutex > lock(m_mutex);

		using std::empty;
		return empty(m_resource_map);
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]
	inline std::size_t ResourcePool< KeyT, ResourceT >::size() const noexcept {
		const std::scoped_lock< std::mutex > lock(m_mutex);

		using std::size;
		return size(m_resource_map);
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]
	bool ResourcePool< KeyT, ResourceT >::Contains(const KeyT& key) noexcept {
		const std::scoped_lock< std::mutex > lock(m_mutex);

		if (const auto it = m_resource_map.find(key);
			it != m_resource_map.end()) {

			const auto resource = it->second.lock();

			if (resource) {
				return true;
			}

			m_resource_map.erase(it);
		}

		return false;
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]
	SharedPtr< ResourceT > ResourcePool< KeyT, ResourceT >
		::Get(const KeyT& key) noexcept {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		if (const auto it = m_resource_map.find(key);
			it != m_resource_map.end()) {

			const auto resource = it->second.lock();

			if (resource) {
				return resource;
			}

			m_resource_map.erase(it);
		}

		return SharedPtr< ResourceT >();
	}

	template< typename KeyT, typename ResourceT >
	template< typename... ConstructorArgsT >
	inline SharedPtr< ResourceT > ResourcePool< KeyT, ResourceT >
		::GetOrCreate(const KeyT& key, ConstructorArgsT&&... args) {

		return GetOrCreateDerived< ResourceT, ConstructorArgsT... >(
			key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename KeyT, typename ResourceT >
	template< typename DerivedResourceT, typename... ConstructorArgsT >
	SharedPtr< ResourceT > ResourcePool< KeyT, ResourceT >
		::GetOrCreateDerived(const KeyT& key, ConstructorArgsT&&... args) {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		if (const auto it = m_resource_map.find(key);
			it != m_resource_map.end()) {

			const auto resource = it->second.lock();
			if (resource) {
				return resource;
			}

			m_resource_map.erase(it);
		}

		const auto new_resource
			= MakeAllocatedShared< Resource< DerivedResourceT > >
			  (*this, key, std::forward< ConstructorArgsT >(args)...);

		m_resource_map.emplace(key, new_resource);

		return new_resource;
	}

	template< typename KeyT, typename ResourceT >
	void ResourcePool< KeyT, ResourceT >::Remove(const KeyT& key) {
		const std::scoped_lock< std::mutex > lock(m_mutex);

		if (const auto it = m_resource_map.find(key);
			it != m_resource_map.end() && it->second.expired()) {

			m_resource_map.erase(it);
		}
	}

	template< typename KeyT, typename ResourceT >
	inline void ResourcePool< KeyT, ResourceT >::RemoveAll() noexcept {
		const std::scoped_lock< std::mutex > lock(m_mutex);

		m_resource_map.clear();
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Resource
	//-------------------------------------------------------------------------
	#pragma region

	template< typename KeyT, typename ResourceT >
	template< typename DerivedResourceT >
	template< typename... ConstructorArgsT >
	ResourcePool< KeyT, ResourceT >::Resource< DerivedResourceT >
		::Resource(ResourcePool& resource_pool,
			       const KeyT& resource_key,
			       ConstructorArgsT&&... args)
		: DerivedResourceT(std::forward< ConstructorArgsT >(args)...),
		m_resource_pool(resource_pool),
		m_resource_key(resource_key) {}

	template< typename KeyT, typename ResourceT >
	template< typename DerivedResourceT >
	ResourcePool< KeyT, ResourceT >::Resource< DerivedResourceT >
		::Resource(Resource&& resource) = default;


	template< typename KeyT, typename ResourceT >
	template< typename DerivedResourceT >
	ResourcePool< KeyT, ResourceT >::Resource< DerivedResourceT >
		::~Resource() {

		m_resource_pool.Remove(m_resource_key);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// PersistentResourcePool
	//-------------------------------------------------------------------------
	#pragma region

	template< typename KeyT, typename ResourceT >
	PersistentResourcePool< KeyT, ResourceT >
		::PersistentResourcePool(PersistentResourcePool&& pool) noexcept
		: m_mutex() {

		const std::scoped_lock< std::mutex > lock(pool.m_mutex);

		m_resource_map = std::move(pool.m_resource_map);
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]
	inline bool PersistentResourcePool< KeyT, ResourceT >
		::empty() const noexcept {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		using std::empty;
		return empty(m_resource_map);
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]
	inline std::size_t PersistentResourcePool< KeyT, ResourceT >
		::size() const noexcept {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		using std::size;
		return size(m_resource_map);
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]bool PersistentResourcePool< KeyT, ResourceT >
		::Contains(const KeyT& key) noexcept {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		const auto it = m_resource_map.find(key);
		return (it != m_resource_map.end());
	}

	template< typename KeyT, typename ResourceT >
	[[nodiscard]]SharedPtr< ResourceT > PersistentResourcePool< KeyT, ResourceT >
		::Get(const KeyT& key) noexcept {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		const auto it = m_resource_map.find(key);
		return (it != m_resource_map.end()) ? it->second
			                                : SharedPtr< ResourceT >();
	}

	template< typename KeyT, typename ResourceT >
	template< typename... ConstructorArgsT >
	inline SharedPtr< ResourceT > PersistentResourcePool< KeyT, ResourceT >
		::GetOrCreate(const KeyT& key, ConstructorArgsT&&... args) {

		return GetOrCreateDerived< ResourceT, ConstructorArgsT... >(
			key, std::forward< ConstructorArgsT >(args)...);
	}

	template< typename KeyT, typename ResourceT >
	template< typename DerivedResourceT, typename... ConstructorArgsT >
	SharedPtr< ResourceT > PersistentResourcePool< KeyT, ResourceT >
		::GetOrCreateDerived(const KeyT& key, ConstructorArgsT&&... args) {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		if (const auto it = m_resource_map.find(key);
			it != m_resource_map.end()) {

			return it->second;
		}

		const auto new_resource = MakeAllocatedShared< DerivedResourceT >
			                      (std::forward< ConstructorArgsT >(args)...);

		m_resource_map.emplace(key, new_resource);

		return new_resource;
	}

	template< typename KeyT, typename ResourceT >
	void PersistentResourcePool< KeyT, ResourceT >
		::Remove(const KeyT& key) {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		if (const auto it = m_resource_map.find(key);
			it != m_resource_map.end()) {

			m_resource_map.erase(it);
		}
	}

	template< typename KeyT, typename ResourceT >
	inline void PersistentResourcePool< KeyT, ResourceT >
		::RemoveAll() noexcept {

		const std::scoped_lock< std::mutex > lock(m_mutex);

		m_resource_map.clear();
	}

	#pragma endregion
}