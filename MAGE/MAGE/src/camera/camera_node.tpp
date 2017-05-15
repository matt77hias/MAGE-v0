#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename CameraT >
	template< typename... ConstructorArgsT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(const string &name, ConstructorArgsT&&... args)
		: CameraNode(name, std::make_unique< CameraT >(std::forward< ConstructorArgsT >(args)...)) {}

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
		return std::make_unique< DerivedCameraNode >(*this);
	}
}