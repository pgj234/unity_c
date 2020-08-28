#include <windows.h> 

int WINAPI 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpCmdLine, int nShowCmd) 
{ 
  MessageBoxW (NULL, L"엽엽", L"가느다란 마법사", MB_OK | MB_ICONINFORMATION); 
  return 0; 
}