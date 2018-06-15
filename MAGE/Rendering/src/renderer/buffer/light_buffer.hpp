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
	struct alignas(16) LightBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a light buffer.
		 */
		LightBuffer() noexcept
			: m_nb_directional_lights(0u), 
			m_nb_omni_lights(0u), 
			m_nb_spot_lights(0u), 
			m_padding0(0u),
			m_nb_sm_directional_lights(0u), 
			m_nb_sm_omni_lights(0u), 
			m_nb_sm_spot_lights(0u), 
			m_padding1(0u), 
			m_La(),
			m_padding2(0.0f) {}
		
		/**
		 Constructs a light buffer from the given light buffer.

		 @param[in]		buffer
						A reference to the light buffer to copy.
		 */
		LightBuffer(const LightBuffer& buffer) noexcept = default;
		
		/**
		 Constructs a light buffer by moving the given light buffer.

		 @param[in]		buffer
						A reference to the light buffer to move.
		 */
		LightBuffer(LightBuffer&& buffer) noexcept = default;
		
		/**
		 Destructs this light buffer.
		 */
		~LightBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given light buffer to this light buffer.

		 @param[in]		buffer
						A reference to the light buffer to copy.
		 @return		A reference to the copy of the given light buffer (i.e. 
						this light buffer).
		 */
		LightBuffer& operator=(const LightBuffer& buffer) noexcept = default;
		
		/**
		 Moves the given light buffer to this light buffer.

		 @param[in]		buffer
						A reference to the light buffer to move.
		 @return		A reference to the moved light buffer (i.e. this light 
						buffer).
		 */
		LightBuffer& operator=(LightBuffer&& buffer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables: Lights without Shadow Mapping
		//---------------------------------------------------------------------

		/**
		 The number of directional lights of this light buffer.
		 */
		U32 m_nb_directional_lights;

		/**
		 The number of omni lights of this light buffer.
		 */
		U32 m_nb_omni_lights;

		/**
		 The number of spotlights of this light buffer.
		 */
		U32 m_nb_spot_lights;

		/**
		 The padding of this light buffer. 
		 */
		U32 m_padding0;

		//---------------------------------------------------------------------
		// Member Variables: Lights with Shadow Mapping
		//---------------------------------------------------------------------

		/**
		 The number of shadow mapped directional lights of this light buffer.
		 */
		U32 m_nb_sm_directional_lights;

		/**
		 The number of shadow mapped omni lights of this light buffer.
		 */
		U32 m_nb_sm_omni_lights;

		/**
		 The number of shadow mapped spotlights of this light buffer.
		 */
		U32 m_nb_sm_spot_lights;

		/**
		 The padding of this light buffer. 
		 */
		U32 m_padding1;

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
		F32 m_padding2;
	};

	static_assert(48 == sizeof(LightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// DirectionalLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of directional light buffers used by shaders.
	 */
	struct alignas(16) DirectionalLightBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an directional light buffer.
		 */
		DirectionalLightBuffer() noexcept
			: m_E(), 
			m_padding0(0u),
			m_neg_d(), 
			m_padding1(0u) {}
		
		/**
		 Constructs an directional light buffer from the given directional 
		 light buffer.

		 @param[in]		buffer
						A reference to the directional light buffer to copy.
		 */
		DirectionalLightBuffer(
			const DirectionalLightBuffer& buffer) noexcept = default;

		/**
		 Constructs an directional light buffer by moving the given directional 
		 light buffer.

		 @param[in]		buffer
						A reference to the directional light buffer to move.
		 */
		DirectionalLightBuffer(
			DirectionalLightBuffer&& buffer) noexcept = default;
		
		/**
		 Destructs this directional light buffer.
		 */
		~DirectionalLightBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given directional light buffer to this directional light 
		 buffer.

		 @param[in]		buffer
						A reference to the directional light buffer to copy.
		 @return		A reference to the copy of the given directional light 
						buffer (i.e. this directional light buffer).
		 */
		DirectionalLightBuffer& operator=(
			const DirectionalLightBuffer& buffer) = default;

		/**
		 Moves the given directional light buffer to this directional light 
		 buffer.

		 @param[in]		buffer
						A reference to the directional light buffer to move.
		 @return		A reference to the moved directional light buffer (i.e. 
						this directional light buffer).
		 */
		DirectionalLightBuffer& operator=(
			DirectionalLightBuffer&& buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The irradiance in watts per square meter of the directional light of 
		 this directional light buffer.
		 */
		RGB m_E;

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding0;

		/**
		 The (normalized) negated direction of the directional light in world 
		 space of this directional light buffer.
		 */
		Direction3 m_neg_d;

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding1;

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-projection matrix 
		 of this directional light buffer.
		 */
		XMMATRIX m_world_to_projection;
	};

	static_assert(96 == sizeof(DirectionalLightBuffer),
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// OmniLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of omni light buffers used by shaders.
	 */
	struct alignas(16) OmniLightBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an omni light buffer.
		 */
		OmniLightBuffer() noexcept
			: m_p(), 
			m_inv_sqr_range(0.0f),
			m_I(), 
			m_padding0(0u) {}
		
		/**
		 Constructs an omni light buffer from the given omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to copy.
		 */
		OmniLightBuffer(const OmniLightBuffer& buffer) noexcept = default;

		/**
		 Constructs an omni light buffer by moving the given omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to move.
		 */
		OmniLightBuffer(OmniLightBuffer&& buffer) noexcept = default;
		
		/**
		 Destructs this omni light buffer.
		 */
		~OmniLightBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given omni light buffer to this omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to copy.
		 @return		A reference to the copy of the given omni light buffer
						(i.e. this omni light buffer).
		 */
		OmniLightBuffer& operator=(
			const OmniLightBuffer& buffer) noexcept = default;

		/**
		 Moves the given omni light buffer to this omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to move.
		 @return		A reference to the moved omni light buffer (i.e. this 
						omni light buffer).
		 */
		OmniLightBuffer& operator=(
			OmniLightBuffer&& buffer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the omni light in world space of this omni light 
		 buffer.
		 */
		Point3 m_p;

		/**
		 The inverse squared range of the omni light of this omni light buffer.
		 */
		F32 m_inv_sqr_range;

		/**
		 The radiant intensity in watts per steradians of the omni light of 
		 this omni light buffer.
		 */
		RGB m_I;

		/**
		 The padding of this omni light buffer.
		 */
		U32 m_padding0;
	};

	static_assert(32 == sizeof(OmniLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// SpotLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of spotlight buffers used by shaders.
	 */
	struct alignas(16) SpotLightBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a spotlight buffer.
		 */
		SpotLightBuffer() noexcept
			: m_p(), 
			m_inv_sqr_range(0.0f),
			m_I(), 
			m_cos_umbra(0.0f),
			m_neg_d(), 
			m_cos_inv_range(0.0f) {}
		
		/**
		 Constructs a spotlight buffer from the given spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to copy.
		 */
		SpotLightBuffer(const SpotLightBuffer& buffer) noexcept = default;

		/**
		 Constructs a spotlight buffer by moving the given spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to move.
		 */
		SpotLightBuffer(SpotLightBuffer&& buffer) noexcept = default;
		
		/**
		 Destructs this spotlight buffer.
		 */
		~SpotLightBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given spotlight buffer to this spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to copy.
		 @return		A reference to the copy of the given spotlight buffer
						(i.e. this spotlight buffer).
		 */
		SpotLightBuffer& operator=(
			const SpotLightBuffer& buffer) noexcept = default;

		/**
		 Moves the given spotlight buffer to this spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to move.
		 @return		A reference to the moved spotlight buffer (i.e. this 
						spotlight buffer).
		 */
		SpotLightBuffer& operator=(
			SpotLightBuffer&& buffer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the spotlight in world space of this spotlight buffer.
		 */
		Point3 m_p;

		/**
		 The inverse squared range of the spotlight of this spotlight buffer.
		 */
		F32 m_inv_sqr_range;

		/**
		 The radiant intensity in watts per steradians of the spotlight of this 
		 spotlight buffer.
		 */
		RGB m_I;

		/**
		 The cosine of the umbra angle of the spotlight of this spotlight
		 buffer.
		 */
		F32 m_cos_umbra;

		/**
		 The (normalized) negated direction of the spotlight in world space of 
		 this spotlight buffer.
		 */
		Direction3 m_neg_d;

		/**
		 The cosine inverse range of the spotlight of this spotlight buffer.
		 */
		F32 m_cos_inv_range;
	};

	static_assert(48 == sizeof(SpotLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// ShadowMappedOmniLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of shadow mapped omni light buffers used by shaders.
	 */
	struct alignas(16) ShadowMappedOmniLightBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shadow mapped omni light buffer.
		 */
		ShadowMappedOmniLightBuffer() noexcept
			: m_light(), 
			m_world_to_light{}, 
			m_projection_values(), 
			m_padding0() {}
		
		/**
		 Constructs a shadow mapped omni light buffer from the given shadow 
		 mapped omni light buffer.

		 @param[in]		buffer
						A reference to the shadow mapped omni light buffer to 
						copy.
		 */
		ShadowMappedOmniLightBuffer(
			const ShadowMappedOmniLightBuffer& buffer) noexcept = default;

		/**
		 Constructs a shadow mapped omni light buffer by moving the given 
		 shadow mapped omni light buffer.

		 @param[in]		buffer
						A reference to the shadow mapped omni light buffer to 
						move.
		 */
		ShadowMappedOmniLightBuffer(
			ShadowMappedOmniLightBuffer&& buffer) noexcept = default;
		
		/**
		 Destructs this shadow mapped omni light buffer.
		 */
		~ShadowMappedOmniLightBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shadow mapped omni light buffer to this shadow mapped 
		 omni light buffer.

		 @param[in]		buffer
						A reference to the shadow mapped omni light buffer to 
						copy.
		 @return		A reference to the copy of the given shadow mapped omni 
						light buffer (i.e. this shadow mapped omni light 
						buffer).
		 */
		ShadowMappedOmniLightBuffer& operator=(
			const ShadowMappedOmniLightBuffer& buffer) = default;

		/**
		 Moves the given shadow mapped omni light buffer to this shadow mapped 
		 omni light buffer.

		 @param[in]		buffer
						A reference to the shadow mapped omni light buffer to 
						move.
		 @return		A reference to the moved shadow mapped omni light 
						buffer (i.e. this shadow mapped omni light buffer).
		 */
		ShadowMappedOmniLightBuffer& operator=(
			ShadowMappedOmniLightBuffer&& buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Light
		//---------------------------------------------------------------------

		/**
		 The omni light buffer of this shadow mapped omni light buffer.
		 */
		OmniLightBuffer m_light;

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-light matrix of 
		 this shadow mapped omni light buffer.
		 */
		XMMATRIX m_world_to_light;

		/**
		 The projection values of the light-to-projection transformation matrix
		 of this shadow mapped omni light buffer.
		 */
		F32x2 m_projection_values;
		
		/**
		 The padding of this shadow mapped omni light buffer. 
		 */
		U32 m_padding0[2];
	};

	static_assert(112 == sizeof(ShadowMappedOmniLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion

	//-------------------------------------------------------------------------
	// ShadowMappedSpotLightBuffer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A struct of shadow mapped spotlight buffers used by shaders.
	 */
	struct alignas(16) ShadowMappedSpotLightBuffer final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shadow mapped spotlight buffer.
		 */
		ShadowMappedSpotLightBuffer() noexcept
			: m_light(), 
			m_world_to_projection{} {}
		
		/**
		 Constructs a shadow mapped spotlight buffer from the given shadow 
		 mapped spotlight buffer.

		 @param[in]		buffer
						A reference to the shadow mapped spotlight buffer to 
						copy.
		 */
		ShadowMappedSpotLightBuffer(
			const ShadowMappedSpotLightBuffer& buffer) noexcept = default;

		/**
		 Constructs a shadow mapped spotlight buffer by moving the given shadow 
		 mapped spotlight buffer.

		 @param[in]		buffer
						A reference to the shadow mapped spotlight buffer to 
						move.
		 */
		ShadowMappedSpotLightBuffer(
			ShadowMappedSpotLightBuffer&& buffer) noexcept = default;
		
		/**
		 Destructs this shadow mapped spotlight buffer.
		 */
		~ShadowMappedSpotLightBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shadow mapped spotlight buffer to this shadow mapped 
		 spotlight buffer.

		 @param[in]		buffer
						A reference to the shadow mapped spotlight buffer to 
						copy.
		 @return		A reference to the copy of the given shadow mapped 
						spotlight buffer (i.e. this shadow mapped spotlight 
						buffer).
		 */
		ShadowMappedSpotLightBuffer& operator=(
			const ShadowMappedSpotLightBuffer& buffer) = default;

		/**
		 Moves the given shadow mapped spotlight buffer to this shadow mapped 
		 spotlight buffer.

		 @param[in]		buffer
						A reference to the shadow mapped spotlight buffer to 
						move.
		 @return		A reference to the moved shadow mapped spotlight buffer 
						(i.e. this shadow mapped spotlight buffer).
		 */
		ShadowMappedSpotLightBuffer& operator=(
			ShadowMappedSpotLightBuffer&& buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Light
		//---------------------------------------------------------------------

		/**
		 The spotlight buffer of this shadow mapped spotlight buffer.
		 */
		SpotLightBuffer m_light;

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) world-to-projection 
		 matrix of this shadow mapped spotlight buffer.
		 */
		XMMATRIX m_world_to_projection;
	};

	static_assert(112 == sizeof(ShadowMappedSpotLightBuffer), 
				  "CPU/GPU struct mismatch");

	#pragma endregion
}