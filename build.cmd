@echo off

REM @author Daulet Tumbayev
REM @date 25.03.2020

REM My machine specific build script, replace it on your own
REM depending on compiler and linker which you wanna use
REM %1 - executable name
REM %2 - executable flag
REM %3 - source solution file
REM %4 - log file
REM these params must be enouth to build with any compiler and linker

if not exist ".intermediate" mkdir ".intermediate"
if not exist "build" mkdir "build"

REM replace the next lines
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
echo cl /EHsc /Wall /W3 /std:c++17 /Fo.intermediate\ /D%2 solution\task-one\main.cpp %3 /link /out:build\%1.exe >> %4
call cl /EHsc /Wall /W3 /std:c++17 /Fo.intermediate\ /D%2 solution\task-one\main.cpp %3 /link /out:build\%1.exe >> %4
if errorlevel 1 exit 1
exit 0