#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\vertex.hpp"
#include "mesh\mesh_object.hpp"
#include "material\material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template < typename Vertex >
	struct ModelOutput final {

	public:

		ModelOutput() = default;
		~ModelOutput() = default;

		size_t GetNumberOfVertices() const {
			return m_vertex_buffer.size();
		}
		size_t GetNumberOfIndices() const {
			return m_index_buffer.size();
		}
		size_t GetNumberOfMaterials() const {
			return m_material_buffer.size();
		}

		const vector< Vertex > &GetVertexBuffer() const {
			return m_vertex_buffer;
		}
		const vector< uint32_t > &GetIndexBuffer() const {
			return m_index_buffer;
		}
		const vector< Material > &GetMaterialBuffer() const {
			return m_material_buffer;
		}

		void AddVertex(const Vertex &vertex) {
			m_vertex_buffer.push_back(vertex);
		}
		void AddIndex(const uint32_t index) {
			m_index_buffer.push_back(index);
		}
		void AddMaterial(const Material &material) {
			m_material_buffer.push_back(material);
		}

		void AddMeshObject(size_t m_start_index, size_t m_nb_indices, const string &object_name, const string &material_name, const string &parent_name = L"") {
			//
		}

	private:

		ModelOutput(const ModelOutput< Vertex > &output) = delete;
		ModelOutput< Vertex > &operator=(ModelOutput< Vertex > &output) = delete;

		vector< Vertex > m_vertex_buffer;
		vector< uint32_t > m_index_buffer;
		vector< Material > m_material_buffer;
	};
}