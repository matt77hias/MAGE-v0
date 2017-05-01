#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"
#include "shader\shaded_material.hpp"
#include "shader\lambertian_shader.hpp"

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

		 @param[in]		mesh
						A pointer to the mesh.
		 @param[in]		start_index
						The start index in the mesh.
		 @param[in]		nb_indices
						The number of indices in the mesh.
		 @param[in]		material
						A reference to the shaded material.
		 */
		explicit Model(SharedPtr< const Mesh > mesh,
			size_t start_index, size_t nb_indices, const ShadedMaterial &material);

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
		Model(Model &&model) = default;

		/**
		 Destructs this model.
		 */
		virtual ~Model() = default;

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
		SharedPtr< Model > Clone() const {
			return CloneImplementation();
		}

		//---------------------------------------------------------------------
		// Member Methods: Geometry
		//---------------------------------------------------------------------

		/**
		 Returns the start index of this model in the mesh of this model.

		 @return		The start index of this model in the mesh of this model.
		 */
		size_t GetStartIndex() const {
			return m_start_index;
		}

		/**
		 Returns the number of indices of this model in the mesh of this model.

		 @return		The number of indices of this model in the mesh of this model.
		 */
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}

		/**
		 Returns the mesh of this model.

		 @return		A pointer to the mesh of this model.
		 */
		const Mesh *GetMesh() const {
			return m_mesh.get();
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
		Material &GetMaterial() {
			return m_material->GetMaterial();
		}

		/**
	 	 Returns the material of this model.

		 @return		A reference to the material of this model.
		 */
		const Material &GetMaterial() const {
			return m_material->GetMaterial();
		}

		/**
		 Returns the shaded material of this model.

		 @return		A reference to the shaded material of this model.
		 */
		ShadedMaterial *GetShadedMaterial() {
			return m_material.get();
		}

		/**
		 Returns the shaded material of this model.

		 @return		A reference to the shaded material of this model.
		 */
		const ShadedMaterial *GetShadedMaterial() const {
			return m_material.get();
		}

		/**
		 Prepares this model for shading.

		 @pre			@a transform is not equal to @c nullptr.
		 @param[in]		transform
						A pointer to the transform buffer.
		 @param[in]		lighting
						A reference to the lighting buffer.
		 */
		void PrepareShading(ID3D11Buffer *transform, const Lighting &lighting) const {
			m_material->PrepareShading(transform, lighting);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this model.

		 @return		A pointer to the clone of this model.
		 */
		virtual SharedPtr< Model > CloneImplementation() const {
			return SharedPtr< Model >(new Model(*this));
		}

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
		 A pointer to the shaded material of this model.
		 */
		UniquePtr< ShadedMaterial > m_material;
	};
}