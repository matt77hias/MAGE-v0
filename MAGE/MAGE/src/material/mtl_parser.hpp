//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\parsing.hpp"
#include "collection\collection.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_MTL_COMMENT_CHAR '#'
#define MAGE_MTL_TOKEN_MATERIAL_DECLARATION "newmtl"
#define MAGE_MTL_TOKEN_XYZ "xyz"
#define MAGE_MTL_TOKEN_SPECTRAL "spectral"
#define MAGE_MTL_TOKEN_AMBIENT_REFLECTIVITY "Ka"
#define MAGE_MTL_TOKEN_DIFFUSE_REFLECTIVITY "Kd"
#define MAGE_MTL_TOKEN_SPECULAR_REFLECTIVITY "Ks"
#define MAGE_MTL_TOKEN_TRANSMISSION_FILTER "Tf"
#define MAGE_MTL_TOKEN_SPECULAR_EXPONENT "Ns"
#define MAGE_MTL_TOKEN_OPTICAL_DENSITY "Ni"
#define MAGE_MTL_TOKEN_DISSOLVE "d"
#define MAGE_MTL_TOKEN_DISSOLVE_HALO "-halo"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	class MTLParser : public LineParser {

	public:

		MTLParser(vector< Material > &material_buffer)
			: LineParser(), m_material_buffer(material_buffer) {}
		virtual ~MTLParser() = default;

	protected:

		virtual HRESULT ParseLine(char *line) override;

		void ParseMTLMaterialName();
		void ParseMTLAmbientReflectivity();
		void ParseMTLDiffuseReflectivity();
		void ParseMTLSpecularReflectivity();
		void ParseMTLTransmissionFilter();
		void ParseMTLSpecularExponent();
		void ParseMTLOpticalDensity();
		void ParseMTLDissolve();

		RGBSpectrum ParseMTLSpectrum();

	private:

		MTLParser(const MTLParser &parser) = delete;
		MTLParser &operator=(const MTLParser &parser) = delete;

		vector< Material > &m_material_buffer;
	};
}