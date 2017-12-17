#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\writer.hpp"
#include "scripting\variable.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 A class of VAR file writers for writing variable scripts.
	 */
	class VARWriter final : public Writer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a writer.

		 @param[in]		variable_buffer
						A reference to a map containing the variables to write 
						to file.
		 */
		explicit VARWriter(const std::map< string, Value > &variable_buffer);
		
		/**
		 Constructs a VAR writer from the given VAR writer.

		 @param[in]		writer
						A reference to the VAR writer to copy.
		 */
		VARWriter(const VARWriter &writer) = delete;

		/**
		 Constructs a VAR writer by moving the given VAR writer.

		 @param[in]		writer
						A reference to the VAR writer to move.
		 */
		VARWriter(VARWriter &&writer) noexcept;

		/**
		 Destructs this VAR writer.
		 */
		virtual ~VARWriter();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given VAR writer to this VAR writer.

		 @param[in]		writer
						A reference to a VAR writer to copy.
		 @return		A reference to the copy of the given VAR writer (i.e. 
						this VAR writer).
		 */
		VARWriter &operator=(const VARWriter &writer) = delete;

		/**
		 Moves the given VAR writer to this VAR writer.

		 @param[in]		writer
						A reference to a VAR writer to move.
		 @return		A reference to the moved VAR writer (i.e. this VAR 
						writer).
		 */
		VARWriter &operator=(VARWriter &&writer) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts writing.

		 @throws		Exception
						Failed to write.
		 */
		virtual void Write() override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a map containing the variables to write by this VAR 
		 writer.
		 */
		const std::map< string, Value > &m_variable_buffer;
	};
}