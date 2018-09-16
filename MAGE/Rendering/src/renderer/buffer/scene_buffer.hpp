#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "geometry\geometry.hpp"
#include "spectrum\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::rendering {

	// HLSL expects column-major packed matrices by default.
	// DirectXMath expects row-major packed matrices.

	//-------------------------------------------------------------------------
	// Camera
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of camera buffers.
	 */
	struct alignas(16) CameraBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transformations
		//---------------------------------------------------------------------

		/**
		 The (column-major packed, row-major matrix) world-to-camera matrix of 
		 the camera of this camera buffer.
		 */
		XMMATRIX m_world_to_camera = {};

		/**
		 The (column-major packed, row-major matrix) camera-to-projection 
		 matrix of the camera of this camera buffer.
		 */
		XMMATRIX m_camera_to_projection = {};

		/**
		 The (column-major packed, row-major matrix) projection-to-camera 
		 matrix of the camera of this camera buffer.
		 */
		XMMATRIX m_projection_to_camera = {};

		/**
		 The (column-major packed, row-major matrix) camera-to-world matrix of 
		 the camera of this camera buffer.
		 */
		XMMATRIX m_camera_to_world = {};

		//---------------------------------------------------------------------
		// Member Variables: Viewports
		//---------------------------------------------------------------------

		/**
		 The top left corner of the viewport of the camera of this camera 
		 buffer.
		 */
		F32x2 m_viewport_top_left;

		/**
		 The resolution of the viewport of the camera of this camera buffer. 
		 */
		U32x2 m_viewport_resolution;

		/**
		 The top left corner of the super-sampled viewport of the camera of 
		 this camera buffer.
		 */
		F32x2 m_ss_viewport_top_left;

		/**
		 The resolution of the super-sampled viewport of the camera of this 
		 camera buffer.
		 */
		U32x2 m_ss_viewport_resolution;

		/**
		 The inverse of the resolution of the viewport of the camera of this 
		 camera buffer. 
		 */
		F32x2 m_viewport_inv_resolution;

		/**
		 The inverse of the resolution of the super-sampled viewport of the 
		 camera of this camera buffer.
		 */
		F32x2 m_ss_viewport_inv_resolution;

		//---------------------------------------------------------------------
		// Member Variables: Fog
		//---------------------------------------------------------------------
	
		/**
		 The (linear) color of the fog of this camera buffer.
		 */
		RGB m_fog_color;
		
		/**
		 The density of the fog of this camera buffer.
		 */
		F32 m_fog_density = {};

		//---------------------------------------------------------------------
		// Member Variables: Sky
		//---------------------------------------------------------------------

		/**
		 The scaling factor of the z component of sky domes of this camera 
		 buffer. 
		 */
		F32 m_sky_dome_scale_z = 1.0f;

		//---------------------------------------------------------------------
		// Member Variables: Voxel Cone Tracing
		//---------------------------------------------------------------------

		/**
		 The cone step expressed in voxel UVW space of this camera buffer.
		 */
		F32 m_cone_step = 0.1f;
		
		/**
		 The maximal cone distance expressed in voxel UVW space of this camera 
		 buffer.
		 */
		F32 m_max_cone_distance = 1.0f;

		//---------------------------------------------------------------------
		// Member Variables: Post-processing
		//---------------------------------------------------------------------

		/**
		 The radius of the lens aperture of the camera lens of this camera 
		 buffer.
		 */
		F32 m_aperture_radius = {};

		/**
		 The focal length (i.e. distance between the lens aperture and the 
		 focal point/focus expressed in camera space) of the camera lens of 
		 this camera buffer.
		 */
		F32 m_focal_length = {};

		/**
		 The focus distance (i.e. distance between the lens aperture and the
		 objects in perfect focus expressed in camera space) of the camera lens 
		 of this camera buffer.
		 */
		F32 m_focus_distance = {};

		/**
		 The padding of this camera buffer.
		 */
		U32x2 m_padding;
	};

	static_assert(352u == sizeof(CameraBuffer), 
				  "CPU/GPU struct mismatch");

	/**
	 A struct of secondary camera buffers.
	 */
	struct alignas(16) SecondaryCameraBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transformations
		//---------------------------------------------------------------------

		/**
		 The (column-major packed, row-major matrix) world-to-camera matrix of 
		 the camera of this secondary camera buffer.
		 */
		XMMATRIX m_world_to_camera = {};

		/**
		 The (column-major packed, row-major matrix) camera-to-projection 
		 matrix of the camera of this secondary camera buffer.
		 */
		XMMATRIX m_camera_to_projection = {};
	};

	static_assert(128u == sizeof(SecondaryCameraBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// Light
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of light buffers used by shaders.
	 */
	struct alignas(16) LightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Lights without Shadow Mapping
		//---------------------------------------------------------------------

		/**
		 The number of directional lights of this light buffer.
		 */
		U32 m_nb_directional_lights = {};

		/**
		 The number of omni lights of this light buffer.
		 */
		U32 m_nb_omni_lights = {};

		/**
		 The number of spotlights of this light buffer.
		 */
		U32 m_nb_spot_lights = {};

		/**
		 The padding of this light buffer. 
		 */
		U32 m_padding0 = {};

		//---------------------------------------------------------------------
		// Member Variables: Lights with Shadow Mapping
		//---------------------------------------------------------------------

		/**
		 The number of shadow mapped directional lights of this light buffer.
		 */
		U32 m_nb_sm_directional_lights = {};

		/**
		 The number of shadow mapped omni lights of this light buffer.
		 */
		U32 m_nb_sm_omni_lights = {};

		/**
		 The number of shadow mapped spotlights of this light buffer.
		 */
		U32 m_nb_sm_spot_lights = {};

		/**
		 The padding of this light buffer. 
		 */
		U32 m_padding1 = {};

		//---------------------------------------------------------------------
		// Member Variables: Ambient Light
		//---------------------------------------------------------------------

		/**
		 The ambient radiance in watts per square meter per steradians of this 
		 light buffer.
		 */
		RGB m_La;

		/**
		 The padding of this light buffer.
		 */
		F32 m_padding2 = {};
	};

	static_assert(48u == sizeof(LightBuffer), 
				  "CPU/GPU struct mismatch");

	/**
	 A struct of point light buffers used by shaders.
	 */
	struct alignas(16) PointLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the point light of this point light buffer expressed 
		 in world space.
		 */
		Point3 m_p_world;

		/**
		 The inverse of the squared range of the point light of this point 
		 light buffer expressed in inversed squared world space.
		 */
		F32 m_inv_sqr_range = {};
	};

	static_assert(16u == sizeof(PointLightBuffer), 
				  "CPU/GPU struct mismatch");

	/**
	 A struct of directional light buffers used by shaders.
	 */
	struct alignas(16) DirectionalLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The (orthogonal) irradiance of the directional light of this 
		 directional light buffer.
		 */
		RGB m_E_ortho;

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding0 = {};

		/**
		 The (normalized) negated direction of the directional light expressed 
		 in world space of this directional light buffer.
		 */
		Direction3 m_neg_d_world;

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding1 = {};

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		/**
		 The (column-major packed, row-major matrix) world-to-projection matrix 
		 of this directional light buffer.
		 */
		XMMATRIX m_world_to_projection = {};
	};

	static_assert(96u == sizeof(DirectionalLightBuffer),
				  "CPU/GPU struct mismatch");

	/**
	 A struct of omni light buffers used by shaders.
	 */
	struct alignas(16) OmniLightBuffer : public PointLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The radiant intensity in watts per steradians of the omni light of 
		 this omni light buffer.
		 */
		RGB m_I;

		/**
		 The padding of this omni light buffer.
		 */
		U32 m_padding0 = {};
	};

	static_assert(32u == sizeof(OmniLightBuffer), 
				  "CPU/GPU struct mismatch");

	/**
	 A struct of spotlight buffers used by shaders.
	 */
	struct alignas(16) SpotLightBuffer : public PointLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The radiant intensity in watts per steradians of the spotlight of this 
		 spotlight buffer.
		 */
		RGB m_I;

		/**
		 The cosine of the umbra angle of the spotlight of this spotlight
		 buffer.
		 */
		F32 m_cos_umbra = {};

		/**
		 The (normalized) negated direction of the directional light expressed 
		 in world space of this directional light buffer.
		 */
		Direction3 m_neg_d_world;

		/**
		 The inverse of the cosine range of the spotlight of this spotlight 
		 buffer.
		 */
		F32 m_cos_inv_range = {};
	};

	static_assert(48u == sizeof(SpotLightBuffer), 
				  "CPU/GPU struct mismatch");

	/**
	 A struct of shadow mapped omni light buffers used by shaders.
	 */
	struct alignas(16) ShadowMappedOmniLightBuffer : public OmniLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		/**
		 The (column-major packed, row-major matrix) world-to-light matrix of 
		 the shadow mapped omni light of this shadow mapped omni light buffer.
		 */
		XMMATRIX m_world_to_light = {};

		/**
		 The projection values of the light-to-projection transformation matrix
		 of the shadow mapped omni light of this shadow mapped omni light buffer.
		 */
		F32x2 m_projection_values;
		
		/**
		 The padding of this shadow mapped omni light buffer. 
		 */
		U32x2 m_padding1;
	};

	static_assert(112u == sizeof(ShadowMappedOmniLightBuffer), 
				  "CPU/GPU struct mismatch");

	/**
	 A struct of shadow mapped spotlight buffers used by shaders.
	 */
	struct alignas(16) ShadowMappedSpotLightBuffer : public SpotLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		/**
		 The (column-major packed, row-major matrix) world-to-projection 
		 matrix of the shadow mapped spotlight of this shadow mapped spotlight 
		 buffer.
		 */
		XMMATRIX m_world_to_projection = {};
	};

	static_assert(112u == sizeof(ShadowMappedSpotLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// Model
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of model buffers.
	 */
	struct alignas(16) ModelBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transforms
		//---------------------------------------------------------------------

		/**
		 The (column-major packed, row-major matrix) object-to-world matrix of 
		 this model buffer.
		 */
		XMMATRIX m_object_to_world = {};
		
		/**
		 The (column-major packed, row-major matrix) object-to-world inverse 
		 transpose matrix (normal-to-world matrix) of this model buffer.
		 */
		XMMATRIX m_normal_to_world = {};

		/**
		 The (column-major packed, row-major matrix) texture transform matrix 
		 of this model buffer.
		 */
		XMMATRIX m_texture_transform = {};

		//---------------------------------------------------------------------
		// Member Variables: Material
		//---------------------------------------------------------------------

		/**
		 The (linear) base color of the material of this model buffer.
		 */
		RGBA m_base_color;

		/**
		 The (linear) roughness of the material of this model buffer.
		 */
		F32 m_roughness = 0.0f;

		/**
		 The (linear) metalness of the material of this model buffer.
		 */
		F32 m_metalness = 0.0f;

		/**
		 The padding of this world buffer.
		 */
		U32x2 m_padding;
	};

	static_assert(224u == sizeof(ModelBuffer), "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// World
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of world buffers.
	 */
	struct alignas(16) WorldBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Display Resolution
		//---------------------------------------------------------------------

		/**
		 The resolution of the display of this world buffer.
		 */
		U32x2 m_display_resolution;

		/**
		 The inverse of the resolution of the display of this game buffer.
		 */
		F32x2 m_display_inv_resolution;

		/**
		 The resolution of the super-sampled display of this world buffer.
		 */
		U32x2 m_ss_display_resolution;

		/**
		 The inverse of the resolution of the super-sampled display of this 
		 world buffer.
		 */
		F32x2 m_ss_display_inv_resolution;

		//---------------------------------------------------------------------
		// Member Variables: Voxelization
		//---------------------------------------------------------------------

		/**
		 The center of the voxel grid expressed in world space of this game 
		 buffer.
		 */
		Point3 m_voxel_grid_center;

		/**
		 The maximum mip level of the voxel texture of this world buffer.
		 */
		U32 m_voxel_texture_max_mip_level = {};

		/**
		 The resolution of the voxel grid for all dimensions of this game 
		 buffer.
		 */
		U32 m_voxel_grid_resolution = {};

		/**
		 The inverse resolution of the voxel grid for all dimensions of this 
		 world buffer.
		 */
		F32 m_voxel_grid_inv_resolution = {};

		/**
		 The size of a voxel for all dimensions of this world buffer.
		 */
		F32 m_voxel_size = {};

		/**
		 The inverse size of a voxel for all dimensions of this world buffer.
		 */
		F32 m_voxel_inv_size = {};

		//---------------------------------------------------------------------
		// Member Variables: Time
		//---------------------------------------------------------------------

		/**
		 The time of this world buffer. 
		 */
		F32 m_time = {};

		//---------------------------------------------------------------------
		// Member Variables: Gamma Correction
		//---------------------------------------------------------------------

		/**
		 The inverse gamma exponent of this world buffer.
		 */
		F32 m_inv_gamma = 1.0f;

		/**
		 The passing of this world buffer.
		 */
		U32x2 m_padding;
	};

	static_assert(80u == sizeof(WorldBuffer), "CPU/GPU struct mismatch");

	#pragma endregion
}