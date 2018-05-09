#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations and Definitions
//-----------------------------------------------------------------------------
namespace mage {

	//-------------------------------------------------------------------------
	// ComboBoxAdd
	//-------------------------------------------------------------------------
	#pragma region

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
	void ComboBoxAdd(NotNull< HWND > dialog, 
					 int id, 
					 const void* data, 
		             NotNull< const_wzstring > desc) noexcept;
	
	/**
	 Adds an item associated with the given value and described with the given
	 descriptor to a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		value
					The value of the item to add.
	 @param[in]		desc
					The description of the item to add.
	 */
	inline void ComboBoxAddValue(NotNull< HWND > dialog, 
								 int id, 
								 size_t value, 
								 NotNull< const_wzstring > desc) noexcept {
		
		ComboBoxAdd(dialog, id, (const void*)value, desc);
	}
	
	/**
	 Adds an item associated with the given pointer and described with the 
	 given descriptor to a combo box.

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
	inline void ComboBoxAddPtr(NotNull< HWND > dialog, 
							   int id, 
							   const T* ptr, 
							   NotNull< const_wzstring > desc) noexcept {

		ComboBoxAdd(dialog, id, (const void*)ptr, desc);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ComboBoxSelect
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Selects the item at the given index in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		index
					The index of the item.
	 */
	void ComboBoxSelect(NotNull< HWND > dialog, int id, int index) noexcept;

	/**
	 Selects the item associated with the given data in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		data
					A pointer to the data of the item.
	 */
	void ComboBoxSelect(NotNull< HWND > dialog, 
						int id, 
						const void* data) noexcept;
	
	/**
	 Selects the item associated with the given value in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		value
					The value of the item to add.
	 */
	inline void ComboBoxSelectValue(NotNull< HWND > dialog, 
									int id, 
									size_t value) noexcept {

		ComboBoxSelect(dialog, id, (const void*)value);
	}
	
	/**
	 Selects the item associated with the given pointer in a combo box.

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
	inline void ComboBoxSelectPtr(NotNull< HWND > dialog, 
								  int id, 
								  const T* ptr) noexcept {

		ComboBoxSelect(dialog, id, (const void*)ptr);
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ComboBoxSelected
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Returns the data associated with the selected item in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		@c nullptr if the combo box has no items.
	 @return		A pointer to the data associated with the selected item in 
					the combo box.
	 */
	[[nodiscard]]
	const void* ComboBoxSelected(NotNull< HWND > dialog, int id) noexcept;

	/**
	 Returns the value associated with the selected item in a combo box.

	 @pre			The combo box must have at least one item.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The value associated with the selected item in a combo box.
	 @note			This function converts the @c void * data to @c size_t data.
	 */
	[[nodiscard]]
	inline size_t ComboBoxSelectedValue(NotNull< HWND > dialog, int id) noexcept {

		return static_cast< size_t >(PtrToUlong(ComboBoxSelected(dialog, id)));
	}

	/**
	 Returns the pointer associated with the selected item in a combo box.

	 @pre			The combo box must have at least one item.
	 @tparam		T
					The data type.
	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The pointer associated with the selected item in a combo box.
	 @note			This function converts the @c void * data to @c T* data.
	 */
	template< typename T >
	[[nodiscard]]
	inline const T* ComboBoxSelectedPtr(NotNull< HWND > dialog, int id) noexcept {
		
		return static_cast< const T* >(ComboBoxSelected(dialog, id));
	}

	#pragma endregion

	//-------------------------------------------------------------------------
	// ComboBoxSomethingSelected
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Checks whether a valid item is selected in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		@c true if a valid item is selected in the combo box.
					@c false otherwise.
	 */
	[[nodiscard]]
	bool ComboBoxSomethingSelected(NotNull< HWND > dialog, int id) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// ComboBoxCount
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Returns the number of items in a combo box.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @return		The number of items of a combo box.	
	 */
	[[nodiscard]]
	int ComboBoxCount(NotNull< HWND > dialog, int id) noexcept;

	#pragma endregion

	//-------------------------------------------------------------------------
	// ComboBoxContains
	//-------------------------------------------------------------------------
	#pragma region

	/**
	 Checks whether a combo box contains the given descriptor.

	 @param[in]		dialog
					A handle to the dialog box that contains the control.
	 @param[in]		id
					The identifier of the control to be retrieved.
	 @param[in]		desc
					The string description to check.
	 @return		@c true if the given description is contained in the combo 
					box. @c false otherwise.
	 */
	[[nodiscard]]
	bool ComboBoxContains(NotNull< HWND > dialog, 
						  int id, 
						  NotNull< const_wzstring > desc) noexcept;

	#pragma endregion
}
