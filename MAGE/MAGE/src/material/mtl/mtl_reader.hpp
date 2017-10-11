#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\line_reader.hpp"
#include "material\material.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of MTL file readers for reading materials.
	 */
	class MTLReader final : public LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 A construct a MTL reader.
		 
		 @param[in]		material_buffer
						A reference to a vector for storing the read materials 
						from file.
		 */
		explicit MTLReader(vector< Material > &material_buffer);

		/**
		 Constructs a MTL reader from the given MTL reader.

		 @param[in]		reader
						A reference to the MTL reader to copy.
		 */
		MTLReader(const MTLReader &reader) = delete;

		/**
		 Constructs a MTL reader by moving the given MTL reader.

		 @param[in]		reader
						A reference to the MTL reader to move.
		 */
		MTLReader(MTLReader &&reader);

		/**
		 Destructs this MTL reader.
		 */
		virtual ~MTLReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given MTL reader to this MTL reader.

		 @param[in]		reader
						A reference to a MTL reader to copy.
		 @return		A reference to the copy of the given MTL reader (i.e. 
						this MTL reader).
		 */
		MTLReader &operator=(const MTLReader &reader) = delete;

		/**
		 Moves the given MTL reader to this MTL reader.

		 @param[in]		reader
						A reference to a MTL reader to move.
		 @return		A reference to the moved MTL reader (i.e. this MTL 
						reader).
		 */
		MTLReader &operator=(MTLReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads the given line.

		 @pre			@a line is not equal to @c nullptr.
		 @param[in,out] line
						A pointer to the null-terminated byte string to read.
		 @throws		FormattedException
						Failed to read the given line.
		 */
		virtual void ReadLine(char *line) override;

		/**
		 Reads a Material Name definition.

		 @throws		FormattedException
						Failed to read a Material Name definition.
		 */
		void ReadMTLMaterialName();

		/**
		 Reads a Base Color definition.

		 @throws		FormattedException
						Failed to read a Base Color definition.
		 */
		void ReadMTLBaseColor();

		/**
		 Reads a Roughness definition.

		 @throws		FormattedException
						Failed to read a Roughness definition.
		 */
		void ReadMTLRoughness();

		/**
		 Reads a Metalness definition.

		 @throws		FormattedException
						Failed to read a Metalness definition.
		 */
		void ReadMTLMetalness();

		/**
		 Reads a Base Color Texture definition.

		 @throws		FormattedException
						Failed to read a Base Color Texture definition.
		 */
		void ReadMTLBaseColorTexture();

		/**
		 Reads a Material Texture definition.

		 @throws		FormattedException
						Failed to read a Material Texture definition.
		 */
		void ReadMTLMaterialTexture();

		/**
		 Reads a Normal Texture definition.

		 @throws		FormattedException
						Failed to read a Normal Texture definition.
		 */
		void ReadMTLNormalTexture();

		/**
		 Reads an RGB spectrum.

		 @return		The @c RGBSpectrum represented by the next token of this 
						MTL reader.
		 @throws		FormattedException
						Failed to read a @c RGBSpectrum.
		 */
		const RGBSpectrum ReadMTLRGBSpectrum();

		/**
		 Reads an RGBA spectrum.

		 @return		The @c RGBASpectrum represented by the next token of 
						this MTL reader.
		 @throws		FormattedException
						Failed to read a @c RGBASpectrum.
		 */
		const RGBASpectrum ReadMTLRGBASpectrum();

		/**
		 Reads a texture.

		 @return		A pointer to the texture represented by the next token
						of this MTL reader.
		 @throws		FormattedException
						Failed to read a texture.
		 */
		SharedPtr< const Texture > ReadMTLTexture();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to a vector containing the read materials of this MTL 
		 reader.
		 */
		vector< Material > &m_material_buffer;
	};
}