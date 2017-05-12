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
						A reference to the (row-major) world-to-view matrix.
		 @param[in]		view_to_projection
						A reference to the (row-major) view-to-projection matrix.
		 */
		explicit TransformBuffer(const XMMATRIX &world_to_view,
			const XMMATRIX &view_to_projection) :
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
		 Returns the (row-major) world-to-view matrix of this transform buffer.

		 @return		A reference to the (row-major) world-to-view matrix
						of this transform buffer.
		 */
		const XMMATRIX GetWorldToViewMatrix() const {
			return XMMatrixTranspose(m_world_to_view);
		}

		/**
		 Returns the (row-major) view-to-projection matrix of this transform buffer.

		 @return		A reference to the (row-major) world-to-view matrix
						of this transform buffer.
		 */
		const XMMATRIX GetViewToProjectionMatrix() const {
			return XMMatrixTranspose(m_view_to_projection);
		}

		/**
		 Sets the object-specific matrices of this transform buffer.

		 @param[in]		object_to_world
						A reference to the (row-major) object-world matrix.
		 @param[in]		view_to_object
						A reference to the (row-major) view-to-object matrix
						(i.e. object-to-view inverse matrix).
		 */
		void SetObjectMatrices(const XMMATRIX &object_to_world,
			const XMMATRIX &view_to_object) const {
			m_object_to_world 
				= XMMatrixTranspose(object_to_world);
			m_object_to_view_inverse_transpose
				= view_to_object;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera independent, object dependent) (column-major) object-to-world matrix
		 of this transform buffer for use in HLSL.
		 */
		mutable XMMATRIX m_object_to_world;
		
		/**
		 The (camera dependent, object independent) (column-major) world-to-view matrix
		 of this transform buffer for use in HLSL.
		 */
		XMMATRIX m_world_to_view;

		/**
		 The (camera dependent, object dependent) (column-major) object-to-view inverse tranpose matrix 
		 (for transforming object space normals) of this transform buffer for use in HLSL.
		 */
		mutable XMMATRIX m_object_to_view_inverse_transpose;

		/**
		 The (camera dependent, object independent) (column-major) view-to-projection matrix 
		 of this transform buffer for use in HLSL.
		 */
		XMMATRIX m_view_to_projection;
	};

	static_assert(sizeof(TransformBuffer) == 256, "CPU/GPU struct mismatch");
}