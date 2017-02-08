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

		 @param[in]		CreateResourceFunction
						The application specific resource creation function.
		 */
		ResourceManager(void(*CreateResourceFunction)(T **resource, const wstring &name, const wstring &path) = nullptr) 
			: CreateResource(CreateResourceFunction) {}

		/**
		 Destructs this resource manager.
		 */
		virtual ~ResourceManager() = default;

		/**
		 Checks whether this resource manager contains the given resource.

		 @param[in]		name
						A reference to the name of the resource.
		 @param[in]		path
						A reference to the path of the resource.
		 @return		@c true if this resource manager contains the given resource.
						@c false otherwise.
		 */
		bool ContainsResource(const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH) const {
			return (GetResource(name, path) != nullptr);
		}

		/**
		 Returns the number of resources of this resource manager.

		 @return		The number of resources of this resource manager.
		 */
		size_t GetNumberbOfResources() const {
			return m_resources.size();
		}

		/**
		 Adds a new resource to this resource manager.

		 @param[in]		name
						A reference to the name of the new resource.
		 @param[in]		path
						A reference to the path of the new resource.
		 @return		A pointer to the resource.
		 */
		SharedPtr< T > AddResource(const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);
		
		/**
		 Removes the given resource from this resource manager.

		 @param[in]		resource
						A pointer to the resource.
		 */
		void RemoveResource(SharedPtr< T > resource);

		/**
		 Removes the given resource from this resource manager.

		 @param[in]		name
						A reference to the name of the resource.
		 @param[in]		path
						A reference to the path of the resource.
		 */
		void RemoveResource(const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH);

		/**
		 Removes all resources from this resource manager.
		 */
		void RemoveAllResources();

		/**
		 Returns a resource of this resource manager by its filename (given name and path).

		 @param[in]		name
						A reference to the name of the resource.
		 @param[in]		path
						A reference to the path of the resource.
		 @return		@c nullptr if the resource is not present.
		 @return		A pointer to the resource.
		 */
		SharedPtr< T > GetResource(const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH) const;

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
		 and their file names as key.
		 */
		map< wstring, SharedPtr< T > > m_resources;

		/**
		 The application specific resource creation function for the resources
		 of this resource manager.
		 */
		void(*CreateResource)(T **resource, const wstring &name, const wstring &path);
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource_manager.tpp"

#pragma endregion