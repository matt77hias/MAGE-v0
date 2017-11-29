//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.hpp"
#include "utils\logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// TransformNode
	//-------------------------------------------------------------------------

	TransformNode::TransformNode()
		: m_transform(),
		m_parent(nullptr), 
		m_childs() {
		
		SetDirty();
	}

	TransformNode::TransformNode(const TransformNode &transform_node)
		: m_transform(transform_node.m_transform),
		m_parent(nullptr), 
		m_childs() {
		
		SetDirty();
	}

	TransformNode::TransformNode(TransformNode &&transform_node) noexcept
		: m_transform(std::move(transform_node.m_transform)),
		m_parent(std::move(transform_node.m_parent)),
		m_childs(std::move(transform_node.m_childs)) {

		SetDirty();
	}

	TransformNode::~TransformNode() = default;

	bool TransformNode::HasChildNode(const Node *node) const {
		return std::find(m_childs.begin(), m_childs.end(), node) 
			!= m_childs.end();
	}

	void TransformNode::RemoveAllChildNodes() noexcept {

		ForEachChildTransformNode([](TransformNode *transform_node) {
			transform_node->m_parent = nullptr;
			transform_node->SetDirty();
		});

		m_childs.clear();
	}

	//-------------------------------------------------------------------------
	// Node
	//-------------------------------------------------------------------------

	IdGenerator Node::s_guid_generator;

	Node::Node(string name)
		: m_guid(s_guid_generator.GetNextId()),
		m_name(std::move(name)),
		m_active(true), 
		m_terminated(false),
		m_transform(MakeUnique< TransformNode >()) {}
	
	Node::Node(const Node &node)
		: m_guid(s_guid_generator.GetNextId()),
		m_name(node.m_name),
		m_active(node.m_active), 
		m_terminated(node.m_terminated),
		m_transform(MakeUnique< TransformNode >(*node.m_transform)) {}

	Node::Node(Node &&node) = default;

	Node::~Node() = default;

	UniquePtr< Node > Node::CloneImplementation() const {
		return MakeUnique< Node >(*this);
	}

	void Node::SetActive(bool active) noexcept {
		if (m_terminated || (m_active == active)) {
			return;
		}

		m_active = active;

		ForEachChildNode([active](Node *node) {
			node->SetActive(active);
		});

		OnActiveChange();
	}

	void Node::OnActiveChange() noexcept {}

	void Node::Terminate() noexcept {
		if (m_terminated) {
			return;
		}

		m_terminated = true;
		m_active     = false;

		ForEachChildNode([](Node *node) {
			node->Terminate();
		});
	
		OnActiveChange();
	}

	void Node::AddChildNode(Node *node) {
		if (!node || this == node->m_transform->m_parent 
			|| IsTerminated() || node->IsTerminated()) {
			return;
		}

		if (node->m_transform->m_parent) {
			node->m_transform->m_parent->RemoveChildNode(node);
		}

		node->m_transform->m_parent = this;
		node->m_transform->SetDirty();

		m_transform->m_childs.push_back(node);
	}

	void Node::RemoveChildNode(Node *node) {
		if (!node || this != node->m_transform->m_parent) {
			return;
		}

		node->m_transform->m_parent = nullptr;
		node->m_transform->SetDirty();

		if (const auto it = std::find(
			m_transform->m_childs.begin(), 
			m_transform->m_childs.end(), node); 
			it != m_transform->m_childs.end()) {

			m_transform->m_childs.erase(it);
		}
		else {
			Fatal("Node connections are broken.");
		}
	}
}