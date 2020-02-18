@echo off

set EXEC_CUSTOM=TRUE
set PROJECT_NAME=%1%
shift

if not exist "logs" mkdir "logs"
set LOG_FILE_PROJECT=logs\%PROJECT_NAME%.log

echo %date% %time% > %LOG_FILE_PROJECT%
echo ------------------ >> %LOG_FILE_PROJECT%

set ALL_CLEAR=TRUE
:loop
if "%1"=="" goto :end_loop
set STUDENT_NAME=%1%
shift
echo %STUDENT_NAME% >> %LOG_FILE_PROJECT%
start /wait exec_custom.cmd %PROJECT_NAME% %STUDENT_NAME%
if errorlevel 1 goto :error
echo ------------------- SUCCESS >> %LOG_FILE_PROJECT%
goto :loop
:error
set ALL_CLEAR=FALSE
echo ------------------- FAILED >> %LOG_FILE_PROJECT%
goto :loop
:end_loop
echo ****************************************** >> %LOG_FILE_PROJECT%
if "%ALL_CLEAR%"=="TRUE" goto :result_success

:result_error
echo RESULT: FAILED >> %LOG_FILE_PROJECT%
exit /b 1

:result_success
echo RESULT: SUCCESS >> %LOG_FILE_PROJECT%
exit /b 0