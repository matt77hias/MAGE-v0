#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "math\transform\transform_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	class MouseLookScript final : public BehaviorScript {

	public:

		enum struct RotationAxes {
			MouseX = 1,
			MouseY = 2,
			MouseXAndY = MouseX | MouseY
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		explicit MouseLookScript(TransformNode *transform,
			RotationAxes axes = RotationAxes::MouseXAndY,
			F32x2 sensitivity      = { 1.8f, 1.8f },
			F32x2 minimum_rotation = { -XM_PI / 3.0f, -XM_PI },
			F32x2 maximum_rotation = {  XM_PI / 3.0f,  XM_PI },
			F32x2 direction        = { 1.0f, 1.0f });
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

		virtual void Update([[maybe_unused]] F64 delta_time) override;

		RotationAxes GetRotationAxes() const noexcept {
			return m_axes;
		}
		void SetRotationAxes(RotationAxes axes) noexcept {
			m_axes = axes;
		}

		F32 GetSensitivityX() const noexcept {
			return m_sensitivity.m_x;
		}
		F32 GetSensitivityY() const noexcept {
			return m_sensitivity.m_y;
		}
		const F32x2 GetSensitivity() const noexcept {
			return m_sensitivity;
		}
		void SetSensitivityX(F32 x) noexcept {
			m_sensitivity.m_x = x;
		}
		void SetSensitivityY(F32 y) noexcept {
			m_sensitivity.m_y = y;
		}
		void SetSensitivity(F32 x, F32 y) {
			m_sensitivity.m_x = x;
			m_sensitivity.m_y = y;
		}
		void SetSensitivity(F32x2 sensitivity) noexcept {
			m_sensitivity = std::move(sensitivity);
		}
		void XM_CALLCONV SetSensitivity(FXMVECTOR sensitivity) noexcept {
			XMStoreFloat2(&m_sensitivity, sensitivity);
		}

		F32 GetMinimumRotationX() const noexcept {
			return m_minimum_rotation.m_x;
		}
		F32 GetMinimumRotationY() const noexcept {
			return m_minimum_rotation.m_y;
		}
		const F32x2 GetMinimumRotation() const noexcept {
			return m_minimum_rotation;
		}
		void SetMinimumRotationX(F32 x) noexcept {
			m_minimum_rotation.m_x = x;
		}
		void SetMinimumRotationY(F32 y) noexcept {
			m_minimum_rotation.m_y = y;
		}
		void SetMinimumRotation(F32 x, F32 y) noexcept {
			m_minimum_rotation.m_x = x;
			m_minimum_rotation.m_y = y;
		}
		void SetMinimumRotation(F32x2 minimum_rotation) noexcept {
			m_minimum_rotation = std::move(minimum_rotation);
		}
		void XM_CALLCONV SetMinimumRotation(FXMVECTOR minimum_rotation) noexcept {
			XMStoreFloat2(&m_minimum_rotation, minimum_rotation);
		}

		F32 GetMaximumRotationX() const noexcept {
			return m_maximum_rotation.m_x;
		}
		F32 GetMaximumRotationY() const noexcept {
			return m_maximum_rotation.m_y;
		}
		const F32x2 GetMaximumRotation() const noexcept {
			return m_maximum_rotation;
		}
		void SetMaximumRotationX(F32 x) noexcept {
			m_maximum_rotation.m_x = x;
		}
		void SetMaximumRotationY(F32 y) noexcept {
			m_maximum_rotation.m_y = y;
		}
		void SetMaximumRotation(F32 x, F32 y) noexcept {
			m_maximum_rotation.m_x = x;
			m_maximum_rotation.m_y = y;
		}
		void SetMaximumRotation(F32x2 maximum_rotation) noexcept {
			m_maximum_rotation = std::move(maximum_rotation);
		}
		void XM_CALLCONV SetMaximumRotation(FXMVECTOR maximum_rotation) noexcept {
			XMStoreFloat2(&m_maximum_rotation, maximum_rotation);
		}

		void InvertDirectionX() noexcept {
			m_direction.m_x *= -1.0f;
		}
		void InvertDirectionY() noexcept {
			m_direction.m_y *= -1.0f;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		TransformNode * const m_transform;
		RotationAxes m_axes;
		F32x2 m_sensitivity;
		F32x2 m_minimum_rotation;
		F32x2 m_maximum_rotation;
		F32x2 m_direction;
	};
}