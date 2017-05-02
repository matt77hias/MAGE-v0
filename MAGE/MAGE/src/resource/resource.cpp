//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\resource.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Resource
	//-------------------------------------------------------------------------

	Resource::Resource(const wstring &guid)
		: m_guid(guid) {}

	Resource::Resource(Resource &&resource) = default;

	Resource::~Resource() = default;

	//-------------------------------------------------------------------------
	// FileResource
	//-------------------------------------------------------------------------

	FileResource::FileResource(const wstring &fname)
		: Resource(fname) {}

	FileResource::FileResource(FileResource &&file_resource) = default;

	FileResource::~FileResource() = default;
}