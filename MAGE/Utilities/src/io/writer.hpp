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
	 A class of writers for writing (non-binary) text files.
	 */
	class Writer {

	public:

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given writer to this writer.

		 @param[in]		writer
						A reference to a writer to copy.
		 @return		A reference to the copy of the given writer (i.e. this 
						writer).
		 */
		Writer& operator=(const Writer& writer) = delete;

		/**
		 Moves the given writer to this writer.

		 @param[in]		writer
						A reference to a writer to move.
		 @return		A reference to the moved writer (i.e. this writer).
		 */
		Writer& operator=(Writer&& writer) noexcept;

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

	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a writer.
		 */
		Writer();

		/**
		 Constructs a writer from the given writer.

		 @param[in]		writer
						A reference to the writer to copy.
		 */
		Writer(const Writer& writer) = delete;

		/**
		 Constructs a writer by moving the given writer.

		 @param[in]		writer
						A reference to the writer to move.
		 */
		Writer(Writer&& writer) noexcept;

		/**
		 Destructs this writer.
		 */
		~Writer();

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the current path of this writer.

		 @return		A reference to the current path of this writer.
		 */
		[[nodiscard]]
		const std::filesystem::path& GetPath() const noexcept {
			return m_path;
		}

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
						A pointer to the null-terminated string to write.
		 @throws		Exception
						Failed to write the given string.
		 */
		void WriteString(NotNull< const_zstring > str);
		
		/**
		 Writes the given string and ends the current line.

		 @param[in]		str
						A pointer to the null-terminated string to write.
		 @throws		Exception
						Failed to write the given string.
		 */
		void WriteStringLine(NotNull< const_zstring > str);
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		Exception
						Failed to write.
		 */
		virtual void Write() = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the file stream of this writer.
		 */
		UniqueFileStream m_file_stream;

		/**
		 The current path of this writer.
		 */
		std::filesystem::path m_path;
	};
}