#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename... ConstructorArgsT >
	ModelNode::ModelNode(const string &name, ConstructorArgsT&&... args)
		: SceneNode(name),
		m_model(std::make_unique< Model >(std::forward< ConstructorArgsT >(args)...)) {}

}