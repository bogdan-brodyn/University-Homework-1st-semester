@echo off
chcp 1251
echo.
setlocal EnableDelayedExpansion
for /r %%i in (*.sln) do (
    echo Building solution: %%i
    msbuild %%i -nologo -consoleLoggerParameters:ErrorsOnly -p:WarningLevel=4;Configuration=Debug -target:Rebuild
    IF !ERRORLEVEL! EQU 0 (
	echo The build was completed successfully
    ) ELSE (
        echo The build failed
    )
)
echo.
echo.
for /d %%i in (.\*) do (
    cd %%i
    for /d %%j in (.\*) do (
        cd %%j
        for /r %%k in (*.Test.exe) do (
            echo Running test: %%k
            %%k >NUL
            IF !ERRORLEVEL! EQU 0 (
                echo The tests were passed successfully
            ) ELSE (
                echo The tests were not passed
            )
        )
        cd ..
    )
    cd ..
)
endlocal