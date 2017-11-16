#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "utils\platform\windows.hpp"

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

	//-------------------------------------------------------------------------
	// ComboBoxAdd
	//-------------------------------------------------------------------------

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
	void ComboBoxAdd(HWND dialog, int id, const void *data, 
		const wchar_t *desc) noexcept;
	
	/**
	 Adds an item associated with the given value and described with the given
	 descriptor to a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			@a desc is not equal to @c nullptr.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		value
					The value of the item to add.
	 @param[in]		desc
					The description of the item to add.
	 */
	inline void ComboBoxAddValue(HWND dialog, int id, size_t value, 
		const wchar_t *desc) noexcept {
		
		ComboBoxAdd(dialog, id, (const void *)value, desc);
	}
	
	/**
	 Adds an item associated with the given pointer and described with the 
	 given descriptor to a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			@a desc is not equal to @c nullptr.
	 @tparam		T
					The data type.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		ptr
					The pointer of the item to add.
	 @param[in]		desc
					The description of the item to add.
	 */
	template< typename T >
	inline void ComboBoxAddPtr(HWND dialog, int id, const T *ptr, 
		const wchar_t *desc) noexcept {

		ComboBoxAdd(dialog, id, (const void *)ptr, desc);
	}

	//-------------------------------------------------------------------------
	// ComboBoxSelect
	//-------------------------------------------------------------------------

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
	void ComboBoxSelect(HWND dialog, int id, int index) noexcept;

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
	void ComboBoxSelect(HWND dialog, int id, const void *data) noexcept;
	
	/**
	 Selects the item associated with the given value in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		value
					The value of the item to add.
	 */
	inline void ComboBoxSelectValue(HWND dialog, int id, size_t value) noexcept {
		ComboBoxSelect(dialog, id, (const void *)value);
	}
	
	/**
	 Selects the item associated with the given pointer in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @tparam		T
					The data type.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		ptr
					The pointer of the item to add.
	 */
	template< typename T >
	inline void ComboBoxSelectPtr(HWND dialog, int id, const T *ptr) noexcept {
		ComboBoxSelect(dialog, id, (const void *)ptr);
	}

	//-------------------------------------------------------------------------
	// ComboBoxSelected
	//-------------------------------------------------------------------------
	
	/**
	 Returns the data associated with the selected item in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		@c nullptr if the combo box has no items.
	 @return		A pointer to the data associated with the selected item in 
					the combo box.
	 */
	const void *ComboBoxSelected(HWND dialog, int id) noexcept;

	/**
	 Returns the value associated with the selected item in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			The combo box must have at least one item.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The value associated with the selected item in a combo box.
	 @note			This function converts the @c void* data to @c size_t data.
	 */
	inline size_t ComboBoxSelectedValue(HWND dialog, int id) noexcept {
		return static_cast< size_t >(PtrToUlong(ComboBoxSelected(dialog, id)));
	}

	/**
	 Returns the pointer associated with the selected item in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @pre			The combo box must have at least one item.
	 @tparam		T
					The data type.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The pointer associated with the selected item in a combo box.
	 @note			This function converts the @c void* data to @c DataT* data.
	 */
	template< typename T >
	inline const T *ComboBoxSelectedPtr(HWND dialog, int id) noexcept {
		return static_cast< const T * >(ComboBoxSelected(dialog, id));
	}

	//-------------------------------------------------------------------------
	// ComboBoxSomethingSelected
	//-------------------------------------------------------------------------

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
	bool ComboBoxSomethingSelected(HWND dialog, int id) noexcept;

	//-------------------------------------------------------------------------
	// ComboBoxCount
	//-------------------------------------------------------------------------

	/**
	 Returns the number of items in a combo box.

	 @pre			@a dialog is not equal to @c nullptr.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The number of items of a combo box.	
	 */
	int ComboBoxCount(HWND dialog, int id) noexcept;

	//-------------------------------------------------------------------------
	// ComboBoxContains
	//-------------------------------------------------------------------------

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
	 @return		@c true if the given description is contained in the combo 
					box. @c false otherwise.
	 */
	bool ComboBoxContains(HWND dialog, int id, const wchar_t *desc) noexcept;
}
