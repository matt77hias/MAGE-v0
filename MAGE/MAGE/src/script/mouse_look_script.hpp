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
			const XMFLOAT2 &sensitivity      = XMFLOAT2(1.8f, 1.8f),
			const XMFLOAT2 &minimum_rotation = XMFLOAT2(-XM_PI / 3.0f, -XM_PI),
			const XMFLOAT2 &maximum_rotation = XMFLOAT2( XM_PI / 3.0f,  XM_PI),
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

		virtual void Update([[maybe_unused]] F64 delta_time) override;

		RotationAxes GetRotationAxes() const noexcept {
			return m_axes;
		}
		void SetRotationAxes(RotationAxes axes) noexcept {
			m_axes = axes;
		}

		F32 GetSensitivityX() const noexcept {
			return m_sensitivity.x;
		}
		F32 GetSensitivityY() const noexcept {
			return m_sensitivity.y;
		}
		const XMFLOAT2 &GetSensitivity() const noexcept {
			return m_sensitivity;
		}
		void SetSensitivityX(F32 x) noexcept {
			m_sensitivity.x = x;
		}
		void SetSensitivityY(F32 y) noexcept {
			m_sensitivity.y = y;
		}
		void SetSensitivity(F32 x, F32 y) {
			m_sensitivity.x = x;
			m_sensitivity.y = y;
		}
		void SetSensitivity(const XMFLOAT2 &sensitivity) noexcept {
			m_sensitivity = sensitivity;
		}
		void SetSensitivity(XMFLOAT2 &&sensitivity) noexcept {
			m_sensitivity = std::move(sensitivity);
		}
		void XM_CALLCONV SetSensitivity(FXMVECTOR sensitivity) noexcept {
			XMStoreFloat2(&m_sensitivity, sensitivity);
		}

		F32 GetMinimumRotationX() const noexcept {
			return m_minimum_rotation.x;
		}
		F32 GetMinimumRotationY() const noexcept {
			return m_minimum_rotation.y;
		}
		const XMFLOAT2 &GetMinimumRotation() const noexcept {
			return m_minimum_rotation;
		}
		void SetMinimumRotationX(F32 x) noexcept {
			m_minimum_rotation.x = x;
		}
		void SetMinimumRotationY(F32 y) noexcept {
			m_minimum_rotation.y = y;
		}
		void SetMinimumRotation(F32 x, F32 y) noexcept {
			m_minimum_rotation.x = x;
			m_minimum_rotation.y = y;
		}
		void SetMinimumRotation(const XMFLOAT2 &minimum_rotation) noexcept {
			m_minimum_rotation = minimum_rotation;
		}
		void SetMinimumRotation(XMFLOAT2 &&minimum_rotation) noexcept {
			m_minimum_rotation = std::move(minimum_rotation);
		}
		void XM_CALLCONV SetMinimumRotation(FXMVECTOR minimum_rotation) noexcept {
			XMStoreFloat2(&m_minimum_rotation, minimum_rotation);
		}

		F32 GetMaximumRotationX() const noexcept {
			return m_maximum_rotation.x;
		}
		F32 GetMaximumRotationY() const noexcept {
			return m_maximum_rotation.y;
		}
		const XMFLOAT2 &GetMaximumRotation() const noexcept {
			return m_maximum_rotation;
		}
		void SetMaximumRotationX(F32 x) noexcept {
			m_maximum_rotation.x = x;
		}
		void SetMaximumRotationY(F32 y) noexcept {
			m_maximum_rotation.y = y;
		}
		void SetMaximumRotation(F32 x, F32 y) noexcept {
			m_maximum_rotation.x = x;
			m_maximum_rotation.y = y;
		}
		void SetMaximumRotation(const XMFLOAT2 &maximum_rotation) noexcept {
			m_maximum_rotation = maximum_rotation;
		}
		void SetMaximumRotation(XMFLOAT2 &&maximum_rotation) noexcept {
			m_maximum_rotation = std::move(maximum_rotation);
		}
		void XM_CALLCONV SetMaximumRotation(FXMVECTOR maximum_rotation) noexcept {
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