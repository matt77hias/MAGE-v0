#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\spectrum.hpp"
#include "math\bounding_volume.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of lights.
	 */
	class Light {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this light.
		 */
		virtual ~Light();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given light to this light.

		 @param[in]		light
						A reference to the light to copy.
		 @return		A reference to the copy of the given light (i.e. this 
						light).
		 */
		Light &operator=(const Light &light);

		/**
		 Moves the given light to this light.

		 @param[in]		light
						A reference to the light to move.
		 @return		A reference to the moved light (i.e. this light).
		 */
		Light &operator=(Light &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this light.

		 @return		A pointer to the clone of this light.
		 */
		UniquePtr< Light > Clone() const {
			return static_pointer_cast< Light >(CloneImplementation());
		}

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the red (sRGB) channel of the (sRGB) base color of this light.

		 @return		The red (sRGB) channel of the (sRGB) base color of this 
						light.
		 */
		F32 GetBaseColorR() const noexcept {
			return m_base_color.x;
		}
		
		/**
		 Returns the green (sRGB) channel of the (sRGB) base color of this 
		 light.

		 @return		The green (sRGB) channel of the (sRGB) base color of 
						this light.
		 */
		F32 GetBaseColorG() const noexcept {
			return m_base_color.y;
		}
		
		/**
		 Returns the blue (sRGB) channel of the (sRGB) base color of this 
		 light.

		 @return		The blue (sRGB) channel of the (sRGB) base color of 
						this light.
		 */
		F32 GetBaseColorB() const noexcept {
			return m_base_color.z;
		}
		
		/**
		 Returns the RGB (sRGB) channels of the (sRGB) base color of this 
		 light.

		 @return		The RGB (sRGB) channels of the (sRGB) base color of 
						this light.
		 */
		const RGBSpectrum GetBaseColorRGB() const noexcept {
			return m_base_color;
		}
		
		/**
		 Sets the red (sRGB) channel of the (sRGB) base color of this light 
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
		 Sets the green (sRGB) channel of the (sRGB) base color of this light 
		 to the given value.

		 @pre			@a green is an element of [0,1].
		 @param[in]		green
						The green (sRGB) channel of the (sRGB) base color.
		 */
		void SetBaseColorG(F32 green) noexcept {
			Assert(0.0f <= green && green <= 1.0f);
			m_base_color.y = green;
		}
		
		/**
		 Sets the blue (sRGB) channel of the (sRGB) base color of this light 
		 to the given value.

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
		 (sRGB) base color of this light to the given values.

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
		 (sRGB) base color of this light to the given value.

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
		 (sRGB) base color of this light to the given value.

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

		//---------------------------------------------------------------------
		// Member Methods: Range
		//---------------------------------------------------------------------

		/**
		Returns the AABB of this light.

		@return		A reference to the AABB of this light.
		*/
		const AABB &GetAABB() const noexcept {
			return m_aabb;
		}

		/**
		Returns the BS of this light.

		@return		A reference to the BS of this light.
		*/
		const BS &GetBS() const noexcept {
			return m_bs;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a light.
		 */
		Light();

		/**
		 Constructs a light from the given light.

		 @param[in]		light
						A reference to the light to copy.
		 */
		Light(const Light &light);

		/**
		 Constructs a light by moving the given light.

		 @param[in]		light
						A reference to the light to move.
		 */
		Light(Light &&light);

		//---------------------------------------------------------------------
		// Member Methods: Range
		//---------------------------------------------------------------------

		/**
		 Updates the bounding volumes of this omni light.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		bs
						A reference to the BS.
		 */
		void SetBoundingVolumes(const AABB &aabb, const BS &bs) noexcept {
			m_aabb = aabb;
			m_bs   = bs;
		}

		/**
		 Updates the bounding volumes of this omni light.

		 @param[in]		aabb
						A reference to the AABB.
		 @param[in]		bs
						A reference to the BS.
		 */
		void SetBoundingVolumes(AABB &&aabb, BS &&bs) noexcept {
			m_aabb = std::move(aabb);
			m_bs   = std::move(bs);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this light.

		 @return		A pointer to the clone of this light.
		 */
		virtual UniquePtr< Light > CloneImplementation() const = 0;

		//---------------------------------------------------------------------
		// Member Variables: Lighting
		//---------------------------------------------------------------------

		/**
		 The (sRGB) base color of this light.
		 */
		RGBSpectrum m_base_color;

		//---------------------------------------------------------------------
		// Member Variables: Range
		//---------------------------------------------------------------------

		/**
		 The AABB of this light.
		 */
		AABB m_aabb;

		/**
		 The BS of this light.
		 */
		BS m_bs;
	};
}