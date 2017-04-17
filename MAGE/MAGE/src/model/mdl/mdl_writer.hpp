#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\writer.hpp"
#include "model\model_output.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename VertexT >
	class MDLWriter final : public Writer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MDLWriter(const ModelOutput< VertexT > &model_output)
			: Writer(), m_model_output(model_output) {}
		MDLWriter(const MDLWriter &writer) = delete;
		MDLWriter(MDLWriter &&writer) = delete;
		virtual ~MDLWriter() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		MDLWriter &operator=(const MDLWriter &writer) = delete;
		MDLWriter &operator=(MDLWriter &&writer) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT Write() override;

		HRESULT ExportMesh();
		void WriteMaterials();
		void WriteModelParts();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		const ModelOutput< VertexT > &m_model_output;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\mdl\mdl_writer.tpp"

#pragma endregion