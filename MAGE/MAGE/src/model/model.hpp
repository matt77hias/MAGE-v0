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

	// Forward declaration
	class SubModel;

	//-------------------------------------------------------------------------
	// Model
	//-------------------------------------------------------------------------
	
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

		virtual void Draw(const LightBuffer &lighting, const TransformBuffer &transform_buffer) const;

		const StaticMesh *GetMesh() const {
			return m_mesh.get();
		}

		size_t GetNumberOfSubModels() const {
			return m_submodels.size();
		}
		SharedPtr< SubModel > GetSubModel(const string &name) const;
		bool HasSubModel(const string &name) const {
			return GetSubModel(name) != nullptr;
		}
		template< typename ActionT >
		void ForEachSubModel(ActionT action) const;

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		explicit Model(const string &name, SharedPtr< StaticMesh > mesh)
			: WorldObject(name), m_mesh(mesh) {}

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void AddSubModel(SharedPtr< SubModel > submodel);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< WorldObject > CloneImplementation() const override {
			return SharedPtr< Model >(new Model(*this));
		}

		virtual void UpdateChildTransforms(bool dirty_ancestor) override;

		HRESULT InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< StaticMesh > m_mesh;
		vector< SharedPtr< SubModel > > m_submodels;
	};

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	/**
	 A class of submodels.
	 */
	class SubModel : public Model {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit SubModel(const string &name, SharedPtr< StaticMesh > mesh,
			size_t start_index, size_t nb_indices, const ShadedMaterial &material);
		SubModel(const SubModel &submodel);
		SubModel(SubModel &&submodel) = default;
		virtual ~SubModel() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		SubModel &operator=(const SubModel &submodel) = delete;
		SubModel &operator=(SubModel &&submodel) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< SubModel > Clone() const {
			return std::static_pointer_cast< SubModel >(CloneImplementation());
		}

		virtual void Draw(const LightBuffer &lighting, const TransformBuffer &transform_buffer) const final;

		size_t GetStartIndex() const {
			return m_start_index;
		}
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}
		Material &GetMaterial() {
			m_material->GetMaterial();
		}
		const Material &GetMaterial() const {
			m_material->GetMaterial();
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< WorldObject > CloneImplementation() const override {
			return SharedPtr< SubModel >(new SubModel(*this));
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		const size_t m_start_index;
		const size_t m_nb_indices;
		UniquePtr< ShadedMaterial > m_material;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.tpp"

#pragma endregion