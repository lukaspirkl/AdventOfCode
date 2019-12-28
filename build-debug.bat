@echo off
Powershell.exe -executionpolicy remotesigned -File  .\build.ps1 -type "Debug"
PAUSE
