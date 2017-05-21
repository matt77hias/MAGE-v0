//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\mtl\mtl_reader.hpp"
#include "material\mtl\mtl_tokens.hpp"
#include "string\string_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	MTLReader::MTLReader(vector< Material > &material_buffer)
		: LineReader(), m_material_buffer(material_buffer) {}

	MTLReader::MTLReader(MTLReader &&reader) = default;

	MTLReader::~MTLReader() = default;

	void MTLReader::ReadLine(char *line) {
		m_context = nullptr;
		const char *token = strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_MTL_COMMENT_CHAR) {
			return;
		}

		if (str_equals(token, MAGE_MTL_TOKEN_MATERIAL_DECLARATION)) {
			ReadMTLMaterialName();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_TRANSMISSION_FILTER)) {
			ReadMTLTransmissionFilter();
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
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_EXPONENT)) {
			ReadMTLSpecularExponent();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE)) {
			ReadMTLDissolve();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_OPTICAL_DENSITY)) {
			ReadMTLOpticalDensity();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_AMBIENT_REFLECTIVITY_MAP)) {
			ReadMTLAmbientReflectivityTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DIFFUSE_REFLECTIVITY_MAP)) {
			ReadMTLDiffuseReflectivityTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_REFLECTIVITY_MAP)) {
			ReadMTLSpecularReflectivityTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_SPECULAR_EXPONENT_MAP)) {
			ReadMTLSpecularExponentTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISSOLVE_MAP)) {
			ReadMTLDissolveTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DECAL_MAP)) {
			ReadMTLDecalTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_DISPLACEMENT_MAP)) {
			ReadMTLDisplacementTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_NORMAL_MAP)) {
			ReadMTLNormalTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_BUMP_MAP)) {
			ReadMTLBumpTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_ILLUMINATION_MDL)) {
			ReadMTLIlluminationModel();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	void MTLReader::ReadMTLMaterialName() {
		const string material_name = ReadString();
		m_material_buffer.emplace_back(material_name);
	}

	void MTLReader::ReadMTLTransmissionFilter() {
		m_material_buffer.back().SetTransmissionFilter(ReadMTLSpectrum());
	}

	void MTLReader::ReadMTLAmbientReflectivity() {
		m_material_buffer.back().SetAmbientReflectivity(ReadMTLSpectrum());
	}

	void MTLReader::ReadMTLDiffuseReflectivity() {
		m_material_buffer.back().SetDiffuseReflectivity(ReadMTLSpectrum());
	}

	void MTLReader::ReadMTLSpecularReflectivity() {
		m_material_buffer.back().SetSpecularReflectivity(ReadMTLSpectrum());
	}

	void MTLReader::ReadMTLSpecularExponent() {
		m_material_buffer.back().SetSpecularExponent(ReadFloat());
	}

	void MTLReader::ReadMTLDissolve() {
		if (!HasFloat()) {
			const char *token = ReadChars();
			Warning("%ls: line %u: unsupported keyword token: %s.", GetFilename().c_str(), GetCurrentLineNumber(), token);
		}

		m_material_buffer.back().SetDissolve(ReadFloat());
	}

	void MTLReader::ReadMTLOpticalDensity() {
		m_material_buffer.back().SetIndexOfRefraction(ReadFloat());
	}

	void MTLReader::ReadMTLAmbientReflectivityTexture() {
		m_material_buffer.back().SetAmbientReflectivityTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLDiffuseReflectivityTexture() {
		m_material_buffer.back().SetDiffuseReflectivityTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLSpecularReflectivityTexture() {
		m_material_buffer.back().SetSpecularReflectivityTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLSpecularExponentTexture() {
		m_material_buffer.back().SetSpecularExponentTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLDissolveTexture() {
		m_material_buffer.back().SetDissolveTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLDecalTexture() {
		m_material_buffer.back().SetDecalTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLDisplacementTexture() {
		m_material_buffer.back().SetDisplacementTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLNormalTexture() {
		m_material_buffer.back().SetNormalTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLBumpTexture() {
		Warning("%ls: line %u: bump maps are not supported, use normal maps instead.", GetFilename().c_str(), GetCurrentLineNumber());
		ReadMTLTexture();
	}

	const RGBSpectrum MTLReader::ReadMTLSpectrum() {
		if (!HasFloat()) {
			const char *str = ReadChars();

			// XYZ spectrum
			if (str_equals(str, MAGE_MTL_TOKEN_XYZ)) {
				const float x = ReadFloat();
				float y = x;
				float z = x;
				if (HasFloat()) {
					y = ReadFloat();
					z = ReadFloat();
				}
				return static_cast< RGBSpectrum >(XYZSpectrum(x, y, z));
			}
			
			// Custom spectrum
			if (str_equals(str, MAGE_MTL_TOKEN_SPECTRAL)) {
				Warning("%ls: line %u: unsupported custom spectrum.", GetFilename().c_str(), GetCurrentLineNumber());
				return RGBSpectrum();
			}

			Warning("%ls: line %u: unsupported spectrum: %s.", GetFilename().c_str(), GetCurrentLineNumber(), str);
			return RGBSpectrum();
		}

		// RGB spectrum
		const float x = ReadFloat();
		float y = x;
		float z = x;
		if (HasFloat()) {
			y = ReadFloat();
			z = ReadFloat();
		}
		return RGBSpectrum(x, y, z);
	}

	SharedPtr< Texture > MTLReader::ReadMTLTexture() {
		// "-options args" are not supported and are not allowed.
		const wstring texture_path = mage::GetPathName(GetFilename());
		const wstring texture_name = str_convert(ReadString());
		const wstring texture_fname = mage::GetFilename(texture_path, texture_name);
		return CreateTexture(texture_fname);
	}

	void MTLReader::ReadMTLIlluminationModel() {
		// Silently ignore illumination model declarations.
		ReadUInt32();
	}
}