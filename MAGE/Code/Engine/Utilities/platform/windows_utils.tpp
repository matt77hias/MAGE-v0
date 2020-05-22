#pragma once

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	template< typename CallerT >
	[[nodiscard]]
	CallerT* GetWindowCaller(NotNull< HWND > window,
							 UINT message,
							 [[maybe_unused]] WPARAM wParam,
							 LPARAM lParam) noexcept {

		if (WM_NCCREATE != message) {
			// Retrieve user data information about the window.
			return reinterpret_cast< CallerT* >(
				GetWindowLongPtr(window, GWLP_USERDATA));
		}

		const auto caller = reinterpret_cast< CallerT* >(
			                reinterpret_cast< CREATESTRUCT* >(lParam)->lpCreateParams);

		// Change the user data attribute of the window.
		SetWindowLongPtr(window, GWLP_USERDATA,
			             reinterpret_cast< LONG_PTR >(caller));

		return caller;
	}

	template< typename CallerT >
	[[nodiscard]]
	CallerT* GetDialogCaller(NotNull< HWND > dialog,
							 UINT message,
							 [[maybe_unused]] WPARAM wParam,
							 LPARAM lParam) noexcept {

		if (WM_INITDIALOG != message) {
			// Retrieve user data information about the window.
			return reinterpret_cast< CallerT* >(
				GetWindowLongPtr(dialog, GWLP_USERDATA));
		}

		const auto caller = reinterpret_cast< CallerT* >(lParam);

		// Changes the user data attribute of the window.
		SetWindowLongPtr(dialog, GWLP_USERDATA,
			             reinterpret_cast< LONG_PTR >(caller));

		return caller;
	}
}