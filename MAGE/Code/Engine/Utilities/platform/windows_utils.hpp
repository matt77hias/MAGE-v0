#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "type\types.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 Returns the caller of @c CreateWindow or @c CreateWindowEx.

	 @pre			The @c lpParam formal parameter of @c CreateWindow or
					@c CreateWindowEx should be initialized to @c this and
					@c this should point to an instance of type @a CallerT.
	 @tparam		CallerT
					The caller type.
	 @param[in]		window
					A handle to the window.
	 @param[in]		message
					The message.
	 @param[in]		wParam
					Additional message-specific information.
	 @param[in]		lParam
					Additional message-specific information.
	 @return		A pointer to the caller of @c CreateWindow or
					@c CreateWindowEx.
	 */
	template< typename CallerT >
	[[nodiscard]]
	CallerT* GetWindowCaller(NotNull< HWND > window,
							 UINT message,
							 [[maybe_unused]] WPARAM wParam,
							 LPARAM lParam) noexcept;

	/**
	 Returns the caller of @c DialogBoxParam.

	 @pre			The @c lParam formal parameter of @c DialogBoxParam should
					be initialized to @c this and @c this should point to an
					instance of type @a CallerT.
	 @tparam		CallerT
					The caller type.
	 @param[in]		dialog
					A handle to the dialog box.
	 @param[in]		message
					The message.
	 @param[in]		wParam
					Additional message-specific information.
	 @param[in]		lParam
					Additional message-specific information.
	 @return		A pointer to the caller of @c DialogBoxParam.
	 */
	template< typename CallerT >
	[[nodiscard]]
	CallerT* GetDialogCaller(NotNull< HWND > dialog,
							 UINT message,
							 [[maybe_unused]] WPARAM wParam,
							 LPARAM lParam) noexcept;
}

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "platform\windows_utils.tpp"

#pragma endregion