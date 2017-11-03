#pragma once

namespace mage {

	enum struct AADescriptor {
		None     = 0,
		FXAA     = 1,
		MSAA_2x  = 2,
		MSAA_4x  = 4,
		MSAA_8x  = 8,
		MSAA_16x = 16,
		MSAA_32x = 32,
		SSAA_2x  = 34,
		SSAA_3x  = 35,
		SSAA_4x  = 36,
	};

	constexpr AADescriptor RetrieveAADescriptor(size_t i) {
		switch (i) {
		
		case static_cast< size_t >(AADescriptor::FXAA) :
			return AADescriptor::FXAA;
		case static_cast< size_t >(AADescriptor::MSAA_2x) :
			return AADescriptor::MSAA_2x;
		case static_cast< size_t >(AADescriptor::MSAA_4x) :
			return AADescriptor::MSAA_4x;
		case static_cast< size_t >(AADescriptor::MSAA_8x) :
			return AADescriptor::MSAA_8x;
		case static_cast< size_t >(AADescriptor::MSAA_16x) :
			return AADescriptor::MSAA_16x;
		case static_cast< size_t >(AADescriptor::MSAA_32x) :
			return AADescriptor::MSAA_32x;
		case static_cast< size_t >(AADescriptor::SSAA_2x) :
			return AADescriptor::SSAA_2x;
		case static_cast< size_t >(AADescriptor::SSAA_3x) :
			return AADescriptor::SSAA_3x;
		case static_cast< size_t >(AADescriptor::SSAA_4x) :
			return AADescriptor::SSAA_4x;
		default:
			return AADescriptor::None;
		}
	}
}