#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Defines
//-----------------------------------------------------------------------------
#pragma region

#define MAGE_DEFAULT_SCENE_FOG_START 0.0f
#define MAGE_DEFAULT_SCENE_FOG_END 100.0f

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of (linear) scene fog with respect to the camera position (eye).
	 */
	struct SceneFog final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a scene fog.

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit SceneFog(const RGBSpectrum &intensity 
			= RGBSpectrum(0.752941251f, 0.752941251f, 0.752941251f))
			: m_intensity(intensity), 
			m_distance_falloff_start(MAGE_DEFAULT_SCENE_FOG_START), 
			m_distance_falloff_end(MAGE_DEFAULT_SCENE_FOG_END) {}

		/**
		 Constructs a scene fog from the given scene fog.

		 @param[in]		scene_fog
						A reference to the scene fog to copy.
		 */
		SceneFog(const SceneFog &scene_fog) = default;

		/**
		 Constructs a scene fog by moving the given scene fog.

		 @param[in]		scene_fog
						A reference to the scene fog to move.
		 */
		SceneFog(SceneFog &&scene_fog) = default;

		/**
		 Destructs this scene fog.
		 */
		~SceneFog() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given scene fog to this scene fog.

		 @param[in]		scene_fog
						A reference to the scene fog to copy.
		 @return		A reference to the copy of the given scene fog (i.e. 
						this scene fog).
		 */
		SceneFog &operator=(const SceneFog &scene_fog) = default;

		/**
		 Moves the given scene fog to this scene fog.

		 @param[in]		scene_fog
						A reference to the scene fog to move.
		 @return		A reference to the moved scene fog (i.e. this scene 
						fog).
		 */
		SceneFog &operator=(SceneFog &&scene_fog) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the intensity of this scene fog.

		 @return		The intensity of this light.
		 */
		const RGBSpectrum GetIntensity() const noexcept {
			return m_intensity;
		}

		/**
		 Sets the intensity of this scene fog to the given intensity.

		 @param[in]		intensity
						A reference to the intensity.
		 */
		void SetIntensity(const RGBSpectrum &intensity) noexcept {
			m_intensity = intensity;
		}

		/**
		 Sets the intensity of this scene fog to the given intensity.

		 @param[in]		intensity
						A reference to the intensity.
		 */
		void SetIntensity(RGBSpectrum &&intensity) noexcept {
			m_intensity = std::move(intensity);
		}

		/**
		 Returns the distance at which intensity falloff starts of this scene 
		 fog.

		 @return		The distance at which intensity falloff starts of this 
						scene fog.
		 */
		f32 GetStartDistanceFalloff() const noexcept {
			return m_distance_falloff_start;
		}

		/**
		 Sets the distance at which intensity falloff starts of this scene fog
		 to the given value.

		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 */
		void SetStartDistanceFalloff(f32 distance_falloff_start) noexcept {
			m_distance_falloff_start = distance_falloff_start;
		}
		
		/**
		 Returns the distance at which intensity falloff ends of this scene fog

		 @return		The distance at which intensity falloff ends of this 
						scene fog.
		 */
		f32 GetEndDistanceFalloff() const noexcept {
			return m_distance_falloff_end;
		}

		/**
		 Sets the distance at which intensity falloff ends of this scene fog
		 to the given value.

		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetEndDistanceFalloff(f32 distance_falloff_end) noexcept {
			m_distance_falloff_end = distance_falloff_end;
		}
		
		/**
		 Sets the distance at which intensity falloff starts and ends of this 
		 scene fog to the given values.

		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 @param[in]		distance_falloff_end
						The distance at which intensity falloff ends.
		 */
		void SetDistanceFalloff(
			f32 distance_falloff_start, f32 distance_falloff_end) noexcept {
			
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
		}

		/**
		 Returns the distance range where intensity falloff occurs of this 
		 scene fog.

		 @return		The distance range where intensity falloff occurs of 
						this scene fog. @a GetEndDistanceFalloff() - 
						@a GetStartDistanceFalloff().
		 */
		f32 GetRangeDistanceFalloff() const noexcept {
			return m_distance_falloff_end - m_distance_falloff_start;
		}
		
		/**
		 Sets the distance at which intensity falloff starts and the distance 
		 range where intensity falloff occurs of this scene fog to the given 
		 values.

		 @param[in]		distance_falloff_start
						The distance at which intensity falloff starts.
		 @param[in]		distance_falloff_range
						The distance range where intensity falloff occurs.
		 */
		void SetRangeDistanceFalloff(
			f32 distance_falloff_start, f32 distance_falloff_range) noexcept {

			SetDistanceFalloff(distance_falloff_start, 
				distance_falloff_start + distance_falloff_range);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The intensity of this scene fog.
		 */
		RGBSpectrum m_intensity;

		/**
		 The start of the distance falloff of this scene fog.
		 */
		f32 m_distance_falloff_start;

		/**
		 The end of the distance falloff of this scene fog.
		 */
		f32 m_distance_falloff_end;
	};
}