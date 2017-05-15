#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scripting\behavior_script.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class WireframeScript final : public BehaviorScript {

	public:

		enum struct WireframeMode {
			None    = 0,
			Mode_3D = 1,
			Mode_2D = 2,
			Mode_3Dand2D = Mode_3D | Mode_2D
		};

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		WireframeScript();
		WireframeScript(const WireframeScript &script) = delete;
		WireframeScript(WireframeScript &&script);
		virtual ~WireframeScript();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		WireframeScript &operator=(const WireframeScript &script) = delete;
		WireframeScript &operator=(WireframeScript &&script) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		WireframeMode GetWireframeMode() const noexcept {
			return m_mode;
		}

		void SetWireframeMode(WireframeMode mode) noexcept {
			m_mode = mode;
		}

		virtual void Update(double delta_time) override;

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		WireframeMode m_mode;

		bool m_solid;
	};
}