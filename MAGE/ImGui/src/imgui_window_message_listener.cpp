#pragma once

//-----------------------------------------------------------------------------
// Engine Includes
//-----------------------------------------------------------------------------
#pragma region

#include "imgui_window_message_listener.hpp"
#include "imgui_impl_win32.h"

#pragma endregion

//-----------------------------------------------------------------------------
// Engine Definitions
//-----------------------------------------------------------------------------
namespace mage {

	ImGuiWindowMessageListener ImGuiWindowMessageListener::s_listener;

	ImGuiWindowMessageListener::ImGuiWindowMessageListener() noexcept = default;

	ImGuiWindowMessageListener::ImGuiWindowMessageListener(
		const ImGuiWindowMessageListener& listener) noexcept = default;

	ImGuiWindowMessageListener::ImGuiWindowMessageListener(
		ImGuiWindowMessageListener&& listener) noexcept = default;

	ImGuiWindowMessageListener::~ImGuiWindowMessageListener() = default;

	ImGuiWindowMessageListener& ImGuiWindowMessageListener
		::operator=(const ImGuiWindowMessageListener& listener) noexcept = default;

	ImGuiWindowMessageListener& ImGuiWindowMessageListener
		::operator=(ImGuiWindowMessageListener&& listener) noexcept = default;

	void ImGuiWindowMessageListener
		::ProcessWindowMessage([[maybe_unused]] NotNull< HWND > window,
							   UINT message,
							   [[maybe_unused]] WPARAM wParam,
							   [[maybe_unused]] LPARAM lParam) {

		ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam);
	}

}