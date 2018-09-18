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
					  "{}: vertex buffer must be empty.", GetPath());
		ThrowIfFailed(empty(m_model_output.m_index_buffer),
					  "{}: index buffer must be empty.", GetPath());

		// Begin current group.
		m_model_output.StartModelPart(ModelPart());
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::Postprocess() {
		// End current group.
		m_model_output.EndModelPart();
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
		const auto mtl_name = StringToWString(Read< std::string >());
		auto mtl_path       = GetPath();
		mtl_path.replace_filename(mtl_name);
		
		ImportMaterialFromFile(mtl_path,
							   m_resource_manager, 
							   m_model_output.m_material_buffer);
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJMaterialUse() {
		m_model_output.SetMaterial(Read< std::string >());
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJGroup() {
		// End current group.
		m_model_output.EndModelPart();

		ModelPart model_part;
		model_part.m_child = Read< std::string >();
		if (ContainsTokens()) {
			if (!Contains< F32 >()) {
				model_part.m_parent  = Read< std::string >();
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
		Read< std::string_view >();
	}

	template< typename VertexT, typename IndexT >
	void OBJReader< VertexT, IndexT >::ReadOBJSmoothingGroup() {
		// Silently ignore smoothing group declarations
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
		
		std::vector< IndexT > indices;
		while (indices.size() < 3 || ContainsTokens()) {
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

		const auto token = Read< std::string_view >();
		const auto first = token.data();
		const auto last  = first + token.size();

		S32 v_index  = 0;
		S32 vt_index = 0;
		S32 vn_index = 0;

		if (const auto slash = token.find("//");
			std::string::npos != slash) {
			
			// v//vn
			
			if (const auto result
				= StringTo< S32 >(NotNull< const char* >(first),
								  NotNull< const char* >(first + slash));
				bool(result)) {

				v_index = *result;
			}
			else {
				throw Exception("{}: line {}: invalid v index value found in {}.",
								GetPath(), GetCurrentLineNumber(), token);
			}

			
			if (const auto result
				= StringTo< S32 >(NotNull< const char* >(first + slash + 2),
								  NotNull< const char* >(last));
				bool(result)) {

				vn_index = *result;
			}
			else {
				throw Exception("{}: line {}: invalid vn index value found in {}.",
								GetPath(), GetCurrentLineNumber(), token);
			}
		}
		else if (const auto slash1 = token.find("/"); 
		         std::string::npos != slash1) {

			// v/vt or v/vt/vn

			if (const auto result
				= StringTo< S32 >(NotNull< const char* >(first),
								  NotNull< const char* >(first + slash1));
			    bool(result)) {

				v_index = *result;
			}
			else {
				throw Exception("{}: line {}: invalid v index value found in {}.",
								GetPath(), GetCurrentLineNumber(), token);
			}

			if (const auto slash2 = token.find("/", slash1 + 1); 
			    std::string::npos != slash2) {

				if (const auto result
					= StringTo< S32 >(NotNull< const char* >(first + slash1 + 1),
									  NotNull< const char* >(first + slash2));
				    bool(result)) {

					vt_index = *result;
				}
				else {
					throw Exception("{}: line {}: invalid vt index value found in {}.",
									GetPath(), GetCurrentLineNumber(), token);
				}

				if (const auto result
					= StringTo< S32 >(NotNull< const char* >(first + slash2 + 1),
									  NotNull< const char* >(last));
				    bool(result)) {

					vn_index = *result;
				}
				else {
					throw Exception("{}: line {}: invalid vn index value found in {}.",
									GetPath(), GetCurrentLineNumber(), token);
				}
			}
			else if (const auto result 
					 = StringTo< S32 >(NotNull< const char* >(first + slash1 + 1),
									   NotNull< const char* >(last));
				     bool(result)) {

					vt_index = *result;
			}
			else {
					throw Exception("{}: line {}: invalid vt index value found in {}.",
									GetPath(), GetCurrentLineNumber(), token);
			}
		} 
		else if (const auto result
				 = StringTo< S32 >(NotNull< const char* >(first), 
								   NotNull< const char* >(last));
		         bool(result)) {

				 v_index = *result;
		}
		else {
			throw Exception("{}: line {}: invalid v index value found in {}.",
							GetPath(), GetCurrentLineNumber(), token);
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