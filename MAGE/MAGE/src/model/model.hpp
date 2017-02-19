//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "rendering\rendering.hpp"
#include "math\transform.hpp"
#include "model\model_loader.hpp"
#include "mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions and Declarations
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration
	template < typename Vertex >
	class SubModel;

	//-------------------------------------------------------------------------
	// Model
	//-------------------------------------------------------------------------

	/**
	 A class of models.

	 @tparam		T
					The vertex type.
	 */
	template < typename Vertex >
	class Model {

	public:

		Model(const string &name, ComPtr< ID3D11Device2 > device, const wstring &fname, const MeshDescriptor &desc);
		virtual ~Model() {
			RemoveAllChilds();
		}

		virtual Model< Vertex > *Clone() const {
			return new Model< Vertex >(*this);
		}

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		size_t GetNumberOfIndices() const {
			return m_mesh->GetNumberOfIndices();
		}
		Transform &GetTransform() const {
			return *m_transform;
		}

		void Update(ComPtr< ID3D11DeviceContext2 > device_context) const;

	protected:

		Model(const Model< Vertex > &model);

		HRESULT InitializeModel(ComPtr< ID3D11Device2 > device, const wstring &fname, const MeshDescriptor &desc);

	private:

		Model< Vertex > &operator=(const Model< Vertex > &model) = delete;

		void AddChild(SubModel< Vertex > *child);
		void RemoveAllChilds();

		string m_name;
		SharedPtr< Mesh< Vertex > > m_mesh;
		SharedPtr< Transform > m_transform;
		set< SubModel< Vertex > *, std::less<> > m_childs;
	};

	//-------------------------------------------------------------------------
	// SubModel
	//-------------------------------------------------------------------------

	/**
	 A class of submodels.

	 @tparam		T
					The vertex type.
	 */
	template < typename Vertex >
	class SubModel final {

	public:

		const string &GetName() const {
			return m_name;
		}
		void SetName(const string &name) {
			m_name = name;
		}
		size_t GetStartIndex() const {
			return m_start_index;
		}
		size_t GetNumberOfIndices() const {
			return m_nb_indices;
		}
		Transform &GetTransform() const {
			return *m_transform;
		}

	private:

		friend class Model< Vertex >;

		SubModel(const string &name, size_t start_index, size_t nb_indices)
			: m_name(name), m_start_index(start_index), m_nb_indices(nb_indices),
			m_transform(new Transform()) {}
		SubModel(const SubModel< Vertex > &submodel);
		~SubModel() {
			RemoveAllChilds();
		}

		SubModel< Vertex > &operator=(const SubModel< Vertex > &submodel) = delete;

		void AddChild(SubModel< Vertex > *child);
		void RemoveAllChilds();

		void Update(ComPtr< ID3D11DeviceContext2 > device_context) const;

		string m_name;
		SharedPtr< Transform > m_transform;
		const size_t m_start_index;
		const size_t m_nb_indices;
		set< SubModel< Vertex > *, std::less<> > m_childs;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model.tpp"

#pragma endregion
