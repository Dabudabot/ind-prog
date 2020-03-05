@echo off

REM My machine specific build script, replace it on your own
REM depending on compiler and linker which you wanna use
REM %1 - executable name
REM %2 - source main file
REM %3 - source solution file
REM %4 - log file

if not exist ".intermediate" mkdir ".intermediate"
if not exist "build" mkdir "build"

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
echo cl /EHsc /Wall /W3 /std:c++17 /Fo.intermediate\ %2 %3 /link /out:build\%1 >> %4
call cl /EHsc /Wall /W3 /std:c++17 /Fo.intermediate\ %2 %3 /link /out:build\%1 >> %4
if errorlevel 1 exit 1
exit 0