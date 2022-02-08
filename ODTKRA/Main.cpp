#include <iostream>

#define WINVER 0x0500
#include <Windows.h>
#include <string>

int main()
{
	LPCWSTR Target_window_Name = L"Oculus Debug Tool";
	HWND hWindowHandle = FindWindow(NULL, Target_window_Name);

	// Close ODT if it's already open because we have no idea what is currently selected
	if (hWindowHandle != NULL) {
		SendMessage(hWindowHandle, WM_CLOSE, 0, 0);
		SwitchToThisWindow(hWindowHandle, true);
	}

	Sleep(100); // not sure if needed

	// Starts ODT
	ShellExecute(NULL, L"open", L"C:\\Program Files\\Oculus\\Support\\oculus-diagnostics\\OculusDebugTool.exe", NULL, NULL, SW_SHOWDEFAULT);
	Sleep(1000); // not sure if needed

	hWindowHandle = FindWindow(NULL, Target_window_Name);
	SwitchToThisWindow(hWindowHandle, true);

	Sleep(100); // not sure if needed

	// Goes to the "Bypass Proximity Sensor Check" toggle
	for (int i = 0; i < 7; i++) {
		keybd_event(VK_DOWN, 0xE0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(VK_DOWN, 0xE0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		Sleep(30); // Looks cools :sunglasses:
	}

	ShowWindow(hWindowHandle, SW_MINIMIZE);

	HWND PropertGrid = FindWindowEx(hWindowHandle, NULL, L"wxWindowNR", NULL);
	HWND wxWindow = FindWindowEx(PropertGrid, NULL, L"wxWindow", NULL);

	// Presses up arrow key and then down every 600 seconds
	while (true) {
		SendMessage(wxWindow, WM_KEYDOWN, VK_UP, 0);
		SendMessage(wxWindow, WM_KEYUP, VK_UP, 0);
		SendMessage(wxWindow, WM_KEYDOWN, VK_DOWN, 0);
		SendMessage(wxWindow, WM_KEYUP, VK_DOWN, 0);
		Sleep(60000);
	}

	return 0;
}