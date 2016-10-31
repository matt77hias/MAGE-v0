#pragma once

namespace mage {
	
	/**
	 A class of sounds.
	 */
	class Sound {

	public:

		/**
		 Constructs a sound.

		 @param[in]		filename
						A reference to the filename.
		 */
		Sound(const string &filename);

		/**
		 Destructs a sound.
		 */
		virtual ~Sound();
	};
}