//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "ui\combo_box.hpp"
#include "logging\error.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	void ComboBoxAdd(HWND dialog, int id, const void *data, 
		const wchar_t *desc) noexcept {

		Assert(dialog);
		Assert(desc);

		// Retrieve a handle to a control in the specified dialog box.
		HWND control = GetDlgItem(dialog, id);
		
		// Add a string to a list in a combo box and
		// return the index of the string in the list.
		const int i = ComboBox_AddString(control, desc);
		
		// Set the application-defined value associated with the specified list 
		// item in a combo box. 
		ComboBox_SetItemData(control, i, data);
	}

	void ComboBoxSelect(HWND dialog, int id, int index) noexcept {
		
		Assert(dialog);
		
		// Retrieve a handle to a control in the specified dialog box.
		HWND control = GetDlgItem(dialog, id);
		
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
		PostMessage(dialog, WM_COMMAND, 
			MAKEWPARAM(id, CBN_SELCHANGE), (LPARAM)control);
	}

	void ComboBoxSelect(HWND dialog, int id, const void *data) noexcept {
		
		Assert(dialog);
		
		// Retrieve a handle to a control in the specified dialog box.
		HWND control = GetDlgItem(dialog, id);
		
		for (int i = 0; i < ComboBoxCount(dialog, id); ++i) {
			// Get the application-defined value associated with the specified 
			// list item in a combo box. 
			if ((void*)ComboBox_GetItemData(control, i) == data) {
				
				// Set the currently selected item in a combo box.
				ComboBox_SetCurSel(control, i);
				
				// Place (posts) a message in the message queue associated with 
				// the thread that created the specified window and returns without 
				// waiting for the thread to process the message.
				// 1. A handle to the window whose window procedure is to receive 
				// the message.
				// 2. The message to be posted.
				// 3. Control identifier.
				// 4. Handle to the control window.
				PostMessage(dialog, WM_COMMAND, 
					MAKEWPARAM(id, CBN_SELCHANGE), (LPARAM)control);
				
				break;
			}
		}
	}

	const void *ComboBoxSelected(HWND dialog, int id) noexcept {
		
		Assert(dialog);
		
		// Retrieve a handle to a control in the specified dialog box.
		HWND control = GetDlgItem(dialog, id);
		
		// Get the currently selected item in a combo box.
		const int index = ComboBox_GetCurSel(control);
		if (index < 0) {
			return nullptr;
		}
		
		// Get the application-defined value associated with the specified list 
		// item in a combo box. 
		return (void*)ComboBox_GetItemData(control, index);
	}

	bool ComboBoxSomethingSelected(HWND dialog, int id) noexcept {
		
		Assert(dialog);
		
		// Retrieve a handle to a control in the specified dialog box.
		HWND control = GetDlgItem(dialog, id);
		
		// Get the currently selected item in a combo box.
		const int index = ComboBox_GetCurSel(control);
		
		return (index >= 0);
	}

	int ComboBoxCount(HWND dialog, int id) noexcept {
		
		Assert(dialog);
		
		// Retrieve a handle to a control in the specified dialog box.
		HWND control = GetDlgItem(dialog, id);
		
		// Gets the number of items in the list box of a combo box.
		return ComboBox_GetCount(control);
	}

	bool ComboBoxContains(HWND dialog, int id, const wchar_t *desc) noexcept {
		
		Assert(dialog);
		Assert(desc);
		
		// Retrieve a handle to a control in the specified dialog box.
		HWND control = GetDlgItem(dialog, id);
		
		wchar_t item[MAX_PATH];
		for (int i = 0; i < ComboBoxCount(dialog, id); ++i) {
			
			// Gets a string from a list in a combo box.
			ComboBox_GetLBText(control, i, item);
			
			// Compares (case-sensitive) two character strings.
			if (lstrcmp(item, desc) == 0) {
				return true;
			}
		}
		
		return false;
	}
}