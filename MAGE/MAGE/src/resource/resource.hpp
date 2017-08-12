#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"

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

	 @tparam		ResourceT
					The reource type.
	 */
	template< typename ResourceT >
	class Resource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a resource.

		 @param[in]		guid
						A reference to the globally unique identifier.
		 */
		explicit Resource(const wstring &guid);

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
		Resource(Resource &&resource);

		/**
		 Destructs this resource.
		 */
		virtual ~Resource();

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

		 @return		A refernce to the globally unique identifier 
						of this resource.
		 */
		const wstring &GetGuid() const noexcept {
			return m_guid;
		}

		/**
		 Returns the filename of this resource.

		 @pre			This resource represents a file resource.
		 @return		A reference to the filename of this resource.
		 */
		const wstring &GetFilename() const noexcept;

		/**
		 Returns the name of this resource.

		 @pre			This resource represents a file resource.
		 @return		The name of this resource.
		 */
		const wstring GetName() const noexcept;

		/**
		 Returns the path of this resource.

		 @pre			This resource represents a file resource.
		 @return		The path of this resource.
		 */
		const wstring GetPath() const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The globally unique identifier of this resource.
		 */
		const wstring m_guid;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.tpp"

#pragma endregion