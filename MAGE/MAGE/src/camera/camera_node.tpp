#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename CameraT >
	template< typename... ConstructorArgsT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(
		string name, ConstructorArgsT&&... args)
		: CameraNode(std::move(name),
			MakeUnique< CameraT >(std::forward< ConstructorArgsT >(args)...)) {}

	template< typename CameraT >
	DerivedCameraNode< CameraT >::DerivedCameraNode(
		string name, UniquePtr< CameraT > &&camera)
		: CameraNode(std::move(name), std::move(camera)) {}

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