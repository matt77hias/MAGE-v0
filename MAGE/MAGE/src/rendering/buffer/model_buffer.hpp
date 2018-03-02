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
namespace mage {

	/**
	 A struct of model buffers.
	 */
	struct alignas(16) ModelBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model buffer.
		 */
		ModelBuffer() noexcept
			: m_object_to_world{},
			m_normal_to_world{},
			m_texture_transform{},
			m_base_color{}, 
			m_roughness(0.0f),
			m_metalness(0.0f),
			m_padding{} {}

		/**
		 Constructs a model buffer from the given model buffer.

		 @param[in]		buffer
						A reference to the model buffer to copy.
		 */
		ModelBuffer(const ModelBuffer& buffer) noexcept = default;
		
		/**
		 Constructs a model buffer by moving the given model 
		 buffer.

		 @param[in]		buffer
						A reference to the model buffer to move.
		 */
		ModelBuffer(ModelBuffer&& buffer) noexcept = default;

		/**
		 Destructs this model buffer.
		 */
		~ModelBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given model buffer to this model buffer.

		 @param[in]		buffer
						A reference to the model buffer to copy.
		 @return		A reference to the copy of the given model buffer (i.e. 
						this model buffer).
		 */
		ModelBuffer& operator=(const ModelBuffer& buffer) = default;

		/**
		 Moves the given model buffer to this model buffer.

		 @param[in]		buffer
						A reference to the model buffer to move.
		 @return		A reference to the moved model buffer (i.e. this model 
						buffer).
		 */
		ModelBuffer& operator=(ModelBuffer&& buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) object-to-world matrix of 
		 this model buffer.
		 */
		XMMATRIX m_object_to_world;
		
		/**
		 The (column-major packed, row-major matrix) object-to-world inverse 
		 transpose matrix (normal-to-world matrix) of this model buffer.
		 */
		XMMATRIX m_normal_to_world;

		/**
		 The (column-major packed, row-major matrix) texture transform matrix 
		 of this model buffer.
		 */
		XMMATRIX m_texture_transform;

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The linear base color of the material of this model buffer.
		 */
		RGBA m_base_color;

		/**
		 The roughness of the material of this model buffer.
		 */
		F32 m_roughness;

		/**
		 The metalness of the material of this model buffer.
		 */
		F32 m_metalness;

		/**
		 The padding of this game buffer.
		 */
		U32 m_padding[2];
	};

	static_assert(224 == sizeof(ModelBuffer), "CPU/GPU struct mismatch");
}