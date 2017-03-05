#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "file\file_utils.hpp"

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
		 Constructs a resource with a given filename.

		 @param[in]		fname
						A reference to the filename.
		 */
		Resource(const wstring &fname)
			: m_fname(fname) {}

		/**
		 Constructs a resource from the given resource.

		 @param[in]		resource
						A reference to the resource.
		 */
		Resource(const Resource &resource) = default;

		/**
		 Destructs this resource.
		 */
		virtual ~Resource() = default;

		/**
		 Copies the given resource to this resource.

		 @param[in]		resource
						A reference to the resource to copy from.
		 @return		A reference to the copy of the given resource
						(i.e. this resource).
		 */
		Resource &operator=(const Resource &resource) = default;

		/**
		 Returns the filename of this resource.

		 @return		The filename of this resource.
		 */
		const wstring GetFilename() const {
			return m_fname;
		}

		/**
		 Returns the name of this resource.

		 @return		The name of this resource.
		 */
		const wstring GetName() const {
			return GetFileName(m_fname);
		}


		/**
		 Returns the path of this resource.

		 @return		The path of this resource.
		 */
		const wstring GetPath() const {
			return GetPathName(m_fname);
		}

	private:

		/**
		 The name of this resource.
		 */
		const wstring m_fname;
	};
}