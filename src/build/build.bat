@echo off
echo Cleaning old files...
if exist mnk.exe del mnk.exe
if exist *.o del *.o

echo Compiling...
g++ -std=c++20 main.cpp ../background_logic/board.cpp ../background_logic/util.cpp -o mnk.exe

if %errorlevel% neq 0 (
    echo.
    echo [!] Compilation Failed.
    pause
    exit /b %errorlevel%
)

echo.
echo [!] Build Successful! Running program...
echo ---------------------------------------
mnk.exe
pause