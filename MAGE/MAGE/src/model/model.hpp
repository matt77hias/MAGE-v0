#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "world\world_object.hpp"
#include "shader\shaded_material.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
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

		void Render(ID3D11DeviceContext2 &device_context, const World &world, const TransformBuffer &transform_buffer) const {
			RenderModel(device_context, world, transform_buffer);
			RenderSubModels(device_context, world, transform_buffer);
		}
		
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

		virtual void RenderModel(ID3D11DeviceContext2 &device_context, const World &world, const TransformBuffer &transform_buffer) const = 0;
		
	private:

		Model &operator=(const Model &model) = delete;

		void RenderSubModels(ID3D11DeviceContext2 &device_context, const World &world, const TransformBuffer &transform_buffer) const;

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
		virtual ~SubModel() {
			delete m_material;
		}

		virtual SubModel *Clone() const {
			return new SubModel(*this);
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

	protected:

		virtual void RenderModel(ID3D11DeviceContext2 &device_context, const World &world, const TransformBuffer &transform_buffer) const override {
			// Appearance
			transform_buffer.SetModelToWorld(GetTransform().GetObjectToWorldMatrix());
			m_material->Render(device_context, world, transform_buffer);
			// Geometry
			device_context.DrawIndexed(static_cast< UINT >(m_nb_indices), static_cast< UINT >(m_start_index), 0);
		}
		
	private:

		SubModel &operator=(const SubModel &submodel) = delete;

		const size_t m_start_index;
		const size_t m_nb_indices;
		ShadedMaterial *m_material;
	};

	inline void Model::RenderSubModels(ID3D11DeviceContext2 &device_context, const World &world, const TransformBuffer &transform_buffer) const {
		for (set< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			(*it)->Render(device_context, world, transform_buffer);
		}
	}
}