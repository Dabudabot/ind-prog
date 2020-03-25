@echo off

call :exec README.??
goto :end

:exec
echo %1

:end