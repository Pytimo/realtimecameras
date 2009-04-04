@echo off

:: If we're already initted, abort
IF "%RTC_ENV_INIT%"=="1" GOTO DONE

echo Setting up Real Time Cameras environment...

:: Store the current directory
PUSHD .

:: See if OGRE SDK is installed
IF NOT EXIST "%OGRE_HOME%\bin\Release\OgreMain.dll" GOTO NOOGRE
IF NOT EXIST "%OGRE_HOME%\bin\Debug\OgreMain_d.dll" GOTO NOOGRE
IF NOT EXIST "%OGRE_HOME%\include\Ogre.h" GOTO NOOGRE
IF NOT EXIST "%OGRE_HOME%\lib\OgreMain.lib" GOTO NOOGRE
IF NOT EXIST "%OGRE_HOME%\lib\OgreMain_d.lib" GOTO NOOGRE

:: Ok, unless someone's being a jerk, the SDK's probably installed

:: Change to root dir
CD /d %~dp0..\..\

:: Write root directory to main RTC_PATH env var
FOR /f "tokens=1" %%B in ('CHDIR') do set RTC_PATH=%%B

:: Strip trailing backspace
IF "%RTC_PATH:~-1%"=="\" SET RTC_PATH=%RTC_PATH:~0,-1%

:: Put OGRE in the path
SET PATH=%PATH%;%OGRE_HOME%\bin\debug
SET PATH=%PATH%;%OGRE_HOME%\bin\release

:SUCCESS
SET RTC_ENV_INIT=1

:POPDONE
POPD
GOTO DONE

:NOOGRE
echo ERROR: Please install the OGRE SDK from http://www.ogre3d.org/
echo.
pause
GOTO POPDONE

:DONE