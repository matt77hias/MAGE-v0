#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.hpp"
#include "model\model_loader.hpp"
#include "mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// MeshModel
	//-------------------------------------------------------------------------

	/*
	 A class of models.

	 @tparam		T
					The vertex type.
	 */
	template < typename Vertex >
	class MeshModel : public Model {

	public:

		MeshModel(const string &name, ComPtr< ID3D11Device2 > device, const wstring &fname, const MeshDescriptor &desc, const CombinedShader &shader);
		MeshModel(const string &name, ComPtr< ID3D11Device2 > device, ModelOutput< Vertex > &buffer, const CombinedShader &shader);
		MeshModel(const MeshModel< Vertex > &model)
			: Model(model), m_mesh(model.m_mesh) {}
		virtual ~MeshModel() = default;

		virtual MeshModel< Vertex > *Clone() const override {
			return new MeshModel< Vertex >(*this);
		}

		const SharedPtr< Mesh< Vertex > > GetMesh() const {
			return m_mesh;
		}

	protected:

		virtual void RenderModel(ComPtr< ID3D11DeviceContext2 > device_context, const World &world, const TransformBuffer &transform_buffer) const override {
			UNUSED(world);
			UNUSED(transform_buffer);
			m_mesh->Render(device_context);
		}

	private:

		MeshModel< Vertex > &operator=(const MeshModel< Vertex > &model) = delete;

		HRESULT InitializeModel(ComPtr< ID3D11Device2 > device, ModelOutput< Vertex > &buffer, const CombinedShader &shader);

		SharedPtr< Mesh< Vertex > > m_mesh;
	};

	//-------------------------------------------------------------------------
	// MeshSubModel
	//-------------------------------------------------------------------------

	class MeshSubModel : public SubModel {

	public:

		MeshSubModel(const string &name, size_t start_index, size_t nb_indices, const ShadedMaterial &material)
			: SubModel(name, material), m_start_index(start_index), m_nb_indices(nb_indices) {}
		MeshSubModel(const MeshSubModel &submodel)
			: SubModel(submodel),
			m_start_index(submodel.m_start_index),
			m_nb_indices(submodel.m_nb_indices) {}
		virtual ~MeshSubModel() = default;

		virtual MeshSubModel *Clone() const override {
			return new MeshSubModel(*this);
		}

		size_t GetStartIndex() const {
			return m_start_index;
		}
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}

	protected:

		virtual void RenderGeometry(ComPtr< ID3D11DeviceContext2 > device_context) const override {
			device_context->DrawIndexed((UINT)m_nb_indices, (UINT)m_start_index, 0);
		}

	private:

		MeshSubModel &operator=(const MeshSubModel &submodel) = delete;

		const size_t m_start_index;
		const size_t m_nb_indices;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\meshmodel.tpp"

#pragma endregion