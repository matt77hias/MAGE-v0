#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// System Includes
//-----------------------------------------------------------------------------
#pragma region

#include <windowsx.h>

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Adds an item associated with the given data and described with the given
	 descriptor to a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			@a desc is not equal to @c nullptr.
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
	 Adds an item associated with the given data and described with the given
	 descriptor to a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			@a desc is not equal to @c nullptr.
	 @tparam		The data type.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		data
					The data of the item to add.
	 @param[in]		desc
					The description of the item to add.
	 @note			This function casts @a data to @c void*.
	 */
	template< typename DataT >
	inline void ComboBoxAddData(HWND dialog, int id, const DataT data, const wchar_t *desc) {
		ComboBoxAdd(dialog, id, (const void *)data, desc);
	}

	/**
	 Selects the item at the given index in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
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

	 @pre			@a dialog is not equal to @c nullptr.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		data
					A pointer to the data of the item.
	 */
	void ComboBoxSelect(HWND dialog, int id, const void *data);

	/**
	 Selects the item associated with the given data in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @tparam		The data type.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		data
					The data of the item to add.
	 @note			This function casts @a data to @c void*.
	 */
	template< typename DataT >
	inline void ComboBoxSelectData(HWND dialog, int id, const DataT data) {
		ComboBoxSelect(dialog, id, (const void *)data);
	}

	/**
	 Returns the data associated with the selected item in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		@c nullptr if the combo box has no items.
	 @return		A pointer to the data associated with the selected item in the combo box.
	 */
	const void *ComboBoxSelected(HWND dialog, int id);

	/**
	 Returns the data associated with the selected item in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			The combo box must have at least one item.
	 @tparam		The data type.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The data associated with the selected item in the combo box.
	 @note			This function converts the @c void* data to @c DataT data.
	 */
	template< typename DataT >
	inline const DataT ComboBoxSelectedData(HWND dialog, int id) {
		return static_cast< const DataT >(PtrToUlong(ComboBoxSelected(dialog, id)));
	}

	/**
	 Checks whether a valid item is selected in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
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

	 @pre			@a dialog is not equal to @c nullptr.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The number of items of a combo box.	
	 */
	int ComboBoxCount(HWND dialog, int id);

	/**
	 Checks whether a combo box contains the given descriptor.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			@a desc is not equal to @c nullptr.
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
