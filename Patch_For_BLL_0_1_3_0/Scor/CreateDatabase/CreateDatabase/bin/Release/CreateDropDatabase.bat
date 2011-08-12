@echo off

sqlcmd -S %1 -i .\%2 -b

echo %ERRORLEVEL%


