#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "loaders\obj\obj_tokens.hpp"
#include "loaders\material_loader.hpp"
#include "resource\mesh\vertex.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering::loader {

	template< typename VertexT, typename IndexT >
	OBJReader< VertexT, IndexT >
		::OBJReader(ResourceManager& resource_manager,
					ModelOutput< VertexT, IndexT >& model_output,
			        const MeshDescriptor< VertexT, IndexT >& mesh_desc)
		: LineReader(),
		m_model_part(),
		m_vertex_coordinates(),
		m_vertex_texture_coordinates(),
		m_vertex_normal_coordinates(),
		m_mapping(),
		m_resource_manager(resource_manager),
		m_model_output(model_output),
		m_mesh_desc(mesh_desc) {}

	template< typename VertexT, typename IndexT >
	OBJReader< VertexT, IndexT >::OBJReader(OBJReader&& reader) noexcept = default;

	template< typename VertexT, typename IndexT >
	OBJReader< VertexT, IndexT >::~OBJReader() = default;

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::FinalizeModelPart() {
		const auto size = static_cast< U32 >(m_model_output.m_index_buffer.size());

		m_model_part.m_nb_indices = size - m_model_part.m_start_index;
		m_model_output.AddModelPart(std::move(m_model_part));

		m_model_part = ModelPart();
		m_model_part.m_start_index = size;
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::Preprocess() {
		using std::empty;
		ThrowIfFailed(empty(m_model_output.m_vertex_buffer),
					  "{}: vertex buffer must be empty.", GetPath());
		ThrowIfFailed(empty(m_model_output.m_index_buffer),
					  "{}: index buffer must be empty.", GetPath());
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::Postprocess() {
		FinalizeModelPart();

		m_model_output.NormalizeModelParts();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadLine() {
		const auto token = Read< std::string_view >();

		if (g_obj_token_comment == token[0]) {
			return;
		}
		else if (g_obj_token_vertex           == token) {
			ReadOBJVertex();
		}
		else if (g_obj_token_texture          == token) {
			ReadOBJVertexTexture();
		}
		else if (g_obj_token_normal           == token) {
			ReadOBJVertexNormal();
		}
		else if (g_obj_token_face             == token) {
			ReadOBJFace();
		}
		else if (g_obj_token_material_library == token) {
			ReadOBJMaterialLibrary();
		}
		else if (g_obj_token_material_use     == token) {
			ReadOBJMaterialUse();
		}
		else if (g_obj_token_group            == token) {
			ReadOBJGroup();
		}
		else if (g_obj_token_object           == token) {
			ReadOBJObject();
		}
		else if (g_obj_token_smoothing_group  == token) {
			ReadOBJSmoothingGroup();
		}
		else {
			Warning("{}: line {}: unsupported keyword token: {}.",
					GetPath(), GetCurrentLineNumber(), token);
			return;
		}

		ReadRemainingTokens();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJMaterialLibrary() {
		const UTF8toUTF16 mtl_name(Read< std::string_view >());
		auto mtl_path = GetPath();
		mtl_path.replace_filename(std::wstring_view(mtl_name));

		ImportMaterialFromFile(mtl_path,
							   m_resource_manager,
							   m_model_output.m_material_buffer);
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJMaterialUse() {
		if (!m_model_part.HasDefaultMaterial()) {
			FinalizeModelPart();
		}

		m_model_part.m_material = Read< std::string_view >();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJGroup() {
		if (!m_model_part.HasDefaultChild()) {
			FinalizeModelPart();
		}

		m_model_part.m_child = Read< std::string_view >();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJObject() {
		ReadOBJGroup();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJSmoothingGroup() {
		// Silently ignore smoothing group declarations.
		Read< std::string_view >();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJVertex() {
		const auto read_vertex = ReadOBJVertexCoordinates();
		auto vertex = m_mesh_desc.InvertHandness() ?
			InvertHandness(read_vertex) : read_vertex;

		m_vertex_coordinates.push_back(std::move(vertex));
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJVertexTexture() {
		const auto read_texture = ReadOBJVertexTextureCoordinates();
		auto texture = m_mesh_desc.InvertHandness() ?
			InvertHandness(read_texture) : read_texture;

		m_vertex_texture_coordinates.push_back(std::move(texture));
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJVertexNormal() {
		const auto read_normal = ReadOBJVertexNormalCoordinates();
		auto normal = m_mesh_desc.InvertHandness() ?
			InvertHandness(read_normal) : read_normal;

		m_vertex_normal_coordinates.push_back(std::move(normal));
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJFace() {
		MemoryBuffer< IndexT, 6u > indices;
		while (indices.size() < 3u || ContainsTokens()) {
			const auto indices3 = ReadOBJVertexIndices();

			if (const auto it = m_mapping.find(indices3);
				it != m_mapping.cend()) {

				// Add the index to the already existing vertex.
				indices.push_back(it->second);
			}
			else {
				// Create an index to a new vertex.
				const auto index
					= static_cast< IndexT >(m_model_output.m_vertex_buffer.size());
				// Add the index to the new vertex.
				indices.push_back(index);

				// Create a new vertex.
				auto vertex = ConstructVertex(indices3);
				// Add the new vertex.
				m_model_output.m_vertex_buffer.push_back(std::move(vertex));

				// Add the new mapping.
				m_mapping[indices3] = index;
			}
		}

		if (m_mesh_desc.ClockwiseOrder()) {
			for (size_t i = 1u; i < indices.size() - 1u; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0u]);
				m_model_output.m_index_buffer.push_back(indices[i + 1u]);
				m_model_output.m_index_buffer.push_back(indices[i]);
			}
		}
		else {
			for (size_t i = 1u; i < indices.size() - 1u; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0u]);
				m_model_output.m_index_buffer.push_back(indices[i]);
				m_model_output.m_index_buffer.push_back(indices[i + 1u]);
			}
		}
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	inline const Point3 OBJReader< VertexT, IndexT >
		::ReadOBJVertexCoordinates() {

		return Point3(Read< F32, 3u >());
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	inline const Normal3 OBJReader< VertexT, IndexT >
		::ReadOBJVertexNormalCoordinates() {

		return Normal3(Read< F32, 3u >());
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	const UV OBJReader< VertexT, IndexT >
		::ReadOBJVertexTextureCoordinates() {

		const UV result(Read< F32, 2u >());

		if (Contains< F32 >()) {
			// Silently ignore 3D vertex texture coordinates.
			Read< F32 >();
		}

		return result;
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	const U32x3 OBJReader< VertexT, IndexT >
		::ReadOBJVertexIndices() {

		const auto token  = Read< std::string_view >();

		const auto slash1 = token.find_first_of('/');
		const bool flag1  = (std::string::npos != slash1);
		const auto slash2 = token.find_first_of('/', slash1 + 1u);
		const bool flag2  = (std::string::npos != slash2);
		const bool flagd  = (slash1 + 1u == slash2);

		static constexpr const_zstring s_token_names[] = {
			"v",
			"vt",
			"vn"
		};
		const bool contains_token[] = {
			true,
			flag1 && !flagd,
			flag2
		};
		const std::string_view tokens[] = {
			// If offset std::string::npos + 1u == 0u then count is don't-care;
			// all unsigned values avoid exception.
			token.substr(0u,          slash1),
			token.substr(slash1 + 1u, slash2       - slash1 - 1u),
			token.substr(slash2 + 1u, token.size() - slash2 - 1u)
		};

		U32x3 indices;
		const S32x3 sizes = {
			static_cast< S32 >(m_vertex_coordinates.size()),
			static_cast< S32 >(m_vertex_texture_coordinates.size()),
			static_cast< S32 >(m_vertex_normal_coordinates.size())
		};

		for (std::size_t i = 0u; i < std::size(s_token_names); ++i) {
			if (!contains_token[i]) {
				continue;
			}

			if (const auto result = StringTo< S32 >(tokens[i]); bool(result)) {
				const auto index = *result;
				indices[i] = static_cast< U32 >((0 <= index) ? index : sizes[i] + index);
			}
			else {
				throw Exception("{}: line {}: invalid {} index value found in {}.",
								GetPath(), GetCurrentLineNumber(), s_token_names[i], token);
			}
		}

		return indices;
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	const VertexT OBJReader< VertexT, IndexT >
		::ConstructVertex(const U32x3& vertex_indices) {

		VertexT vertex;

		if constexpr (VertexT::HasPosition()) {
			if (vertex_indices[0u]) {
				vertex.m_p = m_vertex_coordinates[vertex_indices[0u] - 1u];
			}
		}

		if constexpr (VertexT::HasTexture()) {
			if (vertex_indices[1u]) {
				vertex.m_tex = m_vertex_texture_coordinates[vertex_indices[1u] - 1u];
			}
		}

		if constexpr (VertexT::HasNormal()) {
			if (vertex_indices[2u]) {
				vertex.m_n = m_vertex_normal_coordinates[vertex_indices[2u] - 1u];
			}
		}

		return vertex;
	}
}