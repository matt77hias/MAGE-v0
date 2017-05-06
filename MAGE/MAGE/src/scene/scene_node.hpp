#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "string\string.hpp"
#include "math\transform_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	class SceneNode : public Node {

	public:

		explicit SceneNode(const string &name);

		SceneNode(const SceneNode &scene_node);

		SceneNode(SceneNode &&scene_node);

		virtual ~SceneNode();

		SceneNode &operator=(const SceneNode &scene_node) = delete;

		SceneNode &operator=(SceneNode &&scene_node) = delete;

		UniquePtr< SceneNode > Clone() const {
			return static_pointer_cast< SceneNode >(CloneImplementation());
		}

		const string &GetName() const {
			return m_name;
		}

		void SetName(const string &name) {
			m_name = name;
		}

	private:

		virtual UniquePtr< Node > CloneImplementation() const override;

		string m_name;
	};
}