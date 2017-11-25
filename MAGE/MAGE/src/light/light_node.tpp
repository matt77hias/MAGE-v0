#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename LightT >
	DerivedLightNode< LightT >::DerivedLightNode()
		: LightNode(MakeUnique< LightT >()) {}

	template< typename LightT >
	DerivedLightNode< LightT >::DerivedLightNode(
		const DerivedLightNode &light_node) = default;

	template< typename LightT >
	DerivedLightNode< LightT >::DerivedLightNode(
		DerivedLightNode &&light_node) = default;

	template< typename LightT >
	DerivedLightNode< LightT >::~DerivedLightNode() = default;

	template< typename LightT >
	UniquePtr< Node > DerivedLightNode< LightT >::CloneImplementation() const {
		return MakeUnique< DerivedLightNode >(*this);
	}
}