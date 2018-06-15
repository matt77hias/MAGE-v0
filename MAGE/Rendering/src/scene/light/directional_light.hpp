#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "spectrum\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	#pragma warning( push )
	#pragma warning( disable : 4324 ) // Added padding.

	/**
	 A class of directional lights.
	 */
	class alignas(16) DirectionalLight final : public Component {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a directional light.
		 */
		DirectionalLight() noexcept;
		
		/**
		 Constructs a directional light from the given directional light.

		 @param[in]		light
						A reference to the directional light to copy.
		 */
		DirectionalLight(const DirectionalLight& light) noexcept;

		/**
		 Constructs a directional light by moving the given directional light.

		 @param[in]		light
						A reference to the directional light to move.
		 */
		DirectionalLight(DirectionalLight&& light) noexcept;

		/**
		 Destructs this directional light.
		 */
		virtual ~DirectionalLight();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given directional light to this directional light.

		 @param[in]		light
						A reference to the directional light to copy.
		 @return		A reference to the copy of the given directional light
						(i.e. this directional light).
		 */
		DirectionalLight& operator=(const DirectionalLight& light) noexcept;

		/**
		 Moves the given directional light to this directional light.

		 @param[in]		light
						A reference to the directional light to move.
		 @return		A reference to the moved directional light (i.e. this 
						directional light).
		 */
		DirectionalLight& operator=(DirectionalLight&& light) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Lighting
		//---------------------------------------------------------------------

		/**
		 Returns the (linear) base color of this directional light.

		 @return		A reference to the sRGB base color of this directional 
						light.
		 */
		[[nodiscard]]
		RGB& GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the (linear) base color of this directional light.

		 @return		A reference to the sRGB base color of this directional 
						light.
		 */
		[[nodiscard]]
		const RGB& GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the irradiance of this directional light.

		 @return		The irradiance in watts per square meter of this 
						directional light.
		 */
		[[nodiscard]]
		F32 GetIrradiance() const noexcept {
			return m_irradiance;
		}

		/**
		 Sets the irradiance of this directional light to the given irradiance.
		 
		 @param[in]		irradiance
						The irradiance in watts per square meter.
		 */
		void SetIrradiance(F32 irradiance) noexcept {
			m_irradiance = std::abs(irradiance);
		}

		/**
		 Returns the irradiance spectrum of this directional light.

		 @return		The irradiance spectrum of this directional light.
		 */
		[[nodiscard]]
		const RGB GetIrradianceSpectrum() const noexcept {
			const auto L = m_irradiance * XMLoad(m_base_color);
			return RGB(XMStore< F32x3 >(L));
		}

		//---------------------------------------------------------------------
		// Member Methods: Shadowing
		//---------------------------------------------------------------------

		/**
		 Checks whether shadows should be used for this directional light.

		 @return		@c true if shadows should be used for this
						directional light. @c false otherwise.
		 */
		[[nodiscard]]
		bool UseShadows() const noexcept {
			return m_shadows;
		}

		/**
		 Enables shadows for this directional light.
		 */
		void EnableShadows() noexcept {
			SetShadows(true);
		}

		/**
		 Dissables shadows for this directional light.
		 */
		void DissableShadows() noexcept {
			SetShadows(false);
		}

		/**
		 Toggles shadows for this directional light.
		 */
		void ToggleShadows() noexcept {
			SetShadows(!m_shadows);
		}

		/**
		 Sets shadows for this directional light to the given value.

		 @param[in]		shadows
						@c true if shadows should be used for this directional 
						light. @c false otherwise.
		 */
		void SetShadows(bool shadows) noexcept {
			m_shadows = shadows;
		}

		/**
		 Returns the clipping planes of this directional light expressed in 
		 light space.

		 @return		The clipping planes of this directional light expressed 
						in light space.
		 */
		[[nodiscard]]
		const F32x2 GetClippingPlanes() const noexcept {
			return m_clipping_planes;
		}
		
		/**
		 Sets the clipping planes of this directional light expressed in light 
		 space to the given clipping planes.

		 @param[in]		clipping_planes
						The clipping planes.
		 */
		void SetClippingPlanes(F32x2 clipping_planes) noexcept {
			m_clipping_planes = std::move(clipping_planes);
		}

		/**
		 Returns the size of the projection plane of this directional light 
		 expressed in directional light.

		 @return		The size of the projection plane of this directional 
						light expressed in light space.
		 */
		[[nodiscard]]
		const F32x2 GetSize() const noexcept {
			return m_size;
		}

		/**
		 Sets the size of the projection plane of this directional light 
		 expressed in light space to the given size.

		 @param[in]		size
						The size.
		 */
		void SetSize(F32x2 size) noexcept {
			m_size = std::move(size);
		}

		/**
		 Returns the light-to-projection matrix of the light camera of this 
		 directional light.

		 @return		The light-to-projection matrix of the light camera of 
						this directional light.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV 
			GetLightToProjectionMatrix() const noexcept {

			#ifdef DISABLE_INVERTED_Z_BUFFER
			const auto [near_plane, far_plane] = m_clipping_planes;
			#else  // DISABLE_INVERTED_Z_BUFFER
			const auto [far_plane, near_plane] = m_clipping_planes;
			#endif // DISABLE_INVERTED_Z_BUFFER

			return XMMatrixOrthographicLH(m_size[0], m_size[1],
										  near_plane, far_plane);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether shadows should be calculated or not not for 
		 this directional light.
		 */
		bool m_shadows;

		/**
		 The clipping planes of this directional light expressed in light 
		 space.
		 */
		F32x2 m_clipping_planes;

		/**
		 The size of the projection plane of this directional light expressed 
		 in light space.
		 */
		F32x2 m_size;

		/**
		 The (linear) base color of this directional light.
		 */
		RGB m_base_color;

		/**
		 The irradiance (which is equal to the exitant radiance/radiosity) in 
		 watts per square meter of this directional light.
		 */
		F32 m_irradiance;
	};

	#pragma warning( pop )
}