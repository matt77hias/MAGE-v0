#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "system\timer.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// GameTime
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of game times.
	 */
	class GameTime {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a game time.
		 */
		constexpr GameTime() noexcept
			: m_wall_clock_delta_time(TimeIntervalSeconds::zero()),
			m_wall_clock_total_delta_time(TimeIntervalSeconds::zero()),
			m_core_clock_delta_time(TimeIntervalSeconds::zero()),
			m_core_clock_total_delta_time(TimeIntervalSeconds::zero()) {}

		/**
		 Constructs a game time.

		 @param[in]		wall_clock_delta_time
						The wall clock delta time (in seconds).
		 @param[in]		wall_clock_total_delta_time
						The wall clock total delta time (in seconds).
		 @param[in]		core_clock_delta_time
						The core clock delta time (in seconds).
		 @param[in]		core_clock_total_delta_time
						The core clock total delta time (in seconds).
		 */
		constexpr explicit
			GameTime(TimeIntervalSeconds wall_clock_delta_time,
					 TimeIntervalSeconds wall_clock_total_delta_time,
					 TimeIntervalSeconds core_clock_delta_time,
					 TimeIntervalSeconds core_clock_total_delta_time) noexcept
			: m_wall_clock_delta_time(wall_clock_delta_time),
			m_wall_clock_total_delta_time(wall_clock_total_delta_time),
			m_core_clock_delta_time(core_clock_delta_time),
			m_core_clock_total_delta_time(core_clock_total_delta_time) {}

		/**
		 Constructs a game time from the given game time.

		 @param[in]		time
						A reference to the game time to copy.
		 */
		constexpr GameTime(const GameTime& time) noexcept = default;

		/**
		 Constructs a game time by moving the given game time.

		 @param[in]		time
						A reference to the game time to move.
		 */
		constexpr GameTime(GameTime&& time) noexcept = default;

		/**
		 Destructs this game time.
		 */
		~GameTime() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given game time to this game time.

		 @param[in]		time
						A reference to the game time to copy.
		 @return		A reference to the copy of the given game time (i.e.
						this game time).
		 */
		GameTime& operator=(const GameTime& time) noexcept = default;

		/**
		 Moves the given game time to this game time.

		 @param[in]		time
						A reference to the game time to move.
		 @return		A reference to the moved game time (i.e. this game
						time).
		 */
		GameTime& operator=(GameTime&& time) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Returns the wall clock delta time (in seconds) of this game time.

		 @return		The wall clock delta time (in seconds) of this game
						time.
		 */
		constexpr TimeIntervalSeconds GetWallClockDeltaTime() const noexcept {
			return m_wall_clock_delta_time;
		}

		/**
		 Returns the wall clock total delta time (in seconds) of this game time.

		 @return		The wall clock total delta time (in seconds) of this
						game time.
		 */
		constexpr TimeIntervalSeconds GetWallClockTotalDeltaTime() const noexcept {
			return m_wall_clock_total_delta_time;
		}

		/**
		 Returns the core clock delta time (in seconds) of this game time.

		 @return		The core clock delta time (in seconds) of this game
						time.
		 */
		constexpr TimeIntervalSeconds GetCoreClockDeltaTime() const noexcept {
			return m_core_clock_delta_time;
		}

		/**
		 Returns the core clock total delta time (in seconds) of this game time.

		 @return		The core clock total delta time (in seconds) of this
						game time.
		 */
		constexpr TimeIntervalSeconds GetCoreClockTotalDeltaTime() const noexcept {
			return m_core_clock_total_delta_time;
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The wall clock delta time (in seconds) of this game time.
		 */
		TimeIntervalSeconds m_wall_clock_delta_time;

		/**
		 The wall clock total delta time (in seconds) of this game time.
		 */
		TimeIntervalSeconds m_wall_clock_total_delta_time;

		/**
		 The core clock delta time (in seconds) of this game time.
		 */
		TimeIntervalSeconds m_core_clock_delta_time;

		/**
		 The core clock total delta time (in seconds) of this game time.
		 */
		TimeIntervalSeconds m_core_clock_total_delta_time;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// GameTimer
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 A class of game timers.
	 */
	class GameTimer {

	public:

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs a game timer.
		 */
		GameTimer() noexcept = default;

		/**
		 Constructs a game timer from the given game timer.

		 @param[in]		timer
						A reference to the game timer to copy.
		 */
		GameTimer(const GameTimer& timer) noexcept = default;

		/**
		 Constructs a game timer by moving the given game timer.

		 @param[in]		timer
						A reference to the game timer to move.
		 */
		GameTimer(GameTimer&& timer) noexcept = default;

		/**
		 Destructs this game timer.
		 */
		~GameTimer() = default;

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given game timer to this game timer.

		 @param[in]		timer
						A reference to the game timer to copy.
		 @return		A reference to the copy of the given game timer (i.e.
						this game timer).
		 */
		GameTimer& operator=(const GameTimer& timer) noexcept = default;

		/**
		 Moves the given game timer to this game timer.

		 @param[in]		timer
						A reference to the game timer to move.
		 @return		A reference to the moved game timer (i.e. this game
						timer).
		 */
		GameTimer& operator=(GameTimer&& timer) noexcept = default;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Starts this game timer.
		 */
		void Start() noexcept {
			m_wall_clock_timer.Start();
			m_core_clock_timer.Start();
		}

		/**
		 Stops this game timer.
		 */
		void Stop() noexcept {
			m_wall_clock_timer.Stop();
			m_core_clock_timer.Stop();
		}

		/**
		 Restarts this game timer.
		 */
		void Restart() noexcept {
			m_wall_clock_timer.Restart();
			m_core_clock_timer.Restart();
		}

		/**
		 Resumes this game timer.
		 */
		void Resume() noexcept {
			m_wall_clock_timer.Resume();
			m_core_clock_timer.Resume();
		}

		/**
		 Returns the game time of this game timer.

		 @return		The game time of this game timer.
		 */
		const GameTime GetTime() noexcept {
			const auto wall_clock_time = m_wall_clock_timer.GetTime();
			const auto core_clock_time = m_core_clock_timer.GetTime();

			return GameTime(wall_clock_time.first,
							wall_clock_time.second,
							core_clock_time.first,
							core_clock_time.second);
		}

	private:

		//---------------------------------------------------------------------
		// Member Variables
		//---------------------------------------------------------------------

		/**
		 The wall clock timer of this game timer.
		 */
		WallClockTimer m_wall_clock_timer;

		/**
		 The core clock per core timer of this game timer.
		 */
		CPUTimer m_core_clock_timer;
	};

	#pragma endregion
}