#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"
#include "model\model_descriptor.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/*
	 A class of models.
	 */
	class MeshModel : public Model {

	public:

		MeshModel(const string &name, const ModelDescriptor &desc, const CombinedShader &shader);
		MeshModel(const MeshModel &model)
			: Model(model), m_mesh(model.m_mesh) {}
		MeshModel(MeshModel &&model)
			: Model(model), m_mesh(std::move(model.m_mesh)) {}

		virtual ~MeshModel() = default;

		virtual MeshModel *Clone() const override {
			return new MeshModel(*this);
		}

		const Mesh &GetMesh() const {
			return *m_mesh;
		}

	protected:

		virtual void RenderModel(ID3D11DeviceContext2 &device_context, const World &world, const TransformBuffer &transform_buffer) const override {
			UNUSED(world);
			UNUSED(transform_buffer);
			m_mesh->Render(device_context);
		}

	private:

		MeshModel &operator=(const MeshModel &model) = delete;
		MeshModel &operator=(MeshModel &&model) = delete;

		HRESULT InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader);

		SharedPtr< Mesh > m_mesh;
	};
}