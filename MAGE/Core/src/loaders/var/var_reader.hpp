#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "resource\script\variable_value.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <map>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::loader {

	/**
	 A class of VAR file readers for reading variable scripts.
	 */
	class VARReader final : private LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a VAR reader.

		 @param[in]		variable_buffer
						A reference to a map for storing the read variables 
						from file.
		 */
		explicit VARReader(std::map< string, Value >& variable_buffer);
		
		/**
		 Constructs a VAR reader from the given VAR reader.

		 @param[in]		reader
						A reference to the VAR reader to copy.
		 */
		VARReader(const VARReader& reader) = delete;
		
		/**
		 Constructs a VAR reader by moving the given VAR reader.

		 @param[in]		reader
						A reference to the VAR reader to move.
		 */
		VARReader(VARReader&& reader) noexcept;

		/**
		 Destructs this VAR reader.
		 */
		~VARReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given VAR reader to this VAR reader.

		 @param[in]		reader
						A reference to a VAR reader to copy.
		 @return		A reference to the copy of the given VAR reader (i.e. 
						this VAR reader).
		 */
		VARReader& operator=(const VARReader& reader) = delete;

		/**
		 Moves the given VAR reader to this VAR reader.

		 @param[in]		reader
						A reference to a VAR reader to move.
		 @return		A reference to the moved VAR reader (i.e. this VAR 
						reader).
		 */
		VARReader& operator=(VARReader&& reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		using LineReader::ReadFromFile;

		using LineReader::ReadFromMemory;

		using LineReader::GetPath;

		using LineReader::GetDelimiters;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads the given line.

		 @param[in,out] line
						A pointer to the null-terminated string to read.
		 @throws		Exception
						Failed to read the given line.
		 */
		virtual void ReadLine(NotNull< zstring > line) override;

		/**
		 Reads a Bool variable definition.

		 @throws		Exception
						Failed to read a bool variable definition.
		 */
		void ReadVARBool();

		/**
		 Reads an Int variable definition.

		 @throws		Exception
						Failed to read an int variable definition.
		 */
		void ReadVARInt();

		/**
		 Reads an Int2 variable definition.

		 @throws		Exception
						Failed to read an int2 variable definition.
		 */
		void ReadVARInt2();

		/**
		 Reads an Int variable definition.

		 @throws		Exception
						Failed to read an int3 variable definition.
		 */
		void ReadVARInt3();

		/**
		 Reads a Float variable definition.

		 @throws		Exception
						Failed to read a float variable definition.
		 */
		void ReadVARFloat();

		/**
		 Reads a Float2 variable definition.

		 @throws		Exception
						Failed to read a float2 variable definition.
		 */
		void ReadVARFloat2();

		/**
		 Reads a Float3 variable definition.

		 @throws		Exception
						Failed to read a float3 variable definition.
		 */
		void ReadVARFloat3();

		/**
		 Reads a Float4 variable definition.

		 @throws		Exception
						Failed to read a float4 variable definition.
		 */
		void ReadVARFloat4();

		/**
		 Reads a String variable definition.

		 @throws		Exception
						Failed to read a string variable definition.
		 */
		void ReadVARString();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a map containing the read variables of this VAR reader.
		 */
		std::map< string, Value >& m_variable_buffer;
	};
}