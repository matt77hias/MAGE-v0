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
	 A struct of scene buffers used by shaders.
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
			: m_view_to_projection{},
			m_Ia(), m_flags(0), m_nb_directional_lights(0), 
			m_nb_omni_lights(0), m_nb_spot_lights(0), 
			m_fog_distance_falloff_start(FLT_MAX), m_fog_color(), 
			m_fog_distance_falloff_range(FLT_MAX) {}
		
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
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (camera dependent, object independent) (column-major packed, row-major matrix) 
		 view-to-projection matrix of this scene buffer for use in HLSL.
		 */
		XMMATRIX m_view_to_projection;

		//---------------------------------------------------------------------
		// Member Variables: Lights
		//---------------------------------------------------------------------

		/**
		 The ambient light intensity of this scene buffer.
		 */
		RGBSpectrum m_Ia;

		/**
		 The flags of this scene buffer.
		 */
		uint32_t m_flags;

		/**
		 The number of directional lights of this scene buffer.
		 */
		uint32_t m_nb_directional_lights;

		/**
		 The number of omni lights of this scene buffer.
		 */
		uint32_t m_nb_omni_lights;

		/**
		 The number of spotlights of this scene buffer.
		 */
		uint32_t m_nb_spot_lights;

		//---------------------------------------------------------------------
		// Member Variables: Fog
		//---------------------------------------------------------------------

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

	static_assert(sizeof(SceneBuffer) == 112, "CPU/GPU struct mismatch");
}