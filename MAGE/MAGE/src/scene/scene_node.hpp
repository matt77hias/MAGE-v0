#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of scene nodes.
	 */
	class SceneNode : public Node {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a scene node.

		 @param[in]		name
						A reference to the name.
		 */
		explicit SceneNode(const string &name);

		/**
		 Constructs a scene node from the given scene node.

		 @param[in]		scene_node
						A reference to the scene node to copy.
		 */
		SceneNode(const SceneNode &scene_node);

		/**
		 Constructs a scene node by moving the given scene node.

		 @param[in]		scene_node
						A reference to the scene node to move.
		 */
		SceneNode(SceneNode &&scene_node);

		/**
		 Destructs this scene node.
		 */
		virtual ~SceneNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given scene node to this scene node.

		 @param[in]		scene_node
						A reference to the scene node to copy.
		 @return		A reference to the copy of the given scene node (i.e. 
						this scene node).
		 */
		SceneNode &operator=(const SceneNode &scene_node) = delete;

		/**
		 Moves the given scene node to this scene node.

		 @param[in]		scene_node
						A reference to the scene node to move.
		 @return		A reference to the moved scene node (i.e. this scene 
						node).
		 */
		SceneNode &operator=(SceneNode &&scene_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this scene node.

		 @return		A pointer to the clone of this scene node.
		 */
		UniquePtr< SceneNode > Clone() const {
			return static_pointer_cast< SceneNode >(CloneImplementation());
		}

		/**
		 Returns the name of this scene node.

		 @return		A reference to the name of this scene node.
		 */
		const string &GetName() const noexcept {
			return m_name;
		}

		/**
		 Sets the name of this scene node to the given string.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(const string &name) {
			m_name = name;
		}

		/**
		 Sets the name of this scene node to the given string.

		 @param[in]		name
						A reference to the name.
		 */
		void SetName(string &&name) noexcept {
			m_name = std::move(name);
		}

		/**
		 Sets the name of this scene node to the given string.

		 @pre			@a name is not equal to @c nullptr.
		 @param[in]		name
						A pointer to the name.
		 */
		void SetString(const char *name) {
			m_name = name;
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this scene node.

		 @return		A pointer to the clone of this scene node.
		 */
		virtual UniquePtr< Node > CloneImplementation() const override;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The name of this scene node.
		 */
		string m_name;
	};
}