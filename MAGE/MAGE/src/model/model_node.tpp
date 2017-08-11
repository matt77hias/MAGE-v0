#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename... ConstructorArgsT >
	ModelNode::ModelNode(const string &name, ConstructorArgsT&&... args)
		: SceneNode(name),
		m_model(MakeUnique< Model >(std::forward< ConstructorArgsT >(args)...)) {}

}