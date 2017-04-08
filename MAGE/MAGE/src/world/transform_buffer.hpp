#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	struct TransformBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit TransformBuffer(const Camera &camera);
		TransformBuffer(const TransformBuffer &buffer) = default;
		TransformBuffer(TransformBuffer &&buffer) = default;
		~TransformBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		TransformBuffer &operator=(const TransformBuffer &buffer) = default;
		TransformBuffer &operator=(TransformBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void SetModelToWorld(const XMMATRIX &model_to_world) const {
			m_model_to_world = XMMatrixTranspose(model_to_world);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		mutable XMMATRIX m_model_to_world;
		XMMATRIX m_world_to_view;
		XMMATRIX m_world_to_view_inverse_transpose;
		XMMATRIX m_view_to_projection;
	};
}