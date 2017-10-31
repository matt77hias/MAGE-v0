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

	//-------------------------------------------------------------------------
	// CameraBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of camera buffers.
	 */
	_declspec(align(16)) struct CameraBuffer final 
		: public AlignedData< CameraBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera buffer.
		 */
		CameraBuffer()
			: m_view_to_projection{}, 
			m_projection_to_view{},
			m_world_to_view{}, 
			m_view_to_world{},
			m_viewport_top_left_x(0), 
			m_viewport_top_left_y(0),
			m_viewport_width(0),
			m_viewport_height(0),
			m_viewport_inv_width_minus1(0.0f),
			m_viewport_inv_height_minus1(0.0f){}

		/**
		 Constructs a camera buffer from the given camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to copy.
		 */
		CameraBuffer(const CameraBuffer &buffer) = default;
		
		/**
		 Constructs a camera buffer by moving the given camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to move.
		 */
		CameraBuffer(CameraBuffer &&buffer) = default;

		/**
		 Destructs this camera buffer.
		 */
		~CameraBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given camera buffer to this camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to copy.
		 @return		A reference to the copy of the given camera buffer (i.e. 
						this camera buffer).
		 */
		CameraBuffer &operator=(const CameraBuffer &buffer) = default;

		/**
		 Moves the given camera buffer to this camera buffer.

		 @param[in]		buffer
						A reference to the camera buffer to move.
		 @return		A reference to the moved camera buffer (i.e. this camera 
						buffer).
		 */
		CameraBuffer &operator=(CameraBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera dependent) (column-major packed, row-major matrix) 
		 view-to-projection matrix of this camera buffer for use in HLSL.
		 */
		XMMATRIX m_view_to_projection;

		/**
		 The (camera dependent) (column-major packed, row-major matrix) 
		 projection-to-view matrix of this camera buffer for use in HLSL.
		 */
		XMMATRIX m_projection_to_view;

		/**
		 The (camera dependent) (column-major packed, row-major matrix) 
		 world-to-view matrix of this camera buffer for use in HLSL.
		 */
		XMMATRIX m_world_to_view;

		/**
		 The (camera dependent) (column-major packed, row-major matrix) 
		 view-to-world matrix of this camera buffer for use in HLSL.
		 */
		XMMATRIX m_view_to_world;

		/**
		 The x coordinate of the left hand side of the viewport of this camera 
		 buffer.
		 */
		U32 m_viewport_top_left_x;

		/**
		 The y coordinate of the left hand side of the viewport of this camera 
		 buffer.
		 */
		U32 m_viewport_top_left_y;

		/**
		 The width of the viewport of this camera buffer. 
		 */
		U32 m_viewport_width;

		/**
		 The height of the viewport of this camera buffer. 
		 */
		U32 m_viewport_height;

		/**
		 The inverse width of the viewport minus 1 of this camera buffer. 
		 */
		float m_viewport_inv_width_minus1;

		/**
		 The inverse height of the viewport minus 1 of this camera buffer. 
		 */
		float m_viewport_inv_height_minus1;
	};

	static_assert(sizeof(CameraBuffer) == 288, "CPU/GPU struct mismatch");
}