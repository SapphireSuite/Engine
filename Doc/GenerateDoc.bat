:: Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

@echo off

setlocal

:: Clear console.
cls


:: Query current directory name.
for %%I in (.) do set CurrDirName=%%~nxI
echo %CurrDirName%

:: Set directory to root.
if "%CurrDirName%" == "Doc" cd ../


:: Generate.
doxygen Doc\doxygen.config

:: Open in browser
start "" Doc\html\index.html


endlocal
