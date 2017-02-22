#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform.hpp"
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
	class Model {

	public:

		virtual ~Model() {
			RemoveAndDestructAllElements(m_submodels);
		}

		virtual Model *Clone() const = 0;

		void Render(ComPtr< ID3D11DeviceContext2 > device_context, const World &world, const TransformBuffer &transform_buffer) const {
			RenderModel(device_context, world, transform_buffer);
			RenderSubModels(device_context, world, transform_buffer);
		}
		
		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		Transform &GetTransform() const {
			return *m_transform;
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

		Model(const string &name)
			: m_name(name), m_transform(new Transform()) {}
		Model(const Model &model);

		virtual void RenderModel(ComPtr< ID3D11DeviceContext2 > device_context, const World &world, const TransformBuffer &transform_buffer) const = 0;
		
	private:

		Model &operator=(const Model &model) = delete;

		void RenderSubModels(ComPtr< ID3D11DeviceContext2 > device_context, const World &world, const TransformBuffer &transform_buffer) const;

		string m_name;
		SharedPtr< Transform > m_transform;
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

		virtual ~SubModel() {
			delete m_material;
		}

		virtual SubModel *Clone() const = 0;

		Material &GetMaterial() const {
			m_material->GetMaterial();
		}

	protected:

		SubModel(const string &name, const ShadedMaterial &material)
			: Model(name), m_material(new ShadedMaterial(material)) {}
		SubModel(const SubModel &submodel);

		void RenderModel(ComPtr< ID3D11DeviceContext2 > device_context, const World &world, const TransformBuffer &transform_buffer) const override {
			RenderMaterial(device_context, world, transform_buffer);
			RenderGeometry(device_context);
		}
		virtual void RenderGeometry(ComPtr< ID3D11DeviceContext2 > device_context) const = 0;
		
	private:

		SubModel &operator=(const SubModel &submodel) = delete;

		void RenderMaterial(ComPtr< ID3D11DeviceContext2 > device_context, const World &world, const TransformBuffer &transform_buffer) const {
			transform_buffer.model_to_world = XMMatrixTranspose(GetTransform().GetObjectToWorldMatrix());
			m_material->Render(device_context, world, transform_buffer);
		}

		ShadedMaterial *m_material;
	};

	inline void Model::RenderSubModels(ComPtr< ID3D11DeviceContext2 > device_context, const World &world, const TransformBuffer &transform_buffer) const {
		for (set< SubModel * >::const_iterator it = m_submodels.cbegin(); it != m_submodels.cend(); ++it) {
			(*it)->Render(device_context, world, transform_buffer);
		}
	}
}