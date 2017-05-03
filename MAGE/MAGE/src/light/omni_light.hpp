#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of omni lights.
	 */
	class OmniLight : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an omni light.

		 @param[in]		intensity
						The RGB intensity.
		 */
		explicit OmniLight(const RGBSpectrum &intensity = RGBSpectrum(1.0f, 1.0f, 1.0f));
		
		/**
		 Constructs an omni light from the given omni light.

		 @param[in]		light
						A reference to the omni light to copy.
		 */
		OmniLight(const OmniLight &light);

		/**
		 Constructs an omni light by moving the given omni light.

		 @param[in]		light
						A reference to the omni light to move.
		 */
		OmniLight(OmniLight &&light);

		/**
		 Destructs this omni light.
		 */
		virtual ~OmniLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given omni light to this omni light.

		 @param[in]		light
						A reference to the omni light to copy.
		 @return		A reference to the copy of the given omni light
						(i.e. this omni light).
		 */
		OmniLight &operator=(const OmniLight &light);

		/**
		 Moves the given omni light to this omni light.

		 @param[in]		light
						A reference to the omni light to move.
		 @return		A reference to the moved omni light
						(i.e. this omni light).
		 */
		OmniLight &operator=(OmniLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this omni light.

		 @return		A pointer to the clone of this omni light.
		 */
		SharedPtr< OmniLight > Clone() const {
			return std::static_pointer_cast< OmniLight >(CloneImplementation());
		}
		
		/**
		 Returns the start of the distance falloff of this omni light.

		 @return		The start of the distance falloff of this omni light.
		 */
		float GetStartDistanceFalloff() const {
			return m_distance_falloff_start;
		}
		
		/**
		 Sets the start of the distance falloff of this omni light
		 to the given value.

		 @param[in]		distance_falloff_start
						The start of the distance falloff.
		 @return		A reference to this omni light.
		 */
		OmniLight &SetStartDistanceFalloff(float distance_falloff_start) {
			m_distance_falloff_start = distance_falloff_start;
			return (*this);
		}
		
		/**
		 Returns the end of the distance falloff of this omni light.

		 @return		The end of the distance falloff of this omni light.
		 */
		float GetEndDistanceFalloff() const {
			return m_distance_falloff_end;
		}
		
		/**
		 Sets the end of the distance falloff of this omni light
		 to the given value.

		 @param[in]		distance_falloff_end
						The end of the distance falloff.
		 @return		A reference to this omni light.
		 */
		OmniLight &SetEndDistanceFalloff(float distance_falloff_end) {
			m_distance_falloff_end = distance_falloff_end;
			return (*this);
		}
		
		/**
		 Sets the start and end of the distance falloff of this omni light
		 to the given values.

		 @param[in]		distance_falloff_start
						The start of the distance falloff.
		 @param[in]		distance_falloff_end
						The end of the distance falloff.
		 @return		A reference to this omni light.
		 */
		OmniLight &SetDistanceFalloff(float distance_falloff_start, float distance_falloff_end) {
			SetStartDistanceFalloff(distance_falloff_start);
			SetEndDistanceFalloff(distance_falloff_end);
			return (*this);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this omni light.

		 @return		A pointer to the clone of this omni light.
		 */
		virtual SharedPtr< Light > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The start of the distance falloff of this omni light.
		 */
		float m_distance_falloff_start;

		/**
		 The end of the distance falloff of this omni light.
		 */
		float m_distance_falloff_end;
	};
}