#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "resource\rendering_resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	/**
	 A class of MTL file readers for reading materials.
	 */
	class MTLReader final : private LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a MTL reader.
		 
		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		material_buffer
						A reference to a vector for storing the read materials 
						from file.
		 */
		explicit MTLReader(ResourceManager& resource_manager, 
						   std::vector< Material >& material_buffer);

		/**
		 Constructs a MTL reader from the given MTL reader.

		 @param[in]		reader
						A reference to the MTL reader to copy.
		 */
		MTLReader(const MTLReader& reader) = delete;

		/**
		 Constructs a MTL reader by moving the given MTL reader.

		 @param[in]		reader
						A reference to the MTL reader to move.
		 */
		MTLReader(MTLReader&& reader) noexcept;

		/**
		 Destructs this MTL reader.
		 */
		~MTLReader();

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
		MTLReader& operator=(const MTLReader& reader) = delete;

		/**
		 Moves the given MTL reader to this MTL reader.

		 @param[in]		reader
						A reference to a MTL reader to move.
		 @return		A reference to the moved MTL reader (i.e. this MTL 
						reader).
		 */
		MTLReader& operator=(MTLReader&& reader) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		using LineReader::ReadFromFile;

		using LineReader::ReadFromMemory;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Reads the current line of this MTL reader.

		 @throws		Exception
						Failed to the current line of this MTL reader.
		 */
		virtual void ReadLine() override;

		/**
		 Reads a Material Name definition.

		 @throws		Exception
						Failed to read a Material Name definition.
		 */
		void ReadMTLMaterialName();

		/**
		 Reads a Base Color definition.

		 @throws		Exception
						Failed to read a Base Color definition.
		 */
		void ReadMTLBaseColor();

		/**
		 Reads a Roughness definition.

		 @throws		Exception
						Failed to read a Roughness definition.
		 */
		void ReadMTLRoughness();

		/**
		 Reads a Metalness definition.

		 @throws		Exception
						Failed to read a Metalness definition.
		 */
		void ReadMTLMetalness();

		/**
		 Reads a Radiance definition.

		 @throws		Exception
						Failed to read a Radiance definition.
		 */
		void ReadMTLRadiance();

		/**
		 Reads a Base Color Texture definition.

		 @throws		Exception
						Failed to read a Base Color Texture definition.
		 */
		void ReadMTLBaseColorTexture();

		/**
		 Reads a Material Texture definition.

		 @throws		Exception
						Failed to read a Material Texture definition.
		 */
		void ReadMTLMaterialTexture();

		/**
		 Reads a Normal Texture definition.

		 @throws		Exception
						Failed to read a Normal Texture definition.
		 */
		void ReadMTLNormalTexture();

		/**
		 Reads an sRGB spectrum.

		 @return		The sRGB spectrum represented by the next token of 
						this MTL reader.
		 @throws		Exception
						Failed to read a sRGB spectrum.
		 */
		[[nodiscard]]
		const SRGB ReadMTLSRGB();

		/**
		 Reads an sRGBA spectrum.

		 @return		The sRGBA spectrum represented by the next token of 
						this MTL reader.
		 @throws		Exception
						Failed to read a sRGBA spectrum.
		 */
		[[nodiscard]]
		const SRGBA ReadMTLSRGBA();

		/**
		 Reads a texture.

		 @return		A pointer to the texture represented by the next token
						of this MTL reader.
		 @throws		Exception
						Failed to read a texture.
		 */
		[[nodiscard]]
		TexturePtr ReadMTLTexture();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to resource manager of this MTL reader.
		 */
		ResourceManager& m_resource_manager;

		/**
		 A reference to a vector containing the read materials of this MTL 
		 reader.
		 */
		std::vector< Material >& m_material_buffer;
	};
}