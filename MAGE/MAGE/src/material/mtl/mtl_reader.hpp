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
						A reference to a vector for storing the read materials from file.
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
		 @return		A reference to the copy of the given MTL reader
						(i.e. this MTL reader).
		 */
		MTLReader &operator=(const MTLReader &reader) = delete;

		/**
		 Moves the given MTL reader to this MTL reader.

		 @param[in]		reader
						A reference to a MTL reader to move.
		 @return		A reference to the moved MTL reader
						(i.e. this MTL reader).
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
		 Reads a Transmission Filter definition.

		 @throws		FormattedException
						Failed to read a Transmission Filter definition.
		 */
		void ReadMTLTransmissionFilter();

		/**
		 Reads an Ambient Reflectivity definition.

		 @throws		FormattedException
						Failed to read an Ambient Reflectivity definition.
		 @note			Ambient reflectivities are not supported, use 
						diffuse reflectivities instead.
		 */
		void ReadMTLAmbientReflectivity();

		/**
		 Reads a Diffuse Reflectivity definition.

		 @throws		FormattedException
						Failed to read a Diffuse Reflectivity definition.
		 */
		void ReadMTLDiffuseReflectivity();

		/**
		 Reads a Specular Reflectivity definition.

		 @throws		FormattedException
						Failed to read a Specular Reflectivity definition.
		 */
		void ReadMTLSpecularReflectivity();

		/**
		 Reads a Specular Exponent definition.

		 @throws		FormattedException
						Failed to read a Specular Exponent definition.
		 */
		void ReadMTLSpecularExponent();

		/**
		 Reads a Dissolve definition.

		 @throws		FormattedException
						Failed to read a Dissolve definition.
		 */
		void ReadMTLDissolve();

		/**
		 Reads an Optical Density definition.

		 @throws		FormattedException
						Failed to read an Optical Density definition.
		 */
		void ReadMTLOpticalDensity();

		/**
		 Reads an Ambient Reflectivity Texture definition.

		 @throws		FormattedException
						Failed to read Ambient Reflectivity Texture definition.
		 @note			Ambient reflectivity textures are not supported, use 
						diffuse reflectivity textures instead.
		 */
		void ReadMTLAmbientReflectivityTexture();

		/**
		 Reads a Diffuse Reflectivity Texture definition.

		 @throws		FormattedException
						Failed to read a Diffuse Reflectivity Texture definition.
		 */
		void ReadMTLDiffuseReflectivityTexture();

		/**
		 Reads a Specular Reflectivity Texture definition.

		 @throws		FormattedException
						Failed to read a Specular Reflectivity Texture definition.
		 */
		void ReadMTLSpecularReflectivityTexture();

		/**
		 Reads a Specular Exponent Texture definition.

		 @throws		FormattedException
						Failed to read a Specular Exponent Texture definition.
		 @note			Specular exponent textures are not supported, use the 
						alpha channel of specular reflectivity textures instead.
		 */
		void ReadMTLSpecularExponentTexture();

		/**
		 Reads a Dissolve Texture definition.

		 @throws		FormattedException
						Failed to read a Dissolve Texture definition.
		 @note			Dissolve textures are not supported, use the alpha channel 
						of diffuse reflectivity textures instead.
		 */
		void ReadMTLDissolveTexture();

		/**
		 Reads a Decal Texture definition.

		 @throws		FormattedException
						Failed to read a Decal Texture definition.
		 */
		void ReadMTLDecalTexture();

		/**
		 Reads a Displacement Texture definition.

		 @throws		FormattedException
						Failed to read a Displacement Texture definition.
		 */
		void ReadMTLDisplacementTexture();

		/**
		 Reads a Normal Texture definition.

		 @throws		FormattedException
						Failed to read a Normal Texture definition.
		 */
		void ReadMTLNormalTexture();

		/**
		 Reads a Bump Texture definition.

		 @throws		FormattedException
						Failed to read a Bump Texture definition.
		 @note			Bump textures are not supported, use normal textures instead.
		 */
		void ReadMTLBumpTexture();

		/**
		 Reads an Illumination Model definition.

		 @note			An illumination model is, if present,
						silently ignored.
		 @throws		FormattedException
						Failed to read an Illumination Model definition.
		 */
		void ReadMTLIlluminationModel();

		/**
		 Reads an RGB spectrum.

		 @return		The @c RGBSpectrum represented by the next token
						of this MTL reader.
		 @throws		FormattedException
						Failed to read a @c RGBSpectrum.
		 */
		const RGBSpectrum ReadMTLSpectrum();

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
		 A reference to a vector containing the read materials of this MTL reader.
		 */
		vector< Material > &m_material_buffer;
	};
}