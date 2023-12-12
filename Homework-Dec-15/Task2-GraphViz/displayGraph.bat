@echo off
IF NOT EXIST "%cd%\x64\Debug\Task2-GraphViz.exe" (
    ECHO Executable file not found
    EXIT /b
)
%cd%\x64\Debug\Task2-GraphViz.exe
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error code: %ERRORLEVEL%
    EXIT /b %ERRORLEVEL%
)
DOT -Tpng output.dot >graph.png
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error code: %ERRORLEVEL%
    EXIT /b %ERRORLEVEL%
)
DEL output.dot
graph.png
