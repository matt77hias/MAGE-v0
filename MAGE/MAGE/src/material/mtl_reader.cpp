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

	HRESULT MTLReader::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_MTL_COMMENT_CHAR) {
			return S_OK;
		}

		if (str_equals(token, MAGE_MTL_TOKEN_MATERIAL_DECLARATION)) {
			m_material_buffer.push_back(Material());
			ReadMTLMaterialName();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_AMBIENT_REFLECTIVITY)) {
			ReadMTLAmbientReflectivity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DIFFUSE_REFLECTIVITY)) {
			ReadMTLDiffuseReflectivity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_REFLECTIVITY)) {
			ReadMTLSpecularReflectivity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_TRANSMISSION_FILTER)) {
			ReadMTLTransmissionFilter();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_EXPONENT)) {
			ReadMTLSpecularExponent();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_OPTICAL_DENSITY)) {
			ReadMTLOpticalDensity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE)) {
			ReadMTLDissolve();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		ReadLineRemaining();

		return S_OK;
	}

	void MTLReader::ReadMTLMaterialName() {
		m_material_buffer.back().m_name = ReadString();
	}

	void MTLReader::ReadMTLAmbientReflectivity() {
		m_material_buffer.back().m_ambient_reflectivity = ReadMTLSpectrum();
	}

	void MTLReader::ReadMTLDiffuseReflectivity() {
		m_material_buffer.back().m_diffuse_reflectivity = ReadMTLSpectrum();
	}

	void MTLReader::ReadMTLSpecularReflectivity() {
		m_material_buffer.back().m_specular_reflectivity = ReadMTLSpectrum();
	}

	void MTLReader::ReadMTLTransmissionFilter() {
		m_material_buffer.back().m_transmission_filter = ReadMTLSpectrum();
	}

	void MTLReader::ReadMTLSpecularExponent() {
		m_material_buffer.back().m_specular_exponent = ReadFloat();
	}

	void MTLReader::ReadMTLOpticalDensity() {
		m_material_buffer.back().m_index_of_refraction = ReadFloat();
	}

	void MTLReader::ReadMTLDissolve() {
		float dissolve;

		const char *token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);
		if (!token) {
			Error("%ls: line %u: no float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			dissolve = 0.0f;
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE_HALO)) {
			Warning("%ls: line %u: unsupported halo effect.", GetFilename().c_str(), GetCurrentLineNumber());
			dissolve = ReadFloat();
		}
		else if (StringToFloat(token, dissolve) == invalid_token) {
			Error("%ls: line %u: invalid float value found.", GetFilename().c_str(), GetCurrentLineNumber());
			dissolve = 0.0f;
		}

		m_material_buffer.back().m_dissolve = dissolve;
	}

	RGBSpectrum MTLReader::ReadMTLSpectrum() {
		const char *token = strtok_s(nullptr, GetDelimiters().c_str(), &m_context);

		// No spectrum
		if (!token) {
			Error("%ls: line %u: no spectrum found.", GetFilename().c_str(), GetCurrentLineNumber());
			return RGBSpectrum();
		}

		// XYZ spectrum
		if (str_equals(token, MAGE_MTL_TOKEN_XYZ)) {
			const float x = ReadFloat();
			TokenResult pr;
			const float y = ReadOptionalFloat(x, &pr);
			const float z = (pr != valid_token) ? x : ReadFloat();
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
		TokenResult pr;
		const float y = ReadOptionalFloat(x, &pr);
		const float z = (pr != valid_token) ? x : ReadFloat();
		return RGBSpectrum(x, y, z);
	}
}