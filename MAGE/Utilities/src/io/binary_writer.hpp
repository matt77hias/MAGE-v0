#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <filesystem>

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
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given big endian binary writer to this big endian binary 
		 writer.

		 @param[in]		writer
						A reference to a big endian binary writer to copy.
		 @return		A reference to the copy of the given big endian binary 
						writer (i.e. this big endian binary writer).
		 */
		BigEndianBinaryWriter& operator=(
			const BigEndianBinaryWriter& writer) = delete;

		/**
		 Moves the given big endian binary writer to this big endian binary writer.

		 @param[in]		writer
						A reference to a big endian binary writer to move.
		 @return		A reference to the moved big endian binary writer (i.e. 
						this big endian binary writer).
		 */
		BigEndianBinaryWriter& operator=(
			BigEndianBinaryWriter&& writer) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes to the file associated with the given path.

		 @param[in]		path
						The path.
		 @throws		Exception
						Failed to write to the file.
		 */
		void WriteToFile(std::filesystem::path path);

		/**
		 Returns the current path of this big endian binary writer.

		 @return		A reference to the current path of this big endian 
						binary writer.
		 */
		[[nodiscard]]
		const std::filesystem::path& GetPath() const noexcept {
			return m_path;
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
		 Constructs a big endian binary writer from the given big endian binary 
		 writer.

		 @param[in]		writer
						A reference to the big endian binary writer to copy.
		 */
		BigEndianBinaryWriter(const BigEndianBinaryWriter& writer) = delete;
		
		/**
		 Constructs a big endian binary writer by moving the given big endian 
		 binary writer.

		 @param[in]		writer
						A reference to the big endian binary writer to move.
		 */
		BigEndianBinaryWriter(BigEndianBinaryWriter&& writer) noexcept;

		/**
		 Destructs this big endian binary writer.
		 */
		~BigEndianBinaryWriter();

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Writes the given data.

		 @tparam		DataT
						The data type.
		 @param[in]		data
						A reference to the data.
		 @throws		Exception
						Failed to write the given data.
		 */
		template< typename DataT >
		void Write(const DataT& data);
		
		/**
		 Writes the given data array.

		 @tparam		DataT
						The data type.
		 @param[in]		data
						The data array.
		 @throws		Exception
						Failed to write the given data.
		 */
		template< typename DataT >
		void WriteArray(gsl::span< const DataT > data);

		/**
		 Writes the given character.

		 @param[in]		c
						The character to write.
		 @throws		Exception
						Failed to write the given character.
		 */
		void WriteCharacter(char c);
		
		/**
		 Writes the given string.

		 @param[in]		str
						A pointer to the first null-terminated byte string to 
						write.
		 @throws		Exception
						Failed to write the given string.
		 */
		void WriteString(NotNull< const_zstring > str);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		Exception
						Failed to write.
		 */
		virtual void WriteData() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the file stream of this big endian binary writer.
		 */
		UniqueFileStream m_file_stream;

		/**
		 The current path of this big endian binary writer.
		 */
		std::filesystem::path m_path;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_writer.tpp"

#pragma endregion