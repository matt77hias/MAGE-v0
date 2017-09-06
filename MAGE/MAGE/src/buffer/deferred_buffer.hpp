#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <stdint.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// DeferredBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of deferred buffers used by pixel shaders.
	 */
	_declspec(align(16)) struct DeferredBuffer final : public AlignedData< DeferredBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a deferred buffer.
		 */
		DeferredBuffer()
			: m_projection_values{},
			m_mat1_start(0.0f), m_mat1_range(0.0f),
			m_mat2_start(0.0f), m_mat2_range(0.0f) {}

		/**
		 Constructs a deferred buffer from the given deferred buffer.

		 @param[in]		buffer
						A reference to the deferred buffer to copy.
		 */
		DeferredBuffer(const DeferredBuffer &buffer) = default;
		
		/**
		 Constructs a deferred buffer by moving the given deferred buffer.

		 @param[in]		buffer
						A reference to the deferred buffer to move.
		 */
		DeferredBuffer(DeferredBuffer &&buffer) = default;

		/**
		 Destructs this deferred buffer.
		 */
		~DeferredBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given deferred buffer to this deferred buffer.

		 @param[in]		buffer
						A reference to the deferred buffer to copy.
		 @return		A reference to the copy of the given deferred buffer
						(i.e. this deferred buffer).
		 */
		DeferredBuffer &operator=(const DeferredBuffer &buffer) = default;

		/**
		 Moves the given deferred buffer to this deferred buffer.

		 @param[in]		buffer
						A reference to the deferred buffer to move.
		 @return		A reference to the moved deferred buffer
						(i.e. this deferred buffer).
		 */
		DeferredBuffer &operator=(DeferredBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Assignment Operators: Transforms
		//---------------------------------------------------------------------

		/**
		 The projection values of the view-to-projection transformation matrix
		 of this deferred buffer.
		 */
		XMVECTOR m_projection_values;

		//---------------------------------------------------------------------
		// Assignment Operators: Material
		//---------------------------------------------------------------------

		/**
		 The 1st BRDF dependent material coefficient start
		 of this deferred buffer.
		 */
		float m_mat1_start;

		/**
		 The 1st BRDF dependent material coefficient range
		 of this deferred buffer.
		 */
		float m_mat1_range;

		/**
		 The 2nd BRDF dependent material coefficient start
		 of this deferred buffer.
		 */
		float m_mat2_start;

		/**
		 The 2nd BRDF dependent material coefficient range
		 of this deferred buffer.
		 */
		float m_mat2_range;
	};

	static_assert(sizeof(DeferredBuffer) == 32, "CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// DeferredComputeBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of deferred compute buffers used by pixel shaders.
	 */
	_declspec(align(16)) struct DeferredComputeBuffer final : public AlignedData< DeferredComputeBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a deferred compute buffer.
		 */
		DeferredComputeBuffer()
			: m_projection_values{},
			m_mat1_start(0.0f), m_mat1_range(0.0f),
			m_mat2_start(0.0f), m_mat2_range(0.0f),
			m_resolution_minus1{}, m_padding0{} {}

		/**
		 Constructs a deferred compute buffer from the given deferred compute buffer.

		 @param[in]		buffer
						A reference to the deferred compute buffer to copy.
		 */
		DeferredComputeBuffer(const DeferredComputeBuffer &buffer) = default;
		
		/**
		 Constructs a deferred compute buffer by moving the given deferred compute buffer.

		 @param[in]		buffer
						A reference to the deferred compute buffer to move.
		 */
		DeferredComputeBuffer(DeferredComputeBuffer &&buffer) = default;

		/**
		 Destructs this deferred compute buffer.
		 */
		~DeferredComputeBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given deferred compute buffer to this deferred compute buffer.

		 @param[in]		buffer
						A reference to the deferred compute buffer to copy.
		 @return		A reference to the copy of the given deferred compute buffer
						(i.e. this deferred compute buffer).
		 */
		DeferredComputeBuffer &operator=(const DeferredComputeBuffer &buffer) = default;

		/**
		 Moves the given deferred compute buffer to this deferred compute buffer.

		 @param[in]		buffer
						A reference to the deferred compute buffer to move.
		 @return		A reference to the moved deferred compute buffer
						(i.e. this deferred compute buffer).
		 */
		DeferredComputeBuffer &operator=(DeferredComputeBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Assignment Operators: Transforms
		//---------------------------------------------------------------------

		/**
		 The projection values of the view-to-projection transformation matrix
		 of this deferred compute buffer.
		 */
		XMVECTOR m_projection_values;

		//---------------------------------------------------------------------
		// Assignment Operators: Material
		//---------------------------------------------------------------------

		/**
		 The 1st BRDF dependent material coefficient start
		 of this deferred compute buffer.
		 */
		float m_mat1_start;

		/**
		 The 1st BRDF dependent material coefficient range
		 of this deferred compute buffer.
		 */
		float m_mat1_range;

		/**
		 The 2nd BRDF dependent material coefficient start
		 of this deferred compute buffer.
		 */
		float m_mat2_start;

		/**
		 The 2nd BRDF dependent material coefficient range
		 of this deferred compute buffer.
		 */
		float m_mat2_range;

		/**
		 The (x, y) resolution (minus 1) of the deferred compute buffer.
		 */
		uint32_t m_resolution_minus1[2];

		/**
		 The padding of the deferred compute buffer.
		 */
		uint32_t m_padding0[2];
	};

	static_assert(sizeof(DeferredComputeBuffer) == 48, "CPU/GPU struct mismatch");
}