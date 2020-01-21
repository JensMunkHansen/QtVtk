@echo off

pushd %~dp0

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

REM Variable used in this script - name is arbitrary
set QTDIR=C:/Qt/Qt5.12.3/5.12.3/msvc2017_64

mkdir build

set PATH="C:\Program Files\CMake\bin";%QTDIR%\bin;%PATH%
set VTK_DIR=E:/code/bin/VTK

cmake -H%~dp0 -B%~dp0\build -G "Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH=%VTK_DIR%;%QTDIR%

REM Create solution
cd %~dp0\build

REM Build solution
msbuild QtVtk.sln /p:Configuration=Release

cd %~dp0
