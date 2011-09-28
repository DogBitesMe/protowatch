#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <tlhelp32.h>
#include <shlwapi.h>

using namespace std;

#define PROCESS_NAME "diablo iii.exe"
#define DLL_NAME "protow.dll"
#define FUNC_NAME "StartDll"
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)

BOOL LoadDll(const char *procName, const char *dllName);
BOOL InjectDLL(DWORD dwProcessID, const char *dllName);
unsigned long GetTargetProcessIdFromProcname(const char *procName);
BOOL RaisePrivleges( HANDLE hToken, char *pPriv );
bool IsWindowsNT();

int main(){
	if(IsWindowsNT()){
		LoadDll(PROCESS_NAME, DLL_NAME);
	}
	else{
		MessageBox(0, "Your system does not support this method", "Error!", 0);
	}
	return 0;
}

BOOL LoadDll(const char *procName, const char *dllName){
	DWORD dwProcID = 0;
	char buf[50]={0};
	dwProcID = GetTargetProcessIdFromProcname(procName);
	//sprintf(buf, "Process Id to Inject: %d",dwProcID);
	//MessageBox(NULL, buf, "Loader", NULL);
	if(!dwProcID){
		MessageBox(NULL, "Process not found.","Loader", 0);
		return false;
	}
	if(!InjectDLL(dwProcID, dllName)){
		MessageBox(NULL, "Process located, but injection failed.", "Loader", 0);
	}
	return true;
}

typedef __stdcall int (*tfuncaddr)(int a);
typedef __stdcall HINSTANCE__ * (*tfunc_loadlib)(char * name);
typedef __stdcall void * (*tfunc_getprocaddr)(HINSTANCE__ * hlib, char * name);

struct inj {
	tfunc_loadlib LoadLibraryA;
	tfunc_getprocaddr GetProcAddress;
	char dllName[255];
	char funcName[255];
};

BOOL __stdcall LoadDll2(inj* ainj){
	HINSTANCE__ * hLib = ainj->LoadLibraryA(ainj->dllName);
	tfuncaddr funcaddr = (tfuncaddr)(ainj->GetProcAddress(hLib, ainj->funcName));
	funcaddr(0);
	return true;
}
BOOL AfterLoadDll2() {
}

