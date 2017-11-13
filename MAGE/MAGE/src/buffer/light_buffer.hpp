#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\allocation.hpp"
#include "material\spectrum.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LightBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of light buffers used by shaders.
	 */
	__declspec(align(16)) struct LightBuffer final 
		: public AlignedData< LightBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a light buffer.
		 */
		LightBuffer()
			: m_La(), m_padding0(0),
			m_fog_color(), m_fog_density(0.0f),
			m_nb_directional_lights(0), m_nb_omni_lights(0), 
			m_nb_spot_lights(0), m_padding1(0),
			m_nb_sm_directional_lights(0), m_nb_sm_omni_lights(0), 
			m_nb_sm_spot_lights(0), m_padding2(0) {}
		
		/**
		 Constructs a light buffer from the given light buffer.

		 @param[in]		buffer
						A reference to the light buffer to copy.
		 */
		LightBuffer(const LightBuffer &buffer) = default;
		
		/**
		 Constructs a light buffer by moving the given light buffer.

		 @param[in]		buffer
						A reference to the light buffer to move.
		 */
		LightBuffer(LightBuffer &&buffer) = default;
		
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
		LightBuffer &operator=(const LightBuffer &buffer) = default;
		
		/**
		 Moves the given light buffer to this light buffer.

		 @param[in]		buffer
						A reference to the light buffer to move.
		 @return		A reference to the moved light buffer (i.e. this light 
						buffer).
		 */
		LightBuffer &operator=(LightBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Lights
		//---------------------------------------------------------------------

		/**
		 The ambient radiance in watts per square meter per steradians of this 
		 light buffer.
		 */
		RGB m_La;

		/**
		 The padding of this light buffer.
		 */
		F32 m_padding0;
	
		/**
		 The linear color of the fog of this light buffer.
		 */
		RGB m_fog_color;
		
		/**
		 The density of the fog of this light buffer.
		 */
		F32 m_fog_density;

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
		U32 m_padding1;

		/**
		 The number of directional lights with shadow mapping of this light 
		 buffer.
		 */
		U32 m_nb_sm_directional_lights;

		/**
		 The number of omni lights with shadow mapping of this light buffer.
		 */
		U32 m_nb_sm_omni_lights;

		/**
		 The number of spotlights with shadow mapping of this light buffer.
		 */
		U32 m_nb_sm_spot_lights;

		/**
		 The padding of this light buffer. 
		 */
		U32 m_padding2;
	};

	static_assert(sizeof(LightBuffer) == 64, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// DirectionalLightBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of directional light buffers used by shaders.
	 */
	__declspec(align(16)) struct DirectionalLightBuffer final 
		: public AlignedData< DirectionalLightBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an directional light buffer.
		 */
		DirectionalLightBuffer()
			: m_L(), m_padding0(0),
			m_neg_d(), m_padding1(0) {}
		
		/**
		 Constructs an directional light buffer from the given directional 
		 light buffer.

		 @param[in]		buffer
						A reference to the directional light buffer to copy.
		 */
		DirectionalLightBuffer(const DirectionalLightBuffer &buffer) = default;

		/**
		 Constructs an directional light buffer by moving the given directional 
		 light buffer.

		 @param[in]		buffer
						A reference to the directional light buffer to move.
		 */
		DirectionalLightBuffer(DirectionalLightBuffer &&buffer) = default;
		
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
		DirectionalLightBuffer &operator=(
			const DirectionalLightBuffer &buffer) = default;

		/**
		 Moves the given directional light buffer to this directional light 
		 buffer.

		 @param[in]		buffer
						A reference to the directional light buffer to move.
		 @return		A reference to the moved directional light buffer (i.e. 
						this directional light buffer).
		 */
		DirectionalLightBuffer &operator=(
			DirectionalLightBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The radiance in watts per square meter per steradians of the 
		 directional light of this directional light buffer.
		 */
		RGB m_L;

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding0;

		/**
		 The (normalized) negated direction of the directional light in camera 
		 view space of this directional light buffer.
		 */
		Direction3 m_neg_d;

		/**
		 The padding of this directional light buffer.
		 */
		U32 m_padding1;
	};

	static_assert(sizeof(DirectionalLightBuffer) == 32, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// OmniLightBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of omni light buffers used by shaders.
	 */
	__declspec(align(16)) struct OmniLightBuffer final 
		: public AlignedData< OmniLightBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an omni light buffer.
		 */
		OmniLightBuffer()
			: m_p(), m_inv_sqr_range(0.0f),
			m_I(), m_padding0(0) {}
		
		/**
		 Constructs an omni light buffer from the given omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to copy.
		 */
		OmniLightBuffer(const OmniLightBuffer &buffer) = default;

		/**
		 Constructs an omni light buffer by moving the given omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to move.
		 */
		OmniLightBuffer(OmniLightBuffer &&buffer) = default;
		
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
		OmniLightBuffer &operator=(const OmniLightBuffer &buffer) = default;

		/**
		 Moves the given omni light buffer to this omni light buffer.

		 @param[in]		buffer
						A reference to the omni light buffer to move.
		 @return		A reference to the moved omni light buffer (i.e. this 
						omni light buffer).
		 */
		OmniLightBuffer &operator=(OmniLightBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the omni light in camera view space of this omni light 
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

	static_assert(sizeof(OmniLightBuffer) == 32, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// SpotLightBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of spotlight buffers used by shaders.
	 */
	__declspec(align(16)) struct SpotLightBuffer final 
		: public AlignedData< SpotLightBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a spotlight buffer.
		 */
		SpotLightBuffer()
			: m_p(), m_inv_sqr_range(0.0f),
			m_I(), m_cos_umbra(0.0f),
			m_neg_d(), m_cos_inv_range(0.0f) {}
		
		/**
		 Constructs a spotlight buffer from the given spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to copy.
		 */
		SpotLightBuffer(const SpotLightBuffer &buffer) = default;

		/**
		 Constructs a spotlight buffer by moving the given spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to move.
		 */
		SpotLightBuffer(SpotLightBuffer &&buffer) = default;
		
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
		SpotLightBuffer &operator=(const SpotLightBuffer &buffer) = default;

		/**
		 Moves the given spotlight buffer to this spotlight buffer.

		 @param[in]		buffer
						A reference to the spotlight buffer to move.
		 @return		A reference to the moved spotlight buffer (i.e. this 
						spotlight buffer).
		 */
		SpotLightBuffer &operator=(SpotLightBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The position of the spotlight in camera view space of this spotlight 
		 buffer.
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
		 The (normalized) negated direction of the spotlight in camera view 
		 space of this spotlight buffer.
		 */
		Direction3 m_neg_d;

		/**
		 The cosine inverse range of the spotlight of this spotlight buffer.
		 */
		F32 m_cos_inv_range;
	};

	static_assert(sizeof(SpotLightBuffer) == 48, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// DirectionalLightWithShadowMappingBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of directional light with shadow mapping buffers used by shaders.
	 */
	__declspec(align(16)) struct DirectionalLightWithShadowMappingBuffer final 
		: public AlignedData< DirectionalLightWithShadowMappingBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an directional light with shadow mapping buffer.
		 */
		DirectionalLightWithShadowMappingBuffer()
			: m_light(), m_cview_to_lprojection() {}
		
		/**
		 Constructs an directional light with shadow mapping buffer from the 
		 given directional light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the directional light with shadow 
						mapping buffer to copy.
		 */
		DirectionalLightWithShadowMappingBuffer(
			const DirectionalLightWithShadowMappingBuffer &buffer) = default;

		/**
		 Constructs an directional light with shadow mapping buffer by moving 
		 the given directional light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the directional light with shadow 
						mapping buffer to move.
		 */
		DirectionalLightWithShadowMappingBuffer(
			DirectionalLightWithShadowMappingBuffer &&buffer) = default;
		
		/**
		 Destructs this directional light with shadow mapping buffer.
		 */
		~DirectionalLightWithShadowMappingBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given directional light with shadow mapping buffer to this 
		 directional light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the directional light with shadow 
						mapping buffer to copy.
		 @return		A reference to the copy of the given directional light 
						with shadow mapping buffer (i.e. this directional light 
						with shadow mapping buffer).
		 */
		DirectionalLightWithShadowMappingBuffer &operator=(
			const DirectionalLightWithShadowMappingBuffer &buffer) = default;

		/**
		 Moves the given directional light with shadow mapping buffer to this 
		 directional light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the directional light with shadow 
						mapping buffer to move.
		 @return		A reference to the moved directional light with shadow 
						mapping buffer (i.e. this directional light with shadow 
						mapping buffer).
		 */
		DirectionalLightWithShadowMappingBuffer &operator=(
			DirectionalLightWithShadowMappingBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Light
		//---------------------------------------------------------------------

		/**
		 The directional light buffer of this directional light buffer with 
		 shadow mapping.
		 */
		DirectionalLightBuffer m_light;

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) 
		 camera-view-to-light-projection matrix of this directional light 
		 buffer with shadow mapping for use in HLSL.
		 */
		XMMATRIX m_cview_to_lprojection;
	};

	static_assert(sizeof(DirectionalLightWithShadowMappingBuffer) == 96, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// OmniLightWithShadowMappingBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of omni light with shadow mapping buffers used by shaders.
	 */
	__declspec(align(16)) struct OmniLightWithShadowMappingBuffer final 
		: public AlignedData< OmniLightWithShadowMappingBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an omni light with shadow mapping buffer.
		 */
		OmniLightWithShadowMappingBuffer()
			: m_light(), m_cview_to_lview(),
			m_projection_values(), m_padding0() {}
		
		/**
		 Constructs an omni light with shadow mapping buffer from the given 
		 omni light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the omni light with shadow mapping 
						buffer to copy.
		 */
		OmniLightWithShadowMappingBuffer(
			const OmniLightWithShadowMappingBuffer &buffer) = default;

		/**
		 Constructs an omni light with shadow mapping buffer by moving the given 
		 omni light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the omni light with shadow mapping 
						buffer to move.
		 */
		OmniLightWithShadowMappingBuffer(
			OmniLightWithShadowMappingBuffer &&buffer) = default;
		
		/**
		 Destructs this omni light with shadow mapping buffer.
		 */
		~OmniLightWithShadowMappingBuffer() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given omni light with shadow mapping buffer to this omni 
		 light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the omni light 
						with shadow mapping buffer to copy.
		 @return		A reference to the copy of the given omni light with 
						shadow mapping buffer (i.e. this omni light with shadow 
						mapping buffer).
		 */
		OmniLightWithShadowMappingBuffer &operator=(
			const OmniLightWithShadowMappingBuffer &buffer) = default;

		/**
		 Moves the given omni light with shadow mapping buffer to this omni 
		 light with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the omni light 
						with shadow mapping buffer to move.
		 @return		A reference to the moved omni light with shadow 
						mapping buffer (i.e. this omni light with shadow 
						mapping buffer).
		 */
		OmniLightWithShadowMappingBuffer &operator=(
			OmniLightWithShadowMappingBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Light
		//---------------------------------------------------------------------

		/**
		 The omni light buffer of this omni light buffer with shadow mapping.
		 */
		OmniLightBuffer m_light;

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) camera-view-to-light-view 
		 matrix of this omni light buffer with shadow mapping for use in HLSL.
		 */
		XMMATRIX m_cview_to_lview;

		/**
		 The projection values of the view-to-projection transformation matrix
		 of this omni light buffer with shadow mapping.
		 */
		XMFLOAT2 m_projection_values;
		
		/**
		 The padding of this omni light buffer with shadow mapping. 
		 */
		U32 m_padding0[2];
	};

	static_assert(sizeof(OmniLightWithShadowMappingBuffer) == 112, 
		"CPU/GPU struct mismatch");

	//-------------------------------------------------------------------------
	// SpotLightWithShadowMappingBuffer
	//-------------------------------------------------------------------------

	/**
	 A struct of spotlight with shadow mapping buffers used by shaders.
	 */
	__declspec(align(16)) struct SpotLightWithShadowMappingBuffer final 
		: public AlignedData< SpotLightWithShadowMappingBuffer > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a spotlight with shadow mapping buffer.
		 */
		SpotLightWithShadowMappingBuffer()
			: m_light(), m_cview_to_lprojection() {}
		
		/**
		 Constructs a spotlight with shadow mapping buffer from the given 
		 spotlight with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the spotlight with shadow mapping buffer 
						to copy.
		 */
		SpotLightWithShadowMappingBuffer(
			const SpotLightWithShadowMappingBuffer &buffer) = default;

		/**
		 Constructs a spotlight with shadow mapping buffer by moving the given 
		 spotlight with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the spotlight with shadow mapping buffer 
						to move.
		 */
		SpotLightWithShadowMappingBuffer(
			SpotLightWithShadowMappingBuffer &&buffer) = default;
		
		/**
		 Destructs this spotlight with shadow mapping buffer.
		 */
		~SpotLightWithShadowMappingBuffer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given spotlight with shadow mapping buffer to this 
		 spotlight with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the spotlight 
						with shadow mapping buffer to copy.
		 @return		A reference to the copy of the given spotlight with 
						shadow mapping buffer (i.e. this spotlight with shadow 
						mapping buffer).
		 */
		SpotLightWithShadowMappingBuffer &operator=(
			const SpotLightWithShadowMappingBuffer &buffer) = default;

		/**
		 Moves the given spotlight with shadow mapping buffer 
		 to this spotlight with shadow mapping buffer.

		 @param[in]		buffer
						A reference to the spotlight 
						with shadow mapping buffer to move.
		 @return		A reference to the moved spotlight with shadow mapping 
						buffer (i.e. this spotlight with shadow mapping 
						buffer).
		 */
		SpotLightWithShadowMappingBuffer &operator=(
			SpotLightWithShadowMappingBuffer &&buffer) = default;

		//---------------------------------------------------------------------
		// Member Variables: Light
		//---------------------------------------------------------------------

		/**
		 The spotlight buffer of this spotlight buffer with shadow mapping.
		 */
		SpotLightBuffer m_light;

		//---------------------------------------------------------------------
		// Member Variables: Transform
		//---------------------------------------------------------------------

		// HLSL expects column-major packed matrices by default.
		// DirectXMath expects row-major packed matrices.

		/**
		 The (column-major packed, row-major matrix) 
		 camera-view-to-light-projection matrix of this spotlight buffer with 
		 shadow mapping for use in HLSL.
		 */
		XMMATRIX m_cview_to_lprojection;
	};

	static_assert(sizeof(SpotLightWithShadowMappingBuffer) == 112, 
		"CPU/GPU struct mismatch");
}