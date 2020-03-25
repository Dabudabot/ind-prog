@echo off

REM My machine specific build script, replace it on your own
REM depending on compiler and linker which you wanna use
REM %1 - executable name
REM %2 - executable flag
REM %2 - source solution file
REM %3 - log file

if not exist ".intermediate" mkdir ".intermediate"
if not exist "build" mkdir "build"

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
echo cl /EHsc /Wall /W3 /std:c++17 /Fo.intermediate\ /D%2 solution\task-one\main.cpp %3 /link /out:build\%1.exe >> %4
call cl /EHsc /Wall /W3 /std:c++17 /Fo.intermediate\ /D%2 solution\task-one\main.cpp %3 /link /out:build\%1.exe >> %4
if errorlevel 1 exit 1
exit 0