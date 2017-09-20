#ifndef MAGE_HEADER_GLOBAL
#define MAGE_HEADER_GLOBAL

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#include "hlsl.hpp"
#include "math.hlsli"
#include "structures.hlsli"

//-----------------------------------------------------------------------------
// Samplers
//-----------------------------------------------------------------------------
SamplerState g_variable_sampler0 
	: register(REG_S(SLOT_SAMPLER_VARIABLE_0));
SamplerState g_variable_sampler1 
	: register(REG_S(SLOT_SAMPLER_VARIABLE_1));
SamplerState g_variable_sampler2 
	: register(REG_S(SLOT_SAMPLER_VARIABLE_2));
SamplerState g_variable_sampler3 
	: register(REG_S(SLOT_SAMPLER_VARIABLE_3));

SamplerState g_point_wrap_sampler 
	: register(REG_S(SLOT_SAMPLER_POINT_WRAP));
SamplerState g_point_clamp_sampler 
	: register(REG_S(SLOT_SAMPLER_POINT_CLAMP));
SamplerState g_point_mirror_sampler 
	: register(REG_S(SLOT_SAMPLER_POINT_MIRROR));
SamplerState g_linear_wrap_sampler 
	: register(REG_S(SLOT_SAMPLER_LINEAR_WRAP));
SamplerState g_linear_clamp_sampler 
	: register(REG_S(SLOT_SAMPLER_LINEAR_CLAMP));
SamplerState g_linear_mirror_sampler 
	: register(REG_S(SLOT_SAMPLER_LINEAR_MIRROR));
SamplerState g_anisotropic_wrap_sampler 
	: register(REG_S(SLOT_SAMPLER_ANISOTROPIC_WRAP));
SamplerState g_anisotropic_clamp_sampler 
	: register(REG_S(SLOT_SAMPLER_ANISOTROPIC_CLAMP));
SamplerState g_anisotropic_mirror_sampler 
	: register(REG_S(SLOT_SAMPLER_ANISOTROPIC_MIRROR));

SamplerComparisonState g_pcf_sampler 
	: register(REG_S(SLOT_SAMPLER_PCF));

#endif // MAGE_HEADER_GLOBAL