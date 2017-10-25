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
	 A class of ambient lights.
	 */
	class AmbientLight final : public Light {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an ambient light.
		 */
		AmbientLight();

		/**
		 Constructs an ambient light from the given ambient light.

		 @param[in]		light
						A reference to the ambient light to copy.
		 */
		AmbientLight(const AmbientLight &light);

		/**
		 Constructs an ambient light by moving the given ambient light.

		 @param[in]		light
						A reference to the ambient light to move.
		 */
		AmbientLight(AmbientLight &&light);

		/**
		 Destructs this ambient light.
		 */
		virtual ~AmbientLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given ambient light to this ambient light.

		 @param[in]		light
						A reference to the ambient light to copy.
		 @return		A reference to the copy of the given ambient light 
						(i.e. this ambient light).
		 */
		AmbientLight &operator=(const AmbientLight &light);

		/**
		 Moves the given ambient light to this ambient light.

		 @param[in]		light
						A reference to the ambient light to move.
		 @return		A reference to the moved ambient light (i.e. this 
						ambient light).
		 */
		AmbientLight &operator=(AmbientLight &&light);

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this ambient light.

		 @return		A pointer to the clone of this ambient light.
		 */
		UniquePtr< AmbientLight > Clone() const {
			return static_pointer_cast< AmbientLight >(CloneImplementation());
		}

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the radiance of this ambient light.

		 @return		The radiance in watts per square meter per steradians 
						of this ambient light.
		 */
		F32 GetRadiance() const noexcept {
			return m_radiance;
		}

		/**
		 Sets the radiance of this ambient light to the given radiance.
		 
		 @pre			@a radiance must be non-negative.
		 @param[in]		radiance
						The radiance in watts per square meter per steradians.
		 */
		void SetRadiance(F32 radiance) noexcept {
			Assert(0.0f <= radiance);
			m_radiance = radiance;
		}

		/**
		 Returns the radiance spectrum of this ambient light.

		 @return		The radiance spectrum of this ambient light.
		 */
		const RGBSpectrum GetRadianceSpectrum() const noexcept {
			const RGBSpectrum color = GetBaseColorRGB();
			const XMVECTOR L_v      = m_radiance 
				                    * GammaToLinear(XMLoadFloat3(&color));
			RGBSpectrum L;
			XMStoreFloat3(&L, L_v);
			return L;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this ambient light.

		 @return		A pointer to the clone of this ambient light.
		 */
		virtual UniquePtr< Light > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The radiance in watts per square meter per steradians of this ambient 
		 light.
		 */
		F32 m_radiance;
	};
}