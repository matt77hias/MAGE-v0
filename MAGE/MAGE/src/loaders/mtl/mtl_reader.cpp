//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mtl\mtl_reader.hpp"
#include "loaders\mtl\mtl_tokens.hpp"
#include "string\string_utils.hpp"
#include "resource\resource_manager.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::loader {

	MTLReader::MTLReader(std::vector< Material > &material_buffer)
		: LineReader(), 
		m_material_buffer(material_buffer) {}

	MTLReader::MTLReader(MTLReader &&reader) noexcept = default;

	MTLReader::~MTLReader() = default;

	void MTLReader::ReadLine(char *line) {
		m_context = nullptr;
		const char * const token 
			= strtok_s(line, GetDelimiters().c_str(), &m_context);

		if (!token || g_mtl_token_comment == token[0]) {
			return;
		}

		if (str_equals(token, g_mtl_token_material_declaration)) {
			ReadMTLMaterialName();
		}
		else if (str_equals(token, g_mtl_token_base_color)) {
			ReadMTLBaseColor();
		}
		else if (str_equals(token, g_mtl_token_roughness)) {
			ReadMTLRoughness();
		}
		else if (str_equals(token, g_mtl_token_metalness)) {
			ReadMTLMetalness();
		}
		else if (str_equals(token, g_mtl_token_base_color_texture)) {
			ReadMTLBaseColorTexture();
		}
		else if (str_equals(token, g_mtl_token_material_texture)) {
			ReadMTLMaterialTexture();
		}
		else if (str_equals(token, g_mtl_token_normal_texture)) {
			ReadMTLNormalTexture();
		}
		else if (str_equals(token, g_mtl_token_transparent)) {
			m_material_buffer.back().SetTransparent();
		}
		else if (str_equals(token, g_mtl_token_opaque)) {
			m_material_buffer.back().SetOpaque();
		}
		else if (str_equals(token, g_mtl_token_emissive)) {
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
		m_material_buffer.emplace_back(Read< string >());
	}

	void MTLReader::ReadMTLBaseColor() {
		m_material_buffer.back().GetBaseColor() = ReadMTLSRGBA();
	}

	void MTLReader::ReadMTLRoughness() {
		const F32 roughness = Read< F32 >();
		m_material_buffer.back().SetRoughness(roughness);
	}

	void MTLReader::ReadMTLMetalness() {
		const F32 metalness = Read< F32 >();
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

	const SRGB MTLReader::ReadMTLSRGB() {

		const F32 red = Read< F32 >();

		F32 green = red;
		F32 blue  = red;
		if (Has< F32 >()) {
			green = Read< F32 >();
			blue  = Read< F32 >();
		}

		return SRGB(red, green, blue);
	}

	const SRGBA MTLReader::ReadMTLSRGBA() {
		
		const F32 red = Read< F32 >();

		F32 green = red;
		F32 blue  = red;
		if (Has< F32 >()) {
			green = Read< F32 >();
			blue  = Read< F32 >();
		}

		const F32 alpha = Has< F32 >() ? Read< F32 >() : 1.0f;
		
		return SRGBA(red, green, blue, alpha);
	}

	SharedPtr< const Texture > MTLReader::ReadMTLTexture() {
		// "-options args" are not supported and are not allowed.
		const wstring texture_path  = mage::GetPathName(GetFilename());
		const wstring texture_name  = str_convert(Read< string >());
		const wstring texture_fname = mage::GetFilename(texture_path, texture_name);
		return ResourceManager::Get()->GetOrCreate< Texture >(texture_fname);
	}
}