#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\static_mesh.hpp"
#include "shader\shaded_material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of models.
	 */
	class Model {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model.

		 @pre			@a mesh is not equal to @c nullptr.
		 @param[in]		mesh
						A pointer to the mesh.
		 @param[in]		material
						A reference to the shaded material.
		 */
		explicit Model(SharedPtr< const StaticMesh > mesh, const ShadedMaterial &material);

		/**
		 Constructs a model.

		 @pre			@a mesh is not equal to @c nullptr.
		 @param[in]		mesh
						A pointer to the mesh.
		 @param[in]		start_index
						The start index in the mesh.
		 @param[in]		nb_indices
						The number of indices in the mesh.
		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		bs
						A reference to the BS.
		 @param[in]		material
						A reference to the shaded material.
		 */
		explicit Model(SharedPtr< const Mesh > mesh, size_t start_index, size_t nb_indices, 
			const AABB &aabb, const BS &bs, const ShadedMaterial &material);

		/**
		 Constructs a model from the given model.

		 @param[in]		model
						A reference to the model to copy.
		 */
		Model(const Model &model);

		/**
		 Constructs a model by moving the given model.

		 @param[in]		model
						A reference to the model to move.
		 */
		Model(Model &&model);

		/**
		 Destructs this model.
		 */
		virtual ~Model();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given model to this model.

		 @param[in]		model
						A reference to the model to copy.
		 @return		A reference to the copy of the given model
						(i.e. this model).
		 */
		Model &operator=(const Model &model) = delete;

		/**
		 Moves the given model to this model.

		 @param[in]		model
						A reference to the model to move.
		 @return		A reference to the moved model
						(i.e. this model).
		 */
		Model &operator=(Model &&model) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this model.

		 @return		A pointer to the clone of this model.
		 */
		UniquePtr< Model > Clone() const {
			return CloneImplementation();
		}

		//---------------------------------------------------------------------
		// Member Methods: Geometry
		//---------------------------------------------------------------------

		/**
		 Returns the start index of this model in the mesh of this model.

		 @return		The start index of this model in the mesh of this model.
		 */
		size_t GetStartIndex() const noexcept {
			return m_start_index;
		}

		/**
		 Returns the number of indices of this model in the mesh of this model.

		 @return		The number of indices of this model in the mesh of this model.
		 */
		size_t GetNumberOfIndices() const noexcept {
			return m_nb_indices;
		}

		/**
		 Returns the AABB of this model.

		 @return		A reference to the AABB of this model.
		 */
		const AABB &GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		 Returns the BS of this model.

		 @return		A reference to the BS of this model.
		 */
		const BS &GetBS() const noexcept {
			return m_bs;
		}

		/**
		 Prepares this model for drawing.
		 */
		void PrepareDrawing() const {
			m_mesh->PrepareDrawing();
		}

		/**
		 Drwas this model.
		 */
		void Draw() const {
			m_mesh->Draw(m_start_index, m_nb_indices);
		}

		//---------------------------------------------------------------------
		// Member Methods: Appearance
		//---------------------------------------------------------------------

		/**
		 Returns the material of this model.

		 @return		A reference to the material of this model.
		 */
		ShadedMaterial *GetMaterial() noexcept {
			return m_material.get();
		}

		/**
		 Returns the material of this model.

		 @return		A reference to the material of this model.
		 */
		const ShadedMaterial *GetMaterial() const noexcept {
			return m_material.get();
		}

		/**
		 Prepares this model for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 @param[in]		scene
						A reference to the scene info.
		 */
		void PrepareShading(ID3D11Buffer *transform, const SceneInfo &scene) const {
			m_material->PrepareShading(transform, scene);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this model.

		 @return		A pointer to the clone of this model.
		 */
		virtual UniquePtr< Model > CloneImplementation() const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the mesh of this model.
		 */
		SharedPtr< const Mesh > m_mesh;

		/**
		 The start index of this model in the mesh of this model.
		 */
		const size_t m_start_index;

		/**
		 The number of indices of this model in the mesh of this model.
		 */
		const size_t m_nb_indices;

		/**
		 The AABB of this model.
		 */
		const AABB m_aabb;

		/**
		 The BS of this model.
		 */
		const BS m_bs;

		/**
		 A pointer to the shaded material of this model.
		 */
		UniquePtr< ShadedMaterial > m_material;
	};
}