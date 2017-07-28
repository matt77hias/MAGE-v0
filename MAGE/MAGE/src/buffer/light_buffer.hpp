#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "material\spectrum.hpp"

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
	// SceneBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of scene buffers used by pixel shaders.
	 */
	__declspec(align(16)) struct SceneBuffer final : public AlignedData< SceneBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a scene buffer.
		 */
		SceneBuffer()
			: m_Ia{}, m_nb_omni_lights(0),
			m_Id{}, m_nb_spot_lights(0),
			m_d{}, m_fog_distance_falloff_start(0.0f), 
			m_fog_color{}, m_fog_distance_falloff_range(0.0f) {}
		
		/**
		 Constructs a scene buffer from the given scene buffer.

		 @param[in]		buffer
						A reference to the scene buffer to copy.
		 */
		SceneBuffer(const SceneBuffer &buffer) = default;
		
		/**
		 Constructs a scene buffer by moving the given scene buffer.

		 @param[in]		buffer
						A reference to the scene buffer to move.
		 */
		SceneBuffer(SceneBuffer &&buffer) = default;
		
		/**
		 Destructs this scene buffer.
		 */
		~SceneBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given scene buffer to this scene buffer.

		 @param[in]		buffer
						A reference to the scene buffer to copy.
		 @return		A reference to the copy of the given scene buffer
						(i.e. this scene buffer).
		 */
		SceneBuffer &operator=(const SceneBuffer &buffer) = default;

		/**
		 Moves the given scene buffer to this scene buffer.

		 @param[in]		buffer
						A reference to the scene buffer to move.
		 @return		A reference to the moved scene buffer
						(i.e. this scene buffer).
		 */
		SceneBuffer &operator=(SceneBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The ambient light intensity of this scene buffer.
		 */
		RGBSpectrum m_Ia;

		/**
		 The number of omni lights of this scene buffer.
		 */
		uint32_t m_nb_omni_lights;

		/**
		 The intensity of the directional light of this scene buffer.
		 */
		RGBSpectrum m_Id;

		/**
		 The number of spotlights of this scene buffer.
		 */
		uint32_t m_nb_spot_lights;

		/**
		 The (normalized) direction of the directional light
		 in camera-space coordinates of this scene buffer.
		 */
		Direction3 m_d;

		/**
		 The distance at which intensity falloff starts due to fog
		 of this scene buffer.
		 */
		float m_fog_distance_falloff_start;
	
		/**
		 The color of the fog of this scene buffer.
		 */
		RGBSpectrum m_fog_color;
		
		/**
		 The distance range where intensity falloff occurs due to fog
		 of this scene buffer.
		 */
		float m_fog_distance_falloff_range;
	};

	static_assert(sizeof(SceneBuffer) == 64, "CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// OmniLightBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of omni light buffers used by pixel shaders.
	 */
	__declspec(align(16)) struct OmniLightBuffer final : public AlignedData< OmniLightBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an omni light buffer.
		 */
		OmniLightBuffer()
			: m_p{}, 
			m_I(), m_padding0{},
			m_distance_falloff_end(0.0f), m_distance_falloff_range(0.0f),
			m_padding1{} {}
		
		/**
		 Constructs an omni light buffer from the given omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to copy.
		 */
		OmniLightBuffer(const OmniLightBuffer &buffer) = default;

		/**
		 Constructs an omni light buffer by moving the given omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to move.
		 */
		OmniLightBuffer(OmniLightBuffer &&buffer) = default;
		
		/**
		 Destructs this omni light buffer.
		 */
		~OmniLightBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given omni light buffer to this omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to copy.
		 @return		A reference to the copy of the given omni light buffer
						(i.e. this omni light buffer).
		 */
		OmniLightBuffer &operator=(const OmniLightBuffer &buffer) = default;

		/**
		 Moves the given omni light buffer to this omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to move.
		 @return		A reference to the moved omni light buffer
						(i.e. this omni light buffer).
		 */
		OmniLightBuffer &operator=(OmniLightBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the omni light in camera-space coordinates 
		 of this omni light buffer.
		 */
		XMFLOAT4 m_p;

		/**
		 The intensity of the omni light of this omni light buffer.
		 */
		RGBSpectrum m_I;

		/**
		 The padding of this omni light buffer.
		 */
		uint32_t m_padding0;

		/**
		 The distance at which intensity falloff ends of the omni light 
		 of this omni light buffer.
		 */
		float m_distance_falloff_end;

		/**
		 The distance range where intensity falloff occurs of the omni light
		 of this omni light buffer.
		 */
		float m_distance_falloff_range;

		/**
		 The padding of this omni light buffer.
		 */
		uint32_t m_padding1[2];
	};

	static_assert(sizeof(OmniLightBuffer) == 48, "CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// SpotLightBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of spotlight buffers used by pixel shaders.
	 */
	__declspec(align(16)) struct SpotLightBuffer final : public AlignedData< SpotLightBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a spotlight buffer.
		 */
		SpotLightBuffer()
			: m_p{}, 
			m_I{}, m_exponent_property(0.0f), 
			m_d{}, m_padding{},
			m_distance_falloff_end(0.0f), m_distance_falloff_range(0.0f),
			m_cos_umbra(0.0f), m_cos_range(0.0f) {}
		
		/**
		 Constructs a spotlight buffer from the given spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to copy.
		 */
		SpotLightBuffer(const SpotLightBuffer &buffer) = default;

		/**
		 Constructs a spotlight buffer by moving the given spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to move.
		 */
		SpotLightBuffer(SpotLightBuffer &&buffer) = default;
		
		/**
		 Destructs this spotlight buffer.
		 */
		~SpotLightBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given spotlight buffer to this spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to copy.
		 @return		A reference to the copy of the given spotlight buffer
						(i.e. this spotlight buffer).
		 */
		SpotLightBuffer &operator=(const SpotLightBuffer &buffer) = default;

		/**
		 Moves the given spotlight buffer to this spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to move.
		 @return		A reference to the moved spotlight buffer
						(i.e. this spotlight buffer).
		 */
		SpotLightBuffer &operator=(SpotLightBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the spotlight in camera-space coordinates
		 of this spotlight buffer.
		 */
		XMFLOAT4 m_p;

		/**
		 The intensity of the spotlight of this spotlight buffer.
		 */
		RGBSpectrum m_I;

		/**
		 The exponent property of the spotlight of this spotlight buffer.
		 */
		float m_exponent_property;

		/**
		 The (normalized) direction of the spotlight in camera-space coordinates
		 of this spotlight buffer.
		 */
		Direction3 m_d;

		/**
		 The padding of this spotlight buffer.
		 */
		uint32_t m_padding;
		
		/**
		 The distance at which intensity falloff ends of the spotlight
		 of this spotlight buffer.
		 */
		float m_distance_falloff_end;

		/**
		 The distance range where intensity falloff occurs of the spotlight
		 of this spotlight buffer.
		 */
		float m_distance_falloff_range;
		
		/**
		 The cosine of the umbra angle of the spotlight
		 of this spotlight buffer.
		 */
		float m_cos_umbra;

		/**
		 The cosine range where intensity falloff occurs of the spotlight
		 of this spotlight buffer.
		 */
		float m_cos_range;
	};

	static_assert(sizeof(SpotLightBuffer) == 64, "CPU/GPU struct mismatch");
}