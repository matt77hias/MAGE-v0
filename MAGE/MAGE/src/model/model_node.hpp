#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\transform_node.hpp"

// Models
#include "model\model.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class ModelNode : public Node {

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

		const string &GetName() const {
			return m_name;
		}

		void SetName(const string &name) {
			m_name = name;
		}

		Model *GetModel() {
			return m_model.get();
		}

		const Model *GetModel() const {
			return m_model.get();
		}

	private:

		virtual UniquePtr< Node > CloneImplementation() const override;

		string m_name;

		UniquePtr< Model > m_model;
	};
}