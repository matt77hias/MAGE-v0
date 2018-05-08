//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\mtl\mtl_reader.hpp"
#include "loaders\mtl\mtl_tokens.hpp"
#include "resource\model\material_factory.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	MTLReader::MTLReader(ResourceManager& resource_manager, 
						 std::vector< Material >& material_buffer)
		: LineReader(), 
		m_resource_manager(resource_manager), 
		m_material_buffer(material_buffer) {}

	MTLReader::MTLReader(MTLReader&& reader) noexcept = default;

	MTLReader::~MTLReader() = default;

	void MTLReader::ReadLine(NotNull< zstring > line) {
		m_context = nullptr;
		const auto* const token
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
		else if (str_equals(token, g_mtl_token_radiance)) {
			ReadMTLRadiance();
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
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				    GetPath().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	void MTLReader::ReadMTLMaterialName() {
		auto& material = m_material_buffer.emplace_back(
			CreateDefaultMaterial(m_resource_manager));
		material.SetName(Read< string >());
	}

	void MTLReader::ReadMTLBaseColor() {
		m_material_buffer.back().GetBaseColor() = RGBA(ReadMTLSRGBA());
	}

	void MTLReader::ReadMTLRoughness() {
		const auto roughness = Read< F32 >();
		m_material_buffer.back().SetRoughness(roughness);
	}

	void MTLReader::ReadMTLMetalness() {
		const auto metalness = Read< F32 >();
		m_material_buffer.back().SetMetalness(metalness);
	}

	void MTLReader::ReadMTLRadiance() {
		const auto radiance = Read< F32 >();
		m_material_buffer.back().SetRadiance(radiance);
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

	[[nodiscard]]
	const SRGB MTLReader::ReadMTLSRGB() {
		const auto red = Read< F32 >();

		F32 green = red;
		F32 blue  = red;
		if (Contains< F32 >()) {
			green = Read< F32 >();
			blue  = Read< F32 >();
		}

		return SRGB(red, green, blue);
	}

	[[nodiscard]]
	const SRGBA MTLReader::ReadMTLSRGBA() {
		const auto red = Read< F32 >();

		F32 green = red;
		F32 blue  = red;
		if (Contains< F32 >()) {
			green = Read< F32 >();
			blue  = Read< F32 >();
		}

		const auto alpha = Contains< F32 >() ? Read< F32 >() : 1.0f;
		
		return SRGBA(red, green, blue, alpha);
	}

	[[nodiscard]]
	TexturePtr MTLReader::ReadMTLTexture() {
		// "-options args" are not supported and are not allowed.
		const auto texture_name = StringToWString(Read< string >());
		auto texture_path       = GetPath();
		texture_path.replace_filename(texture_name);

		return m_resource_manager.GetOrCreate< Texture >(texture_path);
	}
}