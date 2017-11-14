#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename... ConstructorArgsT >
	ModelNode::ModelNode(string name, ConstructorArgsT&&... args)
		: SceneNode(std::move(name)),
		m_model(MakeUnique< Model >(std::forward< ConstructorArgsT >(args)...)),
		m_texture_transform(MakeUnique< TextureTransform >()) {}
}