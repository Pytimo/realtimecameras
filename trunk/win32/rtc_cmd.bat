@echo off
:: Create command prompt with environment
START %windir%\system32\cmd.exe /k %~dp0Env\rtc_cmdenv.bat
