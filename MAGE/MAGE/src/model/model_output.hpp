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

	struct ModelPart final {

	public:

		ModelPart(const string &child = "default", const string &parent = "root",
			uint32_t start_index = 0, uint32_t nb_indices = 0, 
			const string &material = "none")
			: child(child), parent(parent), 
			start_index(start_index), nb_indices(nb_indices), material(material) {}
		ModelPart(const ModelPart &model_part) = default;
		~ModelPart() = default;

		ModelPart &operator=(ModelPart &model_part) = default;

		string child;
		string parent;
		string material;
		uint32_t start_index;
		uint32_t nb_indices;
	};

	template < typename Vertex >
	struct ModelOutput final {

	public:

		ModelOutput() = default;
		~ModelOutput() = default;

		vector< Vertex > vertex_buffer;
		vector< uint32_t > index_buffer;
		vector< Material > material_buffer;
		vector< ModelPart > model_parts;

		void StartModelPart(const string &child = "default", const string &parent = "root") {
			const uint32_t start = (uint32_t)index_buffer.size();
			model_parts.push_back(ModelPart(child, parent, start));
		}
		void SetMaterial(const string &material) {
			ModelPart &current = model_parts.back();
			current.material = material;
		}
		void EndModelPart() {
			ModelPart &current = model_parts.back();
			const uint32_t start = current.start_index;
			const uint32_t end = (uint32_t)index_buffer.size();
			current.nb_indices = end - start;
		}

	private:

		ModelOutput(const ModelOutput< Vertex > &output) = delete;
		ModelOutput< Vertex > &operator=(ModelOutput< Vertex > &output) = delete;
	};
}