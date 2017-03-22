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
		Loadable(bool loaded = false) 
			: m_loaded(loaded) {}

		/**
		 Constructs a loadable from the given loadable.

		 @param[in]		loadable
						A reference to the loadable.
		 */
		Loadable(const Loadable &loadable) = default;

		/**
		 Constructs a loadable from the given loadable.

		 @param[in]		loadable
						A reference to the loadable.
		 */
		Loadable(Loadable &&loadable) = default;

		/**
		 Destructs this loadable.
		 */
		virtual ~Loadable() = default;

		/**
		 Copies the given loadable to this loadable.

		 @param[in]		loadable
						A reference to the loadable to copy from.
		 @return		A reference to the copy of the given loadable
						(i.e. this loadable).
		 */
		Loadable &operator=(const Loadable &loadable) = default;

		/**
		 Copies the given loadable to this loadable.

		 @param[in]		loadable
						A reference to the loadable to copy from.
		 @return		A reference to the copy of the given loadable
						(i.e. this loadable).
		 */
		Loadable &operator=(Loadable &&loadable) = default;

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