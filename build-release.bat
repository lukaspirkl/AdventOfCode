@echo off
Powershell.exe -executionpolicy remotesigned -File  .\build.ps1 -type "Release"
PAUSE
