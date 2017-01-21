#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of transforms.
	 */
	struct Transform final {

		Transform(const XMFLOAT3 &translation = { 0.0f, 0.0f, 0.0f }, const XMFLOAT3 &rotation = { 0.0f, 0.0f, 0.0f }, const XMFLOAT3 &scale = { 1.0f, 1.0f, 1.0f })
			: m_translation(translation), m_rotation(rotation), m_scale(scale) {}
		Transform(const Transform &transform)
			: m_translation(transform.m_translation), m_rotation(transform.m_rotation), m_scale(transform.m_scale) {}
		~Transform() {}
		
		Transform &operator=(const Transform &transform) {
			m_translation = transform.GetTranslation();
			m_rotation    = transform.GetRotation();
			m_scale       = transform.GetScale();
			return (*this);
		}

		void SetTranslationX(float x) {
			m_translation.x = x;
		}
		void SetTranslationY(float y) {
			m_translation.y = y;
		}
		void SetTranslationZ(float z) {
			m_translation.z = z;
		}
		void SetTranslation(float x, float y, float z) {
			m_translation.x = x;
			m_translation.y = y;
			m_translation.z = z;
		}
		void SetTranslation(const XMFLOAT3 &translation) {
			m_translation.x = translation.x;
			m_translation.y = translation.y;
			m_translation.z = translation.z;
		}
		void AddTranslationX(float x) {
			m_translation.x += x;
		}
		void AddTranslationY(float y) {
			m_translation.y += y;
		}
		void AddTranslationZ(float z) {
			m_translation.z += z;
		}
		void AddTranslation(float x, float y, float z) {
			m_translation.x += x;
			m_translation.y += y;
			m_translation.z += z;
		}
		void AddTranslation(const XMFLOAT3 &translation) {
			m_translation.x += translation.x;
			m_translation.y += translation.y;
			m_translation.z += translation.z;
		}
		float GetTranslationX() const {
			return m_translation.x;
		}
		float GetTranslationY() const {
			return m_translation.y;
		}
		float GetTranslationZ() const {
			return m_translation.z;
		}
		XMFLOAT3 GetTranslation() const {
			return m_translation;
		}
		XMMATRIX GetTranslationMatrix() const {
			return XMMatrixTranslationFromVector(XMLoadFloat3(&m_translation));
		}

		void SetRotationX(float x) {
			m_rotation.x = x;
		}
		void SetRotationY(float y) {
			m_rotation.y = y;
		}
		void SetRotationZ(float z) {
			m_rotation.z = z;
		}
		void SetRotation(float x, float y, float z) {
			m_rotation.x = x;
			m_rotation.y = y;
			m_rotation.z = z;
		}
		void SetRotation(const XMFLOAT3 &rotation) {
			m_rotation.x = rotation.x;
			m_rotation.y = rotation.y;
			m_rotation.z = rotation.z;
		}
		void AddRotationX(float x) {
			m_rotation.x += x;
		}
		void AddRotationY(float y) {
			m_rotation.y += y;
		}
		void AddRotationZ(float z) {
			m_rotation.z += z;
		}
		void AddRotation(float x, float y, float z) {
			m_rotation.x += x;
			m_rotation.y += y;
			m_rotation.z += z;
		}
		void AddRotation(const XMFLOAT3 &rotation) {
			m_rotation.x += rotation.x;
			m_rotation.y += rotation.y;
			m_rotation.z += rotation.z;
		}
		float GetRotationX() const {
			return m_rotation.x;
		}
		float GetRotationY() const {
			return m_rotation.y;
		}
		float GetRotationZ() const {
			return m_rotation.z;
		}
		XMFLOAT3 GetRotation() const {
			return m_rotation;
		}
		XMMATRIX GetRotationMatrix() const {
			return XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotation));
		}

		void SetScaleX(float x) {
			m_scale.x = x;
		}
		void SetScaleY(float y) {
			m_scale.y = y;
		}
		void SetScaleZ(float z) {
			m_scale.z = z;
		}
		void SetScale(float x, float y, float z) {
			m_scale.x = x;
			m_scale.y = y;
			m_scale.z = z;
		}
		void SetScale(const XMFLOAT3 &scale) {
			m_scale.x = scale.x;
			m_scale.y = scale.y;
			m_scale.z = scale.z;
		}
		void AddScaleX(float x) {
			m_scale.x += x;
		}
		void AddScaleY(float y) {
			m_scale.y += y;
		}
		void AddScaleZ(float z) {
			m_scale.z += z;
		}
		void AddScale(float x, float y, float z) {
			m_scale.x += x;
			m_scale.y += y;
			m_scale.z += z;
		}
		void AddScale(const XMFLOAT3 &scale) {
			m_scale.x += scale.x;
			m_scale.y += scale.y;
			m_scale.z += scale.z;
		}
		float GetScaleX() const {
			return m_scale.x;
		}
		float GetScaleY() const {
			return m_scale.y;
		}
		float GetScaleZ() const {
			return m_scale.z;
		}
		XMFLOAT3 GetScale() const {
			return m_scale;
		}
		XMMATRIX GetScaleMatrix() const {
			return XMMatrixScalingFromVector(XMLoadFloat3(&m_scale));
		}

		XMMATRIX GetTransformMatrix() const {
			return GetTranslationMatrix() * GetRotationMatrix() * GetScaleMatrix();
		}

	private:

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

	/**
	 A struct of camera transforms.
	 */
	struct CameraTransform final {

		CameraTransform(const XMFLOAT3 &translation = { 0.0f, 0.0f, 0.0f }, const XMFLOAT3 &rotation = { 0.0f, 0.0f, 0.0f })
			: m_translation(translation), m_rotation(rotation) {}
		CameraTransform(const CameraTransform &transform)
			: m_translation(transform.m_translation), m_rotation(transform.m_rotation) {}
		~CameraTransform() {}

		CameraTransform &operator=(const CameraTransform &transform) {
			m_translation = transform.GetTranslation();
			m_rotation    = transform.GetRotation();
			return (*this);
		}

		void SetTranslationX(float x) {
			m_translation.x = x;
		}
		void SetTranslationY(float y) {
			m_translation.y = y;
		}
		void SetTranslationZ(float z) {
			m_translation.z = z;
		}
		void SetTranslation(float x, float y, float z) {
			m_translation.x = x;
			m_translation.y = y;
			m_translation.z = z;
		}
		void SetTranslation(const XMFLOAT3 &translation) {
			m_translation.x = translation.x;
			m_translation.y = translation.y;
			m_translation.z = translation.z;
		}
		void AddTranslationX(float x) {
			m_translation.x += x;
		}
		void AddTranslationY(float y) {
			m_translation.y += y;
		}
		void AddTranslationZ(float z) {
			m_translation.z += z;
		}
		void AddTranslation(float x, float y, float z) {
			m_translation.x += x;
			m_translation.y += y;
			m_translation.z += z;
		}
		void AddTranslation(const XMFLOAT3 &translation) {
			m_translation.x += translation.x;
			m_translation.y += translation.y;
			m_translation.z += translation.z;
		}
		float GetTranslationX() const {
			return m_translation.x;
		}
		float GetTranslationY() const {
			return m_translation.y;
		}
		float GetTranslationZ() const {
			return m_translation.z;
		}
		XMFLOAT3 GetTranslation() const {
			return m_translation;
		}
		XMMATRIX GetTranslationMatrix() const {
			return XMMatrixTranslationFromVector(XMLoadFloat3(&m_translation));
		}

		void SetRotationX(float x) {
			m_rotation.x = x;
		}
		void SetRotationY(float y) {
			m_rotation.y = y;
		}
		void SetRotationZ(float z) {
			m_rotation.z = z;
		}
		void SetRotation(float x, float y, float z) {
			m_rotation.x = x;
			m_rotation.y = y;
			m_rotation.z = z;
		}
		void SetRotation(const XMFLOAT3 &rotation) {
			m_rotation.x = rotation.x;
			m_rotation.y = rotation.y;
			m_rotation.z = rotation.z;
		}
		void AddRotationX(float x) {
			m_rotation.x += x;
		}
		void AddRotationY(float y) {
			m_rotation.y += y;
		}
		void AddRotationZ(float z) {
			m_rotation.z += z;
		}
		void AddRotation(float x, float y, float z) {
			m_rotation.x += x;
			m_rotation.y += y;
			m_rotation.z += z;
		}
		void AddRotation(const XMFLOAT3 &rotation) {
			m_rotation.x += rotation.x;
			m_rotation.y += rotation.y;
			m_rotation.z += rotation.z;
		}
		float GetRotationX() const {
			return m_rotation.x;
		}
		float GetRotationY() const {
			return m_rotation.y;
		}
		float GetRotationZ() const {
			return m_rotation.z;
		}
		XMFLOAT3 GetRotation() const {
			return m_rotation;
		}
		XMMATRIX GetRotationMatrix() const {
			return XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotation));
		}

		XMFLOAT3 GetLocalLeft() const {
			return XMFLOAT3(1.0f, 0.0f, 0.0f);
		}
		XMFLOAT3 GetLocalUp() const {
			return XMFLOAT3(0.0f, 1.0f, 0.0f);
		}
		XMFLOAT3 GetLocalFocus() const {
			return XMFLOAT3(0.0f, 0.0f, 1.0f);
		}
		
		XMFLOAT3 GetLeft() const {
			return TransformDirection(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));
		}
		XMFLOAT3 GetUp() const {
			return TransformDirection(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
		}
		XMFLOAT3 GetFocus() const {
			return TransformDirection(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
		}

		XMMATRIX GetWorldToViewMatrix() const {
			const XMVECTOR eye	    = XMLoadFloat3(&m_translation);
			const XMVECTOR focus	= XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			const XMVECTOR up		= XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
			const XMMATRIX rotation = GetRotationMatrix();
			const XMVECTOR t_focus  = XMVector4Transform(focus, rotation);
			const XMVECTOR t_up	    = XMVector4Transform(up, rotation);
			return XMMatrixLookAtLH(eye, focus, up);
		}

	private:

		XMFLOAT3 TransformDirection(XMVECTOR direction) const {
			const XMMATRIX rotation = GetRotationMatrix();
			// World Coordinate System
			const XMVECTOR t_direction_v = XMVector4Transform(direction, rotation);
			XMFLOAT3 t_direction;
			XMStoreFloat3(&t_direction, t_direction_v);
			return t_direction;
		}

		/**
		 The translation component of this camera transform.
		 */
		XMFLOAT3 m_translation;

		/**
		 The rotation component (in radians) of this camera transform.
		 */
		XMFLOAT3 m_rotation;
	};
}