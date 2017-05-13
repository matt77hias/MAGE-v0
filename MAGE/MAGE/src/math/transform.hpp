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
	__declspec(align(16)) struct Transform final : public AlignedData< Transform > {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform from the given translation, rotation and scale component.

		 @param[in]		translation
						A reference to the translation component.
		 @param[in]		rotation
						A reference to the rotation component.
		 @param[in]		scale
						A reference to the scale component.
		 */
		explicit Transform(const XMFLOAT3 &translation = { 0.0f, 0.0f, 0.0f }, 
			const XMFLOAT3 &rotation = { 0.0f, 0.0f, 0.0f }, 
			const XMFLOAT3 &scale = { 1.0f, 1.0f, 1.0f })
			: m_translation(translation), m_rotation(rotation), m_scale(scale) {
			SetDirty();
		}
		
		/**
		 Constructs a transform from the given translation, rotation and scale component.

		 @param[in]		translation
						A reference to the translation component.
		 @param[in]		rotation
						A reference to the rotation component.
		 @param[in]		scale
						A reference to the scale component.
		 */
		explicit Transform(const XMVECTOR &translation, 
			const XMVECTOR &rotation, 
			const XMVECTOR &scale)
			: m_translation(), m_rotation(), m_scale() {
			SetTranslation(translation);
			SetRotation(rotation);
			SetScale(scale);
		}

		/**
		 Constructs a transform from the given transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 */
		Transform(const Transform &transform)
			: m_translation(transform.m_translation), 
			m_rotation(transform.m_rotation),
			m_scale(transform.m_scale) {
			SetDirty();
		}

		/**
		 Constructs a transform by moving the given transform.

		 @param[in]		transform
						A reference to the transform to move.
		 */
		Transform(Transform &&transform) noexcept
			: m_translation(std::move(transform.m_translation)),
			m_rotation(std::move(transform.m_rotation)),
			m_scale(std::move(transform.m_scale)) {
			SetDirty();
		}

		/**
		 Destructs this transform.
		 */
		~Transform() = default;
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to copy.
		 @return		A reference to the copy of the given transform
						(i.e. this transform).
		 */
		Transform &operator=(const Transform &transform) {
			m_translation = transform.m_translation;
			m_rotation    = transform.m_rotation;
			m_scale       = transform.m_scale;
			SetDirty();
			return (*this);
		}

		/**
		 Moves the given transform to this transform.

		 @param[in]		transform
						A reference to the transform to move.
		 @return		A reference to the moved transform
						(i.e. this transform).
		 */
		Transform &operator=(Transform &&transform) noexcept {
			m_translation = std::move(transform.m_translation);
			m_rotation    = std::move(transform.m_rotation);
			m_scale       = std::move(transform.m_scale);
			SetDirty();
			return (*this);
		}

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this transform to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(float x) noexcept {
			m_translation.x = x;
			SetDirty();
		}
		
		/**
		 Sets the y-value of the translation component of this transform to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(float y) noexcept {
			m_translation.y = y;
			SetDirty();
		}
		
		/**
		 Sets the z-value of the translation component of this transform to the given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(float z) noexcept {
			m_translation.z = z;
			SetDirty();
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
		void SetTranslation(float x, float y, float z) noexcept {
			m_translation.x = x;
			m_translation.y = y;
			m_translation.z = z;
			SetDirty();
		}
		
		/**
		 Sets the translation component of this transform to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMFLOAT3 &translation) noexcept {
			m_translation = translation;
			SetDirty();
		}
		
		/**
		 Sets the translation component of this transform to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMVECTOR &translation) {
			XMStoreFloat3(&m_translation, translation);
			SetDirty();
		}

		/**
		 Adds the given x-value to the translation component of this transform.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(float x) noexcept {
			m_translation.x += x;
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the translation component of this transform.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(float y) noexcept {
			m_translation.y += y;
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the translation component of this transform.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(float z) noexcept {
			m_translation.z += z;
			SetDirty();
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
		void AddTranslation(float x, float y, float z) noexcept {
			m_translation.x += x;
			m_translation.y += y;
			m_translation.z += z;
			SetDirty();
		}
		
		/**
		 Adds the given translation component to the translation component of this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT3 &translation) noexcept {
			AddTranslation(translation.x, translation.y, translation.z);
		}
		
		/**
		 Adds the given translation component to the translation component of this transform.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMVECTOR &translation) {
			AddTranslation(XMVectorGetX(translation), XMVectorGetY(translation), XMVectorGetZ(translation));
		}

		/**
		 Returns the x-value of the translation component of this transform.

		 @return		The x-value of the translation component of this transform.
		 */
		float GetTranslationX() const noexcept {
			return m_translation.x;
		}
		
		/**
		 Returns the y-value of the translation component of this transform.

		 @return		The y-value of the translation component of this transform.
		 */
		float GetTranslationY() const noexcept {
			return m_translation.y;
		}
		
		/**
		 Returns the z-value of the translation component of this transform.

		 @return		The z-value of the translation component of this transform.
		 */
		float GetTranslationZ() const noexcept {
			return m_translation.z;
		}
		
		/**
		 Returns the translation component of this transform.

		 @return		The translation component of this transform.
		 */
		const XMFLOAT3 GetTranslation() const noexcept {
			return m_translation;
		}
		
		/**
		 Returns the object-to-parent translation matrix of this transform.

		 @return		The object-to-parent translation matrix of this transform.
		 */
		const XMMATRIX GetObjectToParentTranslationMatrix() const {
			return XMMatrixTranslationFromVector(XMLoadFloat3(&m_translation));
		}

		/**
		 Returns the parent-to-object translation matrix of this transform.

		 @return		The parent-to-object translation matrix of this transform.
		 */
		const XMMATRIX GetParentToObjectTranslationMatrix() const {
			return XMMatrixTranslationFromVector(-XMLoadFloat3(&m_translation));
		}

		//---------------------------------------------------------------------
		// Member Methods: Rotation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the rotation component of this transform to the given value.

		 @param[in]		x
						The x-value of the rotation component.
		 */
		void SetRotationX(float x) noexcept {
			m_rotation.x = x;
			SetDirty();
		}
		
		/**
		 Sets the y-value of the rotation component of this transform to the given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(float y) noexcept {
			m_rotation.y = y;
			SetDirty();
		}
		
		/**
		 Sets the z-value of the rotation component of this transform to the given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(float z) noexcept {
			m_rotation.z = z;
			SetDirty();
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
		void SetRotation(float x, float y, float z) noexcept {
			m_rotation.x = x;
			m_rotation.y = y;
			m_rotation.z = z;
			SetDirty();
		}
		
		/**
		 Sets the rotation component of this transform to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMFLOAT3 &rotation) noexcept {
			m_rotation = rotation;
			SetDirty();
		}

		/**
		 Sets the rotation component of this transform to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMVECTOR &rotation) {
			XMStoreFloat3(&m_rotation, rotation);
			SetDirty();
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

			SetDirty();
		}
		
		/**
		 Adds the given x-value to the rotation component of this transform.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(float x) noexcept {
			m_rotation.x += x;
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the rotation component of this transform.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(float y) noexcept {
			m_rotation.y += y;
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the rotation component of this transform.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(float z) noexcept {
			m_rotation.z += z;
			SetDirty();
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
		void AddRotation(float x, float y, float z) noexcept {
			m_rotation.x += x;
			m_rotation.y += y;
			m_rotation.z += z;
			SetDirty();
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMFLOAT3 &rotation) noexcept {
			AddRotation(rotation.x, rotation.y, rotation.z);
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMVECTOR &rotation) {
			AddRotation(XMVectorGetX(rotation), XMVectorGetY(rotation), XMVectorGetZ(rotation));
		}

		/**
		 Returns the x-value of the rotation component of this transform.

		 @return		The x-value of the rotation component of this transform.
		 */
		float GetRotationX() const noexcept {
			return m_rotation.x;
		}
		
		/**
		 Returns the y-value of the rotation component of this transform.

		 @return		The y-value of the rotation component of this transform.
		 */
		float GetRotationY() const noexcept {
			return m_rotation.y;
		}
		
		/**
		 Returns the z-value of the rotation component of this transform.

		 @return		The z-value of the rotation component of this transform.
		 */
		float GetRotationZ() const noexcept {
			return m_rotation.z;
		}
		
		/**
		 Returns the rotation component of this transform.

		 @return		The rotation component of this transform.
		 */
		const XMFLOAT3 GetRotation() const noexcept {
			return m_rotation;
		}
		
		/**
		 Returns the object-to-parent rotation matrix of this transform.

		 @return		The object-to-parent rotation matrix of this transform.
		 */
		const XMMATRIX GetObjectToParentRotationMatrix() const {
			return XMMatrixRotationZ(GetRotationZ()) * XMMatrixRotationX(GetRotationX()) * XMMatrixRotationY(GetRotationY());
		}

		/**
		 Returns the parent-to-object rotation matrix of this transform.

		 @return		The parent-to-object rotation matrix of this transform.
		 */
		const XMMATRIX GetParentToObjectRotationMatrix() const {
			return XMMatrixRotationY(-GetRotationY()) * XMMatrixRotationX(-GetRotationX()) * XMMatrixRotationZ(-GetRotationZ());
		}

		//---------------------------------------------------------------------
		// Member Methods: Scale
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the scale component of this transform to the given value.

		 @param[in]		x
						The x-value of the scale component.
		 */
		void SetScaleX(float x) noexcept {
			m_scale.x = x;
			SetDirty();
		}
		
		/**
		 Sets the y-value of the scale component of this transform to the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(float y) noexcept {
			m_scale.y = y;
			SetDirty();
		}
		
		/**
		 Sets the z-value of the scale component of this transform to the given value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(float z) noexcept {
			m_scale.z = z;
			SetDirty();
		}

		/**
		 Sets the scale component of this transform to the given scale component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(float s) noexcept {
			SetScale(s, s, s);
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
		void SetScale(float x, float y, float z) noexcept {
			m_scale.x = x;
			m_scale.y = y;
			m_scale.z = z;
			SetDirty();
		}
		
		/**
		 Sets the scale component of this transform to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMFLOAT3 &scale) noexcept {
			m_scale = scale;
			SetDirty();
		}
		
		/**
		 Sets the scale component of this transform to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMVECTOR &scale) {
			XMStoreFloat3(&m_scale, scale);
			SetDirty();
		}

		/**
		 Adds the given x-value to the scale component of this transform.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(float x) noexcept {
			m_scale.x += x;
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the scale component of this transform.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(float y) noexcept {
			m_scale.y += y;
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the scale component of this transform.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(float z) noexcept {
			m_scale.z += z;
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this transform.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(float s) noexcept {
			AddScale(s, s, s);
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
		void AddScale(float x, float y, float z) noexcept {
			m_scale.x += x;
			m_scale.y += y;
			m_scale.z += z;
			SetDirty();
		}
		
		/**
		 Adds the given scale component to the scale component of this transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT3 &scale) noexcept {
			AddScale(scale.x, scale.y, scale.z);
		}

		/**
		 Adds the given scale component to the scale component of this transform.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMVECTOR &scale) {
			AddScale(XMVectorGetX(scale), XMVectorGetY(scale), XMVectorGetZ(scale));
		}
		
		/**
		 Returns the x-value of the scale component of this transform.

		 @return		The x-value of the scale component of this transform.
		 */
		float GetScaleX() const noexcept {
			return m_scale.x;
		}
		
		/**
		 Returns the y-value of the scale component of this transform.

		 @return		The y-value of the scale component of this transform.
		 */
		float GetScaleY() const noexcept {
			return m_scale.y;
		}
		
		/**
		 Returns the z-value of the scale component of this transform.

		 @return		The z-value of the scale component of this transform.
		 */
		float GetScaleZ() const noexcept {
			return m_scale.z;
		}
		
		/**
		 Returns the scale component of this transform.

		 @return		The scale component of this transform.
		 */
		const XMFLOAT3 GetScale() const noexcept {
			return m_scale;
		}
		
		/**
		 Returns the object-to-parent scale matrix of this transform.

		 @return		The scale object-to-parent matrix of this transform.
		 */
		const XMMATRIX GetObjectToParentScaleMatrix() const {
			return XMMatrixScalingFromVector(XMLoadFloat3(&m_scale));
		}

		/**
		 Returns the parent-to-object scale matrix of this transform.

		 @return		The parent-to-object scale matrix of this transform.
		 */
		const XMMATRIX GetParentToObjectScaleMatrix() const {
			return XMMatrixScalingFromVector(XMVectorSet(1.0f / m_scale.x, 1.0f / m_scale.y, 1.0f / m_scale.z, 0.0f));
		}

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform expressed in object space coordinates.

		 @return		The position of the local origin of this transform expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectOrigin() const {
			return XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed in object space coordinates.

		 @return		The direction of the local x-axis of this transform expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisX() const {
			return XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local y-axis of this transform expressed in object space coordinates.

		 @return		The direction of the local y-axis of this transform expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisY() const {
			return XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		}
		
		/**
		 Returns the direction of the local z-axis of this transform expressed in object space coordinates.

		 @return		The direction of the local z-axis of this transform expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisZ() const {
			return XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
		}
		
		/**
		 Returns the local Cartesian axes system of this transform in object space coordinates.

		 @return		The local Cartesian axes system of this transform expressed in object space coordinates.
		 */
		const CartesianAxesSystem GetObjectAxes() const {
			return CartesianAxesSystem(GetObjectAxisX(), GetObjectAxisY(), GetObjectAxisZ());
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform in object space coordinates.

		 @return		The local Cartesian coordinate system of this transform expressed in object space coordinates.
		 */
		const CartesianCoordinateSystem GetObjectCoordinateSystem() const {
			return CartesianCoordinateSystem(GetObjectOrigin(), GetObjectAxes());
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform expressed in parent space coordinates.

		 @return		The position of the local origin of this transform expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentOrigin() const {
			return XMLoadFloat3(&m_translation);
		}

		/**
		 Returns the direction of the local x-axis of this transform expressed in parent space coordinates.

		 @return		The direction of the local x-axis of this transform expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisX() const {
			return TransformObjectToParentDirection(GetObjectAxisX());
		}
		
		/**
		 Returns the direction of the local y-axis of this transform expressed in parent space coordinates.

		 @return		The direction of the local y-axis of this transform expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisY() const {
			return TransformObjectToParentDirection(GetObjectAxisY());
		}
		
		/**
		 Returns the direction of the local z-axis of this transform expressed in parent space coordinates.

		 @return		The direction of the local z-axis of this transform expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisZ() const {
			return TransformObjectToParentDirection(GetObjectAxisZ());
		}
		
		/**
		 Returns the local Cartesian axes system of this transform expressed in parent space coordinates.

		 @return		The local Cartesian axes system of this transform expressed in parent space coordinates.
		 */
		const CartesianAxesSystem GetParentAxes() const {
			return CartesianAxesSystem(GetParentAxisX(), GetParentAxisY(), GetParentAxisZ());
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform in parent space coordinates.

		 @return		The local Cartesian coordinate system of this transform expressed in parent space coordinates.
		 */
		const CartesianCoordinateSystem GetParentCoordinateSystem() const {
			return CartesianCoordinateSystem(GetParentOrigin(), GetParentAxes());
		}

		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------

		/**
		 Returns the object-to-parent matrix of this transform.

		 @return		The object-to-parent matrix of this transform.
		 */
		const XMMATRIX GetObjectToParentMatrix() const {
			UpdateObjectToParentMatrix();
			return m_object_to_parent;
		}

		/**
		 Returns the parent-to-object matrix of this transform.

		 @return		The parent-to-object matrix of this transform.
		 */
		const XMMATRIX GetParentToObjectMatrix() const {
			UpdateParentToObjectMatrix();
			return m_parent_to_object;
		}

		/**
		 Transforms the given vector expressed in object space coordinates to parent space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space coordinates.
		 */
		const XMVECTOR TransformObjectToParent(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetObjectToParentMatrix());
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to object space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space coordinates.
		 */
		const XMVECTOR TransformParentToObject(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetParentToObjectMatrix());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Transforms the given direction expressed in object space coordinates to parent space coordinates.

		 @param[in]		direction
						A reference to the direction expressed in object space coordinates.
		 @return		The transformed (normalized) direction expressed in parent space coordinates.
		 */
		const XMVECTOR TransformObjectToParentDirection(const XMVECTOR &direction) const {
			const XMMATRIX transformation = GetObjectToParentScaleMatrix() * GetObjectToParentRotationMatrix();
			return XMVector3Normalize(XMVector4Transform(direction, transformation));
		}

		/**
		 Sets this transform to dirty.
		 */
		void SetDirty() const noexcept {
			m_dirty_object_to_parent = true;
			m_dirty_parent_to_object = true;
		}

		/**
		 Updates the object-to-parent matrix of this transform if dirty.
		 */
		void UpdateObjectToParentMatrix() const{
			if (m_dirty_object_to_parent) {
				m_object_to_parent = GetObjectToParentScaleMatrix() * GetObjectToParentRotationMatrix() * GetObjectToParentTranslationMatrix();
				m_dirty_object_to_parent = false;
			}
		}
		
		/**
		 Updates the parent-to-object matrix of this transform if dirty.
		 */
		void UpdateParentToObjectMatrix() const{
			if (m_dirty_parent_to_object) {
				m_parent_to_object = GetParentToObjectTranslationMatrix() * GetParentToObjectRotationMatrix() * GetParentToObjectScaleMatrix();
				m_dirty_parent_to_object = false;
			}
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

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
		 The cached object-to-parent matrix of this transform.
		 */
		mutable XMMATRIX m_object_to_parent;

		/**
		 The cached parent-to-object matrix of this transform.
		 */
		mutable XMMATRIX m_parent_to_object;

		/**
		 A flag indicating whether the object-to-parent matrix 
		 of this transform node are dirty.
		 */
		mutable bool m_dirty_object_to_parent;

		/**
		 A flag indicating whether the parent-to-object matrix 
		 of this transform node are dirty.
		 */
		mutable bool m_dirty_parent_to_object;
	};
}