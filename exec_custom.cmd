@echo off

set CURRENT_DIR=%cd%
set PROJECT_NAME=%1%
shift
set STUDENT_NAME=%1%

cd %PROJECT_NAME%

if not exist "logs" mkdir "logs"
set LOG_FILE_STUDENT=logs\%STUDENT_NAME%.log

FINDSTR /R /V "add_executable (%PROJECT_NAME%." CMakeLists.txt > tmp
echo add_executable (%PROJECT_NAME% "main.cpp" "students/%STUDENT_NAME%.cpp") >> tmp
copy /Y tmp CMakeLists.txt
del tmp

echo %date% %time% > %LOG_FILE_STUDENT%
echo ------------------ >> %LOG_FILE_STUDENT%
echo BUILD: >> %LOG_FILE_STUDENT%

call cmake -B .intermediate
call cmake --build .intermediate

if errorlevel 1 goto :error

echo ----- SUCCESS >> %LOG_FILE_STUDENT%
echo RUN: >> %LOG_FILE_STUDENT%

call build\Debug\%PROJECT_NAME%.exe >> %LOG_FILE_STUDENT%

if errorlevel 1 goto :error

echo ----- SUCCESS >> %LOG_FILE_STUDENT%

cd %CURRENT_DIR%
if "%EXEC_CUSTOM%"=="TRUE" exit 0
exit /b 0

:error
echo ----- FAILED >> %LOG_FILE_STUDENT%
cd %CURRENT_DIR%
if "%EXEC_CUSTOM%"=="TRUE" exit 1
exit /b 1