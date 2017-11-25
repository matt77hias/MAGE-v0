#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode()
		: CameraNode(MakeUnique< CameraT >()) {}

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(
		const DerivedCameraNode &camera_node) = default;

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(
		DerivedCameraNode &&camera_node) = default;

	template< typename CameraT >
	DerivedCameraNode< CameraT >::~DerivedCameraNode() = default;

	template< typename CameraT >
	UniquePtr< Node > DerivedCameraNode< CameraT >::CloneImplementation() const {
		return MakeUnique< DerivedCameraNode >(*this);
	}
}