//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\mesh\mesh.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	Mesh::Mesh(size_t vertex_size, 
		       DXGI_FORMAT index_format, 
		       D3D11_PRIMITIVE_TOPOLOGY primitive_topology)
		: m_vertex_buffer(), 
		m_index_buffer(),
		m_nb_vertices(0u), 
		m_nb_indices(0u), 
		m_vertex_size(vertex_size), 
		m_index_format(index_format),
		m_primitive_topology(primitive_topology) {}

	Mesh::Mesh(Mesh&& mesh) noexcept = default;

	Mesh::~Mesh() = default;

	Mesh& Mesh::operator=(Mesh&& mesh) noexcept = default;
}