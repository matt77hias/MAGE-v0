#pragma once

//-----------------------------------------------------------------------------
// Resource
//-----------------------------------------------------------------------------
class Resource : ReferenceCounted {

public:

	Resource(const string &name, const string &path = "./") 
		: ReferenceCounted(), m_name(name), m_path(path) {
		AtomicAdd(&m_reference_count, 1);
	}
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

	const string m_name;
	const string m_path;
};
