#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Clamps the given value to [0,1].

	 @param[in]		value
					The value.
	 @return		The clamped value.
	 */
	[[nodiscard]]
	constexpr F32 Saturate(F32 value) noexcept {
		return std::clamp(value, 0.0f, 1.0f);
	}

	//-------------------------------------------------------------------------
	// Angles
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Clamps the given angle (in degrees) to [-180, 180].

	 @param[in]		angle
					The angle (in degrees).
	 @return		The clamped angle (in degrees).
	 */
	[[nodiscard]]
	inline F32 ClampAngleDegrees(F32 angle) noexcept {
		return std::remainder(angle, 360.0f);
	}

	/**
	 Clamps the given angle (in radians) to [-pi, pi].

	 @param[in]		angle
					The angle (in radians).
	 @return		The clamped angle (in radians).
	 */
	[[nodiscard]]
	inline F32 ClampAngleRadians(F32 angle) noexcept {
		return std::remainder(angle, XM_2PI);
	}

	/**
	 Clamps the given angle (in degrees) between the given minimum and maximum
	 angle (in degrees).

	 @pre			@a min_angle lies in [-180, 180].
	 @pre			@a max_angle lies in [-180, 180].
	 @pre			@a min_angle is not greater than @a max_angle.
	 @param[in]		angle
					The angle (in degrees).
	 @param[in]		min_angle
					The minimum angle (in degrees).
	 @param[in]		max_angle
					The maximum angle (in degrees).
	 @return		The clamped angle between the given minimum and maximum 
					angle (in degrees).
	 */
	[[nodiscard]]
	inline F32 ClampAngleDegrees(F32 angle, F32 min_angle, F32 max_angle) noexcept {
		Assert(min_angle <= max_angle);
		Assert(-180.0f <= max_angle && max_angle <= 180.0f);
		Assert(-180.0f <= max_angle && max_angle <= 180.0f);

		return std::clamp(ClampAngleDegrees(angle), min_angle, max_angle);
	}

	/**
	 Clamps the given angle (in radians) between the given minimum and maximum
	 angle (in radians).

	 @pre			@a min_angle lies in [-pi, pi].
	 @pre			@a max_angle lies in [-pi, pi].
	 @pre			@a min_angle is not greater than @a max_angle.
	 @param[in]		angle
					The angle (in radians).
	 @param[in]		min_angle
					The minimum angle (in radians).
	 @param[in]		max_angle
					The maximum angle (in radians).
	 @return		The clamped angle between the given minimum and maximum 
					angle (in radians).
	 */
	[[nodiscard]]
	inline F32 ClampAngleRadians(F32 angle, F32 min_angle, F32 max_angle) noexcept {
		Assert(min_angle <= max_angle);
		Assert(-XM_PI <= max_angle && max_angle <= XM_PI);
		Assert(-XM_PI <= max_angle && max_angle <= XM_PI);
		
		return std::clamp(ClampAngleRadians(angle), min_angle, max_angle);
	}
	
	#pragma endregion

	//-------------------------------------------------------------------------
	// Normalized <> Absolute
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]
	inline F32 NormalizedToAbsolute(F32 p, F32 resolution) noexcept {
		return p * resolution;
	}

	[[nodiscard]]
	inline const F32x2 NormalizedToAbsolute(const F32x2& p,
											const F32x2& resolution) noexcept {
		return XMStore< F32x2 >(XMLoad(p) * XMLoad(resolution));

	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV
		NormalizedToAbsolute(FXMVECTOR p, FXMVECTOR resolution) noexcept {

		return p * resolution;
	}

	[[nodiscard]]
	inline F32 AbsoluteToNormalized(F32 p, F32 resolution) noexcept {
		return p / resolution;
	}

	[[nodiscard]]
	inline const F32x2 AbsoluteToNormalized(const F32x2& p,
											const F32x2& resolution) noexcept {
		return XMStore< F32x2 >(XMLoad(p) / XMLoad(resolution));
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV
		AbsoluteToNormalized(FXMVECTOR p, FXMVECTOR resolution) noexcept {

		return p / resolution;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// Packing
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Converts the given @c RECT (left, top, right, bottom) to a @c XMVECTOR 
	 (left, top, right, bottom).

	 @param[in]		rect
					A reference to the rectangle.
	 @return		A @c XMVECTOR  (left, top, right, bottom) representing the 
					given @c RECT (left, top, right, bottom).
	 */
	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV 
		XMVectorLeftTopRightBottom(const RECT& rect) noexcept {
		
		return XMLoad(rect);
	}

	/**
	 Converts the given @c RECT (left, top, right, bottom) to a @c XMVECTOR 
	 (left, top, width, height).

	 @param[in]		rect
					A reference to the rectangle.
	 @return		A @c XMVECTOR  (left, top, width, height) representing the 
					given @c RECT (left, top, right, bottom).
	 */
	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV 
		XMVectorLeftTopWidthHeight(const RECT& rect) noexcept {

		const auto v = XMVectorLeftTopRightBottom(rect);
		return v - XMVectorPermute< 0, 1, 4, 5 >(XMVectorZero(), v);

	}

	/**
	 Returns the projection values from the given projection matrix to construct 
	 the NDC z-coordinate from the view z-coordinate.

	 @param[in]		projection_matrix
					The projection matrix.
	 @return		The projection values from the given projection matrix to 
					construct the NDC z-coordinate from the view z-coordinate.
	 */
	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV
		GetNDCZConstructionValues(FXMMATRIX projection_matrix) noexcept {

		//        [ _  0  0  0 ]
		// p_view [ 0  _  0  0 ] = [_, _, p_view.z * X + Y, p_view.z] = p_proj
		//        [ 0  0  X  1 ]
		//        [ 0  0  Y  0 ]
		//
		// p_proj / p_proj.w     = [_, _, X + Y/p_view.z, 1] = p_ndc
		//
		// Construction of p_ndc.z from p_view and projection values
		// p_ndc.z = X + Y/p_view.z

		const auto x = XMVectorGetZ(projection_matrix.r[2]);
		const auto y = XMVectorGetZ(projection_matrix.r[3]);
		
		return { x, y, 0.0f, 0.0f };
	}

	#pragma endregion
}