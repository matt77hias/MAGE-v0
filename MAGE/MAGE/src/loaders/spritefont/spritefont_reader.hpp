#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\binary_reader.hpp"
#include "sprite\font\sprite_font_output.hpp"
#include "sprite\font\sprite_font_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of readers for reading SPRITEFONT files.
	 */
	class SpriteFontReader final : public BigEndianBinaryReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a SPRITEFONT reader.

		 @pre			@a device is not equal to @c nullptr.
		 @param[in]		device
						A pointer to the device.
		 @param[out]	output
						A reference to the sprite font output.
		 @param[in]		desc
						A reference to the sprite font descriptor.
		*/
		explicit SpriteFontReader(ID3D11Device5 *device, 
			SpriteFontOutput &output, const SpriteFontDescriptor &desc);
		
		/**
		 Constructs a SPRITEFONT reader from the given SPRITEFONT reader.

		 @param[in]		reader
						A reference to the SPRITEFONT reader to copy.
		 */
		SpriteFontReader(const SpriteFontReader &reader) = delete;

		/**
		 Constructs a SPRITEFONT reader by moving the given SPRITEFONT reader.

		 @param[in]		reader
						A reference to the SPRITEFONT reader to move.
		 */
		SpriteFontReader(SpriteFontReader &&reader);

		/**
		 Destructs this SPRITEFONT reader.
		 */
		virtual ~SpriteFontReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given SPRITEFONT reader to this SPRITEFONT reader.

		 @param[in]		reader
						A reference to a SPRITEFONT reader to copy.
		 @return		A reference to the copy of the given SPRITEFONT reader
						(i.e. this SPRITEFONT reader).
		 */
		SpriteFontReader &operator=(const SpriteFontReader &reader) = delete;

		/**
		 Moves the given SPRITEFONT reader to this SPRITEFONT reader.

		 @param[in]		reader
						A reference to a SPRITEFONT reader to move.
		 @return		A reference to the moved SPRITEFONT reader (i.e. this 
						SPRITEFONT reader).
		 */
		SpriteFontReader &operator=(SpriteFontReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts reading.

		 @throws		FormattedException
						Failed to read to the given file.
		 */
		virtual void Read() override;

		/**
		 Checks whether the header of the file is valid.

		 @return		@c true if the header of the file is valid. @c false 
						otherwise.
		 @throws		FormattedException
						Failed to read to the given file.
		 */
		bool IsHeaderValid();

		/**
		 Reads a texture.

		 @throws		FormattedException
						Failed to read a texture.
		 @throws		FormattedException
						Failed to read to the given file.
		 */
		void ReadTexture();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the rendering device of this SPRITEFONT reader.
		 */
		ID3D11Device5 * const m_device;

		/**
		 A reference to the sprite font output of this SPRITEFONT reader.
		 */
		SpriteFontOutput &m_output;

		/**
		 A reference to the sprite font descriptor of this SPRITEFONT reader.
		 */
		const SpriteFontDescriptor &m_desc;
	};
}