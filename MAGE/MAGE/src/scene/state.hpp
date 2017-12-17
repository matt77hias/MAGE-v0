#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 An enumeration of the different states.

	 This contains:
	 @c Active,
	 @c Passive and
	 @c Terminated.
	 */
	enum struct State {
		Active,
		Passive,
		Terminated
	};
}