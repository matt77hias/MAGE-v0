#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\color.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of scene fog with respect to the camera position (eye) to avoid 
	 popping artifacts while moving.
	 */
	class SceneFog final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a scene fog.
		 */
		SceneFog()
			: m_base_color(color::Silver.x, color::Silver.y, color::Silver.z), 
			m_density(0.0) {}

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
		 Returns the sRGB base color of this scene fog.

		 @return		A reference to the sRGB base color of this scene fog.
		 */
		SRGB &GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this scene fog.

		 @return		A reference to the sRGB base color of this scene fog.
		 */
		const SRGB &GetBaseColor() const noexcept {
			return m_base_color;
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
		 The sRGB base color of this scene fog.
		 */
		SRGB m_base_color;

		/**
		 The density of this scene fog.
		 */
		F32 m_density;
	};
}