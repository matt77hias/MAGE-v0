#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"
#include "shader\shaded_material.hpp"

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

		virtual ~Model() {
			RemoveAndDestructAllElements(m_submodels);
		}

		virtual Model *Clone() const = 0;

		virtual void Draw(const World &world, const TransformBuffer &transform_buffer) const = 0;
		
		set< SubModel * >::iterator SubModelsBegin() {
			return m_submodels.begin();
		}
		set< SubModel * >::iterator SubModelsEnd() {
			return m_submodels.end();
		}
		set< SubModel * >::const_iterator SubModelsBegin() const {
			return m_submodels.cbegin();
		}
		set< SubModel * >::const_iterator SubModelsEnd() const {
			return m_submodels.cend();
		}
		size_t GetNumberOfSubModels() const {
			return m_submodels.size();
		}
		SubModel *GetSubModel(const string &name) const;
		bool HasSubModel(const string &name) const {
			return GetSubModel(name) != nullptr;
		}
		void AddSubModel(SubModel *submodel);

	protected:

		Model(const string &name);
		Model(const Model &model);
		Model(Model &&model)
			: WorldObject(model), m_submodels(std::move(model.m_submodels)) {}
		
	private:

		Model &operator=(const Model &model) = delete;
		Model &operator=(Model &&model) = delete;

		set< SubModel *, std::less<> > m_submodels;
	};

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	/**
	 A class of submodels.
	 */
	class SubModel : public Model {

	public:

		SubModel(const string &name, size_t start_index, size_t nb_indices, const ShadedMaterial &material);
		SubModel(const SubModel &submodel);
		SubModel(SubModel &&submodel)
			: Model(submodel), 
			m_start_index(submodel.m_start_index),
			m_nb_indices(submodel.m_nb_indices), 
			m_material(std::move(submodel.m_material)) {
			submodel.m_material = nullptr;
		}
		virtual ~SubModel() {
			delete m_material;
		}

		virtual SubModel *Clone() const {
			return new SubModel(*this);
		}

		virtual void Draw(const World &world, const TransformBuffer &transform_buffer) const override {
			transform_buffer.SetModelToWorld(GetTransform().GetObjectToWorldMatrix());
			m_material->Draw(world, transform_buffer);
		}

		size_t GetStartIndex() const {
			return m_start_index;
		}
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}
		Material &GetMaterial() const {
			m_material->GetMaterial();
		}

	private:

		SubModel &operator=(const SubModel &submodel) = delete;
		SubModel &operator=(SubModel &&submodel) = delete;

		const size_t m_start_index;
		const size_t m_nb_indices;
		ShadedMaterial *m_material;
	};
}