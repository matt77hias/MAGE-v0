#pragma once

//-----------------------------------------------------------------------------
// System Defines
//-----------------------------------------------------------------------------
#pragma region

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <d3d11_2.h>

#include <string>
namespace mage {
	using std::string;
	using std::wstring;
}

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "math\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	class MeshObject {

		MeshObject(const string &name, size_t start_index)
			: m_name(name), m_transform(UniquePtr< Transform >(new Transform())),
			m_start_index(start_index), m_nb_indices(0) {}

		virtual ~MeshObject() = default;

		const string &GetName() const {
			return m_name;
		}

		void SetName(const string &name) {
			m_name = name;
		}

		Transform &GetTransform() const {
			return *m_transform.get();
		}

		void SetNumberOfIndices(size_t nb_indices) {
			m_nb_indices = nb_indices;
		}

		void Update(ComPtr< ID3D11DeviceContext2 > device_context) const {
			device_context->DrawIndexed((UINT)m_nb_indices, (UINT)m_start_index, 0);
		}

	private:

		MeshObject(const MeshObject &mesh_object) = delete;
		MeshObject &operator=(const MeshObject &mesh_object) = delete;


		string m_name;

		UniquePtr< Transform > m_transform;

		size_t m_nb_indices;

		size_t m_start_index;
	};
}