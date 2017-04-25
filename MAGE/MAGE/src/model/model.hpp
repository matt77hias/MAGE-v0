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

		explicit Model(SharedPtr< const Mesh > mesh,
			size_t start_index, size_t nb_indices, const ShadedMaterial &material);
		Model(const Model &model);
		Model(Model &&model) = default;
		virtual ~Model() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Model &operator=(const Model &model) = delete;
		Model &operator=(Model &&model) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< Model > Clone() const {
			return CloneImplementation();
		}

		size_t GetStartIndex() const {
			return m_start_index;
		}
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}
		const Mesh *GetMesh() const {
			return m_mesh.get();
		}
		Material &GetMaterial() {
			return m_material->GetMaterial();
		}
		const Material &GetMaterial() const {
			return m_material->GetMaterial();
		}
		ShadedMaterial *GetShadedMaterial() {
			return m_material.get();
		}
		const ShadedMaterial *GetShadedMaterial() const {
			return m_material.get();
		}

		void PrepareDrawing() const {
			m_mesh->PrepareDrawing();
		}
		void PrepareShading(ID3D11Buffer *transform, const Lighting &lighting) const {
			m_material->PrepareShading(transform, lighting);;
		}
		void Draw() const {
			m_mesh->Draw(m_start_index, m_nb_indices);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< Model > CloneImplementation() const {
			return SharedPtr< Model >(new Model(*this));
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< const Mesh > m_mesh;
		const size_t m_start_index;
		const size_t m_nb_indices;
		UniquePtr< ShadedMaterial > m_material;
	};
}