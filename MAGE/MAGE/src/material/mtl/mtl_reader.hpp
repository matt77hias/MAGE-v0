#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"
#include "collection\collection.hpp"
#include "string\line_reader.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class MTLReader final : public LineReader {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MTLReader(vector< Material > &material_buffer)
			: LineReader(), m_material_buffer(material_buffer) {}
		MTLReader(const MTLReader &reader) = delete;
		MTLReader(MTLReader &&reader) = delete;
		virtual ~MTLReader() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		MTLReader &operator=(const MTLReader &reader) = delete;
		MTLReader &operator=(MTLReader &&reader) = delete;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual HRESULT ReadLine(char *line) override;

		void ReadMTLMaterialName();
		void ReadMTLTransmissionFilter();
		void ReadMTLAmbientReflectivity();
		void ReadMTLDiffuseReflectivity();
		void ReadMTLSpecularReflectivity();
		void ReadMTLSpecularExponent();
		void ReadMTLDissolve();
		void ReadMTLOpticalDensity();

		void ReadMTLAmbientReflectivityTexture();
		void ReadMTLDiffuseReflectivityTexture();
		void ReadMTLSpecularReflectivityTexture();
		void ReadMTLSpecularExponentTexture();
		void ReadMTLDissolveTexture();
		void ReadMTLDecalTexture();
		void ReadMTLDisplacementTexture();
		void ReadMTLBumpTexture();

		void ReadMTLIlluminationModel();

		const RGBSpectrum ReadMTLSpectrum();
		SharedPtr< Texture > ReadMTLTexture();

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		vector< Material > &m_material_buffer;
	};
}