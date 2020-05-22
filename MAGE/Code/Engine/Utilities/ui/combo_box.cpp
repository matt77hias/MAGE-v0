//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "ui\combo_box.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <windowsx.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ComboBoxAdd(NotNull< HWND > dialog, int id, const void* data,
					 NotNull< const_wzstring > desc) noexcept {

		// Retrieve a handle to a control in the specified dialog box.
		const auto control = NotNull< HWND >(GetDlgItem(dialog, id));

		// Add a string to a list in a combo box and return the index of the
		// string in the list.
		const auto index = ComboBox_AddString(control, desc);

		// Set the application-defined value associated with the specified list
		// item in a combo box.
		ComboBox_SetItemData(control, index, data);
	}

	void ComboBoxSelect(NotNull< HWND > dialog, int id, int index) noexcept {
		// Retrieve a handle to a control in the specified dialog box.
		const auto control = NotNull< HWND >(GetDlgItem(dialog, id));

		// Set the currently selected item in a combo box.
		ComboBox_SetCurSel(control, index);

		// Place (posts) a message in the message queue associated with the
		// thread that created the specified window and returns without waiting
		// for the thread to process the message.
		// 1. A handle to the window whose window procedure is to receive the
		// message.
		// 2. The message to be posted.
		// 3. Control identifier.
		// 4. Handle to the control window.
		PostMessage(dialog,
			        WM_COMMAND,
			        MAKEWPARAM(id, CBN_SELCHANGE),
			        (LPARAM)control.get());
	}

	void ComboBoxSelect(NotNull< HWND > dialog, int id, const void* data) noexcept {
		// Retrieve a handle to a control in the specified dialog box.
		const auto control = NotNull< HWND >(GetDlgItem(dialog, id));

		for (int index = 0; index < ComboBoxCount(dialog, id); ++index) {

			// Get the application-defined value associated with the specified
			// list item in a combo box.
			if (data == (void*)ComboBox_GetItemData(control, index)) {

				// Set the currently selected item in a combo box.
				ComboBox_SetCurSel(control, index);

				// Place (posts) a message in the message queue associated with
				// the thread that created the specified window and returns without
				// waiting for the thread to process the message.
				// 1. A handle to the window whose window procedure is to receive
				// the message.
				// 2. The message to be posted.
				// 3. Control identifier.
				// 4. Handle to the control window.
				PostMessage(dialog,
					        WM_COMMAND,
					        MAKEWPARAM(id, CBN_SELCHANGE),
					        (LPARAM)control.get());

				break;
			}
		}
	}

	[[nodiscard]]
	const void* ComboBoxSelected(NotNull< HWND > dialog, int id) noexcept {
		// Retrieve a handle to a control in the specified dialog box.
		const auto control = NotNull< HWND >(GetDlgItem(dialog, id));

		// Get the currently selected item in a combo box.
		const auto index = ComboBox_GetCurSel(control);

		// Get the application-defined value associated with the specified list
		// item in a combo box.
		return (0 > index) ? nullptr
			               : (void*)ComboBox_GetItemData(control, index);
	}

	[[nodiscard]]
	bool ComboBoxSomethingSelected(NotNull< HWND > dialog, int id) noexcept {
		// Retrieve a handle to a control in the specified dialog box.
		const auto control = NotNull< HWND >(GetDlgItem(dialog, id));

		// Get the currently selected item in a combo box.
		const auto index = ComboBox_GetCurSel(control);

		return (0 <= index);
	}

	[[nodiscard]]
	int ComboBoxCount(NotNull< HWND > dialog, int id) noexcept {
		// Retrieve a handle to a control in the specified dialog box.
		const auto control = NotNull< HWND >(GetDlgItem(dialog, id));

		// Gets the number of items in the list box of a combo box.
		return ComboBox_GetCount(control);
	}

	[[nodiscard]]
	bool ComboBoxContains(NotNull< HWND > dialog, int id,
						  NotNull< const_wzstring > desc) noexcept {

		// Retrieve a handle to a control in the specified dialog box.
		const auto control = NotNull< HWND >(GetDlgItem(dialog, id));

		wchar_t item[MAX_PATH];
		for (int index = 0; index < ComboBoxCount(dialog, id); ++index) {

			// Gets a string from a list in a combo box.
			ComboBox_GetLBText(control, index, item);

			// Compares (case-sensitive) two character strings.
			if (0 == lstrcmp(item, desc)) {
				return true;
			}
		}

		return false;
	}
}