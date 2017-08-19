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

	/**
	 A struct of model buffers used by pixel shaders.
	 */
	_declspec(align(16)) struct ModelBuffer final : public AlignedData< ModelBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a model buffer.
		 */
		ModelBuffer()
			: 
			m_Kd{}, m_dissolve(0.0f),
			m_Ks{}, m_Ns(0.0f),
			m_extra_parameters{} {}

		/**
		 Constructs a model buffer from the given model buffer.

		 @param[in]		buffer
						A reference to the model buffer to copy.
		 */
		ModelBuffer(const ModelBuffer &buffer) = default;
		
		/**
		 Constructs a model buffer by moving the given model buffer.

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
		 @return		A reference to the copy of the given model buffer
						(i.e. this model buffer).
		 */
		ModelBuffer &operator=(const ModelBuffer &buffer) = default;

		/**
		 Moves the given model buffer to this model buffer.

		 @param[in]		buffer
						A reference to the model buffer to move.
		 @return		A reference to the moved model buffer
						(i.e. this model buffer).
		 */
		ModelBuffer &operator=(ModelBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera independent, object dependent) (column-major packed, row-major matrix) 
		 object-to-world matrix of this model buffer for use in HLSL.
		 */
		XMMATRIX m_object_to_world;
		
		/**
		 The (camera dependent, object dependent) (column-major packed, row-major matrix) 
		 object-to-view inverse tranpose matrix (for transforming object space normals) 
		 of this model buffer for use in HLSL.
		 */
		XMMATRIX m_object_to_view_inverse_transpose;

		//---------------------------------------------------------------------
		// Member variables: Materials
		//---------------------------------------------------------------------

		/**
		 The diffuse reflectivity of this model buffer.
		 */
		RGBSpectrum m_Kd;
		
		/**
		 The dissolve factor (i.e. opacity) of this model buffer.
		 */
		float m_dissolve;

		/**
		 The specular reflectivity of this model buffer.
		 */
		RGBSpectrum m_Ks;

		/**
		 The specular exponent (surface roughness) of this model buffer.
		 */
		float m_Ns;

		/**
		 The extra model parameter of this model buffer.
		 */
		XMFLOAT4 m_extra_parameters;
	};

	static_assert(sizeof(ModelBuffer) == 176, "CPU/GPU struct mismatch");
}