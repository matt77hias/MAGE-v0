#pragma region

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename StringT >
	[[nodiscard]]
	inline const StringT GetFilename(const StringT &path, 
									 const StringT &name) {
		return path + name;
	}

	template< typename StringT >
	[[nodiscard]]
	inline const StringT GetFileExtension(const StringT &fname) {
		static const StringT str(1, StringT::value_type('.'));
		
		const auto begin_pos = fname.find_last_of(str);
		ThrowIfFailed((StringT::npos != begin_pos), 
					  "The filename does not have a file extension.");

		return fname.substr(begin_pos + 1);
	}

	template< typename StringT >
	[[nodiscard]]
	inline const StringT GetFileName(const StringT &fname) {
		static const StringT str(1, StringT::value_type('/'));
		
		const auto begin_pos = fname.find_last_of(str);
		ThrowIfFailed((StringT::npos != begin_pos), 
					  "The filename does not have a file path.");

		return fname.substr(begin_pos + 1);
	}

	template< typename StringT >
	[[nodiscard]]
	inline const StringT GetPathName(const StringT &fname) {
		static const StringT str(1, StringT::value_type('/'));
		
		const auto end_pos = fname.find_last_of(str);
		ThrowIfFailed((string::npos != end_pos), 
					  "The filename does not have a file path.");

		return fname.substr(0, end_pos + 1);
	}

	template< typename StringT >
	[[nodiscard]]
	inline const StringT GetFilenameWithoutFileExtension(const StringT &fname) {
		static const StringT str(1, StringT::value_type('.'));
		
		const auto end_pos = fname.find_last_of(str);
		ThrowIfFailed((StringT::npos != end_pos), 
					  "The filename does not have a file extension.");

		return fname.substr(0, end_pos);
	}
}