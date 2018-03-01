#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\fog.hpp"
#include "camera\sky.hpp"
#include "material\brdf.hpp"
#include "rendering\configuration.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of camera settingss.
	 */
	class CameraSettings final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera settings.
		 */
		CameraSettings() noexcept
			: m_render_mode(RenderMode::Forward), 
			m_brdf(BRDFType::Unknown),
			m_render_layer_mask(static_cast< U32 >(RenderLayer::None)), 
			m_fog(), 
			m_sky() {}
		
		/**
		 Constructs a camera settings from the given camera settings.

		 @param[in]		settings
						A reference to the camera settings to copy.
		 */
		CameraSettings(const CameraSettings &settings) noexcept = default;

		/**
		 Constructs a camera settings by moving the given camera settings.

		 @param[in]		settings
						A reference to the camera settings to move.
		 */
		CameraSettings(CameraSettings &&settings) noexcept = default;

		/**
		 Destructs this camera settings.
		 */
		~CameraSettings() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given camera settings to this camera settings.

		 @param[in]		settings
						A reference to the camera settings to copy.
		 @return		A reference to the copy of the given camera settings 
						(i.e. this camera settings).
		 */
		CameraSettings &operator=(
			const CameraSettings &settings) noexcept = default;

		/**
		 Moves the given camera settings to this camera settings.

		 @param[in]		scene_settings
						A reference to the camera settings to move.
		 @return		A reference to the moved camera settings (i.e. this 
						camera settings).
		 */
		CameraSettings &operator=(
			CameraSettings &&settings) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void Reset() noexcept {
			ResetRenderMode();
			ResetBRDF();
			ResetRenderLayers();
		}

		[[nodiscard]]RenderMode GetRenderMode() const noexcept {
			return m_render_mode;
		}

		void SetRenderMode(RenderMode render_mode) noexcept {
			m_render_mode = render_mode;
		}

		void ResetRenderMode() noexcept {
			SetRenderMode(RenderMode::Forward);
		}

		[[nodiscard]]BRDFType GetBRDF() const noexcept {
			return m_brdf;
		}

		void SetBRDF(BRDFType brdf) noexcept {
			m_brdf = brdf;
		}

		void ResetBRDF() noexcept {
			SetBRDF(BRDFType::Unknown);
		}

		[[nodiscard]]bool ContainsRenderLayers() const noexcept {
			return static_cast< U32 >(RenderLayer::None) != m_render_layer_mask;
		}

		[[nodiscard]]bool ContainsRenderLayer(RenderLayer render_layer) const noexcept {
			return static_cast< bool >(static_cast< U32 >(render_layer)
				                       & m_render_layer_mask);
		}

		void AddRenderLayer(RenderLayer render_layer) noexcept {
			m_render_layer_mask |= static_cast< U32 >(render_layer);
		}

		void RemoveRenderLayer(RenderLayer render_layer) noexcept {
			m_render_layer_mask &= ~(static_cast< U32 >(render_layer));
		}

		void ToggleRenderLayer(RenderLayer render_layer) noexcept {
			m_render_layer_mask ^= static_cast< U32 >(render_layer);
		}

		void ResetRenderLayers() noexcept {
			m_render_layer_mask = static_cast< U32 >(RenderLayer::None);
		}

		[[nodiscard]]Fog &GetFog() noexcept {
			return m_fog;
		}

		[[nodiscard]]const Fog &GetFog() const noexcept {
			return m_fog;
		}

		[[nodiscard]]Sky &GetSky() noexcept {
			return m_sky;
		}

		[[nodiscard]]const Sky &GetSky() const noexcept {
			return m_sky;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The render mode of this camera settings.
		 */
		RenderMode m_render_mode;

		/**
		 The BRDF type used for normal rendering of this camera settings.
		 */
		BRDFType m_brdf;

		/**
		 The render layer mask of this camera settings.
		 */
		U32 m_render_layer_mask;

		/**
		 The fog of this camera settings. 
		 */
		Fog m_fog;

		/**
		 The sky of this camera settings. 
		 */
		Sky m_sky;
	};
}