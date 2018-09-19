#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "transform\local_transform.hpp"
#include "geometry\bounding_volume.hpp"
#include "resource\model\material.hpp"
#include "collection\vector.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A struct of model parts.
	 */
	struct alignas(16) ModelPart {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The default child name for model parts.
		 */
		static constexpr const_zstring s_default_child = "default";

		/**
		 The default parent name for model parts.
		 */
		static constexpr const_zstring s_default_parent = "root";

		/**
		 The default material name for model parts.
		 */
		static constexpr const_zstring s_default_material = "none";

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model part.
		 */
		ModelPart()
			: m_aabb(),
			m_sphere(),
			m_transform(),
			m_start_index(0u), 
			m_nb_indices(0u),
			m_child(s_default_child),
			m_parent(s_default_parent),
			m_material(s_default_material) {}
		
		/**
		 Constructs a model part from the given model part.

		 @param[in]		model_part
						A reference to the model part to copy.
		 */
		ModelPart(const ModelPart& model_part) = default;

		/**
		 Constructs a model part by moving the given model part. 

		 @param[in]		model_part
						A reference to the model part to move.
		 */
		ModelPart(ModelPart&& model_part) noexcept = default;

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
		ModelPart& operator=(const ModelPart& model_part) = default;

		/**
		 Moves the given model part to this model part.

		 @param[in]		model_part
						A reference to the model part to move.
		 @return		A reference to the moved model part (i.e. this model 
						part).
		 */
		ModelPart& operator=(ModelPart&& model_part) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this model part has the default child as its child.

		 @return		@c true if this model part has the default child as its 
						child. @c false otherwise.
		 */
		[[nodiscard]]
		bool HasDefaultChild() const noexcept {
			return s_default_child == m_child;
		}

		/**
		 Checks whether this model part has the default parent as its parent.

		 @return		@c true if this model part has the default parent as 
						its parent. @c false otherwise.
		 */
		[[nodiscard]]
		bool HasDefaultParent() const noexcept {
			return s_default_parent == m_parent;
		}

		/**
		 Checks whether this model part has the default material as its 
		 material.

		 @return		@c true if this model part has the default material as 
						its material. @c false otherwise.
		 */
		[[nodiscard]]
		bool HasDefaultMaterial() const noexcept {
			return s_default_material == m_material;
		}

		//---------------------------------------------------------------------
		// Member Variables: Bounding Volumes
		//---------------------------------------------------------------------

		/**
		 The AABB of this model part.
		 */
		AABB m_aabb;

		/**
		 The bounding sphere of this model part.
		 */
		BoundingSphere m_sphere;

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		/**
		 The local transform of this model part.
		 */
		LocalTransform m_transform;

		//---------------------------------------------------------------------
		// Member Variables: Mesh
		//---------------------------------------------------------------------

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

		//---------------------------------------------------------------------
		// Member Variables: Scene Graph
		//---------------------------------------------------------------------

		/**
		 The name of this model part.
		 */
		std::string m_child;

		/**
		 The name of the parent model part of this model part.
		 */
		std::string m_parent;

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The name of the material of this model part.
		 */
		std::string m_material;
	};

	/**
	 A struct of model outputs.

	 @tparam		VertexT
					The vertex type.
	 @tparam		IndexT
					The index type.
	 */
	template< typename VertexT, typename IndexT >
	struct ModelOutput {

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
		ModelOutput(const ModelOutput& output) = delete;

		/**
		 Constructs a model output by moving the given model output.

		 @param[in]		output
						A reference to the model output to move.
		 */
		ModelOutput(ModelOutput&& output) noexcept = default;

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
		ModelOutput& operator=(const ModelOutput& output) = delete;

		/**
		 Moves the given model output to this model output.

		 @param[in]		output
						A reference to the model output to move.
		 @return		A reference to the moved model output
						(i.e. this model output).
		 */
		ModelOutput& operator=(ModelOutput&& output) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Adds a model part.

		 @param[in]		model_part
						The model part to add.
		 */
		void XM_CALLCONV AddModelPart(ModelPart model_part);

		/**
		 Checks whether this model output contains a model part with the given 
		 name.

		 @param[in]		name
						The name of the model part.
		 */
		[[nodiscard]]
		bool ContainsModelPart(std::string_view name) noexcept;
		
		/**
		 Starts the creation of a new model part.

		 @param[in]		model_part
						The model part to add.
		 */
		void XM_CALLCONV StartModelPart(ModelPart model_part);
		
		/**
		 Sets the name of the material of the last model part to the given 
		 material name.

		 @pre			This model output contains at least one model part.
		 @param[in]		material
						The name of the material.
		 */
		void SetMaterial(std::string material);
		
		/**
		 Ends the creation of the last model part.

		 @pre			This model output contains at least one model part.
		 */
		void EndModelPart() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A vector containing the vertices of this model output.
		 */
		std::vector< VertexT > m_vertex_buffer;

		/**
		 A vector containing the indices of this model output.
		 */
		std::vector< IndexT > m_index_buffer;

		/**
		 A vector containing the materials of this model output.
		 */
		std::vector< Material > m_material_buffer;

		/**
		 A vector containing the model parts of this model output.
		 */
		AlignedVector< ModelPart > m_model_parts;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Normalizes the given model part.

		 @param[in]		model_part
						A reference to the model part.
		 */
		void NormalizeModelPart(ModelPart& model_part) noexcept;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\model\model_output.tpp"

#pragma endregion