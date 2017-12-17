#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "material\spectrum.hpp"
#include "math\geometry\bounding_volume.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of lights.
	 */
	class Light : public Component {

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
		Light &operator=(const Light &light) noexcept;

		/**
		 Moves the given light to this light.

		 @param[in]		light
						A reference to the light to move.
		 @return		A reference to the moved light (i.e. this light).
		 */
		Light &operator=(Light &&light) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this light.

		 @return		A reference to the sRGB base color of this light.
		 */
		SRGB &GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this light.

		 @return		A reference to the sRGB base color of this light.
		 */
		const SRGB &GetBaseColor() const noexcept {
			return m_base_color;
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
		Light() noexcept;

		/**
		 Constructs a light from the given light.

		 @param[in]		light
						A reference to the light to copy.
		 */
		Light(const Light &light) noexcept;

		/**
		 Constructs a light by moving the given light.

		 @param[in]		light
						A reference to the light to move.
		 */
		Light(Light &&light) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Range
		//---------------------------------------------------------------------

		/**
		 Updates the bounding volumes of this omni light.

		 @param[in]		aabb
						The AABB.
		 @param[in]		bs
						The BS.
		 */
		void SetBoundingVolumes(AABB aabb, BS bs) noexcept {
			m_aabb = std::move(aabb);
			m_bs   = std::move(bs);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables: Lighting
		//---------------------------------------------------------------------

		/**
		 The sRGB base color of this light.
		 */
		SRGB m_base_color;

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