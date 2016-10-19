#pragma once

namespace mage {

	//-----------------------------------------------------------------------------
	// ResourceManager
	//-----------------------------------------------------------------------------
	template< typename T >
	class ResourceManager {

	public:

		ResourceManager(void(*CreateResourceFunction)(T **resource, const string &name, const string &path) = NULL) {
			m_resources = new LinkedList< T >;

			CreateResource = CreateResourceFunction;
		}

		virtual ~ResourceManager() {
			delete m_resources;
		}

		T *Add(const string &name, const string &path = "./");
		void Remove(T **resource);

		void EmptyDestroy() {
			m_resources->Empty<false>();
		}

		T *GetResource(const string &name, const string &path = "./") const;
		const LinkedList< T > *GetResources() const {
			return m_resources;
		}


	private:

		// Linked list of resources
		LinkedList< T > *m_resources;
		// Application specific resource creation
		void(*CreateResource)(T **resource, const string &name, const string &path);
	};
}
