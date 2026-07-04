@echo off
cls

g++ ^
main.cpp ^
controllers/*.cpp ^
services/*.cpp ^
models/*.cpp ^
-o backend.exe

if %errorlevel%==0 (
    echo.
    echo ===== COMPILACION EXITOSA =====
    backend.exe
) else (
    echo.
    echo ===== ERROR DE COMPILACION =====
)

pause