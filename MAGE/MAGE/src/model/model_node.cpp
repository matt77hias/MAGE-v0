//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_node.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ModelNode::ModelNode(string name, UniquePtr< Model > &&model)
		: SceneNode(std::move(name)), 
		m_model(std::move(model)),
		m_texture_transform(MakeUnique< TextureTransform >()) {
		
		Assert(m_model);
	}

	ModelNode::ModelNode(const ModelNode &model_node)
		: SceneNode(model_node), 
		m_model(model_node.m_model->Clone()),
		m_texture_transform(
			MakeUnique< TextureTransform >(*model_node.m_texture_transform)) {}

	ModelNode::ModelNode(ModelNode &&model_node) = default;

	ModelNode::~ModelNode() = default;

	UniquePtr< Node > ModelNode::CloneImplementation() const {
		return MakeUnique< ModelNode >(*this);
	}
}