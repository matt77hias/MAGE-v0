#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"
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

		virtual void Draw(const World &world, const TransformBuffer &transform_buffer) const {
			UNUSED(world);
			UNUSED(transform_buffer);
		}
		
		size_t GetNumberOfSubModels() const {
			return m_submodels.size();
		}
		SubModel *GetSubModel(const string &name) const;
		bool HasSubModel(const string &name) const {
			return GetSubModel(name) != nullptr;
		}
		void AddSubModel(SubModel *submodel);
		template< typename ActionT >
		void ForEachSubModel(ActionT action) const;

	protected:

		Model(const string &name);
		Model(const Model &model);
		Model(Model &&model)
			: WorldObject(model), m_submodels(std::move(model.m_submodels)) {}

		virtual void UpdateChildTransforms(bool dirty_ancestor) override;
		
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
		virtual ~SubModel() = default;

		virtual SubModel *Clone() const {
			return new SubModel(*this);
		}

		void Draw(const Mesh &mesh, const World &world, const TransformBuffer &transform_buffer) const {
			// Appearance
			transform_buffer.SetModelToWorld(GetTransform().GetObjectToWorldMatrix());
			m_material->Draw(world, transform_buffer);
			// Geometry
			mesh.Draw(m_start_index, m_nb_indices);
			// Childs
			ForEachSubModel([&](SubModel &submodel) {
				submodel.Draw(mesh, world, transform_buffer);
			});
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
		UniquePtr< ShadedMaterial > m_material;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.tpp"

#pragma endregion