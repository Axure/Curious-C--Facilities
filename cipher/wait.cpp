#include <windows.h>
#include <tlhelp32.h>

void suspend(DWORD processId)
{
  HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

  THREADENTRY32 threadEntry;
  threadEntry.dwSize = sizeof(THREADENTRY32);

  Thread32First(hThreadSnapshot, &threadEntry);

  do
  {
    if (threadEntry.th32OwnerProcessID == processId)
    {
      HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE,
                                  threadEntry.th32ThreadID);

      SuspendThread(hThread);
      CloseHandle(hThread);
    }
  } while (Thread32Next(hThreadSnapshot, &threadEntry));

  CloseHandle(hThreadSnapshot);
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

}