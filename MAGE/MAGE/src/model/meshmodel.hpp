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

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MeshModel(const string &name, const ModelDescriptor &desc, const CombinedShader &shader);
		MeshModel(const MeshModel &model) = default;
		MeshModel(MeshModel &&model) = default;
		virtual ~MeshModel() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		MeshModel &operator=(const MeshModel &model) = delete;
		MeshModel &operator=(MeshModel &&model) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual MeshModel *Clone() const override {
			return new MeshModel(*this);
		}

		virtual void Draw(const World &world, const TransformBuffer &transform_buffer) const override;

		const StaticMesh &GetMesh() const {
			return *m_mesh;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		HRESULT InitializeModel(const ModelDescriptor &desc, const CombinedShader &shader);

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< StaticMesh > m_mesh;
	};
}