#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "string\string.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of writers for writing (big endian) binary files.
	 */
	class BigEndianBinaryWriter {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this big endian binary writer.
		 */
		virtual ~BigEndianBinaryWriter();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given big endian binary writer to this big endian binary writer.

		 @param[in]		writer
						A reference to a big endian binary writer to copy.
		 @return		A reference to the copy of the given big endian binary writer
						(i.e. this big endian binary writer).
		 */
		BigEndianBinaryWriter &operator=(const BigEndianBinaryWriter &writer) = delete;

		/**
		 Moves the given big endian binary writer to this big endian binary writer.

		 @param[in]		writer
						A reference to a big endian binary writer to move.
		 @return		A reference to the moved big endian binary writer
						(i.e. this big endian binary writer).
		 */
		BigEndianBinaryWriter &operator=(BigEndianBinaryWriter &&writer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes to the given file.

		 @param[in]		fname
						A reference to the file name.
		 @throws		FormattedException
						Failed to write to the given file.
		 */
		void WriteToFile(const wstring &fname);

		/**
		 Returns the current filename of this writer.

		 @return		A reference to the current filename of this writer.
		 */
		const wstring &GetFilename() const noexcept {
			return m_fname;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a big endian binary writer.
		 */
		BigEndianBinaryWriter();
		
		/**
		 Constructs a big endian binary writer from the given big endian binary writer.

		 @param[in]		writer
						A reference to the big endian binary writer to copy.
		 */
		BigEndianBinaryWriter(const BigEndianBinaryWriter &writer) = delete;
		
		/**
		 Constructs a big endian binary writer by moving the given big endian binary writer.

		 @param[in]		writer
						A reference to the big endian binary writer to move.
		 */
		BigEndianBinaryWriter(BigEndianBinaryWriter &&writer);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes the given data.

		 @tparam		DataT
						The data type.
		 @param[in]		data
						A reference to the data.
		 @throws		FormattedException
						Failed to write the given data.
		 */
		template< typename DataT >
		void WriteValue(const DataT &data);
		
		/**
		 Writes the given data.

		 @pre			@a data is not equal to @c nullptr.
		 @pre			The array pointed to by @a data
						contains at least @a count elements.
		 @tparam		DataT
						The data type.
		 @param[in]		data
						A pointer to the data.
		 @param[in]		count
						The number of data elements of
						@c size(DataT) to write.
		 @throws		FormattedException
						Failed to write the given data.
		 */
		template< typename DataT >
		void WriteValueArray(const DataT *data, size_t count);

		/**
		 Writes the given character.

		 @param[in]		c
						The character to write.
		 @throws		FormattedException
						Failed to write the given character.
		 */
		void WriteCharacter(char c);
		
		/**
		 Writes the given string.

		 @pre			@a str is not equal to @c nullptr.
		 @param[in]		str
						A pointer to the first null-terminated byte string to write.
		 @throws		FormattedException
						Failed to write the given string.
		 */
		void WriteString(const char *str);

		/**
		 Writes the given string.

		 @param[in]		str
						A reference to the string to write.
		 @throws		FormattedException
						Failed to write the given string.
		 */
		void WriteString(const string &str) {
			WriteString(str.c_str());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		FormattedException
						Failed to write.
		 */
		virtual void Write() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the file stream of this big endian binary writer.
		 */
		UniqueFileStream m_file_stream;

		/**
		 The current filename of this big endian binary writer.
		 */
		wstring m_fname;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_writer.tpp"

#pragma endregion