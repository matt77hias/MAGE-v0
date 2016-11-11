#pragma once

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <windowsx.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Adds an item associated with the given data and described with the given
	 descriptor to a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		data
					A pointer to the data of the item to add.
	 @param[in]		desc
					The description of the item to add.
	 */
	void ComboBoxAdd(HWND dialog, int id, const void *data, const wchar_t *desc);

	/**
	 Selects the item at the given index in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		index
					The index of the item.
	 */
	void ComboBoxSelect(HWND dialog, int id, int index);

	/**
	 Selects the item associated with the given data in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		data
					A pointer to the data of the item.
	 */
	void ComboBoxSelect(HWND dialog, int id, const void *data);

	/**
	 Returns the data associated with the selected item in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		@c NULL if the combo box has no items.
	 @return		A pointer to the data associated with the selected item in the combo box.
	 */
	const void *ComboBoxSelected(HWND dialog, int id);

	/**
	 Checks whether a valid item is selected in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		@c true if a valid item is selected in the combo box.
					@c false otherwise.
	 */
	bool ComboBoxSomethingSelected(HWND dialog, int id);

	/**
	 Returns the number of items in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The number of items of a combo box.	
	 */
	int ComboBoxCount(HWND dialog, int id);

	/**
	 Checks whether a combo box contains the given descriptor.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		desc
					The string description to check.
	 @return		@c true if the given description is contained in the combo box.
					@c false otherwise.
	 */
	bool ComboBoxContains(HWND dialog, int id, const wchar_t *desc);
}
