#include <iostream>
#include <windows.h>


//const char* gDllName = "C:\\Users\\RecaiCingoz\\source\\repos\\G64\\x64\\Debug\\G64.dll";
//const char* gDllName = "C:\\GDLL\\Aff.dll";
const char* gDllName = "C:\\Users\\RecaiCingoz\\source\\repos\\ApiHook\\x64\\Debug\\ApiHook.GDLL.dll";


int main()
{
	INT archNumber;
	HANDLE hProc, hTread;
	DWORD pid;
	PVOID address;
	SIZE_T lpnByteWritten;

	BOOL isWow64;
	std::cin >> pid;

	archNumber = 64;

	hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hProc == NULL)
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}

	const SIZE_T dllPathSize = strlen(gDllName) + 1;
	LPVOID aa;

	address = VirtualAllocEx(hProc, NULL, dllPathSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (address == NULL)
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}
	if (!WriteProcessMemory(hProc, address, gDllName, dllPathSize, &lpnByteWritten))
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}


	hTread = CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, address, 0, NULL);
	if (hTread == NULL)
	{
		std::cout << GetLastError() << std::endl;
		return -1;
	}


}









































//#include <Windows.h>
//#include <Psapi.h>

//HANDLE OpenProcessInject(const wchar_t* procname)
//{
//	DWORD need;
//	DWORD pids[2048] = { 0 };
//
//	if (!EnumProcesses(pids, sizeof(pids), &need))
//		return NULL;
//
//	for (DWORD i = 0; i < need / sizeof(DWORD); ++i) {
//		DWORD dw;
//		HMODULE mod;
//		HANDLE proc;
//		wchar_t pn[MAX_PATH] = { 0 };
//
//		proc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pids[i]);
//		if (proc) {
//			if (EnumProcessModules(proc, &mod, sizeof(mod), &dw)) {
//				GetModuleBaseNameW(proc, mod, pn, sizeof(pn) / sizeof(char));
//				if (_wcsicmp(pn, procname) == 0) {
//					CloseHandle(proc);
//					return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pids[i]);
//				}
//			}
//			CloseHandle(proc);
//		}
//	}
//	return NULL;
//}
//
//int main()
//{
//
//}