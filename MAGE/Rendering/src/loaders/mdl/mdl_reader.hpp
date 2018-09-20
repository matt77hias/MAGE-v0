#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "io\line_reader.hpp"
#include "resource\model\model_output.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage::rendering {
	// Forward declaration.
	class ResourceManager;
}

namespace mage::rendering::loader {

	/**
	 A class of MDL file readers for reading models.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 */
	template< typename VertexT, typename IndexT >
	class MDLReader : private LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a MDL reader.

		 @param[in]		resource_manager
						A reference to the resource manager.
		 @param[in]		model_output
						A reference to the model output for storing the model
						data from file.
		 */
		explicit MDLReader(ResourceManager& resource_manager,
						   ModelOutput< VertexT, IndexT >& model_output);

		/**
		 Constructs a MDL reader from the given MDL reader.

		 @param[in]		reader
						A reference to the MDL reader to copy.
		 */
		MDLReader(const MDLReader& reader) = delete;

		/**
		 Constructs a MDL reader by moving the given MDL reader.

		 @param[in]		reader
						A reference to the MDL reader to move.
		 */
		MDLReader(MDLReader&& reader) noexcept;

		/**
		 Destructs this MDL reader.
		 */
		~MDLReader();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given MDL reader to this MDL reader.

		 @param[in]		reader
						A reference to a MDL reader to copy.
		 @return		A reference to the copy of the given MDL reader (i.e.
						this MDL reader).
		 */
		MDLReader& operator=(const MDLReader& reader) = delete;

		/**
		 Moves the given MDL reader to this MDL reader.

		 @param[in]		reader
						A reference to a MDL reader to move.
		 @return		A reference to the moved MDL reader (i.e. this MDL
						reader).
		 */
		MDLReader& operator=(MDLReader&& reader) = delete;

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
		 Pre-processes before reading the current file of this MDL reader.

		 @throws		Exception
						Failed to finish the pre-processing successfully.
		 */
		virtual void Preprocess() override;

		/**
		 Reads the current line of this MDL reader.

		 @throws		Exception
						Failed to the current line of this MDL reader.
		 */
		virtual void ReadLine() override;

		/**
		 Post-processes after reading the current file of this MDL reader.

		 @throws		Exception
						Failed to finish post-processing successfully.
		 */
		virtual void Postprocess() override;

		/**
		 Reads a Submodel definition.

		 @throws		Exception
						Failed to read a Submodel definition.
		 */
		void ReadMDLSubModel();

		/**
		 Reads a Material Library definition and imports the materials
		 corresponding to the model.

		 @throws		Exception
						Failed to read a Material Library definition.
		 @throws		Exception
						Failed to import the materials.
		 */
		void ReadMDLMaterialLibrary();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the resource manager of this MDL reader.
		 */
		ResourceManager& m_resource_manager;

		/**
		 A reference to the model output containing the model data of this MDL
		 reader.
		 */
		ModelOutput< VertexT, IndexT >& m_model_output;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_reader.tpp"

#pragma endregion