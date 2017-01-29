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
		virtual ~ResourceManager() {}

		/**
		 Adds a new resource to this resource manager.

		 @param[in]		name
						A reference to the name of the new resource.
		 @param[in]		path
						A reference to the path of the new resource.
		 @return		A pointer to the resource.
		 */
		SharedPtr< T > AddResource(const wstring &name, const wstring &path = "./") {
			// If the element already exists, then return a pointer to it.
			SharedPtr< T > resource = GetResource(name, path);
			if (resource) {
				return resource;
			}

			// Create the resource, preferably through the application specific
			// function if it is available.
			if (CreateResource) {
				CreateResource(&resource, name, path);
			}
			else {
				resource = new T(name, path);
			}

			// Add the new resource to this resource manager.
			m_resources.push_back(resource);

			// Return a pointer to the added resource.
			return resource;
		}
		
		/**
		 Removes the given resource from this resource manager.

		 @param[in]		resource
						A pointer to the resource.
		 */
		void RemoveResource(SharedPtr< T > resource) {
			m_resources.remove(resource);
		}

		/**
		 Returns a resource of this resource manager by its filename (given name and path).

		 @param[in]		name
						A reference to the name of the new resource.
		 @param[in]		path
						A reference to the path of the new resource.
		 @return		@c nullptr if the resource is not present.
		 @return		A pointer to the resource.
		 */
		SharedPtr< T > GetResource(const wstring &name, const wstring &path = "./") const {
			// Iterate the resources looking for the specified resource.
			for (list< SharedPtr< T > >::iterator it = m_resources.begin(); it != m_resources.end(); ++it) {
				if ((*it)->GetName() == name && (*it)->getPath() == path) {
					return *it;
				}
			}
			// Return nullptr if the resource was not found.
			return nullptr;
		}

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
		 The linked list containing the resources of this resource manager.
		 */
		list< SharedPtr< T > > m_resources;

		/**
		 The application specific resource creation function for the resources
		 of this resource manager.
		 */
		void(*CreateResource)(T **resource, const wstring &name, const wstring &path);
	};
}