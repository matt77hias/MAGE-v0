#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\bounding_volume.hpp"
#include "material\material.hpp"
#include "utils\collection\collection.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_MDL_PART_DEFAULT_CHILD    "default"
#define MAGE_MDL_PART_DEFAULT_PARENT   "root"
#define MAGE_MDL_PART_DEFAULT_MATERIAL "none"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of model parts.
	 */
	struct ModelPart final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model part.

		 @param[in]		child
						The name.
		 @param[in]		parent
						The name of the parent.
		 @param[in]		start_index
						The start index.
		 @param[in]		nb_indices
						The number of indices.
		 @param[in]		material
						The name of the material.
		 */
		explicit ModelPart(
			string child    = MAGE_MDL_PART_DEFAULT_CHILD, 
			string parent   = MAGE_MDL_PART_DEFAULT_PARENT,
			U32 start_index = 0, 
			U32 nb_indices  = 0, 
			string material = MAGE_MDL_PART_DEFAULT_MATERIAL)
			: m_child(std::move(child)), 
			m_parent(std::move(parent)), 
			m_material(std::move(material)),
			m_start_index(start_index), 
			m_nb_indices(nb_indices),
			m_aabb(), 
			m_bs() {}
		
		/**
		 Constructs a model part from the given model part.

		 @param[in]		model_part
						A reference to the model part to copy.
		 */
		ModelPart(const ModelPart &model_part) = default;

		/**
		 Constructs a model part by moving the given model part. 

		 @param[in]		model_part
						A reference to the model part to move.
		 */
		ModelPart(ModelPart &&model_part) = default;

		/**
		 Destructs this model part.
		 */
		~ModelPart() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given model part to this model part.

		 @param[in]		model_part
						A reference to the model part to copy.
		 @return		A reference to the copy of the given model part (i.e. 
						this model part).
		 */
		ModelPart &operator=(const ModelPart &model_part) = default;

		/**
		 Moves the given model part to this model part.

		 @param[in]		model_part
						A reference to the model part to move.
		 @return		A reference to the moved model part (i.e. this model 
						part).
		 */
		ModelPart &operator=(ModelPart &&model_part) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this model part has the default child as its child.

		 @return		@c true if this model part has the default child as its 
						child. @c false otherwise.
		 */
		bool HasDefaultChild() const noexcept {
			return MAGE_MDL_PART_DEFAULT_CHILD == m_child;
		}

		/**
		 Checks whether this model part has the default parent as its parent.

		 @return		@c true if this model part has the default parent as 
						its parent. @c false otherwise.
		 */
		bool HasDefaultParent() const noexcept {
			return MAGE_MDL_PART_DEFAULT_PARENT == m_parent;
		}

		/**
		 Checks whether this model part has the default material as its 
		 material.

		 @return		@c true if this model part has the default material as 
						its material. @c false otherwise.
		 */
		bool HasDefaultMaterial() const noexcept {
			return MAGE_MDL_PART_DEFAULT_MATERIAL == m_material;
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The name of this model part.
		 */
		const string m_child;

		/**
		 The name of the parent model part of this model part.
		 */
		const string m_parent;

		/**
		 The name of the material of this model part.
		 */
		string m_material;

		/**
		 The start index of this model part in the mesh of the corresponding 
		 model.
		 */
		U32 m_start_index;

		/**
		 The number of indices of this model part in the mesh of the 
		 corresponding model.
		 */
		U32 m_nb_indices;

		/**
		 The AABB of this model part.
		 */
		AABB m_aabb;

		/**
		 The BS of this model part.
		 */
		BS m_bs;
	};

	/**
	 A struct of model outputs.

	 @tparam		VertexT
					The vertex type.
	 */
	template < typename VertexT >
	struct ModelOutput final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model output.
		 */
		ModelOutput() = default;

		/**
		 Constructs a model output from the given model output.

		 @param[in]		output
						A reference to the model output to copy.
		 */
		ModelOutput(const ModelOutput< VertexT > &output) = delete;

		/**
		 Constructs a model output by moving the given model output.

		 @param[in]		output
						A reference to the model output to move.
		 */
		ModelOutput(ModelOutput< VertexT > &&output) = default;

		/**
		 Destructs this model output.
		 */
		~ModelOutput() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given model output to this model output.

		 @param[in]		output
						A reference to the model output to copy.
		 @return		A reference to the copy of the given model output (i.e.
						this model output).
		 */
		ModelOutput< VertexT > &operator=(
			const ModelOutput< VertexT > &output) = delete;

		/**
		 Moves the given model output to this model output.

		 @param[in]		output
						A reference to the model output to move.
		 @return		A reference to the moved model output
						(i.e. this model output).
		 */
		ModelOutput< VertexT > &operator=(
			ModelOutput< VertexT > &&output) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Adds a model part.

		 @param[in]		model_part
						A reference to the model part to add.
		 @param[in]		create_bounding_volumes
						A flag indicating whether bounding volumes must be 
						created for the given model part.
		 */
		void AddModelPart(ModelPart &&model_part, 
			bool create_bounding_volumes = true);

		/**
		 Checks whether this model output contains a model part with the given 
		 name.

		 @param[in]		name
						The name of the model part.
		 */
		bool HasModelPart(const string &name) noexcept;
		
		/**
		 Starts the creation of a new model part.

		 @param[in]		child
						The name.
		 @param[in]		parent
						The name of the parent model part.
		 */
		void StartModelPart(string child, 
			string parent = MAGE_MDL_PART_DEFAULT_PARENT);
		
		/**
		 Sets the name of the material of the last model part to the given 
		 material name.

		 @pre			This model output contains at least one model part.
		 @param[in]		material
						The name of the material.
		 */
		void SetMaterial(string material);
		
		/**
		 Ends the creation of the last model part.

		 @pre			This model output contains at least one model part.
		 @param[in]		create_bounding_volumes
						A flag indicating whether bounding volumes must be 
						created for the given model part.
		 */
		void EndModelPart(bool create_bounding_volumes = true) noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A vector containing the vertices of this model output.
		 */
		vector< VertexT > m_vertex_buffer;

		/**
		 A vector containing the indices of this model output.
		 */
		vector< U32 > m_index_buffer;

		/**
		 A vector containing the materials of this model output.
		 */
		vector< Material > m_material_buffer;

		/**
		 A vector containing the model parts of this model output.
		 */
		vector< ModelPart > m_model_parts;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets up the bounding volumes of the given model part.

		 @param[in]		model_part
						A reference to the model part.
		 */
		void SetupBoundingVolumes(ModelPart &model_part) noexcept;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_output.tpp"

#pragma endregion