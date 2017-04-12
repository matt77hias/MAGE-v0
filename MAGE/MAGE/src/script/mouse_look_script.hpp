#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"
#include "camera\camera.hpp"

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

		explicit MouseLookScript(
			SharedPtr< Camera > camera, 
			RotationAxes axes = RotationAxes_MouseXAndY,
			const XMFLOAT2 &sensitivity = XMFLOAT2(1.8f,1.8f),
			const XMFLOAT2 &minimum = XMFLOAT2(-XM_PI / 3.0f , -XM_2PI),
			const XMFLOAT2 &maximum = XMFLOAT2( XM_PI / 3.0f,   XM_2PI))
			: BehaviorScript(), m_camera(camera), m_axes(axes),
			m_sensitivity(sensitivity), m_min(minimum), m_max(maximum) {}
		MouseLookScript(const MouseLookScript &script) = delete;
		MouseLookScript(MouseLookScript &&script) = default;
		virtual ~MouseLookScript() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		MouseLookScript &operator=(const MouseLookScript &script) = delete;
		MouseLookScript &operator=(MouseLookScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		virtual void Update(double elapsed_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		SharedPtr< Camera > m_camera;
		RotationAxes m_axes;
		XMFLOAT2 m_sensitivity;
		XMFLOAT2 m_min;
		XMFLOAT2 m_max;
	};
}