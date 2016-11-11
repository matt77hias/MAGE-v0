#pragma once

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
		ResourceManager(void(*CreateResourceFunction)(T **resource, const string &name, const string &path) = NULL) : m_resources(list< T * >()), CreateResource(CreateResourceFunction) {}

		/**
		 Destructs this resource manager.
		 */
		virtual ~ResourceManager() {
			m_resources.clear();
		}

		/**
		 Adds a new resource to this resource manager.

		 @param[in]		name
						A reference to the name of the new resource.
		 @param[in]		path
						A reference to the path of the new resource.
		 @return		A pointer to the resource.
		 */
		T *AddResource(const string &name, const string &path = "./") {
			T *resource;

			// If the element already exists, then return a pointer to it.
			resource = GetResource(name, path);
			if (resource) {
				resource->IncrementResourceReferenceCount();
				return resource;
			}

			// Create the resource, preferably through the application specific
			// function if it is available.
			if (CreateResource != NULL) {
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

		 @param[in,out]		resource
						A pointer to the resource.
		 */
		void RemoveResource(T *resource) {
			if (*resource) {
				return;
			}

			// If the resource is no long being used then destroy it.
			if (resource->DecrementResourceReferenceCount() == 0) {
				m_resources.remove(resource);
				delete resource;
			}
		}

		/**
		 Removes and destructs all the resources from this resource manager, 
		 and leaving the resource manager with no resources.
		 */
		void ClearResources() {
			m_resources.clear();
		}

		/**
		 Returns a resource of this resource manager by its filename (given name and path).

		 @param[in]		name
						A reference to the name of the new resource.
		 @param[in]		path
						A reference to the path of the new resource.
		 @return		@c NULL if the resource is not present.
		 @return		A pointer to the resource.
		 */
		T *GetResource(const string &name, const string &path = "./") const {
			// Iterate the resources looking for the specified resource.
			for (list< Resource * >::iterator it = m_resources.begin(); it != m_resources.end(); ++it) {
				if ((*it)->GetName() == name && (*it)->getPath() == path) {
					return *it;
				}
			}
			// Return NULL if the resource was not found.
			return NULL;
		}

	private:

		/**
		 The linked list containing the resources of this resource manager.
		 */
		list< T * > m_resources;

		/** 
		 The application specific resource creation function for the resources
		 of this resource manager.
		 */
		void(*CreateResource)(T **resource, const string &name, const string &path);
	};
}