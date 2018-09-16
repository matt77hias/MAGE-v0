#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "spectrum\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	/**
	 A struct of model buffers.
	 */
	struct alignas(16) ModelBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) object-to-world matrix of 
		 this model buffer.
		 */
		XMMATRIX m_object_to_world = {};
		
		/**
		 The (column-major packed, row-major matrix) object-to-world inverse 
		 transpose matrix (normal-to-world matrix) of this model buffer.
		 */
		XMMATRIX m_normal_to_world = {};

		/**
		 The (column-major packed, row-major matrix) texture transform matrix 
		 of this model buffer.
		 */
		XMMATRIX m_texture_transform = {};

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The (linear) base color of the material of this model buffer.
		 */
		RGBA m_base_color = {};

		/**
		 The (linear) roughness of the material of this model buffer.
		 */
		F32 m_roughness = 0.0f;

		/**
		 The (linear) metalness of the material of this model buffer.
		 */
		F32 m_metalness = 0.0f;

		/**
		 The padding of this world buffer.
		 */
		U32x2 m_padding = {};
	};

	static_assert(224u == sizeof(ModelBuffer), "CPU/GPU struct mismatch");
}