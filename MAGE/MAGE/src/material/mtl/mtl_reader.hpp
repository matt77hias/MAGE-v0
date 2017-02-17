#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\line_reader.hpp"
#include "collection\collection.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class MTLReader : public LineReader {

	public:

		MTLReader(vector< Material > &material_buffer)
			: LineReader(), m_material_buffer(material_buffer) {}
		virtual ~MTLReader() = default;

	protected:

		virtual HRESULT ReadLine(char *line) override;

		void ReadMTLMaterialName();
		void ReadMTLAmbientReflectivity();
		void ReadMTLDiffuseReflectivity();
		void ReadMTLSpecularReflectivity();
		void ReadMTLTransmissionFilter();
		void ReadMTLSpecularExponent();
		void ReadMTLOpticalDensity();
		void ReadMTLDissolve();

		RGBSpectrum ReadMTLSpectrum();

	private:

		MTLReader(const MTLReader &reader) = delete;
		MTLReader &operator=(const MTLReader &reader) = delete;

		vector< Material > &m_material_buffer;
	};
}