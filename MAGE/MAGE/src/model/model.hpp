//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_loader.hpp"
#include "mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of models.

	 @tparam		T
					The vertex type.
	 */
	template < typename Vertex >
	class Model {

	public:

		Model(const string &name, ComPtr< ID3D11Device2 > device, const string &fname, const MeshDescriptor &desc);
		Model(const Model< Vertex > &model);
		virtual ~Model() = default;

		Transform &GetTransform() const {
			return *m_transform.get();
		}

		void Update(ComPtr< ID3D11DeviceContext2 > device_context) const;

	protected:

		HRESULT InitializeModel(ComPtr< ID3D11Device2 > device, const string &fname, const MeshDescriptor &desc);

	private:

		Model< Vertex > &operator=(const Model< Vertex > &model) = delete;

		string m_name;

		UniquePtr< Transform > m_transform;

		SharedPtr< Mesh<Vertex> > m_mesh;

		//vector< pair< MeshObject, Material > > m_childs;
	};
}
//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.tpp"

#pragma endregion
