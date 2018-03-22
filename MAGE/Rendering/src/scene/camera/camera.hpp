#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\component.hpp"
#include "scene\camera\viewport.hpp"
#include "renderer\configuration.hpp"
#include "renderer\buffer\constant_buffer.hpp"
#include "renderer\buffer\camera_buffer.hpp"
#include "resource\texture\texture.hpp"
#include "math_utils.hpp"
#include "geometry\geometry.hpp"
#include "spectrum\color.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	//-------------------------------------------------------------------------
	// CameraLens
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of camera lenses.
	 */
	class CameraLens final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera settings.
		 */
		constexpr CameraLens() noexcept
			: m_radius(0.0f),
			m_focal_length(100.0f),
			m_max_coc_radius(10.0f) {}

		/**
		 Constructs a camera lens from the given camera lens.

		 @param[in]		lens
						A reference to the camera lens to copy.
		 */
		constexpr CameraLens(const CameraLens& lens) noexcept = default;

		/**
		 Constructs a camera lens by moving the given camera lens.

		 @param[in]		lens
						A reference to the camera lens to move.
		 */
		constexpr CameraLens(CameraLens&& lens) noexcept = default;

		/**
		 Destructs this camera lens.
		 */
		~CameraLens() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given camera lens to this camera lens.

		 @param[in]		lens
						A reference to the camera lens to copy.
		 @return		A reference to the copy of the given camera lens (i.e. 
						this camera lens).
		 */
		constexpr CameraLens& operator=(const CameraLens& lens) noexcept = default;

		/**
		 Moves the given camera lens to this camera lens.

		 @param[in]		lens
						A reference to the camera lens to move.
		 @return		A reference to the moved camera lens (i.e. this camera 
						lens).
		 */
		constexpr CameraLens& operator=(CameraLens&& lens) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this camera lens has a finite aperture.

		 @return		@c true if this camera lens has a finite aperture.
						@c false otherwise.
		 */
		[[nodiscard]]
		constexpr bool HasFiniteAperture() const noexcept {
			return 0.0f != m_radius;
		}

		/**
		 Returns the radius of this camera lens.

		 @return		The radius of this camera lens.
		 */
		[[nodiscard]]
		constexpr F32 GetLensRadius() const noexcept {
			return m_radius;
		}
		
		/**
		 Sets the radius of this camera lens to the given value.

		 @param[in]		radius
						The radius of the camera lens.
		 */
		constexpr void SetLensRadius(F32 radius) noexcept {
			m_radius = radius;
		}

		/**
		 Returns the focal length of this camera lens.

		 @return		The focal length of this camera lens.
		 */
		[[nodiscard]]
		constexpr F32 GetFocalLength() const noexcept {
			return m_focal_length;
		}
		
		/**
		 Sets the focal length of this camera lens to the given value.

		 @param[in]		focal_length
						The focal length.
		 */
		constexpr void SetFocalLength(F32 focal_length) noexcept {
			m_focal_length = focal_length;
		}

		/**
		 Returns the maximum radius of the circle of confusion of this camera 
		 lens.

		 @return		The maximum radius of the circle of confusion of this 
						camera lens.
		 */
		[[nodiscard]]
		constexpr F32 GetMaximumCoCRadius() const noexcept {
			return m_max_coc_radius;
		}
		
		/**
		 Sets the maximum radius of the circle of confusion of this camera lens 
		 to the given value.

		 @param[in]		max_coc_radius
						The maximum radius of the circle of confusion.
		 */
		constexpr void SetMaximumCoCRadius(F32 max_coc_radius) noexcept {
			m_max_coc_radius = max_coc_radius;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The radius of this camera lens.
		 */
		F32 m_radius;

		/**
		 The focal length of this camera lens.
		 */
		F32 m_focal_length;

		/**
		 The maximum radius of the circle-of-confusion of this camera lens.
		 */
		F32 m_max_coc_radius;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// VoxelizationSettings
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of voxelization settingss.
	 */
	class VoxelizationSettings final {

	public:

		//---------------------------------------------------------------------
		// Class Member Methods
		//---------------------------------------------------------------------	

		[[nodiscard]]
		static const Point3 GetVoxelGridCenter() noexcept {
			return s_voxel_grid_center;
		}

		static void SetVoxelGridCenter(Point3 voxel_grid_center) noexcept {
			s_voxel_grid_center = std::move(voxel_grid_center);
		}

		[[nodiscard]]
		static U32 GetVoxelGridResolution() noexcept {
			return s_voxel_grid_resolution;
		}

		static void SetVoxelGridResolution(U32 exponent) noexcept {
			s_voxel_grid_resolution = 2u << exponent;
		}

		[[nodiscard]]
		static F32 GetVoxelGridSize() noexcept {
			return s_voxel_size;
		}

		static void SetVoxelGridSize(F32 voxel_size) noexcept {
			s_voxel_size = std::abs(voxel_size);
		}

		[[nodiscard]]
		static U32 GetMaxVoxelTextureMipLevel() noexcept {
			return static_cast< U32 >(std::log2(s_voxel_grid_resolution));
		}

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------	

		/**
		 The maximal number of cones to trace for each shading point.
		 */
		static constexpr U32 s_max_nb_cones = 16u;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------	

		/**
		 Constructs a voxelization settings.
		 */
		constexpr VoxelizationSettings()
			: m_nb_cones(0u), 
			m_cone_step_multiplier(1.0f), 
			m_max_cone_distance(1.0f) {}

		/**
		 Constructs a voxelization settings from the given voxelization 
		 settings.

		 @param[in]		settings
						A reference to the voxelization settings to copy.
		 */
		constexpr VoxelizationSettings(
			const VoxelizationSettings& settings) = default;

		/**
		 Constructs a voxelization settings by moving the given voxelization 
		 settings.

		 @param[in]		settings
						A reference to the voxelization settings to move.
		 */
		constexpr VoxelizationSettings(
			VoxelizationSettings&& settings) noexcept = default;

		/**
		 Destructs this voxelization settings.
		 */
		~VoxelizationSettings() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given voxelization settings to this voxelization settings.

		 @param[in]		settings
						A reference to the voxelization settings to copy.
		 @return		A reference to the copy of the given voxelization 
						settings (i.e. this voxelization settings).
		 */
		constexpr VoxelizationSettings& operator=(
			const VoxelizationSettings& settings) noexcept = default;

		/**
		 Moves the given voxelization settings to this voxelization settings.

		 @param[in]		settings
						A reference to the voxelization settings to move.
		 @return		A reference to the moved voxelization settings (i.e. 
						this voxelization settings).
		 */
		constexpr VoxelizationSettings& operator=(
			VoxelizationSettings&& settings) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		[[nodiscard]]
		constexpr U32 GetNumberOfCones() const noexcept {
			return m_nb_cones;
		}

		constexpr void SetNumberOfCones(U32 nb_cones) noexcept {
			m_nb_cones = std::clamp(nb_cones, 0u, s_max_nb_cones);
		}

		[[nodiscard]]
		constexpr F32 GetConeStepMultiplier() const noexcept {
			return m_cone_step_multiplier;
		}

		void SetConeStepMultiplier(F32 cone_step_multiplier) noexcept {
			m_cone_step_multiplier = std::abs(cone_step_multiplier);
		}

		[[nodiscard]]
		constexpr F32 GetMaxConeDistance() const noexcept {
			return m_max_cone_distance;
		}

		void SetMaxConeDistance(F32 max_cone_distance) noexcept {
			m_max_cone_distance = std::abs(max_cone_distance);
		}

	private:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		/**
		 The center of the voxel grid expressed in world space.
		 */
		static Point3 s_voxel_grid_center;

		/**
		 The resolution of the voxel grid for all dimensions.
		 */
		static U32 s_voxel_grid_resolution;

		/**
		 The size of a voxel for all dimensions expressed in world space.
		 */
		static F32 s_voxel_size;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------
		
		/**
		 The number of cones to trace for each shading point of this 
		 voxelization settings.
		 */
		U32 m_nb_cones;
		
		/**
		 The step multiplier of the cone while marching of this voxelization 
		 settings.
		 */
		F32 m_cone_step_multiplier;
		
		/**
		 The maximal cone distance expressed in normalized texture coordinates 
		 of this voxelization settings.
		 */
		F32 m_max_cone_distance;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Fog
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of fog with respect to the camera position (eye) to avoid popping 
	 artifacts while moving.
	 */
	class Fog final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a fog.
		 */
		constexpr Fog() noexcept
			: m_base_color(color::Silver), 
			m_density(0.0) {}

		/**
		 Constructs a fog from the given fog.

		 @param[in]		fog
						A reference to the fog to copy.
		 */
		constexpr Fog(const Fog& fog) noexcept = default;

		/**
		 Constructs a fog by moving the given fog.

		 @param[in]		fog
						A reference to the fog to move.
		 */
		constexpr Fog(Fog&& fog) noexcept = default;

		/**
		 Destructs this fog.
		 */
		~Fog() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given fog to this fog.

		 @param[in]		fog
						A reference to the fog to copy.
		 @return		A reference to the copy of the given fog (i.e. this fog).
		 */
		constexpr Fog& operator=(const Fog& fog) noexcept = default;

		/**
		 Moves the given fog to this fog.

		 @param[in]		fog
						A reference to the fog to move.
		 @return		A reference to the moved fog (i.e. this fog).
		 */
		constexpr Fog& operator=(Fog&& fog) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the sRGB base color of this fog.

		 @return		A reference to the sRGB base color of this fog.
		 */
		[[nodiscard]]
		constexpr SRGB& GetBaseColor() noexcept {
			return m_base_color;
		}

		/**
		 Returns the sRGB base color of this fog.

		 @return		A reference to the sRGB base color of this fog.
		 */
		[[nodiscard]]
		constexpr const SRGB& GetBaseColor() const noexcept {
			return m_base_color;
		}

		/**
		 Returns the density of this fog.
		
		 @return		The density of this fog.
		 */
		[[nodiscard]]
		constexpr F32 GetDensity() const noexcept {
			return m_density;
		}

		/**
		 Sets the density of this fog to the given value.

		 @param[in]		density
						The density.
		 */
		constexpr void SetDensity(F32 density) noexcept {
			m_density = Saturate(density);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The sRGB base color of this fog.
		 */
		SRGB m_base_color;

		/**
		 The density of this fog.
		 */
		F32 m_density;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Sky
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of sky domes.
	 */
	class Sky final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------	

		/**
		 Constructs a sky.
		 */
		Sky() 
			: m_texture(), 
			m_scale_z(1.5f) {}

		/**
		 Constructs a sky from the given sky.

		 @param[in]		sky
						A reference to the sky to copy.
		 */
		Sky(const Sky& sky) = default;

		/**
		 Constructs a sky by moving the given sky.

		 @param[in]		sky
						A reference to the sky to move.
		 */
		Sky(Sky&& sky) noexcept = default;

		/**
		 Destructs this sky.
		 */
		~Sky() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given sky to this sky.

		 @param[in]		sky
						A reference to the sky to copy.
		 @return		A reference to the copy of the given sky (i.e. this 
						sky).
		 */
		Sky& operator=(const Sky& sky) noexcept = default;

		/**
		 Moves the given sky to this sky.

		 @param[in]		sky
						A reference to the sky to move.
		 @return		A reference to the moved sky (i.e. this sky).
		 */
		Sky& operator=(Sky&& sky) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the texture of this sky.

		 @return		A pointer to the texture of this sky.
		 */
		[[nodiscard]]
		TexturePtr GetTexture() const noexcept {
			return m_texture;
		}
		
		/**
		 Returns the shader resource view of the texture of this sky.

		 @return		@c nullptr, if this sky has no texture.
		 @return		A pointer to the shader resource view of the texture of 
						this sky.
		 */
		[[nodiscard]]
		ID3D11ShaderResourceView* GetSRV() const noexcept {
			return m_texture ? m_texture->Get() : nullptr;
		}
		
		/**
		 Sets the texture of this sky to the given texture.

		 @param[in]		texture
						The texture of this sky.
		 */
		void SetTexture(TexturePtr texture) {
			m_texture = std::move(texture);
		}

		/**
		 Returns the scaling factor of the z component of the sky domes of this 
		 sky.
		
		 @return		The scaling factor of the z component of the sky domes 
						of this sky.
		 */
		[[nodiscard]]
		F32 GetScaleZ() const noexcept {
			return m_scale_z;
		}

		/**
		 Sets scaling factor of the z component of the sky domes of this sky to 
		 the given value.

		 @param[in]		scale_z
						The scaling factor.
		 */
		void SetScaleZ(F32 scale_z) noexcept {
			m_scale_z = std::abs(scale_z);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The cube map texture of this sky.
		 */
		TexturePtr m_texture;

		/**
		 The scaling factor of the z component of the sky domes of this sky.
		 */
		F32 m_scale_z;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// CameraSettings
	//-------------------------------------------------------------------------
	#pragma region

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
			m_brdf(BRDF::Default), 
			m_tone_mapping(ToneMapping::Default), 
			m_gamma(2.2f), 
			m_render_layer_mask(static_cast< U32 >(RenderLayer::None)), 
			m_fog(), 
			m_sky() {}
		
		/**
		 Constructs a camera settings from the given camera settings.

		 @param[in]		settings
						A reference to the camera settings to copy.
		 */
		CameraSettings(const CameraSettings& settings) noexcept = default;

		/**
		 Constructs a camera settings by moving the given camera settings.

		 @param[in]		settings
						A reference to the camera settings to move.
		 */
		CameraSettings(CameraSettings&& settings) noexcept = default;

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
		CameraSettings& operator=(const CameraSettings& settings) noexcept = default;

		/**
		 Moves the given camera settings to this camera settings.

		 @param[in]		settings
						A reference to the camera settings to move.
		 @return		A reference to the moved camera settings (i.e. this 
						camera settings).
		 */
		CameraSettings& operator=(CameraSettings&& settings) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Render Mode
		//---------------------------------------------------------------------

		[[nodiscard]]
		RenderMode GetRenderMode() const noexcept {
			return m_render_mode;
		}

		void SetRenderMode(RenderMode render_mode) noexcept {
			m_render_mode = render_mode;
		}

		//---------------------------------------------------------------------
		// Member Methods: BRDF
		//---------------------------------------------------------------------

		[[nodiscard]]
		BRDF GetBRDF() const noexcept {
			return m_brdf;
		}

		void SetBRDF(BRDF brdf) noexcept {
			m_brdf = brdf;
		}

		//---------------------------------------------------------------------
		// Member Methods: Tone Mapping
		//---------------------------------------------------------------------

		[[nodiscard]]
		ToneMapping GetToneMapping() const noexcept {
			return m_tone_mapping;
		}

		void SetToneMapping(ToneMapping tone_mapping) noexcept {
			m_tone_mapping = tone_mapping;
		}

		//---------------------------------------------------------------------
		// Member Methods: Voxelization
		//---------------------------------------------------------------------

		[[nodiscard]]
		VoxelizationSettings GetVoxelizationSettings() const noexcept {
			return m_voxelization_settings;
		}

		void SetVoxelizationSettings(
			VoxelizationSettings voxelization_settings) noexcept {

			m_voxelization_settings = voxelization_settings;
		}

		//---------------------------------------------------------------------
		// Member Methods: Gamma Correction
		//---------------------------------------------------------------------

		[[nodiscard]]
		F32 GetGamma() const noexcept {
			return m_gamma;
		}

		void SetGamma(F32 gamma) noexcept {
			m_gamma = gamma;
		}

		//---------------------------------------------------------------------
		// Member Methods: Render Layers
		//---------------------------------------------------------------------

		[[nodiscard]]
		bool ContainsRenderLayers() const noexcept {
			return static_cast< U32 >(RenderLayer::None) != m_render_layer_mask;
		}

		[[nodiscard]]
		bool ContainsRenderLayer(RenderLayer render_layer) const noexcept {
			return static_cast< bool >(static_cast< U32 >(render_layer)
				                     &  m_render_layer_mask);
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

		//---------------------------------------------------------------------
		// Member Methods: Fog
		//---------------------------------------------------------------------

		[[nodiscard]]
		Fog& GetFog() noexcept {
			return m_fog;
		}

		[[nodiscard]]
		const Fog& GetFog() const noexcept {
			return m_fog;
		}

		//---------------------------------------------------------------------
		// Member Methods: Sky
		//---------------------------------------------------------------------

		[[nodiscard]]
		Sky& GetSky() noexcept {
			return m_sky;
		}

		[[nodiscard]]
		const Sky& GetSky() const noexcept {
			return m_sky;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables: Render Mode
		//---------------------------------------------------------------------

		/**
		 The render mode of this camera settings.
		 */
		RenderMode m_render_mode;

		//---------------------------------------------------------------------
		// Member Variables: BRDF
		//---------------------------------------------------------------------

		/**
		 The BRDF of this camera settings.
		 */
		BRDF m_brdf;

		//---------------------------------------------------------------------
		// Member Variables: Tone Mapping
		//---------------------------------------------------------------------

		/**
		 The Tone Mapping of this camera settings.
		 */
		ToneMapping m_tone_mapping;

		//---------------------------------------------------------------------
		// Member Variables: Voxelization Settings
		//---------------------------------------------------------------------

		/**
		 The voxelization settings of this camera settings.
		 */
		VoxelizationSettings m_voxelization_settings;

		//---------------------------------------------------------------------
		// Member Variables: Gamma Correction
		//---------------------------------------------------------------------

		/**
		 The gamma exponent of this camera settings.
		 */
		F32 m_gamma;

		//---------------------------------------------------------------------
		// Member Variables: Render Layers
		//---------------------------------------------------------------------

		/**
		 The render layer mask of this camera settings.
		 */
		U32 m_render_layer_mask;

		//---------------------------------------------------------------------
		// Member Variables: Fog
		//---------------------------------------------------------------------

		/**
		 The fog of this camera settings. 
		 */
		Fog m_fog;

		//---------------------------------------------------------------------
		// Member Variables: Sky
		//---------------------------------------------------------------------

		/**
		 The sky of this camera settings. 
		 */
		Sky m_sky;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Camera
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of cameras.
	 */
	class Camera : public Component {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------	

		/**
		 Destructs this camera.
		 */
		virtual ~Camera();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given camera to this camera.

		 @param[in]		camera
						A reference to the camera to copy.
		 @return		A reference to the copy of the given camera (i.e. this 
						camera).
		 */
		Camera& operator=(const Camera& camera) = delete;

		/**
		 Moves the given camera to this camera.

		 @param[in]		camera
						A reference to the camera to move.
		 @return		A reference to the moved camera (i.e. this camera).
		 */
		Camera& operator=(Camera&& camera) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Projection
		//---------------------------------------------------------------------

		/**
		 Returns the clipping planes of this camera expressed in camera space.

		 @return		The clipping planes of this camera expressed in camera 
						space.
		 */
		[[nodiscard]]
		const F32x2 GetClippingPlanes() const noexcept {
			return m_clipping_planes;
		}
		
		/**
		 Sets the clipping planes of this camera expressed in camera space to 
		 the given clipping planes.

		 @param[in]		clipping_planes
						The clipping planes.
		 */
		void SetClippingPlanes(F32x2 clipping_planes) noexcept {
			m_clipping_planes = std::move(clipping_planes);
		}
		
		/**
		 Returns the camera-to-projection matrix of this camera.

		 @return		The camera-to-projection matrix of this camera.
		 */
		[[nodiscard]]
		virtual const XMMATRIX XM_CALLCONV 
			GetCameraToProjectionMatrix() const noexcept = 0;

		/**
		 Returns the projection-to-camera matrix of this camera.

		 @return		The projection-to-camera matrix of this camera.
		 */
		[[nodiscard]]
		virtual const XMMATRIX XM_CALLCONV 
			GetProjectionToCameraMatrix() const noexcept = 0;

		//---------------------------------------------------------------------
		// Member Methods: Lens
		//---------------------------------------------------------------------

		/**
		 Returns the lens of this camera.

		 @return		A reference to the lens of this camera.	
		 */
		[[nodiscard]]
		CameraLens& GetLens() noexcept {
			return m_lens;
		}
		
		/**
		 Returns the lens of this camera.

		 @return		A reference to the lens of this camera.	
		 */
		[[nodiscard]]
		const CameraLens& GetLens() const noexcept {
			return m_lens;
		}

		//---------------------------------------------------------------------
		// Member Methods: Viewport
		//---------------------------------------------------------------------

		/**
		 Returns the viewport of this camera.

		 @return		A reference to the viewport of this camera.
		 */
		[[nodiscard]]
		Viewport& GetViewport() noexcept {
			return m_viewport;
		}

		/**
		 Returns the viewport of this camera.

		 @return		A reference to the viewport of this camera.
		 */
		[[nodiscard]]
		const Viewport& GetViewport() const noexcept {
			return m_viewport;
		}

		//---------------------------------------------------------------------
		// Member Methods: Settings
		//---------------------------------------------------------------------

		/**
		 Returns the settings of this camera.

		 @return		A reference to the settings of this camera.	
		 */
		[[nodiscard]]
		CameraSettings& GetSettings() noexcept {
			return m_settings;
		}
		
		/**
		 Returns the settings of this camera.

		 @return		A reference to the settings of this camera.
		 */
		[[nodiscard]]
		const CameraSettings& GetSettings() const noexcept {
			return m_settings;
		}

		//---------------------------------------------------------------------
		// Member Methods: Buffer
		//---------------------------------------------------------------------

		/**
		 Updates the buffer of this camera.

		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		aa
						The anti-aliasing mode.
		 */
		void UpdateBuffer(ID3D11DeviceContext& device_context,
						  AntiAliasing aa) const;

		/**
		 Binds the buffer of this camera to the given pipeline stage.

		 @tparam		PipelineStageT
						The pipeline stage type.
		 @param[in]		device_context
						A reference to the device context.
		 @param[in]		slot
						The index into the device's zero-based array to set 
						the constant buffer to (ranges from 0 to 
						@c D3D11_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT - 1).
		 */
		template< typename PipelineStageT >
		void BindBuffer(ID3D11DeviceContext& device_context,
						U32 slot) const noexcept {

			m_buffer.Bind< PipelineStageT >(device_context, slot);
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a camera.

		 @param[in]		device
						A reference to the device.
		 */
		Camera(ID3D11Device& device);

		/**
		 Constructs a camera from the given camera.

		 @param[in]		camera
						A reference to the camera to copy.
		 */
		Camera(const Camera& camera) = delete;

		/**
		 Constructs a camera by moving the given camera.

		 @param[in]		camera
						A reference to the camera to move.
		 */
		Camera(Camera&& camera) noexcept;

	private:

		//---------------------------------------------------------------------
		// Member Variables: Buffer
		//---------------------------------------------------------------------

		/**
		 The buffer of this camera.
		 */
		mutable ConstantBuffer< CameraBuffer > m_buffer;

		//---------------------------------------------------------------------
		// Member Variables: Projection
		//---------------------------------------------------------------------

		/**
		 The clipping planes of this camera expressed in camera space.
		 */
		F32x2 m_clipping_planes;

		//---------------------------------------------------------------------
		// Member Variables: Lens
		//---------------------------------------------------------------------

		/**
		 The lens of this camera.
		 */
		CameraLens m_lens;

		//---------------------------------------------------------------------
		// Member Variables: Viewport
		//---------------------------------------------------------------------

		/**
		 The viewport of this camera.
		 */
		Viewport m_viewport;

		//---------------------------------------------------------------------
		// Member Variables: Settings
		//---------------------------------------------------------------------

		/**
		 The settings of this camera.
		 */
		CameraSettings m_settings;
	};

	#pragma endregion
}