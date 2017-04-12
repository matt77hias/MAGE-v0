#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename ValueT >
	inline ValueT Clamp(ValueT x, ValueT low = 0, ValueT high = 1) {
		return (x < high) ? ((x > low) ? x : low) : high;
	}

	inline float ClampAngleDegrees(float angle, float min, float max) {
		if (angle < -360.0f) {
			angle += 360.0f;
		}
		if (angle > 360.0f) {
			angle -= 360.0f;
		}
		return Clamp(angle, min, max);
	}

	inline float ClampAngleRadians(float angle, float min, float max) {
		if (angle < -XM_2PI) {
			angle += XM_2PI;
		}
		if (angle > XM_2PI) {
			angle -= XM_2PI;
		}
		return Clamp(angle, min, max);
	}
}