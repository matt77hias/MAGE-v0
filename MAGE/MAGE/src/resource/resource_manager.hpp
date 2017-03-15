#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "resource\resource.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of resource managers.

	 @tparam		T
					The type of resources.
	 */
	template< typename T >
	class ResourceManager {

	public:

		/**
		 Constructs a resource manager.
		 */
		ResourceManager() = default;

		/**
		 Destructs this resource manager.
		 */
		virtual ~ResourceManager() = default;

		/**
		 Checks whether this resource manager contains the given resource.

		 @param[in]		guid
						A reference to the globally unique identifier of the resource.
		 @return		@c true if this resource manager contains the given resource.
						@c false otherwise.
		 */
		bool ContainsResource(const wstring &guid) const {
			return (GetResource(guid) != nullptr);
		}

		/**
		 Returns the number of resources of this resource manager.

		 @return		The number of resources of this resource manager.
		 */
		size_t GetNumberbOfResources() const {
			return m_resources.size();
		}

		/**
		 Adds the given resource to this resource manager.

		 @param[in]		resource
						A pointer to the resource.
		 */
		void AddResource(SharedPtr< T > resource);
		
		/**
		 Removes the given resource from this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the resource.
		 */
		void RemoveResource(const wstring &guid);

		/**
		 Removes the given resource from this resource manager.

		 @param[in]		resource
						A pointer to the resource.
		 */
		void RemoveResource(SharedPtr< T > resource);

		/**
		 Removes all resources from this resource manager.
		 */
		void RemoveAllResources();

		/**
		 Returns the given resource of this resource manager.

		 @param[in]		guid
						A reference to the globally unique identifier of the resource.
		 @return		@c nullptr if the resource is not present.
		 @return		A pointer to the resource.
		 */
		SharedPtr< T > GetResource(const wstring &guid) const;

	private:

		/**
		 Constructs a resource manager from the given resource manager.

		 @param[in]		resource_manager
						A reference to the resource manager.
		 */
		ResourceManager(const ResourceManager &resource_manager) = delete;

		/**
		 Copies the given resource manager to this resource manager.

		 @param[in]		resource_manager
						A reference to the resource manager to copy from.
		 @return		A reference to the copy of the given resource manager
						(i.e. this resource manager).
		 */
		ResourceManager &operator=(const ResourceManager &resource_manager) = delete;

		/**
		 The map containing the resources of this resource manager as value
		 and their globally unique identifiers as key.
		 */
		map< wstring, SharedPtr< T > > m_resources;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_manager.tpp"

#pragma endregion