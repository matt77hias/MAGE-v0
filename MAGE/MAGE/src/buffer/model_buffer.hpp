#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
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
	 A struct of transform buffers used by pixel shaders for transforming 
	 vertex positions/directions and normals.
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
	 A struct of transform buffers used by pixel shaders for transforming 
	 vertex positions/directions and texture coordinates.
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
	 A struct of transform buffers used by pixel shaders for transforming 
	 vertex positions/directions, normals and texture coordinates.
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
	// ForwardModelBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of forward model buffers used by pixel shaders.
	 */
	_declspec(align(16)) struct ForwardModelBuffer final 
		: public AlignedData< ForwardModelBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a forward model buffer.
		 */
		ForwardModelBuffer()
			: m_transform(),
			m_Kd{}, m_dissolve(0.0f),
			m_Ks{}, m_material_coefficients{} {}

		/**
		 Constructs a forward model buffer from the given forward model buffer.

		 @param[in]		buffer
						A reference to the forward model buffer to copy.
		 */
		ForwardModelBuffer(const ForwardModelBuffer &buffer) = default;
		
		/**
		 Constructs a forward model buffer by moving the given forward model 
		 buffer.

		 @param[in]		buffer
						A reference to the forward model buffer to move.
		 */
		ForwardModelBuffer(ForwardModelBuffer &&buffer) = default;

		/**
		 Destructs this forward model buffer.
		 */
		~ForwardModelBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given forward model buffer to this forward model buffer.

		 @param[in]		buffer
						A reference to the forward model buffer to copy.
		 @return		A reference to the copy of the given forward model 
						buffer (i.e. this forward model buffer).
		 */
		ForwardModelBuffer &operator=(
			const ForwardModelBuffer &buffer) = default;

		/**
		 Moves the given forward model buffer to this forward model buffer.

		 @param[in]		buffer
						A reference to the forward model buffer to move.
		 @return		A reference to the moved forward model buffer (i.e. 
						this forward model buffer).
		 */
		ForwardModelBuffer &operator=(
			ForwardModelBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		/**
		 The transformation matrices of this forward model buffer.
		 */
		ModelNormalTextureTransformBuffer m_transform;

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The diffuse reflectivity of this forward model buffer.
		 */
		RGBSpectrum m_Kd;

		/**
		 The dissolve factor (i.e. opacity) of this forward model buffer.
		 */
		f32 m_dissolve;

		/**
		 The specular reflectivity of this forward model buffer.
		 */
		RGBSpectrum m_Ks;

		/**
		 The BRDF dependent material coefficients of this forward model buffer.
		 */
		f32 m_material_coefficients[2];
	};

	static_assert(sizeof(ForwardModelBuffer) == 240, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// DeferredModelBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of deferred model buffers used by pixel shaders.
	 */
	_declspec(align(16)) struct DeferredModelBuffer final 
		: public AlignedData< DeferredModelBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a deferred model buffer.
		 */
		DeferredModelBuffer()
			: m_transform(),
			m_Kd{}, m_mat2_norm(0.0f),
			m_Ks{}, m_mat1_norm(0.0f) {}

		/**
		 Constructs a deferred model buffer from the given deferred model 
		 buffer.

		 @param[in]		buffer
						A reference to the deferred model buffer to copy.
		 */
		DeferredModelBuffer(const DeferredModelBuffer &buffer) = default;
		
		/**
		 Constructs a deferred model buffer by moving the given deferred 
		 model buffer.

		 @param[in]		buffer
						A reference to the deferred model buffer to move.
		 */
		DeferredModelBuffer(DeferredModelBuffer &&buffer) = default;

		/**
		 Destructs this deferred model buffer.
		 */
		~DeferredModelBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given deferred model buffer to this deferred model buffer.

		 @param[in]		buffer
						A reference to the deferred model buffer to copy.
		 @return		A reference to the copy of the given deferred model 
						buffer (i.e. this deferred model buffer).
		 */
		DeferredModelBuffer &operator=(
			const DeferredModelBuffer &buffer) = default;

		/**
		 Moves the given deferred model buffer to this deferred model buffer.

		 @param[in]		buffer
						A reference to the deferred model buffer to move.
		 @return		A reference to the moved deferred model buffer (i.e. 
						this deferred model buffer).
		 */
		DeferredModelBuffer &operator=(
			DeferredModelBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		/**
		 The transformation matrices of this deferred model buffer.
		 */
		ModelNormalTextureTransformBuffer m_transform;

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The diffuse reflectivity of this deferred model buffer.
		 */
		RGBSpectrum m_Kd;

		/**
		The 2nd BRDF dependent normalized material coefficient
		of this deferred model buffer.
		 */
		f32 m_mat2_norm;

		/**
		 The specular reflectivity of this deferred model buffer.
		 */
		RGBSpectrum m_Ks;

		/**
		 The 1st BRDF dependent normalized material coefficient of this 
		 deferred model buffer.
		 */
		f32 m_mat1_norm;
	};

	static_assert(sizeof(DeferredModelBuffer) == 224, 
		"CPU/GPU struct mismatch");
}