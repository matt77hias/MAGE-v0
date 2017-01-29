#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "file\file_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_RESOURCE_PATH L"./"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of resources.
	 */
	class Resource {

	public:

		/**
		 Constructs a resource with a given name and path.

		 @param[in]		name
						A reference to the name.
		 @param[in]		path
						A reference to the path.
		 */
		Resource(const wstring &name, const wstring &path = MAGE_DEFAULT_RESOURCE_PATH)
			: m_name(name), m_path(path) {}

		/**
		 Destructs this resource.
		 */
		virtual ~Resource() {}

		/**
		 Returns the path of this resource.

		 @return		A reference to the path of this resource.
		 */
		const wstring &GetPath() const {
			return m_path;
		}

		/**
		 Returns the name of this resource.

		 @return		A reference to the name of this resource.
		 */
		const wstring &GetName() const {
			return m_name;
		}
		
		/**
		 Returns the filename of this resource.

		 @return		The filename of this resource.
		 */
		const wstring GetFilename() const {
			return mage::GetFilename(GetPath(), GetName());
		}

	private:

		/**
		 Constructs a resource from the given resource.

		 @param[in]		resource
						A reference to the resource.
		 */
		Resource(const Resource &resource) = delete;

		/**
		 Copies the given resource to this resource.

		 @param[in]		resource
						A reference to the resource to copy from.
		 @return		A reference to the copy of the given resource
						(i.e. this resource).
		 */
		Resource &operator=(const Resource &resource) = delete;

		/**
		 The name of this resource.
		 */
		const wstring m_name;

		/**
		 The path of this resource.
		 */
		const wstring m_path;
	};
}