#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of pass buffers used as input by render passes.
	 */
	struct PassBuffer final {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The number of material coefficients contained in pass buffers.
		 */
		static const u8 s_nb_material_coefficients = 2;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a pass buffer.
		 */
		PassBuffer();

		/**
		 Constructs a pass buffer from the given pass buffer.

		 @param[in]		pass_buffer
						A reference to the pass buffer to copy.
		 */
		PassBuffer(const PassBuffer &pass_buffer) = default;

		/**
		 Constructs a pass buffer by moving the given pass buffer.

		 @param[in]		pass_buffer
						A reference to the pass buffer to move.
		 */
		PassBuffer(PassBuffer &&pass_buffer) = default;

		/**
		 Destructs this pass buffer.
		 */
		~PassBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given pass buffer to this pass buffer.

		 @param[in]		pass_buffer
						A reference to the pass buffer to copy.
		 @return		A reference to the copy of the given pass buffer (i.e. 
						this pass buffer).
		 */
		PassBuffer &operator=(const PassBuffer &pass_buffer) = delete;

		/**
		 Moves the given pass buffer to this pass buffer.

		 @param[in]		pass_buffer
						A reference to the pass buffer to move.
		 @return		A reference to the moved pass buffer (i.e. this pass 
						buffer).
		 */
		PassBuffer &operator=(PassBuffer &&pass_buffer) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates this pass buffer for the given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 */
		void Update(const Scene *scene);

		/**
		 Returns the cameras of this pass buffer.

		 @return		A reference to a vector containing the camera nodes
						of this pass buffer. 
		 */
		const vector< const CameraNode * > &GetCameras() const noexcept {
			return m_cameras;
		}
		
		/**
		 Returns the opaque emissive models of this pass buffer.

		 @return		A reference to a vector containing the opaque emissive 
						model nodes of this pass buffer. 
		 */
		const vector< const ModelNode * > &GetOpaqueEmissiveModels() const noexcept {
			return m_opaque_emissive_models;
		}
		
		/**
		 Returns the opaque BRDF models of this pass buffer.

		 @return		A reference to a vector containing the opaque BRDF 
						model nodes of this pass buffer. 
		 */
		const vector< const ModelNode * > &GetOpaqueBRDFModels() const noexcept {
			return m_opaque_brdf_models;
		}
		
		/**
		 Returns the transparent emissive models of this pass buffer.

		 @return		A reference to a vector containing the transparent 
						emissive model nodes of this pass buffer. 
		 */
		const vector< const ModelNode * > &GetTransparentEmissiveModels() const noexcept {
			return m_transparent_emissive_models;
		}
		
		/**
		 Returns the transparent BRDF models of this pass buffer.

		 @return		A reference to a vector containing the transparent BRDF 
						model nodes of this pass buffer. 
		 */
		const vector< const ModelNode * > &GetTransparentBRDFModels() const noexcept {
			return m_transparent_brdf_models;
		}
		
		/**
		 Returns the directional lights of this pass buffer.

		 @return		A reference to a vector containing the directional 
						light nodes of this pass buffer. 
		 */
		const vector< const DirectionalLightNode * > &GetDirectionalLights() const noexcept {
			return m_directional_lights;
		}
		
		/**
		 Returns the directional lights with shadow mapping of this pass 
		 buffer.

		 @return		A reference to a vector containing the directional 
						light with shadow mapping nodes of this pass buffer. 
		 */
		const vector< const DirectionalLightNode * > &GetDirectionalLightsWithShadowMapping() const noexcept {
			return m_sm_directional_lights;
		}
		
		/**
		 Returns the omni lights of this pass buffer.

		 @return		A reference to a vector containing the omni light nodes 
						of this pass buffer. 
		 */
		const vector< const OmniLightNode * > &GetOmniLights() const noexcept {
			return m_omni_lights;
		}
		
		/**
		 Returns the omni lights with shadow mapping of this pass buffer.

		 @return		A reference to a vector containing the omni light with 
						shadow mapping nodes of this pass buffer. 
		 */
		const vector< const OmniLightNode * > &GetOmniLightsWithShadowMapping() const noexcept {
			return m_sm_omni_lights;
		}
		
		/**
		 Returns the spotlights of this pass buffer.

		 @return		A reference to a vector containing the spotlight nodes 
						of this pass buffer. 
		 */
		const vector< const SpotLightNode * > &GetSpotLights() const noexcept {
			return m_spot_lights;
		}
		
		/**
		 Returns the spotlights with shadow mapping of this pass buffer.

		 @return		A reference to a vector containing the spotlight with 
						shadow mapping nodes of this pass buffer. 
		 */
		const vector< const SpotLightNode * > &GetSpotLightsWithShadowMapping() const noexcept {
			return m_sm_spot_lights;
		}
		
		/**
		 Returns the sprites of this pass buffer.

		 @return		A reference to a vector containing the sprite nodes of 
						this pass buffer. 
		 */
		const vector< const SpriteNode * > &GetSprites() const noexcept {
			return m_sprites;
		}
		
		/**
		 Returns the ambient light of this pass buffer.

		 @return		A reference to the RGB spectrum of the ambient light of 
						this pass buffer. 
		 */
		const RGBSpectrum &GetAmbientLight() const noexcept {
			return m_ambient_light;
		}
		
		/**
		 Returns the fog of this pass buffer.

		 @return		A pointer to the fog of this pass buffer. 
		 */
		const SceneFog *GetFog() const noexcept {
			return m_fog;
		}

		/**
		 Returns the sky of this pass buffer.

		 @return		A pointer to the sky of this pass buffer. 
		 */
		const Sky *GetSky() const noexcept {
			return m_sky;
		}

		/**
		 Returns the minimum of the material coefficient at the given index.

		 @pre			@a index < 
						{@link mage::PassBuffer::s_nb_material_coefficients}.
		 @param[in]		index
						The index.
		 @return		The minimum of the material coefficient at the given 
						index.
		 */
		float GetMaterialCoefficientMinimum(u8 index) const noexcept;
		
		/**
		 Returns the maximum of the material coefficient at the given index.

		 @pre			@a index < 
						{@link mage::PassBuffer::s_nb_material_coefficients}.
		 @param[in]		index
						The index.
		 @return		The maximum of the material coefficient at the given 
						index.
		 */
		float GetMaterialCoefficientMaximum(u8 index) const noexcept;

		/**
		 Returns the range of the material coefficient at the given index.

		 @pre			@a index < 
						{@link mage::PassBuffer::s_nb_material_coefficients}.
		 @param[in]		index
						The index.
		 @return		The range of the material coefficient at the given 
						index.
		 */
		float GetMaterialCoefficientRange(u8 index) const noexcept;
		
	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Updates the cameras of this pass buffer for the given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 */
		void UpdateCameras(const Scene *scene);

		/**
		 Updates the models of this pass buffer for the given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 */
		void UpdateModels(const Scene *scene);

		/**
		 Updates the lights of this pass buffer for the given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 */
		void UpdateLights(const Scene *scene);

		/**
		 Updates the sprites of this pass buffer for the given scene.

		 @pre			@a scene is not equal to @c nullptr.
		 @param[in]		scene
						A pointer to the scene.
		 */
		void UpdateSprites(const Scene *scene);

		/**
		 Resets the material coefficients of this pass buffer.
		 */
		void ResetMaterialCoefficients() noexcept;

		/**
		 Updates the material coefficients of this pass buffer.

		 @pre			@a material is not equal to @c nullptr.
		 @param[in]		material
						A pointer to the material.
		 */
		void UpdateMaterialCoefficients(const Material *material) noexcept;

		/**
		 Finishes the material coefficients of this pass buffer. This handles 
		 material coefficient ranges which are equal to zero.
		 */
		void FinishMaterialCoefficients() noexcept;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A vector containing pointers to the camera nodes of this pass buffer.
		 */
		vector< const CameraNode * > m_cameras;

		/**
		 A vector containing pointers to the opaque emissive model nodes of 
		 this pass buffer.
		 */
		vector< const ModelNode * >	m_opaque_emissive_models;

		/**
		 A vector containing pointers to the opaque BRDF model nodes of this 
		 pass buffer.
		 */
		vector< const ModelNode * >	m_opaque_brdf_models;

		/**
		 A vector containing pointers to the transparent emissive model nodes
		 of this pass buffer.
		 */
		vector< const ModelNode * >	m_transparent_emissive_models;

		/**
		 A vector containing pointers to the transparent BRDF model nodes of 
		 this pass buffer.
		 */
		vector< const ModelNode * >	m_transparent_brdf_models;

		/**
		 A vector containing pointers to the directional nodes of this pass 
		 buffer.
		 */
		vector< const DirectionalLightNode * > m_directional_lights;

		/**
		 A vector containing pointers to the directional with shadow mapping 
		 nodes of this pass buffer.
		 */
		vector< const DirectionalLightNode * > m_sm_directional_lights;

		/**
		 A vector containing pointers to the omni light nodes of this pass 
		 buffer.
		 */
		vector< const OmniLightNode * >	m_omni_lights;

		/**
		 A vector containing pointers to the omni light with shadow mapping 
		 nodes of this pass buffer.
		 */
		vector< const OmniLightNode * >	m_sm_omni_lights;

		/**
		 A vector containing pointers to the spotlight nodes of this pass 
		 buffer.
		 */
		vector< const SpotLightNode * >	m_spot_lights;

		/**
		 A vector containing pointers to the spotlight with shadow mapping 
		 nodes of this pass buffer.
		 */
		vector< const SpotLightNode * >	m_sm_spot_lights;

		/**
		 A vector containing pointers to the sprite nodes of this pass buffer.
		 */
		vector< const SpriteNode * > m_sprites;

		/**
		 The RGB spectrum of the ambient light of this pass buffer.
		 */
		RGBSpectrum	m_ambient_light;

		/**
		 A pointer to the scene fog of this pass buffer.
		 */
		const SceneFog *m_fog;

		/**
		 A pointer to the sky of this pass buffer.
		 */
		const Sky *m_sky;

		/**
		 The minima of the material coefficients of this pass buffer.
		 */
		float m_material_coefficient_min[s_nb_material_coefficients];

		/**
		 The maxima of the material coefficients of this pass buffer.
		 */
		float m_material_coefficient_max[s_nb_material_coefficients];
	};
}