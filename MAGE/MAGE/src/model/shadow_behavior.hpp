#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A struct of shadow behaviors.
	 */
	struct ShadowBehavior final {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a shadow behavior.

		 @param[in]		cast_shadows
						The shadow casting value.
		 @param[in]		recieve_shadows
						The shadow recieving value.
		 */
		explicit ShadowBehavior(bool cast_shadows = true, bool recieve_shadows = true)
			: m_cast_shadows(cast_shadows), m_recieve_shadows(recieve_shadows) {}
		
		/**
		 Constructs a shadow behavior from the given shadow behavior.

		 @param[in]		shadow_behavior
						A reference to the shadow behavior to copy.
		 */
		ShadowBehavior(const ShadowBehavior &shadow_behavior) = default;

		/**
		 Constructs a shadow behavior by moving the given shadow behavior.

		 @param[in]		shadow_behavior
						A reference to the shadow behavior to move.
		 */
		ShadowBehavior(ShadowBehavior &&shadow_behavior) = default;

		/**
		 Destructs this shadow behavior.
		 */
		~ShadowBehavior() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given shadow behavior to this shadow behavior.

		 @param[in]		shadow_behavior
						A reference to the shadow behavior to copy.
		 @return		A reference to the copy of the given shadow behavior
						(i.e. this shadow behavior).
		 */
		ShadowBehavior &operator=(const ShadowBehavior &shadow_behavior) = default;

		/**
		 Moves the given shadow behavior to this shadow behavior.

		 @param[in]		shadow_behavior
						A reference to the shadow behavior to move.
		 @return		A reference to the moved shadow behavior
						(i.e. this shadow behavior).
		 */
		ShadowBehavior &operator=(ShadowBehavior &&shadow_behavior) = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether shadow casting applies or not for this shadow behavior.

		 @return		@c true shadow casting applies for this shadow behavior.
						@c false otherwise.
		 */
		bool CastShadows() const noexcept {
			return m_cast_shadows;
		}

		/**
		 Enables shadow casting for this shadow behavior.
		 */
		void EnableShadowCasting() noexcept {
			SetShadowCasting(true);
		}

		/**
		 Dissables shadow casting for this shadow behavior.
		 */
		void DissableShadowCasting() noexcept {
			SetShadowCasting(false);
		}

		/**
		 Sets the shadow casting of this shadow behavior to the given value.

		 @param[in]		cast_shadows
						The shadow casting value.
		 */
		void SetShadowCasting(bool cast_shadows) noexcept {
			m_cast_shadows = cast_shadows;
		}

		/**
		 Checks whether shadow recieving applies or not for this shadow behavior.

		 @return		@c true shadow recieving applies for this shadow behavior.
						@c false otherwise.
		 */
		bool RecieveShadows() const noexcept {
			return m_recieve_shadows;
		}

		/**
		 Enables shadow recieving for this shadow behavior.
		 */
		void EnableShadowRecieving() noexcept {
			SetShadowRecieving(true);
		}

		/**
		 Dissables shadow recieving for this shadow behavior.
		 */
		void DissableShadowRecieving() noexcept {
			SetShadowRecieving(false);
		}

		/**
		 Sets the shadow recieving of this shadow behavior to the given value.

		 @param[in]		recieve_shadows
						The shadow recieving value.
		 */
		void SetShadowRecieving(bool recieve_shadows) noexcept {
			m_recieve_shadows = recieve_shadows;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 A flag indicating whether shadow casting applies 
		 or not for this shadow behavior.
		 */
		bool m_cast_shadows;

		/**
		 A flag indicating whether shadow recieving applies 
		 or not for this shadow behavior.
		 */
		bool m_recieve_shadows;
	};
}
