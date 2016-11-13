#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of transforms.
	 */
	struct Transform final {

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
		const XMFLOAT3 &GetRotation() const {
			return m_rotation;
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
		const XMFLOAT3 &GetScale() const {
			return m_scale;
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
		const XMFLOAT3 &GetTranslation() const {
			return m_translation;
		}

	private:

		/**
		 The rotation component (in radians) of this transform.
		 */
		XMFLOAT3 m_rotation;

		/**
		 The scale component of this transform.
		 */
		XMFLOAT3 m_scale;

		/**
		 The translation component of this transform.
		 */
		XMFLOAT3 m_translation;
	};

}