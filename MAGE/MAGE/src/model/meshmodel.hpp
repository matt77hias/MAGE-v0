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

		virtual void Draw(const World &world, const TransformBuffer &transform_buffer) const override {
			m_mesh->PrepareDrawing();
			ForEachSubModel([&](SubModel *submodel) {
				submodel->Draw(world, transform_buffer);
				m_mesh->Draw(submodel->GetStartIndex(), submodel->GetNumberOfIndices());
			});
		}

		const StaticMesh &GetMesh() const {
			return *m_mesh;
		}

	private:

		MeshModel &operator=(const MeshModel &model) = delete;
		MeshModel &operator=(MeshModel &&model) = delete;

		HRESULT InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader);

		SharedPtr< StaticMesh > m_mesh;
	};
}