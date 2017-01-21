#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class OrthographicCamera : private Camera {

		OrthographicCamera(const XMMATRIX &view_to_projection, const Transform &transform = Transform()) : Camera(view_to_projection, transform) {}
		virtual ~OrthographicCamera() {}
	};
}