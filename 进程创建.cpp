#include <tchar.h>
#include <wchar.h>
#include <windows.h>
#include <iostream>
#include <cstdio>
#include "Tlhelp32.h"
using namespace std;
#define PROCESS_PATH L"C:\\Program Files\\Windows NT\\Accessories\\wordpad.exe"

void open()
{
	WCHAR proPath[MAX_PATH];
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	BOOL bRet = ::CreateProcess(PROCESS_PATH, NULL , NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	
	printf("进程句柄：%d\n", pi.hProcess);
	printf("线程句柄：%d\n", pi.hThread);
	printf("进程的ID号：%d\n", pi.dwProcessId);
	printf("进程的主线程ID号：%d\n", pi.dwThreadId);
	return;
}
void close()
{
	PROCESSENTRY32 pe;
	HANDLE hProcess;
	pe.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Process32First(hSnapshot, &pe);
	do
	{
		if (!_tcsicmp(pe.szExeFile, _T("wordpad.exe")))
		{
			break;
		}

		pe.dwSize = sizeof(PROCESSENTRY32);
	} while (Process32Next(hSnapshot, &pe));

	STARTUPINFO si = { sizeof(si) };
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;

	hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID); //根据进程ID返回对象句柄
	::TerminateProcess(hProcess, 0);  //根据对象句柄结束进程
	CloseHandle(hSnapshot);
	CloseHandle(hProcess);
	return;
}
int _tmain(int argc, _TCHAR* argv[])
{
	char a;
	while (TRUE)
	{
		cout << "please input the command:";
		cin >> a;
		switch (a)
		{
		case '1':
			open();
			cout << "command confirmed" << endl;
			break;
		case '2':
			close();
			cout << "command confirmed" << endl;
			break;
		case '3':
			exit(0);
			break;
		default:
			cout << "wrong command" << endl;
		}

	}

}
