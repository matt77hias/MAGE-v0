//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "model\model_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename... ConstructorArgsT >
	ModelNode::ModelNode(const string &name, ConstructorArgsT&&... args)
		: SceneNode(name), 
		m_model(std::make_unique< Model >(std::forward< ConstructorArgsT >(args)...)) {}

	ModelNode::ModelNode(const string &name, UniquePtr< Model > &&model)
		: SceneNode(name), m_model(std::move(model)) {}

	ModelNode::ModelNode(const ModelNode &model_node)
		: SceneNode(model_node), m_model(model_node.GetModel()->Clone()) {}

	ModelNode::ModelNode(ModelNode &&model_node) = default;

	ModelNode::~ModelNode() = default;

	UniquePtr< Node > ModelNode::CloneImplementation() const {
		return std::make_unique< ModelNode >(*this);
	}
}