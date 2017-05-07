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

		enum WireframeMode {
			WireframeMode_None = 0,
			WireframeMode_3D   = 1,
			WireframeMode_2D   = 2,
			WireframeMode_3Dand2D = WireframeMode_3D | WireframeMode_2D
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

		WireframeMode GetWireframeMode() const {
			return m_mode;
		}

		void SetWireframeMode(WireframeMode mode) {
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