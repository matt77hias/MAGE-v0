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

	/**
	 A class of local transforms.
	 */
	class LocalTransform final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a local transform from the given translation, rotation and 
		 scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit LocalTransform(F32x3 translation = { 0.0f, 0.0f, 0.0f }, 
			                    F32x3 rotation    = { 0.0f, 0.0f, 0.0f }, 
			                    F32x3 scale       = { 1.0f, 1.0f, 1.0f }) noexcept
			: m_translation(std::move(translation)),
			m_padding0(0),
			m_rotation(std::move(rotation)),
			m_padding1(0),
			m_scale(std::move(scale)),
			m_padding2(0) {}
		
		/**
		 Constructs a local transform from the given translation, rotation and 
		 scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		explicit LocalTransform(FXMVECTOR translation,
			                    FXMVECTOR rotation,
			                    FXMVECTOR scale) noexcept
			: m_translation(),
			m_padding0(0),
			m_rotation(),
			m_padding1(0),
			m_scale(),
			m_padding2(0) {
			
			SetTranslation(translation);
			SetRotation(rotation);
			SetScale(scale);
		}

		/**
		 Constructs a local transform from the given local transform.

		 @param[in]		transform
						A reference to the local transform to copy.
		 */
		LocalTransform(const LocalTransform& transform) noexcept = default;

		/**
		 Constructs a local transform by moving the given local transform.

		 @param[in]		transform
						A reference to the local transform to move.
		 */
		LocalTransform(LocalTransform&& transform) noexcept = default;

		/**
		 Destructs this local transform.
		 */
		~LocalTransform() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given local transform to this local transform.

		 @param[in]		transform
						A reference to the local transform to copy.
		 @return		A reference to the copy of the given local transform 
						(i.e. this local transform).
		 */
		LocalTransform& operator=(const LocalTransform& transform) = default;

		/**
		 Moves the given local transform to this local transform.

		 @param[in]		transform
						A reference to the local transform to move.
		 @return		A reference to the moved local transform (i.e. this 
						local transform).
		 */
		LocalTransform& operator=(LocalTransform&& transform) = default;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the translation component of this local transform 
		 to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(F32 x) noexcept {
			m_translation.m_x = x;
		}
		
		/**
		 Sets the y-value of the translation component of this local transform 
		 to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(F32 y) noexcept {
			m_translation.m_y = y;
		}
		
		/**
		 Sets the z-value of the translation component of this local transform 
		 to the given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(F32 z) noexcept {
			m_translation.m_z = z;
		}
		
		/**
		 Sets the translation component of this local transform to the given 
		 translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(F32 x, F32 y, F32 z) noexcept {
			SetTranslationX(x);
			SetTranslationY(y);
			SetTranslationZ(z);
		}
		
		/**
		 Sets the translation component of this local transform to the given 
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void SetTranslation(F32x3 translation) noexcept {
			m_translation = std::move(translation);
		}
		
		/**
		 Sets the translation component of this local transform to the given 
		 translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			m_translation = XMStore< F32x3 >(translation);
		}

		/**
		 Adds the given x-value to the translation component of this local 
		 transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(F32 x) noexcept {
			m_translation.m_x += x;
		}
		
		/**
		 Adds the given y-value to the translation component of this local transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(F32 y) noexcept {
			m_translation.m_y += y;
		}
		
		/**
		 Adds the given z-value to the translation component of this local transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(F32 z) noexcept {
			m_translation.m_z += z;
		}
		
		/**
		 Adds the given translation component to the translation component of 
		 this local transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(F32 x, F32 y, F32 z) noexcept {
			AddTranslationX(x);
			AddTranslationY(y);
			AddTranslationZ(z);
		}
		
		/**
		 Adds the given translation component to the translation component of 
		 this local transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const F32x3& translation) noexcept {
			AddTranslation(translation.m_x, translation.m_y, translation.m_z);
		}
		
		/**
		 Adds the given translation component to the translation component of 
		 this local transform.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			AddTranslation(XMVectorGetX(translation), 
				           XMVectorGetY(translation), 
				           XMVectorGetZ(translation));
		}

		/**
		 Returns the x-value of the translation component of this local 
		 transform.

		 @return		The x-value of the translation component of this 
						local transform.
		 */
		[[nodiscard]]
		F32 GetTranslationX() const noexcept {
			return m_translation.m_x;
		}
		
		/**
		 Returns the y-value of the translation component of this local 
		 transform.

		 @return		The y-value of the translation component of this 
						local transform.
		 */
		[[nodiscard]]
		F32 GetTranslationY() const noexcept {
			return m_translation.m_y;
		}
		
		/**
		 Returns the z-value of the translation component of this local 
		 transform.

		 @return		The z-value of the translation component of this 
						local transform.
		 */
		[[nodiscard]]
		F32 GetTranslationZ() const noexcept {
			return m_translation.m_z;
		}
		
		/**
		 Returns the translation component of this local transform.

		 @return		The translation component of this local transform.
		 */
		[[nodiscard]]
		const F32x3 GetTranslation() const noexcept {
			return m_translation;
		}
		
		/**
		 Returns the translation component of this local transform.

		 @return		The translation component of this local transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetTranslationV() const noexcept {
			return XMLoad(m_translation);
		}

		/**
		 Returns the object-to-parent translation matrix of this local 
		 transform.

		 @return		The object-to-parent translation matrix of this 
						local transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentTranslationMatrix() const noexcept {
			return XMMatrixTranslation(GetTranslationV());
		}

		/**
		 Returns the parent-to-object translation matrix of this local 
		 transform.

		 @return		The parent-to-object translation matrix of this 
						local transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectTranslationMatrix() const noexcept {
			return XMMatrixInverseTranslation(GetTranslationV());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the rotation component of this local transform to 
		 the given value.

		 @param[in]		x
						The x-value of the rotation component.
		 */
		void SetRotationX(F32 x) noexcept {
			m_rotation.m_x = x;
		}
		
		/**
		 Sets the y-value of the rotation component of this local transform to 
		 the given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(F32 y) noexcept {
			m_rotation.m_y = y;
		}
		
		/**
		 Sets the z-value of the rotation component of this local transform to 
		 the given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(F32 z) noexcept {
			m_rotation.m_z = z;
		}
		
		/**
		 Sets the rotation component of this local transform to the given 
		 rotation component.

		 @param[in]		x
						The x-value of the rotation component.
		 @param[in]		y
						 The y-value of the rotation component.
		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotation(F32 x, F32 y, F32 z) noexcept {
			SetRotationX(x);
			SetRotationY(y);
			SetRotationZ(z);
		}
		
		/**
		 Sets the rotation component of this local transform to the given 
		 rotation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void SetRotation(F32x3 rotation) noexcept {
			m_rotation = std::move(rotation);
		}

		/**
		 Sets the rotation component of this local transform to the given 
		 rotation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void XM_CALLCONV SetRotation(FXMVECTOR rotation) noexcept {
			m_rotation = XMStore< F32x3 >(rotation);
		}
		
		/**
		 Sets the rotation component of this local transform to a rotation of 
		 the given angle around the given normal.

		 @param[in]		normal
						The normal.
		 @param[in]		angle
						The angle.
		 */
		void XM_CALLCONV SetRotationAroundDirection(FXMVECTOR normal, 
			                                        F32 angle) noexcept {

			const XMMATRIX rotation = XMMatrixRotationNormal(normal, angle);
			
			// cosf function instead of sinf in case the angles are not in [-1,1]
			m_rotation.m_y = -asinf(XMVectorGetY(rotation.r[2]));
			const F32 cp   = cosf(m_rotation.m_y);
			const F32 cr   = XMVectorGetY(rotation.r[1]) / cp;
			m_rotation.m_z = acosf(cr);
			const F32 cy   = XMVectorGetZ(rotation.r[2]) / cp;
			m_rotation.m_x = acosf(cy);
		}
		
		/**
		 Adds the given x-value to the rotation component of this local 
		 transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(F32 x) noexcept {
			m_rotation.m_x += x;
		}
		
		/**
		 Adds the given y-value to the rotation component of this local 
		 transform.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(F32 y) noexcept {
			m_rotation.m_y += y;
		}
		
		/**
		 Adds the given z-value to the rotation component of this local 
		 transform.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(F32 z) noexcept {
			m_rotation.m_z += z;
		}
		
		/**
		 Adds the given rotation component to the rotation component of this 
		 local transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotation(F32 x, F32 y, F32 z) noexcept {
			AddRotationX(x);
			AddRotationY(y);
			AddRotationZ(z);
		}
		
		/**
		 Adds the given rotation component to the rotation component of this 
		 local transform.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const F32x3& rotation) noexcept {
			AddRotation(rotation.m_x, rotation.m_y, rotation.m_z);
		}
		
		/**
		 Adds the given rotation component to the rotation component of this 
		 local transform.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void XM_CALLCONV AddRotation(FXMVECTOR rotation) noexcept {
			AddRotation(XMVectorGetX(rotation), 
				        XMVectorGetY(rotation), 
				        XMVectorGetZ(rotation));
		}

		/**
		 Adds the given x-value to the rotation component of this local 
		 transform and clamps the resulting rotation component of this local 
		 transform between the given values.

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
		void AddAndClampRotationX(F32 x, F32 min_angle, F32 max_angle) noexcept {
			m_rotation.m_x = ClampAngleRadians(m_rotation.m_x + x, 
				                               min_angle, 
				                               max_angle);
		}

		/**
		 Adds the given y-value to the rotation component of this local 
		 transform and clamps the resulting rotation component of this local 
		 transform between the given values.

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
		void AddAndClampRotationY(F32 y, F32 min_angle, F32 max_angle) noexcept {
			m_rotation.m_y = ClampAngleRadians(m_rotation.m_y + y, 
				                               min_angle, 
				                               max_angle);
		}

		/**
		 Adds the given z-value to the rotation component of this local 
		 transform and clamps the resulting rotation component of this local 
		 transform between the given values.

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
		void AddAndClampRotationZ(F32 z, F32 min_angle, F32 max_angle) noexcept {
			m_rotation.m_z = ClampAngleRadians(m_rotation.m_z + z, 
				                               min_angle, 
				                               max_angle);
		}

		/**
		 Adds the given rotation component to the rotation component of this 
		 local transform and clamps the resulting rotation component of this 
		 local transform between the given values.

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
		void AddAndClampRotation(F32 x, F32 y, F32 z, 
			                     F32 min_angle, 
			                     F32 max_angle) noexcept {

			AddAndClampRotationX(x, min_angle, max_angle);
			AddAndClampRotationY(y, min_angle, max_angle);
			AddAndClampRotationZ(z, min_angle, max_angle);
		}

		/**
		 Adds the given rotation component to the rotation component of this 
		 local transform and clamps the resulting rotation component of this 
		 local transform between the given values.

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
		void AddAndClampRotation(const F32x3& rotation, 
			                     F32 min_angle, 
			                     F32 max_angle) noexcept {

			AddAndClampRotation(rotation.m_x, 
				                rotation.m_y, 
				                rotation.m_z, 
				                min_angle, 
				                max_angle);
		}

		/**
		 Adds the given rotation component to the rotation component of this 
		 local transform and clamps the resulting rotation component of this 
		 local transform between the given values.

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
		void XM_CALLCONV AddAndClampRotation(FXMVECTOR rotation, 
			                                 F32 min_angle, 
			                                 F32 max_angle) noexcept {

			AddAndClampRotation(XMVectorGetX(rotation), 
				                XMVectorGetY(rotation), 
				                XMVectorGetZ(rotation), 
				                min_angle, 
				                max_angle);
		}

		/**
		 Returns the x-value of the rotation component of this local transform.

		 @return		The x-value of the rotation component of this 
						local transform.
		 */
		[[nodiscard]]
		F32 GetRotationX() const noexcept {
			return m_rotation.m_x;
		}
		
		/**
		 Returns the y-value of the rotation component of this local transform.

		 @return		The y-value of the rotation component of this 
						local transform.
		 */
		[[nodiscard]]
		F32 GetRotationY() const noexcept {
			return m_rotation.m_y;
		}
		
		/**
		 Returns the z-value of the rotation component of this local transform.

		 @return		The z-value of the rotation component of this 
						local transform.
		 */
		[[nodiscard]]
		F32 GetRotationZ() const noexcept {
			return m_rotation.m_z;
		}
		
		/**
		 Returns the rotation component of this local transform.

		 @return		The rotation component of this local transform.
		 */
		[[nodiscard]]
		const F32x3 GetRotation() const noexcept {
			return m_rotation;
		}
		
		/**
		 Returns the rotation component of this local transform.

		 @return		The rotation component of this local transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetRotationV() const noexcept {
			return XMLoad(m_rotation);
		}

		/**
		 Returns the object-to-parent rotation quaternion of this local 
		 transform.

		 @return		The object-to-parent rotation quaternion of this local 
						transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectToParentRotationQuaternion() const noexcept {
			// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
			return XMQuaternionRotationRollPitchYaw(GetRotationV());
		}

		/**
		 Returns the parent-to-object rotation quaternion of this local 
		 transform.

		 @return		The parent-to-object rotation quaternion of this local 
						transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentToObjectRotationQuaternion() const noexcept {
			return XMQuaternionInverseRotationRollPitchYaw(GetRotationV());
		}

		/**
		 Returns the object-to-parent rotation matrix of this local transform.

		 @return		The object-to-parent rotation matrix of this local 
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentRotationMatrix() const noexcept {
			// Rz (Roll) . Rx (Pitch) . Ry (Yaw)
			return XMMatrixRotationRollPitchYaw(GetRotationV());
		}

		/**
		 Returns the parent-to-object rotation matrix of this local transform.

		 @return		The parent-to-object rotation matrix of this local 
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectRotationMatrix() const noexcept {
			return XMMatrixInverseRotationRollPitchYaw(GetRotationV());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Sets the x-value of the scale component of this local transform to the 
		 given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(F32 x) noexcept {
			m_scale.m_x = x;
		}
		
		/**
		 Sets the y-value of the scale component of this local transform to the 
		 given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(F32 y) noexcept {
			m_scale.m_y = y;
		}
		
		/**
		 Sets the z-value of the scale component of this local transform to the 
		 given value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(F32 z) noexcept {
			m_scale.m_z = z;
		}

		/**
		 Sets the scale component of this local transform to the given scale 
		 component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(F32 s) noexcept {
			SetScale(s, s, s);
		}
		
		/**
		 Sets the scale component of this local transform to the given scale 
		 component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScale(F32 x, F32 y, F32 z) noexcept {
			SetScaleX(x);
			SetScaleY(y);
			SetScaleZ(z);
		}
		
		/**
		 Sets the scale component of this local transform to the given scale 
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void SetScale(F32x3 scale) noexcept {
			m_scale = std::move(scale);
		}

		/**
		 Sets the scale component of this local transform to the given scale 
		 component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			m_scale = XMStore< F32x3 >(scale);
		}

		/**
		 Adds the given x-value to the scale component of this local transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(F32 x) noexcept {
			m_scale.m_x += x;
		}
		
		/**
		 Adds the given y-value to the scale component of this local transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(F32 y) noexcept {
			m_scale.m_y += y;
		}
		
		/**
		 Adds the given z-value to the scale component of this local transform.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(F32 z) noexcept {
			m_scale.m_z += z;
		}

		/**
		 Adds the given scale component to the scale component of this 
		 local transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(F32 s) noexcept {
			AddScale(s, s, s);
		}
		
		/**
		 Adds the given scale component to the scale component of this 
		 local transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScale(F32 x, F32 y, F32 z) noexcept {
			AddScaleX(x);
			AddScaleY(y);
			AddScaleZ(z);
		}
		
		/**
		 Adds the given scale component to the scale component of this 
		 local transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const F32x3& scale) noexcept {
			AddScale(scale.m_x, scale.m_y, scale.m_z);
		}

		/**
		 Adds the given scale component to the scale component of this 
		 local transform.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			AddScale(XMVectorGetX(scale), 
				     XMVectorGetY(scale), 
				     XMVectorGetZ(scale));
		}
		
		/**
		 Returns the x-value of the scale component of this local transform.

		 @return		The x-value of the scale component of this local 
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleX() const noexcept {
			return m_scale.m_x;
		}
		
		/**
		 Returns the y-value of the scale component of this local transform.

		 @return		The y-value of the scale component of this local 
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleY() const noexcept {
			return m_scale.m_y;
		}
		
		/**
		 Returns the z-value of the scale component of this local transform.

		 @return		The z-value of the scale component of this local 
						transform.
		 */
		[[nodiscard]]
		F32 GetScaleZ() const noexcept {
			return m_scale.m_z;
		}
		
		/**
		 Returns the scale component of this local transform.

		 @return		The scale component of this local transform.
		 */
		[[nodiscard]]
		const F32x3 GetScale() const noexcept {
			return m_scale;
		}
		
		/**
		 Returns the scale component of this local transform.

		 @return		The scale component of this local transform.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetScaleV() const noexcept {
			return XMLoad(m_scale);
		}

		/**
		 Returns the object-to-parent scale matrix of this local transform.

		 @return		The scale object-to-parent matrix of this local 
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentScaleMatrix() const noexcept {
			return XMMatrixScaling(GetScaleV());
		}

		/**
		 Returns the parent-to-object scale matrix of this local transform.

		 @return		The parent-to-object scale matrix of this local 
						transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectScaleMatrix() const noexcept {
			return XMMatrixInverseScaling(GetScaleV());
		}

		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this local transform 
		 expressed in object space coordinates.

		 @return		The position of the local origin of this local 
						transform expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectOrigin() const noexcept {
			return XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 Returns the direction of the local x-axis of this local transform 
		 expressed in object space coordinates.

		 @return		The direction of the local x-axis of this local 
						transform expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisX() const noexcept {
			return XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local y-axis of this local transform 
		 expressed in object space coordinates.

		 @return		The direction of the local y-axis of this local 
						transform expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisY() const noexcept {
			return XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local z-axis of this local transform 
		 expressed in object space coordinates.

		 @return		The direction of the local z-axis of this local 
						transform expressed in object space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetObjectAxisZ() const noexcept {
			return XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		}
		
		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the position of the local origin of this local transform 
		 expressed in parent space coordinates.

		 @return		The position of the local origin of this local 
						transform expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentOrigin() const noexcept {
			return GetObjectToParentMatrix().r[3];
		}

		/**
		 Returns the direction of the local x-axis of this local transform 
		 expressed in parent space coordinates.

		 @return		The direction of the local x-axis of this local 
						transform expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisX() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[0]);
		}
		
		/**
		 Returns the direction of the local y-axis of this transform local 
		 expressed in parent space coordinates.

		 @return		The direction of the local y-axis of this local 
						transform expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisY() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[1]);
		}
		
		/**
		 Returns the direction of the local z-axis of this transform local 
		 expressed in parent space coordinates.

		 @return		The direction of the local z-axis of this local 
						transform expressed in parent space coordinates.
		 */
		[[nodiscard]]
		const XMVECTOR XM_CALLCONV GetParentAxisZ() const noexcept {
			return XMVector3Normalize(GetObjectToParentMatrix().r[2]);
		}
		
		#pragma endregion

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------
		#pragma region

		/**
		 Returns the object-to-parent matrix of this local transform.

		 @return		The object-to-parent matrix of this local transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetObjectToParentMatrix() const noexcept {
			// Scale . Rotation . Translation
			return XMMatrixAffineTransformation(GetScaleV(), 
				                                GetRotationV(), 
				                                GetTranslationV());
		}

		/**
		 Returns the parent-to-object matrix of this local transform.

		 @return		The parent-to-object matrix of this local transform.
		 */
		[[nodiscard]]
		const XMMATRIX XM_CALLCONV GetParentToObjectMatrix() const noexcept {
			// Translation . Rotation . Scale
			return XMMatrixInverseAffineTransformation(GetScaleV(),
				                                       GetRotationV(),
				                                       GetTranslationV());
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
		 The translation component of this local transform.
		 */
		F32x3 m_translation;

		/**
		 The padding of this local transform.
		 */
		F32 m_padding0;

		/**
		 The rotation component (in radians) of this local transform.
		 */
		F32x3 m_rotation;

		/**
		 The padding of this local transform.
		 */
		F32 m_padding1;

		/**
		 The scale component of this local transform.
		 */
		F32x3 m_scale;

		/**
		 The padding of this local transform.
		 */
		F32 m_padding2;
	};

	static_assert(48 == sizeof(LocalTransform));
}