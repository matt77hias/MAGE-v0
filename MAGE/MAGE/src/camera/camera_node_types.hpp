#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "camera\camera_node.hpp"
#include "camera\orthographic_camera.hpp"
#include "camera\perspective_camera.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Type Declarations and Definitions
	//-------------------------------------------------------------------------

	/**
	 A class of orthographic camera nodes.
	 */
	using OrthographicCameraNode = DerivedCameraNode< OrthographicCamera >;

	/**
	 A class of perspective camera nodes.
	 */
	using PerspectiveCameraNode = DerivedCameraNode< PerspectiveCamera >;
}