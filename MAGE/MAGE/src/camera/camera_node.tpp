#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(const string &name) 
		: CameraNode(name, UniquePtr< Camera >(new CameraT())) {}

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(const string &name, UniquePtr< CameraT > &&camera)
		: CameraNode(name, std::move(camera)) {}

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(const DerivedCameraNode &camera_node) = default;

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(DerivedCameraNode &&camera_node) = default;

	template< typename CameraT >
	DerivedCameraNode< CameraT >::~DerivedCameraNode() = default;

	template< typename CameraT >
	UniquePtr< Node > DerivedCameraNode< CameraT >::CloneImplementation() const {
		return UniquePtr< Node >(new DerivedCameraNode(*this));
	}
}