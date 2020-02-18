@echo off

set FIND_NUMBER=find-number
set FIZZ_BUZZ=fizz-buzz

set EXAMPLE=example

if not exist "logs" mkdir "logs"
set LOG_FILE=logs\all.log

echo %date% %time% > %LOG_FILE%

echo ------------------ >> %LOG_FILE%
call exec_project.cmd %FIND_NUMBER% %EXAMPLE%
if errorlevel 1 goto :error_fn 
echo Project %FIND_NUMBER% SUCCESS >> %LOG_FILE%
goto :fb
:error_fn
echo Project %FIND_NUMBER% FAILED >> %LOG_FILE%

:fb
echo ------------------ >> %LOG_FILE%
call exec_project.cmd %FIZZ_BUZZ% %EXAMPLE%
if errorlevel 1 goto :error_fb
echo Project %FIZZ_BUZZ% SUCCESS >> %LOG_FILE%
goto :exit
:error_fb
echo Project %FIZZ_BUZZ% FAILED >> %LOG_FILE%

:exit