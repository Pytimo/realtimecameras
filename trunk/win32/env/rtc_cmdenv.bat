@echo off
:: Sets up command prompt environment for RTC

:: Set directory
PUSHD .

cd /d %~dp0

CALL rtc_env.bat

:: Punt if environment setting failed
IF NOT "%RTC_ENV_INIT%"=="1" GOTO ERROR

CD /d %RTC_PATH%
TITLE Real Time Cameras Command Prompt

echo The Real Time Cameras environment has been set.
echo.

GOTO :EOF

:ERROR
POPD
echo Setting the RTC Environment failed.  This is a standard 
echo command prompt.
echo.
