#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "math\transform_node.hpp"
#include "light\light.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// LightNode
	//-------------------------------------------------------------------------

	/**
	 A class of light nodes.
	 */
	class LightNode : public Node {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this light node.
		 */
		virtual ~LightNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given light node to this light node.

		 @param[in]		light_node
						A reference to the light node to copy.
		 @return		A reference to the copy of the given light node (i.e. 
						this light node).
		 */
		LightNode &operator=(const LightNode &light_node) = delete;

		/**
		 Moves the given light node to this light node.

		 @param[in]		light_node
						A reference to the light node to move.
		 @return		A reference to the moved light node (i.e. this light 
						node).
		 */
		LightNode &operator=(LightNode &&light_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this light node.

		 @return		A pointer to the clone of this light node.
		 */
		UniquePtr< LightNode > Clone() const {
			return static_pointer_cast< LightNode >(CloneImplementation());
		}

		/**
		 Returns the light of this light node.

		 @return		A pointer to the light of this light node.
		 */
		Light *GetLight() noexcept {
			return m_light.get();
		}

		/**
		 Returns the light of this light node.

		 @return		A pointer to the light of this light node.
		 */
		const Light *GetLight() const noexcept {
			return m_light.get();
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a light node.

		 @pre			@a light refers to a non @c nullptr.
		 @param[in]		light
						A reference to the light to move.
		 */
		explicit LightNode(UniquePtr< Light > &&light);

		/**
		 Constructs a light node from the given light node.

		 @param[in]		light_node
						A reference to the light node to copy.
		 */
		LightNode(const LightNode &light_node);

		/**
		 Constructs a light node by moving the given light node.

		 @param[in]		light_node
						A reference to the light node to move.
		 */
		LightNode(LightNode &&light_node);

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		Clones this light node.

		@return		A pointer to the clone of this light node.
		*/
		virtual UniquePtr< Node > CloneImplementation() const override = 0;

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A pointer to the light of this light node.
		 */
		UniquePtr< Light > m_light;
	};

	//-------------------------------------------------------------------------
	// DerivedLightNode
	//-------------------------------------------------------------------------

	/**
	 A class of derived light nodes.

	 @tparam		LightT
					The light type.
	 */
	template< typename LightT >
	class DerivedLightNode final : public LightNode {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a derived light node.
		 */
		DerivedLightNode();

		/**
		 Constructs a derived light node from the given derived light node.

		 @param[in]		light_node
						A reference to the derived light node to copy.
		 */
		DerivedLightNode(const DerivedLightNode &light_node);

		/**
		 Constructs a derived light node by moving the given derived light node.

		 @param[in]		light_node
						A reference to the derived light node to move.
		 */
		DerivedLightNode(DerivedLightNode &&light_node);

		/**
		 Destructs this derived light node.
		 */
		virtual ~DerivedLightNode();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given derived light node to this derived light node.

		 @param[in]		light_node
						A reference to the derived light node to copy.
		 @return		A reference to the copy of the given derived light 
						node (i.e. this derived light node).
		 */
		DerivedLightNode &operator=(
			const DerivedLightNode &light_node) = delete;

		/**
		 Moves the given derived light node to this derived light node.

		 @param[in]		light_node
						A reference to the derived light node to move.
		 @return		A reference to the moved derived light node (i.e. this 
						derived light node).
		 */
		DerivedLightNode &operator=(
			DerivedLightNode &&light_node) = delete;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this derived light node.

		 @return		A pointer to the clone of this derived light node.
		 */
		UniquePtr< DerivedLightNode > Clone() const {
			return static_pointer_cast< DerivedLightNode >(CloneImplementation());
		}

		/**
		 Returns the light of this derived light node.

		 @return		A pointer to the light of this derived light node.
		 */
		LightT *GetLight() noexcept {
			return static_cast< LightT * >(LightNode::GetLight());
		}

		/**
		 Returns the light of this derived light node.

		 @return		A pointer to the light of this derived light node.
		 */
		const LightT *GetLight() const noexcept {
			return static_cast< const LightT * >(LightNode::GetLight());
		}

	private:

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Clones this derived light node.

		 @return		A pointer to the clone of this derived light node.
		 */
		virtual UniquePtr< Node > CloneImplementation() const override;
	};
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "light\light_node.tpp"

#pragma endregion