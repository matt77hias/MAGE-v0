#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of scene fog with respect to the camera position (eye) to avoid 
	 popping artifacts while moving.
	 */
	class SceneFog final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a scene fog.

		 @param[in]		base_color
						A reference to the (sRGB) base color of this scene fog.
		 */
		explicit SceneFog(const RGBSpectrum &base_color
			= RGBSpectrum(0.752941251f, 0.752941251f, 0.752941251f))
			: m_base_color(base_color), m_density(0.0) {}

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
		// Member Methods: Fogging
		//---------------------------------------------------------------------

		/**
		 Returns the red (sRGB) channel of the (sRGB) base color of this scene 
		 fog.

		 @return		The red (sRGB) channel of the (sRGB) base color of this 
						scene fog.
		 */
		F32 GetBaseColorR() const noexcept {
			return m_base_color.x;
		}
		
		/**
		 Returns the green (sRGB) channel of the (sRGB) base color of this 
		 scene fog.

		 @return		The green (sRGB) channel of the (sRGB) base color of 
						this scene fog.
		 */
		F32 GetBaseColorG() const noexcept {
			return m_base_color.y;
		}
		
		/**
		 Returns the blue (sRGB) channel of the (sRGB) base color of this scene 
		 fog.

		 @return		The blue (sRGB) channel of the (sRGB) base color of 
						this scene fog.
		 */
		F32 GetBaseColorB() const noexcept {
			return m_base_color.z;
		}
		
		/**
		 Returns the RGB (sRGB) channels of the (sRGB) base color of this scene
		 fog.

		 @return		The RGB (sRGB) channels of the (sRGB) base color of 
						this scene fog.
		 */
		const RGBSpectrum GetBaseColorRGB() const noexcept {
			return m_base_color;
		}
		
		/**
		 Sets the red (sRGB) channel of the (sRGB) base color of this scene fog 
		 to the given  value.

		 @pre			@a red is an element of [0,1].
		 @param[in]		red
						The red (sRGB) channel of the (sRGB) base color.
		 */
		void SetBaseColorR(F32 red) noexcept {
			Assert(0.0f <= red && red <= 1.0f);
			m_base_color.x = red;
		}
		
		/**
		 Sets the green (sRGB) channel of the (sRGB) base color of this scene 
		 fog to the given value.

		 @pre			@a green is an element of [0,1].
		 @param[in]		green
						The green (sRGB) channel of the (sRGB) base color.
		 */
		void SetBaseColorG(F32 green) noexcept {
			Assert(0.0f <= green && green <= 1.0f);
			m_base_color.y = green;
		}
		
		/**
		 Sets the blue (sRGB) channel of the (sRGB) base color of this scene 
		 fog to the given value.

		 @pre			@a blue is an element of [0,1].
		 @param[in]		blue
						The blue (sRGB) channel of the (sRGB) base color.
		 */
		void SetBaseColorB(F32 blue) noexcept {
			Assert(0.0f <= blue && blue <= 1.0f);
			m_base_color.z = blue;
		}
		
		/**
		 Sets the red (sRGB), green (sRGB) and blue (sRGB) channel of the 
		 (sRGB) base color of this scene fog to the given values.

		 @pre			@a red is an element of [0,1].
		 @pre			@a green is an element of [0,1].
		 @pre			@a blue is an element of [0,1].
		 @param[in]		red
						The red (sRGB) channel of the (sRGB) base color.
		 @param[in]		green
						The green (sRGB) channel of the (sRGB) base color.
		 @param[in]		blue
						The blue (sRGB) channel of the (sRGB) base color.
		 */
		void SetBaseColorRGB(F32 red, F32 green, F32 blue) noexcept {
			SetBaseColorR(red);
			SetBaseColorG(green);
			SetBaseColorB(blue);
		}
		
		/**
		 Sets the red (sRGB), green (sRGB) and blue (sRGB) channel of the 
		 (sRGB) base color of this scene fog to the given value.

		 @pre			@a rgb is an element of [0,1]^3.
		 @param[in]		rgb
						A reference to red (sRGB), green (sRGB) and blue (sRGB) 
						channel of the (sRGB) base color.
		 */
		void SetBaseColorRGB(const RGBSpectrum &rgb) noexcept {
			Assert(0.0f <= rgb.x && rgb.x <= 1.0f);
			Assert(0.0f <= rgb.y && rgb.y <= 1.0f);
			Assert(0.0f <= rgb.z && rgb.z <= 1.0f);
			m_base_color = rgb;
		}

		/**
		 Sets the red (sRGB), green (sRGB) and blue (sRGB) channel of the 
		 (sRGB) base color of this scene fog to the given value.

		 @pre			@a rgb is an element of [0,1]^3.
		 @param[in]		rgb
						A reference to red (sRGB), green (sRGB) and blue (sRGB) 
						channel of the (sRGB) base color.
		 */
		void SetBaseColorRGB(RGBSpectrum &&rgb) noexcept {
			Assert(0.0f <= rgb.x && rgb.x <= 1.0f);
			Assert(0.0f <= rgb.y && rgb.y <= 1.0f);
			Assert(0.0f <= rgb.z && rgb.z <= 1.0f);
			m_base_color = std::move(rgb);
		}

		/**
		 Returns the density of this scene fog.
		
		 @return		The density of this scene fog.			
		 */
		F32 GetDensity() const noexcept {
			return m_density;
		}

		/**
		 Sets the density of this scene fog to the given value.

		 @pre			@a density is an element of [0,1].
		 @param[in]		density
						The density.
		 */
		void SetDensity(F32 density) noexcept {
			Assert(0.0f <= density && density <= 1.0f);
			m_density = density;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The (sRGB) base color of this scene fog.
		 */
		RGBSpectrum m_base_color;

		/**
		 The density of this scene fog.
		 */
		F32 m_density;
	};
}