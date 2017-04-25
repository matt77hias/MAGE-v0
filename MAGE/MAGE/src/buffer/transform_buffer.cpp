//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "buffer\transform_buffer.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	TransformBuffer::TransformBuffer(const XMMATRIX &world_to_view, const XMMATRIX &view_to_projection) 
		: m_world_to_view(XMMatrixTranspose(world_to_view)), 
		m_view_to_projection(XMMatrixTranspose(view_to_projection)) {
		
		XMVECTOR determinant_v;
		m_world_to_view_inverse_transpose = XMMatrixInverse(&determinant_v, world_to_view);
		float determinant = 0.0f;
		XMStoreFloat(&determinant, determinant_v);
		Assert(determinant != 0.0f);
	}
}