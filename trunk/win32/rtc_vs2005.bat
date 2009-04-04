@echo off
:: Keep changes local
SETLOCAL

:: Initialize env
CALL %~dp0Env\rtc_env.bat

IF NOT "%RTC_ENV_INIT%"=="1" GOTO DONE

:: Start Visual Studio 2005

IF NOT EXISTS "%VS80COMNTOOLS%..\IDE\devenv.exe" GOTO VCEXPRESS

START "DummyTitle" "%VS80COMNTOOLS%..\IDE\devenv.exe"
GOTO DONE

:VCEXPRESS

IF NOT EXISTS "%VS80COMNTOOLS%..\IDE\vcexpress.exe" GOTO NODEVENV

START "DummyTitle" "%VS80COMNTOOLS%..\IDE\vcexpress.exe"
GOTO DONE

:NODEVENV
echo Could not find a valid installation of Visual Studio 2005 or VC Express
echo.
pause

:DONE

ENDLOCAL