@echo off
:: Keep changes local
SETLOCAL

:: Initialize env
CALL %~dp0Env\rtc_env.bat

IF NOT "%RTC_ENV_INIT%"=="1" GOTO DONE

:: Start Visual Studio 2005
START "DummyTitle" "%VS80COMNTOOLS%..\IDE\devenv.exe"

:DONE

ENDLOCAL