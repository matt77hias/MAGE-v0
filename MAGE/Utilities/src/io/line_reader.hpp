#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "exception\exception.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <istream>
#include <regex>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of line readers for reading (non-binary) text files line by line.
	 */
	class LineReader {

	public:

		//---------------------------------------------------------------------
		// Class Member Types
		//---------------------------------------------------------------------

		/**
		 The selection function type for extracting one @a std::ssub_match from 
		 a given @a std::smatch.
		 */
		using SelectionFunction 
			= std::function< const std::ssub_match(const std::smatch&) >;

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The default (line) regex for line readers.
		 */
		static const std::regex s_default_regex;

		/**
		 The default selection function for line readers.
		 */
		static const SelectionFunction s_default_selection_function;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given line reader to this line reader.

		 @param[in]		reader
						A reference to a line reader to copy.
		 @return		A reference to the copy of the given line reader (i.e. 
						this line reader).
		 */
		LineReader& operator=(const LineReader& reader) = delete;

		/**
		 Moves the given line reader to this line reader.

		 @param[in]		reader
						A reference to a line reader to move.
		 @return		A reference to the moved line reader (i.e. this line 
						reader).
		 */
		LineReader& operator=(LineReader&& reader) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads from the file associated with the given path.

		 @param[in]		path
						The path.
		 @param[in]		regex
						The (line) regex.
		 @param[in]		selection_function
						The selection function.
		 @throws		Exception
						Failed to read from the file.
		 */
		void ReadFromFile(std::filesystem::path path, 
						  std::regex regex = s_default_regex, 
						  SelectionFunction selection_function 
						  = s_default_selection_function);
		
		/**
		 Reads from the given input string.

		 @param[in]		input
						A reference to the input string.
		 @param[in]		regex
						The (line) regex.
		 @param[in]		selection_function
						The selection function.
		 @throws		Exception
						Failed to read from the given input string.
		 */
		void ReadFromMemory(const std::string &input,
							std::regex regex = s_default_regex,
							SelectionFunction selection_function
							= s_default_selection_function);

	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a line reader.
		 */
		LineReader();

		/**
		 Constructs a line reader from the given line reader.

		 @param[in]		reader
						A reference to the line reader to copy.
		 */
		LineReader(const LineReader& reader) = delete;

		/**
		 Constructs a line reader by moving the given line reader.

		 @param[in]		reader
						A reference to the line reader to move.
		 */
		LineReader(LineReader&& reader) noexcept;

		/**
		 Destructs this line reader.
		 */
		~LineReader();

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the current path of this line reader.

		 @return		A reference to the current path of this line reader.
		 */
		[[nodiscard]]
		const std::filesystem::path& GetPath() const noexcept {
			return m_path;
		}

		/**
		 Returns the current line number of this line reader.

		 @return		The current line number of this line reader.
		 */
		[[nodiscard]]
		U32 GetCurrentLineNumber() const noexcept {
			return m_line_number;
		}
		
		/**
		 Reads and converts the current token of this line reader to 
		 @c T value.

		 @tparam		T
						The data type.
		 @return		The @c T represented by the current token of this line 
						reader.
		 @throws		Exception
						There is no current token or the current token does not 
						represent a @c T value.
		 */
		template< typename T >
		const T Read();

		/**
		 Reads and converts the current @c N tokens of this line reader to an 
		 @c Array.

		 @@tparam		T
						The data type.
		 @tparam		N
						The number of values in the array.
		 @tparam		A
						The alignment of the array.
		 @return		The @c Array represented by the current @c N tokens of 
						this line reader.
		 @throws		Exception
						There are no @c N current tokens or the current 
						@c N tokens do not represent a @c T value.
		 */
		template< typename T, std::size_t N, size_t A = alignof(T) >
		const Array< T, N, A > Read();

		/**
		 Reads the remaining tokens of the current line of this line reader.
		 */
		void ReadRemainingTokens();

		/**
		 Checks whether the current token of this line reader is a @c T value.

		 @tparam		T
						The data type.
		 @return		@c true if the current token of this line reader is a 
						@c T value. @c false otherwise.
		 */
		template< typename T >
		[[nodiscard]]
		bool Contains() const noexcept;

		/**
		 Checks whether this line reader has a current token.

		 @return		@c true if this line reader has a current token. 
						@c false otherwise.
		 */
		[[nodiscard]]
		bool ContainsTokens() const noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Pre-processes before reading.

		 @throws		Exception
						Failed to finish the pre-processing successfully.
		 */
		virtual void Preprocess();

		/**
		 Processes the given input stream (line by line).

		 @param[in]		stream
						A reference to the input stream.
		 @throws		Exception
						Failed to process the given input stream.
		 */
		void Process(std::istream& stream);

		/**
		 Reads the current line of this line reader.

		 @throws		Exception
						Failed to the current line of this line reader.
		 */
		virtual void ReadLine() = 0;

		/**
		 Post-processes after reading.

		 @throws		Exception
						Failed to finish post-processing successfully.
		 */
		virtual void Postprocess();

		/**
		 Returns the current token of this line reader.

		 @return		The current token of this line reader.
		 */
		[[nodiscard]]
		const std::string_view GetCurrentToken() const noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The current (line) regex of this line reader.
		 */
		std::regex m_regex;

		/**
		 The function for selecting the target submatch from the match of the 
		 regular expression represented by the regex of this strategy.
		 */
		SelectionFunction m_selection_function;

		/**
		 The current path of this line reader.
		 */
		std::filesystem::path m_path;

		/**
		 An iterator to the current token of the current line of this line 
		 reader.
		 */
		std::sregex_iterator m_iterator;

		/**
		 The current line number of this line reader.
		 */
		U32 m_line_number;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.tpp"

#pragma endregion