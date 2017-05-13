#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "math\transform_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	enum RotationAxes {
		RotationAxes_MouseX = 1,
		RotationAxes_MouseY = 2,
		RotationAxes_MouseXAndY = RotationAxes_MouseX | RotationAxes_MouseY
	};

	class MouseLookScript final : public BehaviorScript {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MouseLookScript(TransformNode *transform,
			RotationAxes axes = RotationAxes_MouseXAndY,
			const XMFLOAT2 &sensitivity      = XMFLOAT2(1.8f, 1.8f),
			const XMFLOAT2 &minimum_rotation = XMFLOAT2(-XM_PI / 3.0f, -XM_PI),
			const XMFLOAT2 &maximum_rotation = XMFLOAT2(XM_PI / 3.0f, XM_PI),
			const XMFLOAT2 &direction        = XMFLOAT2(1.0f, 1.0f));
		MouseLookScript(const MouseLookScript &script) = delete;
		MouseLookScript(MouseLookScript &&script);
		virtual ~MouseLookScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		MouseLookScript &operator=(const MouseLookScript &script) = delete;
		MouseLookScript &operator=(MouseLookScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double delta_time) override;

		RotationAxes GetRotationAxes() const noexcept {
			return m_axes;
		}
		void SetRotationAxes(RotationAxes axes) noexcept {
			m_axes = axes;
		}

		float GetSensitivityX() const noexcept {
			return m_sensitivity.x;
		}
		float GetSensitivityY() const noexcept {
			return m_sensitivity.y;
		}
		const XMFLOAT2 &GetSensitivity() const noexcept {
			return m_sensitivity;
		}
		void SetSensitivityX(float x) noexcept {
			m_sensitivity.x = x;
		}
		void SetSensitivityY(float y) noexcept {
			m_sensitivity.y = y;
		}
		void SetSensitivity(float x, float y) {
			m_sensitivity.x = x;
			m_sensitivity.y = y;
		}
		void SetSensitivity(const XMFLOAT2 &sensitivity) noexcept {
			m_sensitivity = sensitivity;
		}
		void SetSensitivity(const XMVECTOR &sensitivity) {
			XMStoreFloat2(&m_sensitivity, sensitivity);
		}

		float GetMinimumRotationX() const noexcept {
			return m_minimum_rotation.x;
		}
		float GetMinimumRotationY() const noexcept {
			return m_minimum_rotation.y;
		}
		const XMFLOAT2 &GetMinimumRotation() const noexcept {
			return m_minimum_rotation;
		}
		void SetMinimumRotationX(float x) noexcept {
			m_minimum_rotation.x = x;
		}
		void SetMinimumRotationY(float y) noexcept {
			m_minimum_rotation.y = y;
		}
		void SetMinimumRotation(float x, float y) noexcept {
			m_minimum_rotation.x = x;
			m_minimum_rotation.y = y;
		}
		void SetMinimumRotation(const XMFLOAT2 &minimum_rotation) noexcept {
			m_minimum_rotation = minimum_rotation;
		}
		void SetMinimumRotation(const XMVECTOR &minimum_rotation) {
			XMStoreFloat2(&m_minimum_rotation, minimum_rotation);
		}

		float GetMaximumRotationX() const noexcept {
			return m_maximum_rotation.x;
		}
		float GetMaximumRotationY() const noexcept {
			return m_maximum_rotation.y;
		}
		const XMFLOAT2 &GetMaximumRotation() const noexcept {
			return m_maximum_rotation;
		}
		void SetMaximumRotationX(float x) noexcept {
			m_maximum_rotation.x = x;
		}
		void SetMaximumRotationY(float y) noexcept {
			m_maximum_rotation.y = y;
		}
		void SetMaximumRotation(float x, float y) noexcept {
			m_maximum_rotation.x = x;
			m_maximum_rotation.y = y;
		}
		void SetMaximumRotation(const XMFLOAT2 &maximum_rotation) noexcept {
			m_maximum_rotation = maximum_rotation;
		}
		void SetMaximumRotation(const XMVECTOR &maximum_rotation) {
			XMStoreFloat2(&m_maximum_rotation, maximum_rotation);
		}

		void InvertDirectionX() noexcept {
			m_direction.x *= -1.0f;
		}
		void InvertDirectionY() noexcept {
			m_direction.y *= -1.0f;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		TransformNode * const m_transform;
		RotationAxes m_axes;
		XMFLOAT2 m_sensitivity;
		XMFLOAT2 m_minimum_rotation;
		XMFLOAT2 m_maximum_rotation;
		XMFLOAT2 m_direction;
	};
}