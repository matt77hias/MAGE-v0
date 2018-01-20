#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\scalar_types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	enum class AADescriptor : U8 {
		None = 0,
		FXAA,
		MSAA_2x,
		MSAA_4x,
		MSAA_8x,
		SSAA_2x,
		SSAA_3x,
		SSAA_4x,
	};

	[[nodiscard]] constexpr AADescriptor 
		RetrieveAADescriptor(size_t desc) noexcept {

		switch (desc) {
		
		case static_cast< size_t >(AADescriptor::FXAA):
			return AADescriptor::FXAA;
		case static_cast< size_t >(AADescriptor::MSAA_2x):
			return AADescriptor::MSAA_2x;
		case static_cast< size_t >(AADescriptor::MSAA_4x):
			return AADescriptor::MSAA_4x;
		case static_cast< size_t >(AADescriptor::MSAA_8x):
			return AADescriptor::MSAA_8x;
		case static_cast< size_t >(AADescriptor::SSAA_2x):
			return AADescriptor::SSAA_2x;
		case static_cast< size_t >(AADescriptor::SSAA_3x):
			return AADescriptor::SSAA_3x;
		case static_cast< size_t >(AADescriptor::SSAA_4x):
			return AADescriptor::SSAA_4x;
		default:
			return AADescriptor::None;
		}
	}

	[[nodiscard]] constexpr U32 
		GetResolutionMultiplier(AADescriptor desc) noexcept {

		switch (desc) {

		case AADescriptor::SSAA_2x:
			return 2u;
		case AADescriptor::SSAA_3x:
			return 3u;
		case AADescriptor::SSAA_4x:
			return 4u;
		default:
			return 1u;

		}
	}
}