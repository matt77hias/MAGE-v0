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
		T *Add(const string &name, const string &path = "./");
		
		/**
		 Removes the given resource from this resource manager.

		 @param[in,out]		resource
						A pointer to a pointer of the resource.
		 */
		void Remove(T **resource);

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
		T *GetResource(const string &name, const string &path = "./") const;
		const LinkedList< T > *GetResources() const {
			return m_resources;
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
