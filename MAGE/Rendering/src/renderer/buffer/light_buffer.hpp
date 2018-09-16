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

	//-------------------------------------------------------------------------
	// LightBuffer
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
		U32 m_nb_directional_lights = 0u;

		/**
		 The number of omni lights of this light buffer.
		 */
		U32 m_nb_omni_lights = 0u;

		/**
		 The number of spotlights of this light buffer.
		 */
		U32 m_nb_spot_lights = 0u;

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
		U32 m_nb_sm_directional_lights = 0u;

		/**
		 The number of shadow mapped omni lights of this light buffer.
		 */
		U32 m_nb_sm_omni_lights = 0u;

		/**
		 The number of shadow mapped spotlights of this light buffer.
		 */
		U32 m_nb_sm_spot_lights = 0u;

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
		RGB m_La = {};

		/**
		 The padding of this light buffer.
		 */
		F32 m_padding2 = {};
	};

	static_assert(48u == sizeof(LightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// PointLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

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
		Point3 m_p_world = {};

		/**
		 The inverse of the squared range of the point light of this point 
		 light buffer expressed in inversed squared world space.
		 */
		F32 m_inv_sqr_range = 0.0f;
	};

	static_assert(16u == sizeof(PointLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// DirectionalLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

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
		RGB m_E_ortho = {};

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding0 = {};

		/**
		 The (normalized) negated direction of the directional light expressed 
		 in world space of this directional light buffer.
		 */
		Direction3 m_neg_d_world = {};

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding1 = {};

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-projection matrix 
		 of this directional light buffer.
		 */
		XMMATRIX m_world_to_projection = {};
	};

	static_assert(96u == sizeof(DirectionalLightBuffer),
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// OmniLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

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
		RGB m_I = {};

		/**
		 The padding of this omni light buffer.
		 */
		U32 m_padding0 = {};
	};

	static_assert(32u == sizeof(OmniLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// SpotLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

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
		RGB m_I = {};

		/**
		 The cosine of the umbra angle of the spotlight of this spotlight
		 buffer.
		 */
		F32 m_cos_umbra = 0.0f;

		/**
		 The (normalized) negated direction of the directional light expressed 
		 in world space of this directional light buffer.
		 */
		Direction3 m_neg_d_world = {};

		/**
		 The inverse of the cosine range of the spotlight of this spotlight 
		 buffer.
		 */
		F32 m_cos_inv_range = 0.0f;
	};

	static_assert(48u == sizeof(SpotLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// ShadowMappedOmniLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of shadow mapped omni light buffers used by shaders.
	 */
	struct alignas(16) ShadowMappedOmniLightBuffer : public OmniLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-light matrix of 
		 the shadow mapped omni light of this shadow mapped omni light buffer.
		 */
		XMMATRIX m_world_to_light = {};

		/**
		 The projection values of the light-to-projection transformation matrix
		 of the shadow mapped omni light of this shadow mapped omni light buffer.
		 */
		F32x2 m_projection_values = {};
		
		/**
		 The padding of this shadow mapped omni light buffer. 
		 */
		U32x2 m_padding1 = {};
	};

	static_assert(112u == sizeof(ShadowMappedOmniLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// ShadowMappedSpotLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of shadow mapped spotlight buffers used by shaders.
	 */
	struct alignas(16) ShadowMappedSpotLightBuffer : public SpotLightBuffer {

	public:

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

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
}