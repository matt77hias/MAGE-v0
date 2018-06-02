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
	void OBJReader< VertexT, IndexT >::Preprocess() {
		using std::empty;
		ThrowIfFailed(empty(m_model_output.m_vertex_buffer), 
					  "%ls: vertex buffer must be empty.", 
					  GetPath().c_str());
		ThrowIfFailed(empty(m_model_output.m_index_buffer),
					  "%ls: index buffer must be empty.", 
					  GetPath().c_str());

		// Begin current group.
		m_model_output.StartModelPart(ModelPart());
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::Postprocess() {
		// End current group.
		m_model_output.EndModelPart();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadLine(NotNull< zstring > line) {
		m_context = nullptr;
		const auto* const token = strtok_s(line, GetDelimiters().c_str(),
										   &m_context);

		if (!token || g_obj_token_comment == token[0]) {
			return;
		}

		const auto not_null_token = NotNull< const_zstring >(token);

		if (     str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_vertex))) {

			ReadOBJVertex();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_texture))) {

			ReadOBJVertexTexture();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_normal))) {

			ReadOBJVertexNormal();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_face))) {

			ReadOBJFace();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_material_library))) {

			ReadOBJMaterialLibrary();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_material_use))) {

			ReadOBJMaterialUse();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_group))) {

			ReadOBJGroup();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_object))) {

			ReadOBJObject();
		}
		else if (str_equals(not_null_token, 
							NotNull< const_zstring >(g_obj_token_smoothing_group))) {

			ReadOBJSmoothingGroup();
		}
		else {
			Warning("%ls: line %u: unsupported keyword token: %s.", 
				    GetPath().c_str(), GetCurrentLineNumber(), token);
			return;
		}

		ReadLineRemaining();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJMaterialLibrary() {
		const auto mtl_name = StringToWString(Read< string >());
		auto mtl_path       = GetPath();
		mtl_path.replace_filename(mtl_name);
		
		ImportMaterialFromFile(mtl_path,
							   m_resource_manager, 
							   m_model_output.m_material_buffer);
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJMaterialUse() {
		m_model_output.SetMaterial(Read< string >());
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJGroup() {
		// End current group.
		m_model_output.EndModelPart();

		ModelPart model_part;
		model_part.m_child = Read< string >();
		if (ContainsChars()) {
			if (!Contains< F32 >()) {
				model_part.m_parent  = Read< string >();
			}
			
			auto translation = InvertHandness(Point3(Read< F32, 3 >()));
			model_part.m_transform.SetTranslation(std::move(translation));
			model_part.m_transform.SetRotation(Read< F32, 3 >());
			model_part.m_transform.SetScale(   Read< F32, 3 >());
		}
		
		// Begin current group.
		m_model_output.StartModelPart(std::move(model_part));
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJObject() {
		Read< string >();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJSmoothingGroup() {
		// Silently ignore smoothing group declarations
		Read< string >();
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
		
		std::vector< IndexT > indices;
		while (indices.size() < 3 || ContainsChars()) {
			const auto vertex_indices = ReadOBJVertexIndices();

			if (const auto it = m_mapping.find(vertex_indices); 
				it != m_mapping.cend()) {

				indices.push_back(it->second);
			}
			else {
				const auto index
					= static_cast< IndexT >(m_model_output.m_vertex_buffer.size());
				indices.push_back(index);
				m_model_output.m_vertex_buffer.push_back(
					ConstructVertex(vertex_indices));
				m_mapping[vertex_indices] = index;
			}
		}

		if (m_mesh_desc.ClockwiseOrder()) {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0]);
				m_model_output.m_index_buffer.push_back(indices[i + 1]);
				m_model_output.m_index_buffer.push_back(indices[i]);
			}
		}
		else {
			for (size_t i = 1; i < indices.size() - 1; ++i) {
				m_model_output.m_index_buffer.push_back(indices[0]);
				m_model_output.m_index_buffer.push_back(indices[i]);
				m_model_output.m_index_buffer.push_back(indices[i + 1]);
			}
		}
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	inline const Point3 OBJReader< VertexT, IndexT >
		::ReadOBJVertexCoordinates() {

		return Point3(Read< F32, 3 >());
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	inline const Normal3 OBJReader< VertexT, IndexT >
		::ReadOBJVertexNormalCoordinates() {

		return Normal3(Read< F32, 3 >());
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	const UV OBJReader< VertexT, IndexT >
		::ReadOBJVertexTextureCoordinates() {

		const UV result(Read< F32, 2 >());
		
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

		const auto token = ReadChars();
		const auto not_null_token = NotNull< const_zstring >(token);

		S32 v_index  = 0;
		S32 vt_index = 0;
		S32 vn_index = 0;

		if (str_contains(not_null_token, NotNull< const_zstring >("//"))) {
			// v1//vn1
			const auto index_end = strchr(token, '/');
			if (TokenResult::Invalid == StringTo< S32 >(token, index_end, v_index)) {
				throw Exception("%ls: line %u: invalid v index value found in %s.", 
					            GetPath().c_str(), GetCurrentLineNumber(), token);
			}
			if (TokenResult::Invalid == StringTo< S32 >(index_end + 2, vn_index)) {
				throw Exception("%ls: line %u: invalid vn index value found in %s.", 
					            GetPath().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (str_contains(not_null_token, '/')) {
			// v1/vt1 or v1/vt1/vn1
			const auto index_end = strchr(token, '/');
			if (TokenResult::Invalid == StringTo< S32 >(token, index_end, v_index)) {
				throw Exception("%ls: line %u: invalid v index value found in %s.", 
					            GetPath().c_str(), GetCurrentLineNumber(), token);
			}
			
			if (str_contains(NotNull< const_zstring >(index_end + 1), '/')) {
				const auto texture_end = strchr(index_end + 1, '/');
				if (TokenResult::Invalid == StringTo< S32 >(index_end + 1, texture_end, vt_index)) {
					throw Exception("%ls: line %u: invalid vt index value found in %s.", 
						            GetPath().c_str(), GetCurrentLineNumber(), token);
				}
				if (TokenResult::Invalid == StringTo< S32 >(texture_end + 1, vn_index)) {
					throw Exception("%ls: line %u: invalid vn index value found in %s.", 
						            GetPath().c_str(), GetCurrentLineNumber(), token);
				}
			}
			else if (TokenResult::Invalid == StringTo< S32 >(index_end + 1, vt_index)) {
				throw Exception("%ls: line %u: invalid vt index value found in %s.", 
					            GetPath().c_str(), GetCurrentLineNumber(), token);
			}
		}
		else if (TokenResult::Invalid == StringTo< S32 >(token, v_index)) {
			throw Exception("%ls: line %u: invalid v index value found in %s.", 
				            GetPath().c_str(), GetCurrentLineNumber(), token);
		}

		const auto v  = static_cast< U32 >((0 <=  v_index) ?  v_index 
		              : static_cast< S32 >(m_vertex_coordinates.size())         +  v_index);
		const auto vt = static_cast< U32 >((0 <= vt_index) ? vt_index 
		              : static_cast< S32 >(m_vertex_texture_coordinates.size()) + vt_index);
		const auto vn = static_cast< U32 >((0 <= vn_index) ? vn_index 
		              : static_cast< S32 >(m_vertex_normal_coordinates.size())  + vn_index);

		return { v, vt, vn };
	}

	template< typename VertexT, typename IndexT >
	[[nodiscard]]
	const VertexT OBJReader< VertexT, IndexT >
		::ConstructVertex(const U32x3& vertex_indices) {
		
		VertexT vertex;

		if constexpr(VertexT::HasPosition()) {
			if (vertex_indices[0]) {
				vertex.m_p = m_vertex_coordinates[vertex_indices[0] - 1];
			}
		}

		if constexpr(VertexT::HasTexture()) {
			if (vertex_indices[1]) {
				vertex.m_tex = m_vertex_texture_coordinates[vertex_indices[1] - 1];
			}
		}

		if constexpr(VertexT::HasNormal()) {
			if (vertex_indices[2]) {
				vertex.m_n = m_vertex_normal_coordinates[vertex_indices[2] - 1];
			}
		}

		return vertex;
	}
}