#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\io\writer.hpp"
#include "model\model_output.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of MDL file writers for writing models.

	 @tparam		VertexT
					The vertex type.
	 */
	template < typename VertexT >
	class MDLWriter final : public Writer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a MDL writer.

		 @param[in]		model_output
						A reference to the model output containing the model 
						data.
		 */
		explicit MDLWriter(const ModelOutput< VertexT > &model_output);

		/**
		 Constructs a MDL writer from the given MDL writer.

		 @param[in]		writer
						A reference to the MDL writer to copy.
		 */
		MDLWriter(const MDLWriter &writer) = delete;

		/**
		 Constructs a MDL writer by moving the given MDL writer.

		 @param[in]		writer
						A reference to the MDL writer to move.
		 */
		MDLWriter(MDLWriter &&writer);

		/**
		 Destructs this MDL writer.
		 */
		virtual ~MDLWriter();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given MDL writer to this MDL writer.

		 @param[in]		writer
						A reference to a MDL writer to copy.
		 @return		A reference to the copy of the given MDL writer (i.e. 
						this MDL writer).
		 */
		MDLWriter &operator=(const MDLWriter &writer) = delete;

		/**
		 Moves the given MDL writer to this MDL writer.

		 @param[in]		writer
						A reference to a MDL writer to move.
		 @return		A reference to the moved MDL writer (i.e. this MDL 
						writer).
		 */
		MDLWriter &operator=(MDLWriter &&writer) = delete;

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

		/**
		 Writes and exports the mesh corresponding to the model.

		 @throws		FormattedException
						Failed to write.
		 @throws		FormattedException
						Failed to export the mesh corresponding 
						to the model to file.
		 */
		void ExportMesh();

		/**
		 Writes the materials corresponding to the model.

		 @throws		FormattedException
						Failed to write.
		 */
		void WriteMaterials();

		/**
		 Writes the model parts corresponding to the model.

		 @throws		FormattedException
						Failed to write.
		 */
		void WriteModelParts();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A reference to the model output containing the model data of this MDL 
		 writer.
		 */
		const ModelOutput< VertexT > &m_model_output;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mdl\mdl_writer.tpp"

#pragma endregion