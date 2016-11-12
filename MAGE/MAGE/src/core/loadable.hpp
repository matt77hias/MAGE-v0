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

		/**
		 Checks wether this loadable is loaded.

		 @return		@c true if this loadable is loaded.
						@c false otherwise.
		 */
		bool IsLoaded() const {
			return m_loaded;
		}

	protected:

		/**
		 Constructs a loadable.

		 @param[in]		loaded
						Flag indicating wether the loadable is loaded.
		 */
		Loadable(bool loaded = false) : m_loaded(loaded) {}

		/**
		 Destructs this loadable.
		 */
		virtual ~Loadable() {}

		/**
		 Set the state of this loadable to the given value.

		 @param[in]		loaded
						Flag indicating wether this loadable is loaded.
		 */
		void SetLoaded(bool loaded = true) {
			m_loaded = loaded;
		}

	private:

		/**
		 Flag indicating wether this loadable is loaded.
		 */
		bool m_loaded;
	};
}