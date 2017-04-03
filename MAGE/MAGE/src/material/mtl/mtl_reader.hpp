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

	class MTLReader : public LineReader {

	public:

		explicit MTLReader(vector< Material > &material_buffer)
			: LineReader(), m_material_buffer(material_buffer) {}
		virtual ~MTLReader() = default;

	protected:

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

		const RGBSpectrum ReadMTLSpectrum();
		SharedPtr< Texture > ReadMTLTexture();

	private:

		MTLReader(const MTLReader &reader) = delete;
		MTLReader(MTLReader &&reader) = delete;
		MTLReader &operator=(const MTLReader &reader) = delete;
		MTLReader &operator=(MTLReader &&reader) = delete;

		vector< Material > &m_material_buffer;
	};
}