#pragma once

namespace mage {

	//-----------------------------------------------------------------------------
	// Resource
	//-----------------------------------------------------------------------------

	// Forward declaration
	template< typename T >
	class ResourceManager;

	class Resource {

	public:

		Resource(const string &name, const string &path = "./")
			: m_name(name), m_path(path), m_reference_count(1) {}
		virtual ~Resource() {}

		// Returns the name of this resource.
		const string &GetName() const {
			return m_name;
		}
		// Returns the path to this resource.
		const string &GetPath() const {
			return m_path;
		}
		// Returns the filename of this resource.
		const string &GetFilename() const {
			return m_name + m_path;
		}

	private:
		template< typename T >
		friend class ResourceManager;

		// Increment the reference count of this resource.
		uint32_t IncrementReferenceCount() {
			return (uint32_t)AtomicAdd(&m_reference_count, 1);
		}
		// Decrement the reference count of this resource.
		uint32_t DecrementReferenceCount() {
			return (uint32_t)AtomicAdd(&m_reference_count, -1);
		}

		const string m_name;
		const string m_path;

		AtomicInt32 m_reference_count;
	};

}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "resource/resource_manager.hpp"