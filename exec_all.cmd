@echo off

cls

set EXEC_CUSTOM=FALSE

if not exist "logs" mkdir "logs"

call :exec find-number
REM call :exec fizz-buzz
goto :exit

:exec
set LOG_FILE_PROJECT=logs\%1.log
echo %date% %time% > %LOG_FILE_PROJECT%
echo ------------------ >> %LOG_FILE_PROJECT%
for /d %%i in (students\*) do (
    echo calling exec_custom.cmd %1 %%i %1\main.cpp %%i\%1\solution.cpp
    echo exec_custom.cmd %1 %%i %1\main.cpp %%i\%1\solution.cpp >> %LOG_FILE_PROJECT%
    call exec_custom.cmd %1 %%i %1\main.cpp %%i\%1\solution.cpp
    if errorlevel 1 ( 
        echo call exec_custom.cmd %1 %%i %1\main.cpp %%i\%1\solution.cpp FAILED && echo %%i FAILED >> %LOG_FILE_PROJECT% 
    ) else ( 
        echo call exec_custom.cmd %1 %%i %1\main.cpp %%i\%1\solution.cpp SUCCESS && echo %%i SUCCESS >> %LOG_FILE_PROJECT% 
    )
)
echo ------------------ >> %LOG_FILE_PROJECT%
exit /b 0

:error


:exit
