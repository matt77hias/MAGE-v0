//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\mtl\mtl_reader.hpp"
#include "material\mtl\mtl_tokens.hpp"
#include "string\string_utils.hpp"
#include "resource\resource_manager.hpp"

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
		const char *token = 
			strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || token[0] == MAGE_MTL_COMMENT_CHAR) {
			return;
		}

		if (str_equals(token, MAGE_MTL_TOKEN_MATERIAL_DECLARATION)) {
			ReadMTLMaterialName();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_BASE_COLOR)) {
			ReadMTLBaseColor();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_ROUGHNESS)) {
			ReadMTLRoughness();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_METALNESS)) {
			ReadMTLMetalness();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_BASE_COLOR_TEXTURE)) {
			ReadMTLBaseColorTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_MATERIAL_TEXTURE)) {
			ReadMTLMaterialTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_NORMAL_TEXTURE)) {
			ReadMTLNormalTexture();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_TRANSPARENT)) {
			m_material_buffer.back().SetTransparent();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_OPAQUE)) {
			m_material_buffer.back().SetOpaque();
		}
		else if (str_equals(token, MAGE_MTL_TOKEN_EMISSIVE)) {
			m_material_buffer.back().DissableLightInteraction();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				GetFilename().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	void MTLReader::ReadMTLMaterialName() {
		const string material_name = ReadString();
		m_material_buffer.emplace_back(material_name);
	}

	void MTLReader::ReadMTLBaseColor() {
		m_material_buffer.back().SetBaseColorRGBA(ReadMTLRGBASpectrum());
	}

	void MTLReader::ReadMTLRoughness() {
		const F32 roughness = ReadF32();
		m_material_buffer.back().SetRoughness(roughness);
	}

	void MTLReader::ReadMTLMetalness() {
		const F32 metalness = ReadF32();
		m_material_buffer.back().SetMetalness(metalness);
	}

	void MTLReader::ReadMTLBaseColorTexture() {
		m_material_buffer.back().SetBaseColorTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLMaterialTexture() {
		m_material_buffer.back().SetMaterialTexture(ReadMTLTexture());
	}

	void MTLReader::ReadMTLNormalTexture() {
		m_material_buffer.back().SetNormalTexture(ReadMTLTexture());
	}

	const RGBSpectrum MTLReader::ReadMTLRGBSpectrum() {

		const F32 red = ReadF32();

		F32 green = red;
		F32 blue = red;
		if (HasF32()) {
			green = ReadF32();
			blue = ReadF32();
		}

		return RGBSpectrum(red, green, blue);
	}

	const RGBASpectrum MTLReader::ReadMTLRGBASpectrum() {
		
		const F32 red = ReadF32();

		F32 green = red;
		F32 blue  = red;
		if (HasF32()) {
			green = ReadF32();
			blue  = ReadF32();
		}

		const F32 alpha = HasF32() ? ReadF32() : 1.0f;
		
		return RGBASpectrum(red, green, blue, alpha);
	}

	SharedPtr< const Texture > MTLReader::ReadMTLTexture() {
		// "-options args" are not supported and are not allowed.
		const wstring texture_path  = mage::GetPathName(GetFilename());
		const wstring texture_name  = str_convert(ReadString());
		const wstring texture_fname = mage::GetFilename(texture_path, texture_name);
		return ResourceManager::Get()->GetOrCreateTexture(texture_fname);
	}
}