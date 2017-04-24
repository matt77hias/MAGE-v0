#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_loader.hpp"
#include "mesh\static_mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ModelDescriptor : public FileResource {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		template < typename VertexT >
		explicit ModelDescriptor(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context,
			const wstring &fname, const MeshDescriptor< VertexT > &desc = MeshDescriptor< VertexT >());
		ModelDescriptor(const ModelDescriptor &desc) = delete;
		ModelDescriptor(ModelDescriptor &&desc) = default;
		virtual ~ModelDescriptor() {
			m_materials.clear();
			m_model_parts.clear();
		}

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ModelDescriptor &operator=(const ModelDescriptor &desc) = delete;
		ModelDescriptor &operator=(ModelDescriptor &&desc) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		SharedPtr< const StaticMesh > GetMesh() const {
			return m_mesh;
		}

		template< typename ActionT >
		void ForEachMaterial(ActionT action) const;
		template< typename ActionT >
		void ForEachModelPart(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< StaticMesh > m_mesh;
		vector< Material > m_materials;
		vector< ModelPart > m_model_parts;
	};

	template < typename VertexT >
	SharedPtr< ModelDescriptor > CreateModelDescriptor(const wstring &fname, const MeshDescriptor< VertexT > &desc);
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_descriptor.tpp"

#pragma endregion