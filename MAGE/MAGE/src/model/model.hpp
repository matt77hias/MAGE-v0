#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"
#include "model\model_descriptor.hpp"
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
	class Model : public WorldObject {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit Model(const string &name, const ModelDescriptor &desc,
			const CombinedShader &shader = CreateLambertianShader());
		Model(const Model &model);
		Model(Model &&model) = default;
		virtual ~Model();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		Model &operator=(const Model &model) = delete;
		Model &operator=(Model &&model) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< Model > Clone() const {
			return std::static_pointer_cast< Model >(CloneImplementation());
		}

		void Draw(const LightBuffer &lighting, const TransformBuffer &transform_buffer) const;

		size_t GetStartIndex() const {
			return m_start_index;
		}
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}
		const StaticMesh *GetMesh() const {
			return m_mesh.get();
		}
		Material &GetMaterial() {
			m_material->GetMaterial();
		}
		const Material &GetMaterial() const {
			m_material->GetMaterial();
		}

		size_t GetNumberOfSubModels() const {
			return m_submodels.size();
		}
		SharedPtr< Model > GetSubModel(const string &name) const;
		bool HasSubModel(const string &name) const {
			return GetSubModel(name) != nullptr;
		}
		template< typename ActionT >
		void ForEachSubModel(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Model::Model(const ModelPart model_part, SharedPtr< const StaticMesh > mesh,
			const ShadedMaterial &material);

		explicit Model(const string &name, SharedPtr< const StaticMesh > mesh,
			size_t start_index, size_t nb_indices, const ShadedMaterial &material);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< WorldObject > CloneImplementation() const override {
			return SharedPtr< Model >(new Model(*this));
		}

		virtual void UpdateChildTransforms(bool dirty_ancestor) override;

		HRESULT InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader);
		void AddSubModel(SharedPtr< Model > submodel);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< const StaticMesh > m_mesh;
		const size_t m_start_index;
		const size_t m_nb_indices;
		UniquePtr< ShadedMaterial > m_material;
		vector< SharedPtr< Model > > m_submodels;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.tpp"

#pragma endregion