//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "transform\transform_utils.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {
	
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
}