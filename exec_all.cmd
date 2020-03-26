@echo off

REM @author Daulet Tumbayev
REM @date 25.03.2020
REM Run all students and all projects

cls

set EXEC_CUSTOM=FALSE

if not exist "logs" mkdir "logs"

call :exec find-number FIND_NUMBER
call :exec fizz-buzz FIZZ_BUZZ
goto :exit

:exec
set LOG_FILE_PROJECT=logs\%1.log
echo %date% %time% > %LOG_FILE_PROJECT%
echo ------------------ >> %LOG_FILE_PROJECT%
for /d %%i in (students\*) do (
    echo exec_custom.cmd %1 %2 %%i %%i\%1\
    echo exec_custom.cmd %1 %2 %%i %%i\%1\ >> %LOG_FILE_PROJECT%
    call exec_custom.cmd %1 %2 %%i %%i\%1\
    if errorlevel 1 ( 
        echo %%i FAILED && echo %%i FAILED >> %LOG_FILE_PROJECT% 
    ) else ( 
        echo %%i SUCCESS && echo %%i SUCCESS >> %LOG_FILE_PROJECT% 
    )
    pause
)
echo ------------------ >> %LOG_FILE_PROJECT%
exit /b 0

:exit
