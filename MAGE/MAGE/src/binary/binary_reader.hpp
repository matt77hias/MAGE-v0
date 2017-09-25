#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Reads the bytes of a binary file.

	 @pre			@a fname is not equal to @c nullptr.
	 @pre			@a size is not equal to @c nullptr.
	 @param[in]		fname
					A pointer to a null-terminated wide string representing the filename.
	 @param[out]	data
					A reference to a pointer to a buffer for storing the read bytes.
	 @param[out]	size
					A pointer to the size of the read bytes.
	 @throws		FormattedException
					Failed to read from the given file.
	 */
	void ReadBinaryFile(const wchar_t *fname, UniquePtr< u8[] > &data, size_t *size);

	//-------------------------------------------------------------------------
	// BinaryReader
	//-------------------------------------------------------------------------

	/**
	 A class of readers for reading binary files.
	 */
	class BinaryReader {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this binary reader.
		 */
		virtual ~BinaryReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given binary reader to this binary reader.

		 @param[in]		reader
						A reference to a binary reader to copy.
		 @return		A reference to the copy of the given binary reader
						(i.e. this binary reader).
		 */
		BinaryReader &operator=(const BinaryReader &reader) = delete;

		/**
		 Moves the given binary reader to this binary reader.

		 @param[in]		reader
						A reference to a binary reader to move.
		 @return		A reference to the moved binary reader
						(i.e. this binary reader).
		 */
		BinaryReader &operator=(BinaryReader &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads from the given file.

		 @param[in]		fname
						A reference to the file name.
		 @param[in]		big_endian
						Flag indicating whether the given byte array
						should be interpreted as big endian or not (i.e. little endian).
		 @throws		FormattedException
						Failed to read from the given file.
		 */
		void ReadFromFile(const wstring &fname, bool big_endian);

		/**
		 Reads the input string.

		 @pre			@a input is not equal to @c nullptr.
		 @param[in]		input
						A pointer to the input byte string.
		 @param[in]		size
						The size of the input string.
		 @param[in]		big_endian
						Flag indicating whether the given byte array
						should be interpreted as big endian or not (i.e. little endian).
		 @throws		FormattedException
						Failed to read from the given input string.
		 */
		void ReadFromMemory(const u8 *input, size_t size, bool big_endian);

		/**
		 Returns the current filename of this binary reader.

		 @return		A reference to the current filename of this binary reader.
		 */
		const wstring &GetFilename() const noexcept {
			return m_fname;
		}
		
	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a binary reader.
		 */
		BinaryReader();
		
		/**
		 Constructs a binary reader from the given binary reader.

		 @param[in]		reader
						A reference to the binary reader to copy.
		 */
		BinaryReader(const BinaryReader &reader) = delete;

		/**
		 Constructs a binary reader by moving the given binary reader.

		 @param[in]		reader
						A reference to the binary reader to move.
		 */
		BinaryReader(BinaryReader &&reader);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks if there are characters left to read by this binary reader.

		 @return		@c true if there are characters left to read by this binary reader.
						@c false otherwise.
		 */
		bool HasCharsLeft() const noexcept {
			return m_pos < m_end;
		}

		/**
		 Reads an array of byte characters.

		 @param			size
						The number of bytes to read.
		 @return		A pointer to the array of characters read.
		 @throws		FormattedException
						Failed to read @c size bytes.
		 */
		const char *ReadChars(size_t size);

		/**
		 Reads a @c i8.

		 @return		The @c i8 read.
		 @throws		FormattedException
						Failed to read a @c i8.
		 */
		i8 ReadI8();

		/**
		 Reads a @c u8.

		 @return		The @c u8 read.
		 @throws		FormattedException
						Failed to read a @c u8.
		 */
		u8 ReadU8();

		/**
		 Reads a @c i16.

		 @return		The @c i16 read.
		 @throws		FormattedException
						Failed to read a @c i16.
		 */
		i16 ReadI16();

		/**
		 Reads a @c u16.

		 @return		The @c u16 read.
		 @throws		FormattedException
						Failed to read a @c u16.
		 */
		u16 ReadU16();

		/**
		 Reads a @c i32.

		 @return		The @c i32 read.
		 @throws		FormattedException
						Failed to read a @c i32.
		 */
		i32 ReadI32();

		/**
		 Reads a @c u32.

		 @return		The @c u32 read.
		 @throws		FormattedException
						Failed to read a @c u32.
		 */
		u32 ReadU32();

		/**
		 Reads a @c i64.

		 @return		The @c i64 read.
		 @throws		FormattedException
						Failed to read a @c i64.
		 */
		i64 ReadI64();

		/**
		 Reads a @c u64.

		 @return		The @c u64 read.
		 @throws		FormattedException
						Failed to read a @c u64.
		 */
		u64 ReadU64();

		/**
		 Reads a @c float.

		 @return		The @c float read.
		 @throws		FormattedException
						Failed to read a @c float.
		 */
		float ReadF32();

		/**
		 Reads a @c double.

		 @return		The @c double read.
		 @throws		FormattedException
						Failed to read a @c double.
		 */
		double ReadF64();

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts reading.

		 @throws		FormattedException
						Failed to read to the given file.
		 */
		virtual void Read() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current filename of this line reader.
		 */
		wstring m_fname;

		/**
		 A flag indicating whether the current data of this binary reader
		 should be interpreted as big endian or not (i.e. little endian).
		 */
		bool m_big_endian;

		/**
		 A pointer to the current position of this binary reader.
		 */
		const u8 *m_pos;

		/**
		 A pointer to the end position of this binary reader.
		 */
		const u8 *m_end;

		/**
		 A pointer to the data to read of this binary reader.
		 */
		UniquePtr< u8[] > m_data;
	};

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------

	/**
	 A class of readers for reading (big endian) binary files.
	 */
	class BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this big endian binary reader.
		 */
		virtual ~BigEndianBinaryReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given big endian binary reader to this big endian binary reader.

		 @param[in]		reader
						A reference to a big endian binary reader to copy.
		 @return		A reference to the copy of the given big endian binary reader
						(i.e. this big endian binary reader).
		 */
		BigEndianBinaryReader &operator=(const BigEndianBinaryReader &reader) = delete;
		
		/**
		 Moves the given big endian binary reader to this big endian binary reader.

		 @param[in]		reader
						A reference to a big endian binary reader to move.
		 @return		A reference to the moved big endian binary reader
						(i.e. this big endian binary reader).
		 */
		BigEndianBinaryReader &operator=(BigEndianBinaryReader &&reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads from the given file.

		 @param[in]		fname
						A reference to the file name.
		 @throws		FormattedException
						Failed to read from the given file.
		 */
		void ReadFromFile(const wstring &fname);

		/**
		 Reads the input string.

		 @pre			@a input is not equal to @c nullptr.
		 @param[in]		input
						A pointer to the input byte string.
		 @param[in]		size
						The size of the input string.
		 @throws		FormattedException
						Failed to read from the given input string.
		 */
		void ReadFromMemory(const u8 *input, size_t size);

		/**
		 Returns the current filename of this big endian binary reader.

		 @return		A reference to the current filename of this big endian binary reader.
		 */
		const wstring &GetFilename() const noexcept {
			return m_fname;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a big endian binary reader.
		 */
		BigEndianBinaryReader();
		
		/**
		 Constructs a big endian binary reader from the given big endian binary reader.

		 @param[in]		reader
						A reference to the big endian binary reader to copy.
		 */
		BigEndianBinaryReader(const BigEndianBinaryReader &reader) = delete;

		/**
		 Constructs a big endian binary reader by moving the given big endian binary reader.

		 @param[in]		reader
						A reference to the big endian binary reader to move.
		 */
		BigEndianBinaryReader(BigEndianBinaryReader &&reader);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks if there are characters left to read by this binary reader.

		 @return		@c true if there are characters left to read by this binary reader.
						@c false otherwise.
		 */
		bool HasCharsLeft() const noexcept {
			return m_pos < m_end;
		}

		/**
		 Reads a @c DataT element.

		 @tparam		DataT
						The data type.
		 @return		A reference to the @c DataT element read.
		 @throws		FormattedException
						Failed to read a @c DataT element.
		 */
		template< typename DataT >
		const DataT &ReadValue();
		
		/**
		 Reads an array of @c DataT elements.

		 @tparam		DataT
						The data type.
		 @param			count
						The number of @c DataT elements to read.
		 @return		A pointer to the array of @c DataT element read.
		 @throws		FormattedException
						Failed to read @c count @c DataT elements.
		 */
		template< typename DataT >
		const DataT *ReadValueArray(size_t count);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts reading.

		 @throws		FormattedException
						Failed to read to the given file.
		 */
		virtual void Read() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current filename of this line reader.
		 */
		wstring m_fname;

		/**
		 A pointer to the current position of this binary reader.
		 */
		const u8 *m_pos;

		/**
		 A pointer to the end position of this binary reader.
		 */
		const u8 *m_end;

		/**
		 A pointer to the data to read of this binary reader.
		 */
		UniquePtr< u8[] > m_data;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "binary\binary_reader.tpp"

#pragma endregion