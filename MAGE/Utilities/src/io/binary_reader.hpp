#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Reads the bytes of a binary file.

	 @param[in]		fname
					A reference to the file name.
	 @param[out]	data
					A reference to a pointer to a buffer for storing the read 
					bytes.
	 @param[out]	size
					A reference to the size of the read bytes.
	 @throws		Exception
					Failed to read from the given file.
	 */
	void ReadBinaryFile(const wstring& fname, 
						UniquePtr< U8[] >& data, 
						size_t& size);

	//-------------------------------------------------------------------------
	// BinaryReader
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of readers for reading binary files.
	 */
	class BinaryReader {

	public:

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given binary reader to this binary reader.

		 @param[in]		reader
						A reference to a binary reader to copy.
		 @return		A reference to the copy of the given binary reader (i.e. 
						this binary reader).
		 */
		BinaryReader& operator=(const BinaryReader& reader) = delete;

		/**
		 Moves the given binary reader to this binary reader.

		 @param[in]		reader
						A reference to a binary reader to move.
		 @return		A reference to the moved binary reader (i.e. this 
						binary reader).
		 */
		BinaryReader& operator=(BinaryReader&& reader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads from the given file.

		 @param[in]		fname
						The file name.
		 @param[in]		big_endian
						Flag indicating whether the given byte array should be 
						interpreted as big endian or not (i.e. little endian).
		 @throws		Exception
						Failed to read from the given file.
		 */
		void ReadFromFile(wstring fname, bool big_endian);
		
		/**
		 Reads the input string.

		 @param[in]		input
						The input byte string.
		 @param[in]		big_endian
						Flag indicating whether the given byte array should be 
						interpreted as big endian or not (i.e. little endian).
		 @throws		Exception
						Failed to read from the given input string.
		 */
		void ReadFromMemory(gsl::span< const U8 > input, bool big_endian);

		/**
		 Returns the current filename of this binary reader.

		 @return		A reference to the current filename of this binary 
						reader.
		 */
		[[nodiscard]]
		const wstring& GetFilename() const noexcept {
			return m_fname;
		}
		
	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
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
		BinaryReader(const BinaryReader& reader) = delete;

		/**
		 Constructs a binary reader by moving the given binary reader.

		 @param[in]		reader
						A reference to the binary reader to move.
		 */
		BinaryReader(BinaryReader&& reader) noexcept;

		/**
		 Destructs this binary reader.
		 */
		~BinaryReader();

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks if there are characters left to read by this binary reader.

		 @return		@c true if there are characters left to read by this 
						binary reader. @c false otherwise.
		 */
		[[nodiscard]]
		bool ContainsChars() const noexcept {
			return m_pos < m_end;
		}

		/**
		 Reads an array of byte characters.

		 @param			size
						The number of bytes to read.
		 @return		A pointer to the array of characters read.
		 @throws		Exception
						Failed to read @c size bytes.
		 */
		NotNull< const_zstring > ReadChars(size_t size);

		/**
		 Reads a @c DataT element.

		 @tparam		DataT
						The data type.
		 @return		The @c DataT element read.
		 @throws		Exception
						Failed to read a @c DataT element.
		 */
		template< typename DataT >
		const DataT Read();

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts reading.

		 @throws		Exception
						Failed to read from the given file.
		 */
		virtual void ReadData() = 0;

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
		const U8* m_pos;

		/**
		 A pointer to the end position of this binary reader.
		 */
		const U8* m_end;

		/**
		 A pointer to the data to read of this binary reader.
		 */
		UniquePtr< U8[] > m_data;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// BigEndianBinaryReader
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of readers for reading (big endian) binary files.
	 */
	class BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given big endian binary reader to this big endian binary 
		 reader.

		 @param[in]		reader
						A reference to a big endian binary reader to copy.
		 @return		A reference to the copy of the given big endian binary 
						reader (i.e. this big endian binary reader).
		 */
		BigEndianBinaryReader& operator=(
			const BigEndianBinaryReader& reader) = delete;
		
		/**
		 Moves the given big endian binary reader to this big endian binary 
		 reader.

		 @param[in]		reader
						A reference to a big endian binary reader to move.
		 @return		A reference to the moved big endian binary reader
						(i.e. this big endian binary reader).
		 */
		BigEndianBinaryReader& operator=(
			BigEndianBinaryReader&& reader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads from the given file.

		 @param[in]		fname
						The file name.
		 @throws		Exception
						Failed to read from the given file.
		 */
		void ReadFromFile(wstring fname);

		/**
		 Reads the input string.

		 @param[in]		input
						The input byte string.
		 @throws		Exception
						Failed to read from the given input string.
		 */
		void ReadFromMemory(gsl::span< const U8 > input);

		/**
		 Returns the current filename of this big endian binary reader.

		 @return		A reference to the current filename of this big endian 
						binary reader.
		 */
		[[nodiscard]]
		const wstring& GetFilename() const noexcept {
			return m_fname;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a big endian binary reader.
		 */
		BigEndianBinaryReader();
		
		/**
		 Constructs a big endian binary reader from the given big endian binary 
		 reader.

		 @param[in]		reader
						A reference to the big endian binary reader to copy.
		 */
		BigEndianBinaryReader(const BigEndianBinaryReader& reader) = delete;

		/**
		 Constructs a big endian binary reader by moving the given big endian 
		 binary reader.

		 @param[in]		reader
						A reference to the big endian binary reader to move.
		 */
		BigEndianBinaryReader(BigEndianBinaryReader&& reader) noexcept;

		/**
		 Destructs this big endian binary reader.
		 */
		~BigEndianBinaryReader();

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks if there are characters left to read by this binary reader.

		 @return		@c true if there are characters left to read by this 
						binary reader. @c false otherwise.
		 */
		[[nodiscard]]
		bool ContainsChars() const noexcept {
			return m_pos < m_end;
		}

		/**
		 Reads a @c DataT element.

		 @tparam		DataT
						The data type.
		 @return		The @c DataT element read.
		 @throws		Exception
						Failed to read a @c DataT element.
		 */
		template< typename DataT >
		const DataT Read();
		
		/**
		 Reads an array of @c DataT elements.

		 @tparam		DataT
						The data type.
		 @param			count
						The number of @c DataT elements to read.
		 @return		A pointer to the array of @c DataT element read.
		 @throws		Exception
						Failed to read @c count @c DataT elements.
		 */
		template< typename DataT >
		const DataT* ReadArray(size_t count);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts reading.

		 @throws		Exception
						Failed to read from the given file.
		 */
		virtual void ReadData() = 0;

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
		const U8* m_pos;

		/**
		 A pointer to the end position of this binary reader.
		 */
		const U8* m_end;

		/**
		 A pointer to the data to read of this binary reader.
		 */
		UniquePtr< U8[] > m_data;
	};

	#pragma endregion
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_reader.tpp"

#pragma endregion