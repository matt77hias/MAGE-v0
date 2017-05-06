#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\scene_node.hpp"

// Models
#include "model\model.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ModelNode : public SceneNode {

	public:

		explicit ModelNode(const string &name, UniquePtr< Model > &&model);

		ModelNode(const ModelNode &model_node);

		ModelNode(ModelNode &&model_node);

		virtual ~ModelNode();

		ModelNode &operator=(const ModelNode &model_node) = delete;

		ModelNode &operator=(ModelNode &&model_node) = delete;

		UniquePtr< ModelNode > Clone() const {
			return static_pointer_cast< ModelNode >(CloneImplementation());
		}

		Model *GetModel() {
			return m_model.get();
		}

		const Model *GetModel() const {
			return m_model.get();
		}

	private:

		virtual UniquePtr< Node > CloneImplementation() const override;

		UniquePtr< Model > m_model;
	};
}