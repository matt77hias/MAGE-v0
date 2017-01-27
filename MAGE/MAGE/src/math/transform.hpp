#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\coordinate_system.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of transforms.
	 */
	struct Transform final {

		/**
		 Constructs a transform from the given local Cartesian axes system.

		 @param[in]		axes
						The local Cartesian axes system.
		 */
		Transform(const CartesianAxesSystem &axes)
			: Transform(CartesianCoordinateSystem(axes)) {}

		/**
		 Constructs a transform from the given local Cartesian coordinate system.

		 @param[in]		coordinate_system
						The local Cartesian coordinate system.
		 */
		Transform(const CartesianCoordinateSystem &coordinate_system)
			: m_scale(XMFLOAT3(1.0f, 1.0f, 1.0f)) {
			
			// Calculate translation components.
			const XMVECTOR translation_v = coordinate_system.GetOrigin();
			XMStoreFloat3(&m_translation, translation_v);

			// Calculate rotation components.
			const float rotation_x = acosf(XMVectorGetByIndex(coordinate_system.GetAxisX(), 0));
			const float rotation_y = acosf(XMVectorGetByIndex(coordinate_system.GetAxisY(), 1));
			const float rotation_z = acosf(XMVectorGetByIndex(coordinate_system.GetAxisZ(), 2));
			m_rotation = XMFLOAT3(rotation_x, rotation_y, rotation_z);
		}
		
		/**
		 Constructs a transform from the given translation, rotation and scale component.

		 @param[in]		translation
						The translation component.
		 @param[in]		rotation
						The rotation component.
		 @param[in]		scale
						The scale component.
		 */
		Transform(const XMFLOAT3 &translation = { 0.0f, 0.0f, 0.0f }, const XMFLOAT3 &rotation = { 0.0f, 0.0f, 0.0f }, const XMFLOAT3 &scale = { 1.0f, 1.0f, 1.0f })
			: m_translation(translation), m_rotation(rotation), m_scale(scale) {}
		
		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						The transform.
		 */
		Transform(const Transform &transform)
			: m_translation(transform.m_translation), m_rotation(transform.m_rotation), m_scale(transform.m_scale) {}

		/**
		 Destructs this transform.
		 */
		~Transform() {}
		
		/**
		 Copies the given transform to this transform.

		 @param[in]		transform
						The transform to copy from.
		 @return		A reference to the copy of the given transform (i.e. this transform).
		 */
		Transform &operator=(const Transform &transform) {
			m_translation = transform.GetTranslation();
			m_rotation    = transform.GetRotation();
			m_scale       = transform.GetScale();
			return (*this);
		}

		/**
		 Sets the x-value of the translation component of this transform to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 @return		A reference to this transform.
		 */
		Transform &SetTranslationX(float x) {
			m_translation.x = x;
			return (*this);
		}
		
		/**
		 Sets the y-value of the translation component of this transform to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 @return		A reference to this transform.
		 */
		Transform &SetTranslationY(float y) {
			m_translation.y = y;
			return (*this);
		}
		
		/**
		 Sets the z-value of the translation component of this transform to the given value.

		 @param[in]		z
						The z-value of the translation component.
		 @return		A reference to this transform.
		 */
		Transform &SetTranslationZ(float z) {
			m_translation.z = z;
			return (*this);
		}
		
		/**
		 Sets the translation component of this transform to the given translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 @return		A reference to this transform.
		 */
		Transform &SetTranslation(float x, float y, float z) {
			m_translation.x = x;
			m_translation.y = y;
			m_translation.z = z;
			return (*this);
		}
		
		/**
		 Sets the translation component of this transform to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 @return		A reference to this transform.
		 */
		Transform &SetTranslation(const XMFLOAT3 &translation) {
			m_translation.x = translation.x;
			m_translation.y = translation.y;
			m_translation.z = translation.z;
			return (*this);
		}
		
		/**
		 Adds the given x-value to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(float x) {
			m_translation.x += x;
		}
		
		/**
		 Adds the given y-value to the translation component of this transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(float y) {
			m_translation.y += y;
		}
		
		/**
		 Adds the given z-value to the translation component of this transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(float z) {
			m_translation.z += z;
		}
		
		/**
		 Adds the given translation component to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 @param[in]		y
						The y-value of the translation component to add.
		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslation(float x, float y, float z) {
			m_translation.x += x;
			m_translation.y += y;
			m_translation.z += z;
		}
		
		/**
		 Adds the given translation component to the translation component of this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT3 &translation) {
			m_translation.x += translation.x;
			m_translation.y += translation.y;
			m_translation.z += translation.z;
		}
		
		/**
		 Returns the x-value of the translation component of this transform.

		 @return		The x-value of the translation component of this transform.
		 */
		float GetTranslationX() const {
			return m_translation.x;
		}
		
		/**
		Returns the y-value of the translation component of this transform.

		 @return		The y-value of the translation component of this transform.
		 */
		float GetTranslationY() const {
			return m_translation.y;
		}
		
		/**
		 Returns the z-value of the translation component of this transform.

		 @return		The z-value of the translation component of this transform.
		 */
		float GetTranslationZ() const {
			return m_translation.z;
		}
		
		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		XMFLOAT3 GetTranslation() const {
			return m_translation;
		}
		
		/**
		 Returns the translation matrix of this transform.

		 @return		The translation matrix of this transform.
		 */
		XMMATRIX GetTranslationMatrix() const {
			return XMMatrixTranslationFromVector(XMLoadFloat3(&m_translation));
		}

		/**
		 Sets the x-value of the rotation component of this transform to the given value.

		 @param[in]		x
						The x-value of the rotation component.
		 @return		A reference to this transform.
		 */
		Transform &SetRotationX(float x) {
			m_rotation.x = x;
			return (*this);
		}
		
		/**
		 Sets the y-value of the rotation component of this transform to the given value.

		 @param[in]		y
						The y-value of the rotation component.
		 @return		A reference to this transform.
		 */
		Transform &SetRotationY(float y) {
			m_rotation.y = y;
			return (*this);
		}
		
		/**
		 Sets the z-value of the rotation component of this transform to the given value.

		 @param[in]		z
						The z-value of the rotation component.
		 @return		A reference to this transform.
		 */
		Transform &SetRotationZ(float z) {
			m_rotation.z = z;
			return (*this);
		}
		
		/**
		 Sets the rotation component of this transform to the given rotation component.

		 @param[in]		x
						The x-value of the rotation component.
		 @param[in]		y
						 The y-value of the rotation component.
		 @param[in]		z
						The z-value of the rotation component.
		 @return		A reference to this transform.
		 */
		Transform &SetRotation(float x, float y, float z) {
			m_rotation.x = x;
			m_rotation.y = y;
			m_rotation.z = z;
			return (*this);
		}
		
		/**
		 Sets the rotation component of this transform to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 @return		A reference to this transform.
		 */
		Transform &SetRotation(const XMFLOAT3 &rotation) {
			m_rotation.x = rotation.x;
			m_rotation.y = rotation.y;
			m_rotation.z = rotation.z;
			return (*this);
		}
		
		/**
		 Sets the rotation component to a rotation of the given angle around the given normal.

		 @param[in]		normal
						A reference to the normal.
		 @param[in]		angle
						The angle.
		 @return		A reference to this transform.
		 */
		Transform &SetRotationAroundDirection(const XMVECTOR &normal, float angle) {
			const XMMATRIX rotation_m = XMMatrixRotationNormal(normal, angle);
			XMFLOAT4X4 rotation;
			XMStoreFloat4x4(&rotation, rotation_m);

			// cosf function instead of sinf in case the angles are greater than [-1,1]
			m_rotation.y = -asinf(rotation._32);
			const float cp = cosf(m_rotation.y);
			const float cr = rotation._22 / cp;
			m_rotation.z = acosf(cr);
			const float cy = rotation._33 / cp;
			m_rotation.x = acosf(cy);

			return (*this);
		}
		
		/**
		 Adds the given x-value to the rotation component of this transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(float x) {
			m_rotation.x += x;
		}
		
		/**
		 Adds the given y-value to the rotation component of this transform.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(float y) {
			m_rotation.y += y;
		}
		
		/**
		 Adds the given z-value to the rotation component of this transform.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(float z) {
			m_rotation.z += z;
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 @param[in]		y
						The y-value of the rotation component to add.
		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotation(float x, float y, float z) {
			m_rotation.x += x;
			m_rotation.y += y;
			m_rotation.z += z;
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMFLOAT3 &rotation) {
			m_rotation.x += rotation.x;
			m_rotation.y += rotation.y;
			m_rotation.z += rotation.z;
		}
		
		/**
		 Returns the x-value of the rotation component of this transform.

		 @return		The x-value of the rotation component of this transform.
		 */
		float GetRotationX() const {
			return m_rotation.x;
		}
		
		/**
		 Returns the y-value of the rotation component of this transform.

		 @return		The y-value of the rotation component of this transform.
		 */
		float GetRotationY() const {
			return m_rotation.y;
		}
		
		/**
		 Returns the z-value of the rotation component of this transform.

		 @return		The z-value of the rotation component of this transform.
		 */
		float GetRotationZ() const {
			return m_rotation.z;
		}
		
		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		XMFLOAT3 GetRotation() const {
			return m_rotation;
		}
		
		/**
		 Returns the rotation matrix of this transform.

		 @return		The rotation matrix of this transform.
		 */
		XMMATRIX GetRotationMatrix() const {
			return XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotation));
		}

		/**
		 Sets the x-value of the scale component of this transform to the given value.

		 @param[in]		x
						The x-value of the scale component.
		 @return		A reference to this transform.
		 */
		Transform &SetScaleX(float x) {
			m_scale.x = x;
			return (*this);
		}
		
		/**
		 Sets the y-value of the scale component of this transform to the given value.

		 @param[in]		y
						The y-value of the scale component.
		 @return		A reference to this transform.
		 */
		Transform &SetScaleY(float y) {
			m_scale.y = y;
			return (*this);
		}
		
		/**
		 Sets the z-value of the scale component of this transform to the given value.

		 @param[in]		z
						The z-value of the scale component.
		 @return		A reference to this transform.
		 */
		Transform &SetScaleZ(float z) {
			m_scale.z = z;
			return (*this);
		}
		
		/**
		 Sets the scale component of this transform to the given scale component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 @param[in]		z
						The z-value of the scale component.
		 @return		A reference to this transform.
		 */
		Transform &SetScale(float x, float y, float z) {
			m_scale.x = x;
			m_scale.y = y;
			m_scale.z = z;
			return (*this);
		}
		
		/**
		 Sets the scale component of this transform to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 @return		A reference to this transform.
		 */
		Transform &SetScale(const XMFLOAT3 &scale) {
			m_scale.x = scale.x;
			m_scale.y = scale.y;
			m_scale.z = scale.z;
			return (*this);
		}
		
		/**
		 Adds the given x-value to the scale component of this transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(float x) {
			m_scale.x += x;
		}
		
		/**
		 Adds the given y-value to the scale component of this transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(float y) {
			m_scale.y += y;
		}
		
		/**
		 Adds the given z-value to the scale component of this transform.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(float z) {
			m_scale.z += z;
		}
		
		/**
		 Adds the given scale component to the scale component of this transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 @param[in]		y
						The y-value of the scale component to add.
		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScale(float x, float y, float z) {
			m_scale.x += x;
			m_scale.y += y;
			m_scale.z += z;
		}
		
		/**
		 Adds the given scale component to the scale component of this transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT3 &scale) {
			m_scale.x += scale.x;
			m_scale.y += scale.y;
			m_scale.z += scale.z;
		}
		
		/**
		 Returns the x-value of the scale component of this transform.

		 @return		The x-value of the scale component of this transform.
		 */
		float GetScaleX() const {
			return m_scale.x;
		}
		
		/**
		 Returns the y-value of the scale component of this transform.

		 @return		The y-value of the scale component of this transform.
		 */
		float GetScaleY() const {
			return m_scale.y;
		}
		
		/**
		 Returns the z-value of the scale component of this transform.

		 @return		The z-value of the scale component of this transform.
		 */
		float GetScaleZ() const {
			return m_scale.z;
		}
		
		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		XMFLOAT3 GetScale() const {
			return m_scale;
		}
		
		/**
		 Returns the scale matrix of this transform.

		 @return		The scale matrix of this transform.
		 */
		XMMATRIX GetScaleMatrix() const {
			return XMMatrixScalingFromVector(XMLoadFloat3(&m_scale));
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed in local space coordinates.

		 @return		The direction of the local x-axis of this transform expressed in local space coordinates.
		 */
		XMVECTOR GetLocalAxisX() const {
			return XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local y-axis of this transform expressed in local space coordinates.

		 @return		The direction of the local y-axis of this transform expressed in local space coordinates.
		 */
		XMVECTOR GetLocalAxisY() const {
			return XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local z-axis of this transform expressed in local space coordinates.

		 @return		The direction of the local z-axis of this transform expressed in local space coordinates.
		 */
		XMVECTOR GetLocalAxisZ() const {
			return XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		}
		
		/**
		 Returns the local Cartesian axes system of this transform in local space coordinates.

		 @return		The local Cartesian axes system of this transform expressed in local space coordinates.
		 */
		CartesianAxesSystem GetLocalAxes() const {
			return CartesianAxesSystem(GetLocalAxisX(), GetLocalAxisY(), GetLocalAxisZ());
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform in local space coordinates.

		 @return		The local Cartesian coordinate system of this transform expressed in local space coordinates.
		 */
		CartesianCoordinateSystem GetLocalCoordinateSystem() const {
			return CartesianCoordinateSystem(GetLocalAxes());
		}
		
		/**
		 Returns the direction of the local x-axis of this transform expressed in world space coordinates.

		 @return		The direction of the local x-axis of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldAxisX() const {
			return TransformObjectToWorldDirection(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));
		}
		
		/**
		 Returns the direction of the local y-axis of this transform expressed in world space coordinates.

		 @return		The direction of the local y-axis of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldAxisY() const {
			return TransformObjectToWorldDirection(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
		}
		
		/**
		 Returns the direction of the local z-axis of this transform expressed in world space coordinates.

		 @return		The direction of the local z-axis of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldAxisZ() const {
			return TransformObjectToWorldDirection(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
		}
		
		/**
		 Returns the local Cartesian axes system of this transform expressed in world space coordinates.

		 @return		The local Cartesian axes system of this transform expressed in world space coordinates.
		 */
		CartesianAxesSystem GetWorldAxes() const {
			return CartesianAxesSystem(GetWorldAxisX(), GetWorldAxisY(), GetWorldAxisZ());
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform in world space coordinates.

		 @return		The local Cartesian coordinate system of this transform expressed in world space coordinates.
		 */
		CartesianCoordinateSystem GetWorldCoordinateSystem() const {
			const XMVECTOR origin = XMLoadFloat3(&m_translation);
			return CartesianCoordinateSystem(origin, GetWorldAxes());
		}

		/**
		 Returns the local left direction of this transform expressed in local space coordinates.

		 @return		The local left direction of this transform expressed in local space coordinates.
		 */
		XMVECTOR GetLocalLeft() const {
			return GetLocalAxisX();
		}
		
		/**
		 Returns the local up direction of this transform expressed in local space coordinates.

		 @return		The local up direction of this transform expressed in local space coordinates.
		 */
		XMVECTOR GetLocalUp() const {
			return GetLocalAxisY();
		}
		
		/**
		 Returns the local forward direction of this transform expressed in local space coordinates.

		 @return		The local forward direction of this transform expressed in local space coordinates.
		 */
		XMVECTOR GetLocalForward() const {
			return GetLocalAxisZ();
		}
		
		/**
		 Returns the local left direction of this transform expressed in world space coordinates.

		 @return		The local left direction of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldLeft() const {
			return GetWorldAxisX();
		}
		
		/**
		 Returns the local up direction of this transform expressed in world space coordinates.

		 @return		The local up direction of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldUp() const {
			return GetWorldAxisY();
		}
		
		/**
		 Returns the local forward direction of this transform expressed in world space coordinates.

		 @return		The local forward direction of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldForward() const {
			return GetWorldAxisZ();
		}
		
		/**
		 Returns the world-to-object matrix of this transform.

		 @return		The world-to-object matrix of this transform.
		 */
		XMMATRIX GetWorldToObjectMatrix() const {
			return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
		}
		
		/**
		 Returns the object-to-world matrix of this transform.

		 @return		The object-to-world matrix of this transform.
		 */
		XMMATRIX GetObjectToWorldMatrix() const {
			return GetInverseScaleMatrix() * GetInverseRotationMatrix() * GetInverseTranslationMatrix();
		}

		/**
		 Returns the world-to-view matrix of this transform.

		 @return		The world-to-view matrix of this transform.
		 */
		XMMATRIX GetWorldToViewMatrix() const {
			return GetTranslationMatrix() * GetRotationMatrix();
		}

	private:

		/**
		 Returns the inverse translation matrix of this transform.

		 @return		The inverse translation matrix of this transform.
		 */
		XMMATRIX GetInverseTranslationMatrix() const {
			return XMMatrixTranslationFromVector(XMVectorSet(-m_translation.x, -m_translation.y,-m_translation.z, 0.0f));
		}

		/**
		 Returns the inverse rotation matrix of this transform.

		 @return		The inverse rotation matrix of this transform.
		 */
		XMMATRIX GetInverseRotationMatrix() const {
			return XMMatrixRotationRollPitchYawFromVector(XMVectorSet(-m_rotation.x, -m_rotation.y, -m_rotation.z, 0.0f));
		}

		/**
		 Returns the inverse scale matrix of this transform.

		 @return		The inverse scale matrix of this transform.
		 */
		XMMATRIX GetInverseScaleMatrix() const {
			return XMMatrixScalingFromVector(XMVectorSet(1.0f / m_scale.x, 1.0f / m_scale.y, 1.0f / m_scale.z, 0.0f));
		}

		/**
		 Transforms the given direction expressed in the local coordinate space
		 of this transform to world coordinate space.

		 @param[in]		direction
						A reference to the direction expressed in the local coordinate space
						of this transform.
		 @return		The transformed (normalized) direction expressed in world coordinate space.
		 */
		XMVECTOR TransformObjectToWorldDirection(const XMVECTOR &direction) const {
			const XMMATRIX transformation = GetInverseScaleMatrix() * GetInverseRotationMatrix();
			return XMVector3Normalize(XMVector4Transform(direction, transformation));
		}

		/**
		 The translation component of this transform.
		 */
		XMFLOAT3 m_translation;

		/**
		 The rotation component (in radians) of this transform.
		 */
		XMFLOAT3 m_rotation;

		/**
		 The scale component of this transform.
		 */
		XMFLOAT3 m_scale;
	};
}