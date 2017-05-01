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

	//-------------------------------------------------------------------------
	// Resource
	//-------------------------------------------------------------------------

	/**
	 A class of resources.
	 */
	class Resource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a resource with a given globally unique identifier.

		 @param[in]		guid
						A reference to the globally unique identifier.
		 */
		explicit Resource(const wstring &guid)
			: m_guid(guid) {}

		/**
		 Constructs a resource from the given resource.

		 @param[in]		resource
						A reference to the resource to copy.
		 */
		Resource(const Resource &resource) = delete;

		/**
		 Constructs a resource by moving the given resource.

		 @param[in]		resource
						A reference to the resource to move.
		 */
		Resource(Resource &&resource) = default;

		/**
		 Destructs this resource.
		 */
		virtual ~Resource() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given resource to this resource.

		 @param[in]		resource
						A reference to the resource to copy.
		 @return		A reference to the copy of the given resource
						(i.e. this resource).
		 */
		Resource &operator=(const Resource &resource) = delete;

		/**
		 Moves the given resource to this resource.

		 @param[in]		resource
						A reference to the resource to move.
		 @return		A reference to the moved resource
						(i.e. this resource).
		 */
		Resource &operator=(Resource &&resource) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the globally unique identifier of this resource.

		 @return		A reference to the globally unique identifier of this resource.
		 */
		const wstring &GetGuid() const {
			return m_guid;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The globally unique identifier of this resource.
		 */
		const wstring m_guid;
	};

	//-------------------------------------------------------------------------
	// FileResource
	//-------------------------------------------------------------------------

	/**
	 A class of file resources.
	 */
	class FileResource : public Resource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a file resource with a given filename.

		 @param[in]		fname
						A reference to the filename.
		 */
		explicit FileResource(const wstring &fname)
			: Resource(fname) {}

		/**
		 Constructs a file resource from the given file resource.

		 @param[in]		file_resource
						A reference to the file resource to copy.
		 */
		FileResource(const FileResource &file_resource) = delete;

		/**
		 Constructs a file resource by moving the given file resource.

		 @param[in]		file_resource
						A reference to the file resource to move.
		 */
		FileResource(FileResource &&file_resource) = default;

		/**
		 Destructs this file resource.
		 */
		virtual ~FileResource() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given file resource to this file resource.

		 @param[in]		file_resource
						A reference to the file resource to copy.
		 @return		A reference to the copy of the given file resource
						(i.e. this file resource).
		 */
		FileResource &operator=(const FileResource &file_resource) = delete;

		/**
		 Moves the given file resource to this file resource.

		 @param[in]		file_resource
						A reference to the file resource to move.
		 @return		A reference to the moved file resource
						(i.e. this file resource).
		 */
		FileResource &operator=(FileResource &&file_resource) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the filename of this file resource.

		 @return		A reference to the filename of this file resource.
		 */
		const wstring &GetFilename() const {
			return GetGuid();
		}

		/**
		 Returns the name of this file resource.

		 @return		The name of this file resource.
		 */
		const wstring GetName() const {
			return GetFileName(GetGuid());
		}

		/**
		 Returns the path of this file resource.

		 @return		The path of this file resource.
		 */
		const wstring GetPath() const {
			return GetPathName(GetGuid());
		}
	};
}