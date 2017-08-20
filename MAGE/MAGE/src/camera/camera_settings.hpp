#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "material\brdf.hpp"
#include "pass\configuration.hpp"

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

	/**
	 A struct of camera settingss.
	 */
	struct CameraSettings final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera settings.
		 */
		CameraSettings()
			: m_render_mode(RenderMode::Default), 
			m_brdf(BRDFType::Unknown),
			m_render_layer_mask(static_cast< uint32_t >(RenderLayer::None)) {}
		
		/**
		 Constructs a camera settings from the given camera settings.

		 @param[in]		scene_settings
						A reference to the camera settings to copy.
		 */
		CameraSettings(const CameraSettings &scene_settings) = default;

		/**
		 Constructs a camera settings by moving the given camera settings.

		 @param[in]		scene_settings
						A reference to the camera settings to move.
		 */
		CameraSettings(CameraSettings &&scene_settings) = default;

		/**
		 Destructs this camera settings.
		 */
		~CameraSettings() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given camera settings to this camera settings.

		 @param[in]		scene_settings
						A reference to the camera settings to copy.
		 @return		A reference to the copy of the given camera settings
						(i.e. this camera settings).
		 */
		CameraSettings &operator=(const CameraSettings &scene_settings) = default;

		/**
		 Moves the given camera settings to this camera settings.

		 @param[in]		scene_settings
						A reference to the camera settings to move.
		 @return		A reference to the moved camera settings
						(i.e. this camera settings).
		 */
		CameraSettings &operator=(CameraSettings &&scene_settings) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		void Reset() noexcept {
			ResetRenderMode();
			ResetBRDF();
			ResetRenderLayers();
		}

		RenderMode GetRenderMode() const noexcept {
			return m_render_mode;
		}

		void SetRenderMode(RenderMode render_mode) noexcept {
			m_render_mode = render_mode;
		}

		void ResetRenderMode() noexcept {
			SetRenderMode(RenderMode::Default);
		}

		BRDFType GetBRDF() const noexcept {
			return m_brdf;
		}

		void SetBRDF(BRDFType brdf) noexcept {
			m_brdf = brdf;
		}

		void ResetBRDF() noexcept {
			SetBRDF(BRDFType::Unknown);
		}

		bool HasRenderLayers() const noexcept {
			return m_render_layer_mask != static_cast< uint32_t >(RenderLayer::None);
		}

		bool HasRenderLayer(RenderLayer render_layer) const noexcept {
			return static_cast< bool >(
				m_render_layer_mask & static_cast< uint32_t >(render_layer));
		}

		void AddRenderLayer(RenderLayer render_layer) noexcept {
			m_render_layer_mask |= static_cast< uint32_t >(render_layer);
		}

		void RemoveRenderLayer(RenderLayer render_layer) noexcept {
			m_render_layer_mask &= ~(static_cast< uint32_t >(render_layer));
		}

		void ToggleRenderLayer(RenderLayer render_layer) noexcept {
			m_render_layer_mask ^= static_cast< uint32_t >(render_layer);
		}

		void ResetRenderLayers() noexcept {
			m_render_layer_mask = static_cast< uint32_t >(RenderLayer::None);
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
		uint32_t m_render_layer_mask;
	};
}