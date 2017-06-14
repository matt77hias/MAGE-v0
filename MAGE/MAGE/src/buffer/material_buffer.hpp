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
	 A struct of material buffers used by pixel shaders.
	 */
	_declspec(align(16)) struct MaterialBuffer final : public AlignedData< MaterialBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a material buffer.
		 */
		MaterialBuffer()
			: m_Kd{}, m_dissolve(0.0f),
			m_Ks{}, m_Ns(0.0f),
			m_extra_parameters{} {}

		/**
		 Constructs a material buffer from the given material buffer.

		 @param[in]		buffer
						A reference to the material buffer to copy.
		 */
		MaterialBuffer(const MaterialBuffer &buffer) = default;
		
		/**
		 Constructs a material buffer by moving the given material buffer.

		 @param[in]		buffer
						A reference to the material buffer to move.
		 */
		MaterialBuffer(MaterialBuffer &&buffer) = default;

		/**
		 Destructs this material buffer.
		 */
		~MaterialBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------
		
		/**
		 Copies the given material buffer to this material buffer.

		 @param[in]		buffer
						A reference to the material buffer to copy.
		 @return		A reference to the copy of the given material buffer
						(i.e. this material buffer).
		 */
		MaterialBuffer &operator=(const MaterialBuffer &buffer) = default;

		/**
		 Moves the given material buffer to this material buffer.

		 @param[in]		buffer
						A reference to the material buffer to move.
		 @return		A reference to the moved material buffer
						(i.e. this material buffer).
		 */
		MaterialBuffer &operator=(MaterialBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member variables
		//---------------------------------------------------------------------

		/**
		 The diffuse reflectivity of this material buffer.
		 */
		RGBSpectrum m_Kd;
		
		/**
		 The dissolve factor (i.e. opacity) of this material buffer.
		 */
		float m_dissolve;

		/**
		 The specular reflectivity of this material buffer.
		 */
		RGBSpectrum m_Ks;

		/**
		 The specular exponent (surface roughness) of this material buffer.
		 */
		float m_Ns;

		/**
		 The extra material parameter of this material buffer.
		 */
		XMFLOAT4 m_extra_parameters;
	};

	static_assert(sizeof(MaterialBuffer) == 48, "CPU/GPU struct mismatch");
}