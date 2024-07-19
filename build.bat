@echo off
cd bin
mingw32-make.exe

if %ERRORLEVEL% equ 0 (
    echo Build successful, starting game...
    game.exe
) else (
    echo Build failed.
)
cd ..
pause
