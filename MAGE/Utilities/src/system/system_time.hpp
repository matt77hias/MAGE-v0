#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <chrono>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// System Time
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Returns the current local system date as a string.

	 @return		The current local system date as a string.
	 */
	[[nodiscard]]
	const std::wstring GetLocalSystemDateAsString();

	/**
	 Returns the current local system time as a string.

	 @return		The current local system time as a string.
	 */
	[[nodiscard]]
	const std::wstring GetLocalSystemTimeAsString();

	/**
	 Returns the current local system date and time as a string.

	 @return		The current local system date and time as a string.
	 */
	[[nodiscard]]
	const std::wstring GetLocalSystemDateAndTimeAsString();

	struct SystemClock {
		using rep        = U64;
		using period     = std::ratio< 1, 10'000'000 >;
		using duration   = std::chrono::duration< rep, period >;
		using time_point = std::chrono::time_point< SystemClock >;

		static constexpr bool is_steady = true;

		[[nodiscard]]
		static const time_point now() noexcept;
	};

	#pragma endregion

	//-------------------------------------------------------------------------
	// Core Time
	//-------------------------------------------------------------------------
	#pragma region

	struct CoreClock {
		using rep        = U64;
		using period     = std::ratio< 1, 10'000'000 >;
		using duration   = std::chrono::duration< rep, period >;
		using time_point = std::chrono::time_point< CoreClock >;

		static constexpr bool is_steady = true;

		[[nodiscard]]
		static const time_point now() noexcept;
	};

	struct KernelModeCoreClock {
		using rep        = U64;
		using period     = std::ratio< 1, 10'000'000 >;
		using duration   = std::chrono::duration< rep, period >;
		using time_point = std::chrono::time_point< KernelModeCoreClock >;

		static constexpr bool is_steady = true;

		[[nodiscard]]
		static const time_point now() noexcept;
	};

	struct UserModeCoreClock {
		using rep        = U64;
		using period     = std::ratio< 1, 10'000'000 >;
		using duration   = std::chrono::duration< rep, period >;
		using time_point = std::chrono::time_point< UserModeCoreClock >;

		static constexpr bool is_steady = true;

		[[nodiscard]]
		static const time_point now() noexcept;
	};

	struct CoreClockPerCore {
		using rep        = U64;
		using period     = std::ratio< 1, 10'000'000 >;
		using duration   = std::chrono::duration< rep, period >;
		using time_point = std::chrono::time_point< CoreClockPerCore >;

		static constexpr bool is_steady = true;

		[[nodiscard]]
		static const time_point now() noexcept;
	};

	struct KernelModeCoreClockPerCore {
		using rep        = U64;
		using period     = std::ratio< 1, 10'000'000 >;
		using duration   = std::chrono::duration< rep, period >;
		using time_point = std::chrono::time_point< KernelModeCoreClockPerCore >;

		static constexpr bool is_steady = true;

		[[nodiscard]]
		static const time_point now() noexcept;
	};

	struct UserModeCoreClockPerCore {
		using rep        = U64;
		using period     = std::ratio< 1, 10'000'000 >;
		using duration   = std::chrono::duration< rep, period >;
		using time_point = std::chrono::time_point< UserModeCoreClockPerCore >;

		static constexpr bool is_steady = true;

		[[nodiscard]]
		static const time_point now() noexcept;
	};

	#pragma endregion
}