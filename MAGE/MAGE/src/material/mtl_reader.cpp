//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\mtl_reader.hpp"
#include "material\mtl_tokens.hpp"
#include "string\string_utils.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	HRESULT MTLReader::ParseLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_MTL_COMMENT_CHAR) {
			return S_OK;
		}

		if (str_equals(token, MAGE_MTL_TOKEN_MATERIAL_DECLARATION)) {
			m_material_buffer.push_back(Material());
			ParseMTLMaterialName();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_AMBIENT_REFLECTIVITY)) {
			ParseMTLAmbientReflectivity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DIFFUSE_REFLECTIVITY)) {
			ParseMTLDiffuseReflectivity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_REFLECTIVITY)) {
			ParseMTLSpecularReflectivity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_TRANSMISSION_FILTER)) {
			ParseMTLTransmissionFilter();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_EXPONENT)) {
			ParseMTLSpecularExponent();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_OPTICAL_DENSITY)) {
			ParseMTLOpticalDensity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE)) {
			ParseMTLDissolve();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		ParseLineRemaining();

		return S_OK;
	}

	void MTLReader::ParseMTLMaterialName() {
		m_material_buffer.back().m_name = ParseString();
	}

	void MTLReader::ParseMTLAmbientReflectivity() {
		m_material_buffer.back().m_ambient_reflectivity = ParseMTLSpectrum();
	}

	void MTLReader::ParseMTLDiffuseReflectivity() {
		m_material_buffer.back().m_diffuse_reflectivity = ParseMTLSpectrum();
	}

	void MTLReader::ParseMTLSpecularReflectivity() {
		m_material_buffer.back().m_specular_reflectivity = ParseMTLSpectrum();
	}

	void MTLReader::ParseMTLTransmissionFilter() {
		m_material_buffer.back().m_transmission_filter = ParseMTLSpectrum();
	}

	void MTLReader::ParseMTLSpecularExponent() {
		m_material_buffer.back().m_specular_exponent = ParseFloat();
	}

	void MTLReader::ParseMTLOpticalDensity() {
		m_material_buffer.back().m_index_of_refraction = ParseFloat();
	}

	void MTLReader::ParseMTLDissolve() {
		float dissolve;

		const char *token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		if (!token) {
			Error("%ls: line %u: no float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			dissolve = 0.0f;
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE_HALO)) {
			Warning("%ls: line %u: unsupported halo effect.", GetFilename().c_str(), GetCurrentLineNumber());
			dissolve = ParseFloat();
		}
		else if (StringToFloat(token, dissolve) == invalid_token) {
			Error("%ls: line %u: invalid float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			dissolve = 0.0f;
		}

		m_material_buffer.back().m_dissolve = dissolve;
	}

	RGBSpectrum MTLReader::ParseMTLSpectrum() {
		const char *token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);

		// No spectrum
		if (!token) {
			Error("%ls: line %u: no spectrum found.", GetFilename().c_str(), GetCurrentLineNumber());
			return RGBSpectrum();
		}

		// XYZ spectrum
		if (str_equals(token, MAGE_MTL_TOKEN_XYZ)) {
			const float x = ParseFloat();
			ParseResult pr;
			const float y = ParseOptionalFloat(x, &pr);
			const float z = (pr != valid_token) ? x : ParseFloat();
			return RGBSpectrum(XYZSpectrum(x, y, z));
		}

		// Custom spectrum
		if (str_equals(token, MAGE_MTL_TOKEN_SPECTRAL)) {
			Warning("%ls: line %u: unsupported custom spectrum.", GetFilename().c_str(), GetCurrentLineNumber());
			return RGBSpectrum();
		}

		// RGB spectrum
		float x;
		if (StringToFloat(token, x) != valid_token) {
			Error("%ls: line %u: invalid float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			x = 0.0f;
		}
		ParseResult pr;
		const float y = ParseOptionalFloat(x, &pr);
		const float z = (pr != valid_token) ? x : ParseFloat();
		return RGBSpectrum(x, y, z);
	}
}