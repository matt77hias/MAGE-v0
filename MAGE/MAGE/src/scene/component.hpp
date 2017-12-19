#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "scene\state.hpp"
#include "utils\type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// Component
	//-------------------------------------------------------------------------
	#pragma region

	// Forward declaration.
	class Node;

	/**
	 A class of components.
	 */
	class Component {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------	

		/**
		 Destructs this component.
		 */
		virtual ~Component();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------	

		/**
		 Copies the given component to this component.

		 @param[in]		script
						A reference to the component to copy.
		 @return		A reference to the copy of the given component (i.e. 
						this component).
		 */
		Component &operator=(const Component &script) noexcept;

		/**
		 Moves the given component to this component.

		 @param[in]		script
						A reference to the component to move.
		 @return		A reference to the moved component (i.e. this 
						component).
		 */
		Component &operator=(Component &&script) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: State
		//---------------------------------------------------------------------

		/**
		 Returns the state of this component.

		 @return		The state of this component.
		 */
		State GetState() const noexcept {
			return m_state;
		}

		/**
		 Sets the state of this component to the given state.
		
		 @param[in]		state
						The state.
		 */
		void SetState(State state) noexcept;

		//---------------------------------------------------------------------
		// Member Methods: Identification
		//---------------------------------------------------------------------

		/**
		 Checks whether this component has an owner.

		 @return		@c true if this component has an owner. @c false 
						otherwise.
		 */
		bool HasOwner() const noexcept {
			return bool(m_owner);
		}

		/**
		 Returns the owner of this component.

		 @return		A pointer to the owner of this component.
		 */
		ProxyPtr< Node > GetOwner() noexcept {
			return m_owner;
		}

		/**
		 Returns the owner of this component.

		 @return		A pointer to the owner of this component.
		 */
		ProxyPtr< const Node > GetOwner() const noexcept {
			return m_owner;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a component.
		 */
		Component() noexcept;

		/**
		 Constructs a component from the given component.

		 @param[in]		component
						A reference to the component to copy.
		 */
		Component(const Component &component) noexcept;

		/**
		 Constructs a component by moving the given component.

		 @param[in]		component
						A reference to the component to move.
		 */
		Component(Component &&component) noexcept;

	private:

		//---------------------------------------------------------------------
		// Friends
		//---------------------------------------------------------------------

		friend class ComponentClient;

		//---------------------------------------------------------------------
		// Member Methods: Update
		//---------------------------------------------------------------------

		/**
		 Sets the owner of this component to the given owner.

		 @param[in]		owner
						A pointer to the owner.
		 */
		void SetOwner(ProxyPtr< Node > owner) noexcept {
			m_owner = std::move(owner);
		}

		//---------------------------------------------------------------------
		// Member Variables: State
		//---------------------------------------------------------------------

		/**
		 The state of this component.
		 */
		State m_state;

		//---------------------------------------------------------------------
		// Member Variables: Identification
		//---------------------------------------------------------------------

		/**
		 A pointer to the node owning this component.
		 */
		ProxyPtr< Node > m_owner;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// ComponentClient
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of component clients.
	 */
	class ComponentClient final {

	public:

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		ComponentClient &operator=(const ComponentClient &client) = delete;
		ComponentClient &operator=(ComponentClient &&client) = delete;

	private:

		//---------------------------------------------------------------------
		// Friends
		//---------------------------------------------------------------------

		friend class Node;

		//---------------------------------------------------------------------
		// Static Member Methods
		//---------------------------------------------------------------------

		/**
		 Sets the owner of the given component to the given owner.

		 @param[in]		component
						A reference to the component.
		 @param[in]		owner
						A pointer to the owner.
		 */
		static void SetOwner(Component &component, ProxyPtr< Node > owner) noexcept {
			component.SetOwner(std::move(owner));
		}

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		ComponentClient() = delete;
		ComponentClient(const ComponentClient &client) = delete;
		ComponentClient(ComponentClient &&client) = delete;
		~ComponentClient() = delete;
	};

	#pragma endregion
}