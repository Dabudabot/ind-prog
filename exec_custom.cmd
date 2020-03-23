@echo off

set PROJECT_NAME=%1%
set PROJECT_DEFINE=%2%
set STUDENT_NAME=%3%
set STUDENT_SOL=%4%

if not exist "logs" mkdir "logs"
if not exist "logs\students" mkdir "logs\students"

set LOG_FILE_STUDENT=logs\%STUDENT_NAME%_%PROJECT_NAME%.log

echo %date% %time% > %LOG_FILE_STUDENT%
echo ------------------ >> %LOG_FILE_STUDENT%
echo BUILD: >> %LOG_FILE_STUDENT%

if not exist %STUDENT_SOL% goto :error

echo build.cmd %PROJECT_NAME% %PROJECT_DEFINE% %STUDENT_SOL% %LOG_FILE_STUDENT%
echo build.cmd %PROJECT_NAME% %PROJECT_DEFINE% %STUDENT_SOL% %LOG_FILE_STUDENT% >> %LOG_FILE_STUDENT%
start /wait build.cmd %PROJECT_NAME% %PROJECT_DEFINE% %STUDENT_SOL% %LOG_FILE_STUDENT%

if errorlevel 1 goto :error

echo ----- SUCCESS
echo ----- SUCCESS >> %LOG_FILE_STUDENT%

echo RUN: >> %LOG_FILE_STUDENT%

setlocal enabledelayedexpansion
set HAS_ERROR=FALSE
for /f %%f in ('dir /b "%PROJECT_NAME%\cases"') do ( 
    REM to call without new line
    echo | set /p dummyName=Running test: %PROJECT_NAME%\cases\%%f >> %LOG_FILE_STUDENT%
    set errorlevel=
    call build\%PROJECT_NAME%.exe %PROJECT_NAME%\cases\%%f
    if !errorlevel!==0 ( 
        echo build\%PROJECT_NAME%.exe %PROJECT_NAME%\cases\%%f SUCCESS
        echo ------- OK >> %LOG_FILE_STUDENT% 
    ) else (
        set HAS_ERROR=TRUE
        echo build\%PROJECT_NAME%.exe %PROJECT_NAME%\cases\%%f FAIL 
        echo ------- FAIL >> %LOG_FILE_STUDENT% 
    )
)

del "build\%PROJECT_NAME%.exe"

if "%HAS_ERROR%"=="TRUE" goto :error

echo ----- SUCCESS >> %LOG_FILE_STUDENT%
echo SUCCESS
if "%EXEC_CUSTOM%"=="TRUE" exit 0
exit /b 0

:error
echo ERRORS
echo ----- FAILED >> %LOG_FILE_STUDENT%
if "%EXEC_CUSTOM%"=="TRUE" exit 1
exit /b 1