BOOL InjectDLL(DWORD dwProcessID, const char *dllName){
	HANDLE hProc;
	HANDLE hToken;
	inj ainj;
	memcpy(ainj.dllName, dllName, strlen(dllName)+1);
	memcpy(ainj.funcName, FUNC_NAME, strlen(FUNC_NAME)+1);
	ainj.LoadLibraryA = (tfunc_loadlib)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	ainj.GetProcAddress = (tfunc_getprocaddr)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetProcAddress");
	
	char buf[50]={0};
	LPVOID RemoteString, LoadLibAddy;
	if(!dwProcessID)return false;
	HANDLE hCurrentProc = GetCurrentProcess();
	if (!OpenProcessToken(hCurrentProc,TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,&hToken)){
		sprintf(buf,"OpenProcessToken Error:%d\n", GetLastError());
		MessageBox(NULL, buf, "Loader", 0);
	}
	else{
		if (!RaisePrivleges(hToken, (char*)SE_DEBUG_NAME)){
			sprintf(buf, "SetPrivlegesSE_DEBUG_NAME Error:%d\n", GetLastError());
			MessageBox(NULL, buf, "Loader", 0);
		}
	}
	if (hToken)CloseHandle(hToken);
	hProc = OpenProcess(CREATE_THREAD_ACCESS, FALSE, dwProcessID);
	if(!hProc){
		sprintf(buf, "OpenProcess() failed: %d", GetLastError());
		MessageBox(NULL, buf, "Loader", 0);
		return false;
	}
	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if(!LoadLibAddy){
		sprintf(buf, "GetProcAddress() failed: %d", GetLastError());
		MessageBox(NULL, buf, "Loader", 0);
		return false;
	}
	RemoteString = (LPVOID)VirtualAllocEx(hProc, NULL, strlen(DLL_NAME) + 1 + (int)((UINT)&AfterLoadDll2 - (UINT)&LoadDll2), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if(!RemoteString){
		sprintf(buf, "VirtualAllocEx() failed: %d", GetLastError());
		MessageBox(NULL, buf, "Loader", 0);
		return false;
	}
	UINT CodeSize = (int)((UINT)&AfterLoadDll2 - (UINT)&LoadDll2);
	if(!WriteProcessMemory(hProc, (LPVOID)RemoteString, (void*)&LoadDll2, CodeSize, NULL)){
		sprintf(buf, "WriteProcessMemoery() failed: %d", GetLastError());
		MessageBox(NULL, buf, "Loader", 0);
		return false;
	}
	if(!WriteProcessMemory(hProc, (LPVOID)((UINT)RemoteString + CodeSize), (void*)&ainj, sizeof(inj), NULL)){
		sprintf(buf, "WriteProcessMemoery() failed: %d", GetLastError());
		MessageBox(NULL, buf, "Loader", 0);
		return false;
	}
	sprintf(buf, "CreateRemoteThread() %x", (UINT)RemoteString);
	MessageBox(NULL, buf, "Loader", 0);
	if(!CreateRemoteThread(hProc, NULL, 0, (LPTHREAD_START_ROUTINE)(LPVOID)(RemoteString), (LPVOID)((UINT)RemoteString + CodeSize), 0, NULL)){
		sprintf(buf, "CreateRemoteThread() failed: %d", GetLastError());
		MessageBox(NULL, buf, "Loader", 0);
		return false;
	}
	CloseHandle(hProc);
	return true;
}

unsigned long GetTargetProcessIdFromProcname(const char *procName){
	PROCESSENTRY32 pe;
	HANDLE thSnapshot;
	BOOL retval, ProcFound = false;
	thSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(thSnapshot == INVALID_HANDLE_VALUE){
		MessageBox(NULL, "Error: unable to create toolhelp snapshot", "Loader", 0);
		return false;
	}
	pe.dwSize = sizeof(PROCESSENTRY32);
	retval = Process32First(thSnapshot, &pe);
	while(retval) {
		if(StrStrI(pe.szExeFile, procName) ){
			ProcFound = true;
			break;
		}
		retval = Process32Next(thSnapshot,&pe);
		pe.dwSize = sizeof(PROCESSENTRY32);
	}
	if(ProcFound) return pe.th32ProcessID;
	else return 0;
}

BOOL RaisePrivleges( HANDLE hToken, char *pPriv ){
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tkp.Privileges[0].Luid.HighPart = 0;
	tkp.Privileges[0].Luid.LowPart = 0;
	
	if (!LookupPrivilegeValue(NULL, pPriv, &tkp.Privileges[0].Luid)){
		printf("LookupPrivilegeValue Error:%d\n", GetLastError());
		return FALSE;
	}
	int iRet = AdjustTokenPrivileges(hToken, FALSE, &tkp, 0x10, (PTOKEN_PRIVILEGES)NULL, 0);
	if (iRet == (int)NULL){
		printf( "AdjustTokenPrivileges Error:%d\n", GetLastError());
		return TRUE;
	}
	else{
		iRet = GetLastError();
		switch (iRet){
			case ERROR_NOT_ALL_ASSIGNED:{
				printf("AdjustTokenPrivileges ERROR_NOT_ALL_ASSIGNED\n" );
				return FALSE;
			}
			case ERROR_SUCCESS:{
				return TRUE;
			}
			default:{
				printf("AdjustTokenPrivileges Unknow Error:%d\n", iRet);
				return FALSE;
			}
		}
	}
}

bool IsWindowsNT(){
	DWORD version = GetVersion();
	DWORD majorVersion = (DWORD)(LOBYTE(LOWORD(version)));
	DWORD minorVersion = (DWORD)(HIBYTE(LOWORD(version)));
	return (version < 0x80000000);
}