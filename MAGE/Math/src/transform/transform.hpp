#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Elementary Matrices and Quaternions
	//-------------------------------------------------------------------------
	#pragma region

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetTranslationMatrix(FXMVECTOR translation) noexcept {

		return XMMatrixTranslationFromVector(translation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseTranslationMatrix(FXMVECTOR translation) noexcept {

		return GetTranslationMatrix(-translation);
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV
		GetRollPitchYawQuaternion(FXMVECTOR rotation) noexcept {

		// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
		return XMQuaternionRotationRollPitchYawFromVector(rotation);
	}

	[[nodiscard]]
	inline const XMVECTOR XM_CALLCONV
		GetInverseRollPitchYawQuaternion(FXMVECTOR rotation) noexcept {

		// Ry (Yaw) . Rx (Pitch) . Rz (Roll)
		return XMQuaternionInverse(GetRollPitchYawQuaternion(rotation));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetRollPitchYawMatrix(FXMVECTOR rotation) noexcept {

		return XMMatrixRotationRollPitchYawFromVector(rotation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseRollPitchYawMatrix(FXMVECTOR rotation) noexcept {

		return XMMatrixTranspose(GetRollPitchYawMatrix(rotation));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetScalingMatrix(FXMVECTOR scale) noexcept {

		return XMMatrixScalingFromVector(scale);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetScalingMatrix(F32 scale) noexcept {

		return GetScalingMatrix(XMLoad(F32x3(scale)));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseScalingMatrix(FXMVECTOR scale) noexcept {

		return GetScalingMatrix(XMVectorReciprocal(scale));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseScalingMatrix(F32 scale) noexcept {

		return GetInverseScalingMatrix(XMLoad(F32x3(scale)));
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(FXMVECTOR scale,
									  FXMVECTOR rotation,
									  FXMVECTOR translation) noexcept {

		// Scale . Rotation . Translation
		//
		//   [ Sx 0  0  0 ] [ R00 R01 R02 0 ] [ 1  0  0  0 ]
		// = [ 0  Sy 0  0 ] [ R10 R11 R12 0 ] [ 0  1  0  0 ]
		//   [ 0  0  Sz 0 ] [ R20 R21 R22 0 ] [ 0  0  1  0 ]
		//   [ 0  0  0  1 ] [ 0   0   0   1 ] [ Tx Ty Tz 1 ]
		//
		//   [ Sx.R00 Sx.R01 Sx.R02 0 ]   [ Sx*R0, ]
		// = [ Sy.R10 Sy.R11 Sy.R12 0 ] = [ Sy*R1, ]
		//   [ Sz.R20 Sz.R21 Sz.R22 0 ]   [ Sz*R2, ]
		//   [ Tx     Ty     Tz     1 ]   [ T    1 ]

		auto transformation = GetRollPitchYawMatrix(rotation);
		transformation.r[0u] *= XMVectorGetX(scale);
		transformation.r[1u] *= XMVectorGetY(scale);
		transformation.r[2u] *= XMVectorGetZ(scale);
		transformation.r[3u] = XMVectorSetW(translation, 1.0f);
		return transformation;
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(F32       scale,
									  FXMVECTOR rotation,
									  FXMVECTOR translation) noexcept {
		
		return GetAffineTransformationMatrix(XMLoad(F32x3(scale)),
											 rotation,
											 translation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseAffineTransformationMatrix(FXMVECTOR scale,
											 FXMVECTOR rotation,
											 FXMVECTOR translation) noexcept {

		// Translation . Rotation . Scale
		//
		//   [ 1   0   0   0 ] [ R00' R01' R02' 0 ] [ Sx' 0   0   0 ]
		// = [ 0   1   0   0 ] [ R10' R11' R12' 0 ] [ 0   Sy' 0   0 ]
		//   [ 0   0   1   0 ] [ R20' R21' R22' 0 ] [ 0   0   Sz' 0 ]
		//   [ Tx' Ty' Tz' 1 ] [ 0    0    0    1 ] [ 0   0   0   1 ]
		//
		//   [   R00'.Sx    R01'.Sy    R02'.Sz 0 ]   [ R0,'*S   ]
		// = [   R10'.Sx    R11'.Sy    R12'.Sz 0 ] = [ R1,'*S   ]
		//   [   R20'.Sx    R21'.Sy    R22'.Sz 0 ]   [ R2,'*S   ]
		//   [ R,0'.T.Sx  R,1'.T.Sy  R,2'.T.Sz 1 ]   [ R [T*S 1]]

		auto transformation = GetInverseRollPitchYawMatrix(rotation);
		const auto t = XMVector3TransformCoord(-translation, transformation);
		const auto s = XMVectorSetW(XMVectorReciprocal(scale), 1.0f);
		transformation.r[0u] *= s;
		transformation.r[1u] *= s;
		transformation.r[2u] *= s;
		transformation.r[3u] = s * t;
		return transformation;
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetInverseAffineTransformationMatrix(F32       scale,
											 FXMVECTOR rotation,
											 FXMVECTOR translation) noexcept {

		return GetInverseAffineTransformationMatrix(XMLoad(F32x3(scale)),
													rotation,
													translation);
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(FXMVECTOR scale,
									  F32       rotation,
									  FXMVECTOR translation) noexcept {

		// Scale . Rotation . Translation
		//
		//   [ Sx 0  0  0 ] [ R00 R01 0 0 ] [ 1  0  0  0 ]
		// = [ 0  Sy 0  0 ] [ R10 R11 0 0 ] [ 0  1  0  0 ]
		//   [ 0  0  _  0 ] [ 0   0   1 0 ] [ 0  0  1  0 ]
		//   [ 0  0  0  1 ] [ 0   0   0 1 ] [ Tx Ty _  1 ]
		//
		//   [ Sx.R00 Sx.R01 0 0 ]   [ Sx*R0,  ]
		// = [ Sy.R10 Sy.R11 0 0 ] = [ Sy*R1,  ]
		//   [ 0      0      _ 0 ]   [ 0 0 _ 0 ]
		//   [ Tx     Ty     0 1 ]   [ T   _ 1 ]

		auto transformation  = XMMatrixRotationZ(rotation);
		transformation.r[0u] *= XMVectorGetX(scale);
		transformation.r[1u] *= XMVectorGetY(scale);
		transformation.r[3u]  = XMVectorSetW(translation, 1.0f);
		return transformation;
	}

	[[nodiscard]]
	inline const XMMATRIX XM_CALLCONV
		GetAffineTransformationMatrix(FXMVECTOR offset,
									  FXMVECTOR scale,
									  F32       rotation,
									  FXMVECTOR translation) noexcept {

		// Inverse Offset Translation . Scale . Rotation . Translation
		auto transformation  = GetAffineTransformationMatrix(scale,
															 rotation,
															 translation);
		transformation.r[3u] = XMVector3TransformCoord(-offset, transformation);
		return transformation;
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// S1ETTransform3D
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of 3D transforms supporting uniform scaling, rotation using Euler
	 angles, and translation.
	 */
	class S1ETTransform3D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit S1ETTransform3D(F32x3 translation = { 0.0f, 0.0f, 0.0f },
			                     F32x3 rotation    = { 0.0f, 0.0f, 0.0f },
			                     F32   scale       =   1.0f) noexcept
			: m_translation(std::move(translation)),
			m_padding{},
			m_rotation(),
			m_scale(scale) {

			SetRotation(rotation);
		}

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit S1ETTransform3D(FXMVECTOR translation,
			                     FXMVECTOR rotation,
								 F32       scale) noexcept
			: S1ETTransform3D(XMStore< F32x3 >(translation),
							  XMStore< F32x3 >(rotation),
							  scale) {}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 */
		S1ETTransform3D(const S1ETTransform3D& transform) noexcept = default;

		/**
		 Constructs a transform by moving the given transform.

		 @param[in]		transform
						A reference to the transform to move.
		 */
		S1ETTransform3D(S1ETTransform3D&& transform) noexcept = default;

		/**
		 Destructs this transform.
		 */
		~S1ETTransform3D() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 @return		A reference to the copy of the given transform (i.e.
						this transform).
		 */
		S1ETTransform3D& operator=(
			const S1ETTransform3D& transform) noexcept = default;

		/**
		 Moves the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to move.
		 @return		A reference to the moved transform (i.e. this
						transform).
		 */
		S1ETTransform3D& operator=(
			S1ETTransform3D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this transform to the
		 given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this transform to the
		 given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the z-value of the translation component of this transform to the
		 given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(F32 z) noexcept {
			m_translation[2u] = z;
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y, F32 z) noexcept {
			SetTranslation(F32x3(x, y, z));
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x3 translation) noexcept {
			m_translation = std::move(translation);
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x3 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given z-value to the translation component of this transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(F32 z) noexcept {
			SetTranslationZ(GetTranslationZ() + z);
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y, F32 z) noexcept {
			AddTranslation(F32x3(x, y, z));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x3& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this transform.

		 @return		The x-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this transform.

		 @return		The y-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the z-value of the translation component of this transform.

		 @return		The z-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationZ() const noexcept {
			return m_translation[2u];
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		/**
		 Returns the object-to-parent translation matrix of this transform.

		 @return		The object-to-parent translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentTranslationMatrix() const noexcept {
			return GetTranslationMatrix(GetTranslation());
		}

		/**
		 Returns the parent-to-object translation matrix of this transform.

		 @return		The parent-to-object translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectTranslationMatrix() const noexcept {
			return GetInverseTranslationMatrix(GetTranslation());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the rotation component of this transform to the
		 given value.

		 @param[in]		x
						The x-value of the rotation component.
		 */
		void SetRotationX(F32 x) noexcept {
			m_rotation[0u] = WrapAngleRadians(x);
		}

		/**
		 Sets the y-value of the rotation component of this transform to the
		 given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(F32 y) noexcept {
			m_rotation[1u] = WrapAngleRadians(y);
		}

		/**
		 Sets the z-value of the rotation component of this transform to the
		 given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(F32 z) noexcept {
			m_rotation[2u] = WrapAngleRadians(z);
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		x
						The x-value of the rotation component.
		 @param[in]		y
						 The y-value of the rotation component.
		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotation(F32 x, F32 y, F32 z) noexcept {
			SetRotation(F32x3(x, y, z));
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const F32x3& rotation) noexcept {
			SetRotation(XMLoad(rotation));
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						The rotation component.
		 */
		void XM_CALLCONV SetRotation(FXMVECTOR rotation) noexcept {
			m_rotation = XMStore< F32x3 >(WrapAngleRadians(rotation));
		}

		/**
		 Sets the rotation component of this transform to a rotation of the
		 given angle around the given direction.

		 @param[in]		direction
						The unit-length direction.
		 @param[in]		angle
						The angle.
		 */
		void XM_CALLCONV SetRotationAroundDirection(FXMVECTOR direction,
			                                        F32 angle) noexcept {

			const auto R = XMMatrixRotationNormal(direction, angle);

			// cos instead of sin in case the angles are not in [-1,1]
			const auto y = -std::asin(XMVectorGetY(R.r[2u]));
			const auto a = 1.0f / std::cos(m_rotation[1u]);
			const auto z = std::acos(a * XMVectorGetY(R.r[1u]));
			const auto x = std::acos(a * XMVectorGetZ(R.r[2u]));
			SetRotation(x, y, z);
		}

		/**
		 Adds the given x-value to the rotation component of this transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(F32 x) noexcept {
			SetRotationX(GetRotationX() + x);
		}

		/**
		 Adds the given x-value to the rotation component of this transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotationX(F32 x, F32 min_angle, F32 max_angle) noexcept {
			m_rotation[0u] = ClampAngleRadians(GetRotationX() + x,
											   min_angle, max_angle);
		}

		/**
		 Adds the given y-value to the rotation component of this transform.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(F32 y) noexcept {
			SetRotationY(GetRotationY() + y);
		}

		/**
		 Adds the given y-value to the rotation component of this transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotationY(F32 y, F32 min_angle, F32 max_angle) noexcept {
			m_rotation[1u] = ClampAngleRadians(GetRotationY() + y,
											   min_angle, max_angle);
		}

		/**
		 Adds the given z-value to the rotation component of this transform.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(F32 z) noexcept {
			SetRotationZ(GetRotationZ() + z);
		}

		/**
		 Adds the given z-value to the rotation component of this transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		z
						The z-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotationZ(F32 z, F32 min_angle, F32 max_angle) noexcept {
			m_rotation[2u] = ClampAngleRadians(GetRotationZ() + z,
											   min_angle, max_angle);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotation(F32 x, F32 y, F32 z) noexcept {
			AddRotation(F32x3(x, y, z));
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotation(F32 x, F32 y, F32 z, F32 min_angle, F32 max_angle) noexcept {
			AddRotation(F32x3(x, y, z), min_angle, max_angle);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const F32x3& rotation) noexcept {
			AddRotation(XMLoad(rotation));
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		rotation
						A reference to the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotation(const F32x3& rotation, F32 min_angle, F32 max_angle) noexcept {
			AddRotation(XMLoad(rotation),
						XMVectorReplicate(min_angle),
						XMVectorReplicate(max_angle));
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void XM_CALLCONV AddRotation(FXMVECTOR rotation) noexcept {
			SetRotation(GetRotation() + rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @pre			@a min_angles lie in [-pi, pi].
		 @pre			@a max_angles lie in [-pi, pi].
		 @pre			@a min_angles is not greater than @a max_angles.
		 @param[in]		rotation
						The rotation component to add.
		 @param[in]		min_angles
						The minimum angles (in radians).
		 @param[in]		max_angles
						The maximum angles (in radians).
		 */
		void XM_CALLCONV AddRotation(FXMVECTOR rotation,
									 FXMVECTOR min_angles,
									 FXMVECTOR max_angles) noexcept {

			m_rotation = XMStore< F32x3 >(
				ClampAngleRadians(GetRotation() + rotation,
								  min_angles, max_angles));
		}

		/**
		 Returns the x-value of the rotation component of this transform.

		 @return		The x-value of the rotation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationX() const noexcept {
			return m_rotation[0u];
		}

		/**
		 Returns the y-value of the rotation component of this transform.

		 @return		The y-value of the rotation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationY() const noexcept {
			return m_rotation[1u];
		}

		/**
		 Returns the z-value of the rotation component of this transform.

		 @return		The z-value of the rotation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationZ() const noexcept {
			return m_rotation[2u];
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetRotationView() const noexcept {
			return m_rotation;
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotation() const noexcept {
			return XMLoad(m_rotation);
		}

		/**
		 Returns the object-to-parent rotation quaternion of this transform.

		 @return		The object-to-parent rotation quaternion of this
						transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectToParentRotationQuaternion() const noexcept {
			// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
			return GetRollPitchYawQuaternion(GetRotation());
		}

		/**
		 Returns the parent-to-object rotation quaternion of this transform.

		 @return		The parent-to-object rotation quaternion of this
						transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentToObjectRotationQuaternion() const noexcept {
			return GetInverseRollPitchYawQuaternion(GetRotation());
		}

		/**
		 Returns the object-to-parent rotation matrix of this transform.

		 @return		The object-to-parent rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentRotationMatrix() const noexcept {
			// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
			return GetRollPitchYawMatrix(GetRotation());
		}

		/**
		 Returns the parent-to-object rotation matrix of this transform.

		 @return		The parent-to-object rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectRotationMatrix() const noexcept {
			return GetInverseRollPitchYawMatrix(GetRotation());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32 scale) noexcept {
			m_scale = scale;
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void AddScale(F32 scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		[[nodiscard]]
		const F32 GetScale() const noexcept {
			return m_scale;
		}

		/**
		 Returns the object-to-parent scale matrix of this transform.

		 @return		The scale object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentScaleMatrix() const noexcept {
			return GetScalingMatrix(GetScale());
		}

		/**
		 Returns the parent-to-object scale matrix of this transform.

		 @return		The parent-to-object scale matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectScaleMatrix() const noexcept {
			return GetInverseScalingMatrix(GetScale());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in object space coordinates.

		 @return		The position of the local origin of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectOrigin() const noexcept {
			return { 0.0f, 0.0f, 0.0f, 1.0f };
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisX() const noexcept {
			return { 1.0f, 0.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisY() const noexcept {
			return { 0.0f, 1.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisZ() const noexcept {
			return { 0.0f, 0.0f, 1.0f, 0.0f };
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in parent space coordinates.

		 @return		The position of the local origin of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentOrigin() const noexcept {
			return GetObjectToParentMatrix().r[3u];
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisX() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[0u]);
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisY() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[1u]);
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisZ() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[2u]);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the object-to-parent matrix of this transform.

		 @return		The object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentMatrix() const noexcept {
			// Scale . Rotation . Translation
			return GetAffineTransformationMatrix(GetScale(),
												 GetRotation(),
												 GetTranslation());
		}

		/**
		 Returns the parent-to-object matrix of this transform.

		 @return		The parent-to-object matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectMatrix() const noexcept {
			// Translation . Rotation . Scale
			return GetInverseAffineTransformationMatrix(GetScale(),
														GetRotation(),
														GetTranslation());
		}

		/**
		 Transforms the given vector expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		vector
						The vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParent(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given point expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		point
						The point expressed in object space coordinates.
		 @return		The transformed point expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given direction expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		direction
						The direction expressed in object space coordinates.
		 @return		The transformed direction expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		vector
						The vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObject(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given point expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		point
						The point expressed in parent space coordinates.
		 @return		The transformed point expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given direction expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		direction
						The direction expressed in parent space coordinates.
		 @return		The transformed direction expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetParentToObjectMatrix());
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component of this transform.
		 */
		F32x3 m_translation;

		/**
		 The padding of this transform.
		 */
		F32 m_padding;

		/**
		 The rotation component (Euler angles in radians) of this transform.
		 */
		F32x3 m_rotation;

		/**
		 The scale component of this transform.
		 */
		F32 m_scale;
	};

	static_assert(32u == sizeof(S1ETTransform3D));

	#pragma endregion

	//-------------------------------------------------------------------------
	// SETTransform3D
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of 3D transforms supporting non-uniform scaling, rotation using
	 Euler angles, and translation.
	 */
	class SETTransform3D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SETTransform3D(F32x3 translation = { 0.0f, 0.0f, 0.0f },
			                    F32x3 rotation    = { 0.0f, 0.0f, 0.0f },
			                    F32x3 scale       = { 1.0f, 1.0f, 1.0f }) noexcept
			: m_translation(std::move(translation)),
			m_padding0{},
			m_rotation(),
			m_padding1{},
			m_scale(std::move(scale)),
			m_padding2{} {

			SetRotation(rotation);
		}

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SETTransform3D(FXMVECTOR translation,
								FXMVECTOR rotation,
								FXMVECTOR scale) noexcept
			: SETTransform3D(XMStore< F32x3 >(translation),
							 XMStore< F32x3 >(rotation),
							 XMStore< F32x3 >(scale)) {}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform.
		 */
		SETTransform3D(const S1ETTransform3D& transform) noexcept
			: SETTransform3D(transform.GetTranslationView(),
							 transform.GetRotationView(),
							 F32x3(transform.GetScale())) {}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 */
		SETTransform3D(const SETTransform3D& transform) noexcept = default;

		/**
		 Constructs a transform by moving the given transform.

		 @param[in]		transform
						A reference to the transform to move.
		 */
		SETTransform3D(SETTransform3D&& transform) noexcept = default;

		/**
		 Destructs this transform.
		 */
		~SETTransform3D() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 @return		A reference to the copy of the given transform (i.e.
						this transform).
		 */
		SETTransform3D& operator=(
			const SETTransform3D& transform) noexcept = default;

		/**
		 Moves the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to move.
		 @return		A reference to the moved transform (i.e. this
						transform).
		 */
		SETTransform3D& operator=(
			SETTransform3D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this transform to the
		 given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this transform to the
		 given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the z-value of the translation component of this transform to the
		 given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(F32 z) noexcept {
			m_translation[2u] = z;
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y, F32 z) noexcept {
			SetTranslation(F32x3(x, y, z));
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x3 translation) noexcept {
			m_translation = std::move(translation);
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x3 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given z-value to the translation component of this transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(F32 z) noexcept {
			SetTranslationZ(GetTranslationZ() + z);
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y, F32 z) noexcept {
			AddTranslation(F32x3(x, y, z));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x3& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this transform.

		 @return		The x-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this transform.

		 @return		The y-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the z-value of the translation component of this transform.

		 @return		The z-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationZ() const noexcept {
			return m_translation[2u];
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		/**
		 Returns the object-to-parent translation matrix of this transform.

		 @return		The object-to-parent translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentTranslationMatrix() const noexcept {
			return GetTranslationMatrix(GetTranslation());
		}

		/**
		 Returns the parent-to-object translation matrix of this transform.

		 @return		The parent-to-object translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectTranslationMatrix() const noexcept {
			return GetInverseTranslationMatrix(GetTranslation());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the rotation component of this transform to the
		 given value.

		 @param[in]		x
						The x-value of the rotation component.
		 */
		void SetRotationX(F32 x) noexcept {
			m_rotation[0u] = WrapAngleRadians(x);
		}

		/**
		 Sets the y-value of the rotation component of this transform to the
		 given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(F32 y) noexcept {
			m_rotation[1u] = WrapAngleRadians(y);
		}

		/**
		 Sets the z-value of the rotation component of this transform to the
		 given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(F32 z) noexcept {
			m_rotation[2u] = WrapAngleRadians(z);
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		x
						The x-value of the rotation component.
		 @param[in]		y
						 The y-value of the rotation component.
		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotation(F32 x, F32 y, F32 z) noexcept {
			SetRotation(F32x3(x, y, z));
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const F32x3& rotation) noexcept {
			SetRotation(XMLoad(rotation));
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						The rotation component.
		 */
		void XM_CALLCONV SetRotation(FXMVECTOR rotation) noexcept {
			m_rotation = XMStore< F32x3 >(WrapAngleRadians(rotation));
		}

		/**
		 Sets the rotation component of this transform to a rotation of the
		 given angle around the given direction.

		 @param[in]		direction
						The unit-length direction.
		 @param[in]		angle
						The angle.
		 */
		void XM_CALLCONV SetRotationAroundDirection(FXMVECTOR direction,
			                                        F32 angle) noexcept {

			const auto R = XMMatrixRotationNormal(direction, angle);

			// cos instead of sin in case the angles are not in [-1,1]
			const auto y = -std::asin(XMVectorGetY(R.r[2u]));
			const auto a = 1.0f / std::cos(m_rotation[1u]);
			const auto z = std::acos(a * XMVectorGetY(R.r[1u]));
			const auto x = std::acos(a * XMVectorGetZ(R.r[2u]));
			SetRotation(x, y, z);
		}

		/**
		 Adds the given x-value to the rotation component of this transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(F32 x) noexcept {
			SetRotationX(GetRotationX() + x);
		}

		/**
		 Adds the given x-value to the rotation component of this transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotationX(F32 x, F32 min_angle, F32 max_angle) noexcept {
			m_rotation[0u] = ClampAngleRadians(GetRotationX() + x,
											   min_angle, max_angle);
		}

		/**
		 Adds the given y-value to the rotation component of this transform.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(F32 y) noexcept {
			SetRotationY(GetRotationY() + y);
		}

		/**
		 Adds the given y-value to the rotation component of this transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotationY(F32 y, F32 min_angle, F32 max_angle) noexcept {
			m_rotation[1u] = ClampAngleRadians(GetRotationY() + y,
											   min_angle, max_angle);
		}

		/**
		 Adds the given z-value to the rotation component of this transform.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(F32 z) noexcept {
			SetRotationZ(GetRotationZ() + z);
		}

		/**
		 Adds the given z-value to the rotation component of this transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		z
						The z-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotationZ(F32 z, F32 min_angle, F32 max_angle) noexcept {
			m_rotation[2u] = ClampAngleRadians(GetRotationZ() + z,
											   min_angle, max_angle);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotation(F32 x, F32 y, F32 z) noexcept {
			AddRotation(F32x3(x, y, z));
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotation(F32 x, F32 y, F32 z, F32 min_angle, F32 max_angle) noexcept {
			AddRotation(F32x3(x, y, z), min_angle, max_angle);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const F32x3& rotation) noexcept {
			AddRotation(XMLoad(rotation));
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		rotation
						A reference to the rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotation(const F32x3& rotation, F32 min_angle, F32 max_angle) noexcept {
			AddRotation(XMLoad(rotation),
						XMVectorReplicate(min_angle),
						XMVectorReplicate(max_angle));
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void XM_CALLCONV AddRotation(FXMVECTOR rotation) noexcept {
			SetRotation(GetRotation() + rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 transform.

		 @pre			@a min_angles lie in [-pi, pi].
		 @pre			@a max_angles lie in [-pi, pi].
		 @pre			@a min_angles is not greater than @a max_angles.
		 @param[in]		rotation
						The rotation component to add.
		 @param[in]		min_angles
						The minimum angles (in radians).
		 @param[in]		max_angles
						The maximum angles (in radians).
		 */
		void XM_CALLCONV AddRotation(FXMVECTOR rotation,
									 FXMVECTOR min_angles,
									 FXMVECTOR max_angles) noexcept {

			m_rotation = XMStore< F32x3 >(
				ClampAngleRadians(GetRotation() + rotation,
								  min_angles, max_angles));
		}

		/**
		 Returns the x-value of the rotation component of this transform.

		 @return		The x-value of the rotation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationX() const noexcept {
			return m_rotation[0u];
		}

		/**
		 Returns the y-value of the rotation component of this transform.

		 @return		The y-value of the rotation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationY() const noexcept {
			return m_rotation[1u];
		}

		/**
		 Returns the z-value of the rotation component of this transform.

		 @return		The z-value of the rotation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationZ() const noexcept {
			return m_rotation[2u];
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetRotationView() const noexcept {
			return m_rotation;
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotation() const noexcept {
			return XMLoad(m_rotation);
		}

		/**
		 Returns the object-to-parent rotation quaternion of this transform.

		 @return		The object-to-parent rotation quaternion of this
						transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectToParentRotationQuaternion() const noexcept {
			// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
			return GetRollPitchYawQuaternion(GetRotation());
		}

		/**
		 Returns the parent-to-object rotation quaternion of this transform.

		 @return		The parent-to-object rotation quaternion of this
						transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentToObjectRotationQuaternion() const noexcept {
			return GetInverseRollPitchYawQuaternion(GetRotation());
		}

		/**
		 Returns the object-to-parent rotation matrix of this transform.

		 @return		The object-to-parent rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentRotationMatrix() const noexcept {
			// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
			return GetRollPitchYawMatrix(GetRotation());
		}

		/**
		 Returns the parent-to-object rotation matrix of this transform.

		 @return		The parent-to-object rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectRotationMatrix() const noexcept {
			return GetInverseRollPitchYawMatrix(GetRotation());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the scale component of this transform to the given
		 value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale[0u] = x;
		}

		/**
		 Sets the y-value of the scale component of this transform to the given
		 value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale[1u] = y;
		}

		/**
		 Sets the z-value of the scale component of this transform to the given
		 value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(F32 z) noexcept {
			m_scale[2u] = z;
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(F32 s) noexcept {
			SetScale(s, s, s);
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScale(F32 x, F32 y, F32 z) noexcept {
			SetScale(F32x3(x, y, z));
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32x3 scale) noexcept {
			m_scale = std::move(scale);
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			SetScale(XMStore< F32x3 >(scale));
		}

		/**
		 Adds the given x-value to the scale component of this transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			SetScaleX(GetScaleX() + x);
		}

		/**
		 Adds the given y-value to the scale component of this transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			SetScaleY(GetScaleY() + y);
		}

		/**
		 Adds the given z-value to the scale component of this transform.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(F32 z) noexcept {
			SetScaleZ(GetScaleZ() + z);
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(F32 s) noexcept {
			AddScale(s, s, s);
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScale(F32 x, F32 y, F32 z) noexcept {
			AddScale(F32x3(x, y, z));
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x3& scale) noexcept {
			AddScale(XMLoad(scale));
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the x-value of the scale component of this transform.

		 @return		The x-value of the scale component of this local
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleX() const noexcept {
			return m_scale[0u];
		}

		/**
		 Returns the y-value of the scale component of this transform.

		 @return		The y-value of the scale component of this transform.
		 */
		[[nodiscard]]
		F32 GetScaleY() const noexcept {
			return m_scale[1u];
		}

		/**
		 Returns the z-value of the scale component of this transform.

		 @return		The z-value of the scale component of this transform.
		 */
		[[nodiscard]]
		F32 GetScaleZ() const noexcept {
			return m_scale[2u];
		}

		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetScaleView() const noexcept {
			return m_scale;
		}

		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetScale() const noexcept {
			return XMLoad(m_scale);
		}

		/**
		 Returns the object-to-parent scale matrix of this transform.

		 @return		The scale object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentScaleMatrix() const noexcept {
			return GetScalingMatrix(GetScale());
		}

		/**
		 Returns the parent-to-object scale matrix of this transform.

		 @return		The parent-to-object scale matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectScaleMatrix() const noexcept {
			return GetInverseScalingMatrix(GetScale());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in object space coordinates.

		 @return		The position of the local origin of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectOrigin() const noexcept {
			return { 0.0f, 0.0f, 0.0f, 1.0f };
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisX() const noexcept {
			return { 1.0f, 0.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisY() const noexcept {
			return { 0.0f, 1.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisZ() const noexcept {
			return { 0.0f, 0.0f, 1.0f, 0.0f };
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in parent space coordinates.

		 @return		The position of the local origin of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentOrigin() const noexcept {
			return GetObjectToParentMatrix().r[3u];
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisX() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[0u]);
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisY() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[1u]);
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisZ() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[2u]);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the object-to-parent matrix of this transform.

		 @return		The object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentMatrix() const noexcept {
			// Scale . Rotation . Translation
			return GetAffineTransformationMatrix(GetScale(),
				                                 GetRotation(),
				                                 GetTranslation());
		}

		/**
		 Returns the parent-to-object matrix of this transform.

		 @return		The parent-to-object matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectMatrix() const noexcept {
			// Translation . Rotation . Scale
			return GetInverseAffineTransformationMatrix(GetScale(),
				                                        GetRotation(),
				                                        GetTranslation());
		}

		/**
		 Transforms the given vector expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		vector
						The vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParent(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given point expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		point
						The point expressed in object space coordinates.
		 @return		The transformed point expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given direction expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		direction
						The direction expressed in object space coordinates.
		 @return		The transformed direction expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		vector
						The vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObject(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given point expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		point
						The point expressed in parent space coordinates.
		 @return		The transformed point expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given direction expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		direction
						The direction expressed in parent space coordinates.
		 @return		The transformed direction expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetParentToObjectMatrix());
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component of this transform.
		 */
		F32x3 m_translation;

		/**
		 The padding of this transform.
		 */
		F32 m_padding0;

		/**
		 The rotation component (Euler angles in radians) of this transform.
		 */
		F32x3 m_rotation;

		/**
		 The padding of this transform.
		 */
		F32 m_padding1;

		/**
		 The scale component of this transform.
		 */
		F32x3 m_scale;

		/**
		 The padding of this transform.
		 */
		F32 m_padding2;
	};

	static_assert(48u == sizeof(SETTransform3D));

	#pragma endregion

	//-------------------------------------------------------------------------
	// S1QTTransform3D
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of 3D transforms supporting uniform scaling, rotation using
	 quaternions, and translation.
	 */
	class S1QTTransform3D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit S1QTTransform3D(F32x3 translation = { 0.0f, 0.0f, 0.0f },
			                     F32x4 rotation    = { 1.0f, 0.0f, 0.0f, 0.0f },
			                     F32   scale       =   1.0f) noexcept
			: m_translation(std::move(translation)),
			m_scale(scale),
			m_rotation() {

			SetRotation(rotation);
		}

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit S1QTTransform3D(FXMVECTOR translation,
			                     FXMVECTOR rotation,
								 F32       scale) noexcept
			: S1QTTransform3D(XMStore< F32x3 >(translation),
							  XMStore< F32x4 >(rotation),
							  scale) {}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 */
		S1QTTransform3D(const S1QTTransform3D& transform) noexcept = default;

		/**
		 Constructs a transform by moving the given transform.

		 @param[in]		transform
						A reference to the transform to move.
		 */
		S1QTTransform3D(S1QTTransform3D&& transform) noexcept = default;

		/**
		 Destructs this transform.
		 */
		~S1QTTransform3D() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 @return		A reference to the copy of the given transform (i.e.
						this transform).
		 */
		S1QTTransform3D& operator=(
			const S1QTTransform3D& transform) noexcept = default;

		/**
		 Moves the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to move.
		 @return		A reference to the moved transform (i.e. this
						transform).
		 */
		S1QTTransform3D& operator=(
			S1QTTransform3D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this transform to the
		 given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this transform to the
		 given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the z-value of the translation component of this transform to the
		 given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(F32 z) noexcept {
			m_translation[2u] = z;
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y, F32 z) noexcept {
			SetTranslation(F32x3(x, y, z));
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x3 translation) noexcept {
			m_translation = std::move(translation);
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x3 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given z-value to the translation component of this transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(F32 z) noexcept {
			SetTranslationZ(GetTranslationZ() + z);
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y, F32 z) noexcept {
			AddTranslation(F32x3(x, y, z));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x3& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this transform.

		 @return		The x-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this transform.

		 @return		The y-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the z-value of the translation component of this transform.

		 @return		The z-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationZ() const noexcept {
			return m_translation[2u];
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		/**
		 Returns the object-to-parent translation matrix of this transform.

		 @return		The object-to-parent translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentTranslationMatrix() const noexcept {
			return GetTranslationMatrix(GetTranslation());
		}

		/**
		 Returns the parent-to-object translation matrix of this transform.

		 @return		The parent-to-object translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectTranslationMatrix() const noexcept {
			return GetInverseTranslationMatrix(GetTranslation());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const F32x4& rotation) noexcept {
			SetRotation(XMLoad(rotation));
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						The rotation component.
		 */
		void XM_CALLCONV SetRotation(FXMVECTOR rotation) noexcept {
			m_rotation = XMStore< F32x4 >(XMQuaternionNormalize(rotation));
		}

		/**
		 Sets the rotation component of this transform to a rotation of the
		 given angle around the given direction.

		 @param[in]		direction
						The unit-length direction.
		 @param[in]		angle
						The angle.
		 */
		void XM_CALLCONV SetRotationAroundDirection(FXMVECTOR direction,
			                                        F32 angle) noexcept {

			SetRotation(XMQuaternionRotationNormal(direction, angle));
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const F32x4 GetRotationView() const noexcept {
			return m_rotation;
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotation() const noexcept {
			return XMLoad(m_rotation);
		}

		/**
		 Returns the object-to-parent rotation matrix of this transform.

		 @return		The object-to-parent rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentRotationMatrix() const noexcept {
			return XMMatrixRotationQuaternion(GetRotation());
		}

		/**
		 Returns the parent-to-object rotation matrix of this transform.

		 @return		The parent-to-object rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectRotationMatrix() const noexcept {
			return XMMatrixRotationQuaternion(XMQuaternionInverse(GetRotation()));
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32 scale) noexcept {
			m_scale = scale;
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void AddScale(F32 scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		[[nodiscard]]
		const F32 GetScale() const noexcept {
			return m_scale;
		}

		/**
		 Returns the object-to-parent scale matrix of this transform.

		 @return		The scale object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentScaleMatrix() const noexcept {
			return GetScalingMatrix(GetScale());
		}

		/**
		 Returns the parent-to-object scale matrix of this transform.

		 @return		The parent-to-object scale matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectScaleMatrix() const noexcept {
			return GetInverseScalingMatrix(GetScale());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in object space coordinates.

		 @return		The position of the local origin of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectOrigin() const noexcept {
			return { 0.0f, 0.0f, 0.0f, 1.0f };
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisX() const noexcept {
			return { 1.0f, 0.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisY() const noexcept {
			return { 0.0f, 1.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisZ() const noexcept {
			return { 0.0f, 0.0f, 1.0f, 0.0f };
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in parent space coordinates.

		 @return		The position of the local origin of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentOrigin() const noexcept {
			return GetObjectToParentMatrix().r[3u];
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisX() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[0u]);
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisY() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[1u]);
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisZ() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[2u]);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the object-to-parent matrix of this transform.

		 @return		The object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentMatrix() const noexcept {
			// Scale . Rotation . Translation
			return GetAffineTransformationMatrix(GetScale(),
				                                 GetRotation(),
				                                 GetTranslation());
		}

		/**
		 Returns the parent-to-object matrix of this transform.

		 @return		The parent-to-object matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectMatrix() const noexcept {
			// Translation . Rotation . Scale
			return GetInverseAffineTransformationMatrix(GetScale(),
				                                        GetRotation(),
				                                        GetTranslation());
		}

		/**
		 Transforms the given vector expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		vector
						The vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParent(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given point expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		point
						The point expressed in object space coordinates.
		 @return		The transformed point expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given direction expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		direction
						The direction expressed in object space coordinates.
		 @return		The transformed direction expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		vector
						The vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObject(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given point expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		point
						The point expressed in parent space coordinates.
		 @return		The transformed point expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given direction expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		direction
						The direction expressed in parent space coordinates.
		 @return		The transformed direction expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetParentToObjectMatrix());
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component of this transform.
		 */
		F32x3 m_translation;

		/**
		 The scale component of this transform.
		 */
		F32 m_scale;

		/**
		 The rotation component (unit quaternion) of this transform.
		 */
		F32x4 m_rotation;
	};

	static_assert(32u == sizeof(S1QTTransform3D));

	#pragma endregion

	//-------------------------------------------------------------------------
	// SQTTransform3D
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of 3D transforms supporting non-uniform scaling, rotation using
	 quaternions, and translation.
	 */
	class SQTTransform3D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SQTTransform3D(F32x3 translation = { 0.0f, 0.0f, 0.0f },
			                    F32x4 rotation    = { 1.0f, 0.0f, 0.0f, 0.0f },
			                    F32x3 scale       = { 1.0f, 1.0f, 1.0f }) noexcept
			: m_translation(std::move(translation)),
			m_padding0{},
			m_rotation(),
			m_padding1{},
			m_scale(std::move(scale)) {

			SetRotation(rotation);
		}

		/**
		 Constructs a transform from the given translation, rotation and scale
		 component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SQTTransform3D(FXMVECTOR translation,
								FXMVECTOR rotation,
								FXMVECTOR scale) noexcept
			: SQTTransform3D(XMStore< F32x3 >(translation),
							 XMStore< F32x4 >(rotation),
							 XMStore< F32x3 >(scale)) {}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform.
		 */
		SQTTransform3D(const S1QTTransform3D& transform) noexcept
			: SQTTransform3D(transform.GetTranslationView(),
							 transform.GetRotationView(),
							 F32x3(transform.GetScale())) {}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 */
		SQTTransform3D(const SQTTransform3D& transform) noexcept = default;

		/**
		 Constructs a transform by moving the given transform.

		 @param[in]		transform
						A reference to the transform to move.
		 */
		SQTTransform3D(SQTTransform3D&& transform) noexcept = default;

		/**
		 Destructs this transform.
		 */
		~SQTTransform3D() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 @return		A reference to the copy of the given transform (i.e.
						this transform).
		 */
		SQTTransform3D& operator=(
			const SQTTransform3D& transform) noexcept = default;

		/**
		 Moves the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to move.
		 @return		A reference to the moved transform (i.e. this
						transform).
		 */
		SQTTransform3D& operator=(
			SQTTransform3D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this transform to the
		 given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this transform to the
		 given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the z-value of the translation component of this transform to the
		 given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(F32 z) noexcept {
			m_translation[2u] = z;
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y, F32 z) noexcept {
			SetTranslation(F32x3(x, y, z));
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x3 translation) noexcept {
			m_translation = std::move(translation);
		}

		/**
		 Sets the translation component of this transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x3 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given z-value to the translation component of this transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(F32 z) noexcept {
			SetTranslationZ(GetTranslationZ() + z);
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y, F32 z) noexcept {
			AddTranslation(F32x3(x, y, z));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x3& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this transform.

		 @return		The x-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this transform.

		 @return		The y-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the z-value of the translation component of this transform.

		 @return		The z-value of the translation component of this
						transform.
		 */
		[[nodiscard]]
		F32 GetTranslationZ() const noexcept {
			return m_translation[2u];
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		/**
		 Returns the object-to-parent translation matrix of this transform.

		 @return		The object-to-parent translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentTranslationMatrix() const noexcept {
			return GetTranslationMatrix(GetTranslation());
		}

		/**
		 Returns the parent-to-object translation matrix of this transform.

		 @return		The parent-to-object translation matrix of this
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectTranslationMatrix() const noexcept {
			return GetInverseTranslationMatrix(GetTranslation());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const F32x4& rotation) noexcept {
			SetRotation(XMLoad(rotation));
		}

		/**
		 Sets the rotation component of this transform to the given rotation
		 component.

		 @param[in]		rotation
						The rotation component.
		 */
		void XM_CALLCONV SetRotation(FXMVECTOR rotation) noexcept {
			m_rotation = XMStore< F32x4 >(XMQuaternionNormalize(rotation));
		}

		/**
		 Sets the rotation component of this transform to a rotation of the
		 given angle around the given direction.

		 @param[in]		direction
						The unit-length direction.
		 @param[in]		angle
						The angle.
		 */
		void XM_CALLCONV SetRotationAroundDirection(FXMVECTOR direction,
			                                        F32 angle) noexcept {

			SetRotation(XMQuaternionRotationNormal(direction, angle));
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const F32x4 GetRotationView() const noexcept {
			return m_rotation;
		}

		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotation() const noexcept {
			return XMLoad(m_rotation);
		}

		/**
		 Returns the object-to-parent rotation matrix of this transform.

		 @return		The object-to-parent rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentRotationMatrix() const noexcept {
			return XMMatrixRotationQuaternion(GetRotation());
		}

		/**
		 Returns the parent-to-object rotation matrix of this transform.

		 @return		The parent-to-object rotation matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectRotationMatrix() const noexcept {
			return XMMatrixRotationQuaternion(XMQuaternionInverse(GetRotation()));
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the scale component of this transform to the given
		 value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale[0u] = x;
		}

		/**
		 Sets the y-value of the scale component of this transform to the given
		 value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale[1u] = y;
		}

		/**
		 Sets the z-value of the scale component of this transform to the given
		 value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(F32 z) noexcept {
			m_scale[2u] = z;
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(F32 s) noexcept {
			SetScale(s, s, s);
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScale(F32 x, F32 y, F32 z) noexcept {
			SetScale(F32x3(x, y, z));
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32x3 scale) noexcept {
			m_scale = std::move(scale);
		}

		/**
		 Sets the scale component of this transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			SetScale(XMStore< F32x3 >(scale));
		}

		/**
		 Adds the given x-value to the scale component of this transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			SetScaleX(GetScaleX() + x);
		}

		/**
		 Adds the given y-value to the scale component of this transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			SetScaleY(GetScaleY() + y);
		}

		/**
		 Adds the given z-value to the scale component of this transform.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(F32 z) noexcept {
			SetScaleZ(GetScaleZ() + z);
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(F32 s) noexcept {
			AddScale(s, s, s);
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScale(F32 x, F32 y, F32 z) noexcept {
			AddScale(F32x3(x, y, z));
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x3& scale) noexcept {
			AddScale(XMLoad(scale));
		}

		/**
		 Adds the given scale component to the scale component of this
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the x-value of the scale component of this transform.

		 @return		The x-value of the scale component of this local
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleX() const noexcept {
			return m_scale[0u];
		}

		/**
		 Returns the y-value of the scale component of this transform.

		 @return		The y-value of the scale component of this transform.
		 */
		[[nodiscard]]
		F32 GetScaleY() const noexcept {
			return m_scale[1u];
		}

		/**
		 Returns the z-value of the scale component of this transform.

		 @return		The z-value of the scale component of this transform.
		 */
		[[nodiscard]]
		F32 GetScaleZ() const noexcept {
			return m_scale[2u];
		}

		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		[[nodiscard]]
		const F32x3 GetScaleView() const noexcept {
			return m_scale;
		}

		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetScale() const noexcept {
			return XMLoad(m_scale);
		}

		/**
		 Returns the object-to-parent scale matrix of this transform.

		 @return		The scale object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentScaleMatrix() const noexcept {
			return GetScalingMatrix(GetScale());
		}

		/**
		 Returns the parent-to-object scale matrix of this transform.

		 @return		The parent-to-object scale matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectScaleMatrix() const noexcept {
			return GetInverseScalingMatrix(GetScale());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in object space coordinates.

		 @return		The position of the local origin of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectOrigin() const noexcept {
			return { 0.0f, 0.0f, 0.0f, 1.0f };
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisX() const noexcept {
			return { 1.0f, 0.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisY() const noexcept {
			return { 0.0f, 1.0f, 0.0f, 0.0f };
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in object space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisZ() const noexcept {
			return { 0.0f, 0.0f, 1.0f, 0.0f };
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this transform expressed
		 in parent space coordinates.

		 @return		The position of the local origin of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentOrigin() const noexcept {
			return GetObjectToParentMatrix().r[3u];
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local x-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisX() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[0u]);
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local y-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisY() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[1u]);
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed
		 in parent space coordinates.

		 @return		The direction of the local z-axis of this transform
						expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisZ() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[2u]);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the object-to-parent matrix of this transform.

		 @return		The object-to-parent matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentMatrix() const noexcept {
			// Scale . Rotation . Translation
			return GetAffineTransformationMatrix(GetScale(),
				                                 GetRotation(),
				                                 GetTranslation());
		}

		/**
		 Returns the parent-to-object matrix of this transform.

		 @return		The parent-to-object matrix of this transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectMatrix() const noexcept {
			// Translation . Rotation . Scale
			return GetInverseAffineTransformationMatrix(GetScale(),
				                                        GetRotation(),
				                                        GetTranslation());
		}

		/**
		 Transforms the given vector expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		vector
						The vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParent(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given point expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		point
						The point expressed in object space coordinates.
		 @return		The transformed point expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given direction expressed in object space coordinates to
		 parent space coordinates.

		 @param[in]		direction
						The direction expressed in object space coordinates.
		 @return		The transformed direction expressed in parent space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformObjectToParentDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		vector
						The vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObject(FXMVECTOR vector) const noexcept {

			return XMVector4Transform(vector, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given point expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		point
						The point expressed in parent space coordinates.
		 @return		The transformed point expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectPoint(FXMVECTOR point) const noexcept {

			return XMVector3TransformCoord(point, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given direction expressed in parent space coordinates to
		 object space coordinates.

		 @param[in]		direction
						The direction expressed in parent space coordinates.
		 @return		The transformed direction expressed in object space
						coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV
			TransformParentToObjectDirection(FXMVECTOR direction) const noexcept {

			return XMVector3TransformNormal(direction, GetParentToObjectMatrix());
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component of this transform.
		 */
		F32x3 m_translation;

		/**
		 The padding of this transform.
		 */
		F32 m_padding0;

		/**
		 The rotation component (unit quaternion) of this transform.
		 */
		F32x4 m_rotation;

		/**
		 The scale component of this transform.
		 */
		F32x3 m_scale;

		/**
		 The padding of this transform.
		 */
		F32 m_padding1;
	};

	static_assert(48u == sizeof(SQTTransform3D));

	#pragma endregion

	//-------------------------------------------------------------------------
	// SpriteTransform2D
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of 2D sprite transforms supporting non-uniform scaling, rotation
	 and translation (incl. depth).
	 */
	class SpriteTransform2D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a sprite transform from the given translation, depth,
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		depth
						The depth component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SpriteTransform2D(F32x2 translation     = { 0.0f, 0.0f },
			                       F32   depth           =   0.0f,
			                       F32   rotation        =   0.0f,
			                       F32x2 rotation_origin = { 0.0f, 0.0f },
			                       F32x2 scale           = { 1.0f, 1.0f }) noexcept
			: m_translation(std::move(translation)),
			m_depth(depth),
			m_rotation(),
			m_rotation_origin(std::move(rotation_origin)),
			m_scale(std::move(scale)) {

			SetRotation(rotation);
		}

		/**
		 Constructs a sprite transform from the given translation, depth,
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		depth
						The depth component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit SpriteTransform2D(FXMVECTOR translation,
			                       F32       depth,
			                       F32       rotation,
			                       FXMVECTOR rotation_origin,
			                       FXMVECTOR scale) noexcept
			: SpriteTransform2D(XMStore< F32x2 >(translation),
								depth, rotation,
								XMStore< F32x2 >(rotation_origin),
								XMStore< F32x2 >(scale)) {}

		/**
		 Constructs a sprite transform from the given sprite transform.

		 @param[in]		transform
						A reference to the sprite transform to copy.
		 */
		SpriteTransform2D(const SpriteTransform2D& transform) noexcept = default;

		/**
		 Constructs a sprite transform by moving the given sprite transform.

		 @param[in]		transform
						A reference to the sprite transform to move.
		 */
		SpriteTransform2D(SpriteTransform2D&& transform) noexcept = default;

		/**
		 Destructs this sprite transform.
		 */
		~SpriteTransform2D() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given sprite transform to this sprite transform.

		 @param[in]		transform
						The sprite transform to move.
		 @return		A reference to the copy of the given sprite transform
						(i.e. this sprite transform).
		 */
		SpriteTransform2D& operator=(
			const SpriteTransform2D& transform) noexcept = default;

		/**
		 Moves the given sprite transform to this sprite transform.

		 @param[in]		transform
						The sprite transform to copy.
		 @return		A reference to the moved sprite transform (i.e. this
						sprite transform).
		 */
		SpriteTransform2D& operator=(
			SpriteTransform2D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this sprite transform
		 to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this sprite transform
		 to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the translation component of this sprite transform to the given
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y) noexcept {
			SetTranslation(F32x2(x, y));
		}

		/**
		 Sets the translation component of this sprite transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x2 translation) noexcept {
			m_translation = std::move(translation);
		}

		/**
		 Sets the translation component of this sprite transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x2 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this sprite
		 transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this sprite
		 transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given translation component to the translation component of
		 this sprite transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y) noexcept {
			AddTranslation(F32x2(x, y));
		}

		/**
		 Adds the given translation component to the translation component of
		 this sprite transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x2& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this sprite transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this sprite
		 transform.

		 @return		The x-value of the translation component of this
						sprite transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this sprite
		 transform.

		 @return		The y-value of the translation component of this
						sprite transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the translation component of this sprite transform.

		 @return		The translation component of this sprite transform.
		 */
		[[nodiscard]]
		const F32x2 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this sprite transform.

		 @return		The translation component of this sprite transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Depth
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the depth component of this sprite transform to the given depth
		 component.

		 @param[in]		depth
						The depth component.
		 */
		void SetDepth(F32 depth) noexcept {
			m_depth = depth;
		}

		/**
		 Adds the given depth component to the depth component of this sprite
		 transform.

		 @param[in]		depth
						The depth component to add.
		 */
		void AddDepth(F32 depth) noexcept {
			SetDepth(GetDepth() + depth);
		}

		/**
		 Returns the depth component of this sprite transform.

		 @return		The depth component of this sprite transform.
		 */
		[[nodiscard]]
		F32 GetDepth() const noexcept {
			return m_depth;
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the rotation component of this sprite transform to the given r
		 otation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(F32 rotation) noexcept {
			m_rotation = WrapAngleRadians(rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 sprite transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void AddRotation(F32 rotation) noexcept {
			SetRotation(GetRotation() + rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 sprite transform and clamps the resulting rotation component of this
		 sprite transform between the given values.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		rotation
						The rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotation(F32 rotation, F32 min_angle, F32 max_angle) noexcept {
			m_rotation = ClampAngleRadians(GetRotation() + rotation,
										   min_angle, max_angle);
		}

		/**
		 Returns the rotation component of this sprite transform.

		 @return		The rotation component of this sprite transform.
		 */
		[[nodiscard]]
		F32 GetRotation() const noexcept {
			return m_rotation;
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation Origin
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the rotation origin of this sprite transform to
		 the given value.

		 @param[in]		x
						The x-value of the rotation origin.
		 */
		void SetRotationOriginX(F32 x) noexcept {
			m_rotation_origin[0u] = x;
		}

		/**
		 Sets the y-value of the rotation origin of this sprite transform to
		 the given value.

		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOriginY(F32 y) noexcept {
			m_rotation_origin[1u] = y;
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation
		 origin.

		 @param[in]		x
						The x-value of the rotation origin.
		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOrigin(F32 x, F32 y) noexcept {
			SetRotationOrigin(F32x2(x, y));
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation
		 origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void SetRotationOrigin(F32x2 rotation_origin) noexcept {
			m_rotation_origin = std::move(rotation_origin);
		}

		/**
		 Sets the rotation origin of this sprite transform to the given rotation
		 origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void XM_CALLCONV SetRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			SetRotationOrigin(XMStore< F32x2 >(rotation_origin));
		}

		/**
		 Adds the given x-value to the rotation origin of this sprite
		 transform.

		 @param[in]		x
						The x-value of the offset to add.
		 */
		void AddRotationOriginX(F32 x) noexcept {
			SetRotationOriginX(GetRotationOriginX() + x);
		}

		/**
		 Adds the given y-value to the rotation origin of this sprite
		 transform.

		 @param[in]		y
						The y-value of the offset to add.
		 */
		void AddRotationOriginY(F32 y) noexcept {
			SetRotationOriginY(GetRotationOriginY() + y);
		}

		/**
		 Adds the given offsets to the rotation origin of this sprite
		 transform.

		 @param[in]		x
						The x-value of the offset to add.
		 @param[in]		y
						The y-value of the offset to add.
		 */
		void AddRotationOrigin(F32 x, F32 y) noexcept {
			AddRotationOrigin(F32x2(x, y));
		}

		/**
		 Adds the given offset to the rotation origin of this sprite transform.

		 @param[in]		offset
						The offset to add.
		 */
		void AddRotationOrigin(const F32x2& offset) noexcept {
			AddRotationOrigin(XMLoad(offset));
		}

		/**
		 Adds the given offset to the rotation origin of this sprite transform.

		 @param[in]		offset
						The offset to add.
		 */
		void XM_CALLCONV AddRotationOrigin(FXMVECTOR offset) noexcept {
			SetRotationOrigin(GetRotationOrigin() + offset);
		}

		/**
		 Returns the x-value of the rotation origin of this sprite transform.

		 @return		The x-value of the rotation origin of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginX() const noexcept {
			return m_rotation_origin[0u];
		}

		/**
		 Returns the y-value of the rotation origin of this sprite transform.

		 @return		The y-value of the rotation origin of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginY() const noexcept {
			return m_rotation_origin[1u];
		}

		/**
		 Returns the rotation origin of this sprite transform.

		 @return		The rotation origin of this sprite transform.
		 */
		[[nodiscard]]
		const F32x2 GetRotationOriginView() const noexcept {
			return m_rotation_origin;
		}

		/**
		 Returns the rotation origin of this sprite transform.

		 @return		The rotation origin of this sprite transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotationOrigin() const noexcept {
			return XMLoad(m_rotation_origin);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the scale component of this sprite transform to
		 the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale[0u] = x;
		}

		/**
		 Sets the y-value of the scale component of this sprite transform to
		 the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale[1u] = y;
		}

		/**
		 Sets the scale component of this sprite transform to the given scale
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(F32 s) noexcept {
			SetScale(s, s);
		}

		/**
		 Sets the scale component of this sprite transform to the given scale
		 component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScale(F32 x, F32 y) noexcept {
			SetScale(F32x2(x, y));
		}

		/**
		 Sets the scale component of this sprite transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32x2 scale) noexcept {
			m_scale = std::move(scale);
		}

		/**
		 Sets the scale component of this sprite transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			SetScale(XMStore< F32x2 >(scale));
		}

		/**
		 Adds the given x-value to the scale component of this sprite
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			SetScaleX(GetScaleX() + x);
		}

		/**
		 Adds the given y-value to the scale component of this sprite
		 transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			SetScaleY(GetScaleY() + y);
		}

		/**
		 Adds the given scale component to the scale component of this sprite
		 transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(F32 s) noexcept {
			AddScale(s, s);
		}

		/**
		 Adds the given scale component to the scale component of this sprite
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScale(F32 x, F32 y) noexcept {
			AddScale(F32x2(x, y));
		}

		/**
		 Adds the given scale component to the scale component of this sprite
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x2& scale) noexcept {
			AddScale(XMLoad(scale));
		}

		/**
		 Adds the given scale component to the scale component of this sprite
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the x-value of the scale component of this sprite transform.

		 @return		The x-value of the scale component of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleX() const noexcept {
			return m_scale[0u];
		}

		/**
		 Returns the y-value of the scale component of this sprite transform.

		 @return		The y-value of the scale component of this sprite
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleY() const noexcept {
			return m_scale[1u];
		}

		/**
		 Returns the scale component of this sprite transform.

		 @return		The scale component of this sprite transform.
		 */
		[[nodiscard]]
		const F32x2 GetScaleView() const noexcept {
			return m_scale;
		}

		/**
		 Returns the scale component of this sprite transform.

		 @return		The scale component of this sprite transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetScale() const noexcept {
			return XMLoad(m_scale);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the transformation matrix of this sprite transform.

		 @return		The transformation matrix of this sprite transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetTransformMatrix() const noexcept {
			auto transformation = GetAffineTransformationMatrix(GetRotationOrigin(),
																GetScale(),
																GetRotation(),
																GetTranslation());
			transformation.r[3u] = XMVectorSetZ(transformation.r[3], GetDepth());

			return transformation;
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component (in pixels) of this sprite transform.
		 */
		F32x2 m_translation;

		/**
		 The depth component of this sprite transform.
		 */
		F32 m_depth;

		/**
		 The rotation component (in radians) of this sprite transform.
		 */
		F32 m_rotation;

		/**
		 The rotation origin (in texels) of this sprite transform.
		 */
		F32x2 m_rotation_origin;

		/**
		 The scale component of this sprite transform.
		 */
		F32x2 m_scale;
	};

	static_assert(32u == sizeof(SpriteTransform2D));

	#pragma endregion

	//-------------------------------------------------------------------------
	// TextureTransform2D
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of 2D texture transforms supporting non-uniform scaling, rotation
	 and translation.
	 */
	class TextureTransform2D {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a texture transform from the given translation, depth,
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit TextureTransform2D(F32x2 translation     = { 0.0f, 0.0f },
			                        F32   rotation        =   0.0f,
			                        F32x2 rotation_origin = { 0.0f, 0.0f },
			                        F32x2 scale           = { 1.0f, 1.0f }) noexcept
			: m_translation(std::move(translation)),
			m_padding{},
			m_rotation(),
			m_rotation_origin(std::move(rotation_origin)),
			m_scale(std::move(scale)) {

			SetRotation(rotation);
		}

		/**
		 Constructs a texture transform from the given translation, depth,
		 rotation, rotation origin and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		rotation_origin
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit TextureTransform2D(FXMVECTOR translation,
									F32       rotation,
									FXMVECTOR rotation_origin,
									FXMVECTOR scale) noexcept
			: TextureTransform2D(XMStore< F32x2 >(translation),
								 rotation,
								 XMStore< F32x2 >(rotation_origin),
								 XMStore< F32x2 >(scale)) {}

		/**
		 Constructs a texture transform from the given texture transform.

		 @param[in]		transform
						A reference to the texture transform to copy.
		 */
		TextureTransform2D(const TextureTransform2D& transform) noexcept = default;

		/**
		 Constructs a texture transform by moving the given texture transform.

		 @param[in]		transform
						A reference to the texture transform to move.
		 */
		TextureTransform2D(TextureTransform2D&& transform) noexcept = default;

		/**
		 Destructs this texture transform.
		 */
		~TextureTransform2D() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given texture transform to this texture transform.

		 @param[in]		transform
						The texture transform to move.
		 @return		A reference to the copy of the given texture transform
						(i.e. this texture transform).
		 */
		TextureTransform2D& operator=(
			const TextureTransform2D& transform) noexcept = default;

		/**
		 Moves the given texture transform to this texture transform.

		 @param[in]		transform
						The texture transform to copy.
		 @return		A reference to the moved texture transform (i.e. this
						texture transform).
		 */
		TextureTransform2D& operator=(
			TextureTransform2D&& transform) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this texture
		 transform to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation[0u] = x;
		}

		/**
		 Sets the y-value of the translation component of this texture
		 transform to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation[1u] = y;
		}

		/**
		 Sets the translation component of this texture transform to the given
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y) noexcept {
			SetTranslation(F32x2(x, y));
		}

		/**
		 Sets the translation component of this texture transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x2 translation) noexcept {
			m_translation = std::move(translation);
		}

		/**
		 Sets the translation component of this texture transform to the given
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(XMStore< F32x2 >(translation));
		}

		/**
		 Adds the given x-value to the translation component of this texture
		 transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			SetTranslationX(GetTranslationX() + x);
		}

		/**
		 Adds the given y-value to the translation component of this texture
		 transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			SetTranslationY(GetTranslationY() + y);
		}

		/**
		 Adds the given translation component to the translation component of
		 this texture transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y) noexcept {
			AddTranslation(F32x2(x, y));
		}

		/**
		 Adds the given translation component to the translation component of
		 this texture transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x2& translation) noexcept {
			AddTranslation(XMLoad(translation));
		}

		/**
		 Adds the given translation component to the translation component of
		 this texture transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			SetTranslation(GetTranslation() + translation);
		}

		/**
		 Returns the x-value of the translation component of this texture
		 transform.

		 @return		The x-value of the translation component of this
						texture transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation[0u];
		}

		/**
		 Returns the y-value of the translation component of this texture
		 transform.

		 @return		The y-value of the translation component of this
						texture transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation[1u];
		}

		/**
		 Returns the translation component of this texture transform.

		 @return		The translation component of this texture transform.
		 */
		[[nodiscard]]
		const F32x2 GetTranslationView() const noexcept {
			return m_translation;
		}

		/**
		 Returns the translation component of this texture transform.

		 @return		The translation component of this texture transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslation() const noexcept {
			return XMLoad(m_translation);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the rotation component of this texture transform to the given
		 rotation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(F32 rotation) noexcept {
			m_rotation = WrapAngleRadians(rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 texture transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void AddRotation(F32 rotation) noexcept {
			SetRotation(GetRotation() + rotation);
		}

		/**
		 Adds the given rotation component to the rotation component of this
		 texture transform and clamps the resulting rotation component of this
		 texture transform between the given values.

		 @pre			@a min_angle lies in [-pi, pi].
		 @pre			@a max_angle lies in [-pi, pi].
		 @pre			@a min_angle is not greater than @a max_angle.
		 @param[in]		rotation
						The rotation component to add.
		 @param[in]		min_angle
						The minimum angle (in radians).
		 @param[in]		max_angle
						The maximum angle (in radians).
		 */
		void AddRotation(F32 rotation, F32 min_angle, F32 max_angle) noexcept {
			m_rotation = ClampAngleRadians(GetRotation() + rotation,
										   min_angle, max_angle);
		}

		/**
		 Returns the rotation component of this texture transform.

		 @return		The rotation component of this texture transform.
		 */
		[[nodiscard]]
		F32 GetRotation() const noexcept {
			return m_rotation;
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation Origin
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the rotation origin of this texture transform to
		 the given value.

		 @param[in]		x
						The x-value of the rotation origin.
		 */
		void SetRotationOriginX(F32 x) noexcept {
			m_rotation_origin[0u] = x;
		}

		/**
		 Sets the y-value of the rotation origin of this texture transform to
		 the given value.

		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOriginY(F32 y) noexcept {
			m_rotation_origin[1u] = y;
		}

		/**
		 Sets the rotation origin of this texture transform to the given
		 rotation origin.

		 @param[in]		x
						The x-value of the rotation origin.
		 @param[in]		y
						The y-value of the rotation origin.
		 */
		void SetRotationOrigin(F32 x, F32 y) noexcept {
			SetRotationOrigin(F32x2(x, y));
		}

		/**
		 Sets the rotation origin of this texture transform to the given
		 rotation origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void SetRotationOrigin(F32x2 rotation_origin) noexcept {
			m_rotation_origin = std::move(rotation_origin);
		}

		/**
		 Sets the rotation origin of this texture transform to the given
		 rotation origin.

		 @param[in]		rotation_origin
						The rotation origin.
		 */
		void XM_CALLCONV SetRotationOrigin(FXMVECTOR rotation_origin) noexcept {
			SetRotationOrigin(XMStore< F32x2 >(rotation_origin));
		}

		/**
		 Adds the given x-value to the rotation origin of this texture
		 transform.

		 @param[in]		x
						The x-value of the offset to add.
		 */
		void AddRotationOriginX(F32 x) noexcept {
			SetRotationOriginX(GetRotationOriginX() + x);
		}

		/**
		 Adds the given y-value to the rotation origin of this texture
		 transform.

		 @param[in]		y
						The y-value of the offset to add.
		 */
		void AddRotationOriginY(F32 y) noexcept {
			SetRotationOriginY(GetRotationOriginY() + y);
		}

		/**
		 Adds the given offsets to the rotation origin of this texture
		 transform.

		 @param[in]		x
						The x-value of the offset to add.
		 @param[in]		y
						The y-value of the offset to add.
		 */
		void AddRotationOrigin(F32 x, F32 y) noexcept {
			AddRotationOrigin(F32x2(x, y));
		}

		/**
		 Adds the given offset to the rotation origin of this texture
		 transform.

		 @param[in]		offset
						The offset to add.
		 */
		void AddRotationOrigin(const F32x2& offset) noexcept {
			AddRotationOrigin(XMLoad(offset));
		}

		/**
		 Adds the given offset to the rotation origin of this texture
		 transform.

		 @param[in]		offset
						The offset to add.
		 */
		void XM_CALLCONV AddRotationOrigin(FXMVECTOR offset) noexcept {
			SetRotationOrigin(GetRotationOrigin() + offset);
		}

		/**
		 Returns the x-value of the rotation origin of this texture transform.

		 @return		The x-value of the rotation origin of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginX() const noexcept {
			return m_rotation_origin[0u];
		}

		/**
		 Returns the y-value of the rotation origin of this texture transform.

		 @return		The y-value of the rotation origin of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetRotationOriginY() const noexcept {
			return m_rotation_origin[1u];
		}

		/**
		 Returns the rotation origin of this texture transform.

		 @return		The rotation origin of this texture transform.
		 */
		[[nodiscard]]
		const F32x2 GetRotationOriginView() const noexcept {
			return m_rotation_origin;
		}

		/**
		 Returns the rotation origin of this texture transform.

		 @return		The rotation origin of this texture transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotationOrigin() const noexcept {
			return XMLoad(m_rotation_origin);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the scale component of this texture transform to
		 the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale[0u] = x;
		}

		/**
		 Sets the y-value of the scale component of this texture transform to
		 the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale[1u] = y;
		}

		/**
		 Sets the scale component of this texture transform to the given scale
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(F32 s) noexcept {
			SetScale(s, s);
		}

		/**
		 Sets the scale component of this texture transform to the given scale
		 component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScale(F32 x, F32 y) noexcept {
			SetScale(F32x2(x, y));
		}

		/**
		 Sets the scale component of this texture transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32x2 scale) noexcept {
			m_scale = std::move(scale);
		}

		/**
		 Sets the scale component of this texture transform to the given scale
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			SetScale(XMStore< F32x2 >(scale));
		}

		/**
		 Adds the given x-value to the scale component of this texture
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			SetScaleX(GetScaleX() + x);
		}

		/**
		 Adds the given y-value to the scale component of this texture
		 transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			SetScaleY(GetScaleY() + y);
		}

		/**
		 Adds the given scale component to the scale component of this texture
		 transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(F32 s) noexcept {
			AddScale(s, s);
		}

		/**
		 Adds the given scale component to the scale component of this texture
		 transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScale(F32 x, F32 y) noexcept {
			AddScale(F32x2(x, y));
		}

		/**
		 Adds the given scale component to the scale component of this texture
		 transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x2& scale) noexcept {
			AddScale(XMLoad(scale));
		}

		/**
		 Adds the given scale component to the scale component of this texture
		 transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			SetScale(GetScale() + scale);
		}

		/**
		 Returns the x-value of the scale component of this texture transform.

		 @return		The x-value of the scale component of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleX() const noexcept {
			return m_scale[0u];
		}

		/**
		 Returns the y-value of the scale component of this texture transform.

		 @return		The y-value of the scale component of this texture
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleY() const noexcept {
			return m_scale[1u];
		}

		/**
		 Returns the scale component of this texture transform.

		 @return		The scale component of this texture transform.
		 */
		[[nodiscard]]
		const F32x2 GetScaleView() const noexcept {
			return m_scale;
		}

		/**
		 Returns the scale component of this texture transform.

		 @return		The scale component of this texture transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetScale() const noexcept {
			return XMLoad(m_scale);
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the transformation matrix of this texture transform.

		 @return		The transformation matrix of this texture transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetTransformMatrix() const noexcept {
			return XMMatrixAffineTransformation2D(GetScale(),
												  GetRotationOrigin(),
												  GetRotation(),
												  GetTranslation());
		}

		#pragma endregion

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The translation component (in UV coordinates) of this texture
		 transform.
		 */
		F32x2 m_translation;

		/**
		 The padding of this texture transform.
		 */
		F32 m_padding;

		/**
		 The rotation component (in radians) of this texture transform.
		 */
		F32 m_rotation;

		/**
		 The rotation origin (in UV coordinates) of this texture transform.
		 */
		F32x2 m_rotation_origin;

		/**
		 The scale component of this texture transform.
		 */
		F32x2 m_scale;
	};

	static_assert(32u == sizeof(TextureTransform2D));

	#pragma endregion
}