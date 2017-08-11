//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// TransformNode
	//-------------------------------------------------------------------------

	TransformNode::TransformNode()
		: m_transform(new Transform()),
		m_parent(nullptr), m_childs() {
		SetDirty();
	}

	TransformNode::TransformNode(const TransformNode &transform_node)
		: m_transform(new Transform(*transform_node.m_transform)), 
		m_parent(nullptr), m_childs() {
		SetDirty();
	}

	TransformNode::TransformNode(TransformNode &&transform_node) noexcept
		: m_transform(std::move(transform_node.m_transform)),
		m_parent(std::move(transform_node.m_parent)),
		m_childs(std::move(transform_node.m_childs)) {
		SetDirty();
	}

	TransformNode::~TransformNode() {
		RemoveAllChildNodes();
	}

	bool TransformNode::HasChildNode(SharedPtr< const Node > node) const {
		return std::find(m_childs.begin(), m_childs.end(), node) != m_childs.end();
	}

	void TransformNode::RemoveAllChildNodes() noexcept {
		
		ForEachChildTransformNode([](TransformNode &transform_node) {
			transform_node.m_parent = nullptr;
			transform_node.SetDirty();
		});

		m_childs.clear();
	}

	//-------------------------------------------------------------------------
	// Node
	//-------------------------------------------------------------------------

	Node::Node()
		: m_transform(new TransformNode()), 
		m_active(true) {}
	
	Node::Node(const Node &node)
		: m_transform(new TransformNode(*node.m_transform)),
		m_active(node.m_active) {

		m_transform->ForEachChildNode([this](const Node &child_node) {
			AddChildNode(child_node.Clone());
		});
	}

	Node::Node(Node &&node) = default;

	Node::~Node() = default;

	UniquePtr< Node > Node::CloneImplementation() const {
		return MakeUnique< Node >(*this);
	}

	void Node::SetActive(bool active) noexcept {
		if (m_active != active) {
			m_active = active;

			ForEachChildNode([active](Node &node) {
				node.SetActive(active);
			});
		}
	}

	void Node::AddChildNode(SharedPtr< Node > node) {
		if (!node || node->m_transform->m_parent == this) {
			return;
		}

		if (node->m_transform->m_parent) {
			node->m_transform->m_parent->RemoveChildNode(node);
		}

		node->m_transform->m_parent = this;
		node->m_transform->SetDirty();

		m_transform->m_childs.push_back(std::move(node));
	}

	void Node::RemoveChildNode(SharedPtr< Node > node) {
		if (!node || node->m_transform->m_parent != this) {
			return;
		}

		node->m_transform->m_parent = nullptr;
		node->m_transform->SetDirty();

		const auto it = std::find(m_transform->m_childs.begin(), m_transform->m_childs.end(), node);
		if (it != m_transform->m_childs.end()) {
			m_transform->m_childs.erase(it);
		}
		else {
			Fatal("Node connections are broken.");
		}
	}
}