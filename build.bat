@echo off
REM build.bat — compila todos los .cpp y enlaza experiments.exe

setlocal

REM —— Configuración de compilador ——
set "CXX=g++"
set "CXXFLAGS=-std=c++17 -O2 -Wall -Wextra -I."

REM —— Lista de fuentes y nombre del ejecutable ——
set "SRCS=geometry.cpp union_find.cpp utils.cpp kruskal.cpp main.cpp"
set "TARGET=experiments.exe"
set "GRAPH=graphs.py"

REM —— Limpieza ——
echo Cleaning old artifacts...
del /Q *.o %TARGET% 2>nul

REM —— Compilación ——
echo Compiling sources...
for %%F in (%SRCS%) do (
  echo   %CXX% %CXXFLAGS% -c %%F -o %%~nF.o
  %CXX% %CXXFLAGS% -c %%F -o %%~nF.o
)

REM —— Enlazado ——
echo Linking into %TARGET%...
%CXX% %CXXFLAGS% *.o -o %TARGET%

REM —— Ejecución y registro de salida ——
echo Running %TARGET% and logging output to log.txt...
%TARGET% > log.txt
python %GRAPH%

echo.
echo Build complete. Run %TARGET% to execute your experiments.
endlocal