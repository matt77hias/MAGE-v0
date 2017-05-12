#pragma once

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of loadables.
	 */
	class Loadable {

	public:

		//---------------------------------------------------------------------
		// Destructors
		//---------------------------------------------------------------------

		/**
		 Destructs this loadable.
		 */
		virtual ~Loadable() noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Checks whether this loadable is loaded.

		 @return		@c true if this loadable is loaded.
						@c false otherwise.
		 */
		bool IsLoaded() const noexcept {
			return m_loaded;
		}

	protected:

		//---------------------------------------------------------------------
		// Constructors
		//---------------------------------------------------------------------

		/**
		 Constructs a loadable.

		 @param[in]		loaded
						Flag indicating whether the loadable is loaded.
		 */
		explicit Loadable(bool loaded = false) noexcept;

		/**
		 Constructs a loadable from the given loadable.

		 @param[in]		loadable
						A reference to the loadable.
		 */
		Loadable(const Loadable &loadable) noexcept;

		/**
		 Constructs a loadable by moving the given loadable.

		 @param[in]		loadable
						A reference to the loadable.
		 */
		Loadable(Loadable &&loadable) noexcept;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given loadable to this loadable.

		 @param[in]		loadable
						A reference to the loadable to copy.
		 @return		A reference to the copy of the given loadable
						(i.e. this loadable).
		 */
		Loadable &operator=(const Loadable &loadable) noexcept;

		/**
		 Moves the given loadable to this loadable.

		 @param[in]		loadable
						A reference to the loadable to move.
		 @return		A reference to the moved loadable
						(i.e. this loadable).
		 */
		Loadable &operator=(Loadable &&loadable) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Set the state of this loadable to the given value.

		 @param[in]		loaded
						Flag indicating whether this loadable is loaded.
		 */
		void SetLoaded(bool loaded = true) noexcept {
			m_loaded = loaded;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 Flag indicating whether this loadable is loaded.
		 */
		bool m_loaded;
	};
}