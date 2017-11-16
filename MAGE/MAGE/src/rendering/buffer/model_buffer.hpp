#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\memory\allocation.hpp"
#include "material\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ModelNormalTransformBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of transform buffers used by shaders for transforming vertex 
	 positions/directions and normals.
	 */
	_declspec(align(16)) struct ModelNormalTransformBuffer final 
		: public AlignedData< ModelNormalTransformBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform buffer.
		 */
		ModelNormalTransformBuffer()
			: m_object_to_view{},
			m_normal_to_view{} {}

		/**
		 Constructs a transform buffer from the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to copy.
		 */
		ModelNormalTransformBuffer(
			const ModelNormalTransformBuffer &buffer) = default;
		
		/**
		 Constructs a transform buffer by moving the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 */
		ModelNormalTransformBuffer(
			ModelNormalTransformBuffer &&buffer) = default;

		/**
		 Destructs this transform buffer.
		 */
		~ModelNormalTransformBuffer() = default;
		
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
		ModelNormalTransformBuffer &operator=(
			const ModelNormalTransformBuffer &buffer) = default;

		/**
		 Moves the given transform buffer to this transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 @return		A reference to the moved transform buffer (i.e. this 
						transform buffer).
		 */
		ModelNormalTransformBuffer &operator=(
			ModelNormalTransformBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera dependent, object dependent) (column-major packed, 
		 row-major matrix) object-to-view matrix of this model buffer for use 
		 in HLSL.
		 */
		XMMATRIX m_object_to_view;
		
		/**
		 The (camera dependent, object dependent) (column-major packed, 
		 row-major matrix) object-to-view inverse tranpose matrix 
		 (normal-to-view matrix) of this model buffer for use in HLSL.
		 */
		XMMATRIX m_normal_to_view;
	};

	static_assert(sizeof(ModelNormalTransformBuffer) == 128, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// ModelTextureTransformBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of transform buffers used by shaders for transforming vertex 
	 positions/directions and texture coordinates.
	 */
	_declspec(align(16)) struct ModelTextureTransformBuffer final 
		: public AlignedData< ModelTextureTransformBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform buffer.
		 */
		ModelTextureTransformBuffer()
			: m_object_to_view{},
			m_texture_transform{} {}

		/**
		 Constructs a transform buffer from the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to copy.
		 */
		ModelTextureTransformBuffer(
			const ModelTextureTransformBuffer &buffer) = default;
		
		/**
		 Constructs a transform buffer by moving the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 */
		ModelTextureTransformBuffer(
			ModelTextureTransformBuffer &&buffer) = default;

		/**
		 Destructs this transform buffer.
		 */
		~ModelTextureTransformBuffer() = default;
		
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
		ModelTextureTransformBuffer &operator=(
			const ModelTextureTransformBuffer &buffer) = default;

		/**
		 Moves the given transform buffer to this transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 @return		A reference to the moved transform buffer (i.e. this 
						transform buffer).
		 */
		ModelTextureTransformBuffer &operator=(
			ModelTextureTransformBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera dependent, object dependent) (column-major packed, 
		 row-major matrix) object-to-view matrix of this model buffer for use 
		 in HLSL.
		 */
		XMMATRIX m_object_to_view;

		/**
		 The (object dependent) (column-major packed, row-major matrix) texture 
		 transform matrix of this model buffer for use in HLSL.
		 */
		XMMATRIX m_texture_transform;
	};

	static_assert(sizeof(ModelTextureTransformBuffer) == 128, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// ModelNormalTextureTransformBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of transform buffers used by shaders for transforming vertex 
	 positions/directions, normals and texture coordinates.
	 */
	_declspec(align(16)) struct ModelNormalTextureTransformBuffer final 
		: public AlignedData< ModelNormalTextureTransformBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform buffer.
		 */
		ModelNormalTextureTransformBuffer()
			: m_object_to_view{},
			m_normal_to_view{},
			m_texture_transform{} {}

		/**
		 Constructs a transform buffer from the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to copy.
		 */
		ModelNormalTextureTransformBuffer(
			const ModelNormalTextureTransformBuffer &buffer) = default;
		
		/**
		 Constructs a transform buffer by moving the given transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 */
		ModelNormalTextureTransformBuffer(
			ModelNormalTextureTransformBuffer &&buffer) = default;

		/**
		 Destructs this transform buffer.
		 */
		~ModelNormalTextureTransformBuffer() = default;
		
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
		ModelNormalTextureTransformBuffer &operator=(
			const ModelNormalTextureTransformBuffer &buffer) = default;

		/**
		 Moves the given transform buffer to this transform buffer.

		 @param[in]		buffer
						A reference to the transform buffer to move.
		 @return		A reference to the moved transform buffer (i.e. this 
						transform buffer).
		 */
		ModelNormalTextureTransformBuffer &operator=(
			ModelNormalTextureTransformBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera dependent, object dependent) (column-major packed, 
		 row-major matrix) object-to-view matrix of this model buffer for use 
		 in HLSL.
		 */
		XMMATRIX m_object_to_view;
		
		/**
		 The (camera dependent, object dependent) (column-major packed, 
		 row-major matrix) object-to-view inverse tranpose matrix 
		 (normal-to-view matrix) of this model buffer for use in HLSL.
		 */
		XMMATRIX m_normal_to_view;

		/**
		 The (object dependent) (column-major packed, row-major matrix) 
		 texture transform matrix of this model buffer for use in HLSL.
		 */
		XMMATRIX m_texture_transform;
	};

	static_assert(sizeof(ModelNormalTextureTransformBuffer) == 192, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// ModelBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of model buffers.
	 */
	_declspec(align(16)) struct ModelBuffer final 
		: public AlignedData< ModelBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model buffer.
		 */
		ModelBuffer()
			: m_transform(),
			m_base_color{}, 
			m_roughness(0.0f),
			m_metalness(0.0f),
			m_padding{} {}

		/**
		 Constructs a model buffer from the given model buffer.

		 @param[in]		buffer
						A reference to the model buffer to copy.
		 */
		ModelBuffer(const ModelBuffer &buffer) = default;
		
		/**
		 Constructs a model buffer by moving the given model 
		 buffer.

		 @param[in]		buffer
						A reference to the model buffer to move.
		 */
		ModelBuffer(ModelBuffer &&buffer) = default;

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
		ModelBuffer &operator=(const ModelBuffer &buffer) = default;

		/**
		 Moves the given model buffer to this model buffer.

		 @param[in]		buffer
						A reference to the model buffer to move.
		 @return		A reference to the moved model buffer (i.e. this model 
						buffer).
		 */
		ModelBuffer &operator=(ModelBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		/**
		 The transformation matrices of this model buffer.
		 */
		ModelNormalTextureTransformBuffer m_transform;

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

	static_assert(sizeof(ModelBuffer) == 224, 
		"CPU/GPU struct mismatch");
}