//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "mesh\mesh.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	Mesh::Mesh(ID3D11Device2 *device, ID3D11DeviceContext2 *device_context, size_t vertex_size,
		DXGI_FORMAT index_format, D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: m_device(device), m_device_context(device_context), m_vertex_buffer(), m_index_buffer(),
		m_vertex_size(vertex_size), m_nb_vertices(0), m_nb_indices(0),
		m_index_format(index_format), m_primitive_topology(primitive_topology) {

		Assert(m_device);
		Assert(m_device_context);
	}
}