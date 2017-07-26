#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of transform buffers used by vertex shaders. 
	 */
	__declspec(align(16)) struct TransformBuffer final : public AlignedData< TransformBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform buffer from the given camera transformation matrices.

		 @param[in]		world_to_view
						The (row-major packed, row-major matrix) world-to-view matrix.
		 @param[in]		view_to_projection
						The (row-major packed, row-major matrix) view-to-projection matrix.
		 */
		explicit TransformBuffer(
			CXMMATRIX world_to_view,
			CXMMATRIX view_to_projection) :
			m_world_to_view(XMMatrixTranspose(world_to_view)),
			m_view_to_projection(XMMatrixTranspose(view_to_projection)) {}

		/**
		 Constructs a transform buffer from the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to copy.
		 */
		TransformBuffer(const TransformBuffer &buffer) = default;

		/**
		 Constructs a transform buffer by moving the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 */
		TransformBuffer(TransformBuffer &&buffer) = default;

		/**
		 Destructs this transform buffer.
		 */
		~TransformBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given transform buffer to this transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to copy.
		 @return		A reference to the copy of the given transform buffer
						(i.e. this transform buffer).
		 */
		TransformBuffer &operator=(const TransformBuffer &buffer) = default;

		/**
		 Moves the given transform buffer to this transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 @return		A reference to the moved transform buffer
						(i.e. this transform buffer).
		 */
		TransformBuffer &operator=(TransformBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the world-to-view matrix of this transform buffer.

		 @return		A reference to the (row-major packed, row-major matrix) 
						world-to-view matrix of this transform buffer.
		 */
		const XMMATRIX GetWorldToViewMatrix() const noexcept {
			return XMMatrixTranspose(m_world_to_view);
		}

		/**
		 Returns the view-to-projection matrix of this transform buffer.

		 @return		A reference to the (row-major packed, row-major matrix) 
						world-to-view matrix of this transform buffer.
		 */
		const XMMATRIX GetViewToProjectionMatrix() const noexcept {
			return XMMatrixTranspose(m_view_to_projection);
		}

		/**
		 Sets the object-specific matrices of this transform buffer.

		 @param[in]		object_to_world
						The (row-major packed, row-major matrix) object-world matrix.
		 @param[in]		view_to_object
						The (row-major packed, row-major matrix) view-to-object matrix
						(i.e. object-to-view inverse matrix).
		 */
		void XM_CALLCONV SetObjectMatrices(
			FXMMATRIX object_to_world,
			FXMMATRIX view_to_object) const noexcept {
			m_object_to_world = XMMatrixTranspose(object_to_world);
			m_object_to_view_inverse_transpose = view_to_object;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera independent, object dependent) (column-major packed, row-major matrix) 
		 object-to-world matrix of this transform buffer for use in HLSL.
		 */
		mutable XMMATRIX m_object_to_world;
		
		/**
		 The (camera dependent, object independent) (column-major packed, row-major matrix) 
		 world-to-view matrix of this transform buffer for use in HLSL.
		 */
		XMMATRIX m_world_to_view;

		/**
		 The (camera dependent, object dependent) (column-major packed, row-major matrix) 
		 object-to-view inverse tranpose matrix (for transforming object space normals) 
		 of this transform buffer for use in HLSL.
		 */
		mutable XMMATRIX m_object_to_view_inverse_transpose;

		/**
		 The (camera dependent, object independent) (column-major packed, row-major matrix) 
		 view-to-projection matrix of this transform buffer for use in HLSL.
		 */
		XMMATRIX m_view_to_projection;
	};

	static_assert(sizeof(TransformBuffer) == 256, "CPU/GPU struct mismatch");
}