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
		ResourceManager(void(*CreateResourceFunction)(T **resource, const string &name, const string &path) = NULL) {
			m_resources = new LinkedList< T >;

			CreateResource = CreateResourceFunction;
		}

		/**
		 Destructs this resource manager.
		 */
		virtual ~ResourceManager() {
			delete m_resources;
		}

		/**
		 Adds a new resource to this resource manager.

		 @param[in]		name
						A reference to the name of the new resource.
		 @param[in]		path
						A reference to the path of the new resource.
		 @return		A pointer to the resource.
		 */
		T *Add(const string &name, const string &path = "./") {
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

			// Add the new resource to this resource manager and return a pointer to it.
			return m_resources->Add(resource);
		}
		
		/**
		 Removes the given resource from this resource manager.

		 @param[in,out]		resource
						A pointer to a pointer of the resource.
		 */
		void Remove(T **resource) {
			if (*resource) {
				return;
			}

			// If the resource is no long being used then destroy it.
			if (*resource->DecrementResourceReferenceCount() == 0) {
				m_resources->Remove(resource);
			}
		}

		/**
		 Destroys all the resources of this resource manager.
		 */
		void EmptyDestroy() {
			m_resources->Empty<false>();
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
			LinkedList< T >::LinkedListIterator it = m_resources->GetIterator();
			while (it.HasNext()) {
				const T *next = it.Next();
				if (next->GetName() == name && next->getPath() == path) {
					return next;
				}
			}
			// Return NULL if the resource was not found.
			return NULL;
		}

	private:

		/**
		 The linked list containing the resources of this resource manager.
		 */
		LinkedList< T > *m_resources;

		/** 
		 The application specific resource creation function for the resources
		 of this resource manager.
		 */
		void(*CreateResource)(T **resource, const string &name, const string &path);
	};
}
