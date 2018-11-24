#include "includes.h"

Inject* ject = new Inject;

bool find_game_by_name(const char* process)
{
	PROCESSENTRY32 pInfo;

	HANDLE		  hGame = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hGame) {
		pInfo.dwSize = sizeof(PROCESSENTRY32);

		// get first process
		if (Process32First(hGame, &pInfo)) {
			do
			{
				// compare our process to target
				if (_stricmp(pInfo.szExeFile, process) == 0) {
					std::cout << "[FOUND][PID: " << pInfo.th32ProcessID << "] " << pInfo.szExeFile   << std::endl;
					ject->pid = pInfo.th32ProcessID;

					return true;
					
				}

			// while there is another process in buffer
			} while (Process32Next(hGame, &pInfo));
		}
	}
	else
	{
		std::cout << "fail" << std::endl;
		
	} 
	return false;
}

int main()
{

	if (!find_game_by_name("steam.exe"))
		return 0;
	

	ject->ourProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, ject->pid);

	if (!ject->ourProcess)
		return false;

	
	char dll[] = "C:\\Users\\iam0x\\source\\repos\\testdll\\Debug\\boop.dll";

	// load library 
	LPVOID LoadLibraryM = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if (!LoadLibraryM)
		return 0;

	std::cout << LoadLibraryM << std::endl;

	// Allocate memory in target for dll
	LPVOID alloc = VirtualAllocEx(ject->ourProcess, NULL, strlen(dll), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	// writing dll in to target
	if (WriteProcessMemory(ject->ourProcess, alloc, dll, strlen(dll), NULL))
	{
		
		CreateRemoteThread(ject->ourProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryM, alloc, NULL, NULL);
		CloseHandle(ject->ourProcess);
	}

	int a;
	std::cin >> a;
}

// how tf do you write an injector hold up