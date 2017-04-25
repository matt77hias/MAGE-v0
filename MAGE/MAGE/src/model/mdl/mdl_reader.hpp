#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_output.hpp"
#include "string\line_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	class MDLReader final : public LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MDLReader(ModelOutput< VertexT > &model_output)
			: LineReader(), m_model_output(model_output) {}
		MDLReader(const MDLReader &reader) = delete;
		MDLReader(MDLReader &&reader) = delete;
		virtual ~MDLReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		MDLReader &operator=(const MDLReader &reader) = delete;
		MDLReader &operator=(MDLReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Preprocess() override;
		virtual void ReadLine(char *line) override;

		void ImportMesh();
		void ReadMDLSubModel();
		void ReadMDLMaterialLibrary();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		ModelOutput< VertexT > &m_model_output;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_reader.tpp"

#pragma endregion