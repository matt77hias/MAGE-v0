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

		SharedPtr< StaticMesh > GetMesh() const {
			return m_mesh;
		}
		vector< Material >::const_iterator MaterialsBegin() const {
			return m_materials.cbegin();
		}
		vector< Material >::const_iterator MaterialsEnd() const {
			return m_materials.cend();
		}
		vector< ModelPart >::const_iterator ModelPartsBegin() const {
			return m_model_parts.cbegin();
		}
		vector< ModelPart >::const_iterator ModelPartsEnd() const {
			return m_model_parts.cend();
		}

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