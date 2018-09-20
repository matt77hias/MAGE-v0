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
		U32 m_start_index = 0u;

		/**
		 The number of indices of this model part in the mesh of the
		 corresponding model.
		 */
		U32 m_nb_indices = 0u;

		//---------------------------------------------------------------------
		// Member Variables: Scene Graph
		//---------------------------------------------------------------------

		/**
		 The name of this model part.
		 */
		std::string m_child = s_default_child;

		/**
		 The name of the parent model part of this model part.
		 */
		std::string m_parent = s_default_parent;

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The name of the material of this model part.
		 */
		std::string m_material = s_default_material;
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
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Adds a model part to this model output.

		 @param[in]		model_part
						The model part to add.
		 */
		void XM_CALLCONV AddModelPart(ModelPart model_part);

		/**
		 Computes the bounding volumes of the model parts of this model output.
		 */
		void ComputeBoundingVolumes() noexcept;

		/**
		 Normalizes the model parts of this model output.
		 */
		void NormalizeModelParts() noexcept;

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
		 Normalizes the vertices in world space of this model output.
		 */
		void NormalizeInWorldSpace() noexcept;

		/**
		 Normalizes the vertices in object space of this model output.
		 */
		void NormalizeInObjectSpace() noexcept;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\model\model_output.tpp"

#pragma endregion