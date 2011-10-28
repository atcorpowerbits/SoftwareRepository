@echo off

sqlcmd -S %1 -i .\%2 -b -o Database.log

echo %ERRORLEVEL%