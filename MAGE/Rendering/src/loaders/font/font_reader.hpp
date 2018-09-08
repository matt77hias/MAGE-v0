#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\binary_reader.hpp"
#include "resource\font\sprite_font_output.hpp"
#include "resource\font\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 A class of readers for reading FONT files.
	 */
	class SpriteFontReader : private BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a FONT reader.

		 @param[in]		device
						A reference to the device.
		 @param[out]	output
						A reference to the sprite font output.
		 @param[in]		desc
						A reference to the sprite font descriptor.
		*/
		explicit SpriteFontReader(ID3D11Device& device, 
								  SpriteFontOutput& output, 
								  const SpriteFontDescriptor& desc);
		
		/**
		 Constructs a FONT reader from the given FONT reader.

		 @param[in]		reader
						A reference to the FONT reader to copy.
		 */
		SpriteFontReader(const SpriteFontReader& reader) = delete;

		/**
		 Constructs a FONT reader by moving the given FONT reader.

		 @param[in]		reader
						A reference to the FONT reader to move.
		 */
		SpriteFontReader(SpriteFontReader&& reader) noexcept;

		/**
		 Destructs this FONT reader.
		 */
		~SpriteFontReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given FONT reader to this FONT reader.

		 @param[in]		reader
						A reference to a FONT reader to copy.
		 @return		A reference to the copy of the given FONT reader
						(i.e. this FONT reader).
		 */
		SpriteFontReader& operator=(const SpriteFontReader& reader) = delete;

		/**
		 Moves the given FONT reader to this FONT reader.

		 @param[in]		reader
						A reference to a FONT reader to move.
		 @return		A reference to the moved FONT reader (i.e. this 
						FONT reader).
		 */
		SpriteFontReader& operator=(SpriteFontReader&& reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		using BigEndianBinaryReader::ReadFromFile;

		using BigEndianBinaryReader::ReadFromMemory;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts reading.

		 @throws		Exception
						Failed to read from the given file.
		 */
		virtual void ReadData() override;

		/**
		 Checks whether the header of the file is valid.

		 @return		@c true if the header of the file is valid. @c false 
						otherwise.
		 @throws		Exception
						Failed to read to the given file.
		 */
		[[nodiscard]]
		bool IsHeaderValid();

		/**
		 Reads a texture.

		 @throws		Exception
						Failed to read a texture.
		 @throws		Exception
						Failed to read to the given file.
		 */
		void ReadTexture();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the rendering device of this FONT reader.
		 */
		ID3D11Device& m_device;

		/**
		 A reference to the sprite font output of this FONT reader.
		 */
		SpriteFontOutput& m_output;

		/**
		 A reference to the sprite font descriptor of this FONT reader.
		 */
		const SpriteFontDescriptor& m_desc;
	};
}