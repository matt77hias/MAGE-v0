#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "collection\collection.hpp"
#include "math\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// TransformNode
	//-------------------------------------------------------------------------

	/**
	 A struct of transform nodes.
	 */
	__declspec(align(16)) struct TransformNode final : public AlignedData< TransformNode > {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this transform node.
		 */
		~TransformNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given transform node to this transform node.

		 @param[in]		node
						A reference to the transform node to copy.
		 @return		A reference to the copy of the given transform node
						(i.e. this transform node).
		 */
		TransformNode &operator=(const TransformNode &node) = delete;

		/**
		 Moves the given transform node to this transform node.

		 @param[in]		node
						A reference to the transform node to move.
		 @return		A reference to the copy of the given transform node
						(i.e. this transform node).
		 */
		TransformNode &operator=(TransformNode &&node) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this transform node to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(float x) noexcept {
			m_transform->SetTranslationX(x);
			SetDirty();
		}
		
		/**
		 Sets the y-value of the translation component of this transform node to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(float y) noexcept {
			m_transform->SetTranslationY(y);
			SetDirty();
		}
		
		/**
		 Sets the z-value of the translation component of this transform node to the given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(float z) noexcept {
			m_transform->SetTranslationZ(z);
			SetDirty();
		}
		
		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(float x, float y, float z) noexcept {
			m_transform->SetTranslation(x, y, z);
			SetDirty();
		}
		
		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMFLOAT3 &translation) noexcept {
			m_transform->SetTranslation(translation);
			SetDirty();
		}
		
		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(XMFLOAT3 &&translation) noexcept {
			m_transform->SetTranslation(std::move(translation));
			SetDirty();
		}

		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		translation
						The translation component.
		 */
		void XM_CALLCONV SetTranslation(FXMVECTOR translation) noexcept {
			m_transform->SetTranslation(translation);
			SetDirty();
		}

		/**
		 Adds the given x-value to the translation component of this transform node.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(float x) noexcept {
			m_transform->AddTranslationX(x);
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the translation component of this transform node.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(float y) noexcept {
			m_transform->AddTranslationY(y);
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the translation component of this transform node.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(float z) noexcept {
			m_transform->AddTranslationZ(z);
			SetDirty();
		}
		
		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(float x, float y, float z) noexcept {
			m_transform->AddTranslation(x, y, z);
			SetDirty();
		}
		
		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT3 &translation) noexcept {
			m_transform->AddTranslation(translation);
			SetDirty();
		}
		
		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		translation
						The translation component to add.
		 */
		void XM_CALLCONV AddTranslation(FXMVECTOR translation) noexcept {
			m_transform->AddTranslation(translation);
			SetDirty();
		}

		/**
		 Returns the x-value of the translation component of this transform node.

		 @return		The x-value of the translation component of this transform node.
		 */
		float GetTranslationX() const noexcept {
			return m_transform->GetTranslationX();
		}
		
		/**
		 Returns the y-value of the translation component of this transform node.

		 @return		The y-value of the translation component of this transform node.
		 */
		float GetTranslationY() const noexcept {
			return m_transform->GetTranslationY();
		}
		
		/**
		 Returns the z-value of the translation component of this transform node.

		 @return		The z-value of the translation component of this transform node.
		 */
		float GetTranslationZ() const noexcept {
			return m_transform->GetTranslationZ();
		}
		
		/**
		 Returns the translation component of this transform node.

		 @return		The translation component of this transform node.
		 */
		const XMFLOAT3 GetTranslation() const noexcept {
			return m_transform->GetTranslation();
		}
		
		/**
		 Returns the object-to-parent translation matrix of this transform node.

		 @return		The object-to-parent translation matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentTranslationMatrix() const noexcept {
			return m_transform->GetObjectToParentTranslationMatrix();
		}

		/**
		 Returns the parent-to-object translation matrix of this transform node.

		 @return		The parent-to-object translation matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectTranslationMatrix() const noexcept {
			return m_transform->GetParentToObjectTranslationMatrix();
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation component of this transform node to the given value.

		 @param[in]		x
						The x-value of the rotation component.
		 */
		void SetRotationX(float x) noexcept {
			m_transform->SetRotationX(x);
			SetDirty();
		}
		
		/**
		 Sets the y-value of the rotation component of this transform node to the given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(float y) noexcept {
			m_transform->SetRotationY(y);
			SetDirty();
		}
		
		/**
		 Sets the z-value of the rotation component of this transform node to the given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(float z) noexcept {
			m_transform->SetRotationZ(z);
			SetDirty();
		}
		
		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		x
						The x-value of the rotation component.
		 @param[in]		y
						 The y-value of the rotation component.
		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotation(float x, float y, float z) noexcept {
			m_transform->SetRotation(x, y, z);
			SetDirty();
		}
		
		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMFLOAT3 &rotation) noexcept {
			m_transform->SetRotation(rotation);
			SetDirty();
		}

		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(XMFLOAT3 &&rotation) noexcept {
			m_transform->SetRotation(std::move(rotation));
			SetDirty();
		}

		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		rotation
						The rotation component.
		 */
		void XM_CALLCONV SetRotation(FXMVECTOR rotation) noexcept {
			m_transform->SetRotation(rotation);
			SetDirty();
		}
		
		/**
		 Sets the rotation component to a rotation of the given angle around the given normal.

		 @param[in]		normal
						The normal.
		 @param[in]		angle
						The angle.
		 */
		void XM_CALLCONV SetRotationAroundDirection(FXMVECTOR normal, float angle) noexcept {
			m_transform->SetRotationAroundDirection(normal, angle);
			SetDirty();
		}
		
		/**
		 Adds the given x-value to the rotation component of this transform node.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(float x) noexcept {
			m_transform->AddRotationX(x);
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the rotation component of this transform node.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(float y) noexcept {
			m_transform->AddRotationY(y);
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the rotation component of this transform node.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(float z) noexcept {
			m_transform->AddRotationZ(z);
			SetDirty();
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotation(float x, float y, float z) noexcept {
			m_transform->AddRotation(x, y, z);
			SetDirty();
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMFLOAT3 &rotation) noexcept {
			m_transform->AddRotation(rotation);
			SetDirty();
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		rotation
						The rotation component to add.
		 */
		void XM_CALLCONV AddRotation(FXMVECTOR rotation) noexcept {
			m_transform->AddRotation(rotation);
			SetDirty();
		}

		/**
		 Adds the given x-value to the rotation component of this transform
		 and clamps the resulting rotation component of this transform 
		 between the given values.

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
		void AddAndClampRotationX(float x, float min_angle, float max_angle) noexcept {
			m_transform->AddAndClampRotationX(x, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Adds the given y-value to the rotation component of this transform
		 and clamps the resulting rotation component of this transform 
		 between the given values.

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
		void AddAndClampRotationY(float y, float min_angle, float max_angle) noexcept {
			m_transform->AddAndClampRotationY(y, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Adds the given z-value to the rotation component of this transform
		 and clamps the resulting rotation component of this transform 
		 between the given values.

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
		void AddAndClampRotationZ(float z, float min_angle, float max_angle) noexcept {
			m_transform->AddAndClampRotationZ(z, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Adds the given rotation component to the rotation component of 
		 this transform and clamps the resulting rotation component of 
		 this transform between the given values.

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
		void AddAndClampRotation(float x, float y, float z, 
			float min_angle, float max_angle) noexcept {

			m_transform->AddAndClampRotation(x, y, z, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Adds the given rotation component to the rotation component of 
		 this transform and clamps the resulting rotation component of 
		 this transform between the given values.

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
		void AddAndClampRotation(const XMFLOAT3 &rotation, 
			float min_angle, float max_angle) noexcept {

			m_transform->AddAndClampRotation(rotation, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Adds the given rotation component to the rotation component of 
		 this transform and clamps the resulting rotation component of 
		 this transform between the given values.

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
			float min_angle, float max_angle) noexcept {

			m_transform->AddAndClampRotation(rotation, min_angle, max_angle);
			SetDirty();
		}

		/**
		 Returns the x-value of the rotation component of this transform node.

		 @return		The x-value of the rotation component of this transform node.
		 */
		float GetRotationX() const noexcept {
			return m_transform->GetRotationX();
		}
		
		/**
		 Returns the y-value of the rotation component of this transform node.

		 @return		The y-value of the rotation component of this transform node.
		 */
		float GetRotationY() const noexcept {
			return m_transform->GetRotationY();
		}
		
		/**
		 Returns the z-value of the rotation component of this transform node.

		 @return		The z-value of the rotation component of this transform node.
		 */
		float GetRotationZ() const noexcept {
			return m_transform->GetRotationZ();
		}
		
		/**
		 Returns the rotation component of this transform node.

		 @return		The rotation component of this transform node.
		 */
		const XMFLOAT3 GetRotation() const noexcept {
			return m_transform->GetRotation();
		}
		
		/**
		 Returns the object-to-parent rotation matrix of this transform node.

		 @return		The object-to-parent rotation matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentRotationMatrix() const noexcept {
			return m_transform->GetObjectToParentRotationMatrix();
		}

		/**
		 Returns the parent-to-object rotation matrix of this transform node.

		 @return		The parent-to-object rotation matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectRotationMatrix() const noexcept {
			return m_transform->GetParentToObjectRotationMatrix();
		}

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the scale component of this transform node to the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(float x) noexcept {
			m_transform->SetScaleX(x);
			SetDirty();
		}
		
		/**
		 Sets the y-value of the scale component of this transform node to the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(float y) noexcept {
			m_transform->SetScaleY(y);
			SetDirty();
		}
		
		/**
		 Sets the z-value of the scale component of this transform node to the given value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(float z) noexcept {
			m_transform->SetScaleZ(z);
			SetDirty();
		}

		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(float s) noexcept {
			m_transform->SetScale(s);
			SetDirty();
		}
		
		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScale(float x, float y, float z) noexcept {
			m_transform->SetScale(x, y, z);
			SetDirty();
		}
		
		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMFLOAT3 &scale) noexcept {
			m_transform->SetScale(scale);
			SetDirty();
		}
		
		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(XMFLOAT3 &&scale) noexcept {
			m_transform->SetScale(std::move(scale));
			SetDirty();
		}

		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		scale
						The scale component.
		 */
		void XM_CALLCONV SetScale(FXMVECTOR scale) noexcept {
			m_transform->SetScale(scale);
			SetDirty();
		}

		/**
		 Adds the given x-value to the scale component of this transform node.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(float x) noexcept {
			m_transform->AddScaleX(x);
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the scale component of this transform node.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(float y) noexcept {
			m_transform->AddScaleY(y);
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the scale component of this transform node.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(float z) noexcept {
			m_transform->AddScaleZ(z);
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(float s) noexcept {
			m_transform->AddScale(s);
			SetDirty();
		}
		
		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScale(float x, float y, float z) noexcept {
			m_transform->AddScale(x, y, z);
			SetDirty();
		}
		
		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT3 &scale) noexcept {
			m_transform->AddScale(scale);
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		scale
						The scale component to add.
		 */
		void XM_CALLCONV AddScale(FXMVECTOR scale) noexcept {
			m_transform->AddScale(scale);
			SetDirty();
		}
		
		/**
		 Returns the x-value of the scale component of this transform node.

		 @return		The x-value of the scale component of this transform node.
		 */
		float GetScaleX() const noexcept {
			return m_transform->GetScaleX();
		}
		
		/**
		 Returns the y-value of the scale component of this transform node.

		 @return		The y-value of the scale component of this transform node.
		 */
		float GetScaleY() const noexcept {
			return m_transform->GetScaleY();
		}
		
		/**
		 Returns the z-value of the scale component of this transform node.

		 @return		The z-value of the scale component of this transform node.
		 */
		float GetScaleZ() const noexcept {
			return m_transform->GetScaleZ();
		}
		
		/**
		 Returns the scale component of this transform node.

		 @return		The scale component of this transform node.
		 */
		const XMFLOAT3 GetScale() const noexcept {
			return m_transform->GetScale();
		}
		
		/**
		 Returns the object-to-parent scale matrix of this transform node.

		 @return		The scale object-to-parent matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentScaleMatrix() const noexcept {
			return m_transform->GetObjectToParentScaleMatrix();
		}

		/**
		 Returns the parent-to-object scale matrix of this transform node.

		 @return		The parent-to-object scale matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectScaleMatrix() const noexcept {
			return m_transform->GetParentToObjectScaleMatrix();
		}

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform node expressed in object space coordinates.

		 @return		The position of the local origin of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectOrigin() const noexcept {
			return m_transform->GetObjectOrigin();
		}

		/**
		 Returns the direction of the local x-axis of this transform node expressed in object space coordinates.

		 @return		The direction of the local x-axis of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisX() const noexcept {
			return m_transform->GetObjectAxisX();
		}
		
		/**
		 Returns the direction of the local y-axis of this transform node expressed in object space coordinates.

		 @return		The direction of the local y-axis of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisY() const noexcept {
			return m_transform->GetObjectAxisY();
		}
		
		/**
		 Returns the direction of the local z-axis of this transform node expressed in object space coordinates.

		 @return		The direction of the local z-axis of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisZ() const noexcept {
			return m_transform->GetObjectAxisZ();
		}
		
		/**
		 Returns the local Cartesian axes system of this transform node in object space coordinates.

		 @return		The local Cartesian axes system of this transform node expressed in object space coordinates.
		 */
		const CartesianAxesSystem GetObjectAxes() const noexcept {
			return m_transform->GetObjectAxes();
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform node in object space coordinates.

		 @return		The local Cartesian coordinate system of this transform node expressed in object space coordinates.
		 */
		const CartesianCoordinateSystem GetObjectCoordinateSystem() const noexcept {
			return m_transform->GetObjectCoordinateSystem();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform node expressed in parent space coordinates.

		 @return		The position of the local origin of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentOrigin() const noexcept {
			return m_transform->GetParentOrigin();
		}

		/**
		 Returns the direction of the local x-axis of this transform node expressed in parent space coordinates.

		 @return		The direction of the local x-axis of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisX() const noexcept {
			return m_transform->GetParentAxisX();
		}
		
		/**
		 Returns the direction of the local y-axis of this transform node expressed in parent space coordinates.

		 @return		The direction of the local y-axis of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisY() const noexcept {
			return m_transform->GetParentAxisY();
		}
		
		/**
		 Returns the direction of the local z-axis of this transform node expressed in parent space coordinates.

		 @return		The direction of the local z-axis of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisZ() const noexcept {
			return m_transform->GetParentAxisZ();
		}
		
		/**
		 Returns the local Cartesian axes system of this transform node expressed in parent space coordinates.

		 @return		The local Cartesian axes system of this transform node expressed in parent space coordinates.
		 */
		const CartesianAxesSystem GetParentAxes() const noexcept {
			return m_transform->GetParentAxes();
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform node in parent space coordinates.

		 @return		The local Cartesian coordinate system of this transform node expressed in parent space coordinates.
		 */
		const CartesianCoordinateSystem GetParentCoordinateSystem() const noexcept {
			return m_transform->GetParentCoordinateSystem();
		}

		//---------------------------------------------------------------------
		// Member Methods: World Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform node expressed in world space coordinates.

		 @return		The position of the local origin of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldOrigin() const noexcept {
			return TransformObjectToWorld(GetObjectOrigin());
		}

		/**
		 Returns the direction of the local x-axis of this transform node expressed in world space coordinates.

		 @return		The direction of the local x-axis of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldAxisX() const noexcept {
			return TransformObjectToWorld(GetObjectAxisX());
		}

		/**
		 Returns the direction of the local y-axis of this transform node expressed in world space coordinates.

		 @return		The direction of the local y-axis of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldAxisY() const noexcept {
			return TransformObjectToWorld(GetObjectAxisY());
		}

		/**
		 Returns the direction of the local z-axis of this transform node expressed in world space coordinates.

		 @return		The direction of the local z-axis of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldAxisZ() const noexcept {
			return TransformObjectToWorld(GetObjectAxisZ());
		}

		/**
		 Returns the local Cartesian axes system of this transform node expressed in world space coordinates.

		 @return		The local Cartesian axes system of this transform node expressed in world space coordinates.
		 */
		const CartesianAxesSystem GetWorldAxes() const noexcept {
			return CartesianAxesSystem(GetWorldAxisX(), GetWorldAxisY(), GetWorldAxisZ());
		}

		/**
		 Returns the local Cartesian coordinate system of this transform node in world space coordinates.

		 @return		The local Cartesian coordinate system of this transform node expressed in world space coordinates.
		 */
		const CartesianCoordinateSystem GetWorldCoordinateSystem() const noexcept {
			return CartesianCoordinateSystem(GetWorldOrigin(), GetWorldAxes());
		}

		//---------------------------------------------------------------------
		// Member Methods: Camera Object Space
		//---------------------------------------------------------------------

		/**
		 Returns the local eye position of this transform node expressed in object space coordinates.

		 @return		The local eye position of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectEye() const noexcept {
			return GetObjectOrigin();
		}

		/**
		 Returns the local left direction of this transform node expressed in object space coordinates.

		 @return		The local left direction of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectLeft() const noexcept {
			return GetObjectAxisX();
		}
		
		/**
		 Returns the local up direction of this transform node expressed in object space coordinates.

		 @return		The local up direction of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectUp() const noexcept {
			return GetObjectAxisY();
		}
		
		/**
		 Returns the local forward direction of this transform node expressed in object space coordinates.

		 @return		The local forward direction of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectForward() const noexcept {
			return GetObjectAxisZ();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Camera World Space
		//---------------------------------------------------------------------

		/**
		 Returns the local eye position of this transform node expressed in world space coordinates.

		 @return		The local eye position of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldEye() const noexcept {
			return GetWorldOrigin();
		}

		/**
		 Returns the local left direction of this transform node expressed in world space coordinates.

		 @return		The local left direction of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldLeft() const noexcept {
			return GetWorldAxisX();
		}
		
		/**
		 Returns the local up direction of this transform node expressed in world space coordinates.

		 @return		The local up direction of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldUp() const noexcept {
			return GetWorldAxisY();
		}
		
		/**
		 Returns the local forward direction of this transform node expressed in world space coordinates.

		 @return		The local forward direction of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldForward() const noexcept {
			return GetWorldAxisZ();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------

		/**
		 Returns the object-to-parent matrix of this transform node.

		 @return		The object-to-parent matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentMatrix() const noexcept {
			return m_transform->GetObjectToParentMatrix();
		}

		/**
		 Returns the parent-to-object matrix of this transform node.

		 @return		The parent-to-object matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectMatrix() const noexcept {
			return m_transform->GetParentToObjectMatrix();
		}

		/**
		 Returns the object-to-world matrix of this transform node.

		 @return		The object-to-world matrix of this transform node.
		 */
		const XMMATRIX GetObjectToWorldMatrix() const noexcept {
			UpdateObjectToWorldMatrix();
			return m_object_to_world;
		}

		/**
		 Returns the world-to-object matrix of this transform node.

		 @return		The world-to-object matrix of this transform node.
		 */
		const XMMATRIX GetWorldToObjectMatrix() const noexcept {
			UpdateWorldToObjectMatrix();
			return m_world_to_object;
		}

		/**
		 Returns the view-to-world matrix of this transform node.

		 @return		The view-to-world matrix of this transform node.
		 @note			Transforms for cameras should not contain scaling components.
		 */
		const XMMATRIX GetViewToWorldMatrix() const noexcept {
			return GetObjectToWorldMatrix();
		}

		/**
		 Returns the world-to-view matrix of this transform node.

		 @return		The world-to-view matrix of this transform node.
		 @note			Transforms for cameras should not contain scaling components.
		 */
		const XMMATRIX GetWorldToViewMatrix() const noexcept {
			return GetWorldToObjectMatrix();
		}

		/**
		 Transforms the given vector expressed in object space coordinates to parent space coordinates.

		 @param[in]		vector
						The vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformObjectToParent(FXMVECTOR vector) const noexcept {
			return m_transform->TransformObjectToParent(vector);
		}

		/**
		 Transforms the given point expressed in object space coordinates to parent space coordinates.

		 @param[in]		point
						The point expressed in object space coordinates.
		 @return		The transformed point expressed in parent space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformObjectToParentPoint(FXMVECTOR point) const noexcept {
			return m_transform->TransformObjectToParentPoint(point);
		}

		/**
		 Transforms the given direction expressed in object space coordinates to parent space coordinates.

		 @param[in]		direction
						The direction expressed in object space coordinates.
		 @return		The transformed direction expressed in parent space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformObjectToParentDirection(FXMVECTOR direction) const noexcept {
			return m_transform->TransformObjectToParentDirection(direction);
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to object space coordinates.

		 @param[in]		vector
						The vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformParentToObject(FXMVECTOR vector) const noexcept {
			return m_transform->TransformParentToObject(vector);
		}

		/**
		 Transforms the given point expressed in parent space coordinates to object space coordinates.

		 @param[in]		point
						The point expressed in parent space coordinates.
		 @return		The transformed point expressed in object space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformParentToObjectPoint(FXMVECTOR point) const noexcept {
			return m_transform->TransformParentToObjectPoint(point);
		}

		/**
		 Transforms the given direction expressed in parent space coordinates to object space coordinates.

		 @param[in]		direction
						The direction expressed in parent space coordinates.
		 @return		The transformed direction expressed in object space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformParentToObjectDirection(FXMVECTOR direction) const noexcept {
			return m_transform->TransformParentToObjectDirection(direction);
		}

		/**
		 Transforms the given vector expressed in object space coordinates to world space coordinates.

		 @param[in]		vector
						The vector expressed in object space coordinates.
		 @return		The transformed vector expressed in world space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformObjectToWorld(FXMVECTOR vector) const noexcept {
			return XMVector4Transform(vector, GetObjectToWorldMatrix());
		}

		/**
		 Transforms the given point expressed in object space coordinates to world space coordinates.

		 @param[in]		point
						The point expressed in object space coordinates.
		 @return		The transformed point expressed in world space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformObjectToWorldPoint(FXMVECTOR point) const noexcept {
			return XMVector3TransformCoord(point, GetObjectToWorldMatrix());
		}

		/**
		 Transforms the given direction expressed in object space coordinates to world space coordinates.

		 @param[in]		direction
						The direction expressed in object space coordinates.
		 @return		The transformed direction expressed in world space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformObjectToWorldDirection(FXMVECTOR direction) const noexcept {
			return XMVector3TransformNormal(direction, GetObjectToWorldMatrix());
		}

		/**
		 Transforms the given vector expressed in world space coordinates to object space coordinates.

		 @param[in]		vector
						The vector expressed in world space coordinates.
		 @return		The transformed vector expressed in object space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformWorldToObject(FXMVECTOR vector) const noexcept {
			return XMVector4Transform(vector, GetWorldToObjectMatrix());
		}

		/**
		 Transforms the given point expressed in world space coordinates to object space coordinates.

		 @param[in]		point
						The point expressed in world space coordinates.
		 @return		The transformed point expressed in object space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformWorldToObjectPoint(FXMVECTOR point) const noexcept {
			return XMVector3TransformCoord(point, GetWorldToObjectMatrix());
		}

		/**
		 Transforms the direction vector expressed in world space coordinates to object space coordinates.

		 @param[in]		direction
						The direction expressed in world space coordinates.
		 @return		The transformed direction expressed in object space coordinates.
		 */
		const XMVECTOR XM_CALLCONV TransformWorldToObjectDirection(FXMVECTOR direction) const noexcept {
			return XMVector3TransformNormal(direction, GetWorldToObjectMatrix());
		}

	private:

		//---------------------------------------------------------------------
		// Friends
		//---------------------------------------------------------------------

		// Nodes are semantically very similar to TransformNodes. They only add
		// an extra indirection to the functionality provided by TransformNodes.
		// Instead of calling the methods of TransformNodes directly, one has to
		// first obtain a pointer to the TransformNode. 
		friend class Node;

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform node.
		 */
		explicit TransformNode();

		/**
		 Constructs a transform node from the given transform node.

		 @param[in]		node
						A reference to the transform node to copy.
		 */
		TransformNode(const TransformNode &node);

		/**
		 Constructs a transform node by moving the given transform node.

		 @param[in]		node
						A reference to the transform node to move.
		 */
		TransformNode(TransformNode &&node) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets this transform node to dirty.
		 */
		void SetDirty() const noexcept {
			m_dirty_object_to_world = true;
			m_dirty_world_to_object = true;
			
			// Sets the descendants of this transform node to dirty.
			ForEachChildTransformNode([](const TransformNode *transform_node) {
				transform_node->SetDirty();
			});
		}

		/**
		 Updates the object-to-world matrix of this transform node if dirty.
		 */
		void UpdateObjectToWorldMatrix() const noexcept;

		/**
		 Updates the world-to-object matrix of this transform node if dirty.
		 */
		void UpdateWorldToObjectMatrix() const noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Graph
		//---------------------------------------------------------------------

		/**
		 Checks whether this transform node has a parent node.

		 @return		@c true if this transform node has a parent node.
						@c false otherwise.
		 */
		bool HasParentNode() const noexcept {
			return m_parent != nullptr;
		}
		
		/**
		 Returns the parent node of this transform node.

		 @return		@c nullptr if this transform node has no parent node.
		 @return		A pointer to the parent node of this transform node.
		 */
		Node *GetParentNode() const noexcept {
			return m_parent;
		}
		
		/**
		 Returns the number of child nodes of this transform node.

		 @return		The number of child nodes of this transform node.
		 */
		size_t GetNumberOfChildNodes() const noexcept {
			m_childs.size();
		}
		
		/**
		 Checks whether this transform node contains the given node
		 as a child node.

		 @param[in]		node
						A pointer to the node.
		 @return		@c true if this transform node contains the
						given node as a child node.
						@c false otherwise.
		 */
		bool HasChildNode(SharedPtr< const Node > node) const;
		
		/**
		 Removes all child nodes from this transform node.
		 */
		void RemoveAllChildNodes() noexcept;
		
		/**
		 Traverses all child transform nodes of this transform node.

		 @tparam		ActionT
						An action to perform on all child 
						transform nodes of this transform node. 
						The action must accept (@c const) 
						@c TransformNode* values.
		 */
		template< typename ActionT >
		void ForEachChildTransformNode(ActionT action) const;
		
		/**
		 Traverses all descendant (childs included) transform nodes 
		 of this transform node.

		 @tparam		ActionT
						An action to perform on all descendant 
						transform nodes of this transform node. 
						The action must accept (@c const) 
						@c TransformNode* values.
		 */
		template< typename ActionT >
		void ForEachDescendantTransformNode(ActionT action) const;
		
		/**
		 Traverses all child nodes of this transform node.

		 @tparam		ActionT
						An action to perform on all child 
						nodes of this transform node. 
						The action must accept (@c const) 
						@c Node* values.
		 */
		template< typename ActionT >
		void ForEachChildNode(ActionT action) const;
		
		/**
		 Traverses all descendant (childs included) nodes
		 of this transform node.

		 @tparam		ActionT
						An action to perform on all descendant 
						nodes of this transform node. 
						The action must accept (@c const) 
						@c Node* values.
		 */
		template< typename ActionT >
		void ForEachDescendantNode(ActionT action) const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The transform of this transform node.
		 */
		SharedPtr< Transform > m_transform;

		/**
		 The parent transform node of this transform node.
		 */
		Node *m_parent;

		/**
		 The child transform nodes of this transform node.
		 */
		vector< SharedPtr< Node > > m_childs;

		/**
		 The cached object-to-world matrix of this transform node.
		 */
		mutable XMMATRIX m_object_to_world;

		/**
		 The cached world-to-object matrix of this transform node.
		 */
		mutable XMMATRIX m_world_to_object;

		/**
		 A flag indicating whether the object-to-world matrix
		 of this transform node are dirty.
		 */
		mutable bool m_dirty_object_to_world;

		/**
		 A flag indicating whether the world-to-object matrix
		 of this transform node are dirty.
		 */
		mutable bool m_dirty_world_to_object;
	};

	//-------------------------------------------------------------------------
	// Node
	//-------------------------------------------------------------------------

	/**
	 A class of nodes.
	 */
	class Node {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a node.
		 */
		Node();

		/**
		 Constructs a node from the given node.

		 @param[in]		node
						A reference to the node.
		 */
		Node(const Node &node);

		/**
		 Constructs a node by moving the given node.

		 @param[in]		node
						A reference to the node to move.
		 */
		Node(Node &&node);

		/**
		 Destructs this node.
		 */
		virtual ~Node();

		//---------------------------------------------------------------------
		// Assignment operators
		//---------------------------------------------------------------------

		/**
		 Copies the given node to this node.

		 @param[in]		node
						A reference to the node to copy.
		 @return		A reference to the copy of the given node
						(i.e. this node).
		 */
		Node &operator=(const Node &node) = delete;

		/**
		 Moves the given node to this node.

		 @param[in]		node
						A reference to the node to move.
		 @return		A reference to the moved node
						(i.e. this node).
		 */
		Node &operator=(Node &&node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this node.

		 @return		A pointer to the clone of this node.
		 */
		UniquePtr< Node > Clone() const {
			return CloneImplementation();
		}

		/**
		 Returns the transform of this node.

		 @return		A pointer to the transform of this node.
		 */
		TransformNode *GetTransform() noexcept {
			return m_transform.get();
		}
		
		/**
		 Returns the transform of this node.

		 @return		A pointer to the transform of this node.
		 */
		const TransformNode *GetTransform() const noexcept {
			return m_transform.get();
		}

		/**
		 Checks whether this node is active.

		 @return		@c true if this node is active.
						@c false otherwise (i.e. passive).
		 */
		bool IsActive() const noexcept {
			return m_active;
		}

		/**
		 Checks whether this node is passive.

		 @return		@c true if this node is passive.
						@c false otherwise (i.e. active).
		 */
		bool IsPassive() const noexcept {
			return !m_active;
		}

		/**
		 Activates this node (and its descendant nodes).
		 */
		void Activate() noexcept {
			SetActive(true);
		}

		/**
		 Deactives this node (and its descendant nodes).
		 */
		void Deactivate() noexcept {
			SetActive(false);
		}

		/**
		 Sets this node active flag to the given value.

		 @param[in]		active
						The active flag.
		 */
		void SetActive(bool active) noexcept;

		/**
		 Checks whether this node is terminated or not.

		 @return		@c true if this node is terminated.
						@c false otherwise.
		 */
		bool IsTerminated() const noexcept {
			return m_terminated;
		}

		/**
		 Terminates this node.
		 */
		void Terminate() noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Graph
		//---------------------------------------------------------------------

		/**
		 Checks whether this node has a parent node.

		 @return		@c true if this node has a parent node.
						@c false otherwise.
		 */
		bool HasParentNode() const noexcept {
			return m_transform->HasParentNode();
		}
		
		/**
		 Returns the parent node of this node.

		 @return		@c nullptr if this node has no parent node.
		 @return		A pointer to the parent node of this node.
		 */
		Node *GetParentNode() const noexcept {
			return m_transform->GetParentNode();
		}
		
		/**
		 Returns the number of child nodes of this node.

		 @return		The number of child nodes of this node.
		 */
		size_t GetNumberOfChildNodes() const noexcept {
			return m_transform->GetNumberOfChildNodes();
		}
		
		/**
		 Checks whether this node contains the given node
		 as a child node.

		 @param[in]		node
						A pointer to the node.
		 @return		@c true if this node contains the
						given node as a child node.
						@c false otherwise.
		 */
		bool HasChildNode(SharedPtr< const Node > node) const {
			return m_transform->HasChildNode(node);
		}
		
		/**
		 Adds the given node to the child nodes of this node.

		 @param[in]		node
						A pointer to the node to add.
		 */
		void AddChildNode(SharedPtr< Node > node);

		/**
		 Removes the given node from the child nodes of this node.

		 @param[in]		node
						A pointer to the node to remove.
		 */
		void RemoveChildNode(SharedPtr< Node > node);

		/**
		 Removes all child nodes from this node.
		 */
		void RemoveAllChildNodes() noexcept {
			return m_transform->RemoveAllChildNodes();
		}
		
		/**
		 Traverses all child nodes of this node.

		 @tparam		ActionT
						An action to perform on all child
						nodes of this node. The action must 
						accept (@c const) @c Node* values.
		*/
		template< typename ActionT >
		void ForEachChildNode(ActionT action) const {
			m_transform->ForEachChildNode(action);
		}
		
		/**
		 Traverses all descendant (childs included) nodes
		 of this transform node.

		 @tparam		ActionT
						An action to perform on all descendant
						nodes of this node. The action must 
						accept (@c const) @c Node* values.
		 */
		template< typename ActionT >
		void ForEachDescendantNode(ActionT action) const {
			m_transform->ForEachDescendantNode(action);
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Notifies this transform node of a change in activeness.
		 */
		virtual void OnActiveChange() noexcept;

		/**
		 Clones this node.

		 @return		A pointer to the clone of this node.
		 */
		virtual UniquePtr< Node > CloneImplementation() const;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the transform of this node.
		 */
		SharedPtr< TransformNode > m_transform;

		/**
		 A flag indicating whether this node is active or not (i.e. passive).
		 */
		bool m_active;

		/**
		 A flag indicating whether this node is terminated or not. 
		 */
		bool m_terminated;
	};

	//-------------------------------------------------------------------------
	// TransformNode
	//-------------------------------------------------------------------------

	inline void TransformNode::UpdateObjectToWorldMatrix() const noexcept {
		if (m_dirty_object_to_world) {
			if (HasParentNode()) {
				m_object_to_world = GetObjectToParentMatrix() * m_parent->GetTransform()->GetObjectToWorldMatrix();
			}
			else {
				m_object_to_world = GetObjectToParentMatrix();
			}

			m_dirty_object_to_world = false;
		}
	}

	inline void TransformNode::UpdateWorldToObjectMatrix() const noexcept {
		if (m_dirty_world_to_object) {
			if (HasParentNode()) {
				m_world_to_object = m_parent->GetTransform()->GetWorldToObjectMatrix() * GetParentToObjectMatrix();
			}
			else {
				m_world_to_object = GetParentToObjectMatrix();
			}

			m_dirty_world_to_object = false;
		}
	}
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.tpp"

#pragma endregion