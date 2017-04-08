#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\material.hpp"
#include "collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_MODEL_PART_DEFAULT_CHILD "default"
#define MAGE_MODEL_PART_DEFAULT_PARENT "root"
#define MAGE_MODEL_PART_DEFAULT_MATERIAL "none"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct ModelPart final {

	public:

		explicit ModelPart(const string &child = MAGE_MODEL_PART_DEFAULT_CHILD, 
			const string &parent = MAGE_MODEL_PART_DEFAULT_PARENT,
			uint32_t start_index = 0, uint32_t nb_indices = 0, 
			const string &material = MAGE_MODEL_PART_DEFAULT_MATERIAL)
			: child(child), parent(parent), material(material), 
			start_index(start_index), nb_indices(nb_indices) {}
		ModelPart(const ModelPart &model_part) = default;
		ModelPart(ModelPart &&model_part) = default;
		~ModelPart() = default;

		ModelPart &operator=(const ModelPart &model_part) = default;
		ModelPart &operator=(ModelPart &&model_part) = default;

		string child;
		string parent;
		string material;
		uint32_t start_index;
		uint32_t nb_indices;
	};

	template < typename VertexT >
	struct ModelOutput final {

	public:

		ModelOutput() = default;
		ModelOutput(const ModelOutput< VertexT > &output) = delete;
		ModelOutput(ModelOutput< VertexT > &&output) = default;
		~ModelOutput() = default;

		ModelOutput< VertexT > &operator=(const ModelOutput< VertexT > &output) = delete;
		ModelOutput< VertexT > &operator=(ModelOutput< VertexT > &&output) = delete;

		bool HasModelPart(const string &child) {
			for (vector< ModelPart >::const_iterator it = model_parts.cbegin(); it != model_parts.cend(); ++it) {
				if (it->child == child) {
					return true;
				}
			}
			return false;
		}
		void StartModelPart(const string &child, const string &parent = MAGE_MODEL_PART_DEFAULT_PARENT) {
			const uint32_t start = static_cast< uint32_t >(index_buffer.size());
			model_parts.push_back(ModelPart(child, parent, start));
		}
		void SetMaterial(const string &material) {
			ModelPart &current = model_parts.back();
			current.material = material;
		}
		void EndModelPart() {
			ModelPart &current = model_parts.back();
			const uint32_t start = current.start_index;
			const uint32_t end = static_cast< uint32_t >(index_buffer.size());
			current.nb_indices = end - start;
		}

		vector< VertexT > vertex_buffer;
		vector< uint32_t > index_buffer;
		vector< Material > material_buffer;
		vector< ModelPart > model_parts;
	};
}