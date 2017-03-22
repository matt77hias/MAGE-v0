#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "collection\collection.hpp"
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

		//-------------------------------------------------------------------------
		// Construction
		//-------------------------------------------------------------------------

		/**
		 Constructs a transform from the given translation, rotation and scale component.

		 @param[in]		translation
						A reference to the translation component.
		 @param[in]		rotation
						A reference to the rotation component.
		 @param[in]		scale
						A reference to the scale component.
		 */
		Transform(const XMFLOAT3 &translation = { 0.0f, 0.0f, 0.0f }, const XMFLOAT3 &rotation = { 0.0f, 0.0f, 0.0f }, const XMFLOAT3 &scale = { 1.0f, 1.0f, 1.0f })
			: m_translation(translation), m_rotation(rotation), m_scale(scale) {
			const XMMATRIX &identity = XMMatrixIdentity();
			Update(identity, identity);
		}
		
		/**
		 Constructs a transform from the components of the given transform.

		 @param[in]		transform
						A reference to the transform.
		 */
		Transform(const Transform &transform)
			: Transform(transform.m_translation, transform.m_rotation, transform.m_scale) {}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform.
		 */
		Transform(Transform &&transform) = default;

		//-------------------------------------------------------------------------
		// Destruction
		//-------------------------------------------------------------------------

		/**
		 Destructs this transform.
		 */
		~Transform() {
			RemoveAllChilds();
		}
		
		//-------------------------------------------------------------------------
		// Copying
		//-------------------------------------------------------------------------

		/**
		 Copies the components of the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to copy from.
		 @return		A reference to the copy of the given transform
						(i.e. this transform).
		 */
		Transform &operator=(const Transform &transform) {
			SetComponents(transform);
			return (*this);
		}

		/**
		 Copies the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to copy from.
		 @return		A reference to the copy of the given transform
						(i.e. this transform).
		 */
		Transform &operator=(Transform &&transform) = default;

		//-------------------------------------------------------------------------
		// Tranbslation + Rotation + Scale
		//-------------------------------------------------------------------------

		/**
		 Sets the translation, rotation, scale component of this transform 
		 to the given components.

		 @param[in]		translation
						A reference to the translation component.
		 @param[in]		rotation
						A reference to the rotation component.
		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetComponents(const XMFLOAT3 &translation, const XMFLOAT3 &rotation, const XMFLOAT3 &scale) {
			m_translation = translation;
			m_rotation    = rotation;
			m_scale       = scale;
			Update();
		}

		/**
		 Sets the translation, rotation, scale component of this transform
		 to the components of the given transform..

		 @param[in]		transform
						A reference to the transform.
		 */
		void SetComponents(const Transform &transform) {
			SetComponents(transform.m_translation, transform.m_rotation, transform.m_scale);
		}

		//-------------------------------------------------------------------------
		// Translation
		//-------------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this transform to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(float x) {
			m_translation.x = x;
			Update();
		}
		
		/**
		 Sets the y-value of the translation component of this transform to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(float y) {
			m_translation.y = y;
			Update();
		}
		
		/**
		 Sets the z-value of the translation component of this transform to the given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(float z) {
			m_translation.z = z;
			Update();
		}
		
		/**
		 Sets the translation component of this transform to the given translation component.

		 @param[in]		x
						The x-value of the translation component.
		 @param[in]		y
						The y-value of the translation component.
		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslation(float x, float y, float z) {
			m_translation.x = x;
			m_translation.y = y;
			m_translation.z = z;
			Update();
		}
		
		/**
		 Sets the translation component of this transform to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMFLOAT3 &translation) {
			m_translation = translation;
			Update();
		}
		
		/**
		 Adds the given x-value to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(float x) {
			m_translation.x += x;
			Update();
		}
		
		/**
		 Adds the given y-value to the translation component of this transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(float y) {
			m_translation.y += y;
			Update();
		}
		
		/**
		 Adds the given z-value to the translation component of this transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(float z) {
			m_translation.z += z;
			Update();
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
			Update();
		}
		
		/**
		 Adds the given translation component to the translation component of this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT3 &translation) {
			AddTranslation(translation.x, translation.y, translation.z);
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

		//-------------------------------------------------------------------------
		// Rotation
		//-------------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation component of this transform to the given value.

		 @param[in]		x
						The x-value of the rotation component.
		 */
		void SetRotationX(float x) {
			m_rotation.x = x;
			Update();
		}
		
		/**
		 Sets the y-value of the rotation component of this transform to the given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(float y) {
			m_rotation.y = y;
			Update();
		}
		
		/**
		 Sets the z-value of the rotation component of this transform to the given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(float z) {
			m_rotation.z = z;
			Update();
		}
		
		/**
		 Sets the rotation component of this transform to the given rotation component.

		 @param[in]		x
						The x-value of the rotation component.
		 @param[in]		y
						 The y-value of the rotation component.
		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotation(float x, float y, float z) {
			m_rotation.x = x;
			m_rotation.y = y;
			m_rotation.z = z;
			Update();
		}
		
		/**
		 Sets the rotation component of this transform to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMFLOAT3 &rotation) {
			m_rotation = rotation;
			Update();
		}
		
		/**
		 Sets the rotation component to a rotation of the given angle around the given normal.

		 @param[in]		normal
						A reference to the normal.
		 @param[in]		angle
						The angle.
		 */
		void SetRotationAroundDirection(const XMVECTOR &normal, float angle) {
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

			Update();
		}
		
		/**
		 Adds the given x-value to the rotation component of this transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(float x) {
			m_rotation.x += x;
			Update();
		}
		
		/**
		 Adds the given y-value to the rotation component of this transform.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(float y) {
			m_rotation.y += y;
			Update();
		}
		
		/**
		 Adds the given z-value to the rotation component of this transform.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(float z) {
			m_rotation.z += z;
			Update();
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
			Update();
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMFLOAT3 &rotation) {
			AddRotation(rotation.x, rotation.y, rotation.z);
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

		//-------------------------------------------------------------------------
		// Scale
		//-------------------------------------------------------------------------

		/**
		 Sets the x-value of the scale component of this transform to the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(float x) {
			m_scale.x = x;
			Update();
		}
		
		/**
		 Sets the y-value of the scale component of this transform to the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(float y) {
			m_scale.y = y;
			Update();
		}
		
		/**
		 Sets the z-value of the scale component of this transform to the given value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(float z) {
			m_scale.z = z;
			Update();
		}
		
		/**
		 Sets the scale component of this transform to the given scale component.

		 @param[in]		x
						The x-value of the scale component.
		 @param[in]		y
						The y-value of the scale component.
		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScale(float x, float y, float z) {
			m_scale.x = x;
			m_scale.y = y;
			m_scale.z = z;
			Update();
		}
		
		/**
		 Sets the scale component of this transform to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMFLOAT3 &scale) {
			m_scale = scale;
			Update();
		}
		
		/**
		 Adds the given x-value to the scale component of this transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(float x) {
			m_scale.x += x;
			Update();
		}
		
		/**
		 Adds the given y-value to the scale component of this transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(float y) {
			m_scale.y += y;
			Update();
		}
		
		/**
		 Adds the given z-value to the scale component of this transform.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(float z) {
			m_scale.z += z;
			Update();
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
			Update();
		}
		
		/**
		 Adds the given scale component to the scale component of this transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT3 &scale) {
			AddScale(scale.x, scale.y, scale.z);
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

		//-------------------------------------------------------------------------
		// Object Space
		//-------------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform expressed in object space coordinates.

		 @return		The position of the local origin of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectOrigin() const {
			return XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed in object space coordinates.

		 @return		The direction of the local x-axis of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectAxisX() const {
			return XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local y-axis of this transform expressed in object space coordinates.

		 @return		The direction of the local y-axis of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectAxisY() const {
			return XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local z-axis of this transform expressed in object space coordinates.

		 @return		The direction of the local z-axis of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectAxisZ() const {
			return XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		}
		
		/**
		 Returns the local Cartesian axes system of this transform in object space coordinates.

		 @return		The local Cartesian axes system of this transform expressed in object space coordinates.
		 */
		CartesianAxesSystem GetObjectAxes() const {
			return CartesianAxesSystem(GetObjectAxisX(), GetObjectAxisY(), GetObjectAxisZ());
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform in object space coordinates.

		 @return		The local Cartesian coordinate system of this transform expressed in object space coordinates.
		 */
		CartesianCoordinateSystem GetObjectCoordinateSystem() const {
			return CartesianCoordinateSystem(GetObjectOrigin(), GetObjectAxes());
		}
		
		//-------------------------------------------------------------------------
		// Parent Space
		//-------------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform expressed in parent space coordinates.

		 @return		The position of the local origin of this transform expressed in parent space coordinates.
		 */
		XMVECTOR GetParentOrigin() const {
			return XMLoadFloat3(&m_translation);
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed in parent space coordinates.

		 @return		The direction of the local x-axis of this transform expressed in parent space coordinates.
		 */
		XMVECTOR GetParentAxisX() const {
			return TransformObjectToParentDirection(GetObjectAxisX());
		}
		
		/**
		 Returns the direction of the local y-axis of this transform expressed in parent space coordinates.

		 @return		The direction of the local y-axis of this transform expressed in parent space coordinates.
		 */
		XMVECTOR GetParentAxisY() const {
			return TransformObjectToParentDirection(GetObjectAxisY());
		}
		
		/**
		 Returns the direction of the local z-axis of this transform expressed in parent space coordinates.

		 @return		The direction of the local z-axis of this transform expressed in parent space coordinates.
		 */
		XMVECTOR GetParentAxisZ() const {
			return TransformObjectToParentDirection(GetObjectAxisZ());
		}
		
		/**
		 Returns the local Cartesian axes system of this transform expressed in parent space coordinates.

		 @return		The local Cartesian axes system of this transform expressed in parent space coordinates.
		 */
		CartesianAxesSystem GetParentAxes() const {
			return CartesianAxesSystem(GetParentAxisX(), GetParentAxisY(), GetParentAxisZ());
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform in parent space coordinates.

		 @return		The local Cartesian coordinate system of this transform expressed in parent space coordinates.
		 */
		CartesianCoordinateSystem GetParentCoordinateSystem() const {
			return CartesianCoordinateSystem(GetParentOrigin(), GetParentAxes());
		}

		//-------------------------------------------------------------------------
		// World Space
		//-------------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform expressed in world space coordinates.

		 @return		The position of the local origin of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldOrigin() const {
			return TransformObjectToWorld(GetObjectOrigin());
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed in world space coordinates.

		 @return		The direction of the local x-axis of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldAxisX() const {
			return TransformObjectToWorld(GetObjectAxisX());
		}

		/**
		 Returns the direction of the local y-axis of this transform expressed in world space coordinates.

		 @return		The direction of the local y-axis of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldAxisY() const {
			return TransformObjectToWorld(GetObjectAxisY());
		}

		/**
		 Returns the direction of the local z-axis of this transform expressed in world space coordinates.

		 @return		The direction of the local z-axis of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldAxisZ() const {
			return TransformObjectToWorld(GetObjectAxisZ());
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
			return CartesianCoordinateSystem(GetWorldOrigin(), GetWorldAxes());
		}

		//-------------------------------------------------------------------------
		// Camera Object Space
		//-------------------------------------------------------------------------

		/**
		 Returns the local eye position of this transform expressed in object space coordinates.

		 @return		The local eye position of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectEye() const {
			return GetObjectOrigin();
		}

		/**
		 Returns the local left direction of this transform expressed in object space coordinates.

		 @return		The local left direction of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectLeft() const {
			return GetObjectAxisX();
		}
		
		/**
		 Returns the local up direction of this transform expressed in object space coordinates.

		 @return		The local up direction of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectUp() const {
			return GetObjectAxisY();
		}
		
		/**
		 Returns the local forward direction of this transform expressed in object space coordinates.

		 @return		The local forward direction of this transform expressed in object space coordinates.
		 */
		XMVECTOR GetObjectForward() const {
			return GetObjectAxisZ();
		}
		
		//-------------------------------------------------------------------------
		// Camera World Space
		//-------------------------------------------------------------------------

		/**
		 Returns the local eye position of this transform expressed in world space coordinates.

		 @return		The local eye position of this transform expressed in world space coordinates.
		 */
		XMVECTOR GetWorldEye() const {
			return GetWorldOrigin();
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
		
		//-------------------------------------------------------------------------
		// Transformation
		//-------------------------------------------------------------------------

		/**
		 Returns the parent-to-object matrix of this transform.

		 @return		The parent-to-object matrix of this transform.
		 */
		XMMATRIX GetParentToObjectMatrix() const {
			return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
		}
		
		/**
		 Returns the object-to-parent matrix of this transform.

		 @return		The object-to-parent matrix of this transform.
		 */
		XMMATRIX GetObjectToParentMatrix() const {
			return GetInverseScaleMatrix() * GetInverseRotationMatrix() * GetInverseTranslationMatrix();
		}

		/**
		 Returns the world-to-object matrix of this transform.

		 @return		The world-to-object matrix of this transform.
		 */
		XMMATRIX GetWorldToObjectMatrix() const {
			return m_world_to_object;
		}

		/**
		 Returns the object-to-world matrix of this transform.

		 @return		The object-to-world matrix of this transform.
		 */
		XMMATRIX GetObjectToWorldMatrix() const {
			return m_object_to_world;
		}
		
		/**
		 Returns the parent-to-view matrix of this transform.

		 @return		The parent-to-view matrix of this transform.
		 @note			Transforms for cameras should not contain scaling components.
		 */
		XMMATRIX GetWorldToViewMatrix() const {
			return m_world_to_object;
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to object space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space coordinates.
		 */
		XMVECTOR TransformParentToObject(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetParentToObjectMatrix());
		}

		/**
		 Transforms the given vector expressed in object space coordinates to parent space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space coordinates.
		 */
		XMVECTOR TransformObjectToParent(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given vector expressed in world space coordinates to object space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in world space coordinates.
		 @return		The transformed vector expressed in object space coordinates.
		 */
		XMVECTOR TransformWorldToObject(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetWorldToObjectMatrix());
		}

		/**
		 Transforms the given vector expressed in object space coordinates to world space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in object space coordinates.
		 @return		The transformed vector expressed in world space coordinates.
		 */
		XMVECTOR TransformObjectToWorld(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetObjectToWorldMatrix());
		}

		//-------------------------------------------------------------------------
		// Childs
		//-------------------------------------------------------------------------

		/**
		 Checks whether this transform contains the given transform as a child transform.

		 @return		@c true if this transform contains the given transform as a child transform.
						@c false otherwise.
		 */
		bool ContainsChild(const SharedPtr< Transform > child) const {
			return m_childs.find(child) != m_childs.cend();
		}

		/**
		 Adds the given child transform to the child transforms of this transform.

		 @pre			@a child may not refer to @c nullptr.
		 @pre			@a child may not refer to @c this.		
		 @param[in]		child
						A pointer to the child transform.
		 */
		void AddChild(SharedPtr< Transform > child);

		/**
		 Removes the given child transform from the child transforms of this transform.

		 @param[in]		child
						A pointer to the child transform.
		 */
		void RemoveChild(SharedPtr< Transform > child);

		/**
		 Removes and destructs all child transforms of this transform.
		 */
		void RemoveAllChilds() {
			m_childs.clear();
		}

		/**
		 Returns the total number of child transforms of this transform.

		 @return		The total number of child transforms of this transform.
		 */
		size_t GetNumberOfChilds() const {
			return m_childs.size();
		}

		/**
		 Returns an iterator to the beginning of the childs of this transform.

		 @return		An iterator to the beginning of the childs of this transform.
		 */
		set< SharedPtr< Transform > >::iterator begin() {
			return m_childs.begin();
		}

		/**
		 Returns an iterator to the end of the childs of this transform.

		 @return		An iterator to the end of the childs of this transform.
		 */
		set< SharedPtr< Transform > >::iterator end() {
			return m_childs.end();
		}

		/**
		 Returns a constant iterator to the beginning of the childs of this transform.

		 @return		A constant iterator to the beginning of the childs of this transform.
		 */
		set< SharedPtr< Transform > >::const_iterator cbegin() const {
			return m_childs.cbegin();
		}

		/**
		 Returns a constant iterator to the end of the childs of this transform.

		 @return		A constant iterator to the end of the childs of this transform.
		 */
		set< SharedPtr< Transform > >::const_iterator cend() const {
			return m_childs.cend();
		}

	private:

		/**
		 Returns the inverse translation matrix of this transform.

		 @return		The inverse translation matrix of this transform.
		 */
		XMMATRIX GetInverseTranslationMatrix() const {
			return XMMatrixTranslationFromVector(XMVectorSet(-m_translation.x, -m_translation.y, -m_translation.z, 0.0f));
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
		 Transforms the given direction expressed in object space coordinates to parent space coordinates.

		 @param[in]		direction
						A reference to the direction expressed in object space coordinates.
		 @return		The transformed (normalized) direction expressed in parent space coordinates.
		 */
		XMVECTOR TransformObjectToParentDirection(const XMVECTOR &direction) const {
			const XMMATRIX transformation = GetInverseScaleMatrix() * GetInverseRotationMatrix();
			return XMVector3Normalize(XMVector4Transform(direction, transformation));
		}

		/**
		 Updates the world-to-object and object-to-world matrices, and 
		 updates all the childs of this transform.
		 */
		void Update();

		/**
		 Updates the world-to-object and object-to-world matrices, and
		 updates the world-to-parent and parent-to-world matrices of this transform
		 based on the given world-to-parent and parent-to-world matrices of this transform.

		 @param[in]		world_to_parent
						A reference to the world-to-parent matrix.
		 @param[in]		parent_to_world
						A reference to the parent-to-world matrix.	
		 */
		void Update(const XMMATRIX &world_to_parent, const XMMATRIX &parent_to_world) {
			m_world_to_parent = world_to_parent;
			m_parent_to_world = parent_to_world;
			Update();
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

		/**
		 The world-to-object matrix of this transform.
		 */
		XMMATRIX m_world_to_object;

		/**
		 The object-to-world matrix of this transform.
		 */
		XMMATRIX m_object_to_world;

		/**
		 The world-to-parent matrix of this transform.
		 */
		XMMATRIX m_world_to_parent;

		/**
		 The parent-to-world matrix of this transform.
		 */
		XMMATRIX m_parent_to_world;

		/**
		 A set containing the child transforms of this transform.
		 */
		set< SharedPtr< Transform >, std::less<> > m_childs;
	};
}