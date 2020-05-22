#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "ui\window.hpp"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Declarations
//-----------------------------------------------------------------------------
namespace mage {

	/**
	 A class of window message listeners.
	 */
	class ImGuiWindowMessageListener final : public WindowMessageListener {

	public:

		//---------------------------------------------------------------------
		// Class Member Variables
		//---------------------------------------------------------------------

		static ImGuiWindowMessageListener s_listener;

		//---------------------------------------------------------------------
		// Constructors and Destructors
		//---------------------------------------------------------------------

		/**
		 Constructs an ImGui window message listener.
		 */
		ImGuiWindowMessageListener() noexcept;

		/**
		 Constructs an ImGui window message listener from the given window
		 message listener.

		 @param[in]		listener
						A reference to the ImGui window message listener to
						copy.
		 */
		ImGuiWindowMessageListener(const ImGuiWindowMessageListener& listener) noexcept;

		/**
		 Constructs an ImGui  window message listener by moving the given window
		 message listener.

		 @param[in]		listener
						A reference to the ImGui window message listener to move.
		 */
		ImGuiWindowMessageListener(ImGuiWindowMessageListener&& listener) noexcept;

		/**
		 Destructs this ImGui window message listener.
		 */
		virtual ~ImGuiWindowMessageListener();

		//---------------------------------------------------------------------
		// Assignment Operators
		//---------------------------------------------------------------------

		/**
		 Copies the given ImGui window message listener to this ImGui window
		 message listener.

		 @param[in]		listener
						A reference to the ImGui window message listener to
						copy.
		 @return		A reference to the copy of the given ImGui window
						message listener (i.e. this ImGui window message
						listener).
		 */
		ImGuiWindowMessageListener& operator=(
			const ImGuiWindowMessageListener& listener) noexcept;

		/**
		 Moves the given ImGui window message listener to this ImGui window
		 message listener.

		 @param[in]		listener
						A reference to the ImGui window message listener to
						move.
		 @return		A reference to the moved ImGui window message listener
						(i.e. this ImGui window message listener).
		 */
		ImGuiWindowMessageListener& operator=(
			ImGuiWindowMessageListener&& listener) noexcept;

		//---------------------------------------------------------------------
		// Member Methods
		//---------------------------------------------------------------------

		/**
		 Processes the given message sent to a window.

		 @param[in]		window
						A handle to the window.
		 @param[in]		message
						The message.
		 @param[in]		wParam
						Additional message information. The contents of this
						parameter depend on the value of @a msg.
		 @param[in]		lParam
						Additional message information. The contents of this
						parameter depend on the value of @a msg.
		 */
		virtual void ProcessWindowMessage([[maybe_unused]] NotNull< HWND > window,
										  UINT message,
										  [[maybe_unused]] WPARAM wParam,
										  [[maybe_unused]] LPARAM lParam) override;
	};
}