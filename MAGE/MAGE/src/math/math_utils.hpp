#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Clamps the given value between the given low and hight value.

	 @pre			@a low is not greater than @a high.
	 @tparam		ValueT
					The type of value.
	 @param[in]		value
					The value.
	 @param[in]		low
					The minimum value.
	 @param[in]		high
					The maximum value.
	 @return		The clamped value between the given
					minimum and maximum value.
	 */
	template< typename ValueT >
	inline ValueT Clamp(ValueT value, ValueT low = 0, ValueT high = 1) noexcept {
		Assert(low <= high);
		
		return (value < high) ? ((value > low) ? value : low) : high;
	}

	/**
	 Clamps the given angle (in degrees) to (-180, 180].

	 @param[in]		angle
					The angle (in degrees).
	 @return		The clamped angle (in degrees).
	 */
	inline float ClampAngleDegrees(float angle) noexcept {
		while (angle < -180.0f) {
			angle += 360.0f;
		}
		while (angle > 180.0f) {
			angle -= 360.0f;
		}
		return angle;
	}

	/**
	 Clamps the given angle (in radians) to [-pi, pi].

	 @param[in]		angle
					The angle (in radians).
	 @return		The clamped angle (in radians).
	 */
	inline float ClampAngleRadians(float angle) noexcept {
		while (angle < -XM_PI) {
			angle += XM_2PI;
		}
		while (angle > XM_PI) {
			angle -= XM_2PI;
		}
		return angle;
	}

	/**
	 Clamps the given angle (in degrees) between the given
	 minimum and maximum angle (in degrees).

	 @pre			@a min_angle lies in [-180, 180].
	 @pre			@a max_angle lies in [-180, 180].
	 @pre			@a min_angle is not greater than @a max_angle.
	 @param[in]		angle
					The angle (in degrees).
	 @param[in]		min_angle
					The minimum angle (in degrees).
	 @param[in]		max_angle
					The maximum angle (in degrees).
	 @return		The clamped angle between the given
					minimum and maximum angle (in degrees).
	 */
	inline float ClampAngleDegrees(float angle, float min_angle, float max_angle) noexcept {
		Assert(min_angle <= max_angle);
		Assert(-XM_PI <= max_angle && max_angle <= XM_PI);
		Assert(-XM_PI <= max_angle && max_angle <= XM_PI);

		return Clamp(ClampAngleDegrees(angle), min_angle, max_angle);
	}

	/**
	 Clamps the given angle (in radians) between the given
	 minimum and maximum angle (in radians).

	 @pre			@a min_angle lies in [-pi, pi].
	 @pre			@a max_angle lies in [-pi, pi].
	 @pre			@a min_angle is not greater than @a max_angle.
	 @param[in]		angle
					The angle (in radians).
	 @param[in]		min_angle
					The minimum angle (in radians).
	 @param[in]		max_angle
					The maximum angle (in radians).
	 @return		The clamped angle between the given
					minimum and maximum angle (in radians).
	 */
	inline float ClampAngleRadians(float angle, float min_angle, float max_angle) noexcept {
		Assert(min_angle <= max_angle);
		Assert(-XM_PI <= max_angle && max_angle <= XM_PI);
		Assert(-XM_PI <= max_angle && max_angle <= XM_PI);
		
		return Clamp(ClampAngleRadians(angle), min_angle, max_angle);
	}
}