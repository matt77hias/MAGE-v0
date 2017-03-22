#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	// Forward declaration
	struct XYZSpectrum;

	struct RGBSpectrum final : public XMFLOAT3 {

	public:

		RGBSpectrum()
			: XMFLOAT3() {}
		RGBSpectrum(float r, float g, float b)
			: XMFLOAT3(r, g, b) {}
		RGBSpectrum(const RGBSpectrum &rgb)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(rgb)) {}
		RGBSpectrum(RGBSpectrum &&rgb)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(rgb)) {}
		RGBSpectrum(const XYZSpectrum &xyz);
		RGBSpectrum(XYZSpectrum &&xyz);
		explicit RGBSpectrum(const XMFLOAT3 &vector)
			: XMFLOAT3(vector) {}
		explicit RGBSpectrum(XMFLOAT3 &&vector)
			: XMFLOAT3(vector) {}

		~RGBSpectrum() = default;

		RGBSpectrum &operator=(const RGBSpectrum &rgb) {
			XMFLOAT3::operator=(rgb);
			return (*this);
		}
		RGBSpectrum &operator=(RGBSpectrum &&rgb) {
			XMFLOAT3::operator=(rgb);
			return (*this);
		}
	};

	struct XYZSpectrum final : public XMFLOAT3 {

	public:

		XYZSpectrum()
			: XMFLOAT3() {}
		XYZSpectrum(float x, float y, float z)
			: XMFLOAT3(x, y, z) {}
		XYZSpectrum(const XYZSpectrum &xyz)
			: XMFLOAT3(static_cast< const XMFLOAT3 & >(xyz)) {}
		XYZSpectrum(XYZSpectrum &&xyz)
			: XMFLOAT3(static_cast< XMFLOAT3 && >(xyz)) {}
		XYZSpectrum(const RGBSpectrum &rgb);
		XYZSpectrum(RGBSpectrum &&rgb);
		explicit XYZSpectrum(const XMFLOAT3 &vector)
			: XMFLOAT3(vector) {}
		explicit XYZSpectrum(XMFLOAT3 &&vector)
			: XMFLOAT3(vector) {}

		~XYZSpectrum() = default;

		XYZSpectrum &operator=(const XYZSpectrum &xyz) {
			XMFLOAT3::operator=(xyz);
			return (*this);
		}
		XYZSpectrum &operator=(XYZSpectrum &&xyz) {
			XMFLOAT3::operator=(xyz);
			return (*this);
		}
	};

	static_assert(sizeof(RGBSpectrum) == sizeof(XMFLOAT3), "RGBSpectrum/XMFLOAT3 mismatch");
	static_assert(sizeof(XYZSpectrum) == sizeof(XMFLOAT3), "XYZSpectrum/XMFLOAT3 mismatch");
}