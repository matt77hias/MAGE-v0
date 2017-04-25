#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "memory\memory.hpp"
#include "collection\collection.hpp"
#include "string\string.hpp"
#include "math\transform.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of transform nodes.
	 */
	class TransformNode {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a transform node.
		 */
		explicit TransformNode()
			: m_transform(new Transform()),
			m_parent(nullptr), m_childs() {
			SetDirty();
		}
		
		/**
		 Constructs a transform node from the given transform node.

		 @param[in]		transform_node
						A reference to the transform node.
		 */
		TransformNode(const TransformNode &transform_node);

		/**
		 Constructs a transform from the given transform node.

		 @param[in]		transform_node
						A reference to the transform node.
		 */
		TransformNode(TransformNode &&transform_node)
			: m_transform(std::move(transform_node.m_transform)),
			m_parent(std::move(transform_node.m_parent)),
			m_childs(std::move(transform_node.m_childs)) {
			SetDirty();
		}

		/**
		 Destructs this transform node.
		 */
		virtual ~TransformNode();
		
		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given transform node to this transform node.

		 @param[in]		transform_node
						A reference to the transform node to copy from.
		 @return		A reference to the copy of the given transform node
						(i.e. this transform node).
		 */
		TransformNode &operator=(const TransformNode &transform_node) = delete;

		/**
		 Copies the given transform node to this transform node.

		 @param[in]		transform_node
						A reference to the transform node to copy from.
		 @return		A reference to the copy of the given transform node
						(i.e. this transform node).
		 */
		TransformNode &operator=(TransformNode &&transform_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods: Clone
		//---------------------------------------------------------------------

		SharedPtr< TransformNode > Clone() const {
			return CloneImplementation();
		}

		//---------------------------------------------------------------------
		// Member Methods: Translation
		//---------------------------------------------------------------------

		/**
		 Sets the x-value of the translation component of this transform node to the given value.

		 @param[in]		x
						The x-value of the translation component.
		 */
		void SetTranslationX(float x) {
			m_transform->SetTranslationX(x);
			SetDirty();
		}
		
		/**
		 Sets the y-value of the translation component of this transform node to the given value.

		 @param[in]		y
						The y-value of the translation component.
		 */
		void SetTranslationY(float y) {
			m_transform->SetTranslationY(y);
			SetDirty();
		}
		
		/**
		 Sets the z-value of the translation component of this transform node to the given value.

		 @param[in]		z
						The z-value of the translation component.
		 */
		void SetTranslationZ(float z) {
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
		void SetTranslation(float x, float y, float z) {
			m_transform->SetTranslation(x, y, z);
			SetDirty();
		}
		
		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMFLOAT3 &translation) {
			m_transform->SetTranslation(translation);
			SetDirty();
		}
		
		/**
		 Sets the translation component of this transform node to the given translation component.

		 @param[in]		translation
						A reference to the translation component.
		 */
		void SetTranslation(const XMVECTOR &translation) {
			m_transform->SetTranslation(translation);
			SetDirty();
		}

		/**
		 Adds the given x-value to the translation component of this transform node.

		 @param[in]		x
						The x-value of the translation component to add.
		 */
		void AddTranslationX(float x) {
			m_transform->AddTranslationX(x);
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the translation component of this transform node.

		 @param[in]		y
						The y-value of the translation component to add.
		 */
		void AddTranslationY(float y) {
			m_transform->AddTranslationY(y);
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the translation component of this transform node.

		 @param[in]		z
						The z-value of the translation component to add.
		 */
		void AddTranslationZ(float z) {
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
		void AddTranslation(float x, float y, float z) {
			m_transform->AddTranslation(x, y, z);
			SetDirty();
		}
		
		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMFLOAT3 &translation) {
			m_transform->AddTranslation(translation);
			SetDirty();
		}
		
		/**
		 Adds the given translation component to the translation component of this transform node.

		 @param[in]		translation
						A reference to the translation component to add.
		 */
		void AddTranslation(const XMVECTOR &translation) {
			m_transform->AddTranslation(translation);
			SetDirty();
		}

		/**
		 Returns the x-value of the translation component of this transform node.

		 @return		The x-value of the translation component of this transform node.
		 */
		float GetTranslationX() const {
			return m_transform->GetTranslationX();
		}
		
		/**
		 Returns the y-value of the translation component of this transform node.

		 @return		The y-value of the translation component of this transform node.
		 */
		float GetTranslationY() const {
			return m_transform->GetTranslationY();
		}
		
		/**
		 Returns the z-value of the translation component of this transform node.

		 @return		The z-value of the translation component of this transform node.
		 */
		float GetTranslationZ() const {
			return m_transform->GetTranslationZ();
		}
		
		/**
		 Returns the translation component of this transform node.

		 @return		The translation component of this transform node.
		 */
		const XMFLOAT3 GetTranslation() const {
			return m_transform->GetTranslation();
		}
		
		/**
		 Returns the object-to-parent translation matrix of this transform node.

		 @return		The object-to-parent translation matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentTranslationMatrix() const {
			return m_transform->GetObjectToParentTranslationMatrix();
		}

		/**
		 Returns the parent-to-object translation matrix of this transform node.

		 @return		The parent-to-object translation matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectTranslationMatrix() const {
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
		void SetRotationX(float x) {
			m_transform->SetRotationX(x);
			SetDirty();
		}
		
		/**
		 Sets the y-value of the rotation component of this transform node to the given value.

		 @param[in]		y
						The y-value of the rotation component.
		 */
		void SetRotationY(float y) {
			m_transform->SetRotationY(y);
			SetDirty();
		}
		
		/**
		 Sets the z-value of the rotation component of this transform node to the given value.

		 @param[in]		z
						The z-value of the rotation component.
		 */
		void SetRotationZ(float z) {
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
		void SetRotation(float x, float y, float z) {
			m_transform->SetRotation(x, y, z);
			SetDirty();
		}
		
		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMFLOAT3 &rotation) {
			m_transform->SetRotation(rotation);
			SetDirty();
		}

		/**
		 Sets the rotation component of this transform node to the given rotation component.

		 @param[in]		rotation
						A reference to the rotation component.
		 */
		void SetRotation(const XMVECTOR &rotation) {
			m_transform->SetRotation(rotation);
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
			m_transform->SetRotationAroundDirection(normal, angle);
			SetDirty();
		}
		
		/**
		 Adds the given x-value to the rotation component of this transform node.

		 @param[in]		x
						The x-value of the rotation component to add.
		 */
		void AddRotationX(float x) {
			m_transform->AddRotationX(x);
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the rotation component of this transform node.

		 @param[in]		y
						The y-value of the rotation component to add.
		 */
		void AddRotationY(float y) {
			m_transform->AddRotationY(y);
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the rotation component of this transform node.

		 @param[in]		z
						The z-value of the rotation component to add.
		 */
		void AddRotationZ(float z) {
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
		void AddRotation(float x, float y, float z) {
			m_transform->AddRotation(x, y, z);
			SetDirty();
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMFLOAT3 &rotation) {
			m_transform->AddRotation(rotation);
			SetDirty();
		}
		
		/**
		 Adds the given rotation component to the rotation component of this transform node.

		 @param[in]		rotation
						A reference to the rotation component to add.
		 */
		void AddRotation(const XMVECTOR &rotation) {
			m_transform->AddRotation(rotation);
			SetDirty();
		}

		/**
		 Returns the x-value of the rotation component of this transform node.

		 @return		The x-value of the rotation component of this transform node.
		 */
		float GetRotationX() const {
			return m_transform->GetRotationX();
		}
		
		/**
		 Returns the y-value of the rotation component of this transform node.

		 @return		The y-value of the rotation component of this transform node.
		 */
		float GetRotationY() const {
			return m_transform->GetRotationY();
		}
		
		/**
		 Returns the z-value of the rotation component of this transform node.

		 @return		The z-value of the rotation component of this transform node.
		 */
		float GetRotationZ() const {
			return m_transform->GetRotationZ();
		}
		
		/**
		 Returns the rotation component of this transform node.

		 @return		The rotation component of this transform node.
		 */
		const XMFLOAT3 GetRotation() const {
			return m_transform->GetRotation();
		}
		
		/**
		 Returns the object-to-parent rotation matrix of this transform node.

		 @return		The object-to-parent rotation matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentRotationMatrix() const {
			return m_transform->GetObjectToParentRotationMatrix();
		}

		/**
		 Returns the parent-to-object rotation matrix of this transform node.

		 @return		The parent-to-object rotation matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectRotationMatrix() const {
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
		void SetScaleX(float x) {
			m_transform->SetScaleX(x);
			SetDirty();
		}
		
		/**
		 Sets the y-value of the scale component of this transform node to the given value.

		 @param[in]		y
						The y-value of the scale component.
		 */
		void SetScaleY(float y) {
			m_transform->SetScaleY(y);
			SetDirty();
		}
		
		/**
		 Sets the z-value of the scale component of this transform node to the given value.

		 @param[in]		z
						The z-value of the scale component.
		 */
		void SetScaleZ(float z) {
			m_transform->SetScaleZ(z);
			SetDirty();
		}

		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		s
						The scale component.
		 */
		void SetScale(float s) {
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
		void SetScale(float x, float y, float z) {
			m_transform->SetScale(x, y, z);
			SetDirty();
		}
		
		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMFLOAT3 &scale) {
			m_transform->SetScale(scale);
			SetDirty();
		}
		
		/**
		 Sets the scale component of this transform node to the given scale component.

		 @param[in]		scale
						A reference to the scale component.
		 */
		void SetScale(const XMVECTOR &scale) {
			m_transform->SetScale(scale);
			SetDirty();
		}

		/**
		 Adds the given x-value to the scale component of this transform node.

		 @param[in]		x
						The x-value of the scale component to add.
		 */
		void AddScaleX(float x) {
			m_transform->AddScaleX(x);
			SetDirty();
		}
		
		/**
		 Adds the given y-value to the scale component of this transform node.

		 @param[in]		y
						The y-value of the scale component to add.
		 */
		void AddScaleY(float y) {
			m_transform->AddScaleY(y);
			SetDirty();
		}
		
		/**
		 Adds the given z-value to the scale component of this transform node.

		 @param[in]		z
						The z-value of the scale component to add.
		 */
		void AddScaleZ(float z) {
			m_transform->AddScaleZ(z);
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		s
						The scale component to add.
		 */
		void AddScale(float s) {
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
		void AddScale(float x, float y, float z) {
			m_transform->AddScale(x, y, z);
			SetDirty();
		}
		
		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMFLOAT3 &scale) {
			m_transform->AddScale(scale);
			SetDirty();
		}

		/**
		 Adds the given scale component to the scale component of this transform node.

		 @param[in]		scale
						A reference to the scale component to add.
		 */
		void AddScale(const XMVECTOR &scale) {
			m_transform->AddScale(scale);
			SetDirty();
		}
		
		/**
		 Returns the x-value of the scale component of this transform node.

		 @return		The x-value of the scale component of this transform node.
		 */
		float GetScaleX() const {
			return m_transform->GetScaleX();
		}
		
		/**
		 Returns the y-value of the scale component of this transform node.

		 @return		The y-value of the scale component of this transform node.
		 */
		float GetScaleY() const {
			return m_transform->GetScaleY();
		}
		
		/**
		 Returns the z-value of the scale component of this transform node.

		 @return		The z-value of the scale component of this transform node.
		 */
		float GetScaleZ() const {
			return m_transform->GetScaleZ();
		}
		
		/**
		 Returns the scale component of this transform node.

		 @return		The scale component of this transform node.
		 */
		const XMFLOAT3 GetScale() const {
			return m_transform->GetScale();
		}
		
		/**
		 Returns the object-to-parent scale matrix of this transform node.

		 @return		The scale object-to-parent matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentScaleMatrix() const {
			return m_transform->GetObjectToParentScaleMatrix();
		}

		/**
		 Returns the parent-to-object scale matrix of this transform node.

		 @return		The parent-to-object scale matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectScaleMatrix() const {
			return m_transform->GetParentToObjectScaleMatrix();
		}

		//---------------------------------------------------------------------
		// Member Methods: Object Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform node expressed in object space coordinates.

		 @return		The position of the local origin of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectOrigin() const {
			return m_transform->GetObjectOrigin();
		}

		/**
		 Returns the direction of the local x-axis of this transform node expressed in object space coordinates.

		 @return		The direction of the local x-axis of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisX() const {
			return m_transform->GetObjectAxisX();
		}
		
		/**
		 Returns the direction of the local y-axis of this transform node expressed in object space coordinates.

		 @return		The direction of the local y-axis of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisY() const {
			return m_transform->GetObjectAxisY();
		}
		
		/**
		 Returns the direction of the local z-axis of this transform node expressed in object space coordinates.

		 @return		The direction of the local z-axis of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectAxisZ() const {
			return m_transform->GetObjectAxisZ();
		}
		
		/**
		 Returns the local Cartesian axes system of this transform node in object space coordinates.

		 @return		The local Cartesian axes system of this transform node expressed in object space coordinates.
		 */
		const CartesianAxesSystem GetObjectAxes() const {
			return m_transform->GetObjectAxes();
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform node in object space coordinates.

		 @return		The local Cartesian coordinate system of this transform node expressed in object space coordinates.
		 */
		const CartesianCoordinateSystem GetObjectCoordinateSystem() const {
			return m_transform->GetObjectCoordinateSystem();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Parent Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform node expressed in parent space coordinates.

		 @return		The position of the local origin of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentOrigin() const {
			return m_transform->GetParentOrigin();
		}

		/**
		 Returns the direction of the local x-axis of this transform node expressed in parent space coordinates.

		 @return		The direction of the local x-axis of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisX() const {
			return m_transform->GetParentAxisX();
		}
		
		/**
		 Returns the direction of the local y-axis of this transform node expressed in parent space coordinates.

		 @return		The direction of the local y-axis of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisY() const {
			return m_transform->GetParentAxisY();
		}
		
		/**
		 Returns the direction of the local z-axis of this transform node expressed in parent space coordinates.

		 @return		The direction of the local z-axis of this transform node expressed in parent space coordinates.
		 */
		const XMVECTOR GetParentAxisZ() const {
			return m_transform->GetParentAxisZ();
		}
		
		/**
		 Returns the local Cartesian axes system of this transform node expressed in parent space coordinates.

		 @return		The local Cartesian axes system of this transform node expressed in parent space coordinates.
		 */
		const CartesianAxesSystem GetParentAxes() const {
			return m_transform->GetParentAxes();
		}
		
		/**
		 Returns the local Cartesian coordinate system of this transform node in parent space coordinates.

		 @return		The local Cartesian coordinate system of this transform node expressed in parent space coordinates.
		 */
		const CartesianCoordinateSystem GetParentCoordinateSystem() const {
			return m_transform->GetParentCoordinateSystem();
		}

		//---------------------------------------------------------------------
		// Member Methods: World Space
		//---------------------------------------------------------------------

		/**
		 Returns the position of the local origin of this transform node expressed in world space coordinates.

		 @return		The position of the local origin of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldOrigin() const {
			return TransformObjectToWorld(GetObjectOrigin());
		}

		/**
		 Returns the direction of the local x-axis of this transform node expressed in world space coordinates.

		 @return		The direction of the local x-axis of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldAxisX() const {
			return TransformObjectToWorld(GetObjectAxisX());
		}

		/**
		 Returns the direction of the local y-axis of this transform node expressed in world space coordinates.

		 @return		The direction of the local y-axis of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldAxisY() const {
			return TransformObjectToWorld(GetObjectAxisY());
		}

		/**
		 Returns the direction of the local z-axis of this transform node expressed in world space coordinates.

		 @return		The direction of the local z-axis of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldAxisZ() const {
			return TransformObjectToWorld(GetObjectAxisZ());
		}

		/**
		 Returns the local Cartesian axes system of this transform node expressed in world space coordinates.

		 @return		The local Cartesian axes system of this transform node expressed in world space coordinates.
		 */
		const CartesianAxesSystem GetWorldAxes() const {
			return CartesianAxesSystem(GetWorldAxisX(), GetWorldAxisY(), GetWorldAxisZ());
		}

		/**
		 Returns the local Cartesian coordinate system of this transform node in world space coordinates.

		 @return		The local Cartesian coordinate system of this transform node expressed in world space coordinates.
		 */
		const CartesianCoordinateSystem GetWorldCoordinateSystem() const {
			return CartesianCoordinateSystem(GetWorldOrigin(), GetWorldAxes());
		}

		//---------------------------------------------------------------------
		// Member Methods: Camera Object Space
		//---------------------------------------------------------------------

		/**
		 Returns the local eye position of this transform node expressed in object space coordinates.

		 @return		The local eye position of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectEye() const {
			return GetObjectOrigin();
		}

		/**
		 Returns the local left direction of this transform node expressed in object space coordinates.

		 @return		The local left direction of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectLeft() const {
			return GetObjectAxisX();
		}
		
		/**
		 Returns the local up direction of this transform node expressed in object space coordinates.

		 @return		The local up direction of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectUp() const {
			return GetObjectAxisY();
		}
		
		/**
		 Returns the local forward direction of this transform node expressed in object space coordinates.

		 @return		The local forward direction of this transform node expressed in object space coordinates.
		 */
		const XMVECTOR GetObjectForward() const {
			return GetObjectAxisZ();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Camera World Space
		//---------------------------------------------------------------------

		/**
		 Returns the local eye position of this transform node expressed in world space coordinates.

		 @return		The local eye position of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldEye() const {
			return GetWorldOrigin();
		}

		/**
		 Returns the local left direction of this transform node expressed in world space coordinates.

		 @return		The local left direction of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldLeft() const {
			return GetWorldAxisX();
		}
		
		/**
		 Returns the local up direction of this transform node expressed in world space coordinates.

		 @return		The local up direction of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldUp() const {
			return GetWorldAxisY();
		}
		
		/**
		 Returns the local forward direction of this transform node expressed in world space coordinates.

		 @return		The local forward direction of this transform node expressed in world space coordinates.
		 */
		const XMVECTOR GetWorldForward() const {
			return GetWorldAxisZ();
		}
		
		//---------------------------------------------------------------------
		// Member Methods: Transformation
		//---------------------------------------------------------------------

		/**
		 Returns the object-to-parent matrix of this transform node.

		 @return		The object-to-parent matrix of this transform node.
		 */
		const XMMATRIX GetObjectToParentMatrix() const {
			return m_transform->GetObjectToParentMatrix();
		}

		/**
		 Returns the parent-to-object matrix of this transform node.

		 @return		The parent-to-object matrix of this transform node.
		 */
		const XMMATRIX GetParentToObjectMatrix() const {
			return m_transform->GetParentToObjectMatrix();
		}

		/**
		 Returns the object-to-world matrix of this transform node.

		 @return		The object-to-world matrix of this transform node.
		 */
		const XMMATRIX GetObjectToWorldMatrix() const {
			UpdateObjectToWorldMatrix();
			return m_object_to_world;
		}

		/**
		 Returns the world-to-object matrix of this transform node.

		 @return		The world-to-object matrix of this transform node.
		 */
		const XMMATRIX GetWorldToObjectMatrix() const {
			UpdateWorldToObjectMatrix();
			return m_world_to_object;
		}

		/**
		 Returns the parent-to-view matrix of this transform node.

		 @return		The parent-to-view matrix of this transform node.
		 @note			Transforms for cameras should not contain scaling components.
		 */
		const XMMATRIX GetWorldToViewMatrix() const {
			return GetWorldToObjectMatrix();
		}

		/**
		 Transforms the given vector expressed in object space coordinates to parent space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in object space coordinates.
		 @return		The transformed vector expressed in parent space coordinates.
		 */
		const XMVECTOR TransformObjectToParent(const XMVECTOR &vector) const {
			return m_transform->TransformObjectToParent(vector);
		}

		/**
		 Transforms the given vector expressed in parent space coordinates to object space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in parent space coordinates.
		 @return		The transformed vector expressed in object space coordinates.
		 */
		const XMVECTOR TransformParentToObject(const XMVECTOR &vector) const {
			return m_transform->TransformParentToObject(vector);
		}

		/**
		 Transforms the given vector expressed in object space coordinates to world space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in object space coordinates.
		 @return		The transformed vector expressed in world space coordinates.
		 */
		const XMVECTOR TransformObjectToWorld(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetObjectToWorldMatrix());
		}

		/**
		 Transforms the given vector expressed in world space coordinates to object space coordinates.

		 @param[in]		vector
						A reference to the vector expressed in world space coordinates.
		 @return		The transformed vector expressed in object space coordinates.
		 */
		const XMVECTOR TransformWorldToObject(const XMVECTOR &vector) const {
			return XMVector4Transform(vector, GetWorldToObjectMatrix());
		}

		//---------------------------------------------------------------------
		// Member Methods: Graph
		//---------------------------------------------------------------------

		bool HasParentTransformNode() const {
			return m_parent != nullptr;
		}
		TransformNode *GetParentTransformNode() const {
			return m_parent;
		}
		size_t GetNumberOfChildTransformNodes() const {
			m_childs.size();
		}
		bool HasChildTransformNode(SharedPtr< const TransformNode > transform_node) const;
		void AddChildTransformNode(SharedPtr< TransformNode > transform_node);
		void RemoveChildTransformNode(SharedPtr< TransformNode > transform_node);
		void RemoveAllChildTransformNodes();
		template< typename ActionT >
		void ForEachChildTransformNode(ActionT action) const;
		template< typename ActionT >
		void ForEachDescendantTransformNode(ActionT action) const;

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual SharedPtr< TransformNode > CloneImplementation() const {
			return SharedPtr< TransformNode >(new TransformNode(*this));
		}

		/**
		 Sets this transform node to dirty.
		 */
		void SetDirty() const {
			m_dirty_object_to_world = true;
			m_dirty_world_to_object = true;
			
			// Sets the descendants of this transform node to dirty.
			ForEachDescendantTransformNode([](const TransformNode &transform_node) {
				transform_node.SetDirty();
			});
		}

		/**
		 Updates the object-to-world matrix of this transform node if dirty.
		 */
		void UpdateObjectToWorldMatrix() const {
			if (m_dirty_object_to_world) {
				if (HasParentTransformNode()) {
					m_object_to_world = GetObjectToParentMatrix() * m_parent->GetObjectToWorldMatrix();
				}
				else {
					m_object_to_world = GetObjectToParentMatrix();
				}
				m_dirty_object_to_world = false;
			}
		}

		/**
		 Updates the world-to-object matrix of this transform node if dirty.
		 */
		void UpdateWorldToObjectMatrix() const {
			if (m_dirty_world_to_object) {
				if (HasParentTransformNode()) {
					m_world_to_object = m_parent->GetWorldToObjectMatrix() * GetParentToObjectMatrix();
				}
				else {
					m_world_to_object = GetParentToObjectMatrix();
				}
				m_dirty_world_to_object = false;
			}
		}

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The transform of this transform node.
		 */
		UniquePtr< Transform > m_transform;

		/**
		 The parent transform node of this transform node.
		 */
		TransformNode *m_parent;

		/**
		 The child transform nodes of this transform node.
		 */
		vector< SharedPtr< TransformNode > > m_childs;

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
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.tpp"

#pragma endregion