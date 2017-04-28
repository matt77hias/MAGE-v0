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

#define MAGE_MDL_PART_DEFAULT_CHILD "default"
#define MAGE_MDL_PART_DEFAULT_PARENT "root"
#define MAGE_MDL_PART_DEFAULT_MATERIAL "none"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct ModelPart final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit ModelPart(const string &child = MAGE_MDL_PART_DEFAULT_CHILD, 
			const string &parent = MAGE_MDL_PART_DEFAULT_PARENT,
			uint32_t start_index = 0, uint32_t nb_indices = 0, 
			const string &material = MAGE_MDL_PART_DEFAULT_MATERIAL)
			: m_child(child), m_parent(parent), m_material(material),
			m_start_index(start_index), m_nb_indices(nb_indices) {}
		ModelPart(const ModelPart &model_part) = default;
		ModelPart(ModelPart &&model_part) = default;
		~ModelPart() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ModelPart &operator=(const ModelPart &model_part) = default;
		ModelPart &operator=(ModelPart &&model_part) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		string m_child;
		string m_parent;
		string m_material;
		uint32_t m_start_index;
		uint32_t m_nb_indices;
	};

	template < typename VertexT >
	struct ModelOutput final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ModelOutput() = default;
		ModelOutput(const ModelOutput< VertexT > &output) = delete;
		ModelOutput(ModelOutput< VertexT > &&output) = default;
		~ModelOutput() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ModelOutput< VertexT > &operator=(const ModelOutput< VertexT > &output) = delete;
		ModelOutput< VertexT > &operator=(ModelOutput< VertexT > &&output) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		bool HasModelPart(const string &child) {
			for (vector< ModelPart >::const_iterator it = m_model_parts.cbegin(); it != m_model_parts.cend(); ++it) {
				if (it->m_child == child) {
					return true;
				}
			}
			return false;
		}
		void StartModelPart(const string &child, const string &parent = MAGE_MDL_PART_DEFAULT_PARENT) {
			const uint32_t start = static_cast< uint32_t >(m_index_buffer.size());
			m_model_parts.push_back(ModelPart(child, parent, start));
		}
		void SetMaterial(const string &material) {
			ModelPart &current = m_model_parts.back();
			current.m_material = material;
		}
		void EndModelPart() {
			ModelPart &current = m_model_parts.back();
			const uint32_t start = current.m_start_index;
			const uint32_t end = static_cast< uint32_t >(m_index_buffer.size());
			current.m_nb_indices = end - start;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		vector< VertexT > m_vertex_buffer;
		vector< uint32_t > m_index_buffer;
		vector< Material > m_material_buffer;
		vector< ModelPart > m_model_parts;
	};
}