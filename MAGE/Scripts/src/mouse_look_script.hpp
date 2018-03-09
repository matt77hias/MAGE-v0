#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "resource\script\behavior_script.hpp"
#include "math.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage::script {

	class MouseLookScript final : public BehaviorScript {

	public:

		enum class RotationAxes : U8 {
			MouseX = 1,
			MouseY = 2,
			MouseXAndY = MouseX | MouseY
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		MouseLookScript();
		MouseLookScript(const MouseLookScript &script) noexcept;
		MouseLookScript(MouseLookScript &&script) noexcept;
		virtual ~MouseLookScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		MouseLookScript &operator=(const MouseLookScript &script) = delete;
		MouseLookScript &operator=(MouseLookScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Load() override;
		virtual void Update([[maybe_unused]] F64 delta_time) override;

		[[nodiscard]]RotationAxes GetRotationAxes() const noexcept {
			return m_axes;
		}
		void SetRotationAxes(RotationAxes axes) noexcept {
			m_axes = axes;
		}

		[[nodiscard]]F32 GetSensitivityX() const noexcept {
			return m_sensitivity.m_x;
		}
		[[nodiscard]]F32 GetSensitivityY() const noexcept {
			return m_sensitivity.m_y;
		}
		[[nodiscard]]const F32x2 GetSensitivity() const noexcept {
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
			m_sensitivity = XMStore< F32x2 >(sensitivity);
		}

		[[nodiscard]]F32 GetMinimumRotationX() const noexcept {
			return m_minimum_rotation.m_x;
		}
		[[nodiscard]]F32 GetMinimumRotationY() const noexcept {
			return m_minimum_rotation.m_y;
		}
		[[nodiscard]]const F32x2 GetMinimumRotation() const noexcept {
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
			m_minimum_rotation = XMStore< F32x2 >(minimum_rotation);
		}

		[[nodiscard]]F32 GetMaximumRotationX() const noexcept {
			return m_maximum_rotation.m_x;
		}
		[[nodiscard]]F32 GetMaximumRotationY() const noexcept {
			return m_maximum_rotation.m_y;
		}
		[[nodiscard]]const F32x2 GetMaximumRotation() const noexcept {
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
			m_maximum_rotation = XMStore< F32x2 >(maximum_rotation);
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

		bool m_locked;
		RotationAxes m_axes;
		F32x2 m_sensitivity;
		F32x2 m_minimum_rotation;
		F32x2 m_maximum_rotation;
		F32x2 m_direction;
	};
}