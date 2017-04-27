#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\writer.hpp"
#include "collection\collection.hpp"
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of VS file writers for writing variable scripts.
	 */
	class VSWriter final : public Writer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a writer.

		 @param[in]		variable_buffer
						A reference to a vector containing the variables to write
						to file.
		 */
		explicit VSWriter(const vector< Variable > &variable_buffer)
			: Writer(), m_variable_buffer(variable_buffer) {}
		
		/**
		 Constructs a VS writer from the given VS writer.

		 @param[in]		writer
						A reference to the VS writer to copy.
		 */
		VSWriter(const VSWriter &writer) = delete;

		/**
		 Constructs a VS writer by moving the given VS writer.

		 @param[in]		writer
						A reference to the VS writer to move.
		 */
		VSWriter(VSWriter &&writer) = delete;

		/**
		 Destructs this VS writer.
		 */
		virtual ~VSWriter() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given VS writer to this VS writer.

		 @param[in]		writer
						A reference to a VS writer to copy.
		 @return		A reference to the copy of the given VS writer
						(i.e. this VS writer).
		 */
		VSWriter &operator=(const VSWriter &writer) = delete;

		/**
		 Moves the given VS writer to this VS writer.

		 @param[in]		writer
						A reference to a VS writer to move.
		 @return		A reference to the moved VS writer
						(i.e. this VS writer).
		 */
		VSWriter &operator=(VSWriter &&writer) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		FormattedException
						Failed to write.
		 */
		virtual void Write() override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a vector containing the variables to write by this VS writer.
		 */
		const vector< Variable > &m_variable_buffer;
	};
}